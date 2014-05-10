/***********************************************
Filename:	    redblacktree.cpp
Description:    红黑树类的实现 
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
#include <stack>
#include "redblacktree.h"

using namespace std;

RedBlackTree::RedBlackTree()
{	
	count=0;
	nullNode= new TreeNode();
	nullNode->parent=NULL;
	nullNode->color=BLACK;
	nullNode->left=NULL;
	nullNode->right=NULL;
	nullNode->key=-1;
	root=nullNode;
}
RedBlackTree::~RedBlackTree()
{
	if(root!=nullNode)
		DestoryTree(root);	
	delete(nullNode);
}
/***********************************************  
FunctionName:	
Description:	查找关键字为key的节点，返回指向该节点的指针
				如果不存在，则返回nullNode
Precondition:	 
References：	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
RedBlackTree::TreeNode* RedBlackTree::Search(int key)
{
	TreeNode *ptr=root;
	while(ptr!=nullNode&&key!=ptr->key)
	{
		if(key < ptr->key)
			ptr=ptr->left;
		else 
			ptr=ptr->right;
	}
	return ptr;
}
/***********************************************  
FunctionName:	
Description:	返回以ptr为根的子树中关键字最小的节点指针
Precondition:	 
References：	...
Author and Time: 	for_wind  [2012/11/18 ]
***********************************************/
RedBlackTree::TreeNode* RedBlackTree::Minmum(TreeNode *ptr)
{
	while(ptr->left!=nullNode)
		ptr=ptr->left;
	return ptr;
}
/***********************************************  
FunctionName:	
Description:	寻找ptr的后继，并返回指向该后继节点的指针
				（某一节点的后继是指关键字key大于该节点的且key最小的那个节点）
Precondition:	 
References：	...
Author and Time: 	for_wind  [2012/11/18 ]
***********************************************/
RedBlackTree::TreeNode* RedBlackTree::Successor(TreeNode *ptr)
{
	if(ptr==nullNode) return ptr;
	//（向下查找）如果ptr右子树非空，则ptr的后继即为右子树中的最左节点
	if(ptr->right!=nullNode)
		return Minmum(ptr->right);
	//（向上查找）如果ptr右子树为空，则ptr的后继为
	//ptr的最低祖先（并且该节点的左孩子也是ptr的祖先）
	TreeNode *ptrY=ptr->parent;
	while(ptrY!=nullNode && ptr==ptrY->right)
	{
		ptr=ptrY;
		ptrY=ptrY->parent;
	}
	return ptrY;
}

