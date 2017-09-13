/*
 * avl_tree.c
 *
 *  Created on: 11-Sep-2017
 *      Author: d
 */
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>

#define MAX(a,b)	(a > b ? a : b);

typedef struct tnode{
	struct tnode *left;
	struct tnode *right;
	int data;
	int height;
}avl_tree;

typedef struct qnode{
	avl_tree *data;
	struct qnode *next;
}avlqueue;

avlqueue *qbase = NULL, *q_current_pos = NULL;
avl_tree *avl_home = NULL;
avl_tree * insert(avl_tree *start,int data);


void inorder_recursive_avl_traverse(avl_tree *start);
void preorder_recursive_avl_traverse(avl_tree *start);
void postorder_recursive_avl_traverse(avl_tree *start);
void AVL_BFS_traverse(avl_tree *start);
int AVL_tree_main(void)
{
	unsigned int choice = 0;
	int data = 0;
	q_current_pos = qbase;
	while(1)
	{
		printf("\n");
		printf("1. Add a node\t\tAVL tree\n");
#if 0
		printf("2. Delete a node 					AVL tree\n");
		printf("3. Find a node		 				AVL tree\n");
		printf("4. Inorder Traversal 				AVL tree\n");
		printf("5. Preorder traversal 				AVL tree\n");
		printf("6. Postorder traversal 				AVL tree\n");
#endif
		printf("7. inOrder Recursive traversal 		AVL tree\n");
		printf("8. Preorder Recursive traversal 	AVL tree\n");
		printf("9. Postorder Recursivetraversal 	AVL tree\n");
//		printf("10. Find Successor 					AVL tree\n");
//		printf("11. Find Predecessor 				AVL tree\n");
		printf("12. Breadth first traversal 		AVL tree\n");
		//printf("13. Find the height of the tree  	AVL tree\n");
		//printf("14. Check if tree is balanced 		AVL tree\n");

		printf("0. Exit\t\tAVL tree\n");

		scanf("%d",&choice);

		switch(choice)
		{
		case 1:
			printf("Enter data for AVL tree (-1 to exit)\n");

			while(1)
			{
				scanf("%d",&data);
				if(data == -1)	break;
				else
					avl_home = insert(avl_home,data);
			}
			break;
#if 0
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
		case 5:
			break;
		case 6:
			break;
#endif
		case 7:
			inorder_recursive_avl_traverse(avl_home);
			break;
		case 8:
			preorder_recursive_avl_traverse(avl_home);
			break;
		case 9:
			postorder_recursive_avl_traverse(avl_home);
			break;
//		case 10:
//			break;
//		case 11:
//			break;
		case 12:
			AVL_BFS_traverse(avl_home);
			break;
//		case 13:
//			break;
//		case 14:
//			break;
		case 0:
			return 0;

		default:
			break;
		}
	}
return 0;
}

avl_tree * newnode(int data)
{
	avl_tree *node = (avl_tree *)malloc(sizeof(avl_tree));
	node->data = data;
	node->height = 1; // default height at leaf node would be 1
	node->left = NULL;
	node->right = NULL;
	return(node);
}
int height(avl_tree *start)
{
	if(start == NULL)
		return 0;
	else
		return start->height;
}

int getBalance(avl_tree *start)
{
	if(start == NULL)
		return 0;
	else
		return (height(start->left) - height(start->right));
}
avl_tree * rightRotate(avl_tree *start)
{
	avl_tree *t2,*x;
	x = start->left;
	t2 = x->right;

	// perform the rotation
	x->right = start;
	start->left = t2;

	// now update the heights
	x->height = 1 + MAX(height(x->left),height(x->right));
	start->height = 1 + MAX(height(start->left),height(start->right));

	return x;
}

avl_tree * leftRotate(avl_tree *start)
{
	avl_tree *x,*t2;
	x = start->right;
	t2 = x->left;

	// lets perform rotation
	x->left = start;
	start->right = t2;

	// update the height of nodes
	x->height = 1 + MAX(height(x->left),height(x->right));
	start->height = 1 + MAX(height(start->left),height(start->right));
	return x;
}
avl_tree * insert(avl_tree *start,int data)
{

	if(start == NULL)	return newnode(data);

	if(data < start->data)
	{
		start->left = insert(start->left,data);
	}
	else if(data > start->data)
	{
		start->right = insert(start->right,data);
	}
	else	return start;

	start->height = 1 + MAX(height(start->left),height(start->right));

	int balance = getBalance(start);

	// if this node is unbalanced then there are 4 cases to be handled

	// left left case
	if(balance > 1 && data < start->left->data)
	{
		return rightRotate(start);
	}

	// right right case
	if(balance < -1 && data > start->right->data)
	{
		return leftRotate(start);
	}

	//left right case
	if(balance > 1 && data > start->left->data)
	{
		start->left = leftRotate(start->left);
		return rightRotate(start);
	}

	// right left case
	if(balance < -1 && data < start->right->data)
	{
		start->right = rightRotate(start->right);
		return leftRotate(start);
	}


	return start;
}


void inorder_recursive_avl_traverse(avl_tree *start)
{
	if(start == NULL)	return;
	inorder_recursive_avl_traverse(start->left);
	printf("%d ==> ",start->data);
	inorder_recursive_avl_traverse(start->right);
}
void preorder_recursive_avl_traverse(avl_tree *start)
{
	if(start == NULL)	return;
	printf("%d ==> ",start->data);
	preorder_recursive_avl_traverse(start->left);
	preorder_recursive_avl_traverse(start->right);
}
void postorder_recursive_avl_traverse(avl_tree *start)
{
	if(start == NULL)	return;
	postorder_recursive_avl_traverse(start->left);
	postorder_recursive_avl_traverse(start->right);
	printf("%d ==> ",start->data);
}

void push_avl_queue(avl_tree *node)
{
	avlqueue *temp;
	temp = (avlqueue *)malloc(sizeof(avlqueue));
	temp->data = node;
	temp->next = NULL;
	if(qbase == NULL)
	{
		qbase = (avlqueue *)malloc(sizeof(avlqueue));
		qbase = temp;
		q_current_pos = qbase;
	}
	else
	{
		q_current_pos->next = temp;
		q_current_pos = q_current_pos->next;
	}
}

avl_tree * unqueue_avl(void)
{
	avl_tree *temp = NULL;

	if(qbase == NULL)
	{
		printf("Queue is empty !\n");
	}
	else
	{
		temp = qbase->data;
		qbase = qbase->next;
	}
return temp;
}


void AVL_BFS_traverse(avl_tree *start)
{
	avl_tree *temp = start;

	while(temp)
	{
		printf("%d ==>\n",temp->data);
		if(temp->left) 		push_avl_queue(temp->left);
		if(temp->right)		push_avl_queue(temp->right);
		temp = unqueue_avl();
	}
}
