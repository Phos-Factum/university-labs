#include <array>
#include <windows.h>
#include <iostream>
#include <random>
#include <vector>
#include <excpt.h>
#include <tchar.h>

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

namespace 
{
	bool set_locale()
	{
		return SetConsoleCP(1251) != 0 && SetConsoleOutputCP(1251) != 0;
	}

	void print_error_message(const DWORD error_code)
	{
		LPSTR message_buffer = nullptr;

		if (const DWORD size = FormatMessageA(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
			nullptr,
			error_code,
			MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),
			reinterpret_cast<LPSTR>(&message_buffer),
			0,
			nullptr
		); size > 0)
		{
			std::cout << "Error: " << error_code << std::endl;
			std::cout << "Error text: " << message_buffer << std::endl;
		}
		else
		{
			std::cerr << "Unable to get error text." << std::endl;
		}

		LocalFree(message_buffer);
	}
}

int main()
{
	if (!set_locale())
	{
		print_error_message(GetLastError());
		return 1;
	}

	bank_account account
	{
		account.balance = 911,
		account.users_state = {await}
	};

	SECURITY_ATTRIBUTES security_attributes{};
	security_attributes.nLength = sizeof(SECURITY_ATTRIBUTES);
	security_attributes.bInheritHandle = TRUE;
	security_attributes.lpSecurityDescriptor = nullptr;

	HANDLE h_access_mutex = CreateMutexW(
		&security_attributes, 
		FALSE, 
		L"GlobalAccess");
	HANDLE h_write_mutex = CreateMutexW(
		&security_attributes, 
		FALSE, 
		L"GlobalWrite");

	const HANDLE h_mapping = CreateFileMapping(INVALID_HANDLE_VALUE, nullptr, PAGE_READWRITE, 0, sizeof(bank_account), L"SharedMemory");
	if (h_mapping == nullptr)
	{
		std::cerr << "Не удалось создать разделяемую память." << std::endl;
		print_error_message(GetLastError());
		CloseHandle(h_mapping);
		return 1;
	}

	const LPVOID p_view = MapViewOfFile(h_mapping, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(bank_account));
	if (p_view == nullptr)
	{
		std::cerr << "Не удалось подключить разделяемую память к процессу." << std::endl;
		print_error_message(GetLastError());
		CloseHandle(h_mapping);
		return 1;
	}

	*static_cast<bank_account*>(p_view) = account;
	std::vector<PROCESS_INFORMATION> processes;

	for (int i = 0; i < 5; ++i)
	{
		STARTUPINFO si;
		PROCESS_INFORMATION pi;

		ZeroMemory(&si, sizeof(si));
		si.cb = sizeof(si);
		ZeroMemory(&pi, sizeof(pi));

		TCHAR command_line[256];
		_stprintf_s(command_line, _T("ChildProcess %d"), i);
		if (const BOOL create_process_status 
			= CreateProcessW(nullptr, 
	              command_line,
	              nullptr,
	              nullptr,
	              FALSE, 
	              0, 
	              nullptr,
	              nullptr,
	              &si, 
	              &pi); !create_process_status)
		{
			std::cerr << "Child process run error." << std::endl;
			print_error_message(GetLastError());
			UnmapViewOfFile(p_view);
			CloseHandle(h_mapping);
			return 1;
		}

		processes.push_back(pi);

		if (!DuplicateHandle(GetCurrentProcess(), h_access_mutex, pi.hProcess, &h_access_mutex, MUTEX_POLICY, TRUE, DUPLICATE_SAME_ACCESS))
		{
			std::cout << "Не удалось передать дескриптор мьютекса." << std::endl;
			print_error_message(GetLastError());
			TerminateProcess(pi.hProcess, 1);
			CloseHandle(pi.hProcess);
			return 1;
		}
		if (!DuplicateHandle(GetCurrentProcess(), h_write_mutex, pi.hProcess, &h_write_mutex, MUTEX_POLICY, TRUE, DUPLICATE_SAME_ACCESS))
		{
			std::cout << "Не удалось передать дескриптор мьютекса." << std::endl;
			print_error_message(GetLastError());
			TerminateProcess(pi.hProcess, 1);
			CloseHandle(pi.hProcess);
			return 1;
		}
	}

	std::vector<HANDLE> process_handles;
	process_handles.reserve(processes.size());
	for (const auto& process_info : processes)
	{
		process_handles.push_back(process_info.hProcess);
	}

	const DWORD wait_result = WaitForMultipleObjects(process_handles.size(), process_handles.data(), TRUE, INFINITE);
	if (wait_result == WAIT_FAILED)
	{
		std::cerr << "Произошла ошибка при ожидании процессов." << std::endl;
		print_error_message(GetLastError());
		return 1;
	}

	for (const auto& process_handle : process_handles)
	{
		CloseHandle(process_handle);
	}

	std::cout << "Shutting down..." << std::endl;

	CloseHandle(h_access_mutex);
	CloseHandle(h_write_mutex);
	UnmapViewOfFile(p_view);
	CloseHandle(h_mapping);

	return 0;
}
