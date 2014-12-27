#ifndef GSS_META_SINGLETON_HPP
# define GSS_META_SINGLETON_HPP

namespace meta
{
	template <class U>
	class singleton
	{
	private:
		static U	_singleton;

		singleton(const singleton<U>&) = delete;
		singleton(singleton<U>&&) = delete;
		singleton& operator=(const singleton<U>&) = delete;
		singleton& operator=(singleton<U>&&) = delete;

	protected:
		inline singleton() {};

	public:
		virtual ~singleton() {};
		static U *instance() {
			return (&singleton::_singleton);
		}
	};

	template <class U>
	U	singleton<U>::_singleton;
}

#endif