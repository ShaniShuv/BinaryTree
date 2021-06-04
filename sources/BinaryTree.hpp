
#pragma once
// #include "node.hpp"
#include <set>
#include <map>
#include <queue>
#include <iostream>
const int PRE = 0;
const int POST = 1;
const int IN = 2;
int ad = 0;
// to delete:
using namespace std;

namespace ariel{
	template<typename T>
	class BinaryTree {

		public:
			class node {
            public:
                T _data; node *  _father,*_lc,* _rc;
                node(node* f,  T d) : _father(f), _data(d), _lc(nullptr), _rc(nullptr){}
                node(const node& other)noexcept{}
				node(node&& other)noexcept{}
				node& operator=(const node n){
					if(this != n){
						this->_data = n._data;
					}
					return *this;
				}
				node &operator=(node &&n) noexcept{
					return *this;
				}
                ~node() { // delete children
                    if(nullptr != _lc) {delete _lc;}
                    if(nullptr != _rc) {delete _rc;}
                }
	        };
	class iterator {
		public:
		node* pointer;
	    queue<node*> nq;
		void insert_inorder(node* root){
            if(root == nullptr) {return;}
            insert_inorder(root->_lc);
            nq.push(root);
            insert_inorder(root->_rc);
	    }

        void insert_preorder(node* root){
            if(nullptr ==root) {return;}
            nq.push(root);
            // if(nullptr !=root->_lc)
            insert_preorder(root->_lc);
            // if(nullptr !=root->_rc)
            insert_preorder(root->_rc);
        }

        void insert_postorder(node* root){
            if(root == nullptr) {return;}
            insert_postorder(root->_lc);
            insert_postorder(root->_rc);
            nq.push(root);
        }
        
        iterator(node* root) : pointer(root){}
	    
        iterator(node* root, const int c){
		// cout<< " in pre creation  " << endl;
		// insert_preorder(ptr);
		switch (c)
		{
            case PRE:
                insert_preorder(root);
                break;
            case POST:
                insert_postorder(root);
                break;
            case IN:
                insert_inorder(root);
                break;
            }
            pointer = nq.front();
            nq.pop();
            // cout<< " out of pre creation  " << endl;
        }

        T& operator*() const {
            // if(pointer == nullptr) cout << " ****************************" << endl ; //return null;
            return pointer->_data;
        }

        T& operator*(){
            // if(pointer == nullptr) cout << " **************************** null" << endl ; //return null;
            return pointer->_data;
        }

        T* operator->() const {
            //         if(pointer == nullptr) return null;
            return &(pointer->_data);
        }

        iterator& operator++() {
            if(nq.empty()){
                pointer = nullptr;
                return *this;
            }
            pointer = nq.front();
            nq.pop();
            return *this;
        }
	// i++;
	// Usually iterators are passed by value and not by const& as they are small.
        //const
		 iterator operator++(int) {
            iterator tmp = *this;
            if(nq.empty()){
                pointer = nullptr;
                return tmp;
            }
            pointer = nq.front();
            nq.pop();
            return tmp;
        }

        bool operator==(const iterator& rhs) const {
            // return pointer._data == rhs.pointer._data;
            return rhs.pointer==this->pointer;
        }
        
        bool operator!=(const iterator& rhs) const {
            return rhs.pointer!=this->pointer;
        }
	}; // END OF CLASS PREORDER ITER
	iterator begin_inorder() {
		if(_root == nullptr) {
			return iterator(nullptr);
		}
		return iterator{_root, IN};
	}

	iterator end_inorder() {
		return iterator{nullptr};
	}

	iterator begin() {
		if(_root == nullptr) {
			return iterator(nullptr);
		}
		return iterator{_root, IN};
	}

	iterator end() {
		return iterator{nullptr};
	}

	iterator begin_preorder() {
		if(_root == nullptr) {
			return iterator(nullptr);
		}
		return iterator(_root, PRE);
	}

	iterator end_preorder() {
		return iterator{nullptr};
	}

