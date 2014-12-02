#ifndef META_OS_HPP
# define META_OS_HPP

#if defined(_WIN32) || defined (_WIN64) || defined(WIN32) || defined(WIN64)
# define META_WINDOWS
# elif defined(__linux__)
# define META_LINUX
# elif defined(__APPLE__) || defined(__MACH__)
# define META_MACOSX
# elif defined(__FreeBSD__)
# define META_FREEBSD
# elif defined(unix) || defined(__unix) || defined(__unix__)
# define META_UNIX
# else
# warning "this Operating system is not recognize"
#endif

namespace meta
{
	enum class OsType { Windows, Unix, Linux, MacOSX, FreeBSD };

	class os
	{
	private:
		char			*_version = nullptr;
		static os		_singleton;

	public:
		#ifdef META_WINDOWS
		static constexpr const char * 	name 	= "Windows";
		static OsType constexpr 		type 	= OsType::Windows;
		# elif defined META_UNIX
		static constexpr const char * 	name 	= "Unix";
		static OsType constexpr 		type 	= OsType::Unix;
		# elif defined META_LINUX
		static constexpr const char * 	name 	= "Linux";
		static OsType constexpr 		type 	= OsType::Linux;
		# elif defined META_MACOSX
		static constexpr const char * 	name 	= "MacOSX";
		static OsType constexpr 		type 	= OsType::MacOSX;
		# elif defined META_FREEBSD
		static constexpr const char * 	name 	= "FreeBSD";
		static OsType constexpr 		type 	= OsType::FreeBSD;
		#endif

		const char *					version() const noexcept {
			return (this->_version);
		}

		static inline os*				singleton() noexcept {
			return (&os::_singleton);
		}
	};
}

#endif