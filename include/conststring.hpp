#ifndef META_CONSTSTRING_HPP
# define META_CONSTSTRING_HPP

# include <stdexcept>

namespace meta
{
	class conststring
	{
	private:
		const char *_str;
		size_t		_size;

	public:
		template <size_t N>
		constexpr conststring(const char (&a)[N]) noexcept : _str(a), _size(N - 1) {}

		constexpr char operator[](size_t n) const {
			return ((n < _size) ? _str[n] : throw std::out_of_range(""));
		}

		constexpr size_t size() const noexcept {
			return (_size);
		}
	};
}

#endif