#ifndef FLAG
#define FLAG
struct tree{
	char *str;
	struct tree *lf;
	struct tree *rg;
};

void add_lf(struct tree *parent, struct tree *lf);

void add_rg(struct tree *parent, struct tree *rg);

void print_tree(struct tree *root);
#endif
