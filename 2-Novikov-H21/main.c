#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
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
	while (node != NULL && node != tree->root && node->parent->color == RED && node->parent->parent != NULL) {
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
					RightRotate(tree,node);
				}
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				LeftRotate(tree,node->parent->parent);
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
	RB_node* node = malloc(sizeof(RB_node)); // add check
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
				LeftRotate(tree,node->parent);
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
					RightRotate(tree,w);
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
		else if(node->parent->left != NULL){
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
					LeftRotate(tree,w);
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
	if (exchange_node->left != NULL){
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
	else{
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


void Merge(RB_tree* tree_1, RB_tree* tree_2, int x) {

}


void SetPos(int x, int y){
	COORD c;
	c.X = x;
	c.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int x = 1;
void PrintTree(RB_node* node, int y){
	if (node != NULL){
		PrintTree(node->left, y + 2);
		SetPos(x, y);
		printf("%i | %s", node->data, node->color == BLACK ? "BLACK" : "RED");
		x += 15;
		PrintTree(node->right, y + 2);
	}
}


int main() {
	RB_tree* tree = RBTreeInit();
	if (tree == NULL) {
		puts("tree init error");
		return 0;
	}
	char mode;
	int value;
	int exit_flag = 0;
	int n = 0;
	while (exit_flag == 0 && scanf("%c %i", &mode, &value) >= 1) {
		n++;
		switch (mode) {
		case 'a':
			if (!InsertNode(tree, value)) {
				return 0;
			}
			break;
		case 'r':
			DeleteNode(tree, value);
			break;
		case 'f':
			FindNode(tree, value);
			break;
		case 'p':
			PrintTree(tree->root, n / 2 + 1);
			break;
		case 'q':
			exit_flag = 1;
			break;
		}
	}
	//PrintTree(tree->root, n/2+1);
	free(tree);


	return 0;
}