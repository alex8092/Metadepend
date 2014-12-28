#ifndef META_INTERFACE_VECTOR_HPP
# define META_INTERFACE_VECTOR_HPP

# include "rules/validator.hpp"
# include "signal.hpp"
# include <vector>
# include <map>

namespace meta
{
	namespace _private
	{
		namespace _interface
		{
			template <class Check, class ... InterfaceChecker>
			struct interface_datas : public interface_datas<InterfaceChecker...>, public Check::storage_type
			{
			};

			template <class Check>
			struct interface_datas<Check> : public Check::storage_type
			{
				void		*object_pointer;
			};

			template <class T, class Check, class ...InterfaceChecker>
			struct interface_init
			{
				template <class M>
				static inline void init(T *data, M *idatas) {
					Check::init(data, idatas);
					interface_init<T, InterfaceChecker...>::template init<M>(data, idatas);
				}
			};
			template <class T, class Check>
			struct interface_init<T, Check>
			{
				template <class M>
				static inline void init(T *data, M *idatas) {
					Check::init(data, idatas);
					idatas->object_pointer = (void *)data;
				}
			};
		}
		
	}

	template <class ... InterfaceChecker>
	class interface
	{
	private:
		_private::_interface::interface_datas<InterfaceChecker...>		_datas;
		interface() = delete;

	public:
		template <class T>
		inline interface(T* data) {
			meta::rules::interface_validator<InterfaceChecker...>::template static_validate<T>();
			_private::_interface::interface_init<T, InterfaceChecker...>::init(data, &this->_datas);
		}
		virtual ~interface() = default;
		inline bool	operator==(const interface& i) const {
			return (this->_datas.object_pointer == i._datas.object_pointer);
		}
		template <class T>
		inline bool	operator==(T *data) const {
			return (this->_datas.object_pointer == data);
		}
		inline bool operator!=(const interface& i) const {
			return (this->_datas.object_pointer != i._datas.object_pointer);
		}
		template <class T>
		inline bool	operator!=(T *data) const {
			return (this->_datas.object_pointer != data);
		}
		inline auto operator->() {
			return (&this->_datas);
		}
		inline auto operator->() const {
			return (&this->_datas);
		}
		inline auto operator*() {
			return (this->_datas);
		}
		inline auto operator*() const {
			return (this->_datas);
		}
	};
}

#endif