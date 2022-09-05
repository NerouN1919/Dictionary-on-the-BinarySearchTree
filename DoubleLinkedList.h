#ifndef BIDIRECTIONALLIT_LIST
#define BIDIRECTIONALLIT_LIST
#include "Node.h"
#include <cassert>
#include <stdexcept>
namespace sviridenko
{
  template <typename T>
  class BidirectionalList
  {
  private:
    Node< T >* head_;
    Node< T >* tail_;
    void swap(BidirectionalList& other) noexcept;
    void insertTail(Node< T >* x);
    void insertHead(Node< T >* x);
    void deleteNode(Node< T >* x);
    Node< T >* searchNode(T item);
  public:
    struct IteratorBL
    {
      IteratorBL();
      IteratorBL(const IteratorBL& other);
      ~IteratorBL() = default;
      T& operator*();
      const T& operator*() const;
      IteratorBL& operator=(const IteratorBL& other);
      bool operator!=(const IteratorBL& lhs) const;
      bool operator==(const IteratorBL& lhs) const;
      IteratorBL& operator++();
      IteratorBL operator++(int);
      T* operator->();
      const T* operator->() const;
    private:
      Node< T >* current_;
      Node< T >* next_;
      Node< T >* prev_;
      IteratorBL(Node< T >* node);
      friend BidirectionalList;
    };
    struct ConstIteratorBL
    {
      ConstIteratorBL();
      ConstIteratorBL(const ConstIteratorBL& other);
      ~ConstIteratorBL() = default;
      const T& operator*() const;
      ConstIteratorBL& operator=(const ConstIteratorBL& other);
      bool operator!=(const ConstIteratorBL& lhs) const;
      bool operator==(const ConstIteratorBL& lhs) const;
      ConstIteratorBL& operator++();
      ConstIteratorBL operator++(int);
      const T* operator->() const;
    private:
      Node< T >* current_;
      Node< T >* next_;
      Node< T >* prev_;
      ConstIteratorBL(Node< T >* node);
      friend BidirectionalList;
    };
    ConstIteratorBL cbeforeBegin() const;
    ConstIteratorBL cbegin() const;
    ConstIteratorBL cend() const;
    IteratorBL beforeBegin();
    IteratorBL begin();
    IteratorBL end();
    BidirectionalList();
    BidirectionalList(const BidirectionalList< T >&);
    BidirectionalList(BidirectionalList< T >&&) noexcept;
    ~BidirectionalList();
    BidirectionalList& operator=(const BidirectionalList& right);
    BidirectionalList& operator=(BidirectionalList&& right) noexcept;
    T headItem() const;
    T& headItem();
    T tailItem() const;
    T& tailItem();
    void insertHead(T item);
    void insertTail(T item);
    bool deleteHead();
    bool deleteTail();
    bool deleteItem(const T item);
    bool searchItem(T item);
    bool replaceItem(T itemOld, T itemNew);
    bool isEmpty();
    bool boolSearchItem(T item);
    int counter_;
  };
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL sviridenko::BidirectionalList< T >::cbeforeBegin() const
{
  ConstIteratorBL it;
  it.current_ = nullptr;
  it.next_ = head_;
  return it;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL sviridenko::BidirectionalList< T >::cbegin() const
{
  return ConstIteratorBL(head_);
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL sviridenko::BidirectionalList< T >::cend() const
{
  return ConstIteratorBL(nullptr);
}

template< typename T >
sviridenko::BidirectionalList< T >::ConstIteratorBL::ConstIteratorBL() :
  current_(nullptr),
  next_(nullptr),
  prev_(nullptr)
{}

template< typename T >
sviridenko::BidirectionalList< T >::ConstIteratorBL::ConstIteratorBL(const ConstIteratorBL& other) :
  current_(other.current_),
  next_(other.next_),
  prev_(other.prev_)
{}

template< typename T >
sviridenko::BidirectionalList< T >::ConstIteratorBL::ConstIteratorBL(Node< T >* node)
{
  if (node == nullptr)
  {
    current_ = nullptr;
    next_ = nullptr;
    prev_ = nullptr;
  }
  else
  {
    current_ = node;
    next_ = node->next_;
    prev_ = node->prev_;
  }
}

template< typename T >
const T& sviridenko::BidirectionalList< T >::ConstIteratorBL::operator*() const
{
  return current_->data;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL&
sviridenko::BidirectionalList< T >::ConstIteratorBL::operator=(const ConstIteratorBL& other)
{
  ConstIteratorBL newIt(other);
  std::swap(current_, newIt.current_);
  std::swap(next_, newIt.next_);
  std::swap(prev_, newIt.prev_);
  return *this;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::ConstIteratorBL::operator!=(const ConstIteratorBL& lhs) const
{
  return !(*this == lhs);
}

template< typename T >
bool sviridenko::BidirectionalList< T >::ConstIteratorBL::operator==(const ConstIteratorBL& lhs) const
{
  return current_ == lhs.current_;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL& sviridenko::BidirectionalList< T >::ConstIteratorBL::operator++()
{
  current_ = next_;
  if (next_ != nullptr)
  {
    next_ = next_->next_;
  }
  return *this;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::ConstIteratorBL sviridenko::BidirectionalList< T >::ConstIteratorBL::operator++(int)
{
  ConstIteratorBL result(*this);
  ++(*this);
  return result;
}

template< typename T >
T* sviridenko::BidirectionalList< T >::IteratorBL::operator->()
{
  return std::addressof(current_->data);
}

template< typename T >
const T* sviridenko::BidirectionalList< T >::ConstIteratorBL::operator->() const
{
  return std::addressof(current_->data);
}

template< typename T >
bool sviridenko::BidirectionalList< T >::isEmpty()
{
  if (head_ == nullptr)
  {
    return true;
  }
  return false;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::beforeBegin()
{
  IteratorBL it;
  it.current_ = nullptr;
  it.next_ = head_;
  return it;
}
template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::begin()
{
  return IteratorBL(head_);
}
template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::end()
{
  return IteratorBL(nullptr);
}

template< typename T >
sviridenko::BidirectionalList< T >::IteratorBL::IteratorBL() :
  current_(nullptr),
  next_(nullptr)
{}
template< typename T >
sviridenko::BidirectionalList< T >::IteratorBL::IteratorBL(const IteratorBL& other) :
  current_(other.current_),
  next_(other.next_),
  prev_(other.prev_)
{}
template< typename T >
sviridenko::BidirectionalList< T >::IteratorBL::IteratorBL(Node< T >* node)
{
  if (node == nullptr)
  {
    current_ = nullptr;
    next_ = nullptr;
    prev_ = nullptr;
  }
  else
  {
    current_ = node;
    next_ = node->next_;
  }
}
template< typename T >
T& sviridenko::BidirectionalList< T >::IteratorBL::operator*()
{
  return current_->item_;
}

template< typename T >
const T& sviridenko::BidirectionalList< T >::IteratorBL::operator*() const
{
  return current_->data;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL&
sviridenko::BidirectionalList< T >::IteratorBL::operator=(const IteratorBL& other)
{
  IteratorBL newIt(other);
  std::swap(current_, newIt.current_);
  std::swap(next_, newIt.next_);
  return *this;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::IteratorBL::operator!=(const IteratorBL& lhs) const
{
  return !(*this == lhs);
}

template< typename T >
bool sviridenko::BidirectionalList< T >::IteratorBL::operator==(const IteratorBL& lhs) const
{
  return current_ == lhs.current_;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL& sviridenko::BidirectionalList< T >::IteratorBL::operator++()
{
  current_ = next_;
  if (next_ != nullptr)
  {
    next_ = next_->next_;
  }
  return *this;
}

template< typename T >
typename sviridenko::BidirectionalList< T >::IteratorBL sviridenko::BidirectionalList< T >::IteratorBL::operator++(int)
{
  IteratorBL result(*this);
  ++(*this);
  return result;
}

template< typename T >
const T* sviridenko::BidirectionalList< T >::IteratorBL::operator->() const
{
  return std::addressof(current_->data);
}

template < typename T >
sviridenko::BidirectionalList< T >::BidirectionalList() : head_(nullptr), tail_(nullptr), counter_(0)
{}

template < typename T >
sviridenko::BidirectionalList< T >::BidirectionalList(const BidirectionalList< T >& other) :
  head_(nullptr),
  tail_(nullptr),
  counter_(0)
{
  BidirectionalList< T > temp;
  Node< T >* src = other.head_;
  while (src)
  {
    temp.insertTail(src->item_);
    src = src->next_;
  }
  swap(temp);
}

template < typename T >
sviridenko::BidirectionalList< T >::BidirectionalList(BidirectionalList&& other) noexcept : head_(other.head_), tail_(other.tail_),
counter_(other.counter_)
{
  other.head_ = nullptr;
  other.tail_ = nullptr;
  other.counter_ = 0;
}

template < typename T >
sviridenko::BidirectionalList< T >::~BidirectionalList()
{
  Node< T >* current = nullptr;
  Node< T >* next = head_;
  while (next != nullptr)
  {
    current = next;
    next = next->next_;
    delete current;
  }
}


template< typename T >
void sviridenko::BidirectionalList< T >::swap(BidirectionalList& other) noexcept
{
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
  std::swap(counter_, other.counter_);
}

template< typename T >
sviridenko::BidirectionalList< T >& sviridenko::BidirectionalList< T >::operator=(const BidirectionalList& right)
{
  if (this != &right) {
    BidirectionalList temp(right);
    swap(temp);
  }
  return *this;
}

template< typename T >
sviridenko::BidirectionalList< T >& sviridenko::BidirectionalList< T >::operator=(BidirectionalList&& right) noexcept
{
  if (this != &right) {
    swap(right);
  }
  return *this;
}

template< typename T >
void sviridenko::BidirectionalList< T >::insertTail(Node< T >* x)
{
  if (tail_ == nullptr)
  {
    head_ = x;
    tail_ = x;
    return;
  }
  x->prev_ = tail_;
  tail_->next_ = x;
  tail_ = x;
}

template< typename T >
void sviridenko::BidirectionalList< T >::insertHead(Node< T >* x)
{
  if (head_ == nullptr)
  {
    head_ = x;
    tail_ = x;
    return;
  }
  x->next_ = head_;
  head_ = x;

}

template< typename T >
void sviridenko::BidirectionalList< T >::deleteNode(Node< T >* x)
{
  if (x->next_ == nullptr && x->prev_ == nullptr)
  {
    tail_ = nullptr;
    head_ = nullptr;
  }
  else if (x->next_ == nullptr)
  {
    x->prev_->next_ = nullptr;
    tail_ = x->prev_;
  }
  else if (x->prev_ == nullptr)
  {
    x->next_->prev_ = nullptr;
    head_ = x->next_;
  }
  else
  {
    x->prev_->next_ = x->next_;
    x->next_->prev_ = x->prev_;
  }
  delete x;

}

template< typename T >
sviridenko::Node< T >* sviridenko::BidirectionalList< T >::searchNode(T item)
{
  Node< T >* x = head_;
  while (x != nullptr && x->item_ != item) {
    x = x->next_;
  }
  return x;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::boolSearchItem(T item)
{
  typename sviridenko::BidirectionalList< T >::IteratorBL temp = begin();
  while (temp != end() && temp.current_->item_ != item)
  {
    typename sviridenko::BidirectionalList< T >::IteratorBL vanish = temp;
    if (++vanish == end())
    {
      break;
    }
    temp++;
  }
  if (temp != end())
  {
    if (temp.current_->item_ == item)
    {
      return true;
    }
    else
    {
      return false;
    }
  }
  return false;
}

template< typename T >
T sviridenko::BidirectionalList< T >::headItem() const
{
  return head_->item_;
}

template< typename T >
T& sviridenko::BidirectionalList< T >::headItem()
{
  return head_->item_;
}

template< typename T >
T sviridenko::BidirectionalList< T >::tailItem() const
{
  if (tail_ != nullptr) {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}

template< typename T >
T& sviridenko::BidirectionalList< T >::tailItem()
{
  if (tail_ != nullptr) {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}

template< typename T >
void sviridenko::BidirectionalList< T >::insertHead(T item)
{
  insertHead(new Node< T >(item));
  counter_++;
}

template< typename T >
void sviridenko::BidirectionalList< T >::insertTail(T item)
{
  insertTail(new Node< T >(item));
  counter_++;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::deleteHead()
{
  if (head_ == nullptr) {
    return 0;
  }
  deleteNode(head_);
  counter_--;
  return 1;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::deleteTail()
{
  if (tail_ == nullptr)
  {
    return 0;
  }
  deleteNode(tail_);
  counter_--;
  return 1;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::deleteItem(const T item)
{
  while (boolSearchItem(item))
  {
    deleteNode(searchNode(item));
    counter_--;
  }
  return 0;
}

template< typename T >
bool sviridenko::BidirectionalList< T >::searchItem(T item)
{
  return (searchNode(item) != nullptr);
}

template< typename T >
bool sviridenko::BidirectionalList< T >::replaceItem(T itemOld, T itemNew)
{
  Node< T >* x = head_;
  while (boolSearchItem(itemOld))
  {
    searchNode(itemOld)->item_ = itemNew;
  }
  x = x->next_;
  return true;
}
#endif
