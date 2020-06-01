#include <iostream>
extern "C" int __cdecl StrIndex(char* source, char* substring);

int main() {

	char str1[]{ "abcabc" };
	char str2[]{ "q" };

	int index;
	__asm {
		lea ebx, str2;
		push ebx;
		lea ebx, str1;
		push ebx;
		call StrIndex;
		add esp, 8;
		mov index, eax;
	}
	std::cout << index << '\n';
	return 0;
}