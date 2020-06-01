#include <iostream>
extern "C" void __cdecl SortString(char** ss, int length);


int main() {

	char str1[] = { "e" };
	char str2[] = { "d" };
	char str3[] = { "c" };
	char str4[] = { "b" };
	char str5[] = { "a" };

	char** slovar = new char* [5];
	slovar[0] = str1;
	slovar[1] = str2;
	slovar[2] = str3;
	slovar[3] = str4;
	slovar[4] = str5;
	for (int i = 0; i < 5; i++) {
		std::cout << slovar[i] << '\n';
	}
	std::cout << "\n\n";
	//Придумай замену ecx иначе крашится repe
	__asm {
		mov ebx, slovar;
		push ebx;
		mov ebx, 5;
		push ebx;
		call SortString;
		add esp, 8;
	}
	for (int i = 0; i < 5; i++) {
		std::cout << slovar[i] << '\n';
	}

	return 0;
}