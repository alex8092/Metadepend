#include <iostream>
#include "meta.hpp"
#include "property.hpp"

using namespace std;

class ttt
{
private:
	int	i = 0;

public:
	ttt() {
		std::cout << "normal constructor" << std::endl;
	}
	ttt(const ttt& t)
	{
		std::cout << "copy constructor" << std::endl;
	}
	ttt(ttt&& t) {
		std::cout << "move constructor" << std::endl;
	}

	ttt& operator=(const ttt& t) {
		std::cout << "copy assignation" << std::endl;
	}

	ttt& operator=(ttt&& t) {
		std::cout << "move assignation" << std::endl;
	}

	~ttt() {
		std::cout << "normal destructor" << std::endl;
	}

	void	print() {
		std::cout << i++ << std::endl;
	}
};

int	main(void)
{
	
	return (0);
}