#include "common.h"
#include "menu.h"

/*
	[show menu]
	show the first(main) menu
	
	input, output: none
*/
void show_menu()
{
	system("cls");
	
	printf("    [전화번호부]\n");
	printf("─────────────────\n");
	printf(" 1. 전화번호 등록\n");
	printf(" 2. 전체 출력\n");
	printf(" 3. 전화번호 검색\n");
	printf(" 4. 전화번호 삭제\n");
	printf(" 5. 전화번호 수정\n");
	printf(" 0. 종료\n");
	printf("─────────────────\n");
}

