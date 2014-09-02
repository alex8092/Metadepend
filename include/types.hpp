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
			template <os::Type _type>
			struct socket
			{
				typedef int 			type;
				static constexpr int	novalid = -1;
			};
			#ifdef META_WINDOWS
			template <>
			struct socket<os::Type::Windows>
			{
				typedef SOCKET 			type;
				static constexpr SOCKET	novalid = INVALID_SOCKET;
			};
			#endif
		}
		typedef _priv::socket<os::current>::type socket;
		constexpr socket invalid_socket = _priv::socket<os::current>::novalid;
	}
}

#endif