	iterator begin_postorder() {
		if(_root == nullptr) {
			return iterator(nullptr);
		}
		return iterator(_root, POST);
	}

	iterator end_postorder() {
		return iterator{nullptr};
	}


	// private:
	// fields
	map< T, set <node* >> nodes;
	node* _root; //, _left, _right; 


		BinaryTree() : _root(nullptr) {}

		BinaryTree (const BinaryTree &bt) {
			_root = new node(nullptr, bt._root->_data);
			copy_con(_root, bt._root);
		}
        // BinaryTree(BinaryTree &&bt) noexcept {
        //     _root = bt._root;
        //     bt._root = nullptr;
        // }

		BinaryTree(BinaryTree &&bt) noexcept {
			if(_root == bt._root){return;}
			if(_root == nullptr) {delete _root;}
			_root = new node(nullptr, bt._root->_data);
			copy_con(_root, bt._root);
			bt._root = nullptr;
		}
		
        void copy_con(node* n1, node* n2){
			if(n2 == nullptr) {return;}
			// n1->_data = n2->_data;
			if(n2->_lc != nullptr){
				n1->_lc = new node(n1, n2->_lc->_data);
				copy_con(n1->_lc, n2->_lc);
			}
			if(n2->_rc != nullptr){
				n1->_rc = new node(n1, n2->_rc->_data);
				copy_con(n1->_rc, n2->_rc);
			}
		}
        


		BinaryTree& operator=(const BinaryTree bt){
			if(this == &bt){
				return *this;
			}
			if(_root != nullptr) {
				delete _root;
			}
			if(bt._root!= nullptr) {
				_root = new node(nullptr, bt._root->_data);
				copy_con(_root, bt._root);
			}
			return *this;
		}

		BinaryTree& operator=(BinaryTree && bt)noexcept{
			if(_root == bt._root){return *this;}
			if(_root == nullptr) {delete _root;}
			_root = new node(nullptr, bt._root->_data);
			copy_con(_root, bt._root);
			bt._root = nullptr;
			return *this;
		}

		~BinaryTree() noexcept {
			if(_root != nullptr){
				delete _root;
			}
		}

		BinaryTree& add_root(T d)
		{
			// cout<< "in add root" << endl;
			if(_root != nullptr) {
				nodes.erase(_root->_data);
				nodes[d].insert(_root);
				_root->_data = d;
				return *this;
			}
			_root = new node(nullptr, d);
			nodes[d].insert(_root);
			// cout<< "out of add root" << endl;
			return *this;
		}

		BinaryTree& add_left(T df, T d) {
			// cout<< "in add left" << endl;
			// cout<< "	father: " << df << " child: " << d << endl;
			if(nodes.count(df) == 0){
				throw std::invalid_argument{" doesn't have this node in the tree"};
			}
			// node* f = new node(_root, _root->_data);
			for(node * f: nodes.at(df)){
				// node* f = n;

				if(f->_lc != nullptr) {
					nodes.erase(f->_lc->_data);
					nodes[d].insert(f->_lc);
					node * child = f->_lc;
					child->_data = d;
					return *this;
				}
				f->_lc =  new node(f, d);
				nodes[d].insert(f->_lc);
				return *this;
				break;
			}
			return *this;
		}

		BinaryTree& add_right(T df, T d) {
			if(nodes.count(df) == 0){
				throw std::invalid_argument{" doesn't have this node in the tree"};
			}
			// node* f = new node(_root->_data, _root->_data);
			for(node * n: nodes.at(df)){
				node* f = n;

				if(f->_rc != nullptr) {
					nodes.erase(f->_rc->_data);
					nodes[d].insert(f->_rc);
					f->_rc->_data = d;
					return *this;
				}
				f->_rc =  new node(f, d);
				nodes[d].insert(f->_rc);
				// if(f == _right){
					// 	_right = np;
				// }`
				return *this;
				break;
			}
			return *this;
		}
		
        friend std::ostream& operator <<	(std::ostream &os, const BinaryTree<T> &bt){
			return os  << "[" << "ss" << "]";
		}
	}; 
};

