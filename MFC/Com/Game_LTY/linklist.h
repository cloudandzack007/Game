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
	linklist(int alen,int blen);//alen:����Ԫ�ص���Ŀ��blen:Ԫ�������ݵĳ���
	~linklist(void);
	YX * head;
	YX * tail;
};

