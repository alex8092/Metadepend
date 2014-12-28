#ifndef META_TRAITS_TYPE_CONVERT_HPP
# define META_TRAITS_TYPE_CONVERT_HPP

namespace meta
{
	namespace traits
	{
		namespace _private
		{
			namespace _type_convert
			{
				template <class U>
				struct _from
				{
					template <class V>
					struct _to
					{
						static constexpr inline V value(U data) {
							return (data);
						}
					};

					template <class V>
					struct _to<V*>
					{
						static constexpr inline V* value(U& data) {
							return (&data);
						}
					};

					template <class V>
					struct _to<V&>
					{
						static constexpr inline V& value(U& data) {
							return (data);
						}
					};

					template <class V>
					struct _to<V&&>
					{
						static constexpr inline V&& value(U&& data) {
							return (data);
						}
					};
				};

				template <class U>
				struct _from<U*>
				{
					template <class V>
					struct _to
					{
						static constexpr inline V value(U* data) {
							return (*data);
						}
					};

					template <class V>
					struct _to<V*>
					{
						static constexpr inline V* value(U* data) {
							return (data);
						}
					};

					template <class V>
					struct _to<V*&>
					{
						static constexpr inline V*& value(U*& data) {
							return (data);
						}
					};

					template <class V>
					struct _to<V&>
					{
						static constexpr inline V& value(U* data) {
							return (*data);
						}
					};

					template <class V>
					struct _to<V&&>
					{
						static constexpr inline V&& value(U* data) {
							return (std::move(*data));
						}
					};
				};

				template <class U>
				struct _from<U&>
				{
					template <class V>
					struct _to
					{
						static constexpr inline V value(U& data) {
							return (data);
						}
					};

					template <class V>
					struct _to<V*>
					{
						static constexpr inline V* value(U& data) {
							return (&data);
						}
					};

					template <class V>
					struct _to<V&>
					{
						static constexpr inline V& value(U& data) {
							return (data);
						}
					};

					template <class V>
					struct _to<V&&>
					{
						static constexpr inline V&& value(U& data) {
							return (std::move(data));
						}
					};
				};

				template <class U>
				struct _from<U&&>
				{};
			}
		}

		template <class U, class V>
		struct type_convert : public _private::_type_convert::_from<U>::template _to<V> {};
	}
}

#endif