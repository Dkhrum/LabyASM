#include <iostream>
#include <limits>

void Subtraction(int* a, int* b) {
	int first_result = *a;
	int second_result = *b;
	int average = 1;

	__asm {

		mov eax, first_result;
		cmp eax, 0;
		je end_1;
		mov ebx, second_result;
		cmp eax, ebx;
		jg first_way;
		mov eax, second_result;
		mov ebx, first_result;

	first_way:
		cdq;
		idiv ebx;
		cmp edx, 0;
		je end_;
		mov eax, ebx;
		mov ebx, edx;
		jmp first_way;

	end_:
		mov average, ebx;

	end_1:
	}
	*a /= average;
	*b /= average;
}

long long int SumOfTheElements(int* arr, int size_1) {
	long long int positive_result = 0;
	long long int negative_result = 0;
	unsigned int first_part_positive = 0;
	unsigned int first_part_negative = 0;
	unsigned int second_part_positive = 0;
	unsigned int second_part_negative = 0;

	__asm {
		mov ebx, arr;
		mov ecx, size_1;
		mov eax, 0;
		mov edx, 0;
		mov esi, 0;
		mov edi, 0;
	
	begin:
		cmp dword ptr[ebx], 0;
		jnl positive;
		jmp negative;

	positive:
		add eax, dword ptr[ebx];
		jnc upper;
		inc edx;

	upper:
		add ebx, 4;
		loop begin;
		jmp end_;

	negative:
		push ecx;
		mov ecx, dword ptr[ebx];
		neg ecx;
		add esi, ecx;
		pop ecx;
		jnc upper_neg;
		inc edi;

	upper_neg:
		add ebx, 4;
		loop begin;

	end_:
		mov first_part_positive, eax;
		mov first_part_negative, esi;
		mov second_part_positive, edx;
		mov second_part_negative, edi;
	}
	positive_result += second_part_positive;
	positive_result = positive_result << 32;
	positive_result += first_part_positive;
	negative_result += second_part_negative;
	negative_result = negative_result << 32;
	negative_result += first_part_negative;
	positive_result -= negative_result;
	return positive_result;
}

int NumberOfMods(int* arr) {
	int tmp;
	int size_ = 7;
	int* mods = new int[size_];
	int size_mods = 0;
	int max_value;

	__asm {
		mov ebx, arr;
		mov edi, mods;
		mov ecx, size_;
		mov eax, 1;

	begin_1:
		cmp ecx, 0;
		jle second_step;
		mov edx, [ebx];
		mov esi, 1;
		mov tmp, 1;

	begin_2:
		cmp esi, ecx;
		jge continue_;
		cmp edx, [ebx + esi * 4];
		je increment;
		inc esi;
		jmp begin_2;

	increment:
		inc tmp;
		inc esi;
		jmp begin_2;

	continue_:
		cmp tmp, eax;
		jg if_bigger;
		sub ecx, 1;
		add ebx, 4;
		jmp begin_1;

	if_bigger:
		mov eax, tmp;
		jmp begin_1;

	second_step:
		sub ebx, 28;
		mov ecx, size_;
		mov ebx, arr;
		mov max_value, eax;

	begin_1_1:
		cmp ecx, 0;
		jle end_;
		mov edx, [ebx];
		mov esi, 1;
		mov eax, 1;

	begin_2_1:
		cmp esi, ecx;
		jge continue_1;
		cmp edx, [ebx + esi * 4];
		je increment_1;
		inc esi;
		jmp begin_2_1;

	increment_1:
		inc eax;
		inc esi;
		jmp begin_2_1;

	continue_1:
		cmp max_value, eax;
		je add_to_mods;
		sub ecx, 1;
		add ebx, 4;
		jmp begin_1_1;

	add_to_mods:
		mov [edi], edx;
		add size_mods, 1;
		add edi, 4;
		add ebx, 4;
		sub ecx, 1;
		jmp begin_1_1;

	end_:
	}
	int counter = 0;
	for (int i = 0; i < size_mods; i++) {
		std::cout << mods[i] << " ";
		++counter;
	}
	std::cout << counter << '\n';
	return counter;
}

int main() {

	/*int arr[10]{ INT_MIN + 1, -1,0,0,0,0,0,0,0,0};
	int arr[10]{ 10,20,30,40,50,60,70,80,90,100 };
	std::cout << SumOfTheElements(arr, 2);
	int a = 0;
	int b = 10;
	int* ptr_a = &a;
	int* ptr_b = &b;
	Subtraction(ptr_a, ptr_b);
	
	std::cout << *ptr_a << " " << *ptr_b;
	*/
	int arr[7]{1 ,2,3,4,5,6,7 };
	int arr1[7]{ -1,-2,-1,-2,3,3,4 };
	int arr2[7]{ 1,1,1,3,3,4,1 };
	NumberOfMods(arr) << '\n';
	NumberOfMods(arr1) << '\n';
	NumberOfMods(arr2) << '\n';

	return 0;
}