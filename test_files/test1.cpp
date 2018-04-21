#include <stdint.h>
#include <iostream>

int main(void)
{
	int8_t a = 127;
	std::cout << static_cast<int>(a) << std::endl;

	float c = 127.32;
	std::cout << c << std::endl;

	double b = 85.36;
	std::cout << std::to_string(b) << std::endl;

	std::string const &tr = "45";
	int nb = std::atoi(tr.c_str());
	std::cout << nb << std::endl;

	int i = 8;
	float j = 4.5;
	std::cout << i - j << std::endl;
	return (0);
}
