#ifndef empStructs_h_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define maxEmp 100
#define empSize 30
#define line 80
#define options 8

#ifndef null 
#define null ( (void *) 0)
#endif

#define false 0;
#define true 1;
#define fail -1;

#define ORDER234 4

typedef struct EMP
{
	int ID;
	char name[empSize];
	double salary;
} EMPLOYEE;
typedef struct NODELINK
{
    int numElements;
    EMPLOYEE *items[3];
    struct NODELINK *links[4];
} NODE;
typedef struct TREENODE
{
	int freeCount;
	int freeList[maxEmp];

	NODE *root;
} TREE;

void deleteEmp(EMPLOYEE**);
EMPLOYEE* createEmp(char*, double, int);
char* printEmp(EMPLOYEE*, char*);

void initializeTree(TREE*);
EMPLOYEE* insert(TREE*, char*, double);
int delete(TREE*, int);
void deleteAll(NODE*);
EMPLOYEE* find(NODE*, int);
int traverse(NODE*, void(*) (EMPLOYEE*, char*));

NODE *createNode();
void visitNode(NODE*, void(*)(EMPLOYEE*, char*));
void destroyNode(NODE**, void (*)(EMPLOYEE**));



#endif