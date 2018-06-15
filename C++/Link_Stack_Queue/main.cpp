
#include<iostream>
using namespace std;

#include "Link.h"
#include "Queue.h"
#include "Stack.h"

/*
要求如下：
1，软件运行以后，打印一个menu界面，显示支持的数据结构，如下：
=====================================
1.单链表  2.循环队列  3.顺序栈  4.退出系统
=====================================
请选择：

2.用户选择4，输出byebye，系统退出！，如果选择1，2，3项，进入
子菜单，显示如下：
=======================
当前数据结构为： xxx
1.增加
2.删除
3.修改
4.查询
5.返回
=======================
请选择：

1.增加:提示用户输入一个或者一组整数，添加到数据结构当中，显示
增加成功或者失败，完成后，继续显示子菜单
2.删除：输入指定的值，在数据结构中全部删除掉，显示结果，完成后，继续显示子菜单
3.修改：提示输入需要修改的数据，再输入修改后的数据，进行全文修改，显示结果，完成后，继续显示子菜单
4.查询：显示数据结构所有的数据
5.返回：返回主菜单

*/
int data;
bool flag = 0;

const int OPERATE_LINK = 1;
const int OPERATE_STACK = 2;
const int OPERATE_QUEUE = 3;
const int OPERATE_QUIT = 4;
//子菜单
const int CHILD_ADD = 1;
const int CHILD_DEL = 2;
const int CHILD_MOD = 3;
const int CHILD_SER = 4;
const int CHILD_EXIT = 5;


class DTSystem
{
public:
	DTSystem() 
		:isRunning(true)
		,isChildRunning(true){}
	void run();
	void showMainMenu()
	{
		cout << "===================" << endl;
		cout << "1.单链表" << endl;
		cout << "2.顺序栈" << endl;
		cout << "3.循环队列" << endl;
		cout << "4.退出系统" << endl;
		cout << "===================" << endl;
	}

	void Add()//增加
	{
		cout << "请输入需要添加的数据:";
		while (cin >> data)
		{
			switch (mChoice)
			{
			case OPERATE_LINK:mLink.insertTail(data); break;
			case OPERATE_STACK:mStack.push(data); break;
			case OPERATE_QUEUE:mQueue.addQue(data); break;
			default:break;
			}
			if (getchar() == '\n')
			{
				flag = true;
				break;
			}
		}
		if (flag)
			cout << "添加成功！" << endl;
		else
			cout << "添加失败" << endl;
	}
	void Del()
	{
		switch (mChoice)
		{
			case OPERATE_LINK:
			{
				cout << "请输入所要删除的数据:";cin >> data;
				mLink.deleteNode(data); break;
			}
			case OPERATE_STACK:mStack.pop(); break;
			case OPERATE_QUEUE:mQueue.delQue(); break;
			default:break;
		}
	}
	void Mod()
	{
		cout << "请输入需要修改的数据及修改后的数据：";
		int m;
		cin >> data >> m;
		switch (mChoice)
		{
		case OPERATE_LINK:mLink.modify(data, m);; break;
		case OPERATE_STACK:mStack.modify(data,m); break;
		case OPERATE_QUEUE:mQueue.modify(data,m); break;
		default:break;
		}
	}
	void Show()
	{
		switch (mChoice)
		{
		case OPERATE_LINK:mLink.show(); break;
		case OPERATE_STACK:mStack.show(); break;
		case OPERATE_QUEUE:mQueue.show(); break;
		default:break;
		}
	}
	void Child_return()
	{
		isChildRunning = false;
	}

	//做链表操作
	void doLink();
	//做栈操作
	void doStack();
	//做队列操作
	void doQueue();
	//做退出操作
	void doQuit()
	{
		isRunning = false;
	}

	void showChildMenu(char *name)
	{
		cout << "-------------------------------" << endl;
		cout << "	当前数据结构为：" << name << endl;
		cout << "	1.添加" << endl;
		cout << "	2.删除" << endl;
		cout << "	3.修改" << endl;
		cout << "	4.查询" << endl;
		cout << "	5.返回" << endl;
		cout << "-------------------------------" << endl;
	}
private:
	//三个数据结构的对象
	Link mLink;
	SqStack mStack;
	CircleQue mQueue;
	bool isRunning;
	bool isChildRunning;
	int mChoice;//Main
	int nChoice;//Child
};
typedef void (DTSystem::*PFUNC)();
typedef struct
{
	int choice;
	PFUNC pfunc;
}ElemType;
//事件驱动的表结构
ElemType mainMenuTable[] =
{
	{ OPERATE_LINK, &DTSystem::doLink },
	{ OPERATE_STACK, &DTSystem::doStack },
	{ OPERATE_QUEUE, &DTSystem::doQueue },
	{ OPERATE_QUIT, &DTSystem::doQuit },
};
//子菜单
ElemType Child_Table[] =
{
	{ CHILD_ADD, &DTSystem::Add },
	{ CHILD_DEL, &DTSystem::Del },
	{ CHILD_MOD, &DTSystem::Mod },
	{ CHILD_SER, &DTSystem::Show },
	{ CHILD_EXIT, &DTSystem::Child_return },
};

int mainMenuTableSize = sizeof(mainMenuTable) / sizeof(mainMenuTable[0]);
int Child_TableSize = sizeof(Child_Table) / sizeof(Child_Table[0]);


void DTSystem::doLink()
{
	while (isChildRunning)
	{
		showChildMenu("单链表");
		cout << "请选择:";
		cin >> nChoice;
		for (int i = 0; i < Child_TableSize; ++i)
		{
			if (nChoice == Child_Table[i].choice)
			{
				(this->*Child_Table[i].pfunc)();
			}
		}
	}
}

void DTSystem::doStack()
{
	while (isChildRunning)
	{
		showChildMenu("顺序栈");
		cout << "请选择:";
		cin >> nChoice;
		for (int i = 0; i < Child_TableSize; ++i)
		{
			if (nChoice == Child_Table[i].choice)
			{
				(this->*Child_Table[i].pfunc)();
			}
		}
	}
}
void DTSystem::doQueue()
{
	while (isChildRunning)
	{
		showChildMenu("循环队列");
		cout << "请选择:";
		cin >> nChoice;
		for (int i = 0; i < Child_TableSize; ++i)
		{
			if (nChoice == Child_Table[i].choice)
			{
				(this->*Child_Table[i].pfunc)();
			}
		}
	}
}

void DTSystem::run()
{
	while (isRunning)
	{
		showMainMenu();
		cout << "请选择:";
		cin >> mChoice;

		//做一个选择的操作，代码固定，增加/删除功能，都不影响以前的代码 =>高内聚/低耦合
		for (int i = 0; i < mainMenuTableSize; ++i)
		{
			if (mChoice == mainMenuTable[i].choice)
			{
				isChildRunning = true;
				(this->*mainMenuTable[i].pfunc)();
			}
		}
	}
	cout << "bye bye!" << endl;
}
int main()
{
	DTSystem sys;
	sys.run();
	return 0;
}