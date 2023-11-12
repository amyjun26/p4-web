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
    return numElements == 0;
  }

  // EFFECTS: returns the number of elements in this List
  // HINT:    Traversing a list is really slow.  Instead, keep track of the size
  //          with a private member variable.  That's how std::list does it.
  int size() const
  {
    /*Node *p = first;

    while (p != nullptr)
    {
      numElements += 1;
      p = p->next;
    }*/
    return numElements;
  }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the first element in the list by reference
  T &front()
  {
    return first->datum;
  }

  // REQUIRES: list is not empty
  // EFFECTS: Returns the last element in the list by reference
  T &back()
  {
    return last->datum;
  }

  // EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum)
  {
    Node *newPtr = new Node;
    newPtr->datum = datum;

    // edge cases
    if (empty())
    {
      first = newPtr;
      last = newPtr;
      newPtr->prev = nullptr;
      newPtr->next = nullptr;
    }

    // connect nodes to each other
    if (!empty())
    {
      newPtr->next = first;
      first->prev = newPtr;

      // make newPtr the new first
      newPtr->prev = nullptr;
      // call newPtr first
      first = newPtr;
    }
    numElements++;
  }

  // EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum)
  {
    Node *newPtr = new Node;
    newPtr->datum = datum;

    // edge cases
    if (empty())
    {
      first = newPtr;
      last = newPtr;
      newPtr->next = nullptr;
      newPtr->prev = nullptr;
    }
    // connect nodes to each other
    if (!empty())
    {
      newPtr->prev = last;
      last->next = newPtr;

      // make newPtr the new last
      newPtr->next = nullptr;
      last = newPtr;
    }
    numElements++;
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the front of the list
  void pop_front()
  {
    if (empty())
    {
      last = nullptr;
      first = nullptr;
    }
    if (!empty())
    {
      Node *newPtr = first->next;
      // delete's the NODE that first is pointing to. aka deletes node in memory
      delete first;
      first = newPtr;

      numElements--;
    }
  }

  // REQUIRES: list is not empty
  // MODIFIES: may invalidate list iterators
  // EFFECTS:  removes the item at the back of the list
  void pop_back()
  {
    if (empty())
    {
      first = nullptr;
      last = nullptr;
    }
    if (!empty())
    {
      Node *newPtr = last->prev;
      // delete the NODE that last it pointing to
      delete last;
      last = newPtr;

      numElements--;
    }
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

  List &operator=(const List &rhs)
  {
    if (this == &rhs)
    {
      return *this;
    }
    clear();
    copy_all(rhs);
    this->numElements = rhs.numElements;
    return *this;
  }

  ~List()
  {
    clear();
  }

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
    for (Iterator it = other.begin(); it != other.end(); ++it)
    {
      // will create a pointer
      push_back(*it);
    }
  }

  Node *first; // points to first Node in list, or nullptr if list is empty
  Node *last;  // points to last Node in list, or nullptr if list is empty

  int numElements = 0;

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

    // my public operator implementations
    Iterator &operator++()
    {
      node_ptr = node_ptr->next;
      // og node_ptr
      return *this;
    }
    // for dereferencing
    T &operator*() const
    {
      assert(node_ptr);
      return node_ptr->datum;
    }
    bool operator==(Iterator rhs) const
    {
      return this->node_ptr == rhs.node_ptr;
    }
    bool operator!=(Iterator rhs) const
    {
      return this->node_ptr != rhs.node_ptr;
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

    // add any friend declarations here
    friend class List;

    // construct an Iterator at a specific position
    Iterator(Node *p) : node_ptr(p) {}

  }; // List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const
  {
    return Iterator(first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const
  {
    return Iterator(last);
  }

  // REQUIRES: i is a valid, dereferenceable iterator associated with this list
  // MODIFIES: may invalidate other list iterators
  // EFFECTS: Removes a single element from the list container
  void erase(Iterator i)
  {
    // edge cases
    if (i == first)
    {
      pop_front();
    }
    if (i == last)
    {
      pop_back();
    }
    // an iterator points to a node
    if (i != first && i != last)
    {
      i.node_ptr->prev->next = i.node_ptr->next;
      i.node_ptr->next->prev = i.node_ptr->prev;
    }
  }

  // REQUIRES: i is a valid iterator associated with this list
  // EFFECTS: inserts datum before the element at the specified position.
  void insert(Iterator i, const T &datum)
  {
    // edge cases - call first, push front
    if (i == first)
    {
      push_front(datum);
    }

    if (i != first)
    {
      // create a new node
      Node *newPtr = new Node;
      newPtr->datum = datum;

      newPtr->prev = i.node_ptr->prev;
      i.node_ptr->prev->next = newPtr;

      newPtr->next = i.node_ptr;
      i.node_ptr->prev = newPtr;
    }
  }

}; // List

////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.

#endif // Do not remove this. Write all your code above this line.
