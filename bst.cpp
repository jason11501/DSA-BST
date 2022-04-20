#include <iostream>
#include <queue>
using namespace std;
////THanh 19127549
struct NODE
{
    int key;
    NODE *p_left;
    NODE *p_right;
};
NODE* createNode(int data)
{
    NODE*p=new NODE;
    p->key=data;
    p->p_left=NULL;
    p->p_right=NULL;
    return p;
}
void LNR(NODE*&pRoot)
{
    if(pRoot==NULL)
        return;
    else{
        LNR(pRoot->p_left);
        cout<<pRoot->key<<" ";
        LNR(pRoot->p_right);
    }
}
void Insert(NODE*&pRoot,int data)
{
  
    if(pRoot==NULL)
    {
      pRoot=createNode(data);
    }
    else if(pRoot->key>data)
    {
        Insert(pRoot->p_left,data);
    }
    else if(pRoot->key<data)
    {
        Insert(pRoot->p_right,data);
    }
}

/**/
//Ho Dang Khoa - 443
NODE* CreateTree(int a[], int n){
    NODE * root = createNode(a[0]);
    for(int i = 1; i < n; i++){
        Insert(root, a[i]);
    }
    return root;
}

//Le Minh Huy - 19127157
void LevelOrder(NODE* root) {
    if (!root)
        return;
    queue<NODE*> q;
    q.push(root);
    
    while (!q.empty()) {
        NODE* fr = q.front();
        cout << fr->key << " ";
        if (fr->p_left)
            q.push(fr->p_left);
        if (fr->p_right)
            q.push(fr->p_right);
        q.pop();
    }
}

//Nguyen Huu Hoang An - 19127325
NODE* searchNode(NODE* pRoot,int data)
{
    if(pRoot == NULL)
    {
        return NULL;
    }
    if(pRoot->key == data)
    {
        return pRoot;
    }
    else
    {
        if(pRoot->key > data)
            return searchNode(pRoot->p_left,data);
        else return searchNode(pRoot->p_right,data);
    }
    return NULL;
}

//Ho Thien Phuoc 19127517

void deleteNode(NODE*&pRoot, NODE*&q){
    if(pRoot->p_right)
        deleteNode(pRoot->p_right, q);
    else{
        q->key = pRoot->key;
        q = pRoot;
        pRoot = pRoot->p_left;
    }
}

void Remove(NODE *&pRoot, int x){
    if (pRoot == NULL) return;
    if (pRoot->key > x)
        Remove(pRoot->p_left, x);
    else{
        if(pRoot->key < x)
            Remove(pRoot->p_right, x);
        else{
            NODE *q = pRoot;
            if (q->p_right == NULL)
                pRoot = q->p_left;
            else
                if (q->p_left == NULL)
                    pRoot = q->p_left;
                else
                    deleteNode(pRoot->p_left, q);//predecessor
                //delete(pRoot->p_right, q);//successor
            delete q;
        }
     }
}

//Thanh 19127549
int countLess(NODE* pRoot, int x)
   {
    int count=0;
    if(pRoot==NULL)
       return 0;
    else if(pRoot->key<x)
      {
        count++;
        count+=countLess(pRoot->p_left,x);
        count+=countLess(pRoot->p_right,x);
    }
    else{
        count+=countLess(pRoot->p_left,x);
    }
    return count;
}
// Vo Dinh Phuc-515
int max(int a, int b)
{
    return (a>b)?a:b;
}
int Height(NODE* pRoot)
{
    if(pRoot==NULL)
        return 0;
    int h1=Height(pRoot->p_left);
    int h2=Height(pRoot->p_right);
    return max(h1,h2)+1;
}
    
// Tran Le Quoc Bao - 340
int countNode(NODE* pRoot)
{
    if (pRoot == NULL)
        return 0;
    
    return 1 + countNode(pRoot->p_left) + countNode(pRoot->p_right);
}
    
// Phan Minh Hieu -141
int levelNode(NODE* root,NODE*p){
    if(root==nullptr)
        return -1;
    int count=0;
    bool flag=0;
    while(root){
        if(root->key == p->key){
            flag=1;
            break;
        }
        ++count;
        root= (root->key <p->key)? root->p_right : root->p_left;
    }
    return (flag) ? count : -1;
 }
// Le Hoang Anh - 19127329
int sumNode(NODE* root) {
    if (root == NULL)
        return 0;
    
    return root->key + sumNode(root->p_left) + sumNode(root->p_right);
}
    
//Nguyen Nhat Cuong - 19127346
int heightNode(NODE* pRoot, int value) {
    if (pRoot == NULL)
         return -1;
                  
    if (pRoot->key < value)
        return heightNode(pRoot->p_right, value);
    else if (pRoot->key > value)
        return heightNode(pRoot->p_left, value);
    else
        return Height(pRoot);
}
//Le Thanh Dat - 19127354
int countLeaf(NODE* pRoot) {
    if(pRoot == NULL)
        return 0;
     else if (pRoot->p_left == NULL && pRoot->p_right == NULL)
        return 1;
    else
        return countLeaf(pRoot->p_left) + countLeaf(pRoot->p_right);
} 

int findMin(Node *root)
{
    if(root==NULL)
        return 0;
    int min = root->key;
    int lmin=findMin(root->p_left);
    int rmin =findMin(root->p_riht);
    
    if(lmin < min)
        min =lmin;
    if(rmin < min)
        min =rmin;
    return min;
}

int findMax(Node *root)
{
    if(root==NULL)
        return 0;
    int max = root->key;
    int lmax=findMax(root->p_left);
    int rmax =findMax(root->p_riht);
    
    if(lmax > max)
        max =lmax;
    if(rmax > max)
        max =rmax;
    return max;
}


// Nguyen Thai Tien 19127575
bool isBst(NODE *root)
{
    if(root==NULL)
        return true;
    if(root->p_left && findMax(root->p_left) > root->key)
        return false;
    if(root->p_right && findMin(root-p_right) < root->key)
        return fasle;
    if(!isBst(root->p_right) || !isBst(root->p_left))
        return false;
    return true;
        
}
//Vo Tran Quang Thong -19127567
bool isFullBST(NODE*pRoot){
    if(pRoot==NULL)
        return true;
    
    if(pRoot->p_left==NULL && pRoot->p_right==NULL)
        return true;
    
    if((pRoot->p_left) && (pRoot->p_right))
        return(isFullBST(pRoot->p_left) && isFullBST(pRoot->p_right));
    return false;
}
int main()
{
    int a[] = {15, 2, 20, 1, 3, 16, 31, 68, 40, 75};
    int n =  sizeof(a)/sizeof(a[0]);
    NODE * root = CreateTree(a, n);
    //LNR(root);
    cout << endl;
    //LevelOrder(root);
    //NODE* p_ = searchNode(root, 68);
    //cout << endl << p_->p_left->key;
    //Remove(root, 20);
    //LevelOrder(root);
    cout << isFullBST(root);
}
