#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
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


void LeftRotate(RB_tree* tree, RB_node* father) {
	RB_node* r_child = father->right;

	father->right = r_child->left;
	if (r_child->left != NULL) { 
		r_child->left->parent = father; 
	}

	if (r_child != NULL) {
		r_child->parent = father->parent;
		r_child->left = father; // Возможно очибка здесь
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

	if (father != NULL) {
		father->parent = r_child;
	}
}


void RightRotate(RB_tree* tree, RB_node* father) {
	RB_node* l_child = father->left;

	father->left = l_child->right;
	if (l_child->right != NULL) {
		l_child->right->parent = father;
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

	if (father != NULL) {
		father->parent = l_child;
	}
}


void InsertFixup(RB_tree* tree, RB_node* node) {
	while (node != tree->root && node->parent->color == RED) {
		if (node->parent == node->parent->parent->left) {
			RB_node* r_brother_of_parent = node->parent->parent->right; // Возможно тут нужна проверка, если дяди нет
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
				node->parent->color = BLACK;
				node->parent->parent->color = RED;
				RightRotate(tree, node->parent->parent);
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
	tree->root->color = BLACK;
}


void AddNode(RB_tree* tree, int data) {
	RB_node* parent = NULL;
	RB_node* current = tree->root;
	while (current != NULL) {
		if (data == current->data) {
			return;
		}	
		parent = current;
		current = data < current->data ? current->left : current->right;
	}
	RB_node* node = malloc(sizeof(RB_node)); // add check
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
}


void DeleteFixup(RB_tree* tree, RB_node* node) {
	while (node != tree->root && node->color == BLACK) {
		if (node == node->parent->left) {
			RB_node* w = node->parent->right;
			//Case 1
			if (w->color == RED) {
				w->color = BLACK;
				node->parent->color = RED;
				LeftRotate(tree,node->parent);
				w = node->parent->right;
			}
			//Case 2
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				node = node->parent;
			}
			else {
				//Case 3
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					RightRotate(tree,w);
					w = node->parent->right;
				}
				//Case 4
				w->color = node->parent->color;
				node->parent->color = BLACK;
				w->right->color = BLACK;
				LeftRotate(tree,node->parent);
				node = tree->root;
			}
		}
		else {
			RB_node* w = node->parent->left;
			//Case 1
			if (w->color == RED) {
				w->color = BLACK;
				node->parent->color = RED;
				RightRotate(tree, node->parent);
				w = node->parent->left;
			}
			//Case 2
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				node = node->parent;
			}
			else {
				//Case 3
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					LeftRotate(tree,w);
					w = node->parent->left;
				}
				//Case 4
				w->color = node->parent->color;
				node->parent->color = BLACK;
				w->left->color = BLACK;
				RightRotate(tree,node->parent);
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
	else {
		tree->root = exchange_node_child;
	}
	// мб добавить проверку
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


RB_tree* RBTreeInit() {
	RB_tree* tree = malloc(sizeof(RB_tree));
	tree->root = NULL;
	return tree;
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


int main() {
	RB_tree* tree = RBTreeInit();
	char mode;
	int value;
	while (scanf("%c %i", &mode, &value) >= 1) {
		switch (mode) {
		case 'a':
			AddNode(tree, value);
			break;
		case 'r':
			DeleteNode(tree, value);
			break;
		case 'f':
			FindNode(tree, value);
			break;
		}
	}
	free(tree);

	return 0;
}