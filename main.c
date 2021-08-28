

#include "common.h"
#include "menu.h"
#include "phoneData.h"
#include "phoneFunc.h"

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
	struct phone_book pbook;
	
	/* initializing phone_book */
	init_phone_book(&pbook);
	
	while (1) {
		/* show menu to choose num for user */
		show_menu();
		
		printf(">> 메뉴를 선택해주세요.(1~5, 0) : ");
		fflush(stdin);
		scanf("%d", &menu_num);
		fflush(stdin);
		
		switch (menu_num) {
		case END:
			free_all_phone_data(&pbook);
			return 0;
		case INSERT:
			insert_phone_data(&pbook);
			break;
		case SHOW:
			show_phone_book(&pbook);
			break;
		case SEARCH:
			search_phone_data(&pbook);
			break;
		case DELETE:
			delete_phone_data(&pbook);
			break;
		case UPDATE:
			update_phone_data(&pbook);
			break;
		}		
	}
	
	return 0;
}
