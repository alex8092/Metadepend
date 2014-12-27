Metadepend
==========

Meta programming

## 1. Signals

You can use signals by using meta::signal<>, it's a template class who allow other objects/functions to connect with him, and receive when a signal is emit.

### 1.1. Template parameters

declaration of meta::signal is like this "template <typename ... Params> class signal", template variadic are use to know what type of parameter send by the signal.

### 1.2. Emit

to send a signal, use the function emit of this signal, with as parameters the same type and the same numbers than the signal. like :

```c++
meta::signal<int, const std::string&> ft_sig;
ft_sig.emit(60, "hello");
ft_sig.emit(10, "world");
```

### 1.3. Connection

The first way to connect a signal, it's by a function who has no linkage with an object, for example

```c++
# include <iostream>
# include "meta.hpp"

void  ft_handler(int c)
{
  std::cout << "sig receive : " << c << std::endl;
}

int main(void)
{
  meta::signal<int> ft_sig;
  ft_sig.connect(ft_handler);
  ft_sig.emit(60);
  return (0);
}
```

The second way to connect a signal, is by a member function of an object, for example :

```c++
# include <iostream>
# include "meta.hpp"

struct test
{
  void  ft_member(int c, const std::string& s) {
    std::cout << "receive of string [" << s << "] with value : " << c << std::endl;
  }
};

int main(void)
{
  meta::signal<int, const std::string&> ft_sig;
  test                                  ft_test;
  ft_sig.connect(&test::ft_member, ft_test);
  ft_sig.emit(100, "this is a test of connecting member function");
  return (0);
}
```

### 1.4. Disconnection

To disconnect a signal, use the function disconnect with in parameter the function (not the member function) or the object link to the signal, like :

```c++
# include <iostream>
# include "meta.hpp"

struct test
{
  void  ft_member(int c, const std::string& s) {
    std::cout << "receive of string [" << s << "] with value : " << c << std::endl;
  }
};

void  ft_function(int c, const std::string& s)
{
  std::cout << "receive (without object) of string [" << s << "] with value : " << c << std::endl;
}

int main(void)
{
  meta::signal<int, const std::string&> ft_sig;
  test                                  ft_test;
  ft_sig.connect(&test::ft_member, &ft_test);
  ft_sig.connect(ft_function);
  ft_sig.emit(100, "this is a test of connecting member function");
  ft_sig.disconnect(&ft_test);
  ft_sig.emit(0, "Only ft_function will receive this signal");
  ft_sig.disconnect(ft_function);
  return (0);
}
```

### 1.5. Rule of emit

emit is a public function, all people can send the signal in accordance of visibility of the meta::signal object. By this way, the signal can react as an input or output, like "addObject" or "onObjectAdded".

## 2. Singleton

The singleton class provide an access to singleton advantage of a class with the less operations as possible, like :
```c++
#include "meta.hpp"

class test : public meta::singleton<test>
{
  private:
    test() {
    }
    friend class meta::singleton<test>;
  public:
    auto  print() {
      static int i = 0;
      std::cout << i++ << std::endl;
      return (test::instance());
    }
}

int main(void)
{
  test::instance()->print()->print()->print();
  return (0);
}
