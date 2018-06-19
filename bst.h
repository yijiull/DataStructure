#include <iostream>
class Node{
public:
    typedef Node* node_ptr;
    int val;
    node_ptr left, right, parent;
    Node(){
        left = right = parent = 0;
    }
    Node(int val):val(val){
        left = right = parent = 0;
    }
    static node_ptr increment(node_ptr x){
        node_ptr y;
        if(x->right == 0){
            y = x->parent;
            while(y != 0 && x == y->right){
                x = y;
                y = y->parent;
            }
            return y;
        }else{
            return mininum(x->right);
        }
    }
    static node_ptr mininum(node_ptr x){
        while(x->left != 0) x = x->left;
        return x;
    }
    static node_ptr maxinum(node_ptr x){
        while(x->right != 0) x = x->right;
        return x;
    }
};

class BST{
    typedef Node::node_ptr node_ptr;
private:
    node_ptr root;
    int& val(){
        return root->val;
    }
    node_ptr& left(){
        return root->left;
    }
    node_ptr& right(){
        return root->right;
    }

public:
    BST(){
        root = 0;
    }
    node_ptr& getroot(){
        return root;
    }
    bool insert_equal(int v){
        if(root == 0){
            root = new Node();
            root->val = v;
            return true;
        }else{
            node_ptr x = root, y = root;
            while(x != 0){
                y = x;
                if(v < x->val){
                    x = x->left;
                }else{
                    x = x->right;
                }
            }
            insert(y, v);
            return true;
        }
    }
    bool insert_unique(int v){
        if(root == 0){
            root = new Node();
            root->val = v;
            return true;
        }else{
            node_ptr x = root, y = root;
            while(x != 0){
                y = x;
                if(v < x->val){
                    x = x->left;
                }else if(v > x->val){
                    x = x->right;
                }else{
                    return false;
                }
            }
            insert(y, v);
        }
    }
    void insert(node_ptr x, int v){
        node_ptr z = new Node(v);
        if(v < x->val){
            x->left = z;
        }else{
            x->right = z;
        }
        z->parent = x;
        return ;
    }
    node_ptr find(int v){
        node_ptr cur = root;
        while(cur){
            if(v == cur->val){
                return cur;
            }else if(v < cur->val){
                cur = cur->left;
            }else{
                cur = cur->right;
            }
        }
        return cur;
    }
    void transplant(node_ptr u, node_ptr v){
        if(u->parent == 0){
            root = v;
        }else if(u == u->parent->left){
            u->parent->left = v;
        }else {
            u->parent->right = v;
        }
        if(v) v->parent = u->parent;
    }
    void remove(int v){
        node_ptr x = find(v);
        if(x){
            std::cout<<"找到:"<<v<<std::endl;
            if(x->left == 0){
                transplant(x, x->right);
            }else if(x->right == 0){
                transplant(x, x->left);
            }else{
                node_ptr y = Node::increment(x);
                std::cout<<"increment : "<<y->val<<std::endl;
                if(y->parent != x){
                    transplant(y, y->right);
                    y->right = x->right;
                    y->right->parent = y;
                }
                transplant(x, y);
                y->left = x->left;
                y->left->parent = y;
            }

        }
    }
    void print(node_ptr cur){
        if(cur == 0){
            std::cout<<"#\n";
            return;
        }
        std::cout<<cur->val<<std::endl;
        print(cur->left);
        print(cur->right);
    }

};