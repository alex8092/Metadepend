#include <iostream>
#include "meta.hpp"
#include "property.hpp"
#include "traits/pointer_level.hpp"
#include "rules/validator.hpp"

using namespace std;

void	test(meta::RuledProperty<int*, meta::rules::nullptr_validator> a)
{
	std::cout << *a + 4 << std::endl;
}

int	main(void)
{
	int	a = 60;
	try
	{
		test(&a);
		test(&a);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return (0);
}