#ifndef GSS_META_SINGLETON_PTR_HPP
# define GSS_META_SINGLETON_PTR_HPP

namespace meta
{
	template <class U>
	class singleton_ptr
	{
	private:
		U	*_ref = U::instance();
	public:
		inline 			singleton_ptr() noexcept {}
		inline const U*	operator->() const {
			return (this->_ref);
		}
		inline U*		operator->() {
			return (this->_ref);
		}
		inline const U& operator*() const {
			return (*this->_ref);
		}
		inline U&		operator*() {
			return (*this->_ref);
		}
	};
}

#endif