# Process
easy to use wrappers for reading and writing process memory externally

# Example program
```cpp
#include "include/Process.hpp"

int main()
{
	Process process;
	while (!process.attach(L"process.exe"))
		Sleep(500);

	while (!process.getModule(L"module.dll"))
		Sleep(500);

	auto valueRead = process.read<int>(0x4);
	process.write<int>(0x4, 1);

	return 0;
}
```