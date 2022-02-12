#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include "RedBlackTree.h"
#define Y_OFFSET 2
#define X_OFFSET 12

RB_tree* RBTreeInit() {
	RB_tree* tree = malloc(sizeof(RB_tree));
	if (tree != NULL) {
		tree->root = NULL;
	}
	return tree;
}


void LeftRotate(RB_tree* tree, RB_node* father) {
	if (father == NULL) {
		return;
	}
	RB_node* r_child = NULL;
	if (father->right != NULL) {
		r_child = father->right;
		father->right = r_child->left;
		if (r_child->left != NULL) {
			r_child->left->parent = father;
		}
	}
	if (r_child != NULL) {
		r_child->parent = father->parent;
		r_child->left = father;
	}
	if (father->parent != NULL) {
		if (father == father->parent->left)
			father->parent->left = r_child;
		else
			father->parent->right = r_child;
	}
	else {
		tree->root = r_child;
	}
	father->parent = r_child;
}


void RightRotate(RB_tree* tree, RB_node* father) {
	if (father == NULL) {
		return;
	}
	RB_node* l_child = NULL;
	if (father->left != NULL) {
		l_child = father->left;
		father->left = l_child->right;
		if (l_child->right != NULL) {
			l_child->right->parent = father;
		}
	}
	if (l_child != NULL) {
		l_child->parent = father->parent;
		l_child->right = father;
	}
	if (father->parent != NULL) {
		if (father == father->parent->right)
			father->parent->right = l_child;
		else
			father->parent->left = l_child;
	}
	else {
		tree->root = l_child;
	}
	father->parent = l_child;
}


