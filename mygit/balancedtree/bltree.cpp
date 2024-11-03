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
    //获取平衡因子
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
    
    //更新每个节点的高度的函数，这是一种思路，然鹅其实每次操作只影响与之相关的节点，而与之无关的不必要去更新
    //所以我们可以在每个对其进行变动的同时改变相关的节点高度即可，这样可以优化效率
    //故如果能递归尽量递归完成，以下这个updateh函数只在实在没办法在递归过程中update时就在最后调用一次
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
    //更新一个节点的高度
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
    //左旋（先改变各种箭头的指向，最后将指向根节点的指针指向进行改变）
    void lrotate(node*& subroot){
        //先存下要用到的三个节点（原来的根节点，根节点的右节点，右节点的左节点（因为右节点的左指针指向根节点所以原来的左指针变为原根节点的右节点））
        node* rone=subroot->m_r;
        node* rlone=subroot->m_r->m_l;
        //原根节点右节点指向原右节点的左节点
        subroot->m_r=rlone;
        //原右节点新左节点为原根节点
        rone->m_l=subroot;
        //更新高度（只有地位互换的俩节点高度发生了变化）
        updateNodeH(subroot);
        updateNodeH(rone);
        //将原右节点提升为根节点
        subroot=rone;   
    }

    //右旋（同左旋）
    void rrotate(node*& subroot){
        node* lone=subroot->m_l;
        node* lrone=subroot->m_l->m_r;
        lone->m_r=subroot;
        subroot->m_l=lrone;
        updateNodeH(subroot);
        updateNodeH(lone);
        subroot=lone;
    }
    //这里我想到了两种方法：
    //1.递归的实现插入，因为平衡二叉树的每一个子树都是平衡二叉树，而递归函数体内部势必每个子树都要执行一次getbalance(subroot)的判断，但是更新高度简单，在递归返回过程自然的体现路径
    //2.循环的实现插入，这种只要在最后对整体判断一次getbalance(root),但是更新高度过程相对比较麻烦，或许要用前面废弃的updateh函数(其路径不好搞，要自底下向上更新)
    //插入值（递归的找到最后的叶子节点进行插入后,，更新高度,判断是否平衡进行左右旋）
    void insert(node*& subroot,int val){
        //插入操作
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
       //更新高度（由于插入操作是递归完成的，递归返回的过程中就会对路径上的每个节点的高度进行更新）
        updateNodeH(subroot);
        if(getbalance(subroot)>1){
            //LL型
            if(val<subroot->m_val){
                rrotate(subroot);
            }
            //LR型
            else{
                lrotate(subroot->m_l);
                rrotate(subroot);
            }
        }
        else if(getbalance(subroot)<-1){
            //RR型
            if(val>subroot->m_val){
                lrotate(subroot);
            }
            //RL型
            else{
                rrotate(subroot->m_l);
                lrotate(subroot);
            }
        }
    }
    //重载一个方便使用
    void insert(int val){
        insert(root,val);
    }

    //删除元素
    void delval(node*& subroot,node* parent,int val){
        //找到了删除元素
        if(subroot->m_val==val){
            //叶子节点直接删除
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
            //不是叶子就让与他最接近的叶子节点换掉它，之后删叶子节点
            else {
                //右子树的最左
                if(subroot->m_l==NULL){
                    node* current=subroot->m_r;
                    while(current->m_l){
                        current=current->m_l;
                    }
                    //复制current(与删除节点最接近的节点)到subroot,再删除current
                    subroot->m_val=current->m_val;
                    delval(subroot->m_r,subroot,current->m_val);
                }
                //左子树的最右
                else{
                    node* current=subroot->m_l;
                    while(current->m_r){
                        current=current->m_r;
                    }
                    //复制current(与删除节点最接近的节点)到subroot,再删除current
                    subroot->m_val=current->m_val;
                    delval(subroot->m_l,subroot,subroot->m_val);
                }
                
            }
        }
        //没找到
        //val小于当前节点向左找
        else if(subroot->m_val>val){
            //真没找到
            if(subroot->m_l==NULL){
                cout<<"there is no such value here"<<endl;
                return;
            }
            else{
                delval(subroot->m_l,subroot,val);
            }
        }
        //val大于当前节点向右找
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
        //检查一次是否平衡
        //to be resolved:这里处理失衡类型判断不同于insert,不能简单复制
        if(getbalance(root)>1){
            //LL型
            if(getbalance(root->m_l)>0){
                rrotate(root);
            }
            //LR型
            else{
                lrotate(root->m_l);
                rrotate(root);
            }
        }
        else if(getbalance(root)<-1){
            //RR型
            if(getbalance(root->m_r)<0){
                lrotate(root);
            }
            //RL型
            else{
                rrotate(root->m_l);
                lrotate(root);
            }
        }
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