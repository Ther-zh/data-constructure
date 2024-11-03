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
    //��subroot�����ֵ,��Ϊ�ն�subroot�������ʴ���һ��ָ�������
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
    //����һ������ʹ��
    void insert(int val){
        insert(root,val);
    }
    //��subroot��ɾ��ֵ���п���ɾ��subroot��Ϊ����ֵ����Ҫ�ö���ָ��/һ��ָ�������
    //����ɾ���ڵ��Ҫ�Ը��ڵ����������һ�����ڵ�ָ��
    void delval(node*& subroot,node* parent,int val){
        if(val==subroot->m_val){
            if(subroot->m_r!=NULL){
                node* cur=subroot->m_r;
                node* p_cur=subroot;
                //�ҽڵ������Ҷ�ӽڵ�
                while(cur->m_l){
                    cur=cur->m_l;
                }
                //����ֵ��ɾ�����Ҷ�ӽڵ�
                subroot->m_val=cur->m_val;
                delval(subroot->m_r,subroot,cur->m_val);
            }
            else if(subroot->m_l!=NULL){
                node* cur=subroot->m_l;
                //��ڵ������Ҷ�ӽڵ�
                while(cur->m_r){
                    cur=cur->m_r;
                }
                //����ֵ��ɾ�����Ҷ�ӽڵ�
                subroot->m_val=cur->m_val;
                //�ݹ��ɾ�����Ҷ�ӽڵ�
                delval(subroot->m_r,subroot,cur->m_val);
            }
            //ΪҶ�ӽڵ�
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
    //���������
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
    //��α���
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