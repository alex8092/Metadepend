#ifndef GSS_META_SIGNAL_HPP
# define GSS_META_SIGNAL_HPP

# include <vector>
# include <functional>
# include <map>

using namespace std::placeholders;


namespace meta
{
	template <int N>
	struct _my_placeholder {};
}

namespace std
{
    template<int N>
    struct is_placeholder<meta::_my_placeholder<N>> : public integral_constant<int, N> {};
}

namespace meta
{
	namespace _priv
	{
		template <class U, class V, class W, int Current>
		struct _bind
		{
			template <typename ...Args>
			static inline void Do(U *vect, V func, W *object, Args&&... params) noexcept {
				meta::_priv::_bind<U, V, W, Current - 1>::Do(vect, func, object, _my_placeholder<Current>{}, params...);
			}
		};

		template <class U, class V, class W>
		struct _bind<U, V, W, 0>
		{
			template <typename ...Args>
			static inline void Do(U *vect, V func, W *object, Args&&... params) noexcept {
				(*vect)[(void *)object] = std::bind(func, object, params...);
			}
		};
	}

	template <typename ... Params>
	class signal
	{
	private:
		signal(signal<Params...>&) = delete;
		signal(signal<Params...>&&) = delete;
		signal& operator=(signal<Params...>&) = delete;
		signal&& operator=(signal<Params...>&&) = delete;
		int 			_max_connections;
		int 			_current_connections = 0;
	protected:
		std::map<void *, std::function<void(Params...)>>							_binds;
		std::vector<void (*)(Params...)>											_binds_no_obj;
		typedef typename std::map<void *, std::function<void(Params...)>>::iterator	iterator;
		virtual void																onRemoveIterator(iterator) noexcept {};

	public:
		signal(int max_connections = 0) : _max_connections(max_connections) {};
		virtual ~signal() = default;

		template <class U, class V>
		bool	connect(U func, V *object)
		{
			if (this->_max_connections && this->_current_connections >= this->_max_connections)
				return (false);
			meta::_priv::_bind<std::map<void *, std::function<void(Params...)>>, U, V, sizeof...(Params)>::Do(&this->_binds, func, object);
			++this->_current_connections;
			return (true);
		}

		bool	connect(void (*func)(Params...))
		{
			if (this->_max_connections && this->_current_connections >= this->_max_connections)
				return (false);
			this->_binds_no_obj.push_back(func);
			++this->_current_connections;
			return (true);
		}

		template <class V>
		bool 	disconnect(V *object) noexcept {
			auto it = this->_binds.find((void *)object);
			if (it == this->_binds.end())
				return (false);
			onRemoveIterator(it);
			this->_binds.erase(it);
			--this->_current_connections;
			return (true);
		}

		bool	disconnect(void (*func)(Params...))
		{
			auto it = this->_binds_no_obj.begin();
			for (;it != this->_binds_no_obj.end(); ++it)
			{
				if (*it == func)
					break ;
			}
			if (it != this->_binds_no_obj.end())
				this->_binds_no_obj.erase(it);
			else return (false);
			--this->_current_connections;
			return (true);
		}

		virtual void emit(Params... parameters) noexcept {
			for (auto it : this->_binds) it.second(parameters...);
			for (auto it2 : this->_binds_no_obj) it2(parameters...);
		}
	};
}

#endif