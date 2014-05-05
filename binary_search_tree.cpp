
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef int KeyType;
typedef struct Node
{
	KeyType key;
	struct Node * left;
	struct Node * right;
	struct Node * parent;
}Node,*PNode;
// 插入
void insert(PNode * root,KeyType key)
{
	// 初始化插入节点
	PNode p = (PNode)malloc(sizeof(Node));
	p->key = key;
	p->left = p->right = p->parent = NULL;
	// 空树，则此节点直接作为根节点
	if(*root == NULL)
	{
		*root = p;
		return ;
	}
	// 插入当前节点root的左孩子
	if((*root)->left == NULL && (*root)->key > key)
	{
		p->parent = (*root);
		(*root)->left = p;
		return ;
	}
	// 插入当前节点root的右孩子
	if((*root)->right == NULL && (*root)->key < key)
	{
		p->parent = (*root);
		(*root)->right = p;
		return ;
	}

	if((*root)->key > key)
		insert(&(*root)->left,key);
	else if((*root)->key < key)
		insert(&(*root)->right,key);
	else
		return;
}
// 查找特定关键词
PNode search(PNode root,KeyType key)
{
	if(root == NULL)
		return NULL;
	// 查找右子数
	if(key > root->key)
		return search(root->right,key);
	// 查找左字数
	else if(key < root->key)
		return search(root->left,key);
	else
		return root;
}

// 查找最小的关键字
PNode find_Min(PNode root)
{
	if(root == NULL)
		return NULL;
	if(root->left == NULL)
		return root;
	else
		return find_Min(root->left);
}
// 查找最大关键词
PNode find_Max(PNode root)
{
	if(root == NULL)
		return NULL;
	if(root->right == NULL)
		return root;
	else 
		return find_Max(root->right);
}

// 查找某个节点的前驱
PNode searchPredecessor(PNode p)
{
	// 空树
	if(p == NULL)
		return p;
	// 有左子树、左子树最大的那个
	if(p->left)
		return find_Max(p->left);
	// 无左子树，查找某个节点的右子树遍历完了
	else
	{
		if(p->parent == NULL)
			return NULL;
		// 向上寻找前驱
		while(p)
		{
			if(p->parent->right == p)
				break;
			p = p->parent;
		}
		return p->parent;
	}
}

PNode searchSuccessor(PNode p)
{
	// 空树
	if(p == NULL)
		return p;
	// 有右子树，右子树最小的那个
	if(p->right)
		return find_Min(p->right);
	// 无右子树，查找某个节点的左子树遍历完了
	else
	{
		if(p->parent == NULL)
			return NULL;
		// 向上寻找
		while(p)
		{
			if(p->parent->left == p)
				break;
			p = p->parent;
		}
		return p->parent;
	}
}


// 根据关键词删除某个节点，删除成功返回1，否则返回0
int deleteNode(PNode* root,KeyType key)
{
	PNode q;
	PNode p = search(*root,key);
	KeyType temp;
	// 没找到此关键词，返回0
	if(!p)
		return 0;
	// 1.如果是叶子节点，则直接删除
	if(p->left == NULL && p->right == NULL)
	{
		// 只有一个元素，删除后变成空树
		if(p->parent == NULL)
		{
			free(p);
			(*root) = NULL;
		}
		else
		{
			if(p->parent->left == p)
				p->parent->left = NULL;
			else
				p->parent->right = NULL;
			free(p);
		}
	}

	// 2.被删除的只有左子树
	else if(p->left && !(p->right))
	{
		p->left->parent = p->parent;
		// 如果删除的是父节点，要改变父节点的指针
		if(p->parent = NULL)
			*root = p->left;
		// 删除的节点是父亲节点的左孩子
		else if(p->parent->left == p)
			p->parent->left = p->left;
		// 删除的节点是父亲节点的右孩子
		else 
			p->parent->right = p->left;
		free(p);
	}

	// 3.删除节点只有右子树
	else if(p->right && !(p->left))
	{
		p->right->parent = p->parent;
		// 如果删除的是父节点，要改变父节点的指针
		if(p->parent == NULL)
			*root = p->right;
		// 删除的节点是父亲节点的左孩子
		else if(p->parent->left == p)
			p->parent->left = p->right;
		// 删除的节点是父亲节点的右孩子
		else 
			p->parent->right = p->right;
		free(p);
	}

	// 4.被删除的节点，既有左孩子，又有右孩子
	// 该节点的后继节点肯定没有左子树
	// 删掉后继节点，后继节点的值代替节点
	else
	{
		q = searchSuccessor(p);
		temp = q->key;
		deleteNode(root,q->key);
		p->key = temp;
	}
	return 1;
}

// 创建二叉搜索树
void create(PNode* root,KeyType *keyArray,int length)
{
	int i;
	// 逐节点插入二叉树
	for(i = 0;i < length;i++)
		insert(root,keyArray[i]);
}

int main()
{
	int i;
	PNode root = NULL;
	KeyType nodeArray[11] = {15,6,18,3,7,17,20,2,4,13,9};
	create(&root,nodeArray,11);
	for(i=0;i<2;i++)
		deleteNode(&root,nodeArray[i]);
	std::cout << searchPredecessor(root)->key << std::endl;
	std::cout << searchSuccessor(root)->key << std::endl;
	std::cout << find_Min(root)->key << std::endl;
	std::cout << find_Max(root)->key << std::endl;
	std::cin.get();
	return 0;
}