/*
 * tree.c
 *
 *  Created on: 07-Aug-2017
 *      Author: devarsh
 */
#include<stdio.h>
#include<malloc.h>
#include<string.h>
#include<stdbool.h>
#include<stdlib.h>
#define TRUE 1
#define FALSE 0


typedef struct tnode{
	int data;
	struct tnode *left;
	struct tnode *right;
}tree;
tree *home = NULL;
typedef struct stack_node{
	tree *data;
	struct stack_node *next;
}stack;

typedef struct queue_node{
	tree *data;
	struct queue_node *next;
}queue;

bool FLAG = FALSE;
stack *head = NULL;
queue *q_base = NULL;
void add_node(void);
void delete_node(void);
void find_node(void);
void inorder_traverse(tree *start);
void preorder_traverse(tree *start);
void postorder_traverse(tree *start);
void inorder_recursive_traverse(tree *start);
void preorder_recursive_traverse(tree *start);
void postorder_recursive_traverse(tree *start);
void find_successor(void);
tree * search_successor(tree *ret);
tree * search_predecessor(tree *ret);
void find_predecessor(void);
void breadth_first_search_traverse(tree *);
int find_tree_height(tree *);
bool isBalance(tree *start);
void push_stack(tree *);
tree *pop_stack(void);
void push_queue(tree *);
tree * unqueue(void);
void sortToBalancedBST(tree *start);
int ht = 0;

int tree_main(void)
{
	unsigned int choice = 0;
	while(1)
	{
		printf("\n");
		printf("1. Add a node\n");
		printf("2. Delete a node\n");
		printf("3. Find a node\n");
		printf("4. Inorder Traversal\n");
		printf("5. Preorder traversal \n");
		printf("6. Postorder traversal\n");
		printf("7. inOrder Recursive traversal\n");
		printf("8. Preorder Recursive traversal\n");
		printf("9. Postorder Recursivetraversal\n");
		printf("10. Find Successor\n");
		printf("11. Find Predecessor\n");
		printf("12. Breadth first traversal\n");
		printf("13. Find the height of the tree \n");
		printf("14. Check if tree is balanced \n");
		printf("15. Make a balanced binary tree \n");
		printf("16. Create an AVL tree !!\n");
		printf("0. Exit\n");

		scanf("%d",&choice);

		switch(choice)
		{
		case 1:
			add_node();
			break;
		case 2:
			delete_node();
			break;
		case 3:
			find_node();
			break;
		case 4:
			{
				inorder_traverse(home);
			}
			break;
		case 5:
			{
				preorder_traverse(home);
			}
			break;
		case 6:
			postorder_traverse(home);
			break;
		case 7:
			inorder_recursive_traverse(home);
			break;
		case 8:
			preorder_recursive_traverse(home);
			break;
		case 9:
			postorder_recursive_traverse(home);
			break;
		case 10:
			find_successor();
			break;
		case 11:
			find_predecessor();
			break;
		case 12:
			breadth_first_search_traverse(home);
			break;
		case 13:
			ht = find_tree_height(home);
			printf("Height of the tree is %d \n",ht);
			break;
		case 14:
			if(isBalance(home))
			{
				printf("This tree is Balanced !!\n");
			}
			else
			{
				printf("tree is not balanced\n");
			}
			break;
		case 15:
				sortToBalancedBST(home);
			break;
		case 0:
			return 0;
			break;
		default:
			printf("Invalid Input\n");
			break;
		}
	}
return 0;
}


