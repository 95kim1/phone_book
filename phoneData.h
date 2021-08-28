#ifndef _PHONE_DATA_H_
#define _PHONE_DATA_H_

#define NAME_LEN 32
#define PHONE_LEN 32

struct phone_data {
	char name[NAME_LEN];
	char phone[PHONE_LEN];
	struct phone_data *next;
};

struct phone_book {
	struct phone_data *head;
	struct phone_data *tail;
	int cnt;
};

/* basic of basic functions */
void init_phone_book(struct phone_book *pbook);
void free_all_phone_data(struct phone_book *pbook);
struct phone_data *next_data(struct phone_data *pdata);
int is_empty_book(struct phone_book *pbook);
struct phone_data *create_data(char *name, char *phone);

/* main functions */
void insert_data(struct phone_book *pbook, struct phone_data *pdata);
void show_data(struct phone_data *pdata);
struct phone_data* find_data_with_name(struct phone_data* from, char* name);
struct phone_data* find_data_with_phone(struct phone_data* from, char* phone);
void delete_data(struct phone_book *pbook, struct phone_data *pdata);

/* sub function */
int check_phone_num(char *phone);

#endif
