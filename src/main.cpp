#include <iostream>
#include <algorithm>
#include "meta.hpp"
#include "property.hpp"
#include "rules/validator.hpp"
#include "interface.hpp"

using namespace std;


META_RULES_ICHECKER_FUNCTION_BUILD(print);
META_RULES_ICHECKER_FUNCTION_BUILD(test);

typedef meta::interface<
	meta::rules::has_function_print<false, void, int>,
	meta::rules::has_function_test<false, void>
	>	itest;

struct tata
{
	template <class T>
	void	print(T c)
	{
		std::cout << "print tata: " << c << std::endl;
	}

	void	haha() {}
	void	test() {
		std::cout << "test tata" << std::endl;
	}
};

struct toto
{
	void	print(int c)
	{
		std::cout << "print toto: " << c << std::endl;
	}
	void	test()
	{
		std::cout << "test toto" << std::endl;
	}
};

int	main(void)
{
	std::vector<itest>	vec;
	tata	*tata_obj = new tata();
	vec.push_back(tata_obj);
	vec.push_back(new toto());
	for (auto it : vec) {
		it->print(0);
		it->test();
	}
	vec.erase(std::remove(vec.begin(), vec.end(), tata_obj), vec.end());
	for (auto it : vec) {
		it->print(1);
		it->test();
	}
	return (0);
}