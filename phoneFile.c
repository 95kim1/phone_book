#include "common.h"
#include "phoneFile.h"

/*
	[load book]
	load phone_book (memory) from a file (disk)
	
	input:
		filename: file's name having data
		pbook: phone book pointer where data will be loaded
		
	output:
		1: succeed, 0: fail
*/
int load_book(char *filename, struct phone_book *pbook)
{
 	FILE *fp;
 	struct phone_data *pdata;
 	
 	if (pbook == NULL)
		return 0;
 	
 	fp = fopen(filename, "rb");
 	if (fp == NULL)
 		return 0;
 	
 	while (1) {
 		pdata = (struct phone_data *)malloc(sizeof(struct phone_data));
 		fread(pdata, sizeof(struct phone_data), 1, fp);
 		
 		if (feof(fp)) {
 			fclose(fp);
 			return 0;
		}
 		
 		pdata->next = NULL;
		insert_data(pbook, pdata);
	}
	
	fclose(fp);
		
	return 1;
}

/*
	[store book]
	store phone_book (memory) to a file (disk)
	
	input:
		filename: file's name where data will be stored
		pbook: phone book pointer having data
	
	output:
		1: succeed, 0: fail
*/
int store_book(char *filename, struct phone_book *pbook)
{
	FILE *fp;
	struct phone_data *cur;
	
	if (pbook == NULL)
		return 0;
	
	fp = fopen(filename, "wb");
	if (fp == NULL)
		return 0;
	
	cur = pbook->head;
	
	while (cur != NULL) {
		fwrite(cur, sizeof(struct phone_data), 1, fp);
		
		if (feof(fp)) {
 			fclose(fp);
 			return 0;
		}
			
		cur = next_data(cur);
	}
	
	fclose(fp);	
	
	return 1;
}

/*
	[add data]
	add phone_data to the last position of a file
	
	input:
		filename: file's name where data will be added
		pdata: pointing data which will be added to a file
		
	output:
		1: succeed, 0: fail
*/
int add_data(char *filename, struct phone_data *pdata)
{
	FILE *fp;
	
	if (pdata == NULL)
		return 0;
	
	fp = fopen(filename, "ab");
	if (fp == NULL)
		return 0;
		
	fwrite(pdata, sizeof(struct phone_data), 1, fp);

	if (feof(fp)) {
		fclose(fp);
		return 0;
	}
	
	fclose(fp);
	
	return 1;
}


