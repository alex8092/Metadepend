#include <iostream>
#include "meta.hpp"

using namespace std;

int	main(void)
{
	std::cout << meta::os::singleton()->version() << std::endl;
	return (0);
}