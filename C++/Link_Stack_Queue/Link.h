#ifndef LINK_H
#define LINK_H


struct Node
{
	Node(int val = 0);
	int value;
	Node *pnext;
};

//实现带有头结点的单链表
class Link
{
public:
	//构造头结点
	Link();
	//释放链表
	~Link();
	//头插法
	void insertHead(int val);
	//尾插法
	void insertTail(int val);
	//删除元素
	void deleteNode(int val);
	//打印链表的
	void modify(int data, int m);
	void show();
	
private:
	Node *phead;
};


#endif