// Oliver Kullmann, 23.2.2010 (Swansea)

/*!
  \file RootedTrees.hpp
  \brief Implementing the disjoint-sets data-structure via rooted trees
  according to CLRS

  See LinkedLists.hpp for further implementations of the DisjointSets concept,
  and also for explanations regarding this concept.
*/

#ifndef ROOTEDTREES_jHeqPo8r3
#define ROOTEDTREES_jHeqPo8r3

#include <ostream>
#include <iomanip>

namespace DisjointSets {

  /*!
    \class RootedTrees
    \brief Simple implementation using rooted trees
  */

  template <typename Element>
  class RootedTrees {
    struct Node {
      Element x;
      Node* p;
    };
  public :
    typedef Element value_type;
    typedef Node node_type;
    typedef const Node* pointer_type;
    static value_type value(const pointer_type x) { return x->x; }
    static pointer_type make_set(const value_type x) {
      Node* p = new Node;
      make_set(x, p);
      return p;
    }
    static void make_set(const value_type x, node_type* const p) {
      p->x = x;
      p->p = 0;
    }
    static pointer_type find_set(pointer_type x) {
      while (x->p != 0) x = x->p;
      return x;
    }
    static void union_sets(pointer_type x, const pointer_type y) {
      const_cast<Node*>(find_set(x))->p = const_cast<Node*>(find_set(y));
    }
  };

  /*!
    \class RootedTreesHS
    \brief Using the size heuristics.
  */

  template <typename Element>
  class RootedTreesHS {
    typedef unsigned int size_type;
    struct Node {
      Element x;
      Node* p;
      size_type s;
    };
  public :
    typedef Element value_type;
    typedef Node node_type;
    typedef const Node* pointer_type;
    static value_type value(const pointer_type x) { return x->x; }
    static pointer_type make_set(const value_type x) {
      Node* p = new Node;
      make_set(x, p);
      return p;
    }
    static void make_set(const value_type x, node_type* const p) {
      p->x = x;
      p->p = 0;
      p->s = 1;
    }
    static pointer_type find_set(pointer_type x) {
      while (x->p != 0) x = x->p;
      return x;
    }
    static void union_sets(pointer_type x, const pointer_type y) {
      Node* const x_root = const_cast<Node*>(find_set(x));
      Node* const y_root = const_cast<Node*>(find_set(y));
      if (x_root->s <= y_root->s) {
        x_root->p = y_root;
        y_root->s += x_root->s;
      }
      else {
        y_root->p = x_root;
        x_root->s += y_root->s;
      }
    }
  };

  /*!
    \class RootedTreesHP
    \brief Using path compression
  */

  template <typename Element>
  class RootedTreesHP {
    struct Node {
      Element x;
      Node* p;
    };
  public :
    typedef Element value_type;
    typedef Node node_type;
    typedef const Node* pointer_type;
    static value_type value(const pointer_type x) { return x->x; }
    static pointer_type make_set(const value_type x) {
      Node* p = new Node;
      make_set(x, p);
      return p;
    }
    static void make_set(const value_type x, node_type* const p) {
      p->x = x;
      p->p = 0;
    }
    static pointer_type find_set(const pointer_type x) {
      Node* y = const_cast<Node*>(x);
      Node* x_root = y;
      while (x_root->p != 0) x_root = x_root->p;
      while (y != x_root) {
        Node* const z = y->p;
        y->p = x_root;
        y = z;
      }
      return x_root;
    }
    static void union_sets(pointer_type x, const pointer_type y) {
      const_cast<Node*>(find_set(x))->p = const_cast<Node*>(find_set(y));
    }
  };

  /*!
    \class RootedTreesHSP
    \brief Using the size heuristics and path compression
  */

  template <typename Element>
  class RootedTreesHSP {
    typedef unsigned int size_type;
    struct Node {
      Element x;
      Node* p;
      size_type s;
    };
  public :
    typedef Element value_type;
    typedef Node node_type;
    typedef const Node* pointer_type;
    static value_type value(const pointer_type x) { return x->x; }
    static pointer_type make_set(const value_type x) {
      Node* p = new Node;
      make_set(x, p);
      return p;
    }
    static void make_set(const value_type x, node_type* const p) {
      p->x = x;
      p->p = 0;
      p->s = 1;
    }
    static pointer_type find_set(const pointer_type x) {
      Node* y = const_cast<Node*>(x);
      Node* x_root = y;
      while (x_root->p != 0) x_root = x_root->p;
      while (y != x_root) {
        Node* const z = y->p;
        y->p = x_root;
        y = z;
      }
      return x_root;
    }
    static void union_sets(pointer_type x, const pointer_type y) {
      Node* const x_root = const_cast<Node*>(find_set(x));
      Node* const y_root = const_cast<Node*>(find_set(y));
      if (x_root->s <= y_root->s) {
        x_root->p = y_root;
        y_root->s += x_root->s;
      }
      else {
        y_root->p = x_root;
        x_root->s += y_root->s;
      }
    }
  };

}

#endif
