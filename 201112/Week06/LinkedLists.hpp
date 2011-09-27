// Oliver Kullmann, 22.2.2010 (Swansea)

/*!
  \file LinkedLists.hpp
  \brief Implementing the disjoint-sets data-structure via linked lists
  according to CLRS

  General remarks on the concept of DisjointSets:
   - when using the version of make_set which creates the node, then the
     client becomes the owner of this node, and needs to delete it
     appropriately (via the returned pointer)
   - other implementations are in RootedTrees.hpp.

*/

#ifndef LINKEDLISTS_jBVCCr43W
#define LINKEDLISTS_jBVCCr43W

#include <ostream>
#include <iomanip>

namespace DisjointSets {

  /*!
    \class LinkedLists
    \brief Simple implementation using linked lists
  */

  template <typename Element>
  class LinkedLists {

    struct Node {
      Element x;
      Node* rep;
      Node* next;
      Node* last;
    };

  public :
    typedef Element value_type;
    typedef Node node_type;
    typedef const Node* pointer_type;

    static value_type value(const pointer_type x) { return x->x; }

    // returns the pointer to the node of x
    static pointer_type make_set(const value_type x) {
      Node* p = new Node;
      make_set(x, p);
      return p;
    }
    static void make_set(const value_type x, node_type* const p) {
      p->x = x;
      p->rep = p;
      p->next = 0;
      p->last = p;

    }

    static pointer_type find_set(const pointer_type x) { return x->rep; }

    static void union_sets(const pointer_type x, const pointer_type y) {
      Node* const new_rep = y->rep;
      new_rep->last->next = x->rep;
      new_rep->last = x->rep->last;
      for (Node* p = x->rep; p != 0; p = p->next)
        p->rep = new_rep;
    }

    // output the whole node together with its address
    static void output(std::ostream& out, pointer_type p) {
      using std::setw;
      out << (void*) p << "->" << setw(5) << p->x << " " << setw(10) << (void*) p->rep << " " << setw(10) << (void*) p->next << " " << setw(10) << (void*) p->last;
    }

  };


  /*!
    \class LinkedListsH
    \brief Implementation with size heuristics
  */

  template <typename Element>
  class LinkedListsH {

    typedef unsigned int size_type;

    struct Node {
      Element x;
      Node* rep;
      Node* next;
      Node* last;
      size_type s;
    };

  public :
    typedef Element value_type;
    typedef Node node_type;
    typedef const Node* pointer_type;

    static value_type value(const pointer_type x) { return x->x; }

    // returns the pointer to the node of x
    static pointer_type make_set(const value_type x) {
      Node* p = new Node;
      make_set(x, p);
      return p;
    }
    static void make_set(const value_type x, node_type* const p) {
      p->x = x;
      p->rep = p;
      p->next = 0;
      p->last = p;
      p->s = 1;
    }

    static pointer_type find_set(const pointer_type x) { return x->rep; }

    static void union_sets(pointer_type x, pointer_type y) {
      if (x->rep->s <= y->rep->s) {
        Node* const new_rep = y->rep;
        new_rep->last->next = x->rep;
        new_rep->last = x->rep->last;
        new_rep->s = new_rep->s + x->rep->s;
        for (Node* p = x->rep; p != 0; p = p->next)
          p->rep = new_rep;
      }
      else {
        Node* const new_rep = x->rep;
        new_rep->last->next = y->rep;
        new_rep->last = y->rep->last;
        new_rep->s += y->rep->s;
        for (Node* p = y->rep; p != 0; p = p->next)
          p->rep = new_rep;
      }
    }

    // output the whole node together with its address
    static void output(std::ostream& out, pointer_type p) {
      using std::setw;
      out << (void*) p << "->" << setw(5) << p->x << " " << setw(10) << (void*) p->rep << " " << setw(10) << (void*) p->next << " " << setw(10) << (void*) p->last << " " << setw(7) << p->s;
    }

  };

}

#endif
