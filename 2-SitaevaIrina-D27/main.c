#include <stdio.h>

#include "queen_solver.h"

int main(){
	unsigned size;
	fscanf(stdin, "%u", &size);
	
	Cell* ans = queen_task_solver(size);
	
	for (unsigned i = 0; i < size; i++)
		fprintf(stdout, "%u %u\n", ans[i].row, ans[i].colomn);
	
	return 0;
}







