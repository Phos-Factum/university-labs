#include <windows.h>
#include <chrono>
#include <iostream>
#include <random>
#include <thread>
#include <locale.h>

constexpr const size_t N = 5;

enum class State
{
    THINKING = 0,
    HUNGRY = 1,
    EATING = 2,
};

State state[N];

CRITICAL_SECTION critical_region_mtx;
CRITICAL_SECTION output_mtx;

void print_philosophers_status()
{
    EnterCriticalSection(&output_mtx);
    for (size_t i = 0; i < N; ++i)
    {
        std::cout << "Философ" << i + 1 << ":";
        switch (state[i])
        {
        case State::THINKING:
            std::cout << " думает ";
            break;
        case State::HUNGRY:
            std::cout << " голоден";
            break;
        case State::EATING:
            std::cout << " ест    ";
            break;
        }
        if (i < N - 1)
        {
            std::cout << " | ";
        }
    }
    std::cout << std::endl;
    LeaveCriticalSection(&output_mtx);
}

size_t inline left(size_t i)
{
    return (i - 1 + N) % N;
}

size_t inline right(size_t i)
{
    return (i + 1) % N;
}

HANDLE both_forks_available[N];

size_t my_rand(size_t min, size_t max)
{
    static std::mt19937 rnd(std::time(nullptr));
    return std::uniform_int_distribution<>(min, max)(rnd);
}

void test(size_t i)
{
    if (state[i] == State::HUNGRY &&
        state[left(i)] != State::EATING &&
        state[right(i)] != State::EATING)
    {
        state[i] = State::EATING;
        ReleaseSemaphore(both_forks_available[i], 1, NULL);
    }
}

void think(size_t i)
{
    size_t duration = my_rand(400, 800);
    state[i] = State::THINKING;
    print_philosophers_status();
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void take_forks(size_t i)
{
    EnterCriticalSection(&critical_region_mtx);
    state[i] = State::HUNGRY;
    print_philosophers_status();
    test(i);
    LeaveCriticalSection(&critical_region_mtx);
    WaitForSingleObject(both_forks_available[i], INFINITE);
}

void eat(size_t i)
{
    size_t duration = my_rand(400, 800);
    state[i] = State::EATING;
    print_philosophers_status();
    std::this_thread::sleep_for(std::chrono::milliseconds(duration));
}

void put_forks(size_t i)
{
    EnterCriticalSection(&critical_region_mtx);
    state[i] = State::THINKING;
    test(left(i));
    test(right(i));
    LeaveCriticalSection(&critical_region_mtx);
}

void philosopher(size_t i)
{
    while (true)
    {
        think(i);
        take_forks(i);
        eat(i);
        put_forks(i);
    }
}

DWORD WINAPI PhilosopherThread(LPVOID lpParam)
{
    int id = reinterpret_cast<int>(lpParam);
    philosopher(id);
    return 0;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    system("chcp 1251");

    InitializeCriticalSection(&critical_region_mtx);
    InitializeCriticalSection(&output_mtx);

    for (size_t i = 0; i < N; ++i)
    {
        both_forks_available[i] = CreateSemaphore(NULL, 0, 1, NULL);
    }

    HANDLE threads[N];
    for (int i = 0; i < N; ++i)
    {
        threads[i] = CreateThread(NULL, 0, PhilosopherThread, reinterpret_cast<LPVOID>(i), 0, NULL);
    }

    WaitForMultipleObjects(N, threads, TRUE, INFINITE);

    for (size_t i = 0; i < N; ++i)
    {
        CloseHandle(threads[i]);
        CloseHandle(both_forks_available[i]);
    }

    for (size_t i = 0; i < N; ++i)
    {
        CloseHandle(both_forks_available[i]);
    }

    DeleteCriticalSection(&critical_region_mtx);
    DeleteCriticalSection(&output_mtx);

    return 0;
}
