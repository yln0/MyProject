#include "Link.h"
#include<iostream>
using namespace std;

Node::Node(int val) :value(val), pnext(NULL){}
//构造头结点
Link::Link()
{
	phead = new Node;
	phead->pnext = NULL;
}
//释放链表
Link::~Link()
{
	Node*p = phead;
	while (p->pnext)
	{
		Node*tmp = p->pnext;
		p->pnext = tmp->pnext;
		delete tmp;
	}
	delete phead;//释放头结点
}
//头插法
void Link::insertHead(int val)
{
	Node*t = new Node;
	t->value = val;
	t->pnext = phead->pnext;
	phead->pnext = t;
}
//尾插法
void Link::insertTail(int val)
{
	Node*p = phead;
	for (; p->pnext != NULL; p = p->pnext);
	Node *t = new Node;
	t->value = val;
	p->pnext = t;
	t->pnext = NULL;
}
//删除元素
void Link::deleteNode(int val)
{
	if (phead->pnext == NULL)
		return;
	Node*p = phead;
	bool f = 0;
	for (; p->pnext!= NULL; p = p->pnext)
	{
		if (p->pnext->value == val)
		{	
			f = 1;
			Node*pcur = p->pnext;
			p->pnext = pcur->pnext;
			delete pcur;
		}
		if (p->pnext == NULL)
		{
			break;
		}
		
	}
	if (!f)
	cout << "Failed" << endl;
}
void Link::modify(int data, int m)
{
	if (phead->pnext == NULL)
		return;
	Node*p = phead;
	for (; p->pnext != NULL; p = p->pnext)
	{
		if (p->pnext->value == data)
		{
			p->pnext->value = m;
		}
		if (p->pnext == NULL)
		{
			break;
		}
	}
}
//打印链表的
void Link::show()
{
	Node*p = phead->pnext;
	while (p)
	{
		cout << p->value << " ";
		p = p->pnext;
	}
	cout << endl;
}
