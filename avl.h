#include<iostream>
using namespace std;
class AVL
{
	private:
		struct node
		{
			int data;
			string item;
		    int price;
		    node* left;
		    node* right;
		    int height;
		    int count;
		};
		node* root;
	public:
		AVL();
		node* findMin(node* t);
		node* findMax(node* t);
		node* insert(int x, string y, int z,node* t);
		void insert(int x, string y, int z);
		node* RightRotate(node* &t);
		node* LeftRotate(node* &t);
		node* RightLeftRotate(node* &t);
		node* LeftRightRotate(node* &t);
		int height(node* t);
		string srch(int key);
		int sch(int key);
		int search(int key);
		void count(int key);
        void count1(int key);
        int count2(int key);
		int s=0;//total amount
		void frequency(node *&t);
		void frequency();
		void print(node *&t);
		void print();
		void deletetree();
		void deletetree(node*& t);
		void update(int key, string new_item,int new_price);
		void delete1(int & x);
		void balance(node *&t);
		void delete_element(int &x,node*&t);
};

AVL::AVL()
{
	root = NULL;
}

//Function to find minimum
struct AVL::node* AVL::findMin(node* t)
{
	if(t == NULL)
        return NULL;
    else if(t->left == NULL)
        return t;
    else
        return findMin(t->left);
}

//Function to find maximum
struct AVL::node* AVL::findMax(node* t)
{
	if(t == NULL)
        return NULL;
    else if(t->right == NULL)
        return t;
    else
        return findMax(t->right);
}

//Function to insert a new node
struct AVL::node* AVL::insert(int x, string y, int z,node* t)
{
	if(t == NULL)
    {
        t = new node;
        t->data = x;
        t->item = y;
        t->price = z;
        t->height = 0;
        t->left = t->right = NULL;
        t->count = 1;
    }
    else if(x < t->data)
    {
        t->left = insert(x, y, z,t->left);
        if(height(t->left) - height(t->right) == 2)
        {
            if(x < t->left->data)
                t = RightRotate(t);
            else
                t = LeftRightRotate(t);
        }
    }
    else if(x > t->data)
    {
        t->right = insert(x, y, z,t->right);
        if(height(t->right) - height(t->left) == 2)
        {
            if(x > t->right->data)
                t = LeftRotate(t);
            else
                t = RightLeftRotate(t);
        }
    }
	t->height = max(height(t->left), height(t->right))+1;
    return t;
}

void AVL::insert(int x, string y, int z)
{
    root = insert(x, y, z,root);
}

//LL IMBALANCE
struct AVL::node* AVL::RightRotate(node* &t)
{
	node* u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(u->left), t->height)+1;
    return u;
}

//RR IMBALANCE
struct AVL::node* AVL::LeftRotate(node* &t)
{
	node* u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right))+1;
    u->height = max(height(t->right), t->height)+1 ;
    return u;
}

//RL IMBALANCE
struct AVL::node* AVL::RightLeftRotate(node* &t)
{
	t->right = RightRotate(t->right);
    return LeftRotate(t);
}

//LR IMBALANCE
struct AVL::node* AVL::LeftRightRotate(node* &t)
{
	t->left = LeftRotate(t->left);
    return RightRotate(t);
}

//FUNCTION TO FIND HEIGHT
int AVL::height(node *t)
{
	return (t == NULL ? -1 : t->height);
}

void AVL::delete1(int &x)
{
	delete_element(x,root);
}

//FUNCTION TO BALANCE THE TREE
void AVL::balance(node*&t)
{
	if(t!=NULL)
    {
		if(height(t->left)-height(t->right)==2)
		{
			if(height(t->left->left)>=height(t->left->right))
			{
				t=RightRotate(t);
			}
			else
			{
				t=LeftRightRotate(t);
			}
		}
		else if(height(t->right)-height(t->left)==2)
		{
			if(height(t->right->right)>=height(t->right->left))
			{
				t=LeftRotate(t);
			}
			else
			{
				t=RightLeftRotate(t);
			}
		}
		t->height=max(height(t->left),height(t->right))+1;
	}
}

//FUNCTION TO DELETE A NODE
void AVL::delete_element(int&x,node*&t)
{
	if(t!=NULL)
    {
		if(t->data>x)
		{
			delete_element(x,t->left);
		}
		else if(t->data<x)
		{
			delete_element(x,t->right);
		}
		else if(t->left!=NULL && t->right!=NULL)
		{
			node *temp;
			temp=findMin(t->right);
			t->data=temp->data;
			t->item=temp->item;
			t->price=temp->price;
			t->count=temp->count;
			delete_element(t->data,t->right);
		}
		else
		{
			node*temp=t;
			t=(t->left!=NULL)?t->left:t->right;
			delete temp;
		}
	}
	balance(t);
}

