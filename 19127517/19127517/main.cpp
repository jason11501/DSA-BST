//
//  main.cpp
//  19127517
//
//  Created by jason on 01/07/2022.
//

#include <iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>

using namespace std;

struct NODE
{
    string key;
    NODE* left;
    NODE* right;
};

NODE* createNODE(string key)
{
    NODE* t = new NODE;
    t->key = key;
    t->right = NULL;
    t->left = NULL;
    return t;
}

template <class T>
void LNR(T pRoot)
{
    if(pRoot==NULL)
        return;
    else
    {
        LNR(pRoot->left);
        cout<<pRoot->key<<" ";
        LNR(pRoot->right);
    }
}

void NLR(NODE* pRoot)
{
    if(pRoot==NULL)
        return;
    else
    {
        cout<<pRoot->key<<" ";
        LNR(pRoot->left);
        LNR(pRoot->right);
    }
}

void LRN(NODE* pRoot)
{
    if(pRoot==NULL)
        return;
    else
    {
        LNR(pRoot->left);
        LNR(pRoot->right);
        cout<<pRoot->key<<" ";
    }
}

struct Array
{
    string* arr;
    int size;

    Array()
    {
        arr = nullptr;
        size = 0;
    }

    Array(int newSize)
    {
        size = newSize;
        arr = new string[size];
    }

    string& operator[](int index)
    {
        return arr[index];
    }
    
    ~Array()
    {
        if (arr)
            delete[] arr;
    }
};

int linearSearch(Array& a, string checking)
{
    for (int i=0; i<a.size; i++) {
        if (a[i].compare(checking)==0)
            return i;
    }
    return -1;
}

NODE* insertLevelOrder(vector<string> arr, int i, int n)
{
    NODE *root = nullptr;
    // Base case for recursion
    if (i < n)
    {
        root = createNODE(arr[i]);
         
        // insert left child
        root->left = insertLevelOrder(arr, 2 * i + 1, n);
 
        // insert right child
        root->right = insertLevelOrder(arr, 2 * i + 2, n);
    }
    return root;
}

void readFile(string filename, NODE*& t)
{
    int line1;
    ifstream f1(filename);
    if (!f1.is_open())
    {
        cout << "file is not open" << endl;
    }
    else
    {
        f1 >> line1;
        f1.get(); // Note
        string line;
        Array a(line1*2+ 1);
        int j = 0;
        for (int i=1; i<=line1; i++)
        {
            getline(f1, line, '\n');
            
            line = line.erase(0,1);
            string parent = line.substr(0,
                                        line.find(' '));

            line = line.erase(0,
                              parent.length() + 2);
            string left = line.substr(0,
                                           line.find(" "));

            line = line.erase(0,
                              left.length() + 1);
            string right = line.substr(0,
                                        line.find(')'));

            if (i==1)
            {
                a[j]= parent;
                a[2*j+1]= left;
                a[2*j+2]= right;
            }
            else
            {
                a[2*linearSearch(a, parent)+1]= left;
                a[2*linearSearch(a, parent)+2] = right;
            }
            j++;

        }

        vector<string> v;
        for (int i=0; i<line1*2+1; i++) {
            v.push_back(a[i]);

        }

//        v= { "1", "2", "3", "4", "5", "6", "6", "6", "6" };
//        t=insertLevelOrder(v, 0, 9);
        t=insertLevelOrder(v, 0, line1*2+1);


    }

    f1.close();
}

void del(NODE*& t, NODE*& q)
{
    if (t->right)
        del(t->right,q);
    else
    {
        q->key = t->key;
        q = t;
        t = t->left;
    }
}

void removeSearch(NODE*& t, string x)
{
    if (t == NULL)
        return;
    else
    {
        if (t->key < x)
            removeSearch(t->right, x);
        else
        {
            if (t->key > x)
                removeSearch(t->left, x);
            else
            {
                NODE* q = t;
                if (t->left == NULL)
                    t = t->right;
                else
                {
                    if (t->right == NULL)
                        t = t->left;
                    else
                        del(t->left, q);
                }
                delete q;
            }
        }
    }
}

void removeAll(NODE*& t)
{
    while (t)
        removeSearch(t, t->key);
}

struct Student{
    string id;
    string name;
    string birth;
    bool status;
};

struct BSTNode {
    Student key;
    BSTNode* left, * right;
    BSTNode(Student val)
    {
        left = nullptr;
        right = nullptr;
        key = val;
    }
    
};

bool operator<(Student first, Student second){
    return first.id < second.id;
}

bool operator>(Student first, Student second){
    return first.id > second.id;
}

Student Input()
{
    Student e;
    cout << "Nhap ten hoc sinh: ";
    getline(cin, e.name);
    cout << "ID hoc sinh: ";
    cin >> e.id;
    cin.ignore();
    cout << "birth: ";
    getline(cin, e.birth);
    cout << "Nhap status: ";
    cin >> e.status;
    cin.ignore();

    return e;
}

BSTNode* InsertByID(BSTNode*& root, Student key)
{
    if (root)
    {
        if (key < root->key)
            root->left = InsertByID(root->left, key);
        else if (key > root->key)
            root->right = InsertByID(root->right, key);

        return root;
    }
    return new BSTNode(key);
}

bool operator<<(Student first, Student second){
    return first.name < second.name;
}

bool operator>>(Student first, Student second){
    return first.name > second.name;
}

BSTNode* InsertByName(BSTNode*& root, Student key)
{
    if (root)
    {
        if (key << root->key)
            root->left = InsertByName(root->left, key);
        else if (key >> root->key)
            root->right = InsertByName(root->right, key);

        return root;
    }
    return new BSTNode(key);
}

