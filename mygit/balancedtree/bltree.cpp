#include<iostream>
#include<queue>
using namespace std;
class node{
public:
    int m_val;
    node* m_l;
    node* m_r;
    int m_h;
    node(int val):m_val(val),m_l(NULL),m_r(NULL),m_h(0){}
    ~node(){
        if (m_l!=NULL)delete m_l;
        if(m_r!=NULL)delete m_r;
        m_l=NULL;
        m_r=NULL;
    }
};

class bltree{
public:
    node* root;
    bltree():root(NULL){}
    ~bltree(){
        if(root!=NULL)delete root;
        root=NULL;
    }
    //��ȡƽ������
    int getbalance(node* subroot){
        if(subroot->m_l==NULL&&subroot->m_r==NULL){
            return 0;
        }
        else if(subroot->m_l==NULL){
            return -subroot->m_r->m_h-1;
        }
        else if(subroot->m_r==NULL){
            return subroot->m_l->m_h+1;
        }
        else {
            return subroot->m_l->m_h-subroot->m_r->m_h;
        }
    }
    
    //����ÿ���ڵ�ĸ߶ȵĺ���������һ��˼·��Ȼ����ʵÿ�β���ֻӰ����֮��صĽڵ㣬����֮�޹صĲ���Ҫȥ����
    //�������ǿ�����ÿ��������б䶯��ͬʱ�ı���صĽڵ�߶ȼ��ɣ����������Ż�Ч��
    //������ܵݹ龡���ݹ���ɣ��������updateh����ֻ��ʵ��û�취�ڵݹ������updateʱ����������һ��
    void updateh(node* subroot){
        if(subroot==NULL)return;
        if(subroot->m_l==NULL&&subroot->m_r==NULL)return;
        if(subroot->m_l!=NULL){
            updateh(subroot->m_l);
        }
        if(subroot->m_r!=NULL){
            updateh(subroot->m_r);
        }
        updateNodeH(subroot);
    }
    //����һ���ڵ�ĸ߶�
    void updateNodeH(node* subroot){
        if(subroot->m_l==NULL&&subroot->m_r==NULL){
            subroot->m_h=0;
        }
        else if(subroot->m_l==NULL){
            subroot->m_h=subroot->m_r->m_h+1;
        }
        else if(subroot->m_r==NULL){
            subroot->m_h=subroot->m_l->m_h+1;
        }
        else {
            subroot->m_h=subroot->m_l->m_h > subroot->m_r->m_h ? subroot->m_l->m_h+1 : subroot->m_r->m_h+1;
        }
    }
    //�������ȸı���ּ�ͷ��ָ�����ָ����ڵ��ָ��ָ����иı䣩
    void lrotate(node*& subroot){
        //�ȴ���Ҫ�õ��������ڵ㣨ԭ���ĸ��ڵ㣬���ڵ���ҽڵ㣬�ҽڵ����ڵ㣨��Ϊ�ҽڵ����ָ��ָ����ڵ�����ԭ������ָ���Ϊԭ���ڵ���ҽڵ㣩��
        node* rone=subroot->m_r;
        node* rlone=subroot->m_r->m_l;
        //ԭ���ڵ��ҽڵ�ָ��ԭ�ҽڵ����ڵ�
        subroot->m_r=rlone;
        //ԭ�ҽڵ�����ڵ�Ϊԭ���ڵ�
        rone->m_l=subroot;
        //���¸߶ȣ�ֻ�е�λ���������ڵ�߶ȷ����˱仯��
        updateNodeH(subroot);
        updateNodeH(rone);
        //��ԭ�ҽڵ�����Ϊ���ڵ�
        subroot=rone;   
    }

