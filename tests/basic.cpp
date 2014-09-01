#include <iostream>
#include "meta.hpp"

using namespace std;

int	main(void)
{
	meta::socket::init();
	meta::types::socket sock = meta::socket::create(meta::socket::Type::TCP);

	if (meta::socket::connect(sock, meta::socket::Type::TCP, "www.google.fr"))
		cout << "win" << endl;

	meta::socket::close(sock);
	meta::socket::cleanup();
	return (0);
}