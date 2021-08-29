#include "common.h"
#include "phoneFunc.h"

#define SIZE 5

/* 
	[insert data into book]
	이름, 전화번호 입력받아서 전화번호부에 저장 
	
	input:
		pbook: phone book pointer
	
	output: 
		address of inserted data
*/
struct phone_data *insert_phone_data(struct phone_book *pbook)
{
	char name[NAME_LEN];
	char phone[PHONE_LEN];
	struct phone_data *tmp = pbook->head;
	
	printf("> 이름 입력: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';
	fflush(stdin);
	
	do {
		printf("> 전화번호(숫자만) 입력: ");
		fgets(phone, sizeof(phone), stdin);
		phone[strlen(phone)-1] = '\0';
		fflush(stdin);
	} while (!check_phone_num(phone));
	
	/* 이름, 전화번호가 존재하는지 체크 */
	while (1) {
		tmp = find_data_with_name(tmp, name);
		
		if (tmp == NULL)
			break;
		
		if (strcmp(tmp->phone, phone) == 0) {
			printf("이미 존재하는 데이터입니다.\n");
			return NULL;
		}
		
		tmp = next_data(tmp);
	}
	
	tmp = create_data(name, phone);
	
	insert_data(pbook, tmp);
	
	printf("등록이 완료되었습니다.\n");
	
	return tmp;
}

/* 
	[show all phone data]
	show all list in a phone book
	
	input:
		pbook: phone book pointer
	
	output: none
*/
void show_phone_book(struct phone_book *pbook)
{
	struct phone_data *cur = pbook->head;
	
	printf("\n");
	
	while (cur != NULL) {
		show_data(cur);
		
		cur = next_data(cur);
	}
	
	printf("\n검색이 완료되었습니다.\n");
	getchar();
}

/* 
	[search a phone data]
	search phone data from a phone book
	
	user input name.
	find a data with the name.
	show all data.
	
	input:
		pbook: phone book pointer
	
	output: none
*/
void search_phone_data(struct phone_book *pbook)
{
	char name[NAME_LEN];
	char phone[PHONE_LEN];
	struct phone_data *tmp_data = pbook->head;
	
	/* 이름이 같은 데이터 임시 저장소 */
	struct phone_data **tmp; 
	struct phone_data **arr_data = (struct phone_data **)malloc(sizeof(struct phone_data *) * SIZE);
	int cnt_arr = 0;		//데이터 개수 
	int size_arr = SIZE;	//저장소 크기 
	
	int i;
	
	printf(">> 검색할 이름을 입력해주세요: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';
	fflush(stdin);
	
	/* 일치하는 데이터 찾기 (중복 포함) */
	while (1) {
		tmp_data = find_data_with_name(tmp_data, name);
		
		if (tmp_data == NULL)
			break;
			
		if (cnt_arr == size_arr) {
			tmp = arr_data;
			size_arr *= 2;
			arr_data = realloc(arr_data, sizeof(struct phone_data *) * size_arr);
			free(tmp);
		}
		arr_data[cnt_arr++] = tmp_data;
		
		tmp_data = next_data(tmp_data);
	}
	
	/* show all found data */	
	printf("-------------\n");
	for (i = 0; i < cnt_arr; i++) {
		show_data(arr_data[i]);
	}
	
	free(arr_data);
	
	printf("\n검색이 완료되었습니다.\n");
	getchar();	
}


/*
	[delete a phone data]
	delete a phone data from a phone book
	
	user input name.
	find a data with the name.
	if there are several same names, 
		user input phone num
		find a data with the phone num.
	delete if it exist or not
	
	input:
		pbook: phone book pointer
	
	output: none
*/
void delete_phone_data(struct phone_book *pbook)
{
	char name[NAME_LEN];
	char phone[PHONE_LEN];
	struct phone_data *tmp_data = pbook->head;
	
	/* 이름이 같은 데이터 임시 저장소 */
	struct phone_data **tmp;
	struct phone_data **arr_data = (struct phone_data **)malloc(sizeof(struct phone_data *) * SIZE);
	int cnt_arr = 0;		//데이터 개수 
	int size_arr = SIZE;	//저장소 크기 
	
	int i;
	
	printf(">> 삭제할 이름을 입력해주세요: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';
	fflush(stdin);
	
	/* 일치하는 데이터 찾기 (중복 포함) */
	while (1) {
		tmp_data = find_data_with_name(tmp_data, name);
		
		if (tmp_data == NULL)
			break;
			
		if (cnt_arr == size_arr) {
			tmp = arr_data;
			size_arr *= 2;
			arr_data = realloc(arr_data, sizeof(struct phone_data *) * size_arr);
			free(tmp);
		}
		arr_data[cnt_arr++] = tmp_data;
		
		tmp_data = next_data(tmp_data);
	}
	
	/* 일치하는 데이터가 없는 경우 */
	if (cnt_arr == 0) {
		free(arr_data);
		printf("해당 데이터가 존재하지 않습니다.\n");
		getchar();
		return;
	}
	
	/* 일치하는 데이터가 1개인 경우 */
	if (cnt_arr == 1) {
		delete_data(pbook, arr_data[0]);
		free(arr_data);
		printf("삭제가 완료되었습니다.\n");
		getchar();
		return;
	}
	
	/* 일치하는 데이터가 여러개인 경우, 해당 리스트 보여주기 */
	printf("\n");
	for (i = 0; i < cnt_arr; i++) {
		show_data(arr_data[i]);
	}
	printf("\n");
	
	/* 일치하는 데이터가 여러개인 경우, 전화번호로 찾기 */
	printf("중복되는 데이터가 여러개입니다.\n");
	printf(">> 삭제할 데이터의 전화번호를 입력해주세요: ");
	fgets(phone, sizeof(phone), stdin);
	phone[strlen(phone)-1] = '\0';
	fflush(stdin);
	
	/* 일치하는 데이터 찾기 */
	for (i = 0; i < cnt_arr; i++) {
		if (strcmp(arr_data[i]->phone, phone) == 0) {
			tmp_data = arr_data[i];
			break;
		}
	}
	
	free(arr_data);
		
	if (tmp_data == NULL) {
		printf("해당 데이터가 존재하지 않습니다.\n");
	} else {
		delete_data(pbook, tmp_data);
		printf("삭제가 완료되었습니다.\n");
	}
	getchar();
}

/*
	[update a phone data]
	update a phone data from a phone book
	
	user input name.
	find a data with the name.
	if there are several same names, 
		user input phone num
		find a data with the phone num.
	update if it exist or not
	
	input:
		pbook: phone book pointer
	
	output: none
*/
void update_phone_data(struct phone_book *pbook)
{
	char name[NAME_LEN];
	char phone[PHONE_LEN];
	struct phone_data *tmp_data = pbook->head;
	
	/* 이름이 같은 데이터 임시 저장소 */
	struct phone_data **tmp;
	struct phone_data **arr_data = (struct phone_data **)malloc(sizeof(struct phone_data *) * SIZE);
	int cnt_arr = 0;		//데이터 개수 
	int size_arr = SIZE;	//저장소 크기 
	
	int i;
	
	printf(">> 수정할 이름을 입력해주세요: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';
	fflush(stdin);
	
	/* 일치하는 데이터 찾기 (중복 포함) */
	while (1) {
		tmp_data = find_data_with_name(tmp_data, name);
		
		if (tmp_data == NULL)
			break;
			
		if (cnt_arr == size_arr) {
			tmp = arr_data;
			size_arr *= 2;
			arr_data = realloc(arr_data, sizeof(struct phone_data *) * size_arr);
			free(tmp);
		}
		arr_data[cnt_arr++] = tmp_data;
		
		tmp_data = next_data(tmp_data);
	}
	
	/* 일치하는 데이터가 없는 경우 */
	if (cnt_arr == 0) {
		free(arr_data);
		printf("해당 데이터가 존재하지 않습니다.\n");
		getchar();
		return;
	}
	
	/* 일치하는 데이터가 1개인 경우 */
	if (cnt_arr == 1) {
		printf(">> 새로운 전화번호를 입력해주세요: ");
		fgets(phone, sizeof(phone), stdin);
		phone[strlen(phone)-1] = '\0';
		fflush(stdin);
		
		strcpy(arr_data[0]->phone, phone);
		
		free(arr_data);
		printf("수정이 완료되었습니다.\n");
		getchar();
		return;
	}
	
	/* 일치하는 데이터가 여러개인 경우, 해당 리스트 보여주기 */
	printf("\n");
	for (i = 0; i < cnt_arr; i++) {
		show_data(arr_data[i]);
	}
	printf("\n"); 
	
	/* 일치하는 데이터가 여러개인 경우, 전화번호로 찾기 */
	printf("중복되는 데이터가 여러개입니다.\n");
	printf(">> 이전 전화번호를 입력해주세요: ");
	fgets(phone, sizeof(phone), stdin);
	phone[strlen(phone)-1] = '\0';
	fflush(stdin);
	
	/* 일치하는 데이터 찾기 */
	for (i = 0; i < cnt_arr; i++) {
		if (strcmp(arr_data[i]->phone, phone) == 0) {
			tmp_data = arr_data[i];
			break;
		}
	}
	
	free(arr_data);
		
	if (tmp_data == NULL) {
		printf("해당 데이터가 존재하지 않습니다.\n");
	} else {
		printf(">> 새로운 전화번호를 입력해주세요: ");
		fgets(phone, sizeof(phone), stdin);
		phone[strlen(phone)-1] = '\0';
		fflush(stdin);
		
		strcpy(tmp_data->phone, phone);
		
		printf("수정이 완료되었습니다.\n");
	}
	getchar();
}


