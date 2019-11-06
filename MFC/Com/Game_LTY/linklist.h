#pragma once

typedef struct _YX
{
	byte * data;
	int id;
	_YX * next;
	_YX * prev;
}YX;

class linklist
{
public:
	linklist(int alen,int blen);//alen:链表元素的数目　blen:元素中数据的长度
	~linklist(void);
	YX * head;
	YX * tail;
};

