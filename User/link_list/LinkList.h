#ifndef _LINKLIST_H
#define _LINKLIST_H
#include "sys.h"


typedef double* DListDataType;

typedef struct DListElement_
{
	DListDataType* data;
	struct DListElement_* prev;
	struct DListElement_* next;
}DListElement;

typedef struct DList_
{
	int size;
	DListElement *head;
	DListElement *tail;
}*Dlist, dList;


Dlist InitDList(void);
int dlist_ins_prev(Dlist list, DListElement *element, const void *data);
int dlist_ins_next(Dlist list, DListElement *element, const void *data);
int dlist_rm_node(Dlist list, DListElement *element, void **data);
int dlist_clear(Dlist list);
#endif
