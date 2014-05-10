/***********************************************
Filename:	    redblacktree.h
Description:    红黑树类 
				红黑树是一种接近平衡的二叉查找树
				满足以下5条性质：
				1、每个节点或是红，或是黑；
				2、根节点是黑的；
				3、每个叶子节点是黑的；
				4、如果一个节点是红的，则其两个儿子节点都是黑的；
				5、对于每个节点，从该节点到其子孙节点的所有路径上包含相同数目的黑节点。
MainFunctions:	        
Precondition:	暂无	  	   
References：	暂无
Author and Time: 	for_wind  [2012/11/18]
Contact Me：		jiajia.wind@gmail.com
***********************************************/


#include <iostream>
#include <string>
using namespace std;

class RedBlackTree
{
private:
	enum Color {BLACK =0, RED =1, UNKNOWN=3};
	typedef struct node
	{
		int key; 
		Color color;
		struct node *left;
		struct node *right;
		struct node *parent;
	}TreeNode;
	int count;			//树节点的个数
	TreeNode *root;		//根指针
	TreeNode *nullNode;	//哨兵表示为空叶节点
public:
	RedBlackTree();
	~RedBlackTree();
	TreeNode* Search(int key);					//按关键字搜索，返回节点指针
	TreeNode* Minmum(TreeNode *ptr);			//返回关键字最小的节点指针
	//TreeNode* Maxmum(TreeNode *ptr);			//返回关键字最大的节点指针
	TreeNode* Successor(TreeNode *ptr);		//返回关键字最小的节点指针
	//TreeNode* Predecessor(TreeNode *ptr);
	void LeftRoate(TreeNode *ptrX);
	void RightRoate(TreeNode *ptrX);
	void InsertNode(int key);
	void InsertFixup(TreeNode *ptrZ);
	void DeleteNode(int key);
	void DeleteFixup(TreeNode *ptrX);
	void PreorderTravel();
	//void InorderTravel();
	//void PostorderTravel();
	void DestoryTree(TreeNode *ptr);
};