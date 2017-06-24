#include "EmpStruct.h"

void getID(TREE*, int*);
NODE* split(NODE *, NODE *);
void* insertNonfull(NODE *, EMPLOYEE *, NODE *);
void* insertInto(NODE *, EMPLOYEE *, NODE *);

void initializeTree(TREE* empList)
{
    int i;
    for (i = 0; i <= maxEmp; i++)
    { empList->freeList[i] = i+1;}
    empList->freeCount = maxEmp;
    empList->root = createNode();
}
EMPLOYEE* insert(TREE* empList, char* name, double salary)
{
    int ID, i;
	getID(empList, &ID);
	/*check if employee ID already exists*/
    if (find(empList->root, ID) != null){return null;}

    EMPLOYEE* emp = createEmp(name, salary, ID);
    NODE *current = empList->root;

	/*IF root full THEN split and create new root*/
	if (current->numElements == 3)
	{
		NODE *parent = createNode();
		empList->root = parent;
		parent->links[0] = current;
		split(parent, current);
		insertNonfull(parent, emp, null);
	}
	else{ insertNonfull(current, emp, null); }
	return emp;
}
int delete(TREE* empList, int ID)
{
	
	return true;
}
void deleteAll(NODE* node)
{
    destroyNode(&node, deleteEmp);
}
EMPLOYEE* find(NODE* node, int ID)
{
	int i = 1;
    EMPLOYEE* emp = null;
	while (i <= node->numElements && ID > node->items[i - 1]->ID && node->items[i-1] != null) { i++; }
	if (i <= node->numElements && ID == node->items[i-1]->ID)
	{ 
            return node->items[i-1]; 
        }
	if (node->links[i-1] != null) 
        { 
            emp = find(node->links[i - 1], ID); 
        }
	return emp;
}

int traverse(NODE* node, void(*print)(EMPLOYEE*, char*))
{
    /*return false if null*/
    if (node == null){ return false; }
    char output[line+1];
    int i;
    
    /*if leaf print elements*/
    if(node->links[0] == null)
    {
        visitNode(node, print);
        return true;
    }
    
	for (i = 0; i <= node->numElements; i++)
	{
		/*traverse down next link*/
		if (node->links[i] != null) { traverse(node->links[i], print); }

		/*print next element*/
		if (node->items[i] != null && i < 3){ print(node->items[i], output); }
	}
    return true;	
}

void getID(TREE *empList, int* ID)
{
	*ID = empList->freeList[(int)(rand() % (empList->freeCount))];
	int i;
	int found = false;
	/*pulling up free ids after randomly selecting one*/
	for (i = 0; i < empList->freeCount - 1; i++)
	{
		if (empList->freeList[i] == *ID && !found){ found = true; }
		/*pulls up ids after finding hole*/
		if (found) { empList->freeList[i] = empList->freeList[i + 1]; }
	}
	empList->freeCount--;
}
NODE* split(NODE *parent, NODE *current)
{
    NODE *node = createNode();
    node->items[0] = current->items[2];
    node->links[0] = current->links[2];
    node->links[1] = current->links[3];
    node->numElements = 1;
    current->numElements = 1;
    insertInto(parent, current->items[1], node);
    
    current->links[2] = current->links[3] = null;
    current->items[1] = current->items[2] = null;
    return parent;
}
void* insertNonfull(NODE *current, EMPLOYEE *emp, NODE *node)
{
	int i;
	NODE *parent = null;

	/*traverse down the tree until node to insert into is found*/
	while (current != null)
	{
		/*splits current node IF full*/
		if (current->numElements == 3)
		{
			current = split(parent, current);
		}
		/*keeps track of parent node*/
		parent = current;
		/*IF current is LEAF THEN BREAKS loop*/
		if (current->links[0] == null)
		{
			current = null;
		}
		else{/*ELSE find appropiate link to follow*/
			for (i = 0; i < current->numElements; i++)
			{
				if (current->items[i]->ID >= emp->ID)
				{
					break;
				}
			}
			current = current->links[i];
		}
	}
	insertInto(parent, emp, null);
}

void* insertInto(NODE *parent, EMPLOYEE *emp, NODE *node)
{
	int i;
	/*loop through items in node to find correct spot to input emp*/
	for (i = parent->numElements; i > 0; i--)
	{
		/*breaks loop if emp is to be inserted in last spot*/
		if (emp->ID > parent->items[i - 1]->ID)
		{
			break;
		}
		/*pulls items and links forward to make room for new item/node*/
		if (i + 1 != 3){ parent->items[i + 1] = parent->items[i]; }
		parent->items[i] = parent->items[i - 1];
		parent->links[i + 1] = parent->links[i];

	}
	/*place item and node in appropiate space and increments number of elements*/
    parent->items[i] = emp;
    parent->links[i+1] = node;
    parent->numElements++;
}

