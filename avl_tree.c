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

void add_avl_node(void);

typedef struct tnode{
	struct tree *left;
	struct tree *right;
	int data;
	int height;
}avl_tree;

avl_tree *avl_home = NULL;
int AVL_tree_main(void)
{
	unsigned int choice = 0;
	while(1)
	{
		printf("\n");
		printf("1. Add a node 	    				AVL tree\n");
		printf("2. Delete a node 					AVL tree\n");
		printf("3. Find a node		 				AVL tree\n");
		printf("4. Inorder Traversal 				AVL tree\n");
		printf("5. Preorder traversal 				AVL tree\n");
		printf("6. Postorder traversal 				AVL tree\n");
		printf("7. inOrder Recursive traversal 		AVL tree\n");
		printf("8. Preorder Recursive traversal 	AVL tree\n");
		printf("9. Postorder Recursivetraversal 	AVL tree\n");
		printf("10. Find Successor 					AVL tree\n");
		printf("11. Find Predecessor 				AVL tree\n");
		printf("12. Breadth first traversal 		AVL tree\n");
		printf("13. Find the height of the tree  	AVL tree\n");
		printf("14. Check if tree is balanced 		AVL tree\n");
		printf("0. Exit 							AVL tree\n");

		scanf("%d",&choice);

		switch(choice)
		{
		case 1:
			add_avl_node();
			break;
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
		case 7:
			break;
		case 8:
			break;
		case 9:
			break;
		case 10:
			break;
		case 11:
			break;
		case 12:
			break;
		case 13:
			break;
		case 14:
			break;
		default:
			break;
		}
	}
return 0;
}

void add_avl_node(void)
{
	int data = 0;
	avl_tree *temp,*travel;
	printf("Enter data for AVL tree (-1 to exit)\n");

	while(1)
	{
		if(data == -1)	break;
		else
		{
			temp = (avl_tree *)malloc(sizeof(avl_tree));
			temp->data = data;
			temp->height = 1; // default height to be 1
			temp->left = temp->right = NULL;
			if(avl_home == NULL)
			{
				avl_home = (avl_tree *)malloc(sizeof(avl_tree));
				avl_home = temp;
			}
			else
			{

			}
		}
	}
}
