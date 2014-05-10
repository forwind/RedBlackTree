/***********************************************
Filename:	    redblacktree.cpp
Description:    ��������ʵ�� 
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
Description:	���ҹؼ���Ϊkey�Ľڵ㣬����ָ��ýڵ��ָ��
				��������ڣ��򷵻�nullNode
Precondition:	 
References��	...
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
Description:	������ptrΪ���������йؼ�����С�Ľڵ�ָ��
Precondition:	 
References��	...
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
Description:	Ѱ��ptr�ĺ�̣�������ָ��ú�̽ڵ��ָ��
				��ĳһ�ڵ�ĺ����ָ�ؼ���key���ڸýڵ����key��С���Ǹ��ڵ㣩
Precondition:	 
References��	...
Author and Time: 	for_wind  [2012/11/18 ]
***********************************************/
RedBlackTree::TreeNode* RedBlackTree::Successor(TreeNode *ptr)
{
	if(ptr==nullNode) return ptr;
	//�����²��ң����ptr�������ǿգ���ptr�ĺ�̼�Ϊ�������е�����ڵ�
	if(ptr->right!=nullNode)
		return Minmum(ptr->right);
	//�����ϲ��ң����ptr������Ϊ�գ���ptr�ĺ��Ϊ
	//ptr��������ȣ����Ҹýڵ������Ҳ��ptr�����ȣ�
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
Description:	����ؼ���Ϊkey�Ľڵ�
Precondition:	...	  	   
References��	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::InsertNode(int key)
{
	//�½��ڵ㣬����ֵ��ʼ��
	TreeNode *ptrZ= new TreeNode();
	ptrZ->key=key;
	ptrZ->left=nullNode;
	ptrZ->right=nullNode;

	TreeNode *ptrY=nullNode,*ptrX=root;
	while(ptrX!=nullNode)
	{
		ptrY=ptrX;
		//���ݹؼ��ֵıȽϽ����ȷ����ת����ת
		if(ptrZ->key<ptrY->key)
			ptrX=ptrX->left;
		else 
			ptrX=ptrX->right;
	}
	//����
	ptrZ->parent=ptrY;
	if(ptrY==nullNode)
		root=ptrZ;
	else if(ptrZ->key < ptrY->key)
		ptrY->left=ptrZ;
	else 
		ptrY->right=ptrZ;

	ptrZ->color=RED;
	/*
	Ϊ�ν��²������Ϊ��ɫ��
	����ڵ㣬������·���Ϻڵ����Ŀ��һ�����ƻ�����5
	�����㣬
	���丸�ڵ�Ϊ��ɫʱ����Ӱ��ƽ�⣬�������ֺ������
	���丸�ڵ�Ϊ��ɫʱ�����ƻ�����4����Ҫ����������
	*/
	InsertFixup(ptrZ);//����
	++count;//���ڵ����Ŀ����
}
/***********************************************  
FunctionName:	void RedBlackTree::InsertFixup(TreeNode *ptrZ)
Description:	���������ֺ��������
Precondition:	����ؼ���Ϊkey�Ľڵ�ptrZ��	  	   
References��	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::InsertFixup(TreeNode *ptrZ)
{
	while(ptrZ->parent!=nullNode&&ptrZ->parent->color == RED)
	{
		//ptrZָ������������������Ҳ�
		if(ptrZ->parent == ptrZ->parent->parent->left)
		{
			//ptrYָ��Ľڵ���ptrZ������
			TreeNode *ptrY=ptrZ->parent->parent->right;
			if(ptrY->color == RED)
			{
				//case 1:ptrZ������ptrZ�Ǻ�ɫ��
				//��ɫ�������£�����ptrZ��������������
				ptrZ->parent->color=BLACK;
				ptrY->color=BLACK;
				ptrZ->parent->parent->color=RED;
				ptrZ=ptrZ->parent->parent;
				/*
				Ϊ�ν�ptrZ=ptrZ->parent->parent;����ѭ��������
				��ΪptrZ->parent->parent������Ϊ��ɫ
				��ptrZ->parent->parent->parentΪ��ɫʱ
				�����µĺ�Z�ĸ��ڵ����Ϊ��ɫ����
				����case 1���Ծ��ƻ�����4
				*/
			}
			else
			{
				if(ptrZ==ptrZ->parent->right)
				{
					//case 2:ptrZ������ptrZ�Ǻ�ɫ�ģ�����ptrZ���Һ���
					//����һ��������ת��Ϊcase 3.
					ptrZ=ptrZ->parent;
					LeftRoate(ptrZ);
				}
				//case 3:��ɫ����������һ������
				ptrZ->parent->color=BLACK;
				ptrZ->parent->parent->color=RED;
				RightRoate(ptrZ->parent->parent);				
			}
		}
		//ptrZָ���Ҳ����������������
		else if(ptrZ->parent == ptrZ->parent->parent->right)
		{
			//ptrYָ��Ľڵ���ptrZ������
			TreeNode *ptrY=ptrZ->parent->parent->left;
			if(ptrY->color == RED)
			{
				//case 1:ptrZ������ptrZ�Ǻ�ɫ��
				//��ɫ�������£�����ptrZ��������������
				ptrZ->parent->color=BLACK;
				ptrY->color=BLACK;
				ptrZ->parent->parent->color=RED;
				ptrZ=ptrZ->parent->parent;
			}
			else
			{
				if(ptrZ==ptrZ->parent->left)
				{
					//case 2:ptrZ������ptrZ�Ǻ�ɫ�ģ�����ptrZ���Һ���
					//����һ��������ת��Ϊcase 3.
					ptrZ=ptrZ->parent;
					RightRoate(ptrZ);

				}
				//case 3:��ɫ����������һ������
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
Description:	ɾ���ؼ���Ϊkey��һ���ڵ�
				
Precondition:	�������ϵĹؼ��ֶ������ 
References��	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::DeleteNode(int key)
{
	TreeNode *ptrZ=Search(key),*ptrY=nullNode,*ptrX=nullNode;
	if(ptrZ==nullNode)
		return;
	//ptrYָ��ȷ��Ҫɾ���Ľڵ�
	if(ptrZ->left==nullNode || ptrZ->right==nullNode)
		//ptrZ�Ľڵ�������һ����Ů��ptrYΪptrZ
		ptrY=ptrZ;
	else //ptrz��������Ů��ptrYΪptrZ�ĺ��
		ptrY=Successor(ptrZ);
	//ptrXָ��ptrY�ķǿ���Ů������Ϊ��
	if(ptrY->left!=nullNode)
		ptrX=ptrY->left;
	else
		ptrX=ptrY->right;
	//ͨ���޸�ptrY��ptrX��ָ�룬��ptrYָ��Ľڵ�ɾ��
	ptrX->parent=ptrY->parent;
	if(ptrY->parent==nullNode)
	{
		root=ptrX;
	}
	else if(ptrY == ptrY->parent->left)
		ptrY->parent->left=ptrX;
	else ptrY->parent->right=ptrX;
	//���ptrZ�ĺ��ptrY��ʵ��Ҫ��ɾ���Ľڵ�
	//���ú��ptrY��key����ptrZ��key
	if(ptrY!=ptrZ)
		ptrZ->key=ptrY->key;
	//���ɾ����ptrYָ��ڵ����ɫ�Ǻ�ɫ�ģ���������Ա���
	if(ptrY->color==BLACK)
	{		
		DeleteFixup(ptrX);//����
	}
	delete(ptrY);
}
/***********************************************  
FunctionName:	
Description:	���������ֺ��������
Precondition:	ɾ���ڵ��ptrXΪptrY�ĺ��ӻ�Ϊ��	
				��ptrY�ľ��庬����ο�
				void RedBlackTree::DeleteNode(int key)��
References��	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::DeleteFixup(TreeNode *ptrX)
{
	TreeNode *ptrW=nullNode;
	while(ptrX!=root &&ptrX->color==BLACK)
	{
		if(ptrX==ptrX->parent->left)//ptrX����������
		{
			//ptrW��ptrX���ֵܣ������Ҳ�
			ptrW=ptrX->parent->right;
			if(ptrW->color==RED)
			{
				//case 1��ptrX���ֵ�ptrW�Ǻ�ɫ��
				//ptrW�ĺ���һ��Ϊ��
				//�ı�ptrW��ptrw���ڵ����ɫ������ptrW��parent����������
				ptrW->color=BLACK;
				ptrX->parent->color=RED;
				LeftRoate(ptrX->parent);
				ptrW=ptrX->parent->right;
			}
			else if( ptrW->left->color==BLACK&&ptrW->right->color==BLACK)
			{
				//case 2��ptrX���ֵ�ptrW�Ǻ�ɫ�ģ���ptrW���������Ӷ��Ǻ�ɫ��
				//��ptrW����ɫ��Ϊ��ɫ��������������5
				//ptrX����һ��
				ptrW->color=RED;
				ptrX=ptrX->parent;
			}
			else 
			{
				if(ptrW->right->color==BLACK)
				{
					//case 3��ptrX���ֵ�ptrW�Ǻ�ɫ�ģ���ptrW�������Ǻ�ɫ�ģ��Һ���Ϊ��ɫ��
					//����ptrW�������ӵ���ɫ������ptrW��������
					//ת��Ϊcase 4
					ptrW->left->color=BLACK;
					ptrW->color=RED;
					RightRoate(ptrW);
					ptrW=ptrX->parent->right;
				}
				//case 4��ptrX���ֵ�ptrW�Ǻ�ɫ�ģ���ptrW���Һ����Ǻ�ɫ��
				//�޸���ɫ������ptrX��һ������
				ptrW->color=ptrX->parent->color;
				ptrX->parent->color=BLACK;
				ptrW->right->color=BLACK;
				LeftRoate(ptrX->parent);
				ptrX=root;
			}
		}
		else //ptrX����������
		{
			//ptrW��ptrX���ֵܣ��������
			ptrW=ptrX->parent->left;
			if(ptrW->color==RED)
			{
				//case 1��ptrX���ֵ�ptrW�Ǻ�ɫ��
				//ptrW�ĺ���һ��Ϊ��
				//�ı�ptrW��ptrw���ڵ����ɫ������ptrW��parent����������
				ptrW->color=BLACK;
				ptrX->parent->color=RED;
				RightRoate(ptrX->parent);
				ptrW=ptrX->parent->left;
			}
			else if( ptrW->right->color==BLACK&&ptrW->left->color==BLACK)
			{
				//case 2��ptrX���ֵ�ptrW�Ǻ�ɫ�ģ���ptrW���������Ӷ��Ǻ�ɫ��
				//��ptrW����ɫ��Ϊ��ɫ��������������5
				//ptrX����һ��
				ptrW->color=RED;
				ptrX=ptrX->parent;
			}
			else 
			{
				if(ptrW->left->color==BLACK)
				{
					//case 3��ptrX���ֵ�ptrW�Ǻ�ɫ�ģ���ptrW���Һ����Ǻ�ɫ�ģ�����Ϊ��ɫ��
					//����ptrW�����Һ��ӵ���ɫ������ptrW��������
					//ת��Ϊcase 4
					ptrW->right->color=BLACK;
					ptrW->color=RED;
					LeftRoate(ptrW);
					ptrW=ptrX->parent->left;
				}
				//case 4��ptrX���ֵ�ptrW�Ǻ�ɫ�ģ���ptrW�������Ǻ�ɫ��
				//�޸���ɫ������ptrX��һ������
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
Description:	����
				����ptrX�����Һ���ptrY����Ϊ֧�������ת��
				ʹ��ptrY��Ϊ�������¸���ptrX��ΪptrY�����ӣ�
				��ptrY���������ΪptrX���Һ��ӣ�
				���ڱ�������5
Precondition:	 
References��	...
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
Description:	����
				���ڱ�������5
Precondition:	 
References��	...
Author and Time: 	for_wind  [2012/11/15]
***********************************************/
void RedBlackTree::RightRoate(TreeNode *ptrX)
{
	TreeNode *ptrY=ptrX->left; 
	//ptrY���Һ��ӳ�ΪptrX������
	ptrX->left=ptrY->right;			
	if(ptrY->right!=nullNode)
		ptrY->right->parent=ptrX;
	//ptrY��Ϊ�������¸�
	ptrY->parent=ptrX->parent;
	if(ptrX->parent==nullNode)
		root=ptrY;
	else
	{
		if(ptrX==ptrX->parent->left)
			ptrX->parent->left=ptrY;
		else ptrX->parent->right=ptrY;
	}
	//ptrX��ΪptrY���Һ���
	ptrY->right=ptrX;
	ptrX->parent=ptrY;
}
/***********************************************  
FunctionName:	
Description:	ǰ�����
Precondition:	  	   
References��	...
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
Description:	ɾ����
Precondition:	Ĭ������ɾ��������ptr=root
				���������ɾ����ptrΪ��������ʱ��
				��ע�⵽��parent�����Һ���ָ��δ�Ķ�  	   
References��	...
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