/***********************************************  
FunctionName:	void RedBlackTree::InsertNode(int key)
Description:	插入关键字为key的节点
Precondition:	...	  	   
References：	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::InsertNode(int key)
{
	//新建节点，并赋值初始化
	TreeNode *ptrZ= new TreeNode();
	ptrZ->key=key;
	ptrZ->left=nullNode;
	ptrZ->right=nullNode;

	TreeNode *ptrY=nullNode,*ptrX=root;
	while(ptrX!=nullNode)
	{
		ptrY=ptrX;
		//根据关键字的比较结果，确定左转或右转
		if(ptrZ->key<ptrY->key)
			ptrX=ptrX->left;
		else 
			ptrX=ptrX->right;
	}
	//插入
	ptrZ->parent=ptrY;
	if(ptrY==nullNode)
		root=ptrZ;
	else if(ptrZ->key < ptrY->key)
		ptrY->left=ptrZ;
	else 
		ptrY->right=ptrZ;

	ptrZ->color=RED;
	/*
	为何将新插入点设为红色？
	插入黑点，会增加路径上黑点的数目，一定会破坏性质5
	插入红点，
	当其父节点为黑色时，不影响平衡，继续保持红黑性质
	当其父节点为红色时，才破坏性质4，需要进行修正。
	*/
	InsertFixup(ptrZ);//修正
	++count;//树节点的数目增加
}
/***********************************************  
FunctionName:	void RedBlackTree::InsertFixup(TreeNode *ptrZ)
Description:	修正并保持红黑树性质
Precondition:	插入关键字为key的节点ptrZ后	  	   
References：	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::InsertFixup(TreeNode *ptrZ)
{
	while(ptrZ->parent!=nullNode&&ptrZ->parent->color == RED)
	{
		//ptrZ指向左侧子树，叔叔在右侧
		if(ptrZ->parent == ptrZ->parent->parent->left)
		{
			//ptrY指向的节点是ptrZ的叔叔
			TreeNode *ptrY=ptrZ->parent->parent->right;
			if(ptrY->color == RED)
			{
				//case 1:ptrZ的叔叔ptrZ是红色的
				//颜色分配如下，并将ptrZ在树中上移两层
				ptrZ->parent->color=BLACK;
				ptrY->color=BLACK;
				ptrZ->parent->parent->color=RED;
				ptrZ=ptrZ->parent->parent;
				/*
				为何将ptrZ=ptrZ->parent->parent;继续循环迭代？
				因为ptrZ->parent->parent被设置为红色
				当ptrZ->parent->parent->parent为红色时
				（即新的红Z的父节点可能为红色），
				符合case 1，仍旧破坏性质4
				*/
			}
			else
			{
				if(ptrZ==ptrZ->parent->right)
				{
					//case 2:ptrZ的叔叔ptrZ是黑色的，而且ptrZ是右孩子
					//进行一次左旋，转变为case 3.
					ptrZ=ptrZ->parent;
					LeftRoate(ptrZ);
				}
				//case 3:颜色修正，进行一次右旋
				ptrZ->parent->color=BLACK;
				ptrZ->parent->parent->color=RED;
				RightRoate(ptrZ->parent->parent);				
			}
		}
		//ptrZ指向右侧子树，叔叔在左侧
		else if(ptrZ->parent == ptrZ->parent->parent->right)
		{
			//ptrY指向的节点是ptrZ的叔叔
			TreeNode *ptrY=ptrZ->parent->parent->left;
			if(ptrY->color == RED)
			{
				//case 1:ptrZ的叔叔ptrZ是红色的
				//颜色分配如下，并将ptrZ在树中上移两层
				ptrZ->parent->color=BLACK;
				ptrY->color=BLACK;
				ptrZ->parent->parent->color=RED;
				ptrZ=ptrZ->parent->parent;
			}
			else
			{
				if(ptrZ==ptrZ->parent->left)
				{
					//case 2:ptrZ的叔叔ptrZ是黑色的，而且ptrZ是右孩子
					//进行一次右旋，转变为case 3.
					ptrZ=ptrZ->parent;
					RightRoate(ptrZ);

				}
				//case 3:颜色修正，进行一次左旋
				ptrZ->parent->color=BLACK;
				ptrZ->parent->parent->color=RED;
				LeftRoate(ptrZ->parent->parent);
			}
		}
	}
	root->color=BLACK;
}
/***********************************************  
FunctionName:	
Description:	删除关键字为key的一个节点
				
Precondition:	假设树上的关键字都不相等 
References：	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::DeleteNode(int key)
{
	TreeNode *ptrZ=Search(key),*ptrY=nullNode,*ptrX=nullNode;
	if(ptrZ==nullNode)
		return;
	//ptrY指向确定要删除的节点
	if(ptrZ->left==nullNode || ptrZ->right==nullNode)
		//ptrZ的节点至多有一个子女，ptrY为ptrZ
		ptrY=ptrZ;
	else //ptrz有两个子女，ptrY为ptrZ的后继
		ptrY=Successor(ptrZ);
	//ptrX指向ptrY的非空子女，或置为空
	if(ptrY->left!=nullNode)
		ptrX=ptrY->left;
	else
		ptrX=ptrY->right;
	//通过修改ptrY和ptrX的指针，将ptrY指向的节点删除
	ptrX->parent=ptrY->parent;
	if(ptrY->parent==nullNode)
	{
		root=ptrX;
	}
	else if(ptrY == ptrY->parent->left)
		ptrY->parent->left=ptrX;
	else ptrY->parent->right=ptrX;
	//如果ptrZ的后继ptrY是实际要被删除的节点
	//则用后继ptrY的key覆盖ptrZ的key
	if(ptrY!=ptrZ)
		ptrZ->key=ptrY->key;
	//如果删除的ptrY指向节点的颜色是红色的，红黑性质仍保持
	if(ptrY->color==BLACK)
	{		
		DeleteFixup(ptrX);//修正
	}
	delete(ptrY);
}
/***********************************************  
FunctionName:	
Description:	修正并保持红黑树性质
Precondition:	删除节点后，ptrX为ptrY的孩子或为空	
				（ptrY的具体含义请参看
				void RedBlackTree::DeleteNode(int key)）
References：	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::DeleteFixup(TreeNode *ptrX)
{
	TreeNode *ptrW=nullNode;
	while(ptrX!=root &&ptrX->color==BLACK)
	{
		if(ptrX==ptrX->parent->left)//ptrX是左子树根
		{
			//ptrW是ptrX的兄弟，在其右侧
			ptrW=ptrX->parent->right;
			if(ptrW->color==RED)
			{
				//case 1：ptrX的兄弟ptrW是红色的
				//ptrW的孩子一定为黑
				//改变ptrW和ptrw父节点的颜色，并从ptrW的parent处进行左旋
				ptrW->color=BLACK;
				ptrX->parent->color=RED;
				LeftRoate(ptrX->parent);
				ptrW=ptrX->parent->right;
			}
			else if( ptrW->left->color==BLACK&&ptrW->right->color==BLACK)
			{
				//case 2：ptrX的兄弟ptrW是黑色的，且ptrW的两个孩子都是黑色的
				//将ptrW的颜色置为红色，用于满足性质5
				//ptrX上移一层
				ptrW->color=RED;
				ptrX=ptrX->parent;
			}
			else 
			{
				if(ptrW->right->color==BLACK)
				{
					//case 3：ptrX的兄弟ptrW是黑色的，且ptrW的左孩子是红色的，右孩子为黑色的
					//交换ptrW和其左孩子的颜色，并对ptrW进行右旋
					//转变为case 4
					ptrW->left->color=BLACK;
					ptrW->color=RED;
					RightRoate(ptrW);
					ptrW=ptrX->parent->right;
				}
				//case 4：ptrX的兄弟ptrW是黑色的，且ptrW的右孩子是红色的
				//修改颜色，并对ptrX做一次左旋
				ptrW->color=ptrX->parent->color;
				ptrX->parent->color=BLACK;
				ptrW->right->color=BLACK;
				LeftRoate(ptrX->parent);
				ptrX=root;
			}
		}
		else //ptrX是右子树根
		{
			//ptrW是ptrX的兄弟，在其左侧
			ptrW=ptrX->parent->left;
			if(ptrW->color==RED)
			{
				//case 1：ptrX的兄弟ptrW是红色的
				//ptrW的孩子一定为黑
				//改变ptrW和ptrw父节点的颜色，并从ptrW的parent处进行右旋
				ptrW->color=BLACK;
				ptrX->parent->color=RED;
				RightRoate(ptrX->parent);
				ptrW=ptrX->parent->left;
			}
			else if( ptrW->right->color==BLACK&&ptrW->left->color==BLACK)
			{
				//case 2：ptrX的兄弟ptrW是黑色的，且ptrW的两个孩子都是黑色的
				//将ptrW的颜色置为红色，用于满足性质5
				//ptrX上移一层
				ptrW->color=RED;
				ptrX=ptrX->parent;
			}
			else 
			{
				if(ptrW->left->color==BLACK)
				{
					//case 3：ptrX的兄弟ptrW是黑色的，且ptrW的右孩子是红色的，左孩子为黑色的
					//交换ptrW和其右孩子的颜色，并对ptrW进行左旋
					//转变为case 4
					ptrW->right->color=BLACK;
					ptrW->color=RED;
					LeftRoate(ptrW);
					ptrW=ptrX->parent->left;
				}
				//case 4：ptrX的兄弟ptrW是黑色的，且ptrW的左孩子是红色的
				//修改颜色，并对ptrX做一次右旋
				ptrW->color=ptrX->parent->color;
				ptrX->parent->color=BLACK;
				ptrW->left->color=BLACK;
				RightRoate(ptrX->parent);
				ptrX=root;
			}
		}
	}

}
/***********************************************  
FunctionName:	void RedBlackTree::LeftRoate(TreeNode *ptrX)
Description:	左旋
				（以ptrX到其右孩子ptrY的链为支轴进行旋转，
				使得ptrY成为子树的新根，ptrX成为ptrY的左孩子，
				而ptrY的左孩子则成为ptrX的右孩子）
				用于保持性质5
Precondition:	 
References：	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::LeftRoate(TreeNode *ptrX)
{
	TreeNode *ptrY=ptrX->right;
	ptrX->right=ptrY->left; 
	if(ptrY->left!=nullNode)
		ptrY->left->parent=ptrX;
	ptrY->parent=ptrX->parent;
	if(ptrX->parent==nullNode)
		root=ptrY;
	else
	{
		if(ptrX==ptrX->parent->left)
			ptrX->parent->left=ptrY;
		else ptrX->parent->right=ptrY;
	}
	ptrY->left=ptrX;
	ptrX->parent=ptrY;
}
/***********************************************  
FunctionName:	void RedBlackTree::RightRoate(TreeNode *ptrX)
Description:	右旋
				用于保持性质5
Precondition:	 
References：	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::RightRoate(TreeNode *ptrX)
{
	TreeNode *ptrY=ptrX->left; 
	//ptrY的右孩子成为ptrX的左孩子
	ptrX->left=ptrY->right;			
	if(ptrY->right!=nullNode)
		ptrY->right->parent=ptrX;
	//ptrY成为子树的新根
	ptrY->parent=ptrX->parent;
	if(ptrX->parent==nullNode)
		root=ptrY;
	else
	{
		if(ptrX==ptrX->parent->left)
			ptrX->parent->left=ptrY;
		else ptrX->parent->right=ptrY;
	}
	//ptrX成为ptrY的右孩子
	ptrY->right=ptrX;
	ptrX->parent=ptrY;
}
/***********************************************  
FunctionName:	
Description:	前序遍历
Precondition:	  	   
References：	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::PreorderTravel()
{
	TreeNode *ptr= root;
	stack <TreeNode *> preStack;
	while(ptr!=nullNode||!preStack.empty())
	{
		while (ptr!=nullNode)
		{
			cout<<ptr->key<<'['<<ptr->color<<']'<<' ';
			preStack.push(ptr);
			ptr=ptr->left;
		}
		if(!preStack.empty())
		{
			ptr=preStack.top();
			preStack.pop();
			ptr=ptr->right;
		}
	}
}
/***********************************************  
FunctionName:	
Description:	删除树
Precondition:	默认用于删除整棵树ptr=root
				否则仅用于删除以ptr为根的子树时，
				请注意到其parent的左右孩子指针未改动  	   
References：	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::DestoryTree(TreeNode *ptr)
{
	if(ptr!=nullNode)
	{
		DestoryTree(ptr->left);
		DestoryTree(ptr->right);
		//cout<<ptr->key<<endl;
		delete(ptr);
	}	
}
