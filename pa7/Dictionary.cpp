/*
Eric Wang, twang173, Programming Assignment 7
*/

#include <iostream>
#include <string>
#include "Dictionary.h"
#include <climits>

std::string s;

Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
}


Dictionary::Dictionary(){  
    nil = new Node("\0", -1);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("\0", -1);
    nil->parent = nil;
    nil->left = nil;
    nil->right = nil;
    root = nil;
    current = nil;
    num_pairs = 0;

    if(this != &D){
        preOrderCopy(D.root, D.nil);
    }
}

Dictionary::Node* Dictionary::search(Dictionary::Node* R, keyType k) const {
    int compare = k.compare(R->key);
    if(R == nil || compare == 0){
        return R;
    } else if(compare < 0){
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
}

void Dictionary::preOrderCopy(Node* R, Node * N){
    if(R != N){
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
        setValue(R->key, R->val);
    }
    return;
}

Dictionary::~Dictionary(){
    postOrderDelete(this->root);
    num_pairs = 0;
    delete nil;
}

void Dictionary::postOrderDelete(Node* R){
    if(R != nil){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete R;
    }
}

int Dictionary::size() const{
    return(num_pairs);
}

bool Dictionary::contains(keyType k) const{
    if(search(root, k) != nil){
        return true;
    }
    return false;
}

valType& Dictionary::getValue(keyType k) const{
    Node *N = search(root, k);
    if(N == nil){
        throw std::logic_error("Dictionary: getValue(): key does not exist");
        exit(EXIT_FAILURE);
    }
    return N->val;
}

bool Dictionary::hasCurrent() const{
    if(current == nil){
        return false;
    } else {
        return true;
    }
}

keyType Dictionary::currentKey() const{
    if(!hasCurrent()){
        throw std::logic_error("Dictionary: currentKey(): current undefined");
        exit(EXIT_FAILURE);
    }
    return current->key;
}

valType& Dictionary::currentVal() const{
    if(!hasCurrent()){
        throw std::logic_error("Dictionary: currentVal(): current undefined");
        exit(EXIT_FAILURE);
    }
    return current->val;
}

void Dictionary::clear(){
    if(num_pairs == 0){
        return;
    }
    postOrderDelete(this->root);
    root = nil;
    current = nil;
    num_pairs = 0;
}

void Dictionary::setValue(keyType k, valType v){
    Node *M = nil;
    Node *tempNode = this->root;

    while(tempNode != nil){
        M = tempNode;
        if(k.compare(tempNode->key) < 0){
            tempNode = tempNode->left;
        } else if(k.compare(tempNode->key) > 0){
            tempNode = tempNode->right;
        } else{
            tempNode->val = v;
            return;
        }
    }
    Node *N = new Node(k, v);
    N->parent = M;
    if(M == nil){
        this->root = N;
    }
    else if(k < M->key){
        M->left = N;
    } else {
        M->right = N;
    }
    N->left = nil;
    N->right = nil;
    num_pairs += 1;
    return;
}

void Dictionary::remove(keyType k){
    if(!contains(k)){
        throw std::logic_error("Dictionary: remove(): key does not exist");
        exit(EXIT_FAILURE);
    }
    num_pairs -= 1;
    Node* tempNode = root;
    while(tempNode != nil){
        if(k.compare(tempNode->key) < 0){
            tempNode = tempNode->left;
        } else if(k.compare(tempNode->key) > 0){
            tempNode = tempNode->right;
        } else{
            break;
        }
    }
    if(tempNode == current){
        current = nil;
    }
    if(tempNode->left == nil){
        transplant(tempNode, tempNode->right);
        delete tempNode;
    } else if (tempNode->right == nil)
    {
        transplant(tempNode, tempNode->left);
        delete tempNode;
    }
    else{
        Node *N = findMin(tempNode->right);
        if(N->parent != tempNode){
            transplant(N, N->right);
            N->right = tempNode->right;
            N->right->parent = N;
        }
        transplant(tempNode, N);
        N->left = tempNode->left;
        N->left->parent = N;
        delete tempNode;
    }
}


void Dictionary::transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    } else if(u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    if(v != nil){
        v->parent = u->parent;
    }
}

