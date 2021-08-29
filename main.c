/*
	2021-08-29
	95kim1 made phone book project.
*/

#include "common.h"
#include "menu.h"
#include "phoneData.h"
#include "phoneFunc.h"
#include "phoneFile.h"

/* kinds of function */
enum {
	END,
	INSERT,
	SHOW,
	SEARCH,
	DELETE,
	UPDATE,
};

int main(void) 
{
	int menu_num;
	struct phone_book book;
	struct phone_data *pdata;
	char phone_filename[] = "phoneDB";
	
	/* initializing phone_book */
	init_phone_book(&book);
	
	/* load phone book from db-file*/
	load_book(phone_filename, &book);
		
	while (1) {
		/* show menu to choose num for user */
		show_menu();
		
		/* choose menu number */
		printf(">> 메뉴를 선택해주세요.(1~5, 0) : ");
		fflush(stdin);
		scanf("%d", &menu_num);
		fflush(stdin);
		
		/* do the function which user choosed */
		switch (menu_num) {
		case END:
			store_book(phone_filename, &book);
			free_all_phone_data(&book);
			return 0;
		case INSERT:
			pdata = insert_phone_data(&book);
			if (pdata != NULL)
				add_data(phone_filename, pdata);
			getchar();
			break;
		case SHOW:
			show_phone_book(&book);
			break;
		case SEARCH:
			search_phone_data(&book);
			break;
		case DELETE:
			delete_phone_data(&book);
			break;
		case UPDATE:
			update_phone_data(&book);
			break;
		}		
	}
	
	return 0;
}
