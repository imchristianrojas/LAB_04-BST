/*
 Christian Rojas
 CIS 22C
 Lab03_Trees
 Professor Larkin
 July 25,2020
 Purpose: To convert a ArrayTree to a Binary Tree using TreeNode definition(left,right). And
 to modifiy the inorder function to output the tree horizontally like this
 100
 50 150
 20 30 170 190
 
 
 */
#include <iostream>
#include <ctime>
#include <vector>
#include <math.h>
#include <fstream>
using namespace std;


template<typename T>
class TreeNode
{
public:
    T data;
    TreeNode<T> *left;
    TreeNode<T> *right;
    
};

template <typename T>
class BinarySearchTree
{
    TreeNode<T>* root;
public:
    
    BinarySearchTree(int firstnum)
    {
        root = new TreeNode<T>;
        root->data = firstnum;
        root->left = NULL;
        root->right = NULL;
        
    }
      
    
    TreeNode<T>* getRoot(){return root;}

	
    
	TreeNode<T>* insert(T data, TreeNode<T>* temp)
	{
        
        if(temp == NULL)
        {
            temp = new TreeNode<T>;
            temp->left = NULL;
            temp->right = NULL;
            temp->data = data;
            return temp;
        }
  
            
        if(data < temp->data)
        {
            temp->left = insert(data, temp->left);
        }
        
        else if(data > temp->data)
        {
            temp->right = insert(data,temp->right);
        }
        
        return temp;
    
    
    }
    
    
    void printLines(TreeNode<T>*theNode)
    {
        int x = getLevel(root, theNode->data, 0);
        
        while(x!=0)
        {
            x = (x-1);
            cout<<"---|";
        }
        
    }

    int getLevel(TreeNode<T>*treeptr,int data, int level)
    {

        if(treeptr == NULL)
            return 0;
        if(treeptr->data == data)
            return level;
        int downLevel = getLevel(treeptr->left, data, level +1);
        
        if(downLevel!= 0)
            return downLevel;
        downLevel  = getLevel(treeptr->right, data, level + 1);
        
        return downLevel;
        
        //Source:
        //www.geeksforgeeks.org/get-level-of-a-node-in-a-binary-tree
        
    }
	void search(T x)
	{
        
        TreeNode<T>* treePtr = root;

        int ill = 0;
		while (true)
		{
			if (treePtr == NULL)
				break;
			
			if (treePtr->data == x)
			{
                
                cout<<"Found data with BST: "<<x<<endl;
                cout<<"It took "<<ill<<" comparisons to find data with binary search tree! \n"<<endl;
				break;
			}
			else if (x < treePtr->data)
                treePtr = treePtr->left;
			
			else
                treePtr = treePtr->right;
            ill++;
		}
        
	}


    
/* I figured that the best way to print horizontally would be line by line. And if a node
 at a given line was to be NULL it would print out a '-' character. This function uses recursions to get
the left hand side first then the right hand side last. */
  void printLevel(TreeNode<T>*treePtr,int level)
    {
        if(treePtr == NULL){
            cout<<'-';
            return;
        }
        if(level == 1)
            cout<<treePtr->data<<" ";
        else if(level>1)
        {
            
            printLevel(treePtr->left, level-1);
            printLevel(treePtr->right, level-1);
        }
        
    }
    void modifiedInOrder(TreeNode<T>*treeptr)
    {
    
        int height = getHeight(root);//In order for the function above to work I needed the height of the tree
        for(int i = 1; i<=height; i++){
            printLevel(root, i);
            cout<<'|'<<endl;
        }
        
        
    }
    
    
    int getHeight(TreeNode<T>* node)
{
    if (node == NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int leftHeight = getHeight(node->left);
        int rightHeight = getHeight(node->right);
  
        /* use the larger one */
        if (leftHeight > rightHeight)
            return(leftHeight + 1);
        else return(rightHeight + 1);
    }
    //Source:
} //www.geeksforgeeks.org/level-order-tree-traversal/
    
    void InOrder(TreeNode<T>*treePtr)
    {

        if(treePtr != NULL)
        {
            InOrder(treePtr->left);
            printLines(treePtr);
            cout<<treePtr->data<<" "<<endl;
            InOrder(treePtr->right);
            
        }


    }

    
   /*For the rest of the functions their overall structure stayed the same. I just implemented
    the treeNodes in all of them.*/
	void preOrder(TreeNode<T>* treePtr)
	{
        
        if(treePtr!=NULL)
        {
            printLines(treePtr);
            cout<<treePtr->data<<" "<<endl;
            preOrder(treePtr->left);
            preOrder(treePtr->right);
        }
	}
    
	void postOrder(TreeNode<T>* treePtr)
	{
        
        if(treePtr!=NULL)
        {
            
            postOrder(treePtr->left);
            postOrder(treePtr->right);
            printLines(treePtr);
            cout<<treePtr->data<<" "<<endl;
        }
        
	}
	void reverseOrder(TreeNode<T>*treePtr)
	{
        
        if(treePtr!=NULL)
        {
            reverseOrder(treePtr->right);
            printLines(treePtr);
            cout<<treePtr->data<<" "<<endl;
            reverseOrder(treePtr->left);
        }
        
	}
};
int main() 
{
    
    vector<int>numbers;
    fstream numberFile;
    numberFile.open("Numbers.txt");//List of numbers from Radix Sort Lab
    
    int feeder;
    if(numberFile.fail()){
        cerr<<"Cannot Open File!"<<endl;
        exit(1);
    }
    while(!(numberFile.eof()))
    {
        numberFile>>feeder;
        numbers.push_back(feeder);
        
    }
    
    
    
    //Compared to a standard linear search BST is really fast
    int key = 31504;
    /*I was curious as to how fast this data stucture really is so I compared it to one
     of the least efficients methods of searching to convince me.
     Granted I could've used pen,paper, and a calculator to show their differences in time complexity
     but I enjoy seeing it first hand instead.
     */
    for(int i = 0; i<numbers.size();i++)
    {
        if(numbers[i] == key){
            cout<<"There was a total of "<<i<<" comparisons with the linear search to find "<<key <<"\n"<<endl;
        }
        
    }
    
    BinarySearchTree<int>alotOfDataTree(numbers[0]);
    TreeNode<int>*root2 = alotOfDataTree.getRoot();
    
    for(int i = 1; i<numbers.size();i++)
    {
        alotOfDataTree.insert(numbers[i], root2);
    }
    alotOfDataTree.search(key);
    

//    alotOfDataTree.InOrder(root2);           /*Since the data set is really large it cannot ouput it correctly onto console. Take my word
//    alotOfDataTree.modifiedInOrder(root2);       that it works properly.*/
    
    
    
    //Data presented to the class
	vector<int> varray = { 42, 68, 35, 1, 70, 25, 79, 59, 63, 65 };
    BinarySearchTree<int>tree(varray[0]);

    
    TreeNode<int>*root = tree.getRoot();
    for(int i = 1; i<varray.size(); i++)
    {
        tree.insert(varray[i], root);
        
    }
    
 
    cout<<"Test with Data given by professor:\n"<<endl;
    cout<<"In Order: "<<endl;
    tree.InOrder(root);
    cout<<"\nIn Preorder: "<<endl;
    tree.preOrder(root);
    cout<<"\nIn postOrder "<<endl;
    tree.postOrder(root);
    cout<<"\nModified Inorder: "<<endl;
    tree.modifiedInOrder(root);
    
    
    
}