void Dictionary::begin(){
    if(num_pairs != 0){
        current = findMin(root);
    }
}

void Dictionary::end(){
    if(num_pairs != 0){
        current = findMax(root);
    }
}

void Dictionary::next(){
    if(hasCurrent()){
        current = findNext(current);
    } else {
        throw std::logic_error("Dictionary: next(): current not defined");
        exit(EXIT_FAILURE);
    }
}

Dictionary::Node* Dictionary::findNext(Node* N){
    if(N == findMax(root)){
        return nil;
    }
    if(N->right != nil){
        return findMin(N->right);
    }
    Node* tempNode = N->parent;
    while((N == tempNode->right) && (tempNode != nil)){
        N = tempNode;
        tempNode = tempNode->parent;
    }
    return tempNode;
}

void Dictionary::prev(){
    if(hasCurrent()){
        current = findPrev(current);
    } else {
        throw std::logic_error("Dictionary: prev(): current not defined");
        exit(EXIT_FAILURE);
    }
}

Dictionary::Node* Dictionary::findPrev(Node* N){
    if(N == findMin(root)){
        return nil;
    }
    if(N->left != nil){
        return findMax(N->left);
    }
    Node* tempNode = N->parent;
    while((N == tempNode->left) && (tempNode != nil)){
        N = tempNode;
        tempNode = tempNode->parent;
    }
    return tempNode;
}

Dictionary::Node* Dictionary::findMin(Node* R){
    while(R->left != nil){
        R = R->left;
    }
    return R;
}

Dictionary::Node* Dictionary::findMax(Node* R){
    while(R->right != nil){
        R = R->right;
    }
    return R;
}

std::string Dictionary::to_string() const{
    stringSupport(root);
    std::string temp = s;
    s.clear();
    return temp;
}

void Dictionary::stringSupport(Node* root) const{
    if(root == nil){
        return;
    }
    stringSupport(root->left);
    s += root->key+" : ";
    s += std::to_string(root->val)+"\n";
    stringSupport(root->right);
}

std::string Dictionary::pre_string() const{
    std::string prestring;
    preOrderString(prestring, root);
    return prestring;
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s += R->key; 
        s += "\n";
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

bool Dictionary::equals(const Dictionary& D) const {
	Dictionary A = *this;
	Dictionary B = D;
	Node *x = A.root;
	Node *y = B.root;
	if (x == A.nil && y == B.nil) { // both are empty trees
		return true;
	}
	while (x != A.nil && y != B.nil) {
		if (x->key != y->key || x->val != y->val) {
			return false;
		}
		x = A.findNext(x);
		y = B.findNext(y);
	}
	// on last (rightmost) node
	x = x->right;
	y = y->right;
	if (x->key != y->key || x->val != y->val) {
		return false;
	}
	return true;
}

bool Dictionary::equalsSupport(Node* a, Node* b, const Dictionary& D) const{
    if(a == nil && b == D.nil){
        return true;
    } else if(a == nil && b != D.nil){
        return false;
    } else if(a != nil && b == D.nil){
        return false;
    } else {
        if(a->val == b->val && a->key == b->key && equalsSupport(a->left, b->left, D) && equalsSupport(a->right, b->right, D)){
            return true;
        } else {
            return false;
        }
    }
    exit(EXIT_FAILURE);
}

std::ostream& operator<<(std::ostream& stream, Dictionary& D){
    return stream << D.Dictionary::to_string();
}

bool operator==(const Dictionary& A, const Dictionary& B){
    return A.Dictionary::equals(B);
}

Dictionary& Dictionary::operator=(const Dictionary& D){
    if(this != &D){
        Dictionary tD = D;

        std::swap(nil, tD.nil);
        std::swap(current, tD.current);
        std::swap(root, tD.root);
        num_pairs = tD.num_pairs;
    }
    return *this;
}