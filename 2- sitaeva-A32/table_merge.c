#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table_merge.h"

#define LINE_BUFF_SIZE 100
#define KEY_BUFF_SIZE 30

static void get_key(int col, char *stroka, char *key){
	int k = 0;
	*key = '\0';

	while (*stroka != '\0'){
		if (*stroka == ',') 
			k++;
			
		if (k == col) {
			if (*stroka == ',') stroka++;
			while (*stroka != ',' && *stroka != '\0' && *stroka != '\t')
				*key++ = *stroka++;
			*key = '\0';
			return;
		}
		stroka++;
	}
}


int table_merge(int col, const char *name1, const char *name2, const  char *name_output) {
	
	FILE* table1, * table2, *output_table;
	
	if ((table1 = fopen(name1, "r")) == NULL) return 0;
	if ((table2 = fopen(name2, "r")) == NULL) return 0;
	if ((output_table = fopen(name_output, "w")) == NULL) return 0;

	char stroka1[LINE_BUFF_SIZE] = {'\0'};
	char stroka2[LINE_BUFF_SIZE] = {'\0'};
	char key1[KEY_BUFF_SIZE] = {'\0'};
	char key2[KEY_BUFF_SIZE] = {'\0'};
	
	
	fgets(stroka1, LINE_BUFF_SIZE, table1);
	fgets(stroka2, LINE_BUFF_SIZE, table2);
	
	get_key(col, stroka1, key1);
	get_key(col, stroka2, key2);
	
	if (strlen(key1) == 0 && strlen(key2) == 0){
		fclose(table1);
		fclose(table2);
		fclose(output_table);
		return 1;
	}
	
	// key comparing merging
	while (!feof(table1) && !feof(table2)) {
		if (strcmp(key1, key2) < 0) {
			fputs(stroka1, output_table);
			*stroka1 = '\0';
			fgets(stroka1, LINE_BUFF_SIZE, table1);
			get_key(col, stroka1, key1);
		}
		else {
			fputs(stroka2, output_table);
			*stroka2 = '\0';
			fgets(stroka2, LINE_BUFF_SIZE, table2);
			get_key(col, stroka2, key2);
		}
	}
	
	// last buffer comparing
	if (strlen(key1) != 0 && strcmp(key1, key2) < 0) {
		fputs(stroka1, output_table);
		fgets(stroka1, LINE_BUFF_SIZE, table1);
		get_key(col, stroka1, key1);
	}
	else if (strlen(key2) != 0) {
		fputs(stroka2, output_table);
		fgets(stroka2, LINE_BUFF_SIZE, table2);
		get_key(col, stroka2, key2);
	}
	 
	// writing tail to the end of final table 
	if (feof(table1) != 0) {
		while (feof(table2) == 0) {
			fputs(stroka2, output_table);
			fgets(stroka2, LINE_BUFF_SIZE, table2);
		}
		fputs(stroka2, output_table);
	}
	else if (feof(table2) != 0) {
		while (feof(table1) == 0) {
			fputs(stroka1, output_table);
			fgets(stroka1, LINE_BUFF_SIZE, table1);
		}
		fputs(stroka1, output_table);
	}
	
	fclose(table1);
	fclose(table2);
	fclose(output_table);
	return 1;
 }

