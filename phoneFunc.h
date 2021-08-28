#ifndef _PHONE_FUNC_H_
#define _PHONE_FUNC_H_

#include "phoneData.h"

void insert_phone_data(struct phone_book *pbook);
void show_phone_book(struct phone_book *pbook);
void search_phone_data(struct phone_book *pbook);
void delete_phone_data(struct phone_book *pbook);
void update_phone_data(struct phone_book *pbook);

#endif
