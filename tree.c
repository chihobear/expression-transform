#include<stdio.h>
#include"tree.h"
//Add a tree as a left child into another tree.
void add_lf(struct tree *parent, struct tree *lf)
{
	parent->lf = lf;
}

//Add a tree as a right child into another tree.
void add_rg(struct tree *parent, struct tree *rg)
{
	parent->rg = rg;
}

//Print out the tree in inorder traversal.
void print_tree(struct tree *root)
{
	if(root->lf == NULL && root->rg == NULL)
	{
		printf("%s", root->str);
		return;
	}
	printf("(");
	print_tree(root->lf);
	printf(" %s ", root->str);
	print_tree(root->rg);
	printf(")");
}
