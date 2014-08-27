#ifndef META_TYPES_HPP
# define META_TYPES_HPP

# include "os.hpp"

# ifdef META_WINDOWS
#  include <windows.h>
#  include <winsock2.h>
# endif

namespace meta
{
	namespace types
	{
		namespace _priv
		{
			template <os::Type type>
			struct socket
			{};
			template <>
			struct socket<os::Type::Unix> {
				typedef int 	type;
			};
			#ifdef META_WINDOWS
			template <>
			struct socket<os::Type::Windows> {
				typedef SOCKET 	type;
			};
			#endif
			template <>
			struct socket<os::Type::MacOSX> : public socket<os::Type::Unix> {};
			template <>
			struct socket<os::Type::FreeBSD> : public socket<os::Type::Unix> {};
			template <>
			struct socket<os::Type::Linux> : public socket<os::Type::Unix> {};
		}
		typedef _priv::socket<os::current>::type socket;
	}
}

#endif