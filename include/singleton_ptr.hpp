#ifndef GSS_META_SINGLETON_PTR_HPP
# define GSS_META_SINGLETON_PTR_HPP

namespace meta
{
	template <class U>
	class singleton_ptr
	{
	public:
		inline 			singleton_ptr() noexcept {}
		inline const U*	operator->() const {
			return (&U::_singleton);
		}
		inline U*		operator->() {
			return (&U::_singleton);
		}
		inline const U& operator*() const {
			return (U::_singleton);
		}
		inline U&		operator*() {
			return (U::_singleton);
		}
	};
}

#endif