#include "common.h"
#include "phoneFunc.h"

#define SIZE 5

/* 
	[insert data into book]
	�̸�, ��ȭ��ȣ �Է¹޾Ƽ� ��ȭ��ȣ�ο� ���� 
	
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
	
	printf("> �̸� �Է�: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';
	fflush(stdin);
	
	do {
		printf("> ��ȭ��ȣ(���ڸ�) �Է�: ");
		fgets(phone, sizeof(phone), stdin);
		phone[strlen(phone)-1] = '\0';
		fflush(stdin);
	} while (!check_phone_num(phone));
	
	/* �̸�, ��ȭ��ȣ�� �����ϴ��� üũ */
	while (1) {
		tmp = find_data_with_name(tmp, name);
		
		if (tmp == NULL)
			break;
		
		if (strcmp(tmp->phone, phone) == 0) {
			printf("�̹� �����ϴ� �������Դϴ�.\n");
			return NULL;
		}
		
		tmp = next_data(tmp);
	}
	
	tmp = create_data(name, phone);
	
	insert_data(pbook, tmp);
	
	printf("����� �Ϸ�Ǿ����ϴ�.\n");
	
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
	
	printf("\n�˻��� �Ϸ�Ǿ����ϴ�.\n");
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
	
	/* �̸��� ���� ������ �ӽ� ����� */
	struct phone_data **tmp; 
	struct phone_data **arr_data = (struct phone_data **)malloc(sizeof(struct phone_data *) * SIZE);
	int cnt_arr = 0;		//������ ���� 
	int size_arr = SIZE;	//����� ũ�� 
	
	int i;
	
	printf(">> �˻��� �̸��� �Է����ּ���: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';
	fflush(stdin);
	
	/* ��ġ�ϴ� ������ ã�� (�ߺ� ����) */
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
	
	printf("\n�˻��� �Ϸ�Ǿ����ϴ�.\n");
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
	
	/* �̸��� ���� ������ �ӽ� ����� */
	struct phone_data **tmp;
	struct phone_data **arr_data = (struct phone_data **)malloc(sizeof(struct phone_data *) * SIZE);
	int cnt_arr = 0;		//������ ���� 
	int size_arr = SIZE;	//����� ũ�� 
	
	int i;
	
	printf(">> ������ �̸��� �Է����ּ���: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';
	fflush(stdin);
	
	/* ��ġ�ϴ� ������ ã�� (�ߺ� ����) */
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
	
	/* ��ġ�ϴ� �����Ͱ� ���� ��� */
	if (cnt_arr == 0) {
		free(arr_data);
		printf("�ش� �����Ͱ� �������� �ʽ��ϴ�.\n");
		getchar();
		return;
	}
	
	/* ��ġ�ϴ� �����Ͱ� 1���� ��� */
	if (cnt_arr == 1) {
		delete_data(pbook, arr_data[0]);
		free(arr_data);
		printf("������ �Ϸ�Ǿ����ϴ�.\n");
		getchar();
		return;
	}
	
	/* ��ġ�ϴ� �����Ͱ� �������� ���, �ش� ����Ʈ �����ֱ� */
	printf("\n");
	for (i = 0; i < cnt_arr; i++) {
		show_data(arr_data[i]);
	}
	printf("\n");
	
	/* ��ġ�ϴ� �����Ͱ� �������� ���, ��ȭ��ȣ�� ã�� */
	printf("�ߺ��Ǵ� �����Ͱ� �������Դϴ�.\n");
	printf(">> ������ �������� ��ȭ��ȣ�� �Է����ּ���: ");
	fgets(phone, sizeof(phone), stdin);
	phone[strlen(phone)-1] = '\0';
	fflush(stdin);
	
	/* ��ġ�ϴ� ������ ã�� */
	for (i = 0; i < cnt_arr; i++) {
		if (strcmp(arr_data[i]->phone, phone) == 0) {
			tmp_data = arr_data[i];
			break;
		}
	}
	
	free(arr_data);
		
	if (tmp_data == NULL) {
		printf("�ش� �����Ͱ� �������� �ʽ��ϴ�.\n");
	} else {
		delete_data(pbook, tmp_data);
		printf("������ �Ϸ�Ǿ����ϴ�.\n");
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
	
	/* �̸��� ���� ������ �ӽ� ����� */
	struct phone_data **tmp;
	struct phone_data **arr_data = (struct phone_data **)malloc(sizeof(struct phone_data *) * SIZE);
	int cnt_arr = 0;		//������ ���� 
	int size_arr = SIZE;	//����� ũ�� 
	
	int i;
	
	printf(">> ������ �̸��� �Է����ּ���: ");
	fgets(name, sizeof(name), stdin);
	name[strlen(name)-1] = '\0';
	fflush(stdin);
	
	/* ��ġ�ϴ� ������ ã�� (�ߺ� ����) */
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
	
	/* ��ġ�ϴ� �����Ͱ� ���� ��� */
	if (cnt_arr == 0) {
		free(arr_data);
		printf("�ش� �����Ͱ� �������� �ʽ��ϴ�.\n");
		getchar();
		return;
	}
	
	/* ��ġ�ϴ� �����Ͱ� 1���� ��� */
	if (cnt_arr == 1) {
		printf(">> ���ο� ��ȭ��ȣ�� �Է����ּ���: ");
		fgets(phone, sizeof(phone), stdin);
		phone[strlen(phone)-1] = '\0';
		fflush(stdin);
		
		strcpy(arr_data[0]->phone, phone);
		
		free(arr_data);
		printf("������ �Ϸ�Ǿ����ϴ�.\n");
		getchar();
		return;
	}
	
	/* ��ġ�ϴ� �����Ͱ� �������� ���, �ش� ����Ʈ �����ֱ� */
	printf("\n");
	for (i = 0; i < cnt_arr; i++) {
		show_data(arr_data[i]);
	}
	printf("\n"); 
	
	/* ��ġ�ϴ� �����Ͱ� �������� ���, ��ȭ��ȣ�� ã�� */
	printf("�ߺ��Ǵ� �����Ͱ� �������Դϴ�.\n");
	printf(">> ���� ��ȭ��ȣ�� �Է����ּ���: ");
	fgets(phone, sizeof(phone), stdin);
	phone[strlen(phone)-1] = '\0';
	fflush(stdin);
	
	/* ��ġ�ϴ� ������ ã�� */
	for (i = 0; i < cnt_arr; i++) {
		if (strcmp(arr_data[i]->phone, phone) == 0) {
			tmp_data = arr_data[i];
			break;
		}
	}
	
	free(arr_data);
		
	if (tmp_data == NULL) {
		printf("�ش� �����Ͱ� �������� �ʽ��ϴ�.\n");
	} else {
		printf(">> ���ο� ��ȭ��ȣ�� �Է����ּ���: ");
		fgets(phone, sizeof(phone), stdin);
		phone[strlen(phone)-1] = '\0';
		fflush(stdin);
		
		strcpy(tmp_data->phone, phone);
		
		printf("������ �Ϸ�Ǿ����ϴ�.\n");
	}
	getchar();
}


