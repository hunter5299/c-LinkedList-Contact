#pragma once
#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>
#define NAME_MAX 20
#define TL_MAX 20
#define FILENAME "contact.txt"
typedef struct Person{
	int id;
	char name[NAME_MAX];
	char telnum[TL_MAX];
}Person;
typedef struct address{
	Person p;	//Êý¾ÝÓò
	struct address* next;	
}Contact;
void menu();
int initc(Contact** linkedlist,char* filename);
int addContact(Contact** lnk);
int delContact(Contact** lnk);
int modContact(Contact** lnk);
int searchContact(Contact** lnk);
int showContact(Contact** lnk);
int sortContact(Contact** lnk);
int saveContact(Contact** lnk, char* filename);
int destroyContact(Contact* lnk);