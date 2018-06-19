#include "rbNode.h"
class rbTree{
    const bool red = 0;
    const bool black = 1;
private:
    typedef rbNode::node_ptr node_ptr;
    node_ptr header;
    node_ptr nil;
public:
    node_ptr& left(node_ptr p){
        return p->left;
    }
    node_ptr& right(node_ptr p){
        return p->right;
    }
    node_ptr& parent(node_ptr p){
        return p->parent;
    }
    node_ptr& root(){
        return header->parent;
    }
    node_ptr& leftmost(){
        return header->left;
    }
    node_ptr& rightmost(){
        return header->right;
    }
    rbTree(){
        header = new rbNode();
        nil = new rbNode();
        header->color = red;
        header->left = header;
        header->right = header;
        header->parent = nil;
    }

    void left_rotate(node_ptr x){
        node_ptr y = x->right;
        x->right = y->left;
        if(y->left != nil){
            y->left->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil){
            root() = y;
        }else if(x == x->parent->left){
            x->parent->left = y;
        }else if(x == x->parent->right){
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }

    void right_rotate(node_ptr x){
        node_ptr y = x->left;
        x->left = y->right;
        if(y->right != nil){
            y->right->parent = x;
        }
        y->parent = x->parent;
        if(x->parent == nil){
            root() = y;
        }else if(x == x->parent->left){
            x->parent->left = y;
        }else if(x == x->parent->right){
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }
    void insert(int val){
        node_ptr y = header;
        node_ptr x = root();
        while(x != nil){
            y = x;
            if(val < x->val){
                x = x->left;
            }else x = x->right;
        }
        node_ptr z = new rbNode();
        z->val = val;
        z->color = red;
        z->right = z->left = nil;
        z->parent = y;
        if(y == header || x!= nil || val < y->val){ //x != nil ? 
            left(y) = z;
            if(y == header){
                root() = z;
                rightmost() = z;
            }else if(y == leftmost()){
                leftmost() = z;
            }
        }else {
            right(y) = z;
            if(y == rightmost()){
                rightmost() = z;
            }
        }
        insert_fixup(z);
    }

    void insert_fixup(node_ptr z){
        while(z != root() && z->parent->color == red){
            if(z->parent == z->parent->parent->left){
                node_ptr y = z->parent->parent->right;
                if(y->color == red){
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }else {
                    if(z == z->parent->right){
                        z = z->parent;
                        left_rotate(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    right_rotate(z->parent->parent);
                }
            }else{
                node_ptr y = z->parent->parent->left;
                if(y->color == red){
                    z->parent->color = black;
                    y->color = black;
                    z->parent->parent->color = red;
                    z = z->parent->parent;
                }else{
                    if(z == z->parent->left){
                        z = z->parent;
                        right_rotate(z);
                    }
                    z->parent->color = black;
                    z->parent->parent->color = red;
                    left_rotate(z->parent->parent);
                }
            }
        }
        root()->color = black;
    }
    node_ptr find(int val){
        node_ptr cur = root();
        while(cur != nil){
            if(val == cur->val){
                return cur;
            }
            if(val < cur->val){
                cur = cur->left;
            }else{
                cur = cur->right;
            }
        }
        return cur;
    }
    void transplant(node_ptr u, node_ptr v){
        if(u == root()){
            root() = v;
        }else if(u == u->parent->right){
            u->parent->right = v;
        }else {
            u->parent->left = v;
        }
        v->parent = u->parent;
    }
    node_ptr mininum(node_ptr cur){
       while(cur->left != nil) cur = cur->left;
       return cur;
   }
    node_ptr maxinum(node_ptr cur){
       while(cur->right != nil) cur = cur->right;
       return cur;
   }
    void remove(int val){
        node_ptr temp = find(val);
        printf("find %d\n", temp->val);
        if(temp == nil) return;
        node_ptr z = temp;
        node_ptr y = z, x;
        bool originalColor = y->color;
        if(z->left ==nil){
            x = z->right;
            transplant(z, z->right);
        }else if(z->right == nil){
            x = z->left;
            transplant(z, z->left);
        }else{
            y = mininum(z->right);
            originalColor = y->color;
            x = y->right;
            if(y->parent == z){
                x->parent = y;
            }else{
                transplant(y, y->right);
                y->right = z->right;
                y->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->color = z->color;
        }
        if(originalColor == black){
            remove_fix(x);
        }
    }
    void remove_fix(node_ptr x){
        while(x != root() && x->color == black){
            if(x == x->parent->left){
                node_ptr w = x->parent->right;
                if(w->color == red){
                    w->color = black;
                    x->parent->color = red;
                    left_rotate(x->parent);
                    w = x->parent->right;
                }
                if(w->left->color == black && w->right->color == black){
                    w->color = red;
                    x = x->parent;
                }else {
                    if(w->right->color == black){
                        w->left->color = black;
                        w->color = red;
                        right_rotate(w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->right->color = black;
                    left_rotate(x->parent);
                    x = root();
                }
            }else{
                node_ptr w = x->parent->left;
                if(w->color == red){
                    w->color = black;
                    x->parent->color = red;
                    right_rotate(x->parent);
                    w = x->parent->left;
                }
                if(w->right->color == black && w->left->color == black){
                    w->color = red;
                    x = x->parent;
                }else {
                    if(w->left->color == black){
                        w->right->color = black;
                        w->color = red;
                        left_rotate(w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = black;
                    w->left->color = black;
                    right_rotate(x->parent);
                    x = root();
                }
            }
        }
        x->color = black;
    }
    void print(node_ptr it){
        if(it == nil) {
            printf("#\n");
            return ;
        }
        printf("val = %d  color = %s\n", it->val, it->color == red ? "red" : "black");
        print(it->left);
        print(it->right);
    }

};