    //������ͬ������
    void rrotate(node*& subroot){
        node* lone=subroot->m_l;
        node* lrone=subroot->m_l->m_r;
        lone->m_r=subroot;
        subroot->m_l=lrone;
        updateNodeH(subroot);
        updateNodeH(lone);
        subroot=lone;
    }
    //�������뵽�����ַ�����
    //1.�ݹ��ʵ�ֲ��룬��Ϊƽ���������ÿһ����������ƽ������������ݹ麯�����ڲ��Ʊ�ÿ��������Ҫִ��һ��getbalance(subroot)���жϣ����Ǹ��¸߶ȼ򵥣��ڵݹ鷵�ع�����Ȼ������·��
    //2.ѭ����ʵ�ֲ��룬����ֻҪ�����������ж�һ��getbalance(root),���Ǹ��¸߶ȹ�����ԱȽ��鷳������Ҫ��ǰ�������updateh����(��·�����ø㣬Ҫ�Ե������ϸ���)
    //����ֵ���ݹ���ҵ�����Ҷ�ӽڵ���в����,�����¸߶�,�ж��Ƿ�ƽ�������������
    void insert(node*& subroot,int val){
        //�������
        if(subroot==NULL){
            subroot=new node(val);
            return;
        }
        if(val==subroot->m_val){
            cout<<"This value has been here"<<endl;
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
       //���¸߶ȣ����ڲ�������ǵݹ���ɵģ��ݹ鷵�صĹ����оͻ��·���ϵ�ÿ���ڵ�ĸ߶Ƚ��и��£�
        updateNodeH(subroot);
        if(getbalance(subroot)>1){
            //LL��
            if(val<subroot->m_val){
                rrotate(subroot);
            }
            //LR��
            else{
                lrotate(subroot->m_l);
                rrotate(subroot);
            }
        }
        else if(getbalance(subroot)<-1){
            //RR��
            if(val>subroot->m_val){
                lrotate(subroot);
            }
            //RL��
            else{
                rrotate(subroot->m_l);
                lrotate(subroot);
            }
        }
    }
    //����һ������ʹ��
    void insert(int val){
        insert(root,val);
    }

    //ɾ��Ԫ��
    void delval(node*& subroot,node* parent,int val){
        //�ҵ���ɾ��Ԫ��
        if(subroot->m_val==val){
            //Ҷ�ӽڵ�ֱ��ɾ��
            if(subroot->m_l==NULL && subroot->m_r==NULL){
                delete subroot;
                subroot=NULL;
                if(parent){
                    if(parent->m_val>val){
                        parent->m_l=NULL;
                    }
                    else{
                        parent->m_r=NULL;
                    }
                }
            }
            //����Ҷ�Ӿ���������ӽ���Ҷ�ӽڵ㻻������֮��ɾҶ�ӽڵ�
            else {
                //������������
                if(subroot->m_l==NULL){
                    node* current=subroot->m_r;
                    while(current->m_l){
                        current=current->m_l;
                    }
                    //����current(��ɾ���ڵ���ӽ��Ľڵ�)��subroot,��ɾ��current
                    subroot->m_val=current->m_val;
                    delval(subroot->m_r,subroot,current->m_val);
                }
                //������������
                else{
                    node* current=subroot->m_l;
                    while(current->m_r){
                        current=current->m_r;
                    }
                    //����current(��ɾ���ڵ���ӽ��Ľڵ�)��subroot,��ɾ��current
                    subroot->m_val=current->m_val;
                    delval(subroot->m_l,subroot,subroot->m_val);
                }
                
            }
        }
        //û�ҵ�
        //valС�ڵ�ǰ�ڵ�������
        else if(subroot->m_val>val){
            //��û�ҵ�
            if(subroot->m_l==NULL){
                cout<<"there is no such value here"<<endl;
                return;
            }
            else{
                delval(subroot->m_l,subroot,val);
            }
        }
        //val���ڵ�ǰ�ڵ�������
        else{
            if(subroot->m_r==NULL){
                cout<<"there is no such value here"<<endl;
                return;
            }
            else{
                delval(subroot->m_r,subroot,val);
            }
        }
        
    }
    void delval(int val){
        delval(root,NULL,val);
        updateh(root);
        //���һ���Ƿ�ƽ��
        //to be resolved:���ﴦ��ʧ�������жϲ�ͬ��insert,���ܼ򵥸���
        if(getbalance(root)>1){
            //LL��
            if(getbalance(root->m_l)>0){
                rrotate(root);
            }
            //LR��
            else{
                lrotate(root->m_l);
                rrotate(root);
            }
        }
        else if(getbalance(root)<-1){
            //RR��
            if(getbalance(root->m_r)<0){
                lrotate(root);
            }
            //RL��
            else{
                rrotate(root->m_l);
                lrotate(root);
            }
        }
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
        cout<<endl;
    }
    void levelprint(){
        levelprint(root);
    }
};

int main(){
    bltree* bl=new bltree();
    bl->insert(0);
    bl->insert(-10);
    bl->insert(6);
    bl->insert(5);
    bl->insert(15);
    bl->insert(17);
    bl->levelprint();
    bl->delval(17);
    bl->delval(15);
    bl->levelprint();
    delete bl;
}