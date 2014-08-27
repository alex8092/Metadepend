#ifndef META_SOCKET_HPP
# define META_SOCKET_HPP

# include "os.hpp"
# include <system_error>

namespace meta
{
	namespace socket
	{
		namespace _priv
		{
			template <os::Type>
			struct _init
			{
				static inline void init() noexcept {}
				static inline void cleanup() noexcept {}
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
			};
			#endif
		}

		inline void init() {
			_priv::_init<os::current>::init();
		}

		inline void cleanup() {
			_priv::_init<os::current>::cleanup();
		}
	}
}

#endif