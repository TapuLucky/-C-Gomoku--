#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h> //界面库
#include<conio.h>   //输入输出库

#include"Mystack.h" //自写栈头文件
#include"MyLinkList.h"  //自写双链表头文件
#include"Appearance.h"  //界面外观头文件

#define MAXSIZE 15  //标准棋盘大小

int p[MAXSIZE][MAXSIZE];    //储存对局信息
char buffer[2*MAXSIZE+1][4*MAXSIZE+3];  //输出缓冲区
int count;    //回合数
int Now;      //表示当前玩家，黑为1，白为2
//int Cx,Cy;    //当前光标的位置
int wl,wp;    //当前写入缓冲器的行数和列数
char* Text;   //在界面上给用户的提示

int Puting;   //表示当前是否可以走棋
int Exiting;  //当棋盘上无子时表示退出程序，返回1；当场上有子时表示悔棋，返回2
int ExitRep;  //当回放结束时询问是否退出回放，返回1；其余状况下返回2

void Initialize()   //初始化一个对局
{
    int i,j;
    Text="";        //重置显示信息
    count = 0;      //初始化回合数为0
    Rcd_Now=Rcd_Begin=New_Rcd();
    for(i=0;i<MAXSIZE;i++)      //初始化对局信息
        for(j=0;j<MAXSIZE;j++)
            p[i][j] = 0;
    Cx = Cy = MAXSIZE/2;        //初始化光标位置
    Now = 1;        //初始化为黑方先行
}

void Exit()         //检查是否为退出
{
	if(Exiting)     //如果是第二次按下ESC
	{
		exit(0);
	}
	else            //如果是第一次按下ESC则询问是否退出程序
	{
		Text = "是否确认退出？再次按下ESC退出，其他键返回";
		Exiting = 1;  //指示已经按下过ESC
	}
}

void Exit_Replay()  //检查是否退出回放
{
    if(ExitRep)
    {
        ExitRep = 2;
    }
    else
    {
        Text="是否退出？再次后移退出回放，其他键返回";
        ExitRep = 1;
    }
}

char* Copy(char* str1,const char* str2)   //字符串复制函数，忽略末端的\0
{
	char* str = str1;   //新建字符串
	while (*str2!='\0') //复制非空字符
	{
		*str1++=*str2++;
	}
	return str;         //返回复制完成的字符串
}

char* Creat_Board(int i,int j)    //用制表符绘制棋盘
{
    if(p[i][j]==1)      //1为黑子
        return "●";
    else if(p[i][j]==2) //2为白子
        return "○";
    else if(i==0&&j==0) //以下为边缘棋盘样式
        return "╔";
    else if(i==MAXSIZE-1&&j==0)
        return "╗";
    else if(i==MAXSIZE-1&&j==MAXSIZE-1)
        return "╝";
    else if(i==0&&j==MAXSIZE-1)
        return "╚";
    else if(i==0)
        return "╟";
    else if(i==MAXSIZE-1)
        return "╢";
    else if(j==0)
        return "╤";
    else if(j==MAXSIZE-1)
        return "╧";
    return "┼";
}

char* Creat_Cursor(int i,int j)   //制表符来模拟光标的显示
{
	if(Puting)     //可走棋时光标为粗线
	{
		if(i==Cx){
			if(j==Cy)
				return "┏";
			else if (j==Cy+1)
				return "┗";
		}
		else if(i==Cx+1)
		{
			if(j==Cy)
				return "┓";
			else if (j==Cy+1)
				return "┛";
		}
	}
	else            //不可走棋时光标为虚线
	{
		if(i==Cx){
			if(j==Cy)
				return "┌";
			else if (j==Cy+1)
				return "└";
		}
		else if(i==Cx+1)
		{
			if(j==Cy)
				return "┐";
			else if (j==Cy+1)
				return "┘";
		}
	}
	return "　";     //如果不属于光标范围则为空
}

void write(char* c)     //向缓冲区写入字符串
{
	Copy(buffer[wl] + wp,c);
	wp += strlen(c);
}

void Add_line()         //缓冲区位置换行
{
	wl += 1;    //行数+1
	wp = 0;     //列数置零
}

