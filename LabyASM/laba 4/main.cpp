#include <iostream>

void Subtraction(int** matrix, int n, int m) {

	__asm {
		mov ebx, matrix;
		mov eax, [ebx];
		mov edx, [eax][0];
		mov ecx, n;

	begin_n:
		mov eax, [ebx];
		push ecx;
		mov ecx, m;
		xor esi, esi;

	begin_m:
		cmp edx, [eax][esi * 4];
		jg if_less;

	continue_:
		inc esi;
		loop begin_m;
		add ebx, 4;
		pop ecx;
		loop begin_n;
		jmp end_;

	if_less:
		mov edx, [eax][esi * 4];
		jmp continue_;

	end_:
		mov ebx, matrix;
		mov eax, [ebx];
		mov ecx, n;

	begin_n_1:
		mov eax, [ebx];
		push ecx;
		mov ecx, m;
		xor esi, esi;

	begin_m_1:
		sub [eax][esi*4], edx;
		inc esi;
		loop begin_m_1;
		add ebx, 4;
		pop ecx;
		loop begin_n_1;
	}
}


int main() {

	int** matrix = new int* [2];
	matrix[0] = new int[3]{ 12,11,10 };
	matrix[1] = new int[3]{ 8,7,6 };
	Subtraction(matrix, 2, 3);
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 3; j++) {
			std::cout << matrix[i][j]<<" ";
		}
		std::cout << '\n';
	}

	return 0;
}