BSTNode* InsertByStatus(BSTNode*& root, Student key)
{
    if (root)
    {
        if (root->key.status > key.status)
            root->left = InsertByStatus(root->left, key);
        else if (root->key.status < key.status)
            root->right = InsertByStatus(root->right, key);
        else
        {
            if (root->right)
                root->right = InsertByStatus(root->right, key);
            else if (root->left)
                root->left = InsertByStatus(root->left, key);
        }


        return root;
    }
    return new BSTNode(key);
}

void BuildTree(BSTNode* &root, int n)
{
    cout<< "Input Student from keyboard\n";
    for (int i = 0; i < n; i++)
    {
        root = InsertByID(root, Input());
    }
}

BSTNode* searchIDAndUpdate(BSTNode* &t, string id)
{
    if (t == NULL)
        return NULL;
    if (t->key.id == id)
    {
        cout<<"Found Student ID. Updating...\n";
        t->key = Input();
        return t;
    }
    else
        if (t->key.id > id)
            return searchIDAndUpdate(t->left, id);
        else
            return searchIDAndUpdate(t->right, id);
}

ostream& operator<<(ostream& out, Student e)
{
    out << e.name << ", " << e.id << ", " << e.birth << ", " << e.status << '\n';
    return out;
}

void LNRListAllGraduates(BSTNode* pRoot)
{
    if(pRoot==NULL)
        return;

    else
    {
        LNRListAllGraduates(pRoot->left);
        if (pRoot->key.status == 1)
        {
            cout<<pRoot->key<<"\n";
        }
        LNRListAllGraduates(pRoot->right);
    }
}

BSTNode* FindSub(BSTNode* node)
{
    while (node && node->right)
        node = node->right;
    return node;
}

BSTNode* Delete(BSTNode* root, string val, bool& del)
{
    if (root)
    {
        //The node need deleting
        if (root->key.id == val || root->key.status == stoi(val))
        {
            del = true;
            //Not have any children
            if (!root->left && !root->right)
            {
                delete root;
                root = nullptr;
            }
            else
            {
                if (root->left && root->right) //2 children
                {
                    BSTNode* sub = FindSub(root);
                    string temp = sub->key.id;
                    if (sub)
                    {
                        //Delete the sub
                        root = Delete(root, temp, del);
                        root->key.id = temp;
                    }
                }
                else if (root->left) //pLeft child
                {
                    BSTNode* temp = root;
                    root = root->left;
                    delete temp;
                }
                else //pRight child
                {
                    BSTNode* temp = root;
                    root = root->right;
                    delete temp;
                }
            }
        }
        else if (root->key.id < val || root->key.status < stoi(val))
            root->right = Delete(root->right, val, del);
        else
            root->left = Delete(root->left, val, del);
    }

    return root;
}

bool DeleteByID(BSTNode*& root, string id)
{
    bool del = false;
    root = Delete(root, id, del);
    return del;
}

void LNRCheckGraduates(BSTNode* pRoot, bool &flag)
{
    if(pRoot==NULL)
        return;
    
    else
    {
        LNRCheckGraduates(pRoot->left, flag);
        if (pRoot->key.status == 1)
        {
            flag = true;
        }
        LNRCheckGraduates(pRoot->right, flag);

    }
}

bool DeleteAllGraduates(BSTNode*& root)
{
    bool del = false;
    bool check;
    LNRCheckGraduates(root, check);
    while (check)
    {
        root = Delete(root, "1", del);
        check = false;
        
        LNRCheckGraduates(root, check);
        if (check == true)
            continue;
        else
            break;
            
    }
    return del;
}

void DeleteTree(BSTNode* root)
{
    if (root)
    {
        DeleteTree(root->left);
        DeleteTree(root->right);
        delete root;
    }
}

int main() {
//6.1
    NODE* t;
    readFile("/Users/jason/Downloads/DSA-BST-main/19127517/19127517/input.txt", t);
    cout<<"6.1\nNLR"<<endl;
    NLR(t);
    cout<<"\nLNR"<<endl;
    LNR(t);
    cout<<"\nLRN"<<endl;
    LRN(t);
    removeAll(t);
    
//6.2
    cout<<"\n\n6.2\n";
    BSTNode* rootByID = NULL;
    BSTNode* rootByName = NULL;
    BSTNode* rootByStatus = NULL;
    //load tree from file
    fstream in("/Users/jason/Downloads/DSA-BST-main/19127517/19127517/student.data");
    int num;
    if (in)
    {
        in >> num;
        in.get();

        for (int i=0; i<num; i++) {
            Student e;
            getline(in, e.id, '\n');
            getline(in, e.name, '\n');
            getline(in, e.birth, '\n');
            string status;
            getline(in, status, '\n');
            e.status = stoi(status);
            
            rootByID = InsertByID(rootByID, e);
            rootByName = InsertByName(rootByName, e);
            rootByStatus = InsertByStatus(rootByStatus, e);
        }
    }
    in.close();
    BuildTree(rootByID, num); //create a new student info and insert
    searchIDAndUpdate(rootByID, "1212346"); // Find an student by his/hers unique code, and support updating
    LNR(rootByName); // lexicographic order of their names
    LNRListAllGraduates(rootByID); //List all graduated students.
    DeleteByID(rootByID, "1212346"); // Delete an student given by its code.
    DeleteAllGraduates(rootByStatus); //Delete all graduates
    
    DeleteTree(rootByID);
    DeleteTree(rootByName);
    DeleteTree(rootByStatus);
    return 0;
}
