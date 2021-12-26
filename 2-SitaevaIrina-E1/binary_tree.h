#ifndef GRAF_H
#define GRAF_H

typedef struct BinNode{
	int value;
	int diff;
	struct BinNode* left;
	struct BinNode* right;
} BinNode;

void bin_insert(BinNode** tree, int val);
int bin_search(BinNode* tree, int val);
void bin_remove(BinNode** tree, int val);
void bin_print(BinNode* tree);

#endif
