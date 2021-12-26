#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "binary_tree.h"


static int bin_height_diff(BinNode* node){
	if (node == NULL)
		return 0;
	
	if (node->left == NULL && node->right == NULL)
		return 1;
		
	node->diff = bin_height_diff(node->left) - bin_height_diff(node->right);
	return abs(node->diff) + 1;
}

static void bin_insert_node(BinNode** tree, BinNode* new_node){

	if (new_node == NULL)
		return;

	if (tree == NULL || (*tree) == NULL){
		*tree = new_node;
		return;
	}
	
	BinNode* node = *tree;

	while(node != NULL){
		if (new_node->value < node->value){
			if (node->left == NULL){
				node->left = new_node;
				break;
			}
			else{
				node = node->left;
			}
		}
		else if (new_node->value == node->value){
			free(new_node);
			break;
		}
		else{
			if (node->right == NULL){
				node->right = new_node;
				break;
			}
			else{
				node = node->right;
			}
		}
	}
	
	bin_height_diff(*tree);
}

void bin_insert(BinNode** tree, int val){

	BinNode* new_node = (BinNode*)malloc(sizeof(BinNode));
	if (new_node == NULL)
			return;

	new_node->value = val;
	new_node->left = NULL;
	new_node->right = NULL;
	new_node->diff = 0;


	bin_insert_node(tree, new_node);
}


int bin_search(BinNode* tree, int val){
	BinNode* node = tree;

	while(node != NULL){
		if (val < node->value){
			node = node->left;
		}
		else if (val == node->value){
			return 1;
		}
		else{
			node = node->right;
		}
	}
	return 0;
}


void bin_remove(BinNode** tree, int val){
	BinNode* node = *tree;
	BinNode* parent = node;
	int leaf_left_flag = 1;

	while(node != NULL){
		if (val < node->value){
			parent = node;
			leaf_left_flag = 1;
			node = node->left;
		}
		else if (val == node->value){
			if (node == *tree){
				if ((*tree)->right != NULL){
					node = (*tree)->left;
					(*tree) = (*tree)->right;
					bin_insert_node(tree, node);
				}
				else{
					(*tree) = (*tree)->left;
				}
				return;
			}

			if (leaf_left_flag)
				parent->left = NULL;
			else
				parent->right = NULL;

			bin_insert_node(tree, node->left);
			bin_insert_node(tree, node->right);
			free(node);
			return;
		}
		else{
			parent = node;
			leaf_left_flag = 0;
			node = node->right;
		}
	}
	bin_height_diff(*tree);
}

static void _bin_print(BinNode* node, int n){
	if (node != NULL) {
        _bin_print(node->right, n + 2);
        for (int i = 0; i < n; i++) {
            putchar('\t');
        }
        printf("<%d (diff: %d)>", node->value, node->diff);
        printf("\n");
        _bin_print(node->left, n + 2);
    }
}

void bin_print(BinNode* node){
	_bin_print(node, 0);
}
