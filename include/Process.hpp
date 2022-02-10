#pragma once

#include <Windows.h>
#include <string>

// Class for reading and writing memory to a process externally
class Process
{
public:
	Process();
	~Process();

	// Finds process and calls OpenProcess()
	// returns process id, if it can't find the program returns 0
	int attach(std::wstring process_name);

	// Returns the base address of a loaded module
	// if it can't find the module it returns 0
	uintptr_t getModule(std::wstring module_name);

	// Reads a memory address within the process
	// returns 0 if ReadProcessMemory fails
	// Example:
	//    auto value = process.read<int>(0x99999);
	template<typename T>
	T read(uintptr_t address)
	{
		T buffer;
		if (!ReadProcessMemory(handle, reinterpret_cast<void*>(address), &buffer, sizeof(T), 0))
			return 0; // the j af ngl

		return buffer;
	}

	// Writes to a memory address within the process
	// returns false if WriteProcessMemory fails, otherwise, true
	// Example:
	//    process.write<int>(0x99999, 1);
	template<typename T>
	bool write(uintptr_t address, T value)
	{
		if (!WriteProcessMemory(handle, reinterpret_cast<void*>(address), &value, sizeof(value), 0))
			return false;

		return true;
	}

private:
	DWORD pid;
	HANDLE handle;
};