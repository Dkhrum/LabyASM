#include <iostream>
#include <cmath>

extern "C" double IntegrateCotan(int N);

int main() {
	int N = 10000;
	float result;

	__asm {
		MOV ebx, N;
		PUSH ebx;
		call IntegrateCotan;
		ADD esp, 4;
		mov result, eax;
	}
	std::cout << result << '\n';
	return 0;
}