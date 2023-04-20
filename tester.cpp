#include <iostream>
#include <cstdint>

void print(uint16_t num) {
	std::cout<< " x|  3|  2|  1|  0|st" << std::endl;
	for (int i  = 15; i >= 0; i--){
		std::cout << ((num >> i) & 1);
		if (i == 14 || i == 11 || i == 8 || i == 5 || i == 2)
			std::cout << "|";
	}
	std::cout << std::endl;
	
}

int main() {

	uint16_t test = 0;
	int state = 3;

	print(test);

	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	
	print(test);

	state = 1;

	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	test += (1 << (state * 3 + 2));
	print(test);
	
	//get num of states
	std::cout << (test >> (3 * 3 + 2) & 0x07) << std::endl;

	test = 159;
	std::cout << (test & 0x03) << std::endl;

	print(test);
	print(test ^= 0x03);
	return (0);
}
