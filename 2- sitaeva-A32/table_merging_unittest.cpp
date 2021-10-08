#include "gtest/gtest.h"


extern "C" {
#include <stdlib.h>
#include "table_merge.h"
}

#define TABLE_1_FILE_NAME "test_table_1"
#define TABLE_2_FILE_NAME "test_table_2"
#define FINAL_TABLE_NAME "test_output"
#define TEST_LINE_LENGTH 50


TEST(tables_merging_testing_first_colomn_simple_key, empty_tables_merge){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	fclose(table1);
	fclose(table2);
	
	table_merge(0, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	EXPECT_EQ(getc(final_table), EOF);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
}

TEST(tables_merging_testing_first_colomn_simple_key, first_empty_table_merge){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table2, "1\n" \
					"2\n" \
					"3\n");
	fclose(table1);
	fclose(table2);
	
	table_merge(0, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[TEST_LINE_LENGTH];
	memset(line,'\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "1\n"), 0);

	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "2\n"), 0);

	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "3\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
}

TEST(tables_merging_testing_first_colomn_simple_key, second_empty_table_merge){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "1\n" \
					"2\n" \
					"3\n");
	fclose(table1);
	fclose(table2);
	
	table_merge(0, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[TEST_LINE_LENGTH];
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "1\n"), 0);

	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "2\n"), 0);

	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "3\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}

TEST(tables_merging_testing_first_colomn_simple_key, both_one_line_table_merge_first_greater){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "1\n");
	fprintf(table2, "2\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(0, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[TEST_LINE_LENGTH];

	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "1\n"), 0);

	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "2\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}


TEST(tables_merging_testing_first_colomn_simple_key, both_one_line_table_merge_second_greater){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "2\n");
	fprintf(table2, "1\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(0, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[TEST_LINE_LENGTH];
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "1\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "2\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}

TEST(tables_merging_testing_first_colomn_simple_key, both_one_line_table_merge_equal_lines){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "1\n");
	fprintf(table2, "1\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(0, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[TEST_LINE_LENGTH];
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "1\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "1\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}

TEST(tables_merging_testing_first_colomn_simple_key, multy_line_table_merge_intersection){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "1\n" \
					"3\n");
	
	fprintf(table2, "2\n" \
					"4\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(0, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[TEST_LINE_LENGTH];
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "1\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "2\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "3\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "4\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}

TEST(tables_merging_testing_first_colomn_simple_key, multy_line_table_merge_intersection_with_equals){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "1\n" \
					"3\n");
	
	fprintf(table2, "3\n" \
					"4\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(0, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[TEST_LINE_LENGTH];
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "1\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "3\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "3\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 2, final_table);
	EXPECT_EQ(strcmp(line, "4\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}

TEST(tables_merging_testing_second_colomn_simple_key, multy_line_table_merge_intersection){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "9,1\n" \
					"8,3\n");
	
	fprintf(table2, "7,2\n" \
					"6,4\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(1, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[TEST_LINE_LENGTH];
	
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 4, final_table);
	EXPECT_EQ(strcmp(line, "9,1\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 4, final_table);
	EXPECT_EQ(strcmp(line, "7,2\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 4, final_table);
	EXPECT_EQ(strcmp(line, "8,3\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 4, final_table);
	EXPECT_EQ(strcmp(line, "6,4\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}

TEST(tables_merging_testing_second_colomn_simple_key,
	 multy_line_table_merge_intersection_with_equal_lines){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "9,1\n" \
					"7,3\n");
	
	fprintf(table2, "7,2\n" \
					"7,3\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(1, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[TEST_LINE_LENGTH];
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 4, final_table);
	EXPECT_EQ(strcmp(line, "9,1\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 4, final_table);
	EXPECT_EQ(strcmp(line, "7,2\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 4, final_table);
	EXPECT_EQ(strcmp(line, "7,3\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fread(line, sizeof(char), 4, final_table);
	EXPECT_EQ(strcmp(line, "7,3\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}

TEST(tables_merging_testing_second_colomn_key,
	 multy_line_table_merge_intersection){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "9,Abrosimov\n" \
					"7,Gorkov\n");
	
	fprintf(table2, "8,Bobilev\n" \
					"5,Kolodin\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(1, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[50] = {'\0'};
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "9,Abrosimov\n"), 0);
	
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "8,Bobilev\n"), 0);
	
	memset(line, '\0', TEST_LINE_LENGTH);
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "7,Gorkov\n"), 0);
	

	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "5,Kolodin\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}

TEST(tables_merging_testing_second_colomn_key,
	 multy_line_table_merge_intersection_with_equals){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "9,Abrosimov\n" \
					"7,Gorkov\n");
	
	fprintf(table2, "9,Abrosimov\n" \
					"5,Korinov\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(1, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[50] = {'\0'};
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "9,Abrosimov\n"), 0);
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "9,Abrosimov\n"), 0);
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "7,Gorkov\n"), 0);
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "5,Korinov\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}

TEST(tables_merging_testing_first_colomn_key,
	 multy_line_table_merge_intersection){
	FILE* table1 = fopen(TABLE_1_FILE_NAME, "w");
	FILE* table2 = fopen(TABLE_2_FILE_NAME, "w");
	
	fprintf(table1, "2,Abrosimov\n" \
					"3,Gorkov\n");
	
	fprintf(table2, "1,Korinov\n" \
					"4,Abrosimov\n");
	
	fclose(table1);
	fclose(table2);
	
	table_merge(0, TABLE_1_FILE_NAME, TABLE_2_FILE_NAME, FINAL_TABLE_NAME);
	
	FILE* final_table = fopen(FINAL_TABLE_NAME, "r");
	
	char line[50] = {'\0'};
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "1,Korinov\n"), 0);
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "2,Abrosimov\n"), 0);
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "3,Gorkov\n"), 0);
	
	fgets(line, 50, final_table);
	EXPECT_EQ(strcmp(line, "4,Abrosimov\n"), 0);
	
	remove(TABLE_1_FILE_NAME);
	remove(TABLE_2_FILE_NAME);
	remove(FINAL_TABLE_NAME);
}
