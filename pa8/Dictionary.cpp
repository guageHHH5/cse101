/*
Eric Wang, twang173, Programming Assignment 8
*/

#include <iostream>
#include <string>
#include "Dictionary.h"
#include <climits>

#define BLACK 4
#define RED 2



Dictionary::Node::Node(keyType k, valType v){
    key = k;
    val = v;
    parent = nullptr;
    left = nullptr;
    right = nullptr;
    color = 9;
}

void Dictionary::inOrderString(std::string& s, Node* R) const{
    if(R != nil){
        inOrderString(s, R->left);
        s.append(R->key);
        s.append(" : ");
        s.append(std::to_string(R->val));
        s.append("\n");
        inOrderString(s, R->right);
    }
}
Dictionary::Dictionary(){  
    nil = new Node("asdfhopiur", -2);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
}

Dictionary::Dictionary(const Dictionary& D){
    nil = new Node("asdfhopiur", -2);
    nil->color = BLACK;
    root = nil;
    current = nil;
    num_pairs = 0;
    preOrderCopy(D.root, D.nil);
    // if(this != &D){
    //     preOrderCopy(D.root, D.nil);
    // }
}

Dictionary::Node* Dictionary::search(Dictionary::Node* R, keyType k) const {
    //int compare = k.compare(R->key);
    if(R == nil || k == R->key){
        return R;
    } else if(k < R->key){
        return search(R->left, k);
    } else {
        return search(R->right, k);
    }
}

void Dictionary::preOrderCopy(Node* R, Node * N){
    if(R != N){
        setValue(R->key, R->val);
        preOrderCopy(R->left, N);
        preOrderCopy(R->right, N);
        
    }
}

Dictionary::~Dictionary(){
    clear();
    delete (nil);
}

void Dictionary::postOrderDelete(Node* R){
    if(R != nil && R != nullptr){
        postOrderDelete(R->left);
        postOrderDelete(R->right);
        delete(R);
        num_pairs -= 1;
    }
}

int Dictionary::size() const{
    return num_pairs;
}

bool Dictionary::contains(keyType k) const{
    if(root == nil){
        return false;
    }
    if(search(root, k) == nil){
        return false;
    }
    return true;
}

