#ifndef MYSTACK_H_INCLUDED
#define MYSTACK_H_INCLUDED

#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10

typedef struct      //ջ�ṹ��
{
    int * base;
    int * top;
    int stacksize;
}SqStack;

SqStack S;          //����һ��ջS

void InitStack(SqStack * s)     //�½���ջ
{
    s->base = (int *)malloc(STACK_INIT_SIZE*sizeof(int));
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
}

void Push(SqStack *s, int e)    //Ԫ����ջ
{
    if (s->top - s->base >= s->stacksize)
    {
        s->base = (int *)realloc(s->base, (s->stacksize + STACKINCREMENT)*sizeof(int));
        s->top = s->base + s->stacksize;    //���ջ������Ϊ��������Ŀռ�
        s->stacksize += STACKINCREMENT;
    }
    *s->top = e;
    s->top++;
}

int Pop(SqStack *s)             //Ԫ�س�ջ
{
    int i;
    if (s->top == s->base)
        return 0;
    s->top--;
    i = *s->top;
    return i;       //iΪ��ջԪ��
}

void ClearStack(SqStack *S)     //���ջ
{
    S->top = S->base;
}

#endif // MYSTACK_H_INCLUDED
