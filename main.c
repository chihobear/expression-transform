/*
*  Project: jdec
*  Author: Chenghao Xiong
*  Purpose: Modify a JVM Decompiler
*  Example input: iload var
                  iconst 1
                  iadd
                  iconst 2
                  isub
                  iload num
                  imul
                  iconst 3
                  idiv
*  Example output: ((((var + 1) - 2) * num) / 3)
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"linkedStack.h"
#include"tree.h"

#define PROCESS_OPERANDS(argument)  rg = pop(&head);\
									lf = pop(&head);\
									if(rg == NULL || lf == NULL)\
									{\
										fprintf(stderr, "The expression is errorneous!\n");\
										exit(1);\
									}\
									parent = (struct tree*)malloc(sizeof(struct tree));\
									parent->str = (char*)malloc(sizeof(char) + 1);\
									parent->str[0] = argument;\
									parent->str[1] = '\0';\
									add_lf(parent, lf);\
									add_rg(parent, rg); \
									p = (struct link_stack*)malloc(sizeof(struct link_stack));\
									p->root = parent;\
									p->next = NULL;\
									push(&head, p);
int check_string_letter(char *str);
									
int main() {
	struct tree *lf = NULL, *rg = NULL, *parent = NULL;
	struct link_stack *head = NULL, *p = NULL;
	int trigger = 0, operand_num = 0;
	char *line = NULL, *tok = NULL, *ptr = NULL;
	char operands[5] = "+-*/";
	size_t len = 0;
	
	//Read in one line.
	while(getline(&line, &len, stdin) != EOF)
	{
		trigger = 0;
		operand_num = 0;
		ptr = line;
		//Get strings separated by blank spaces.
		while(tok = strtok(ptr, " \t\n"), tok != NULL)
		{
			ptr = NULL;
			//If the string is command "iload", set "trigger" to 1. Add one to operand numbers processed.
			if(strcmp("iload", tok) == 0)
			{
				trigger = 1;
				operand_num++;
			}
			//If the string is command "iconst", set "trigger" to 2. Add one to operand numbers processed.
			else if(strcmp("iconst", tok) == 0)
			{
				trigger = 2;
				operand_num++;
			}
			/*
			*  If the string is command "+ - * /", add one to operand numbers processed and process.
			*  Process: Pop out two trees in the stack and add them as children to a new tree of which content is the symbol.
			*           Then push this new treee into the stack. If there are no two tree in the stack to be pushed, print the error and exit. 
			*/
			else if(strcmp("iadd", tok) == 0)
			{
				operand_num++;
				PROCESS_OPERANDS(operands[0]);
			}
			else if(strcmp("isub", tok) == 0)
			{
				operand_num++;
				PROCESS_OPERANDS(operands[1]);
			}
			else if(strcmp("imul", tok) == 0)
			{
				operand_num++;
				PROCESS_OPERANDS(operands[2]);
			}
			else if(strcmp("idiv", tok) == 0)
			{
				operand_num++;
				PROCESS_OPERANDS(operands[3]);
			}
			else
			{
				//If the command "iload" or "iconst" has been read in.
				if(trigger == 1 || trigger == 2)
				{
					if(trigger == 1)
					{
						//If the command is "iload", check the string.
						if(check_string_letter(tok) == 1)
						{
							fprintf(stderr, "The string should consist of letters\n");
							exit(1);
						}
					}
					if(trigger == 2)
					{
						//If the command is "iconst", check the string.
						if(strspn(tok, "0123456789") != strlen(tok))
						{
							fprintf(stderr, "The string should be a number\n");
							exit(1);
						}
					}
					//Creat a new tree of which content is the string. And push it into the stack.
					parent = (struct tree*)malloc(sizeof(struct tree));
					parent->str = strdup(tok);
					parent->lf = NULL;
					parent->rg = NULL;
					p = (struct link_stack*)malloc(sizeof(struct link_stack));
					p->root = parent;
					p->next = NULL;
					push(&head, p);
				}
				//If the string is none of the commands and the strings that should be in the tree.
				else
				{
					fprintf(stderr, "Error symbol!\n");
					exit(1);
				}
			}
		}
		//If there are more than one commands in a line.
		if(operand_num > 1)
		{
			fprintf(stderr, "Too many operands one line!\n");
			exit(1);
		}
	}
	if(head == NULL)
	{
		return 0;
	}
	//When all commands are processed, if there are more than one elements in the stack, report this error.
	if(head->next != NULL)
	{
		fprintf(stderr, "The expression is errorneous!\n");
		exit(1);
	}
	//Print out the expression.
	print_tree(head->root);
	printf("\n");
	return 0;
}

//If a string contains more than letters, return 1. Otherwise, return 0.
int check_string_letter(char *str)
{
	int number = strlen(str);
	int i = 0;
	for(i = 0;i < number;i++)
	{
		if(str[i] < 'A' || str[i] > 'z' || (str[i] > 'Z' && str[i] < 'a'))
		{
			return 1;
		}
	}
	return 0;
}
