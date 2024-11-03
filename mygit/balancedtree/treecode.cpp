#include<iostream>
using namespace std;
#include<queue>
class tree;
class node{
public:
    node* m_l;
    node* m_r;
    int m_val;
    node(int value):m_l(NULL),m_r(NULL),m_val(value){};
    ~node(){
        delete m_l;
        delete m_r;
        m_l=NULL;
        m_r=NULL;
    }
};

class tree{
public:
    node* root;
    tree():root(NULL){};
    tree(int val):root(new node(val)){};
    ~tree(){
        delete root;
        root=NULL;
    }
    //从subroot起插入值,若为空对subroot操作，故传入一级指针的引用
    void insert(node*& subroot,int val){
        if(subroot==NULL){
            subroot=new node(val);
            return;
        }
        if(val==subroot->m_val){
            cout<<"This value has been there"<<endl;
            return;
        }
        else if(val>subroot->m_val){
            if(subroot->m_r==NULL){
                subroot->m_r=new node(val);
            }
            else{
                insert(subroot->m_r,val);
            }
        }
        else{
            if(subroot->m_l==NULL){
                subroot->m_l=new node(val);
            }
            else{
                insert(subroot->m_l,val);
            }
        }
    }
    //重载一个方便使用
    void insert(int val){
        insert(root,val);
    }
    //从subroot起删除值，有可能删掉subroot，为避免值传递要用二级指针/一级指针的引用
    //由于删除节点后要对父节点操作，传入一个父节点指针
    void delval(node*& subroot,node* parent,int val){
        if(val==subroot->m_val){
            if(subroot->m_r!=NULL){
                node* cur=subroot->m_r;
                node* p_cur=subroot;
                //右节点的最左叶子节点
                while(cur->m_l){
                    cur=cur->m_l;
                }
                //复制值后删掉这个叶子节点
                subroot->m_val=cur->m_val;
                delval(subroot->m_r,subroot,cur->m_val);
            }
            else if(subroot->m_l!=NULL){
                node* cur=subroot->m_l;
                //左节点的最右叶子节点
                while(cur->m_r){
                    cur=cur->m_r;
                }
                //复制值后删掉这个叶子节点
                subroot->m_val=cur->m_val;
                //递归的删除这个叶子节点
                delval(subroot->m_r,subroot,cur->m_val);
            }
            //为叶子节点
            else{
                delete subroot;
                subroot=NULL;
                if(parent!=NULL){
                    if(parent->m_val>val){
                        parent->m_l=NULL;
                    }
                    else{
                        parent->m_r=NULL;
                    }
                }
            }
        }
        else if(val>subroot->m_val){
            delval(subroot->m_r,subroot,val);
        }
        else{
            delval(subroot->m_l,subroot,val);
        }
    }   
    void delval(int val){
        delval(root,NULL,val);
    }
    //先序遍历树
    void fs(node* subroot){
        cout<<subroot->m_val<<" ";
        if(subroot->m_l!=NULL){
            fs(subroot->m_l);
        }
        if(subroot->m_r!=NULL){
            fs(subroot->m_r);
        }
    }
    void fs(){
        fs(root);
    }
    //层次遍历
    void levelprint(node* subroot){
        queue<node*> que;
        que.push(subroot);
        while(!que.empty()){
            node* tem=que.front();
            cout<<tem->m_val<<" ";
            que.pop();
            if(tem->m_l){
                que.push(tem->m_l);
            }
            if(tem->m_r){
                que.push(tem->m_r);
            }
        }
    }
};



int main(){
    tree t;
    t.insert(0);
    t.insert(-3);
    t.insert(1);
    t.insert(6);
    t.insert(0);
    t.insert(-99);
    t.insert(-1);
    t.insert(-2);
    t.delval(-3);
    t.delval(0);
    t.fs();
}