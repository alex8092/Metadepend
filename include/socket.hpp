#ifndef META_SOCKET_HPP
# define META_SOCKET_HPP

# include "os.hpp"
# 	ifdef META_WINDOWS
#	include <winsock2.h>
# 	else
#	include <sys/socket.h>
#	include <unistd.h>
#	include <netdb.h>
#	include <arpa/inet.h>
#	include <sstream>
# 	endif
# include <system_error>

namespace meta
{
	namespace socket
	{
		namespace _priv
		{
			template <os::Type>
			struct _type
			{
				static constexpr int raw = SOCK_RAW;
				static constexpr int tcp = SOCK_STREAM;
				static constexpr int udp = SOCK_DGRAM;
			};
			#ifdef META_WINDOWS
			template <>
			struct _type<meta::os::Type::Windows>
			{
				static constexpr int raw = 0;
				static constexpr int tcp = 0;
				static constexpr int udp = 0;
			};
			#endif
		}

		enum class Type
		{
			RAW = _priv::_type<os::current>::raw,
			TCP = _priv::_type<os::current>::tcp,
			UDP = _priv::_type<os::current>::udp
		};

		namespace _priv
		{
			template <os::Type>
			struct _init
			{
				static inline void init() noexcept {}
				static inline void cleanup() noexcept {}
				static constexpr inline meta::types::socket create(Type sock_type) noexcept {
					return (::socket(AF_INET, (int)sock_type, 0));
				}
				static inline void	close(meta::types::socket& sock) noexcept {
					::close(sock);
					sock = -1;
				}
				static bool connect(meta::types::socket sock, Type sock_type, const std::string& host, const uint16_t port) noexcept {
					struct addrinfo hints = { 0, 0, 0, 0, 0, 0, 0, 0 };
					struct addrinfo *result, *current;
					hints.ai_family = AF_INET;
					hints.ai_socktype = (int)sock_type;
					hints.ai_flags = AI_PASSIVE;
					std::stringstream	port_str;
					port_str << port;
					int s = ::getaddrinfo(host.c_str(), port_str.str().c_str(), &hints, &result);
					if (s != 0)
						return (false);
					for (current = result; current != nullptr; current = current->ai_next)
					{
						s = ::connect(sock, current->ai_addr, current->ai_addrlen);
						if (s != -1)
							return (true);
					}
					return (false);
				}
				static inline bool bind(meta::types::socket sock, const uint16_t port) noexcept {
					struct sockaddr_in sin { AF_INET, htons(port), INADDR_ANY, { 0 }};
					return (::bind(sock, (struct sockaddr*)&sin, sizeof(sin)) != -1);
				}
				static inline bool listen(meta::types::socket sock, const uint32_t queue_max) noexcept {
					return (::listen(sock, queue_max) != -1);
				}
				static inline meta::types::socket accept(meta::types::socket sock) noexcept {
					static sockaddr_in sin = { 0, 0, 0, { 0 } };
					static socklen_t len = 0;
					return (::accept(sock, (struct sockaddr*)&sin, &len));
				}
				static int32_t read(meta::types::socket sock, char *buffer, uint32_t max) noexcept {
					ssize_t ret = ::read(sock, (void *)buffer, max);
					if (ret != -1)
						buffer[ret] = 0;
					return (ret);
				}
				static inline int32_t write(meta::types::socket sock, const char *buffer, uint32_t size) noexcept {
					return (::write(sock, buffer, size));
				}
			};
			#ifdef META_WINDOWS
			template<>
			struct _init
			{
				static void init() throws(const std::system_error&) {
					static bool is_init = false;
					if (is_init)
						return ;
					WSADATA		wsaData = {0};
					int 		iResult = 0;

					iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
					if (iResult != 0) {
						throw (std::system_error(iResult));
					}
					is_init = true;
				}
				static inline void cleanup() noexcept {
					WSACleanup();
				}
				static meta::types::socket create(Type sock_type) noexcept {
					#warning "meta::socket::create not implemented for your os at this time"
					return (0);
				}

				static void close(meta::types::socket& sock) noexcept {
					#warning "meta::socket::close not implemented for your os at this time"
					return (0);
				}

				static bool connect(meta::types::socket sock, const std::string& ip, const uint16_t port) noexcept {
					#warning "meta::socket::connect not implemented for your os at this time"
					return (false);
				}

				static bool bind(meta::types::socket sock, const uint16_t port) noexcept {
					#warning "meta::socket::bind not implemented for your os at this time"
					return (false);
				}
				static inline bool listen(meta::types::socket sock, const uint32_t queue_max) noexcept {
					#warning "meta::socket::listen not implemented for your os at this time"
					return (false);
				}
				static inline meta::types::socket accept(meta::types::socket sock) noexcept {
					#warning "meta::socket::accept not implemented for your os at this time"
					return (false);
				}
				static int32_t read(meta::types::socket sock, char *buffer, uint32_t max) noexcept {
					#warning "meta::socket::read not implemented for your os at this time"
					return (0);
				}
				static inline int32_t write(meta::types::socket sock, const char *buffer, uint32_t size) noexcept {
					#warning "meta::socket::read not implemented for your os at this time"
					return (0);
				}
			};
			#endif
		}

		inline void init() {
			_priv::_init<os::current>::init();
		}

		inline void cleanup() {
			_priv::_init<os::current>::cleanup();
		}

		constexpr inline meta::types::socket create(Type sock_type) noexcept {
			return (_priv::_init<os::current>::create(sock_type));
		}

		inline bool	connect(meta::types::socket sock, Type sock_type, const std::string& host, const uint16_t port = 80) noexcept {
			return (_priv::_init<os::current>::connect(sock, sock_type, host, port));
		}

		inline bool bind(meta::types::socket sock, const uint16_t port) noexcept {
			return (_priv::_init<os::current>::bind(sock, port));
		}

		inline bool listen(meta::types::socket sock, const uint32_t queue_max) noexcept {
			return (_priv::_init<os::current>::listen(sock, queue_max));
		}

		inline meta::types::socket accept(meta::types::socket sock) noexcept {
			return (_priv::_init<os::current>::accept(sock));
		}

		inline int32_t read(meta::types::socket sock, char *buffer, uint32_t max) noexcept {
			return (_priv::_init<os::current>::read(sock, buffer, max));
		}

		inline int32_t	write(meta::types::socket sock, const char *buffer, uint32_t size) noexcept {
			return (_priv::_init<os::current>::write(sock, buffer, size));
		}

		inline bool is_valid(meta::types::socket sock) noexcept {
			return (sock != meta::types::invalid_socket);
		}

		inline void close(meta::types::socket& sock) noexcept {
			_priv::_init<os::current>::close(sock);
		}
	}
}

#endif