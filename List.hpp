#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 Project 4
 */

#include <iostream>
#include <cassert> //assert
#include <cstddef> //NULL

template <typename T>
class List
{
  // OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:
  // EFFECTS:  returns true if the list is empty
  bool empty() const
  {
    return first == nullptr;
  }

  // EFFECTS: returns the number of elements in this List
  // HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //          with a private member variable.  That's how std::list does it.
  int size() const
  {
    int numElements;
    Node *p = first;

    while (p != nullptr)
    {
      numElements++;
      p = p->next;
    }
    return numElements;
  }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the first element in the list by reference
  T &front()
  {
    return first;
  }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the last element in the list by reference
  T &back()
  {
    return last;
  }

  // EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum)
  {
    Node *newPtr = new Node;
    newPtr->datum = datum;

    // connect nodes to each other
    newPtr->next = first;
    first->prev = newPtr;

    // make newPtr the new first
    newPtr->prev = nullptr;
    // call newPtr first
    first = newPtr;
  }

  // EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum)
  {
    Node *newPtr = new Node;
    newPtr->datum = datum;

    // connect nodes to each other
    newPtr->prev = last;
    last->next = newPtr;

    // make newPtr the new last
    newPtr->next = nullptr;
    last = newPtr;
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the front of the list
  void pop_front()
  {
    if (first == nullptr)
    {
      last == nullptr;
    }
    Node *newPtr = first->next;
    // delete's the NODE that first is pointing to. aka deletes node in memory
    delete first;
    first = newPtr;
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the back of the list
  void pop_back()
  {
    if (last == nullptr)
    {
      first == nullptr;
    }
    Node *newPtr = last->prev;
    // delete the NODE that last it pointing to
    delete last;
    last = newPtr;
  }

  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes all items from the list
  void clear()
  {
    while (first != nullptr)
    {
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you can omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists

  // my List constructors and overloaded assignment operators
  List() : first(nullptr), last(nullptr)
  {
  }

  ~List() {}

private:
  // a private type
  struct Node
  {
    Node *next;
    Node *prev;
    T datum;
  };

  // REQUIRES: list is empty
  // EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other)
  {
    for (Node *newPtr = first; newPtr != nullptr; newPtr = newPtr->next)
    {
      // will create a pointer
      push_back(other->datum);
      push_back(other->previous);
      push_back(other->next);
    }
  }

  Node *first; // points to first Node in list, or nullptr if list is empty
  Node *last;  // points to last Node in list, or nullptr if list is empty

public:
  ////////////////////////////////////////
  class Iterator
  {
    // OVERVIEW: Iterator interface to List

    // You should add in a default constructor, destructor, copy constructor,
    // and overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you can omit them. A user
    // of the class must be able to create, copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators: *,
    // ++ (prefix), default constructor, == and !=.

  public:
    // my constructors implementations
    Iterator() : node_ptr(nullptr)
    {
    }

    ~Iterator() {}

    // my public operator implementations
    Iterator &operator++()
    {
      node_ptr = node_ptr->next;
      return node_ptr;
    }
    // for dereferencing
    Iterator &operator*()
    {
      return node_ptr->datum;
    }
    bool &operator==(Iterator rhs)
    {
      return node_ptr == rhs.node_ptr;
    }
    bool &operator!=(Iterator rhs)
    {
      return node_ptr != rhs.node_ptr;
    }

    // This operator will be used to test your code. Do not modify it.
    // Requires that the current element is dereferenceable.
    Iterator &operator--()
    {
      assert(node_ptr);
      node_ptr = node_ptr->prev;
      return *this;
    }

  private:
    Node *node_ptr; // current Iterator position is a List node
    // add any additional necessary member variables here
    int size;

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p);

  }; // List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const
  {
    return Iterator(*first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const
  {
    return Iterator(*end);
  }

  // REQUIRES: i is a valid, dereferenceable iterator associated with this list
  // MODIFIES: may invalidate other list iterators
  // EFFECTS: Removes a single element from the list container
  void erase(Iterator i)
  {
    // an iterator points to a node
    Node *newPtr = i;
    Node *prevPtr = i->prev;
    Node *nextPtr = i->next;
    prevPtr->next = nextPtr;
    nextPtr->prev = prePtr;
    delete i;
  }

  // REQUIRES: i is a valid iterator associated with this list
  // EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum);

}; // List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
