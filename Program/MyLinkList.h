#ifndef MYLINKLIST_H_INCLUDED
#define MYLINKLIST_H_INCLUDED

int Cx,Cy;    //当前光标的位置

typedef struct rcd* Record;     //结构体指针
typedef struct rcd record;      //结构体节点
Record Rcd_Now,Rcd_Begin;       //当前落子信息与第一个落子信息

struct rcd    //用双链表结构体记录棋局信息
{
    int X;    //当前记录的横纵坐标
    int Y;
    Record Next;    //下一步
    Record Back;    //上一步
};

Record New_Rcd()    //初始化双链表
{
	Record r=(Record)malloc(sizeof(record));//初始化空间
	r->Next=NULL;   //前后节点置为空
	r->Back=NULL;
	return r;
}

void Add_Rcd()      //添加节点
{
	Rcd_Now->X=Cx;  //记录坐标
	Rcd_Now->Y=Cy;
	Rcd_Now->Next=New_Rcd();    //创建下一个节点
	Rcd_Now->Next->Back=Rcd_Now;//当前节点为下一节点的前置节点
	Rcd_Now=Rcd_Now->Next;      //当前记录后移至下一个节点
}

int Del_Rcd()       //删除当前节点，返回1为删除成功，0为删除失败
{
	Record b;   //上一个节点
	if(Rcd_Now->Back!=NULL)
	{
		b=Rcd_Now->Back;    //b为上一个节点
		free(Rcd_Now);      //释放当前节点
		Rcd_Now=b;          //当前记录回至上一个节点
		return 1;
	}
	else
		return 0;           //没有节点可删除时
}

void Clean_Rcd()    //清空链表
{
	Record n;   //下一个节点
	while(Rcd_Begin->Next!=NULL)//删除所有记录
	{
		n=Rcd_Begin->Next;  //n为下一个节点
		free(Rcd_Begin);    //释放当前节点
		Rcd_Begin=n;        //当前记录后移至下一个节点
	}
}


#endif // MYLINKLIST_H_INCLUDED
