#pragma once
typedef enum {
	RED,
	BLACK
}color;
typedef struct RB_node {
	struct RB_node* parent;
	struct RB_node* left;
	struct RB_node* right;
	int data;
	color color;
}RB_node;
typedef struct RB_tree {
	struct RB_node* root;
}RB_tree;
RB_tree* RBTreeInit();
int InsertNode(RB_tree* tree, int data);
void DeleteNode(RB_tree* tree, int data);
void FindNode(RB_tree* tree, int data);
void Merge(RB_tree* tree_1, RB_tree* tree_2, RB_tree* merged_tree, int x);
void PrintTree(RB_tree* tree, int start_y_pos);
void SetPos(int x, int y);
int TreeHeight(RB_node* root);