void add_node(void)
{
	// definition
	int data;
	tree *temp = NULL;
	tree *travel= NULL;
	printf("Enter the data_node for tree ... (-1) to break \n");
	while(1)
	{
		scanf("%d",&data);
		if(data == -1)	break;
		else
		{
			temp = (tree *)malloc(sizeof(tree));
			temp->data = data;
			temp->left = temp->right = NULL;

			if(home == NULL)
			{
				home = (tree *)malloc(sizeof(tree));
				home = temp;
			}
			else
			{
				travel = home;
				while(1)
				{
					if(travel->data > temp->data)
					{
						if(travel->left != NULL)
						{
							travel = travel->left;
						}
						else
						{
							travel->left = temp;
							break;
						}
					}
					else
					{
						if(travel->right != NULL)
						{
							travel = travel->right;
						}
						else
						{
							travel->right = temp;
							break;
						}
					}
				}
			}
		}

	}
}
tree * search_node(int data)
{
tree *travel;
travel = home;
	while(1)
	{
		if(travel->data == data)
		{
			printf("%d is found in tree !!!\n",data);
			break;
		}
		else if(travel->data < data)
		{
			if(travel->right != NULL)
			{
				travel = travel->right;
			}
			else
			{
				printf("%d is not available in tree !!\n",data);
				travel = NULL;
				break;
			}
		}
		else
		{
			if(travel->left != NULL)
			{
				travel = travel->left;
			}
			else
			{
				printf("%d is not in the tree !!\n",data);
				travel = NULL;
				break;
			}
		}
	}
	return travel;
}
void delete_node(void)
{
// definition
	int del_data;
	bool DEL_FLAG = FALSE;
	tree * ret,*travel,*temp;
	printf("Enter a node_data to delete\n");
	scanf("%d",&del_data);
	ret = search_node(del_data);
	do
	{
		travel = home;
		if(ret != NULL)
		{
			if(ret->right != NULL)
			{
				temp = search_successor(ret);
			}
			else
			{
				temp = search_predecessor(ret);
			}
		}
		else
		{
			printf("node %d not found in the tree !!\n",del_data);
			DEL_FLAG = FALSE;
		}
		// if head is the node to be deleted ,
		if(home == ret)
		{
			tree *x_temp = NULL;
			temp->left = home->left;
			if(temp->right)
			{
				x_temp = temp->right;
			}
			temp->right = home->right;
			home->right->left = x_temp;
			home->left = NULL;
			free(travel);
			home = temp;
			return;
		}
		while(travel->left != ret || travel->right != ret)
		{
			if(travel->left == ret || travel->right == ret)
			{
				break;
			}
			if(travel->data > ret->data)
			{
				travel = travel->left;
			}
			else
			{
				travel = travel->right;
			}
		}


		// if node to be deleted is left child of the travel-node
		if(travel->left == ret)
		{
			// if the node to be deleted is the leaf-node
			if(ret->left == NULL && ret->right == NULL)
			{
				travel->left = NULL;
				free(travel->left);
			}
			else
			{
				free(travel->left);
				travel->left = temp;
			}
			DEL_FLAG = FALSE;
		}
		// if the node to be deleted is right child of the travel-node
		else if(travel->right == ret)
		{
			// if the node to be deleted is the leaf-node
			if(ret->left == NULL && ret->right == NULL)
			{
				travel->right = NULL;
				free(travel->right);
			}
			else
			{
				if(ret->left != NULL)	temp->left = ret->left;
				free(travel->right);
				travel->right = temp;
			}
			DEL_FLAG = FALSE;
		}
		// if head is the node to be deleted ,
		else
		{
			// lets check if this condition is required anymore here !!
		}
	}while(DEL_FLAG);
}

void find_node()
{
	// definition
	int data;
	tree * ret;
	printf("Enter a node_data to search\n");
	scanf("%d",&data);
	ret = search_node(data);
	printf("%d node is found in a tree !!\n",ret->data);
}

void preorder_traverse(tree *start)
{
	tree *temp = start;
	if(temp != NULL)
	{
		while(1)
		{
			while(temp->left != NULL)
			{
				printf("%d ==> ",temp->data);
				if(temp->right != NULL)	push_stack(temp->right);
				temp = temp->left;
			}
			printf("%d ==> ",temp->data);
			if(temp->right != NULL)
			{
				temp = temp->right;
				//printf("%d ==> ",temp->data);
			}
			else
			{
				temp = pop_stack();
				if(temp == NULL)	break;
			}
		}
	}

}

