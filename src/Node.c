#include "EmpStruct.h"

NODE *createNode()
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    int i;
    for(i=0; i < 3; i++ )
    { 
		node->items[i] =null; 
		node->links[i] = null;
	}
	node->numElements = 0;
	node->links[i] = null;
	return node;
}
void visitNode(NODE* node, void(*f)(EMPLOYEE*, char*))
{
    int i;
    char output[line + 1];
    for(i = 0; i <node->numElements ; i++)
    { f(node->items[i], output); }
}
void destroyNode(NODE** current, void (*f)(EMPLOYEE**))
{
    NODE *node= *current;
	if (node == null){ return; }
    int i;
    for(i = 0; i < node->numElements; i++)
    {
        destroyNode(&(node->links[i]), f);
        f(&(node->items[i]));
    }
	if (node->links[i] != null){ destroyNode(&(node->links[i]), f); }
	free(node);
	node = null;
}
