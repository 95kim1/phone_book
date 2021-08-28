#include "common.h"
#include "phoneData.h"

/*
	[itnitialize book]
	initialize phone book
	
	input:
		phone book pointer
	
	output: none	
*/
void init_phone_book(struct phone_book *pbook)
{
	pbook->head = NULL;
	pbook->tail = NULL;
	pbook->cnt = 0;
}

/* 	
	[free all data]
	free all phone data from a phone book 
	
	intput:
		pbook: phone book pointer
	
	output: none
*/
void free_all_phone_data(struct phone_book *pbook)
{
	struct phone_data *cur_data = pbook->head;
	struct phone_data *tmp;
	
	while (cur_data != NULL) {
			tmp = cur_data;
			cur_data = next_data(cur_data);
			free(tmp);
	}
	
	init_phone_book(pbook);
}

/* 
	[next data]
	return next data in a phone_book list 
	
	input:
		pdata: phone data pointer
	
	output:
		phone data pointer
*/
struct phone_data *next_data(struct phone_data *pdata)
{
	if (pdata == NULL)
		return NULL;
	
	return pdata->next;
}

/* 	
	[empty book]
	check that a phone book list is empty 
	
	input:
		pbook: phone book pointer
	
	output:
		(1 : empty, 0: not empty)
*/
int is_empty_book(struct phone_book *pbook)
{
	return !pbook->cnt;
}

/* 	
	[create data]
	create a phone data 
	
	input:
		name: name
		phone: phone number 
	
	output:
		phone data pointer (created data)
*/
struct phone_data *create_data(char *name, char *phone)
{
	struct phone_data *tmp = (struct phone_data *)malloc(sizeof(struct phone_data));
	
	if (tmp == NULL)
		return NULL;
	
	strcpy(tmp->name, name);
	strcpy(tmp->phone, phone);
	
	tmp->next = NULL;
	
	return tmp;
}

/* 	
	[insert data]
	insert phone data to phone book 
	
	input:
		pbook: phone book pointer
		pdata: phone data pointer
	
	output: none
*/
void insert_data(struct phone_book *pbook, struct phone_data *pdata)
{
	if (is_empty_book(pbook)) {
		pbook->head = pdata;
		pbook->tail = pdata;
		pbook->cnt = 1;
		return;
	}
	
	pbook->tail->next = pdata;
	pbook->tail = pdata;
	pbook->cnt++;
}

/*
	[show data]
	show a certain phone data
	
	input:
		pdata: phone data pointer
	
	output: none 
*/
void show_data(struct phone_data *pdata)
{
	printf("┌───────────────────────\n");
	printf("│ ▶ 이름: %s\n", pdata->name);
	printf("│ ▶ 전화번호: %s\n", pdata->phone);
	printf("└───────────────────────\n");		
}

/*
	[find data with a name]
	
	find data from the variable, from.
	
	input:
		from: starting position
		name: name of data
	
	output:
		NULL if not found
		phone_data pointer if found	
*/
struct phone_data* find_data_with_name(struct phone_data* from, char* name)
{
	while (from != NULL) {
		if (strcmp(from->name, name) == 0)
			return from;
		
		from = next_data(from);
	}
	
	return NULL;
}

/*
	[find data with a phone num]
	
	find data from the variable, from.
	
	input:
		from: starting position
		phone: phone number of data
	
	output:
		NULL if not found
		phone_data pointer if found	
*/
struct phone_data* find_data_with_phone(struct phone_data* from, char* phone)
{
	while (from != NULL) {
		if (strcmp(from->phone, phone) == 0)
			return from;
			
		from = next_data(from);
	}
	
	return NULL;
}

/* 
	[delete data]
	
	input:
		pbook: phone book pointer
		pdata: phone book pointer
	
	output: none
*/
void delete_data(struct phone_book *pbook, struct phone_data *pdata)
{
	struct phone_data *cur = pbook->head;
	struct phone_data *prev = NULL;
	
	/* find previous data of pdata */
	while (cur != pdata) {
		prev = cur;
		cur = next_data(cur);
	}
	
	if (cur == pbook->head) {
		pbook->head = cur->next;	
	}
	
	if (cur == pbook->tail) {
		pbook->tail = prev;
	}
	
	if (prev != NULL) {
		prev->next = cur->next;
	}
	
	pbook->cnt--;
	free(cur);
}

/* 
	[check phone number]
	check whether right phone number or not]
	
	input:
		phone: phone number
	
	output:
		(1: right, 0: wrong)
*/
int check_phone_num(char *phone)
{
	while (*phone != '\0') {
		if (*phone < '0' || '9' < *phone)
			return 0;
		phone++;
	}
	return 1;
}



