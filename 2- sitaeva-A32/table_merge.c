#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_merge.h"

#define LINE_BUFF_SIZE 100
#define KEY_BUFF_SIZE 30

void get_key(int col, char * line, char *key){
	int k = 0;
	*key = '\0';

	while (*line != '\0'){
		if (*line == ',')
			k++;
			
		if (k == col) {
			if (*line == ',') line++;
			while (*line != ',' && *line != '\0' && *line != '\t'&& *line != '\n')
				*key++ = *line++;
			*key = '\0';
			return;
		}
		line++;
	}
}


int table_merge(int col, const char *name1, const char *name2, const  char *name_output) {
	
	FILE* table1, * table2, *output_table;
	
	if ((table1 = fopen(name1, "r")) == NULL) return 0;
	if ((table2 = fopen(name2, "r")) == NULL) return 0;
	if ((output_table = fopen(name_output, "w")) == NULL) return 0;

	char line1[LINE_BUFF_SIZE] = {'\0'};
	char line2[LINE_BUFF_SIZE] = {'\0'};
	char key1[KEY_BUFF_SIZE] = {'\0'};
	char key2[KEY_BUFF_SIZE] = {'\0'};
	
	
	fgets(line1, LINE_BUFF_SIZE, table1);
	fgets(line2, LINE_BUFF_SIZE, table2);
	
	get_key(col, line1, key1);
	get_key(col, line2, key2);
	
	if (strlen(key1) == 0 && strlen(key2) == 0){
		fclose(table1);
		fclose(table2);
		fclose(output_table);
		return 1;
	}
	
	// key comparing merging
	while (!feof(table1) && !feof(table2)) {
		if (strcmp(key1, key2) < 0) {
			fputs(line1, output_table);
			*line1 = '\0';
			fgets(line1, LINE_BUFF_SIZE, table1);
			get_key(col, line1, key1);
		}
		else {
			fputs(line2, output_table);
			*line2 = '\0';
			fgets(line2, LINE_BUFF_SIZE, table2);
			get_key(col, line2, key2);
		}
	}
	
	// last buffer comparing
	if (strlen(key1) != 0 && strcmp(key1, key2) < 0) {
		fputs(line1, output_table);
		fgets(line1, LINE_BUFF_SIZE, table1);
		get_key(col, line1, key1);
	}
	else if (strlen(key2) != 0) {
		fputs(line2, output_table);
		fgets(line2, LINE_BUFF_SIZE, table2);
		get_key(col, line2, key2);
	}
	 
	// writing tail to the end of final table 
	if (feof(table1) != 0) {
		while (feof(table2) == 0) {
			fputs(line2, output_table);
			fgets(line2, LINE_BUFF_SIZE, table2);
		}
		fputs(line2, output_table);
	}
	else if (feof(table2) != 0) {
		while (feof(table1) == 0) {
			fputs(line1, output_table);
			fgets(line1, LINE_BUFF_SIZE, table1);
		}
		fputs(line1, output_table);
	}
	
	fclose(table1);
	fclose(table2);
	fclose(output_table);
	return 1;
 }


