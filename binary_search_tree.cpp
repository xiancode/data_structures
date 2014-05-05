
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
// ����
void insert(PNode * root,KeyType key)
{
	// ��ʼ������ڵ�
	PNode p = (PNode)malloc(sizeof(Node));
	p->key = key;
	p->left = p->right = p->parent = NULL;
	// ��������˽ڵ�ֱ����Ϊ���ڵ�
	if(*root == NULL)
	{
		*root = p;
		return ;
	}
	// ���뵱ǰ�ڵ�root������
	if((*root)->left == NULL && (*root)->key > key)
	{
		p->parent = (*root);
		(*root)->left = p;
		return ;
	}
	// ���뵱ǰ�ڵ�root���Һ���
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
// �����ض��ؼ���
PNode search(PNode root,KeyType key)
{
	if(root == NULL)
		return NULL;
	// ����������
	if(key > root->key)
		return search(root->right,key);
	// ����������
	else if(key < root->key)
		return search(root->left,key);
	else
		return root;
}

// ������С�Ĺؼ���
PNode find_Min(PNode root)
{
	if(root == NULL)
		return NULL;
	if(root->left == NULL)
		return root;
	else
		return find_Min(root->left);
}
// �������ؼ���
PNode find_Max(PNode root)
{
	if(root == NULL)
		return NULL;
	if(root->right == NULL)
		return root;
	else 
		return find_Max(root->right);
}

// ����ĳ���ڵ��ǰ��
PNode searchPredecessor(PNode p)
{
	// ����
	if(p == NULL)
		return p;
	// ���������������������Ǹ�
	if(p->left)
		return find_Max(p->left);
	// ��������������ĳ���ڵ����������������
	else
	{
		if(p->parent == NULL)
			return NULL;
		// ����Ѱ��ǰ��
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
	// ����
	if(p == NULL)
		return p;
	// ������������������С���Ǹ�
	if(p->right)
		return find_Min(p->right);
	// ��������������ĳ���ڵ����������������
	else
	{
		if(p->parent == NULL)
			return NULL;
		// ����Ѱ��
		while(p)
		{
			if(p->parent->left == p)
				break;
			p = p->parent;
		}
		return p->parent;
	}
}


// ���ݹؼ���ɾ��ĳ���ڵ㣬ɾ���ɹ�����1�����򷵻�0
int deleteNode(PNode* root,KeyType key)
{
	PNode q;
	PNode p = search(*root,key);
	KeyType temp;
	// û�ҵ��˹ؼ��ʣ�����0
	if(!p)
		return 0;
	// 1.�����Ҷ�ӽڵ㣬��ֱ��ɾ��
	if(p->left == NULL && p->right == NULL)
	{
		// ֻ��һ��Ԫ�أ�ɾ�����ɿ���
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

	// 2.��ɾ����ֻ��������
	else if(p->left && !(p->right))
	{
		p->left->parent = p->parent;
		// ���ɾ�����Ǹ��ڵ㣬Ҫ�ı丸�ڵ��ָ��
		if(p->parent = NULL)
			*root = p->left;
		// ɾ���Ľڵ��Ǹ��׽ڵ������
		else if(p->parent->left == p)
			p->parent->left = p->left;
		// ɾ���Ľڵ��Ǹ��׽ڵ���Һ���
		else 
			p->parent->right = p->left;
		free(p);
	}

	// 3.ɾ���ڵ�ֻ��������
	else if(p->right && !(p->left))
	{
		p->right->parent = p->parent;
		// ���ɾ�����Ǹ��ڵ㣬Ҫ�ı丸�ڵ��ָ��
		if(p->parent == NULL)
			*root = p->right;
		// ɾ���Ľڵ��Ǹ��׽ڵ������
		else if(p->parent->left == p)
			p->parent->left = p->right;
		// ɾ���Ľڵ��Ǹ��׽ڵ���Һ���
		else 
			p->parent->right = p->right;
		free(p);
	}

	// 4.��ɾ���Ľڵ㣬�������ӣ������Һ���
	// �ýڵ�ĺ�̽ڵ�϶�û��������
	// ɾ����̽ڵ㣬��̽ڵ��ֵ����ڵ�
	else
	{
		q = searchSuccessor(p);
		temp = q->key;
		deleteNode(root,q->key);
		p->key = temp;
	}
	return 1;
}

// ��������������
void create(PNode* root,KeyType *keyArray,int length)
{
	int i;
	// ��ڵ���������
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