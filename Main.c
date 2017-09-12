/*
 * Main.c
 *
 *  Created on: 07-Aug-2017
 *      Author: d
 */
#include<stdio.h>
int tree_main(void);
int AVL_tree_main(void);
int main()
{
	unsigned int choice;
	printf("1. Normal Binary search Tree  and traversal !!\n");
	printf("2. Balanced binary search tree !! \n");

	scanf("%d",&choice);

	switch(choice)
	{
	case 1:
		tree_main();
		break;
	case 2:
		AVL_tree_main();
		break;
	default:
		printf("Invalid input \n");
		break;

	}
return 0;
}

