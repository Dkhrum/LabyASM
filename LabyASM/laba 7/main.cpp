#include <iostream>

extern "C" {
int __cdecl TrimAll(char* s, int l);
}
int main() {

	char str1[] = { "  a b  " };
	int l = 7;
	int newLength;

	__asm {
		mov ebx, l;
		push ebx;
		lea ebx, str1;
		push ebx;
		call TrimAll;
		add esp, 8;
		mov newLength, eax;
	}


	std::cout << "^";
	for (auto i = 0; i < newLength; ++i)
	{
		std::cout << str1[i];
	}
	std::cout << "$";

	std::cout << std::endl;
	return 0;
}