void inorder_traverse(tree *start)
{
		tree *temp = start;
		if(temp != NULL)
		{
			while(1)
			{
				while(temp->left != NULL && FLAG == FALSE)
				{
					push_stack(temp);
					temp = temp->left;
				}
				printf("%d ==> ",temp->data);

				if(temp->right == NULL)
				{
					temp = pop_stack();
					if(temp)	FLAG = TRUE;
					else		FLAG = FALSE;
				}
				else
				{
					temp = temp->right;
					FLAG = FALSE;
				}
				if(FLAG == FALSE && head == NULL && temp->right == NULL)
				{
					printf("%d ==> ",temp->data);
					break;
				}
			}
		}
}

void postorder_traverse(tree *start)
{
	// definition
	printf("This is not yet been implemented !!\n");
}

void push_stack(tree *stack_node)
{
//definition
	stack *temp;
	temp = (stack *)malloc(sizeof(stack));
	temp->next = NULL;
	temp->data = stack_node;
	if(head == NULL)
	{
		head = temp;
	}
	else
	{
		temp->next = head;
		head = temp;
	}
}

tree * pop_stack(void)
{
	// definition
	if(head != NULL)
	{
		stack *temp;
		temp = head;
		head = head->next;
		return temp->data;
	}
	else
	{
		printf("Stack is Empty !!\n");
		return NULL;
	}
}
void inorder_recursive_traverse(tree *start)
{
	if(start == NULL)	return;
	inorder_recursive_traverse(start->left);
	printf("%d ==> ",start->data);
	inorder_recursive_traverse(start->right);
}
void preorder_recursive_traverse(tree *start)
{
	if(start == NULL)	return;
	printf("%d ==> ",start->data);
	preorder_recursive_traverse(start->left);
	preorder_recursive_traverse(start->right);
}
void postorder_recursive_traverse(tree *start)
{
	if(start == NULL)	return;
	postorder_recursive_traverse(start->left);
	postorder_recursive_traverse(start->right);
	printf("%d ==> ",start->data);
}
void find_successor(void)
{
	int search = 0;
	tree * ret,*temp;
	printf("Find a successor of a node ... ??\n");
	scanf("%d",&search);
	temp = home;
	ret = search_node(search);
	if(ret)
	{
		temp = search_successor(ret);
		if(temp)
		{
			printf("%d is the successor of the node !!\n",temp->data);
		}
	}
	else
		printf("Successor of the non-existing node can't be found !!\n");

}

tree * search_successor(tree *ret)
{
	tree *node = NULL ,*temp;
	temp = home;
	if(ret)
	{
		if(ret->right != NULL)
		{
			temp = ret->right;
			while(temp->left != NULL)	temp = temp->left;
			node = temp;
			printf("%d is the successor of the given node !!\n",temp->data);
		}
		else
		{
			while(temp->data != ret->data)
			{
				if(ret->data < temp->data)
				{
					push_stack(temp);
					temp = temp->left;
				}
				if(ret->data > temp->data)
				{
					temp = temp->right;
				}
			}
			// now pop from the stack and this would be the successor of the node...
			temp = pop_stack(); // --> this is the successor
			if(temp != NULL)
			{
				printf("%d is the successor of the given node !!\n",temp->data);
				node = temp;
				while(temp != NULL)
				{
					temp = pop_stack();
				}
			}
			else
				printf("Seems the node is the greatest node of the tree , so no successor !!\n");
		}

	}
return node;
}

void find_predecessor(void)
{
	int search;
	tree * ret, *temp;
	printf("Find the predecessor of the node ?? \n");
	scanf("%d",&search);
	temp = home;
	ret = search_node(search);

	if(ret)
	{
		temp = search_predecessor(ret);
		if(temp)
		{
			printf("%d is the predecessor of  the node !!\n",temp->data);
		}
	}
	else
	{
		printf("Predecessor of non-existing node can't be found!!\n");
	}
}

