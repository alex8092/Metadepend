#ifndef META_TRAITS_TYPE_INFOS_HPP
# define META_TRAITS_TYPE_INFOS_HPP

# include <type_traits>

namespace meta
{
	namespace traits
	{
		namespace _private
		{
			namespace _type_infos
			{
				template <class U, bool isptr, bool islref, bool isrref, bool isfundamental>
				struct type_infos
				{
					typedef U				base_type;
					typedef U*				ptr_type;
					typedef U*&				ptr_ref_type;
					typedef U&				ref_type;
					typedef U&&				rref_type;
					typedef const U			const_base_type;
					typedef const U*		const_ptr_type;
					typedef const U*&		const_ptr_ref_type;
					typedef const U&		const_ref_type;
					static constexpr bool	is_pointer = isptr;
					static constexpr bool	is_lvalue_reference = islref;
					static constexpr bool	is_rvalue_reference = isrref;
					static constexpr bool	is_reference = is_lvalue_reference || is_rvalue_reference;
					static constexpr bool	is_fundamental = isfundamental;
				};
			}
		}
		template <class U>
		struct type_infos : public _private::_type_infos::type_infos<
			typename std::remove_pointer<typename std::remove_reference<typename std::remove_const<U>::type>::type>::type,
			std::is_pointer<U>::value,
			std::is_lvalue_reference<U>::value,
			std::is_rvalue_reference<U>::value,
			std::is_fundamental<U>::value
		>
		{
			typedef typename std::remove_const<U>::type	type;
			typedef typename std::add_const<U>::type 	const_type;
		};
	}
}

#endif