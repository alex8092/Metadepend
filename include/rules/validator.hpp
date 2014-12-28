#ifndef META_RULES_VALIDATOR_HPP
# define META_RULES_VALIDATOR_HPP

# include "rules/bad_value_except.hpp"

namespace meta
{
	namespace rules
	{
		struct nullptr_validator
		{
			template <class T>
			static inline void	validate(T* data) {
				if (data == nullptr)
					throw rules::bad_value();
			}
		};
	}
}

#endif