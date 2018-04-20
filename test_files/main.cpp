#include <stdint.h>
#include <iostream>

int main(void)
{
	int8_t a = 127;
	std::cout << static_cast<int>(a) << std::endl;

	float c = 127.32;
	std::cout << c << std::endl;
	return (0);
}
