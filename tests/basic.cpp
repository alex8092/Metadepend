#include <iostream>
#include "meta.hpp"

using namespace std;

int	main(void)
{
	meta::socket::init();
	meta::types::socket sock = meta::socket::create(meta::socket::Type::TCP);

	if (!meta::socket::bind(sock, 1555))
		return (-1);
	if (!meta::socket::listen(sock, 1000))
		return (-2);
	meta::types::socket client;
	while (meta::socket::is_valid((client = meta::socket::accept(sock))))
	{
		char	buffer[1025];
		meta::socket::read(client, buffer, 1024);
		cout << "read : " << buffer << endl;
		meta::socket::close(client);
	}
	meta::socket::close(sock);
	meta::socket::cleanup();
	return (0);
}