#include <iostream>
#include <limits>

bool treug(unsigned int a, unsigned int b, unsigned int c) {
	bool result = false;
	__asm {
		mov eax, a;
		cmp eax, b;
		ja first_step;
		mov eax, b;
		jmp second_step;
	first_step:
		cmp eax, c;
		ja second_step;
		mov eax, c;
	second_step:
		cmp eax, a;
		je case_for_a;
		cmp eax, b;
		je case_for_b;
		cmp eax, c;
		je case_for_c;
	case_for_a:
		sub eax, b;
		cmp eax, c;
		jb end_;
		jmp end_false;
	case_for_b:
		sub eax, a;
		cmp eax, c;
		jb end_;
		jmp end_false;
	case_for_c:
		sub eax, a;
		cmp eax, b;
		jb end_;
		jmp end_false;
	end_:
		mov result, 1;
	end_false:

	}
	return result;
}

int NumberOfSolution(int a, int b, int c) {
	int result;
	__asm {
		mov eax, b;
		shr eax, 1;
		imul eax;
		mov esi, eax;
		mov edi, edx;

		mov eax, a;
		mov ebx, c;
		imul ebx;
		
		cmp edx, edi;
		je if_equals;
		jg if_bigger;
		jl if_lower;
	if_equals:
		cmp eax, esi;
		je if_equals_1;
		jg if_bigger;
		jl if_lower;
		jmp end_;
	if_equals_1:
		mov result, 1;
		jmp end_;
	if_bigger:
		mov result, 0;
		jmp end_;
	if_lower:
		mov result, 2;
		jmp end_;
	end_:

	}
	return result;
}

int factorial(int a) {
	int result;
	__asm {
		mov ebx, a;
		mov eax, 1;
		mov ecx, 1;
		cmp a, 0;
		jle error_end;

	checking:
		cmp ebx, ecx;
		jge cikl;
		jmp end_;
	cikl:
		imul eax, ecx;
		add ecx, 1;
		jmp checking;
	error_end:
		mov eax, 0;
	end_:
		mov result, eax;
	}
	return result;
}

int main() {
//	std::cout << factorial(-5);
//	std::cout << treug(UINT_MAX - 3, UINT_MAX - 7, UINT_MAX - 3);
	std::cout << NumberOfSolution(-10000, -1000000000, -10000);
//	std::cout << treug(3, 7, 3);
//	std::cout << NumberOfSolution(1, 1, 1);
	return 0;
}