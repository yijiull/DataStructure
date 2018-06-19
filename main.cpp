#include <bits/stdc++.h>
#include <memory>
#include "rbTree.h"
using namespace std;
class A{

};
int main(){
    rbTree tr;
    int x;
    
    char op;
    while(cin>>op>>x){
        if(op == 'i'){
            tr.insert(x);
        }else{
            tr.remove(x);
        }
            tr.print(tr.root());
        printf("----------------------\n");
    }
}