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
		printf("文件打开失败\n");
		return -1;
	}
	Contact *cp = NULL;
	Contact* t = NULL;
	Contact* ct = NULL;

	//读取第一行的空格
	fgetc(fp);
	while (!feof(fp)){
		//feof(fp)判断文件指针此时的位置是否为EOF，非空为0，空为1
		if (cp==NULL){
			//建立一个无数据头结点
			cp = (Contact*)malloc(sizeof(Contact)); 
			if (cp == NULL){
				printf("申请内存失败\n");
				return -1;
			}
			cp->next = NULL;
			ct = cp;
		}
		t= (Contact*)malloc(sizeof(Contact));
		if (t == NULL){
			printf("申请内存失败\n");
			return -1;
		}
		fscanf(fp,"%d %s %s", &(t->p.id), &(t->p.name), &(t->p.telnum)); 
		t->next = NULL;

		ct->next = t;
		ct = ct->next;
	}
	fclose(fp);
	//释放无数据头结点
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
	//若头节点为空
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
	//写入数据
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
	printf("输入要删除的id:\n");
	int delnum = 0;
	scanf("%d", &delnum);
	Contact* t = NULL;
	t = *lnk;
	if (t == NULL){
		printf("链表为空！\n");
		return -1;
	}
	//若头节点是要删除的元素
	Contact* td = NULL;
	if (t->p.id == delnum){
		td = t;
		t = t->next;
		free(td);
		td = NULL;
		*lnk = t;
		printf("删除成功！\n");
		return 0;
	}

	while (t->next != NULL){
		if (t->next->p.id == delnum){
			td = t->next;
			t->next = td->next;
			free(td);
			printf("删除成功!\n");
			return 0;
		}
		t = t->next;
	}
	printf("删除失败，无此id\n");
	return 0;
}
int modContact(Contact** lnk){
	Contact* t = NULL;
	t = *lnk;
	int modnum = 0;
	printf("请输入需要修改的id：\n");
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
	printf("无此id!\n");
	return 1;
}
int searchContact(Contact** lnk){
	assert(lnk);
	Contact* t = NULL;
	t = *lnk;
	char name[20] = { 0 };
	printf("请输入需要查找的名字：\n");
	scanf("%s", name);
	while (t){
		if (strcmp(t->p.name,name)== 0 ){
			printf("id：%d\t name:%s\t telnum:%s\t\n", t->p.id, t->p.name, t->p.telnum);
			return 0;
		}
		t = t->next;
	}
	printf("查无此人!\n");
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
		printf("保存失败，请从新操作\n");
		return -1;
	}
	while (t != NULL){
		fprintf(fp, "\n%d %s %s", t->p.id, t->p.name, t->p.telnum);
		t = t->next;
	}
	fclose(fp);
	fp = NULL;
	printf("保存成功\n");
	return 0;
}
int destroyContact(Contact* lnk);