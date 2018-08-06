#ifndef FLAG1
#define FLAG1
#include"tree.h"
struct link_stack{
	struct tree *root;
	struct link_stack *next;
};

void push(struct link_stack **head, struct link_stack *node);

struct tree* pop(struct link_stack **head);

void print_linked_stack(struct link_stack *head);
#endif
