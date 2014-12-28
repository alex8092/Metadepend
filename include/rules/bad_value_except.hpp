#ifndef META_RULES_BAD_VALUE_EXCEPT_HPP
# define META_RULES_BAD_VALUE_EXCEPT_HPP

# include <exception>

namespace meta
{
	namespace rules
	{
		struct bad_value : public std::exception {
			const char* what() const noexcept {return "Rule: Bad Value\n";}
		};
	}
}

#endif