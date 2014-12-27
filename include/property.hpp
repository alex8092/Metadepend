#ifndef GSS_META_PROPERTY_HPP
# define GSS_META_PROPERTY_HPP

# include "signal.hpp"
# include "traits/type_infos.hpp"
# include "traits/type_convert.hpp"

namespace meta
{
	namespace _private
	{
		template <class U, bool has_alternate>
		class PrivateProperty;

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
				typedef typename traits::type_infos<U>::ptr_type		get_type;
				typedef typename traits::type_infos<U>::ptr_type		set_type;
				static constexpr bool									has_alternate_set = false;
				static constexpr bool									is_pointer = true;
			};

			template <class U>
			struct _types<U, false, true, false, false>
			{
				typedef typename traits::type_infos<U>::ptr_type		storage_type;
				typedef typename traits::type_infos<U>::ref_type		get_type;
				typedef typename traits::type_infos<U>::ref_type		set_type;
				static constexpr bool									has_alternate_set = false;
				static constexpr bool									is_pointer = false;
			};

			template <class U, bool is_pointer = _types<U>::is_pointer>
			struct _pointer_helper
			{
			public:
				inline auto operator->() {
					return (static_cast<U*>(this)->get());
				}
				inline auto operator->() const {
					return (static_cast<U*>(this)->get());
				}
				inline auto operator*() {
					return (*static_cast<U*>(this)->get());
				}
				inline auto operator*() const {
					return (*static_cast<U*>(this)->get());
				}
			};

			template <class U>
			struct _pointer_helper<U, false>
			{};
		}
	}

	template <class U, bool has_alternate = _private::_property::_types<U>::has_alternate_set>
	class PrivateProperty : public _private::_property::_pointer_helper<PrivateProperty<U, has_alternate>>
	{
		typedef typename _private::_property::_types<U>::storage_type	storage_type;
		typedef typename std::add_const<storage_type>::type				const_storage_type;
		typedef typename _private::_property::_types<U>::get_type		get_type;
		typedef typename std::add_const<get_type>::type					const_get_type;
		typedef typename _private::_property::_types<U>::set_type		set_type;
		typedef PrivateProperty<U, has_alternate>						base;

	protected:
		storage_type	_value;

	public:
		inline explicit PrivateProperty() = default;
		inline 			PrivateProperty(const base& prop) : _value(prop._value) {}
		inline 			PrivateProperty(base&& prop) : _value(std::move(prop._value)) {}
		inline 			PrivateProperty(set_type value) : _value(traits::type_convert<set_type, storage_type>::value(value)) {};
		
		inline base&	operator=(set_type value)
		{
			this->_value = traits::type_convert<set_type, storage_type>::value(value);
			return (*this);
		}

		inline get_type				get() {
			return (traits::type_convert<storage_type, get_type>::value(this->_value));
		}

		inline const_get_type		get() const {
			return (traits::type_convert<const_storage_type, const_get_type>::value(this->_value));
		}

		inline PrivateProperty<U>&	set(set_type value) {
			this->_value = traits::type_convert<set_type, storage_type>::value(value);
			return (*this);
		}
	};

	template <class U>
	class PrivateProperty<U, true> : public PrivateProperty<U, false>
	{
		typedef typename _private::_property::_types<U>::set_type			set_type;
		typedef typename _private::_property::_types<U>::alternate_set_type	alternate_set_type;
		typedef PrivateProperty<U, true>									base;

	public:
		inline explicit PrivateProperty() = default;
		inline 			PrivateProperty(const PrivateProperty<U, true>& prop) = default;
		inline 			PrivateProperty(PrivateProperty<U, true>&& prop) = default;
		inline 			PrivateProperty(set_type value) : PrivateProperty<U, false>(value) {}

		inline base&	operator=(alternate_set_type value)
		{
			this->_value = std::move(value);
			return (*this);
		}

		inline base&	set(alternate_set_type value) {
			this->_value = std::move(value);
			return (*this);
		}
	};
}

#endif