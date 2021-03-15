#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include"Concact.h"

void menu()
{
	printf("*************************************\n");
	printf("*****   1. add         2. del   *****\n");
	printf("*****   3. search      4. modify*****\n");
	printf("*****   5. show        6. sort  *****\n");
	printf("*****   0. exit        7. save  *****\n");
	printf("*************************************\n");
}
int initc(Contact** linkedlist,char *filename){
	assert(linkedlist&&filename);
	FILE  *fp = fopen(filename, "a+");
	if (fp == NULL){
		printf("�ļ���ʧ��\n");
		return -1;
	}
	Contact *cp = NULL;
	Contact* t = NULL;
	Contact* ct = NULL;

	//��ȡ��һ�еĿո�
	fgetc(fp);
	while (!feof(fp)){
		//feof(fp)�ж��ļ�ָ���ʱ��λ���Ƿ�ΪEOF���ǿ�Ϊ0����Ϊ1
		if (cp==NULL){
			//����һ��������ͷ���
			cp = (Contact*)malloc(sizeof(Contact)); 
			if (cp == NULL){
				printf("�����ڴ�ʧ��\n");
				return -1;
			}
			cp->next = NULL;
			ct = cp;
		}
		t= (Contact*)malloc(sizeof(Contact));
		if (t == NULL){
			printf("�����ڴ�ʧ��\n");
			return -1;
		}
		fscanf(fp,"%d %s %s", &(t->p.id), &(t->p.name), &(t->p.telnum)); 
		t->next = NULL;

		ct->next = t;
		ct = ct->next;
	}
	fclose(fp);
	//�ͷ�������ͷ���
	if (cp != NULL){
		ct = cp;
		cp = cp->next;
		free(ct);
		ct = NULL;
	}
	*linkedlist = cp;
	return 0;
}
int addContact(Contact** lnk){
	assert(lnk);
	Contact* t = NULL;
	t = *lnk;
	int count = 1;
	//��ͷ�ڵ�Ϊ��
	if (t == NULL){
		t = (Contact*)malloc(sizeof(Contact));
		if (t == NULL){
			printf("add failed!\n");
			return -1;
		}
		t->next = NULL;
		*lnk = t;
	}
	else{
		while (t->next != NULL){
			t = t->next;
			count++;
		}
		t->next = (Contact*)malloc(sizeof(Contact));
		if (t->next == NULL){
			printf("add failed!\n");
			return -1;
		}
		t = t->next;
		t->next = NULL;
		count++;
	}
	//д������
	t->p.id = count;
	printf("plz enter name\n");
	scanf("%s", &(t->p.name));
	printf("plz enter telnum\n");
	scanf("%s", &(t->p.telnum));
	//saveContact(&t,FILENAME);
	return 0;
}
int delContact(Contact** lnk){
	assert(lnk);
	printf("����Ҫɾ����id:\n");
	int delnum = 0;
	scanf("%d", &delnum);
	Contact* t = NULL;
	t = *lnk;
	if (t == NULL){
		printf("����Ϊ�գ�\n");
		return -1;
	}
	//��ͷ�ڵ���Ҫɾ����Ԫ��
	Contact* td = NULL;
	if (t->p.id == delnum){
		td = t;
		t = t->next;
		free(td);
		td = NULL;
		*lnk = t;
		printf("ɾ���ɹ���\n");
		return 0;
	}

	while (t->next != NULL){
		if (t->next->p.id == delnum){
			td = t->next;
			t->next = td->next;
			free(td);
			printf("ɾ���ɹ�!\n");
			return 0;
		}
		t = t->next;
	}
	printf("ɾ��ʧ�ܣ��޴�id\n");
	return 0;
}
int modContact(Contact** lnk){
	Contact* t = NULL;
	t = *lnk;
	int modnum = 0;
	printf("��������Ҫ�޸ĵ�id��\n");
	scanf("%d", &modnum);
	while (t != NULL){
		if (t->p.id == modnum){
			printf("plz enter name\n");
			scanf("%s", &(t->p.name));
			printf("plz enter telnum\n");
			scanf("%s", &(t->p.telnum));
			return 0;
		}
		t = t->next;
	}
	printf("�޴�id!\n");
	return 1;
}
int searchContact(Contact** lnk){
	assert(lnk);
	Contact* t = NULL;
	t = *lnk;
	char name[20] = { 0 };
	printf("��������Ҫ���ҵ����֣�\n");
	scanf("%s", name);
	while (t){
		if (strcmp(t->p.name,name)== 0 ){
			printf("id��%d\t name:%s\t telnum:%s\t\n", t->p.id, t->p.name, t->p.telnum);
			return 0;
		}
		t = t->next;
	}
	printf("���޴���!\n");
	return -1;
}
int showContact(Contact** lnk){
	Contact* t = *lnk;
	if (t == NULL){
		printf("contact is empty!\n");
		return -1;
	}
	while (t != NULL){
		printf("id:%d\t name:%s\t telNum:%s\t\n", t->p.id, t->p.name, t->p.telnum);
		t = t->next;
	}
	return 0;
}
int sortContact(Contact** lnk);
int saveContact(Contact** lnk,char* filename){
	Contact* t = *lnk;
	FILE *fp = fopen(filename, "w+");
	if (!fp){
		printf("����ʧ�ܣ�����²���\n");
		return -1;
	}
	while (t != NULL){
		fprintf(fp, "\n%d %s %s", t->p.id, t->p.name, t->p.telnum);
		t = t->next;
	}
	fclose(fp);
	fp = NULL;
	printf("����ɹ�\n");
	return 0;
}
int destroyContact(Contact* lnk);