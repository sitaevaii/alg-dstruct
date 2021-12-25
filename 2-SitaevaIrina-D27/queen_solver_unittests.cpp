#include "gtest/gtest.h"

extern "C" {
	#include <string.h>
	#include "queen_solver.h"
}

#define OUTPUT_FILENAME "output.txt"
#define CHECK_LINE_LEN 100


TEST(Example_test, test_0){
	int size = 4;
	Cell* ans = queen_task_solver(size);
	print_solve_to_file(ans, size, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	
	char line[CHECK_LINE_LEN] = {0};
	for (int i = 0; i < size; i++)
		fgets(line + strlen(line), CHECK_LINE_LEN, output);
	
	EXPECT_TRUE(strcmp(line, "0 1\n1 3\n2 0\n3 2\n") == 0);
}


TEST(Border_value_test, zero_size_test){
	int size = 0;
	Cell* ans = queen_task_solver(size);
	print_solve_to_file(ans, size, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	
	char line[CHECK_LINE_LEN] = {0};
	
	fgets(line + strlen(line), CHECK_LINE_LEN, output);
	
	EXPECT_TRUE(strcmp(line, "0") == 0);
}

TEST(Border_value_test, one_size_test){
	int size = 1;
	Cell* ans = queen_task_solver(size);
	print_solve_to_file(ans, size, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	
	char line[CHECK_LINE_LEN] = {0};
	
	for (int i = 0; i < size; i++)
		fgets(line + strlen(line), CHECK_LINE_LEN, output);
	
	EXPECT_TRUE(strcmp(line, "0") == 0);
}

TEST(Border_value_test, two_size_test){
	int size = 1;
	Cell* ans = queen_task_solver(size);
	print_solve_to_file(ans, size, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	
	char line[CHECK_LINE_LEN] = {0};
	
	for (int i = 0; i < size; i++)
		fgets(line + strlen(line), CHECK_LINE_LEN, output);
	
	EXPECT_TRUE(strcmp(line, "0") == 0);
}

TEST(Border_value_test, three_size_test){
	int size = 1;
	Cell* ans = queen_task_solver(size);
	print_solve_to_file(ans, size, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	
	char line[CHECK_LINE_LEN] = {0};
	
	for (int i = 0; i < size; i++)
		fgets(line + strlen(line), CHECK_LINE_LEN, output);
	
	EXPECT_TRUE(strcmp(line, "0") == 0);
}

TEST(Solving_test, five_size_test){
	int size = 5;
	Cell* ans = queen_task_solver(size);
	print_solve_to_file(ans, size, OUTPUT_FILENAME);
	
	FILE* output = fopen(OUTPUT_FILENAME, "r");
	
	char line[CHECK_LINE_LEN] = {0};
	
	for (int i = 0; i < size; i++)
		fgets(line + strlen(line), CHECK_LINE_LEN, output);
	
	EXPECT_TRUE(strcmp(line, "0 0\n1 2\n2 4\n3 1\n4 3\n") == 0);
}
