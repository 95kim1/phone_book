#ifndef _PHONE_FILE_H_
#define _PHONE_FILE_H_

#include "phoneData.h"

int load_book(char *filename, struct phone_book *pbook);
int store_book(char *filename, struct phone_book *pbook);
int add_data(char *filename, struct phone_data *pdata);

#endif
