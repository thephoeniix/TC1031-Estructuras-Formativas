#ifndef SplayTree_H_
#define SplayTree_H_

#include <string>
#include <sstream>
#include <iostream>

using namespace std;

template <class T> class SplayTree;

template <class T>
class Node {
private:
	T value;
	Node *left, *right, *parent;

	Node<T>* succesor();
	Node<T>* rot_right(Node<T>*);
	Node<T>* rot_left(Node<T>*);

public:
	Node(T);
	Node(T, Node<T>*, Node<T>* ,Node<T>*);
	Node<T>* add(T);
	Node<T>* find(T);
	Node<T>* remove(T);
	void removeChilds();
	void inorder(stringstream&) const;
	void print_tree(stringstream&) const;
	void preorder(stringstream&) const;
	Node<T>* splay(Node<T>*, Node<T>*);

	friend class SplayTree<T>;
};

template <class T>
Node<T>::Node(T val) : value(val), left(0), right(0), parent(0) {};

template <class T>
Node<T>::Node(T val, Node<T> *l, Node<T> *r, Node<T> *p) : value(val), left(l), right(r), parent(p) {};

template <class T>
Node<T>* Node<T>::add(T val) {
	if (val < value) {
		if (left != 0) {
			return left -> add(val);
		} 
        else {
			left = new Node<T>(val);
			left -> parent = this;
			return left;
		}
	} 
    else {
		if (right != 0) {
			return right -> add(val);
		} 
        else {
			right = new Node<T>(val);
			right -> parent = this;
			return right;
		}
	}
}

template <class T>
Node<T>* Node<T>::find(T val) {
	if (val == value) {
		return this;
	} 
    else if (val < value) {
		if (left != 0)
		 	return left -> find(val);
		else
			return this;
	} 
    else {
		if (right != 0)
		 	return right -> find(val);
		else
			return this;
	}
}

template <class T>
Node<T>* Node<T>::succesor() {
	Node<T> *l, *r;

	l = left;
	r = right;

	if (right -> left == 0) {
		right = right -> right;
		r -> right = 0;
		return r;
	}

	Node<T> *p, *c;
	p = right;
	c = right -> left;
	while (c -> left != 0) {
		p = c;
		c = c -> left;
	}
	p -> left = c -> right;
	c -> right = 0;
	return c;
}

template <class T>
Node<T>* Node<T>::remove(T val) {
	Node<T> *s, *o;
	if (val < value) {
		if (left != 0) {
			if (left -> value == val) {
				o = left;
				if(o -> left != 0 && o -> right != 0){
					s = left -> succesor();
					if (s != 0) {
						s -> left = o -> left;
						s -> right = o -> right;
						s -> parent = o -> parent;
						if(s -> left)
							s -> left -> parent = s;
						if(s -> right)
							s -> right -> parent = s;
					}
					left = s;
				} 
                else if (o -> right != 0){
					o -> right -> parent = left -> parent;
					left = o -> right;

				} 
                else if (o -> left != 0){ 
					o -> left -> parent = left -> parent;
					left = o -> left;
				} 
                else {  
					left = 0;
				}
				delete o;
				return this;
			} 
            else {
				return left -> remove(val);
			}
		}
	} 
    else if (val > value) {
		if (right != 0) {
			if (right->value == val) {
				o = right;
				if(o -> left != 0 && o -> right != 0){  
					s = right -> succesor();
					if (s != 0) {
						s -> left = o -> left;
						s -> right = o -> right;
						s -> parent = o -> parent;
						if(s -> left)
							s -> left -> parent = s;
						if(s -> right)
							s -> right -> parent = s;
					}
					right = s;
				} 
                else if (o -> right != 0){  
					o -> right -> parent = right -> parent;
					right = o -> right;

				} 
                else if (o -> left != 0){  
					o -> left -> parent = right -> parent;
					right = o -> left;
				} 
                else {  
					right = 0;
				}
				delete o;
				return this;
			} 
            else {
				return right -> remove(val);
			}
		}
	}
	return this;
}

template <class T>
void Node<T>::removeChilds() {
	if (left != 0) {
		left -> removeChilds();
		delete left;
		left = 0;
	}
	if (right != 0) {
		right -> removeChilds();
		delete right;
		right = 0;
	}
}

