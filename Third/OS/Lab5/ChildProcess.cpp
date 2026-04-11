#include <iostream>
#include <windows.h>
#include <ctime>
#include <chrono>
#include <iostream>
#include <thread>
#include <handleapi.h>
#include <memoryapi.h>
#include <random>
#include <array>

#define MUTEX_POLICY MUTEX_ALL_ACCESS
constexpr auto process_count = 5;

enum user_state
{
    await,
    try_deposit,
    deposit,
    try_withdraw,
    withdraw,
    try_show,
    show
};

struct bank_account
{
    int balance;
    std::array<user_state, process_count> users_state;
};

std::string enum_to_str(const user_state state)
{
    switch (state)
    {
        case await:
            return "Ожидание";
        case try_deposit:
            return "Попытка депозита";
        case deposit:
            return "Депозит";
        case try_withdraw:
            return "Попытка снятия";
        case withdraw:
            return "Снятие";
        case try_show:
            return "Попытка просмотра";
        case show:
            return "Просмотр";
    }
}

void print_status(const bank_account& account)
{
	const HANDLE h_mutex = OpenMutex(MUTEX_POLICY, FALSE, L"GlobalWrite");
    DWORD wait = WaitForSingleObject(h_mutex, INFINITE);

    for (size_t i = 0; i < process_count; ++i)
    {
        std::cout << "U" << i << ": " << std::setw(17) << enum_to_str(account.users_state.at(i)) << " ";

        if (i == process_count - 1)
        {
            std::cout << "Баланс: " << account.balance << std::endl;
        }
    }

    ReleaseMutex(h_mutex);
    CloseHandle(h_mutex);
}

void set_status(bank_account& account, const size_t id, const user_state status)
{
    account.users_state[id] = status;
    print_status(account);
}

int int_rand(const int& min, const int& max)
{
    static thread_local std::mt19937* generator = nullptr;
    if (!generator) generator = new std::mt19937(clock());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(*generator);
}

static void bank_deposit(bank_account& account, const size_t id)
{
    HANDLE hMutex = OpenMutex(MUTEX_POLICY, FALSE, L"GlobalAccess");

    if (hMutex == nullptr)
    {
        std::cout << "Не удалось открыть семафор. Ошибка: " << GetLastError() << std::endl;
        return;
    }

    set_status(account, id, user_state::try_deposit);
    DWORD wait = WaitForSingleObject(hMutex, INFINITE); 
    
	account.balance += 100;

	set_status(account, id, user_state::deposit);
	std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	set_status(account, id, user_state::await);
	ReleaseMutex(hMutex);

    CloseHandle(hMutex);
}

static void bank_withdraw(bank_account& account, const size_t id)
{
    HANDLE hMutex = OpenMutex(MUTEX_POLICY, FALSE, L"GlobalAccess");

    if (hMutex == nullptr)
    {
        std::cout << "Не удалось открыть семафор. Ошибка: " << GetLastError() << std::endl;
        return;
    }

    set_status(account, id, user_state::try_withdraw);

    DWORD wait = WaitForSingleObject(hMutex, INFINITE);
    
    if (account.balance >= 100)
    {
        account.balance -= 100;
        
    }

    set_status(account, id, user_state::withdraw);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    set_status(account, id, user_state::await);
    ReleaseMutex(hMutex);
    
    CloseHandle(hMutex);
}

static void show_balance(bank_account& account, const size_t id)
{
    HANDLE hMutex = OpenMutex(MUTEX_POLICY, FALSE, L"GlobalAccess");

    if (hMutex == nullptr)
    {
        std::cout << "Не удалось открыть семафор. Ошибка: " << GetLastError() << std::endl;
        return;
    }
    set_status(account, id, user_state::try_show);
    DWORD wait = WaitForSingleObject(hMutex, INFINITE);

    set_status(account, id, user_state::show);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    set_status(account, id, user_state::await);

    ReleaseMutex(hMutex);
    CloseHandle(hMutex);
}

int main(int argc, char* argv[])
{
	const HANDLE h_mutex = OpenMutex(MUTEX_POLICY, FALSE, L"GlobalWrite");

    if (h_mutex == nullptr)
    {
        std::cout << "Не удалось открыть мьютекс." << std::endl;
        return 1;
    }

    CloseHandle(h_mutex);

    if (argc < 2)
    {
        std::cout << "Необходимо передать целое число в аргументы командной строки!" << std::endl;
        return 1;
    }

	const size_t number = std::atoi(argv[1]);

	const HANDLE hMapping = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(bank_account), L"SharedMemory");
    if (hMapping == nullptr)
    {
        std::cerr << "Не удалось создать разделяемую память." << std::endl;
        return 1;
    }

	const LPVOID pView = MapViewOfFile(hMapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(bank_account));
    if (pView == nullptr)
    {
        std::cerr << "Не удалось подключить разделяемую память к процессу." << std::endl;
        CloseHandle(hMapping);
        return 1;
    }

    bank_account account = *(bank_account*)pView;

    size_t i = 0;
    while (++i < 5)
    {
	    switch (size_t j = int_rand(0, 2))
        {
            case 0: { bank_deposit(*(bank_account*)pView, number); break; }
            case 1: { bank_withdraw(*(bank_account*)pView, number); break; }
            case 2: { show_balance(*(bank_account*)pView, number); break; }
        }
    }

    UnmapViewOfFile(pView);
    CloseHandle(hMapping);

    return 0;
}
