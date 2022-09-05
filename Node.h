#ifndef NODE
#define NODE
namespace sviridenko
{
  template <typename T>
  struct Node
  {
    T item_;
    Node< T >* next_;
    Node< T >* prev_;
    explicit Node< T >(const T& item, Node< T >* next = nullptr, Node< T >* prev = nullptr) : item_(item), next_(next), prev_(prev)
    {}
  };
}
#endif
