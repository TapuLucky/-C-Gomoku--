#ifndef MYLINKLIST_H_INCLUDED
#define MYLINKLIST_H_INCLUDED

int Cx,Cy;    //��ǰ����λ��

typedef struct rcd* Record;     //�ṹ��ָ��
typedef struct rcd record;      //�ṹ��ڵ�
Record Rcd_Now,Rcd_Begin;       //��ǰ������Ϣ���һ��������Ϣ

struct rcd    //��˫����ṹ���¼�����Ϣ
{
    int X;    //��ǰ��¼�ĺ�������
    int Y;
    Record Next;    //��һ��
    Record Back;    //��һ��
};

Record New_Rcd()    //��ʼ��˫����
{
	Record r=(Record)malloc(sizeof(record));//��ʼ���ռ�
	r->Next=NULL;   //ǰ��ڵ���Ϊ��
	r->Back=NULL;
	return r;
}

void Add_Rcd()      //��ӽڵ�
{
	Rcd_Now->X=Cx;  //��¼����
	Rcd_Now->Y=Cy;
	Rcd_Now->Next=New_Rcd();    //������һ���ڵ�
	Rcd_Now->Next->Back=Rcd_Now;//��ǰ�ڵ�Ϊ��һ�ڵ��ǰ�ýڵ�
	Rcd_Now=Rcd_Now->Next;      //��ǰ��¼��������һ���ڵ�
}

int Del_Rcd()       //ɾ����ǰ�ڵ㣬����1Ϊɾ���ɹ���0Ϊɾ��ʧ��
{
	Record b;   //��һ���ڵ�
	if(Rcd_Now->Back!=NULL)
	{
		b=Rcd_Now->Back;    //bΪ��һ���ڵ�
		free(Rcd_Now);      //�ͷŵ�ǰ�ڵ�
		Rcd_Now=b;          //��ǰ��¼������һ���ڵ�
		return 1;
	}
	else
		return 0;           //û�нڵ��ɾ��ʱ
}

void Clean_Rcd()    //�������
{
	Record n;   //��һ���ڵ�
	while(Rcd_Begin->Next!=NULL)//ɾ�����м�¼
	{
		n=Rcd_Begin->Next;  //nΪ��һ���ڵ�
		free(Rcd_Begin);    //�ͷŵ�ǰ�ڵ�
		Rcd_Begin=n;        //��ǰ��¼��������һ���ڵ�
	}
}


#endif // MYLINKLIST_H_INCLUDED
