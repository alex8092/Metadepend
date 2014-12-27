#include <iostream>
#include "meta.hpp"

using namespace std;


void	when_int(int c)
{
	cout << "value: " << c << endl;
}

int	main(void)
{
	meta::signal<int>	sint;

	sint.connect(when_int);

	sint.emit(999);

	return (0);
}