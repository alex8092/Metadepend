#include <iostream>
#include "meta.hpp"

using namespace std;

class test : public meta::singleton<test>
{
private:
	test() {

	}
	friend class meta::singleton<test>;
public:
	void print() {
		static int i = 0;
		std::cout << i++ << std::endl;
	}
};
int	main(void)
{
	test::instance()->print();
	test::instance()->print();
	return (0);
}