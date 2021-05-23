
#pragma once
// #include "node.hpp"
#include <set>
#include <map>
#include <queue>
#include <iostream>

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
			~node() { // delete children
				if(!_lc) delete _lc;
				if(!_rc) delete _rc;
			}
	};

//******************************************************************************************************
// 				PRE				
//******************************************************************************************************

	class preorder_iterator {
	node* pointer_to_current_node;
    queue<node*> nodesQ;
	public:
        void insert_preorder(node* root){
			// cout<< " ***  " << ++ ad<< endl;
            if(nullptr ==root) return;
            nodesQ.push(root);
            // if(nullptr !=root->_lc)
			insert_preorder(root->_lc);
            // if(nullptr !=root->_rc)
			insert_preorder(root->_rc);
        }
		preorder_iterator(node* ptr ){
			// cout<< " in pre creation  " << endl;
            insert_preorder(ptr);
            pointer_to_current_node = nodesQ.front();
            nodesQ.pop();
			// cout<< " out of pre creation  " << endl;
		}
		T& operator*() const {
			return pointer_to_current_node->_data;
		}
		T* operator->() const {
			return &(pointer_to_current_node->_data);
		}
		preorder_iterator& operator++() {
			if(nodesQ.empty()){
                pointer_to_current_node = nullptr;
                return *this;
            }
            pointer_to_current_node = nodesQ.front();
            nodesQ.pop();
            return *this;
		}

		// i++;
		// Usually iterators are passed by value and not by const& as they are small.
		const preorder_iterator operator++(int) {
            if(nodesQ.empty()){
                pointer_to_current_node = nullptr;
                return *this;
            }
			preorder_iterator tmp= *this;
			++this;
			return tmp;
		}

		bool operator==(const preorder_iterator& rhs) const {
			return pointer_to_current_node == rhs.pointer_to_current_node;
		}

		bool operator!=(const preorder_iterator& rhs) const {
			return pointer_to_current_node != rhs.pointer_to_current_node;
		}
	 }; // END OF CLASS PREORDER ITER
	preorder_iterator begin_preorder() {
		return preorder_iterator(_root);
	}
	
	preorder_iterator end_preorder() {
		return preorder_iterator{nullptr};
	}	


//******************************************************************************************************
// 				POST				
//******************************************************************************************************
	class postorder_iterator {
	node* pointer_to_current_node;
    queue<node*> nodesQ;

	public:
        void insert_postorder(node* root){
            if(!root) return;
            insert_postorder(root->_lc);
            insert_postorder(root->_rc);
            nodesQ.push(root);
        }
			postorder_iterator(node* ptr = nullptr){
                insert_postorder(ptr);
                pointer_to_current_node = nodesQ.front();
                nodesQ.pop();
		}
		T& operator*() const {
			return pointer_to_current_node->_data;
			// we want to return the value in the node 
		}

		T* operator->() const {
			return &(pointer_to_current_node->_data);
		}

		// postorder_iterator operator+( const int i){
        //     postorder_iterator temp = &begin_postorder(this);
			
        //     for(int j = 0; j < i; j++){
		// 		temp++;	
		// 	}
			
		// 	pointer_to_current_node = temp;
		// 	return temp;
		// }
		// ++i;
		postorder_iterator& operator++() {
			if(nodesQ.empty()){
                pointer_to_current_node = nullptr;
                return *this;
            }
            pointer_to_current_node = nodesQ.front();
            nodesQ.pop();
            return *this;
		}


		// i++;
		// Usually iterators are passed by value and not by const& as they are small.
		const postorder_iterator operator++(int) {
			if(nodesQ.empty()){
                pointer_to_current_node = nullptr;
                return *this;
            }
			iterator tmp= *this;
			++this;
			return tmp;
		}

		bool operator==(const postorder_iterator& rhs) const {
			return pointer_to_current_node == rhs.pointer_to_current_node;
		}

		bool operator!=(const postorder_iterator& rhs) const {
			return pointer_to_current_node != rhs.pointer_to_current_node;
		}
	 }; // END OF CLASS PREORDER ITER
	postorder_iterator begin_postorder() {
		return postorder_iterator(_root);
	}
	
	postorder_iterator end_postorder() {
		return postorder_iterator{nullptr};
	}

    	
	
//******************************************************************************************************
// 				IN				
//******************************************************************************************************
	class inorder_iterator {
	node* pointer_to_current_node;
    queue <node*> nodesQ;
	public:
		void insert_inorder(node* root){
            if(!root) return;
            insert_inorder(root->_lc);
            nodesQ.push(root);
            insert_inorder(root->_rc);
        }
        inorder_iterator(node* ptr = nullptr)
		{
            insert_inorder(ptr);
            pointer_to_current_node = nodesQ.front();
            nodesQ.pop();
		}
		T& operator*() const {
			return pointer_to_current_node->_data;
			// we want to return the value in the node 
		}

		T* operator->() const {
			return &(pointer_to_current_node->_data);
		}
		// ++i;
		inorder_iterator& operator++() {
			// this.pointer_to_current_node->_visited = true;
			if(nodesQ.empty()){
                pointer_to_current_node = nullptr;
                return *this;
            }
            pointer_to_current_node = nodesQ.front();
            nodesQ.pop();
            return *this;
		}

		// i++;
		// Usually iterators are passed by value and not by const& as they are small.
		const inorder_iterator operator++(int) {
			if(nodesQ.empty()){
                pointer_to_current_node = nullptr;
                return *this;
            }
			iterator tmp= *this;
			++this;
			return tmp;
		}

		bool operator==(const inorder_iterator& rhs) const {
			return pointer_to_current_node == rhs.pointer_to_current_node;
		}

		bool operator!=(const inorder_iterator& rhs) const {
			return pointer_to_current_node != rhs.pointer_to_current_node;
		}
	 }; // END OF CLASS PREORDER ITER
	inorder_iterator begin_inorder() {
		return inorder_iterator{_root};
	}
	
	inorder_iterator end_inorder() {
		return inorder_iterator{nullptr};
	}

    inorder_iterator begin() {
		return inorder_iterator{_root};
	}
	
	inorder_iterator end() {
		return inorder_iterator{nullptr};
	}

private:
	// fields
	map< T, set <node* >> nodes;
    node* _root; //, _left, _right; 
public:	


	BinaryTree() : _root(nullptr) {
		// cout<< "in creation" << endl;
	}

	~BinaryTree() {
		delete _root;
	}

	BinaryTree& add_root(const T& d)
    {
		// cout<< "in add root" << endl;
		if(_root) {
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
		node* f;
		for(node * n: nodes.at(df)){
			f = n;
			break;
		}
		if(f->_lc) {
			nodes.erase(f->_lc->_data);
			nodes[d].insert(f->_lc);
			node * child = f->_lc;
			child->_data = d;
			return *this;
		}
		f->_lc =  new node(f, d);
		nodes[d].insert(f->_lc);    
		return *this;
	}

	BinaryTree& add_right(T df, T d) {
		if(nodes.count(df) == 0){
			throw std::invalid_argument{" doesn't have this node in the tree"};
		}
		node* f;
		for(node * n: nodes.at(df)){
			f = n;
			break;
		}
		if(f->_rc) {
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
    }
    friend std::ostream& operator <<	(std::ostream &os, const BinaryTree<T> &bt){
        return os  << "[" << "ss" << "]";
    }


}; 
 };