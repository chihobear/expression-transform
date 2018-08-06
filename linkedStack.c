#include<stdio.h>
#include<stdlib.h>
#include"linkedStack.h"
#include"tree.h"

//Push a node into the first position of the linked stack.
void push(struct link_stack **head, struct link_stack *node)
{
	//If the liked stack is empty.
	if(*head == NULL)
	{
		*head = node;
	}
	else
	{
		node->next = *head;
	    *head = node;	
	}
}

/*Pop the first node of the linked stack and return the value of the poped node.
  If the linked stack is empty, do nothing and return -1.*/
struct tree* pop(struct link_stack **head)
{
	struct tree *root = NULL;
	if(*head != NULL)
	{
		struct link_stack *p = *head;
		root = p->root;
		*head = (*head)->next;
		free(p);
	}
	return root;
}

//Print out the linked stack.
void print_linked_stack(struct link_stack *head)
{
	struct link_stack *p;
	p = head;
	while(p != NULL)
	{
		//printf("%d\n", p->number);
		p = p->next;
	}
 }
