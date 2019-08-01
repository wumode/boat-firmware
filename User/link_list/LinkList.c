#include "LinkList.h"

Dlist InitDList(void)
{
	Dlist L = (Dlist)malloc(sizeof(dList));
	if (L == NULL)
	{
		printf("Defeat!\n");
	}
	return L;
}

int dlist_ins_prev(Dlist list, DListElement *element, const void *data)
{
	DListElement *new_element;
	if (element == NULL && list->size != 0)
		return -1;
	
	if ((new_element = (DListElement *)malloc(sizeof(DListElement))) == NULL)
		return -1;
	
	new_element->data = (DListDataType *)data;
	if (list->size == 0)
	{
		list->head = new_element;
		list->tail = new_element;
		new_element->prev = NULL;
		new_element->next = NULL;
	}
	else
	{
		if (element->prev == NULL) {
			new_element->prev = NULL;
			list->head = new_element;
		}
		else
		{
			element->prev->next = new_element;
			new_element->prev = element->prev;
		}
		element->prev = new_element;
		new_element->next = element;
	}
	
	list->size++;
	
	return 0;
}

int dlist_ins_next(Dlist list, DListElement *element, const void *data)
{
	DListElement *new_element;
	if (element == NULL && list->size != 0)
		return -1;
	if ((new_element = (DListElement *)malloc(sizeof(DListElement))) == NULL)
		return -1;
	new_element->data = (DListDataType *)data;
	if (list->size == 0)
	{
		list->head = new_element;
		list->tail = new_element;
		new_element->prev = NULL;
		new_element->next = NULL;
	}
	else
	{
		if (element->next == NULL)
		{

			new_element->next = NULL;
			list->tail = new_element;
		}
		else
		{
			new_element->next = element->next;
			element->next->prev = new_element;

		}
		element->next = new_element;
		new_element->prev = element;
	}
	list->size++;
	return 0;
}

int dlist_rm_node(Dlist list, DListElement *element, void **data)
{
	if (element == NULL || list->size == 0)
		return -1;

	*data = element->data;
	if (element->prev == NULL)
	{
		if (element->next) {
			list->head = element->next;
			list->head->prev = NULL;
		}
		else
		{
			list->head = element->next;
			list->tail = list->head;
		}
	}

	if (element->next == NULL)
	{
		if (element->prev != NULL)
		{
			list->tail = element->prev;
			list->tail->next = NULL;
		}
	}
	else
	{
		element->prev = element->next;
		element->next->prev = element->prev;
	}
	if (element != NULL)
	{
		free(element);
	}
	list->size--;
	return 0;
}

int dlist_clear(Dlist list) {
	DListElement* p;
	DListElement* q;
	p = list->head;
	while (p != NULL)
	{
		q = p;
		p = p->next;
		free(q);
	}
	list->size = 0;
	return 0;
}
