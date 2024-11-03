//����һ�´�������Ϊÿ��node��������һ��tree�����ǲ��Ե�
#include<iostream>
using namespace std;
class tree;
class node{
public:
    tree* m_l;
    tree* m_r;
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
    //����ֵ
    void insert(int val){
        if(root=NULL){
            root=new node(val);
            return;
        }
        if(val==root->m_val){
            cout<<"This value has been there"<<endl;
            return;
        }
        else{
            if(val>root->m_val){
                if(root->m_r==NULL){
                    tree* tem=new tree(val);
                    root->m_r=tem;
                }
                else{
                    root->m_r->insert(val);
                }
            }
            else{
                if(root->m_l==NULL){
                    tree* tem=new tree(val);
                    root->m_l=tem;
                }
                else{
                    root->m_l->insert(val);
                }
            }
        }
    }

    //ɾ��ֵ
    void delval(int val){
        if(val==root->m_val){
            if(root->m_r!=NULL){
                tree* cur=root->m_r;
                //�ҽڵ������Ҷ�ӽڵ�
                while(cur->root->m_l){
                    cur=cur->root->m_l;
                }
                //����ֵ��ɾ�����Ҷ�ӽڵ�
                root->m_val=cur->root->m_val;
                delete cur;
                cur=NULL;
            }
            else if(root->m_l!=NULL){
                tree* cur=root->m_l;
                //��ڵ������Ҷ�ӽڵ�
                while(cur->root->m_r){
                    cur=cur->root->m_r;
                }
                //����ֵ��ɾ�����Ҷ�ӽڵ�
                root->m_val=cur->root->m_val;
                delete cur;
                cur=NULL;
            }
            //ΪҶ�ӽڵ�
            else{
                delete root;
                root=NULL;
            }
        }
        else if(val>root->m_val){
            root->m_r->delval(val);
        }
        else{
            root->m_l->delval(val);
        }
    }   
    //���������
    void fs(){
        cout<<root->m_val<<" ";
        if(root->m_l!=NULL){
            root->m_l->fs();
        }
        if(root->m_r!=NULL){
            root->m_r->fs();
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
    t.fs();
}