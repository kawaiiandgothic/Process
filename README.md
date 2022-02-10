# Process
Easy to use wrappers for reading and writing process memory externally

# Example program: 
```cpp
#include "include/Process.hpp"

int main()
{
    Process process;
    
    while (!process.attach(L"process.exe"))
        Sleep(500);

    auto dll = process.getModule(L"module.dll");
    auto valueRead = process.read<int>(dll + 0xDEEZ);
    
    process.write<int>(valueRead, 1);

    return 0;
}
```