template <class T>
Node<T>* Node<T>::rot_right(Node<T>* x){
	Node<T> *y = x -> left;
	x -> left = y -> right;
	if (y -> right)
		y -> right -> parent = x;
	y -> right = x;
	y -> parent = x -> parent;
	x -> parent = y;
	if (y -> parent){
		if (y -> parent -> left && y -> parent -> left -> value == x -> value)
			y -> parent -> left = y;
		else
			y -> parent -> right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::rot_left(Node<T>* x){
	Node<T> *y = x -> right;
	x -> right = y -> left;
	if (y -> left)
		y -> left -> parent = x;
	y -> left = x;
	y -> parent = x -> parent;
	x -> parent = y;
	if (y -> parent){
		if (y -> parent -> left && y -> parent -> left -> value == x -> value)
			y -> parent -> left = y;
		else
			y -> parent -> right = y;
	}
	return y;
}

template <class T>
Node<T>* Node<T>::splay(Node<T>* root, Node<T>* x){
	while(x->parent != 0){

		if(x -> parent -> value == root -> value){
			if(x -> parent -> left && x -> parent -> left -> value == x -> value){
				rot_right(x -> parent);
			}
            else {
				rot_left(x -> parent);
			}
		}
        else{
			Node<T>*p = x -> parent;  
			Node<T>*g = p -> parent;  
			if (p -> left && g -> left && x -> value == p -> left -> value && p -> value == g -> left -> value){
				rot_right(g);
				rot_right(p);
			}
            else if (p->right && g->right && x -> value == p -> right -> value && p -> value == g -> right -> value){
				rot_left(g);
				rot_left(p);
			}
            else if (p->left && g->right && x -> value == p -> left -> value && p -> value == g -> right -> value){
				rot_right(p);
				rot_left(g);
			}
            else {
				rot_left(p);
				rot_right(g);
			}
		}
	}
	return x;
}

template <class T>
void Node<T>::inorder(stringstream &aux) const {
	if (left != 0) {
		left -> inorder(aux);
	}
	if (aux.tellp() != 1) {
		aux << " ";
	}
	aux << value;
	if (right != 0) {
		right -> inorder(aux);
	}
}

template <class T>
void Node<T>::print_tree(stringstream &aux) const {
	if (parent != 0){
		aux << "\n node " << value;
		aux << " parent " << parent -> value;
	}else
		aux << "\n root " << value;
	if (left != 0)
		aux << " left " << left -> value;
	if (right != 0)
		aux << " right " << right -> value;
	aux << "\n";

	if (left != 0) {
		left -> print_tree(aux);
	}
	if (right != 0) {
		right -> print_tree(aux);
	}
}

template <class T>
void Node<T>::preorder(stringstream &aux) const {
	aux << value;
	if (left != 0) {
		aux << " ";
		left -> preorder(aux);
	}
	if (right != 0) {
		aux << " ";
		right -> preorder(aux);
	}
}

template <class T>
class SplayTree {
private:
	Node<T> *root;
    int cant = 0;

public:
	SplayTree();
	~SplayTree();
	bool empty() const;
	void add(T);
	bool find(T);
	void remove(T);
	void removeAll();
    int size();
	string inorder() const;
	string print_tree() const;
	string preorder() const;
};

template <class T>
SplayTree<T>::SplayTree() : root(0) {};

template <class T>
SplayTree<T>::~SplayTree() {
	if (root != 0) {
		root -> removeChilds();
	}
	delete root;
	root = 0;
    cant = 0;
}

template <class T>
bool SplayTree<T>::empty() const {
	return (root == 0);
}

template<class T>
void SplayTree<T>::add(T val) {

	if (root != 0) {
			Node<T>* added = root -> add(val);
			root = root -> splay(root, added);
	} 
    else {
		root = new Node<T>(val);
	}
    cant ++;
}

template <class T>
void SplayTree<T>::remove(T val) {
	if (root != 0) {
		if (val == root -> value) {
			Node<T> *s = root -> succesor();
			if (s != 0) {
					s -> left = root -> left;
					s -> right = root -> right;
					s -> parent = 0;
					if(s -> left)
						s -> left -> parent = s;
					if(s -> right)
						s -> right -> parent = s;
			}
			delete root;
			root = s;
		} 
        else {
			Node<T>* p = root -> remove(val);
			root = root -> splay(root, p);
		}
	}
    cant --;
}

template <class T>
bool SplayTree<T>::find(T val){
	if (root != 0) {
		Node<T>* found = root -> find(val);
		root = root -> splay(root, found);
		return (root -> value == val);
	} 
    else {
		return false;
	}
}

template <class T>
int SplayTree<T>::size() {
    return cant;
}

template <class T>
string SplayTree<T>::inorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root -> inorder(aux);
	}
	aux << "]";
	return aux.str();
}

template <class T>
string SplayTree<T>::print_tree() const {
	stringstream aux;

	aux << "\n ================================ ";
	if (!empty()) {
		root -> print_tree(aux);
	}
	aux << " ================================ \n";
	return aux.str();
}

template <class T>
string SplayTree<T>::preorder() const {
	stringstream aux;

	aux << "[";
	if (!empty()) {
		root -> preorder(aux);
	}
	aux << "]";
	return aux.str();
}
#endif