#ifndef GSS_META_PROPERTY_HPP
# define GSS_META_PROPERTY_HPP

# include "signal.hpp"
# include "traits/type_infos.hpp"
# include "traits/type_convert.hpp"
# include "traits/type_access.hpp"

namespace meta
{
	namespace _private
	{
		namespace _property
		{
			template <class U,
				bool pointer = traits::type_infos<U>::is_pointer,
				bool lvalue_reference = traits::type_infos<U>::is_lvalue_reference,
				bool rvalue_reference = traits::type_infos<U>::is_rvalue_reference,
				bool fundamental = traits::type_infos<U>::is_fundamental
				>
			struct _types
			{};

			template <class U>
			struct _types<U, false, false, false, true>
			{
				typedef typename traits::type_infos<U>::base_type		storage_type;
				typedef typename traits::type_infos<U>::ref_type		lvalue_type;
				typedef typename traits::type_infos<U>::base_type		get_type;
				typedef typename traits::type_infos<U>::base_type		set_type;
				static constexpr bool									has_alternate_set = false;
				typedef typename traits::type_infos<U>::rref_type		alternate_set_type;
				static constexpr bool									is_pointer = false;
			};

			template <class U>
			struct _types<U, false, false, false, false>
			{
				typedef typename traits::type_infos<U>::base_type		storage_type;
				typedef typename traits::type_infos<U>::ref_type		lvalue_type;
				typedef typename traits::type_infos<U>::ref_type		get_type;
				typedef typename traits::type_infos<U>::const_ref_type	set_type;
				static constexpr bool									has_alternate_set = true;
				typedef typename traits::type_infos<U>::rref_type		alternate_set_type;
				static constexpr bool									is_pointer = false;
			};

			template <class U>
			struct _types<U, true, false, false, false>
			{
				typedef typename traits::type_infos<U>::ptr_type		storage_type;
				typedef typename traits::type_infos<U>::ptr_ref_type	lvalue_type;
				typedef typename traits::type_infos<U>::ptr_type		get_type;
				typedef typename traits::type_infos<U>::ptr_type		set_type;
				static constexpr bool									has_alternate_set = false;
				static constexpr bool									is_pointer = true;
			};

			template <class U>
			struct _types<U, false, true, false, false>
			{
				typedef typename traits::type_infos<U>::ptr_type		storage_type;
				typedef typename traits::type_infos<U>::ref_type		lvalue_type;
				typedef typename traits::type_infos<U>::ref_type		get_type;
				typedef typename traits::type_infos<U>::ref_type		set_type;
				static constexpr bool									has_alternate_set = false;
				static constexpr bool									is_pointer = false;
			};

			template <class U, bool is_pointer = _types<U>::is_pointer>
			struct _pointer_helper
			{
			public:
				
			};

			template <class U>
			struct _pointer_helper<U, false>
			{};
		}
	}

	template <class U>
	class Property
	{
		typedef typename _private::_property::_types<U>::storage_type		storage_type;
		typedef typename _private::_property::_types<U>::lvalue_type		lvalue_type;
		typedef typename _private::_property::_types<U>::get_type			get_type;
		typedef typename std::add_const<get_type>::type						const_get_type;
		typedef typename _private::_property::_types<U>::set_type			set_type;
		typedef Property<U>													base;

		typedef typename traits::type_convert<storage_type, lvalue_type> 		 	__lvalue;
		typedef typename traits::type_convert<storage_type, get_type>				__get;
		typedef typename traits::type_convert<set_type, storage_type>				__storage;

	protected:
		storage_type	_value;

	public:
		inline explicit Property() = default;
		inline 			Property(const base& prop) : _value(prop._value) {}
		inline 			Property(base&& prop) : _value(std::move(prop._value)) {}

		template <class T>
		inline 			Property(T value) : _value(value) {};

		template <class T>
		inline base&	operator=(T value)
		{
			__lvalue::value(this->_value) = value;
		}

		inline base&	operator++()
		{
			++__lvalue::value(this->_value);
			return (*this);
		}

		inline base&&	operator++(int)
		{
			base	cpy(static_cast<const base&>(*this));
			this->operator++();
			return (std::move(cpy));
		}

		inline base&	operator--()
		{
			--__lvalue::value(this->_value);
			return (*this);
		}

		inline base&&	operator--(int)
		{
			base	cpy(static_cast<const base&>(*this));
			this->operator--();
			return (*this);
		}

		template <class T>
		inline auto		operator[](T value) const
		{
			return (__get::value(this->_value)[value]);
		}

		template <class T>
		inline auto		operator[](T value)
		{
			return (__get::value(this->_value)[value]);
		}

		template <class T>
		inline base&	operator+=(T value)
		{
			__lvalue::value(this->_value) += value;
			return (*this);
		}

		template <class T>
		inline base&	operator-=(T value)
		{
			__lvalue::value(this->_value) -= value;
			return (*this);
		}

		template <class T>
		inline base&	operator*=(T value)
		{
			__lvalue::value(this->_value) *= value;
			return (*this);
		}

		template <class T>
		inline base&	operator/=(T value)
		{
			__lvalue::value(this->_value) /= value;
			return (*this);
		}

		template <class T>
		inline auto	operator+(T value)
		{
			return (std::move(Property<decltype(__get::value(this->_value) + value)>(__get::value(this->_value) + value)));
		}

		template <class T>
		inline auto operator-(T value)
		{
			return (std::move(Property<decltype(__get::value(this->_value) - value)>(__get::value(this->_value) - value)));
		}

		template <class T>
		inline auto operator*(T value)
		{
			return (std::move(Property<decltype(__get::value(this->_value) * value)>(__get::value(this->_value) * value)));
		}

		template <class T>
		inline auto operator/(T value)
		{
			return (std::move(Property<decltype(__get::value(this->_value) / value)>(__get::value(this->_value) / value)));
		}

		inline auto operator->() {
			return (&(*__lvalue::value(this->_value)));
		}
		inline auto operator->() const {
			return (&(*__lvalue::value(this->_value)));
		}
		inline auto operator*() {
			return (*__lvalue::value(this->_value));
		}
		inline auto operator*() const {
			return (*__lvalue::value(this->_value));
		}

		inline operator get_type ()
		{
			return (__get::value(this->_value));
		}
	};

	template <class U, class Validator>
	struct RuledProperty : public Property<U>
	{
		template <class T>
		RuledProperty(T data) : Property<U>(data) {
			Validator::validate(data);
		}
	};
}

#endif