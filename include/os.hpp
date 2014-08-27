#ifndef META_OS_HPP
# define META_OS_HPP

namespace meta
{
	namespace os
	{
		enum class Type { Windows, Unix, Linux, MacOSX, FreeBSD };

		#if defined(_WIN32) || defined (_WIN64) || defined(WIN32) || defined(WIN64)
		# define META_WINDOWS
		Type constexpr current = Type::Windows;
		constexpr const char *  current_str = "Windows";
		# elif defined(__linux__)
		# define META_LINUX
		Type constexpr current = Type::Linux;
		constexpr const char * current_str = "Linux";
		# elif defined(__APPLE__) || defined(__MACH__)
		# define META_MACOSX
		Type constexpr current = Type::MacOSX;
		constexpr const char * current_str = "MacOSX";
		# elif defined(__FreeBSD__)
		# define META_FREEBSD
		Type constexpr current = Type::FreeBSD;
		constexpr const char * current_str = "FreeBSD";
		# elif defined(unix) || defined(__unix) || defined(__unix__)
		# define META_UNIX
		Type constexpr current = Type::Unix;
		constexpr const char * current_str = "Unix";
		# else
		# warning "this Operating system is not recognize"
		#endif
	}
}

#endif