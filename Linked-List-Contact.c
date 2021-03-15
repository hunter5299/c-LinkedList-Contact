#define _CRT_SECURE_NO_WARNINGS 1
#include"Concact.h"

enum Oprt{
	EXIT,//0
	ADD,
	DEL,
	FIND,
	MOD,
	SHOW,
	SORT,
	SAVE
};
int main(){
	enum Oprt input;
	Contact* lnklist = NULL;
	initc(&lnklist,FILENAME);
	do{
		menu();
		scanf("%d", &input);
		switch (input){
		case ADD:
			addContact(&lnklist);
			break;
		case DEL:
			delContact(&lnklist);
			break;
		case FIND:
			searchContact(&lnklist);
			break;
		case MOD:
			modContact(&lnklist);
			break;
		case SHOW:
			showContact(&lnklist);
			break;
		case SORT:
			//sortContact(&lnklist);
			break;
		case SAVE:
			saveContact(&lnklist,FILENAME);
			break;
		case EXIT:
			//destroyContact(&lnklist);
			printf("contact exit!\n");
			break;
		}
	} while (input);
	system("pause");
	return 0;
}