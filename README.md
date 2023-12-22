# proc
[process](https://github.com/kawaiiandgothic/process) rewritten in c for 64 bit

# usage
```c
#include "../proc.h"

int main(void)
{
	proc_init("window name");
	size_t dll = proc_module(L"dll.dll");
	void* dll_boobs_val = proc_read(dll + 0x80085);
}
```
