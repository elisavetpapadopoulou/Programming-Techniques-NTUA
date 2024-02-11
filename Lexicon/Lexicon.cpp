/*
 * Lexicon.cpp
 *
 *  Created on: 23 May 2021
 *      Author: elisa
 */

#include <iostream>
#include <string>

using namespace std;

class lexicon {
public:
	lexicon();
	~lexicon();

	void insert (const string &s);
	int lookup (const string &s) const;
	int depth (const string &s) const;
	void replace (const string &s1, const string &s2);

	friend ostream & operator << (ostream &out, const lexicon &l);

private:
	struct node {
		string data;
		int counter = 0;
		node *left, *right;
	};
	node *root;

	node *max_left(node *t) {
		node *current;
		current = t;
		while (t != nullptr and t->right != nullptr)
			t = t->right;
		return current;
	}

	node *insert_help (node *t, const string &s) {
		if (t == nullptr) {
			node *p = new node;
			p->data = s;
			p->counter++;
			p->left = nullptr;
			p->right = nullptr;
			return p;
		}

		else if (t->data > s)
			t->left = insert_help(t->left, s);
		else if (t->data < s)
			t->right = insert_help(t->right, s);
		else if (t->data == s) {
			t->counter++;
			return t; //*************************************************
		}
		return t;
	}

	node *search (node *t, const string &key) const {
		if (t == nullptr)
			return nullptr;
		else if (t->data == key)
			return t;
		else if (t->data > key)
			return search(t->left, key);
		else
			return search(t->right, key);
	}

	node *delete_node (node *t, const string &key) {
		if (t == nullptr)
			return nullptr;
		else if (key < t->data)
			t->left = delete_node(t->left, key);
		else if (key > t->data)
			t->right = delete_node(t->right, key);
		else {
			if (t->left == nullptr and t->right == nullptr) {
				//delete t;
				return nullptr;
			}
			else if (t->left == nullptr) {
				node *p;
				p = t->right;
				//delete t;
				return p;
			}
			else if (t->right == nullptr) {
				node *p;
				p = t->left;
				//delete t;
				return p;
			}
			else {
				node *p;
				p = max_left(t->left);
				t->data = p->data;
				t->counter = p->counter;
				t->left = delete_node(t->left, p->data);
			}
		}
		return t;
	}

	void postorder (node *t) const {
		if (t != nullptr) {
			postorder(t->left);
			cout << t->data << " " << t->counter << endl;
			postorder (t->right);
		}
	}
};



lexicon::lexicon() {
	root = nullptr;
}

lexicon::~lexicon() {
	delete root;
}

void lexicon::insert (const string &s) {
	root = insert_help (root, s);
}

int lexicon::lookup(const string &s) const {
	node *p;
	p = search(root, s);
	if (p == nullptr)
		return 0;
	else
		return p->counter;
}

int lexicon::depth(const string &s) const {
	node *p;
	int counter = 0;
	p = root;

	while (p != nullptr) {
		if (p->data == s) return counter;
		else if (s < p->data) {
			p = p->left;
			counter++;
		}
		else if (s > p->data) {
			p = p->right;
			counter++;
		}
	}
	if (p == nullptr)
		return -1;
	else
		return counter;
}

void lexicon::replace(const string &s1, const string &s2) {
	node *p1, *p2;
	int k;
	p1 = search(root, s1);

	if (p1 == nullptr) return;
	else {
		k = p1->counter;
		root = delete_node(root, s1);
		p2 = search(root, s2);

		if (p2 == nullptr) {
			root = insert_help(root, s2);
			p2 = search(root, s2);
			p2->counter = k;
		}
		else {
			p2->counter+=k;
		}
	}
}

ostream & operator << (ostream &out, const lexicon &l) {
	lexicon::node *p;
	p = l.root;
	l.postorder(p);
	return out;
}

#ifndef CONTEST
int main() {
	lexicon l;
	l.insert("the");
	l.insert("boy");
	l.insert("and");
	l.insert("the");
	l.insert("wolf");
	cout << "The word 'the' is found " << l.lookup("the") << " time(s)" << endl;
	cout << "The word 'and' is found at depth " << l.depth("and") << endl;
	cout << l;
	l.replace("boy", "wolf");
	cout << "After replacement:\n";
	cout << l;
	cout << "Now the word 'and' is found at depth " << l.depth("and") << endl;
	l.replace("and", "dummy");
	cout << "wolf is now found " << l.lookup("wolf") << " time(s)" << endl;
	l.replace("boy", "dummy");
	cout << "Wolf is now found " << l.lookup("wolf") << " time(s)" << endl;
}

#endif