//FUNCTION TO RETURN ITEM
string AVL::srch(int key)
{
	node *t = root;
	while (t != NULL){
		if (t->data == key)
        {
			return t->item;
			break;
		}
		t = t->data < key ? t->right : t->left;
	}
}

//FUNCTION TO RETURN PRICE
int AVL::sch(int key)
{
	node *t = root;
	while (t != NULL)
	{
		if (t->data == key)
        {
			return t->price;
			break;
		}
		t = t->data < key ? t->right : t->left;
	}
}

//FUNCTION TO SEARCH A NODE
int AVL::search(int key)
{
	node *t = root;
	if(t == NULL)
    {
		return 1;
	}
	else if(t != NULL)
	{
		while (t != NULL)
		{
		    if (t->data == key)
		    {
				return 0;
		        break;
	        }
	        else if(t->data < key)
	        {
	            t  = t->right ;
	            if(t == NULL)
	            {
	            	return 1;
				}
			}
			else if(t->data > key)
			{
				t = t->left ;
				if(t == NULL)
				{
					return 1;
				}
			}
		}
	}
}

//IF PRESENT , INCREMENTING THE COUNT
void AVL::count(int key)
{
	node *t=root;
	while (t != NULL)
    {
		if (t->data == key)
		{
		    t->count++;
		    break;
		}
		t = t->data < key ? t->right : t->left;
	}
}

//FUNCTION TO DISPLAY BILL
void AVL::frequency()
{
	cout<<left<<setw(76)<<setfill('-')<<""<<endl;
	cout<<left<<setw(10)<<setfill(' ')<<"Item.Code";
    cout<<left<<setw(30)<<setfill(' ')<<"Items";
    cout<<left<<setw(12)<<setfill(' ')<<"Price";
    cout<<left<<setw(9)<<setfill(' ')<<"Quantity";
    cout<<left<<setw(15)<<setfill(' ')<<"Total Price\n";
	cout<<left<<setw(76)<<setfill('-')<<""<<endl;
	frequency(root);
}

void AVL::frequency(node *&t)
{
	if(t != NULL){
		frequency(t->left);
        cout<<left<<setw(10)<<setfill(' ')<<t->data;
        cout<<left<<setw(30)<<setfill(' ')<<t->item;
        cout<<left<<setw(12)<<setfill(' ')<<t->price;
        cout<<left<<setw(9)<<setfill(' ')<<t->count;
        cout<<left<<setw(15)<<setfill(' ')<<t->price*t->count<<endl;
		cout<<left<<setw(76)<<setfill('-')<<""<<endl;
		s+=t->price*t->count;
		frequency(t->right);
	}
}

//FUNCTION TO PRINT MENU
void AVL::print(node *&t)
{
	if (t != NULL)
    {
		print(t->left);
        cout<<left<<setw(10)<<setfill(' ')<<t->data;
        cout<<left<<setw(30)<<setfill(' ')<<t->item;
        cout<<left<<setw(12)<<setfill(' ')<<t->price<<endl;
		cout<<left<<setw(52)<<setfill('-')<<""<<endl;
		print(t->right);
	}
}

void AVL::print()
{
	cout<<left<<setw(52)<<setfill('-')<<""<<endl;
	cout<<left<<setw(10)<<setfill(' ')<<"Item.Code";
    cout<<left<<setw(30)<<setfill(' ')<<"Items";
    cout<<left<<setw(12)<<setfill(' ')<<"Price"<<endl;
	cout<<left<<setw(52)<<setfill('-')<<""<<endl;
	print(root);
}

//FUNCTION TO UPDATE INFORMATION
void AVL::update(int key, string new_item,int new_price)
{
    node *t = root;
    while (t != NULL)
    {
        if (t->data == key)
        {
            t->item = new_item;
            t->price = new_price;
            break;
        }
        t = t->data < key ? t->right : t->left;
    }
}

//DECREMENTING QUANTITY ON DELETION
void AVL::count1(int key)
{
	node *t=root;
	while (t != NULL)
    {
		if (t->data == key)
		{
		    t->count--;
		    break;
		}
		t = t->data < key ? t->right : t->left;
	}
}

//RETURN COUNT OF A PARTICULAR NODE
int AVL::count2(int key)
{
	node *t=root;
	while (t != NULL)
    {
		if (t->data == key)
		{
		    return t->count;
		    break;
		}
		t = t->data < key ? t->right : t->left;
	}
}

void AVL::deletetree()
{
	deletetree(root);
}

//FUNCTION TO DELETE ENTIRE TREE
void AVL::deletetree(node*& t)
{
	if(t!=NULL)
    {
		deletetree(t->left);
		deletetree(t->right);
		delete t;
	}
	t=NULL;
}
