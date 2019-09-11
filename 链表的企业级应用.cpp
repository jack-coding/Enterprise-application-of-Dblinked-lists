#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include<crtdbg.h>

#include<iostream>
#include<windows.h>

#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new(_NORMAL_BLOCK,__FILE__,__LINE__)
#define new DBG_NEW
#endif
#endif 

using namespace std;

typedef struct _DbLinkNode {
	struct _DbLinkNode *next;
	struct _DbLinkNode *prev;
}
DbLinkList,DbLinkNode;

typedef struct {
	int fd;
	time_t timeout;
	DbLinkNode node;
}Conntimeout;

//初始化双向链表
bool Ini_DbLinkNode(DbLinkList &L) {
	L.next = &L;
	L.prev = &L;

	return true;
}
//前插法插入数据
bool DbLinkinsert_front(DbLinkList &L, DbLinkNode &p_In) {
	if (L.next) {
		L.next->prev = &p_In;
	}
	p_In.next = L.next;
	p_In.prev = &L;
	L.next = &p_In;

	return true;
}
bool DbLink_print(DbLinkList  &L) {
	if (!L.next) {
		cout << "\n链表为空!无需打印\n";
		return false;
	}
	DbLinkNode *p = L.next;
	while (p!=&L) {
		int offset = offsetof(Conntimeout, node);
		Conntimeout *temp = (Conntimeout *)((size_t)p - offset);
		cout << "\t结构体首位置:  ox" << temp;
		cout << "\tfd=" << temp->fd << endl;
		p = p->next;
	}
	cout << "\n\t______逆向打印_______\n\n";
	p = p->prev;
	while (p!=&L) {
		int offset = offsetof(Conntimeout, node);
		Conntimeout *temp = (Conntimeout *)((size_t)p - offset);
		cout << "\t结构体首位置:  ox" << temp;
		cout << "\tfd=" << temp->fd << endl;
		p = p->prev;
	}
	cout << endl;
	return true;
}
//销毁链表
bool DbLink_Destroy(DbLinkList &L) {
	DbLinkNode *p = L.next;
	while (p!=&L) {
		int offset = offsetof(Conntimeout, node);
		Conntimeout *c1 = (Conntimeout *)((size_t)p - offset);
		cout << "\t删除结点位置:ox" << c1<<endl;
		p = p->next;
		delete c1;
	}
	int offset = offsetof(Conntimeout, node);
	Conntimeout *c2 = (Conntimeout *)((size_t)p - offset);
	delete c2;
	return true;
}
int main(void) {

	Conntimeout *c1 = new Conntimeout;
	DbLinkNode *p = &(c1->node);
	int n;

	Ini_DbLinkNode(c1->node);
	c1->fd = -1;
	cout << "\n前插插入元素......\n";
	cout << "\n请输入创建元素的个数:";
	cin >> n;
	while (n) {
		Conntimeout *c2 = new Conntimeout;
		cout << "\n请输入元素的文件句柄:";
		cin >> c2->fd;
		DbLinkinsert_front(c1->node, c2->node);
		n--;
	}
	DbLink_print(c1->node);

	if (DbLink_Destroy(c1->node)) {
		cout << "\n双向链表销毁成功!\n";
	}
	else {
		cout << "\n双向链表销毁失败!\n";
	}
	_CrtDumpMemoryLeaks();
	system("pause");
	return 0;
}