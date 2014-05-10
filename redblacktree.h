/***********************************************
Filename:	    redblacktree.h
Description:    ������� 
				�������һ�ֽӽ�ƽ��Ķ��������
				��������5�����ʣ�
				1��ÿ���ڵ���Ǻ죬���Ǻڣ�
				2�����ڵ��Ǻڵģ�
				3��ÿ��Ҷ�ӽڵ��Ǻڵģ�
				4�����һ���ڵ��Ǻ�ģ������������ӽڵ㶼�Ǻڵģ�
				5������ÿ���ڵ㣬�Ӹýڵ㵽������ڵ������·���ϰ�����ͬ��Ŀ�ĺڽڵ㡣
MainFunctions:	        
Precondition:	����	  	   
References��	����
Author and Time: 	for_wind  [2012/11/18]
Contact Me��		jiajia.wind@gmail.com
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
	int count;			//���ڵ�ĸ���
	TreeNode *root;		//��ָ��
	TreeNode *nullNode;	//�ڱ���ʾΪ��Ҷ�ڵ�
public:
	RedBlackTree();
	~RedBlackTree();
	TreeNode* Search(int key);					//���ؼ������������ؽڵ�ָ��
	TreeNode* Minmum(TreeNode *ptr);			//���عؼ�����С�Ľڵ�ָ��
	//TreeNode* Maxmum(TreeNode *ptr);			//���عؼ������Ľڵ�ָ��
	TreeNode* Successor(TreeNode *ptr);		//���عؼ�����С�Ľڵ�ָ��
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