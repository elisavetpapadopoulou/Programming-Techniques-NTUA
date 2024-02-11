/*
 * example.cpp
 *
 *  Created on: 3 Jun 2021
 *      Author: elisa
 */

#include <iostream>
#include <limits>
#include <string>

#include "avl.hpp"

using namespace std;

// Simple driver program for testing the AVL tree implementation.
// It starts with an empty tree and reads from stdin commands of the form:
//
//   i key   insert key
//   l key   prints "Y" if key was found, "N" if it was not
//   r key   removes key, if it exists
//   s       prints the tree size, i.e., number of nodes
//   c       clears the tree, i.e., removes all of its nodes
//   p       prints the tree's elements using in-order traversal
//
// All keys are integer numbers.

/*int main() {
  avltree<int> t;
  char op;
  while (cin >> op) {
    switch (op) {
      case 'i': {
        int key;
        cin >> key;
        t.insert(key);
        break;
      }
      case 'l': {
        int key;
        cin >> key;
        auto i = t.lookup(key);
        cout << (i == t.end() ? "N" : "Y") << endl;
        break;
      }
      case 'r': {
        int key;
        cin >> key;
        t.remove(key);
        break;
      }
      case 's': {
        cout << t.size() << endl;
        break;
      }
      case 'c': {
        t.clear();
        break;
      }
      case 'p': {
        bool sep = false;
        for (int x : t) {
          cout << (sep ? " " : "") << x;
          sep = true;
        }
        cout << endl;
        break;
      }
      case 'j': {
    	  int n;
    	  cin >> n;
    	  auto i = t.rank(n);
    	  if (i != t.end())
    		  cout << *i << endl;
    	  else
    		  cout << "WRONG" << endl;
    	  break;
      }
      default: {
        cerr << "Unknown operation: " << op << endl;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
    }
  }
}*/


/*int main() {
	avltree<int> t;
	t.insert(42);
	auto i = t.rank(0);
	cout << *i << endl;
	t.remove(42);
	i = t.rank(0);
	if (i != t.end())
		cout << *i << endl;
	t.insert(5);
	t.insert(6);
	t.insert(7);
	t.insert(3);
	i = t.rank(2);
	if (i != t.end())
	cout << *i << endl;
	i = t.rank(1);
	if (i != t.end())
	cout << *i << endl;
	t.insert(5);
	t.insert(2);
	i = t.rank(3);
	if (i != t.end())
	cout << *i << endl;
	t.remove(6);
	i = t.rank(0);
	if (i != t.end())
	cout << *i << endl;
	i = t.rank(1);
	if (i != t.end())
	cout << *i << endl;
	i = t.rank(2);
	if (i != t.end())
	cout << *i << endl;
	i = t.rank(3);
	if (i != t.end())
	cout << *i << endl;
	i = t.rank(4);
	if (i != t.end())
	cout << *i << endl;
	t.remove(5);
	i = t.rank(2);
	if (i != t.end())
	cout << *i << endl;
	t.remove(7);
	i = t.rank(2);
	if (i != t.end())
	cout << *i << endl;
	t.remove(3);
	i = t.rank(0);
	if (i != t.end())
	cout << *i << endl;

}*/

int main() {
	avltree<int> t;
	t.insert(20);
	t.insert(4);
	t.insert(26);
	t.insert(3);
	t.insert(9);
	t.insert(21);
	t.insert(30);
	t.insert(2);
	t.insert(7);
	t.insert(11);
	t.insert(15);
	t.remove(15);
	t.remove(7);
	t.remove(3);
	auto i = t.rank(0);
	if (i != t.end())
		cout << *i << endl;
	else
		cout << "Wrong" << endl;
}

