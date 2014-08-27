#include <iostream>
#include "meta.hpp"

using namespace std;

int	main(void)
{
	meta::types::socket sock(0);

	meta::socket::init();
	cout << sock << endl;
	meta::socket::cleanup();
	return (0);
}