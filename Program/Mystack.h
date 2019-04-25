#ifndef MYSTACK_H_INCLUDED
#define MYSTACK_H_INCLUDED

#define STACK_INIT_SIZE 50
#define STACKINCREMENT 10

typedef struct      //栈结构体
{
    int * base;
    int * top;
    int stacksize;
}SqStack;

SqStack S;          //定义一个栈S

void InitStack(SqStack * s)     //新建空栈
{
    s->base = (int *)malloc(STACK_INIT_SIZE*sizeof(int));
    s->top = s->base;
    s->stacksize = STACK_INIT_SIZE;
}

void Push(SqStack *s, int e)    //元素入栈
{
    if (s->top - s->base >= s->stacksize)
    {
        s->base = (int *)realloc(s->base, (s->stacksize + STACKINCREMENT)*sizeof(int));
        s->top = s->base + s->stacksize;    //如果栈满，则为其分配额外的空间
        s->stacksize += STACKINCREMENT;
    }
    *s->top = e;
    s->top++;
}

int Pop(SqStack *s)             //元素出栈
{
    int i;
    if (s->top == s->base)
        return 0;
    s->top--;
    i = *s->top;
    return i;       //i为出栈元素
}

void ClearStack(SqStack *S)     //清空栈
{
    S->top = S->base;
}

#endif // MYSTACK_H_INCLUDED
