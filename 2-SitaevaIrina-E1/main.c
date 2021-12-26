#pragma warning (disable:4996)
#define _CRT_SECURE_NO_WORNINGS

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree.h"


int main(){
	char command;
	int value;

	BinNode* tree = NULL;

	while (scanf("%c", &command) >= 1){
		if (command != 'p' && command != 'q')
			scanf("%i", &value);
		switch(command){
			case 'a':
				bin_insert(&tree, value);
				break;
			case 'r':
				bin_remove(&tree, value);
				break;
			case 'f':
				if (bin_search(tree, value))
					puts("yes");
				else
					puts("no");
				break;
			case 'p':
				bin_print(tree);
				break;
			case 'q':
				return 0;
				break;
		}
	}

	return 0;
}
