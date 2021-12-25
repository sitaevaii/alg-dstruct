#ifndef QUEEN_SOLVER_H
#define QUEEN_SOLVER_H

typedef struct{
	int row;
	int colomn;
} Cell;

Cell* queen_task_solver(unsigned size);
void print_solve_to_file(Cell* solve, unsigned board_size, const char* filename);

#endif
