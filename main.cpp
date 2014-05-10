//Author and Time: 	for_wind  [2012/11/18]
//Contact Me£º		jiajia.wind@gmail.com

#include <iostream>
#include "redblacktree.h"
using namespace std;

int main()
{
	RedBlackTree newTree;
	//int key[10]={1,2,3,4,5,6,7,8,9,10};
 	int key[10]={9,8,7,6,5,4,3,2,1,0};
	for(int i=0;i<10;i++)
	{
		newTree.InsertNode(key[i]);
		newTree.PreorderTravel();
		cout<<endl;
	}
	cout<<"now to delete the node of key = "<<7<<endl;
	newTree.DeleteNode(7);
	newTree.PreorderTravel();
}
