#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<sstream>
using namespace std;

struct NODE
{
	int key;
	NODE* left;
	NODE* right;
};

NODE* createNODE(int key)
{
	NODE* t = new NODE;
	t->key = key;
	t->right = NULL;
	t->left = NULL;
	return t;
}

void LNR(NODE* t)
{
	if (t)
	{
		LNR(t->left);
		cout << t->key << " ";
		LNR(t->right);
		
	}
}

void readFile(string filename, vector<int>& tmp,int &A,int &B ,int& K)
{
	string line1;
	ifstream f1("input.txt");
	if (!f1.is_open())
	{
		cout << "file is not open" << endl;
	}
	else
	{
		getline(f1, line1, '\n');
		string token;
		istringstream iss(line1) ;
		while (getline(iss, token, ' '))
		{
			tmp.push_back(stoi(token));
		}
		f1 >> A;
		f1 >> B;
		f1 >> K;
	}

	f1.close();
}
NODE* search(NODE* t, int key)
{
	if (t == NULL)
		return NULL;
	if (t->key == key)
		return t;
	else
		if (t->key > key)
			return search(t->left, key);
		else
			return search(t->right, key);
}
void addSearch(NODE*& t, int key)
{
	if (t == NULL)
	{
		t = createNODE(key);
	}
	else
		if (t->key > key)
			addSearch(t->left, key);
		else
			if (t->key < key)
				addSearch(t->right, key);
			else
				return;
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

void removeSearch(NODE*& t,int x)
{
	if (t == NULL)
		return;
	else
		if (t->key < x)
			removeSearch(t->right, x);
		else
			if (t->key > x)
				removeSearch(t->left, x);
			else
			{
				NODE* q = t;
				if (t->left == NULL)
					t = t->right;
				else
					if (t->right == NULL)
						t = t->left;
					else
						del(t->left, q);
				delete q;
			}
}
void removeAll(NODE*& t)
{
	while (t)
	{
		removeSearch(t, t->key);
	}
}

int findBNode(NODE* t, int B)//tim ra node chia het cho B
{
	if (t == NULL)
		return 0;
	if (t->key % B == 0)
		return 1;
	else
		return findBNode(t->left, B) + findBNode(t->right, B);
}

int max(int a, int b)
{
	if (a > b)
		return a;
	else
		return b;
}

int maxK(NODE* t, int level, int K) //find max value which have 2 children in tree at level K .
{
	if (t == NULL)
		return 0;
	if (level == K)
	{
		if (t->left && t->right)
			return t->key;
		else
			return 0;
	}
	else
		return max(maxK(t->left,level+1,K), maxK(t->right,level+1,K));
}

int main()
{
	vector<int> tmp;
	int A, B, K;

	readFile("input.txt", tmp,A,B,K);
	NODE* tree=NULL;

	for (int i = 0; i < tmp.size(); i++)
	{
		addSearch(tree, tmp[i]);
	}

	cout << "cau 1 : " << endl;
	LNR(tree);

	cout << endl;
	cout << "cau 2 : " << endl;
	NODE* ANode=search(tree, A); // tim ra node co gia tri A

	if (ANode == NULL)
		cout << 0 << endl;
	else
		cout << findBNode(ANode->left, B) + findBNode(ANode->right, B) << endl;// cau 2

	cout << "cau 3 : " << endl;
	removeSearch(tree, maxK(tree, 1, K));//cau 3

	LNR(tree);

	removeAll(tree);
	return 0;
}