tree * search_predecessor(tree *ret)
{
	tree *node = NULL ,*temp;
	temp = home;

	if(ret)
	{
		if(ret->left != NULL)
		{
			temp = ret->left;
			while(temp->right != NULL)	temp = temp->right;
			node = temp;
			printf("%d is the predecessor of the given node\n",temp->data);
		}
		else
		{
			temp = home;
			while(temp->data != ret->data)
			{
				if(temp->data > ret->data)
				{
					if(temp->left != NULL)	temp = temp->left;
				}
				else if(temp->data < ret->data)
				{
					push_stack(temp);
					temp = temp->right;
				}
			}
			temp = pop_stack();
			if(temp != NULL)
			{
				printf("%d is the predecessor of the given node\n",temp->data);
				node = temp;
				while(temp != NULL)	temp = pop_stack();
			}
			else
			{
				printf("Seems the node is the smallest node of the tree , so no predecessor !!\n");
			}
		}
	}
	return node;
}

void push_queue(tree *node)
{
	queue *travel = NULL, *temp = NULL;

	travel = (queue *)malloc(sizeof(queue));
	travel->data = node;
	travel->next = NULL;

	if(q_base == NULL)
	{
		q_base = travel;
	}
	else
	{
		temp = q_base;
		while(temp->next != NULL)	temp = temp->next;
		temp->next = travel;
	}
}

tree * unqueue(void)
{
	tree *temp = NULL;

	if(q_base)
	{
		temp = q_base->data;
		q_base = q_base->next;
	}
	else
	{
		printf("Queue is empty now !!\n");
	}

	return temp;
}

void breadth_first_search_traverse(tree *start)
{
	tree * temp = start;
//	if(start != NULL)
	{
		while(temp)
		{
			printf("%d ==> \n",temp->data);
			if(temp->left != NULL)		push_queue(temp->left);
			if(temp->right != NULL)		push_queue(temp->right);
			temp = unqueue();
		}
	}
}


int find_tree_height(tree *traverse)
{
	int height_left = 0, height_right = 0;
	tree * temp = traverse;
	if(temp == NULL)
	{
		return 0;
	}
	else
	{
		if(temp->left)		height_left += find_tree_height(temp->left);
		if(temp->right)		height_right += find_tree_height(temp->right);
	}
	if(height_left > height_right)
	{
		return height_left+1;
	}
	else
	{
		return height_right+1;
	}
}

bool isBalance(tree *start)
{
	int left_ht = 0, right_ht = 0;
	if(start == NULL)	return 1;

	left_ht = find_tree_height(start->left);
	right_ht = find_tree_height(start->right);

	if(abs(left_ht - right_ht) <= 1 && isBalance(start->left) && isBalance(start->right))
	{
		return 1;
	}
	return 0;
}

void treeToarray(tree *start)
{
	tree *temp = start;
	if(temp == NULL)	return ;
	treeToarray(temp->left);
	push_queue(temp);
	treeToarray(temp->right);
}

tree * buildBSTutils(queue *start,int begin,int end)
{
	int i=0;
	queue *temp = start;
	if(begin > end)	return NULL;

	int mid = begin + (end- begin)/2;
	for(i=0;i<mid;i++)
		temp = temp->next;
	tree *bst = temp->data;

	bst->left = buildBSTutils(start,begin,mid-1);
	bst->right = buildBSTutils(start,mid+1,end);

	return bst;
}


void sortToBalancedBST(tree *start)
{
	queue *temp = NULL;
	int counter = 0;
	treeToarray(start);

	temp = q_base;

	while(temp != NULL)
	{
		temp = temp->next;
		counter++;
	}
	home = buildBSTutils(q_base,0,counter-1);
	temp = q_base;
	while(temp != NULL)
	{
		temp = temp->next;
		free(q_base);
		q_base = temp;
	}
	printf("Tree is now balanced but BFS traversal would be different !!\n");
}
