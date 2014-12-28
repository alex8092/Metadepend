#ifndef META_RULES_VALIDATOR_HPP
# define META_RULES_VALIDATOR_HPP

# include "rules/bad_value_except.hpp"

# define META_RULES_ICHECKER_FUNCTION_BUILD(X) \
namespace meta \
{ \
	namespace rules \
	{ \
		template <bool checkStatic, class ReturnType, typename ... Parameters> \
		struct has_function_##X \
		{ \
			typedef std::true_type	yes;\
			typedef std::false_type	no;\
			template <typename C, ReturnType (C::*f)(Parameters...)> struct SFINAE{};\
			template <typename C, ReturnType (C::*f)(Parameters...) const> struct SFINAE<C,f>{};\
			template <typename C> static constexpr yes check(SFINAE<C,&C::X>*); \
			template <typename> static constexpr no check(...); \
			static constexpr yes check_static(ReturnType (*)(Parameters...)); \
			static constexpr no check_static(...); \
			template <class T, bool has = (!checkStatic && std::is_same<yes,decltype(check<T>(nullptr))>::value) || (checkStatic && std::is_same<yes,decltype(check_static(&T::X))>::value)>\
			static constexpr bool value() {\
				return (has); \
			} \
			struct storage_type \
			{ \
				std::function<ReturnType(Parameters...)> X; \
			}; \
			template <class T> \
			static inline std::function<ReturnType(Parameters...)> bind(T* data) { \
				return (meta::rules::_private::_bind<ReturnType (T::*)(Parameters...), T, sizeof...(Parameters)>::Do(&T::X, data)); \
			} \
			template <class T> \
			static inline void										init(T* data, storage_type *self) \
			{\
				self->X = bind<T>(data);\
			}\
		}; \
	} \
}

namespace meta
{
	namespace rules
	{
		namespace _private
		{
			template <class V, class W, int Current>
			struct _bind
			{
				template <typename ...Args>
				static inline auto Do(V func, W *object, Args&&... params) {
					return (_bind<V, W, Current - 1>::Do(func, object, _my_placeholder<Current>{}, params...));
				}
			};

			template <class V, class W>
			struct _bind<V, W, 0>
			{
				template <typename ...Args>
				static inline auto Do(V func, W *object, Args&&... params) {
					return (std::bind(func, object, params...));
				}
			};
		}

		struct nullptr_validator
		{
			template <class T>
			static inline void	validate(T* data) {
				if (data == nullptr)
					throw rules::bad_value();
			}
		};

		template <class ... InterfaceChecker>
		struct interface_validator
		{
			template <class V, class Check, class ... Next>
			struct _checker
			{
				static constexpr bool value = Check::template value<V>() && _checker<V, Next...>::value;
			};

			template <class V, class Check>
			struct _checker<V, Check>
			{
				static constexpr bool value = Check::template value<V>();
			};

			template <class T>
			static inline void validate(T data) {
				if (!_checker<T, InterfaceChecker...>::value)
					std::cout << "failed" << std::endl;
			}

			template <class T>
			static constexpr void static_validate() {
				static_assert(_checker<T, InterfaceChecker...>::value, "Interface check failed");
			}
		};
	}
}

#endif