void InsertFixup(RB_tree* tree, RB_node* node) {
	while (node != NULL && node != tree->root && node->parent != NULL && node->parent->color == RED && node->parent->parent != NULL) {
		if (node->parent == node->parent->parent->left) {
			RB_node* r_brother_of_parent = node->parent->parent->right;
			if (r_brother_of_parent != NULL && r_brother_of_parent->color == RED) {
				node->parent->color = BLACK;
				r_brother_of_parent->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->right) {
					node = node->parent;
					LeftRotate(tree, node);
				}
				if (node->parent != NULL) {
					node->parent->color = BLACK;
					node->parent->parent->color = RED;
					RightRotate(tree, node->parent->parent);
				}
			}
		}
		else {
			RB_node* l_brother_of_parent = node->parent->parent->left;
			if (l_brother_of_parent != NULL && l_brother_of_parent->color == RED) {
				node->parent->color = BLACK;
				l_brother_of_parent->color = BLACK;
				node->parent->parent->color = RED;
				node = node->parent->parent;
			}
			else {
				if (node == node->parent->left) {
					node = node->parent;
					RightRotate(tree, node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				LeftRotate(tree, node->parent->parent);
			}
		}
	}
	if (tree->root != NULL) {
		tree->root->color = BLACK;
	}

}


int InsertNode(RB_tree* tree, int data) {
	RB_node* parent = NULL;
	RB_node* current = tree->root;
	while (current != NULL) {
		if (data == current->data) {
			return 1;
		}
		parent = current;
		current = data < current->data ? current->left : current->right;
	}
	RB_node* node = malloc(sizeof(RB_node));
	if (node == NULL) {
		puts("malloc node error");
		return 0;
	}
	node->parent = parent;
	node->left = NULL;
	node->right = NULL;
	node->data = data;
	node->color = RED;
	if (parent != NULL) {
		if (data < parent->data) {
			parent->left = node;
		}
		else {
			parent->right = node;
		}
	}
	else {
		tree->root = node;
	}
	InsertFixup(tree, node);
	return 1;
}


void DeleteFixup(RB_tree* tree, RB_node* node) {
	while (node != tree->root && node->color == BLACK) {
		if (node->parent->right != NULL && node == node->parent->left) {
			RB_node* w = node->parent->right;
			//Case 1
			if (w->color == RED) {
				w->color = BLACK;
				node->parent->color = RED;
				LeftRotate(tree, node->parent);
				w = node->parent->right;
			}
			//Case 2
			if (w->left != NULL && w->right != NULL && w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				node = node->parent;
			}
			else {
				//Case 3
				if (w->left != NULL && w->right != NULL && w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(tree, w);
					w = node->parent->right;
				}
				//Case 4
				if (w->right != NULL) {
					w->color = node->parent->color;
					node->parent->color = BLACK;
					w->right->color = BLACK;
					LeftRotate(tree, node->parent);
				}
				node = tree->root;
			}
		}
		else if (node->parent->left != NULL) {
			RB_node* w = node->parent->left;
			//Case 1
			if (w->color == RED) {
				w->color = BLACK;
				node->parent->color = RED;
				RightRotate(tree, node->parent);
				w = node->parent->left;
			}
			//Case 2
			if (w->left != NULL && w->right != NULL && w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				node = node->parent;
			}
			else {
				//Case 3
				if (w->left != NULL && w->right != NULL && w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(tree, w);
					w = node->parent->left;
				}
				//Case 4
				if (w->left != NULL) {
					w->color = node->parent->color;
					node->parent->color = BLACK;
					w->left->color = BLACK;
					RightRotate(tree, node->parent);
				}
				node = tree->root;
			}
		}
	}
	node->color = BLACK;
}


void DeleteNode(RB_tree* tree, int data) {
	RB_node* current = tree->root;
	RB_node* del_node = NULL;
	while (current != NULL) {
		if (data == current->data) {
			del_node = current;
			break;
		}
		else {
			current = data < current->data ? current->left : current->right;
		}
	}
	if (del_node == NULL) {
		return;
	}
	RB_node* exchange_node;
	if (del_node->left == NULL || del_node->right == NULL) {
		exchange_node = del_node;
	}
	else {
		exchange_node = del_node->right;
		while (exchange_node->left != NULL) {
			exchange_node = exchange_node->left;
		}
	}
	RB_node* exchange_node_child;
	if (exchange_node->left != NULL) {
		exchange_node_child = exchange_node->left;
	}
	else {
		exchange_node_child = exchange_node->right;
	}

	if (exchange_node_child != NULL) {
		exchange_node_child->parent = exchange_node->parent;
	}
	if (exchange_node->parent != NULL) {
		if (exchange_node == exchange_node->parent->left) {
			exchange_node->parent->left = exchange_node_child;
		}
		else {
			exchange_node->parent->right = exchange_node_child;
		}
	}
	else {
		tree->root = exchange_node_child;
	}
	if (exchange_node != del_node) {
		del_node->data = exchange_node->data;
	}

	if (exchange_node->color == BLACK && exchange_node_child != NULL) {
		//exchange_node_child->color = BLACK; // added
		DeleteFixup(tree, exchange_node_child);
	}
	if (exchange_node != NULL) {
		free(exchange_node);
	}

}


void FindNode(RB_tree* tree, int data) {
	RB_node* current = tree->root;
	while (current != NULL) {
		if (data == current->data) {
			puts("yes");
			return;
		}
		else {
			current = data < current->data ? current->left : current->right;
		}
	}
	puts("no");
}


int CalcBlackHeight(RB_tree* tree) {
	RB_node* current = tree->root;
	int n = 0;
	while (current != NULL) {
		if (current->color == BLACK) {
			n++;
		}
		current = current->left;
	}
	return n;
}


RB_node* find(RB_tree* tree, int h) {
	int curBH = CalcBlackHeight(tree);
	RB_node* current = tree->root;
	while (curBH != h) {
		current = current->right;
		if (current->color == BLACK) {
			curBH--;
		}
	}
	return current;
}


RB_node* JoinToRight(RB_tree* tree_1, RB_tree* tree_2, RB_tree* merged_tree, int x, int height_1, int height_2) {
	RB_node* Y = find(tree_1, height_2);
	InsertNode(merged_tree, x);
	merged_tree->root->left = Y;
	merged_tree->root->right = tree_2->root;
	merged_tree->root->color = RED;
	Y->parent->right = merged_tree->root;
	InsertFixup(tree_1, Y->parent->right);
	return tree_1->root;
}


void Merge(RB_tree* tree_1, RB_tree* tree_2, RB_tree* merged_tree, int x) {
	int height_1 = CalcBlackHeight(tree_1);
	int height_2 = CalcBlackHeight(tree_2);
	if (height_1 == height_2) {
		InsertNode(merged_tree, x);
		merged_tree->root->left = tree_1->root;
		merged_tree->root->right = tree_2->root;
	}
	else if (height_1 > height_2) {
		merged_tree->root = JoinToRight(tree_1, tree_2, merged_tree, x, height_1, height_2);
	}
}


void SetPos(int x, int y) {
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}


int x = 1;
int offset_right = X_OFFSET / 2;
int offset_left = X_OFFSET / 2;
void printRightLines(int y, int local_x) {
	for (int i = 1; i < 2; i++){
		SetPos(local_x + X_OFFSET /2, y-i);
		printf("%c", '|');
	}
	for (int i = 1; i < offset_right - 1; i++) {
		SetPos(local_x + X_OFFSET / 2 + i, y- 2);
		printf("%c", '_');
	}
	
}
void printLeftLines(int y, int local_x) {
	for (int i = 1; i < 2; i++) {
		SetPos(local_x , y - i); //+ X_OFFSET / 2
		printf("%c", '|');
	}
	for (int i = 1; i < offset_left - 2 - offset_right - X_OFFSET / 2; i++) {
		SetPos(local_x - i, y - 2);
		printf("%c", '_');
	}

}
//void _printTree(RB_node* node, int y) {
//	if (node != NULL) {
//		_printTree(node->left, y + Y_OFFSET);
//		SetPos(x, y);
//		printf("%i | %s", node->data, node->color == BLACK ? "BLACK" : "RED");
//		x += X_OFFSET;
//		_printTree(node->right, y + Y_OFFSET);
//	}
//}
void _printTree(RB_node* node, int y) {
	if (node != NULL) {
		_printTree(node->left, y + Y_OFFSET);
		SetPos(x, y);
		printf("%i | %s", node->data, node->color == BLACK ? "BLACK" : "RED");	
		int local_x = x;
		/*int local_r_of = 0;
		if (node->right != NULL) {
			local_r_of += X_OFFSET;
		}*/
		x += X_OFFSET;		
		_printTree(node->right, y + Y_OFFSET);
		if (node->parent != NULL && node->parent->left == node) { // переделать if
			printRightLines(y, local_x);
			//offset_left += X_OFFSET;
		}
		else if (node->parent != NULL){
			//printLeftLines(y, local_r_of);
			offset_right += X_OFFSET;
		}
	}
}


void PrintTree(RB_tree* tree, int start_y_pos) {
	_printTree(tree->root, start_y_pos);
	x = 1;
}