void Display()          //将缓冲区内容输出到屏幕
{
	int i,l = strlen(Text);         //l为中间文字信息的长度
	int Offset = MAXSIZE*2+2-l/2;   //算出中间文字信息居中所在的横坐标位置
	if(Offset%2==1)                 //如果位置为奇数，则移动到偶数,防止显示错乱
	{
		Offset--;
	}
	Copy(buffer[MAXSIZE]+Offset,Text);  //将文字信息复制到缓冲器
	if(l%2==1)            //如果中间文字长度为奇数，则补上空格，防止显示错乱
	{
		*(buffer[MAXSIZE]+Offset+l)=0x20;
	}
	system("cls");        //清屏，准备写入信息
	for(i=0;i<MAXSIZE*2+1;i++){     //循环写入每一行
		printf("%s",buffer[i]);
		if(i<MAXSIZE*2)             //写入完每一行需要换行
			printf("\n");
	}
}

void Painting()         //将棋盘算出并储存到缓冲器，然后调用Display函数显示出来
{
	int i,j;    //循环变量
	wl=0;       //缓冲器行列数置零
	wp=0;
	for(j=0;j<=MAXSIZE;j++)
	{
		for(i=0;i<=MAXSIZE;i++)
		{
			write(Creat_Cursor(i,j));//写入左上角字符
			if(j==0||j==MAXSIZE)     //如果是棋上下盘边缘则没有连接的竖线，用空格填充位置
			{
				if(i!=MAXSIZE)
					write("　");
			}
			else                     //如果在棋盘中间则用竖线承接上下
			{
				if(i==0||i==MAXSIZE-1)//左右边缘的竖线用双线
					write("║");
				else if(i!=MAXSIZE)   //中间的竖线
					write("│");
			}
		}
		if(j==MAXSIZE)
		{
			break;
		}
		Add_line();                   //换行开始打印交点内容
		write("　");                  //用空位补齐位置
		for(i=0;i<MAXSIZE;i++)        //按横坐标循环
		{
			write(Creat_Board(i,j));  //写入交点字符
			if(i!=MAXSIZE-1)          //如果不在最右侧则补充一个横线承接左右
			{
				if(j==0||j==MAXSIZE-1)
				{
					write("═");       //上下边缘的横线用双线
				}
				else
				{
					write("─");       //中间的横线
				}
			}
		}
		Add_line();                   //写完一行后换行
	}
	Display();                        //将缓冲器内容输出到屏幕
}

int Check()             //遍历棋盘判断胜负
{
    Attention();
	int w=1,x=1,y=1,z=1,i;   //记录当前点四周的连续相同棋子数目
	for(i=1;i<5;i++)
        if(Cy+i<=MAXSIZE&&p[Cx][Cy+i]==Now)
            w++;
        else break;     //向下遍历
	for(i=1;i<5;i++)
        if(Cy-i>=0&&p[Cx][Cy-i]==Now)
            w++;
        else break;     //向上遍历
	if(w>=5)
        return Now;     //若达到5个则判断当前玩家为赢家
	for(i=1;i<5;i++)
        if(Cx+i<=MAXSIZE&&p[Cx+i][Cy]==Now)
            x++;
        else break;     //向右遍历
	for(i=1;i<5;i++)
        if(Cx-i>=0&&p[Cx-i][Cy]==Now)
            x++;
        else break;     //向左遍历
	if(x>=5)
        return Now;     //若达到5个则判断当前玩家为赢家
	for(i=1;i<5;i++)
        if(Cx+i<=MAXSIZE&&Cy+i<=MAXSIZE&&p[Cx+i][Cy+i]==Now)
            y++;
        else break;     //向右下遍历
	for(i=1;i<5;i++)
        if(Cx-i>=0&&Cy-i>=0&&p[Cx-i][Cy-i]==Now)
            y++;
        else break;     //向左上遍历
	if(y>=5)
        return Now;     //若达到5个则判断当前玩家为赢家
	for(i=1;i<5;i++)
        if(Cx+i<=MAXSIZE&&Cy-i>=0&&p[Cx+i][Cy-i]==Now)
            z++;
        else break;     //向右上遍历
	for(i=1;i<5;i++)
        if(Cx-i>=0&&Cy+i<=MAXSIZE&&p[Cx-i][Cy+i]==Now)
            z++;
        else break;     //向左下遍历
	if(z>=5)
        return Now;     //若达到5个则判断当前玩家为赢家
	return 0;           //若没有检查到五子连珠，则返回0表示还没有玩家达成胜利
}

