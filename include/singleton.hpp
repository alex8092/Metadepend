#ifndef GSS_META_SINGLETON_HPP
# define GSS_META_SINGLETON_HPP

# include "singleton_ptr.hpp"

namespace meta
{
	template <class U>
	class singleton
	{
	private:
		static U	_singleton;

		friend class singleton_ptr<U>;
		singleton(const singleton<U>&) = delete;
		singleton(singleton<U>&&) = delete;
		singleton& operator=(const singleton<U>&) = delete;
		singleton& operator=(singleton<U>&&) = delete;

	protected:
		typedef singleton_ptr<U>	itself;
		inline singleton() {};

	public:
		virtual ~singleton() {};
		static singleton_ptr<U>	instance() {
			return (singleton_ptr<U>());
		}
	};

	template <class U>
	U	singleton<U>::_singleton;
}

#endif