valType& Dictionary::getValue(keyType k) const{
    Node* N = search(root, k);
    if(N == nil){
        throw std::logic_error("Dictionary: getValue(): key does not exist");
        //exit(EXIT_FAILURE);
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
    postOrderDelete(root);
    num_pairs = 0;
    root = nil;
    current = nil;
    
}

void Dictionary::setValue(keyType k, valType v){
    // if(contains(k)){
    //     Node* tempNode = root;
    //     while(tempNode != nil){
    //         if(k.compare(tempNode->key) == 0){
    //             tempNode->val = v;
    //             return;
                
    //         } else if(/*k.compare(tempNode->key) > 0*/k.compare(tempNode->key) < 0){
    //             tempNode = tempNode->left;
    //         } else{
    //             tempNode = tempNode->right;
    //         }
    //     }
    // }
    Node* y = nil;
    Node* x = root;
    while(x != nil && x != nullptr){
        y = x;
        if(k == x->key){
            x->val = v;
            return;
        } else if (k < x->key){
            x = x->left;
        } else {
            x = x->right;
        }
    }
    Node* N = new Node(k, v); //z
    num_pairs += 1;
    N->parent = y;
    if(y == nil){
        root = N;
        root->left = nil;
        root->right = nil;
        root->parent = nil;
    } else if (k < y->key){
        y->left = N;
    } else {
        y->right = N;
    }
    N->left = nil;
    N->right = nil;
    N->color = RED;
    RB_InsertFixUp(N);
}

void Dictionary::remove(keyType k){
    if (contains(k) != true) {
        throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
    }
    Node* N = search(root, k);
    Node* M = N;
    Node* Z = N->right;
    int green = M->color;
    if (N->left == nil){
        Z = N->right;
        RB_Transplant(N, N->right);
    }
    else if(N->right == nil){
        Z = N->left;
        RB_Transplant(N, N->left);
    }
    else{
        M = findMin(N->right);
        green = M->color;
        Z = M->right;
        if (M->parent == N){
            Z->parent = M;
        }
        else{
            RB_Transplant(M, M->right);
            M->right = N->right;
            M->right->parent = M;
        }
        RB_Transplant(N, M);
        M->left = N->left;
        M->left->parent = M;
        M->color = N->color;
    }
    if(green == BLACK){
        RB_DeleteFixUp(Z);
    }
    if(current == N){
        current = nil;
    }
    delete(N);
    num_pairs--;
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
    if(root != nil){
        current = root;
        while(current->left != nil){
            current = current->left;
        }
    }
}

void Dictionary::end(){
    if(root != nil){
        current = root;
        while(current->right != nil){
            current = current->right;
        }
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
    if(N == nil || findMax(root) == N){
        return nil;
    }
    if(N->right != nil){
        return findMin(N->right);
    }
    Node* tempNode = N->parent;
    Node* C = N;
    while((C == tempNode->right) && (tempNode != nil)){
        C = tempNode;
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
    if(N == nil || findMin(root) == N){
        return nil;
    }
    if(N->left != nil){
        return findMax(N->left);
    }
    Node* tempNode = N->parent;
    Node* C = N;
    while((C == tempNode->left) && (tempNode != nil)){
        C = tempNode;
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
    //stringSupport(root);
    std::string temp;
    inOrderString(temp, root);
    return temp;
}


std::string Dictionary::pre_string() const{
    std::string prestring;
    preOrderString(prestring, root);
    return prestring;
}

void Dictionary::preOrderString(std::string& s, Node* R) const{
    if(R != nil){
        s.append(R->key);
        if(R->color == RED){
            s.append(" (RED)");
        }
        s.append("\n");
        preOrderString(s, R->left);
        preOrderString(s, R->right);
    }
}

bool Dictionary::equals(const Dictionary& D) const {
    if (this->size() == 0 && D.size() == 0) {
        return true;
    }
    if (this->size() != D.size()) {
        return false;
    }
    // iterate over dict 1, call contains on dict 2
    Dictionary newD = D;
    newD.begin();
    bool eq = true;
    while (newD.current != newD.nil && eq){
        eq = this->contains(newD.current->key);
        if (eq){
            eq = (newD.current->val == getValue(newD.current->key) );
        }
        newD.next();
    }
    return eq;
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
        std::swap(root, tD.root);
        std::swap(current, tD.current);
        std::swap(num_pairs, tD.num_pairs);
    }
    return *this;
}

//RBT helpers

void Dictionary::LeftRotate(Node* x){
    Node* n = x->right;

    x->right = n->left;
    if(n->left != nil){
        n->left->parent = x;
    }

    n->parent = x->parent;
    if(x->parent == nil){
        root = n;
    } else if(x == x->parent->left){
        x->parent->left = n;
    } else {
        x->parent->right = n;
    }

    n->left = x;
    x->parent = n;
}

void Dictionary::RightRotate(Node* x){
    Node* n = x->left;

    x->left = n->right;
    if(n->right != nil){
        n->right->parent = x;
    }

    n->parent = x->parent;
    if(x->parent == nil){
        root = n;
    } else if(x == x->parent->right){
        x->parent->right = n;
    } else {
        x->parent->left = n;
    }

    n->right = x;
    x->parent = n;
}

void Dictionary::RB_InsertFixUp(Node* z){
    Node* y;
    while(z->parent->color == RED){
        if(z->parent == z->parent->parent->left){
            y = z->parent->parent->right;
            if(y->color == RED){
                z->parent->color = BLACK;           //case 1
                y->color = BLACK;                   //case 1
                z->parent->parent->color = RED;     //case 1
                z = z->parent->parent;              //case 1
            } else {
                if(z == z->parent->right){
                    z = z->parent;                  //case 2
                    LeftRotate(z);                  //case 2
                }
                z->parent->color = BLACK;           //case 3
                z->parent->parent->color = RED;     //case 3
                RightRotate(z->parent->parent);     //case 3
            }
        } else {
            y = z->parent->parent->left;
            if(y->color == RED){
                z->parent->color = BLACK;           //case 4
                y->color = BLACK;                   //case 4
                z->parent->parent->color = RED;     //case 4
                z = z->parent->parent;              //case 4
            } else {
                if(z == z->parent->left){
                    z = z->parent;                  //case 5
                    RightRotate(z);                 //case 5
                }
                z->parent->color = BLACK;           //case 6
                z->parent->parent->color = RED;     //case 6
                LeftRotate(z->parent->parent);      //case 6
            }
        }
    }
    root->color = BLACK;
}

void Dictionary::RB_Transplant(Node* u, Node* v){
    if(u->parent == nil){
        root = v;
    } else if(u == u->parent->left){
        u->parent->left = v;
    } else {
        u->parent->right = v;
    }
    v->parent = u->parent;
}

void Dictionary::RB_DeleteFixUp(Node* x){
    Node *w;
    while(x != root && x->color == BLACK){
        if(x == x->parent->left){
            w = x->parent->right;
            if(w->color == RED){
                w->color = BLACK;                    // case 1 starts  
                x->parent->color = RED;
                LeftRotate(x->parent);
                w = x->parent->right;                // case 1 ends
            }
            if(w->left->color == BLACK && w->right->color == BLACK){
                w->color = RED;                      // case 2 starts
                x = x->parent;                       // case 2 ends
            } else {
                if (w->right->color == BLACK){
                    w->left->color = BLACK;          // case 3 starts
                    w->color = RED;
                    RightRotate(w);
                    w = w->parent->right;            // case 3 ends
                }
                w->color = x->parent->color;         // case 4 starts
                x->parent->color = BLACK;
                w->right->color = BLACK;
                LeftRotate(x->parent);
                x = root;                            // case 4 ends
            }
        } else {
            w = x->parent->left;
            if(w->color == RED){
                w->color = BLACK;                    // case 5 starts
                x->parent->color = RED;
                RightRotate(x->parent);
                w = x->parent->left;                 // case 5 ends
            }
            if(w->right->color == BLACK && w->left->color == BLACK){
                w->color = RED;
                x = x->parent;
            } else {
                if(w->left->color == BLACK){
                    w->right->color = BLACK;         // case 7 starts
                    w->color = RED;
                    LeftRotate(w);
                    w = x->parent->left;             // case 7 ends
                }
                w->color = x->parent->color;         // case 8 starts
                x->parent->color = BLACK;
                w->left->color = BLACK;
                RightRotate(x->parent);
                x = root;                            // case 8 ends
            }
        }
    }
    x->color = BLACK;
}

void Dictionary::RB_Delete(Node* z){
    Node* x;
    Node* y = z;
    int y_original_color = y->color;
    if(z->left == nil){
        x = z->right;
        RB_Transplant(z, z->right);
        delete z;
    } else if(z->right == nil) {
        x = z->left;
        RB_Transplant(z, z->left);
        delete z;
    } else {
        y = findMin(z->right);
        y_original_color = y->color;
        x = y->right;
        if(y->parent == z){
            x->parent = y;
        } else {
            RB_Transplant(y, y->right);
            y->right = z->right;
            y->right->parent = y;
        }
        RB_Transplant(z, y);
        y->left = z->left;
        y->left->parent = y;
        y->color = z->color;
        delete z;
    }
    if(x != nil && y_original_color == BLACK){
        RB_DeleteFixUp(x);
    }
}