int Put()               //在当前光标位置落子
{
	if(Puting)
	{
		p[Cx][Cy]=Now;//改变该位置数据
		Add_Rcd();
		return 1;     //返回1表示成功
	}
	else
		return 0;
}

void Regret()           //悔棋
{
    if(Del_Rcd()){                  //删除当前节点
		p[Rcd_Now->X][Rcd_Now->Y]=0;//删除当前的棋子
		if(Rcd_Now->Back==NULL)     //如果删除的是第一颗子则将光标移动到第一颗子原来的位置上
		{
			Cx=Rcd_Now->X;
			Cy=Rcd_Now->Y;
		}
		else                    //否则将光标移动到上一颗子上
		{
			Cx=Rcd_Now->Back->X;
			Cy=Rcd_Now->Back->Y;
		}
		Attention();
		Now=3-Now;  //反转当前黑白方
	}
	else
	{
		Exit();     //如果没有棋子可以撤销，则询问退出
	}
}

void Return()           //取消悔棋
{
    if(S.top != S.base) //栈不为空
    {
        Now = Pop(&S);  //当前黑白方出栈
        Cy = Pop(&S);   //当前横纵坐标出栈
        Cx = Pop(&S);
        p[Cx][Cy]=Now;  //改变该位置数据
        Add_Rcd();      //添加节点
        Painting();     //打印棋盘
        Attention();    //变更黑白方提示信息
        Now = 3-Now;    //交换当前黑白方
        count++;        //回合数+1
    }
    else
    {
        Text="栈为空，请继续落子";
        Painting();
    }
}

void Replay_Mode()      //复盘回放模块
{
    int i,j;
    MessageBox(NULL,TEXT("回放中按左键后退\n右键或空格前进，Esc退出"),TEXT("提示"),MB_OK);
    system("title 回放中按左键后退，右键或空格前进，Esc退出");
    Text="";    //重置显示信息
	count=0;    //回合数归零
	Puting=0;   //不可走棋状态
	Rcd_Begin->Back=New_Rcd();
	Rcd_Begin->Back->Next=Rcd_Begin;
	Rcd_Begin=Rcd_Begin->Back;
	for(i=0;i<MAXSIZE;i++)  //重置对局信息
	{
		for(j=0;j<MAXSIZE;j++)
		{
			p[i][j]=0;
		}
	}
	Now=1;      //重置当前为黑方
}

void Replay_Go()        //回放模式前进
{
	if(Rcd_Now->Next->Next!=NULL)     //检查回放是否完毕
	{
		Rcd_Now=Rcd_Now->Next;        //当前节点推至下一个记录节点
		p[Rcd_Now->X][Rcd_Now->Y]=Now;//按照记录还原一个回合
		Cx=Rcd_Now->X;                //设置光标位置
		Cy=Rcd_Now->Y;
		Now=3-Now;                    //转换当前的黑白方
	}
	else                //若回放完毕则询问退出
	{
		Exit_Replay();
	}
}

void Replay_Back()      //回放模式后退
{
	if(Rcd_Now->Back!=NULL)         //检查回放是否完毕
	{
		p[Rcd_Now->X][Rcd_Now->Y]=0;//按照记录后退一个回合
		if(Rcd_Now->Back->Back==NULL)//在整个棋盘没有棋子时隐藏光标
		{
			Cx=-2;
			Cy=-2;
		}
		else if(Rcd_Now->Back==NULL)//在只有一个棋子时移动光标到这个棋子的位置
		{
			Cx=Rcd_Now->X;
			Cy=Rcd_Now->Y;
		}
		else            //其余情况下移动光标到上一回合的位置
		{
			Cx=Rcd_Now->Back->X;
			Cy=Rcd_Now->Back->Y;
		}
		Rcd_Now=Rcd_Now->Back;  //当前节点后退至上一个记录节点
		Now=3-Now;              //转换当前的黑白方
	}
}

