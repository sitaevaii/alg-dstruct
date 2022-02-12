#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "RedBlackTree.h"


void AddFindDeleteTest() {
	RB_tree* tree = RBTreeInit();
	if (tree == NULL) {
		puts("tree init error");
		return;
	}
	char mode;
	int value;
	while (scanf("%c %i", &mode, &value) >= 1) {
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
		}
	}
}


void MergeTest() {
	RB_tree* tree_1 = RBTreeInit();
	if (tree_1 == NULL) {
		puts("tree init error");
		return 0;
	}
	RB_tree* tree_2 = RBTreeInit();
	if (tree_2 == NULL) {
		puts("tree init error");
		return 0;
	}
	RB_tree* merged_tree = RBTreeInit();
	if (merged_tree == NULL) {
		puts("tree init error");
		return 0;
	}
	char mode;
	int value;
	int exit_flag;
	int y_offset = 0;
	int x = 10;
	for (int i = 0; i < 2; i++){
		exit_flag = 0;
		RB_tree* tree = i == 0 ? tree_1 : tree_2;
		while (exit_flag == 0 && scanf("%c %i", &mode, &value) >= 1) {
			y_offset++;
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
				PrintTree(tree, y_offset / 2 + 1);
				exit_flag = 1;
				puts("");
				break;
			}
		}
		y_offset += y_offset / 2 + 1;
		// calc deepest
	}
	Merge(tree_1, tree_2, merged_tree, x);
	PrintTree(merged_tree, y_offset );
}


int main() {
	//MergeTest();
	RB_tree* tree = RBTreeInit();
	if (tree == NULL) {
		puts("tree init error");
		return;
	}
	char mode;
	int value;
	int y_offset = 0;
	y_offset++;
	while (scanf("%c %i", &mode, &value) >= 1) {
		y_offset++;
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
			PrintTree(tree, y_offset / 2 + 1);
		}
	}
	return 0;
}