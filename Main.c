/*
 * Main.c
 *
 *  Created on: 07-Aug-2017
 *      Author: d
 */
#include<stdio.h>

int main()
{
	unsigned int choice;
	int ret;
	printf("1. Normal Binary search Tree  and traversal !!\n");
	printf("2. Balanced binary search tree !! \n");

	scanf("%d",&choice);

	switch(choice)
	{
	case 1:
		ret = tree_main();
		break;
	case 2:
		ret = AVL_tree_main();
		break;
	default:
		printf("Invalid input \n");
		break;

	}
return 0;
}