void Replay()           //开始回放
{
	int input;      //输入变量
	Replay_Mode();  //初始化回放模式
	Rcd_Now=Rcd_Begin;//从头开始回放
	Replay_Go();    //显示第一次走棋
	while(1)        //开始循环，直到Esc退出
	{
		if(ExitRep==2)
		{
			ExitRep=0;
			break;
		}
		Painting();      //打印棋盘
		input=getch();//等待键盘按下一个字符
		if(input==27) //如果是ESC则退出回放
		{
			return;
		}
		else if(input==0x20)//如果是空格则前进
		{
			Replay_Go();
			continue;
		}
		else if(input==0xE0)//如果按下的是方向键，会填充两次输入，第一次为0xE0表示按下的是控制键
		{
			input=getch();//获得第二次输入信息
			switch(input)//判断方向键方向并移动光标位置
			{
			case 0x4B:
				Replay_Back();//向左后退
				break;
			case 0x4D:
				Replay_Go();//向右前进
				continue;
			}
		}
		ExitRep=0;   //未再次按后移则不准备退出
		Text="";    //重置显示信息
	}
}

void Replay_get()       //判断是否开始回放
{
    int input;
    input=getch();
    if(input=='R'||input=='r')
    {
        Replay();
    }
}

int RunGame()           //程序运行，返回赢家信息
{
    InitStack(&S);
    int input;          //输入变量
    int victor;         //赢家信息
    Initialize();       //初始化对局
    while(1){           //游戏循环，直到出现胜利或平局
    Puting = p[Cx][Cy] == 0;
    Painting();         //打印棋盘
    input=getch();      //等待键盘按下一个字符
    if(input==27)       //如果输入是ESC则悔棋或者退出程序
    {
        Push(&S,Cx);    //将当前的横纵坐标入栈
        Push(&S,Cy);
        Push(&S,3-Now); //将当前黑白方入栈
        Regret();       //悔棋
        Painting();     //打印棋盘
        continue;
    }
    else if(input=='0') //如果输入是0则取消悔棋
    {
        Return();       //取消悔棋
        continue;
    }
    else if(input==0x20)//如果是空格则开始走子
    {
        ClearStack(&S); //落子时要清空栈，避免取消悔棋时输入错误的点
        if(Put())       //如果走子成功则判断胜负
        {
            victor=Check();
            Now=3-Now;  //轮换当前走子玩家
            count++;
            if(victor==1)   //如果黑方达到胜利，显示提示文字并等待一次按键，返回胜利信息
            {
                Painting(); //打印棋盘
                MessageBox(NULL,TEXT("黑方胜利！"),TEXT("提示"),MB_OK);
                Text="按r键查看回放，其余任意键重新开始";
                Painting();     //打印提示
                Replay_get();   //读取字符，判断是否开始回放
                return Now;
            }
            else if(victor==2)//如果白方达到胜利，显示提示文字并等待一次按键，返回胜利信息
            {
                Painting(); //打印棋盘
                MessageBox(NULL,TEXT("白方胜利！"),TEXT("提示"),MB_OK);
                Text="按r键查看回放，其余任意键重新开始";
                Painting();
                Replay_get();   //读取字符，判断是否开始回放
                return Now;
            }
            else if(count>=MAXSIZE*MAXSIZE*0.8)//如果回合数大于棋盘总量的80%，即为平局
            {
                Painting(); //打印棋盘
                MessageBox(NULL,TEXT("平局！"),TEXT("提示"),MB_OK);
                Text="按r键查看回放，其余任意键重新开始";
                Painting();
                Replay_get();   //读取字符，判断是否开始回放
                Clean_Rcd();    //清空储存信息
                return 0;
            }
        }
    }
    else if(input==0xE0)//如果按下的是方向键，会填充两次输入，第一次为0xE0表示按下的是控制键
    {
        input=getch();//获得第二次输入信息
        switch(input)//判断方向键方向并移动光标位置
        {
            case 0x4B://
                Cx--;
                break;
            case 0x48:
                Cy--;
                break;
            case 0x4D:
                Cx++;
                break;
            case 0x50:
                Cy++;
                break;
        }
        if(Cx<0)Cx=MAXSIZE-1;//如果光标位置越界则移动到对侧
        if(Cy<0)Cy=MAXSIZE-1;
        if(Cx>MAXSIZE-1)Cx=0;
        if(Cy>MAXSIZE-1)Cy=0;
    }
        Exiting=0;//未再次按下ESC则不准备退出
		Text="";
    }
}

int Attention()         //提示当前为哪方走子
{
    if(Now == 1)
        system("title 当前为白方走子");
    else if(Now == 2)
        system("title 当前为黑方走子");
}

int main()      //主函数
{
    Look();     //界面外观以及使用教程
    while(1)    //循环游戏
    {
        RunGame();
    }
    return 0;
}


