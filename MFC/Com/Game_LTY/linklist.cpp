#include "StdAfx.h"
#include "linklist.h"


linklist::linklist(int alen,int blen)//alen:链表元素的数目　blen:元素中数据的长度
{
	YX * yx = NULL;
	yx = new YX;
	yx->data = new byte[blen];
	ZeroMemory(yx->data,blen);
	yx->id = alen-1;
	yx->next = NULL;
	YX * yo = yx;
	tail = yx ;

	for(int i=0;i<alen-1;i++)
	{
		yx  = new YX;
		yx->data = new byte[blen];
		ZeroMemory(yx->data,blen);
		yx->id = alen-2-i;
		yx->next = yo;
		yo = yx;
	}
	head = yx;
	tail->next = head;
	YX * cur = head;
	for(int i=0;i<alen;i++)
	{
		cur->next->prev = cur;
		cur = cur->next;
	}
}


linklist::~linklist(void)
{

}
