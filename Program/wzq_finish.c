#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<windows.h> //�����
#include<conio.h>   //���������

#include"Mystack.h" //��дջͷ�ļ�
#include"MyLinkList.h"  //��д˫����ͷ�ļ�
#include"Appearance.h"  //�������ͷ�ļ�

#define MAXSIZE 15  //��׼���̴�С

int p[MAXSIZE][MAXSIZE];    //����Ծ���Ϣ
char buffer[2*MAXSIZE+1][4*MAXSIZE+3];  //���������
int count;    //�غ���
int Now;      //��ʾ��ǰ��ң���Ϊ1����Ϊ2
//int Cx,Cy;    //��ǰ����λ��
int wl,wp;    //��ǰд�뻺����������������
char* Text;   //�ڽ����ϸ��û�����ʾ

int Puting;   //��ʾ��ǰ�Ƿ��������
int Exiting;  //������������ʱ��ʾ�˳����򣬷���1������������ʱ��ʾ���壬����2
int ExitRep;  //���طŽ���ʱѯ���Ƿ��˳��طţ�����1������״���·���2

void Initialize()   //��ʼ��һ���Ծ�
{
    int i,j;
    Text="";        //������ʾ��Ϣ
    count = 0;      //��ʼ���غ���Ϊ0
    Rcd_Now=Rcd_Begin=New_Rcd();
    for(i=0;i<MAXSIZE;i++)      //��ʼ���Ծ���Ϣ
        for(j=0;j<MAXSIZE;j++)
            p[i][j] = 0;
    Cx = Cy = MAXSIZE/2;        //��ʼ�����λ��
    Now = 1;        //��ʼ��Ϊ�ڷ�����
}

void Exit()         //����Ƿ�Ϊ�˳�
{
	if(Exiting)     //����ǵڶ��ΰ���ESC
	{
		exit(0);
	}
	else            //����ǵ�һ�ΰ���ESC��ѯ���Ƿ��˳�����
	{
		Text = "�Ƿ�ȷ���˳����ٴΰ���ESC�˳�������������";
		Exiting = 1;  //ָʾ�Ѿ����¹�ESC
	}
}

void Exit_Replay()  //����Ƿ��˳��ط�
{
    if(ExitRep)
    {
        ExitRep = 2;
    }
    else
    {
        Text="�Ƿ��˳����ٴκ����˳��طţ�����������";
        ExitRep = 1;
    }
}

char* Copy(char* str1,const char* str2)   //�ַ������ƺ���������ĩ�˵�\0
{
	char* str = str1;   //�½��ַ���
	while (*str2!='\0') //���Ʒǿ��ַ�
	{
		*str1++=*str2++;
	}
	return str;         //���ظ�����ɵ��ַ���
}

char* Creat_Board(int i,int j)    //���Ʊ����������
{
    if(p[i][j]==1)      //1Ϊ����
        return "��";
    else if(p[i][j]==2) //2Ϊ����
        return "��";
    else if(i==0&&j==0) //����Ϊ��Ե������ʽ
        return "�X";
    else if(i==MAXSIZE-1&&j==0)
        return "�[";
    else if(i==MAXSIZE-1&&j==MAXSIZE-1)
        return "�a";
    else if(i==0&&j==MAXSIZE-1)
        return "�^";
    else if(i==0)
        return "�c";
    else if(i==MAXSIZE-1)
        return "�f";
    else if(j==0)
        return "�h";
    else if(j==MAXSIZE-1)
        return "�k";
    return "��";
}

char* Creat_Cursor(int i,int j)   //�Ʊ����ģ�������ʾ
{
	if(Puting)     //������ʱ���Ϊ����
	{
		if(i==Cx){
			if(j==Cy)
				return "��";
			else if (j==Cy+1)
				return "��";
		}
		else if(i==Cx+1)
		{
			if(j==Cy)
				return "��";
			else if (j==Cy+1)
				return "��";
		}
	}
	else            //��������ʱ���Ϊ����
	{
		if(i==Cx){
			if(j==Cy)
				return "��";
			else if (j==Cy+1)
				return "��";
		}
		else if(i==Cx+1)
		{
			if(j==Cy)
				return "��";
			else if (j==Cy+1)
				return "��";
		}
	}
	return "��";     //��������ڹ�귶Χ��Ϊ��
}

void write(char* c)     //�򻺳���д���ַ���
{
	Copy(buffer[wl] + wp,c);
	wp += strlen(c);
}

void Add_line()         //������λ�û���
{
	wl += 1;    //����+1
	wp = 0;     //��������
}

void Display()          //�������������������Ļ
{
	int i,l = strlen(Text);         //lΪ�м�������Ϣ�ĳ���
	int Offset = MAXSIZE*2+2-l/2;   //����м�������Ϣ�������ڵĺ�����λ��
	if(Offset%2==1)                 //���λ��Ϊ���������ƶ���ż��,��ֹ��ʾ����
	{
		Offset--;
	}
	Copy(buffer[MAXSIZE]+Offset,Text);  //��������Ϣ���Ƶ�������
	if(l%2==1)            //����м����ֳ���Ϊ���������Ͽո񣬷�ֹ��ʾ����
	{
		*(buffer[MAXSIZE]+Offset+l)=0x20;
	}
	system("cls");        //������׼��д����Ϣ
	for(i=0;i<MAXSIZE*2+1;i++){     //ѭ��д��ÿһ��
		printf("%s",buffer[i]);
		if(i<MAXSIZE*2)             //д����ÿһ����Ҫ����
			printf("\n");
	}
}

void Painting()         //��������������浽��������Ȼ�����Display������ʾ����
{
	int i,j;    //ѭ������
	wl=0;       //����������������
	wp=0;
	for(j=0;j<=MAXSIZE;j++)
	{
		for(i=0;i<=MAXSIZE;i++)
		{
			write(Creat_Cursor(i,j));//д�����Ͻ��ַ�
			if(j==0||j==MAXSIZE)     //������������̱�Ե��û�����ӵ����ߣ��ÿո����λ��
			{
				if(i!=MAXSIZE)
					write("��");
			}
			else                     //����������м��������߳н�����
			{
				if(i==0||i==MAXSIZE-1)//���ұ�Ե��������˫��
					write("�U");
				else if(i!=MAXSIZE)   //�м������
					write("��");
			}
		}
		if(j==MAXSIZE)
		{
			break;
		}
		Add_line();                   //���п�ʼ��ӡ��������
		write("��");                  //�ÿ�λ����λ��
		for(i=0;i<MAXSIZE;i++)        //��������ѭ��
		{
			write(Creat_Board(i,j));  //д�뽻���ַ�
			if(i!=MAXSIZE-1)          //����������Ҳ��򲹳�һ�����߳н�����
			{
				if(j==0||j==MAXSIZE-1)
				{
					write("�T");       //���±�Ե�ĺ�����˫��
				}
				else
				{
					write("��");       //�м�ĺ���
				}
			}
		}
		Add_line();                   //д��һ�к���
	}
	Display();                        //�������������������Ļ
}

int Check()             //���������ж�ʤ��
{
    Attention();
	int w=1,x=1,y=1,z=1,i;   //��¼��ǰ�����ܵ�������ͬ������Ŀ
	for(i=1;i<5;i++)
        if(Cy+i<=MAXSIZE&&p[Cx][Cy+i]==Now)
            w++;
        else break;     //���±���
	for(i=1;i<5;i++)
        if(Cy-i>=0&&p[Cx][Cy-i]==Now)
            w++;
        else break;     //���ϱ���
	if(w>=5)
        return Now;     //���ﵽ5�����жϵ�ǰ���ΪӮ��
	for(i=1;i<5;i++)
        if(Cx+i<=MAXSIZE&&p[Cx+i][Cy]==Now)
            x++;
        else break;     //���ұ���
	for(i=1;i<5;i++)
        if(Cx-i>=0&&p[Cx-i][Cy]==Now)
            x++;
        else break;     //�������
	if(x>=5)
        return Now;     //���ﵽ5�����жϵ�ǰ���ΪӮ��
	for(i=1;i<5;i++)
        if(Cx+i<=MAXSIZE&&Cy+i<=MAXSIZE&&p[Cx+i][Cy+i]==Now)
            y++;
        else break;     //�����±���
	for(i=1;i<5;i++)
        if(Cx-i>=0&&Cy-i>=0&&p[Cx-i][Cy-i]==Now)
            y++;
        else break;     //�����ϱ���
	if(y>=5)
        return Now;     //���ﵽ5�����жϵ�ǰ���ΪӮ��
	for(i=1;i<5;i++)
        if(Cx+i<=MAXSIZE&&Cy-i>=0&&p[Cx+i][Cy-i]==Now)
            z++;
        else break;     //�����ϱ���
	for(i=1;i<5;i++)
        if(Cx-i>=0&&Cy+i<=MAXSIZE&&p[Cx-i][Cy+i]==Now)
            z++;
        else break;     //�����±���
	if(z>=5)
        return Now;     //���ﵽ5�����жϵ�ǰ���ΪӮ��
	return 0;           //��û�м�鵽�������飬�򷵻�0��ʾ��û����Ҵ��ʤ��
}

int Put()               //�ڵ�ǰ���λ������
{
	if(Puting)
	{
		p[Cx][Cy]=Now;//�ı��λ������
		Add_Rcd();
		return 1;     //����1��ʾ�ɹ�
	}
	else
		return 0;
}

void Regret()           //����
{
    if(Del_Rcd()){                  //ɾ����ǰ�ڵ�
		p[Rcd_Now->X][Rcd_Now->Y]=0;//ɾ����ǰ������
		if(Rcd_Now->Back==NULL)     //���ɾ�����ǵ�һ�����򽫹���ƶ�����һ����ԭ����λ����
		{
			Cx=Rcd_Now->X;
			Cy=Rcd_Now->Y;
		}
		else                    //���򽫹���ƶ�����һ������
		{
			Cx=Rcd_Now->Back->X;
			Cy=Rcd_Now->Back->Y;
		}
		Attention();
		Now=3-Now;  //��ת��ǰ�ڰ׷�
	}
	else
	{
		Exit();     //���û�����ӿ��Գ�������ѯ���˳�
	}
}

void Return()           //ȡ������
{
    if(S.top != S.base) //ջ��Ϊ��
    {
        Now = Pop(&S);  //��ǰ�ڰ׷���ջ
        Cy = Pop(&S);   //��ǰ���������ջ
        Cx = Pop(&S);
        p[Cx][Cy]=Now;  //�ı��λ������
        Add_Rcd();      //��ӽڵ�
        Painting();     //��ӡ����
        Attention();    //����ڰ׷���ʾ��Ϣ
        Now = 3-Now;    //������ǰ�ڰ׷�
        count++;        //�غ���+1
    }
    else
    {
        Text="ջΪ�գ����������";
        Painting();
    }
}

void Replay_Mode()      //���̻ط�ģ��
{
    int i,j;
    MessageBox(NULL,TEXT("�ط��а��������\n�Ҽ���ո�ǰ����Esc�˳�"),TEXT("��ʾ"),MB_OK);
    system("title �ط��а�������ˣ��Ҽ���ո�ǰ����Esc�˳�");
    Text="";    //������ʾ��Ϣ
	count=0;    //�غ�������
	Puting=0;   //��������״̬
	Rcd_Begin->Back=New_Rcd();
	Rcd_Begin->Back->Next=Rcd_Begin;
	Rcd_Begin=Rcd_Begin->Back;
	for(i=0;i<MAXSIZE;i++)  //���öԾ���Ϣ
	{
		for(j=0;j<MAXSIZE;j++)
		{
			p[i][j]=0;
		}
	}
	Now=1;      //���õ�ǰΪ�ڷ�
}

void Replay_Go()        //�ط�ģʽǰ��
{
	if(Rcd_Now->Next->Next!=NULL)     //���ط��Ƿ����
	{
		Rcd_Now=Rcd_Now->Next;        //��ǰ�ڵ�������һ����¼�ڵ�
		p[Rcd_Now->X][Rcd_Now->Y]=Now;//���ռ�¼��ԭһ���غ�
		Cx=Rcd_Now->X;                //���ù��λ��
		Cy=Rcd_Now->Y;
		Now=3-Now;                    //ת����ǰ�ĺڰ׷�
	}
	else                //���ط������ѯ���˳�
	{
		Exit_Replay();
	}
}

void Replay_Back()      //�ط�ģʽ����
{
	if(Rcd_Now->Back!=NULL)         //���ط��Ƿ����
	{
		p[Rcd_Now->X][Rcd_Now->Y]=0;//���ռ�¼����һ���غ�
		if(Rcd_Now->Back->Back==NULL)//����������û������ʱ���ع��
		{
			Cx=-2;
			Cy=-2;
		}
		else if(Rcd_Now->Back==NULL)//��ֻ��һ������ʱ�ƶ���굽������ӵ�λ��
		{
			Cx=Rcd_Now->X;
			Cy=Rcd_Now->Y;
		}
		else            //����������ƶ���굽��һ�غϵ�λ��
		{
			Cx=Rcd_Now->Back->X;
			Cy=Rcd_Now->Back->Y;
		}
		Rcd_Now=Rcd_Now->Back;  //��ǰ�ڵ��������һ����¼�ڵ�
		Now=3-Now;              //ת����ǰ�ĺڰ׷�
	}
}

void Replay()           //��ʼ�ط�
{
	int input;      //�������
	Replay_Mode();  //��ʼ���ط�ģʽ
	Rcd_Now=Rcd_Begin;//��ͷ��ʼ�ط�
	Replay_Go();    //��ʾ��һ������
	while(1)        //��ʼѭ����ֱ��Esc�˳�
	{
		if(ExitRep==2)
		{
			ExitRep=0;
			break;
		}
		Painting();      //��ӡ����
		input=getch();//�ȴ����̰���һ���ַ�
		if(input==27) //�����ESC���˳��ط�
		{
			return;
		}
		else if(input==0x20)//����ǿո���ǰ��
		{
			Replay_Go();
			continue;
		}
		else if(input==0xE0)//������µ��Ƿ������������������룬��һ��Ϊ0xE0��ʾ���µ��ǿ��Ƽ�
		{
			input=getch();//��õڶ���������Ϣ
			switch(input)//�жϷ���������ƶ����λ��
			{
			case 0x4B:
				Replay_Back();//�������
				break;
			case 0x4D:
				Replay_Go();//����ǰ��
				continue;
			}
		}
		ExitRep=0;   //δ�ٴΰ�������׼���˳�
		Text="";    //������ʾ��Ϣ
	}
}

void Replay_get()       //�ж��Ƿ�ʼ�ط�
{
    int input;
    input=getch();
    if(input=='R'||input=='r')
    {
        Replay();
    }
}

int RunGame()           //�������У�����Ӯ����Ϣ
{
    InitStack(&S);
    int input;          //�������
    int victor;         //Ӯ����Ϣ
    Initialize();       //��ʼ���Ծ�
    while(1){           //��Ϸѭ����ֱ������ʤ����ƽ��
    Puting = p[Cx][Cy] == 0;
    Painting();         //��ӡ����
    input=getch();      //�ȴ����̰���һ���ַ�
    if(input==27)       //���������ESC���������˳�����
    {
        Push(&S,Cx);    //����ǰ�ĺ���������ջ
        Push(&S,Cy);
        Push(&S,3-Now); //����ǰ�ڰ׷���ջ
        Regret();       //����
        Painting();     //��ӡ����
        continue;
    }
    else if(input=='0') //���������0��ȡ������
    {
        Return();       //ȡ������
        continue;
    }
    else if(input==0x20)//����ǿո���ʼ����
    {
        ClearStack(&S); //����ʱҪ���ջ������ȡ������ʱ�������ĵ�
        if(Put())       //������ӳɹ����ж�ʤ��
        {
            victor=Check();
            Now=3-Now;  //�ֻ���ǰ�������
            count++;
            if(victor==1)   //����ڷ��ﵽʤ������ʾ��ʾ���ֲ��ȴ�һ�ΰ���������ʤ����Ϣ
            {
                Painting(); //��ӡ����
                MessageBox(NULL,TEXT("�ڷ�ʤ����"),TEXT("��ʾ"),MB_OK);
                Text="��r���鿴�طţ�������������¿�ʼ";
                Painting();     //��ӡ��ʾ
                Replay_get();   //��ȡ�ַ����ж��Ƿ�ʼ�ط�
                return Now;
            }
            else if(victor==2)//����׷��ﵽʤ������ʾ��ʾ���ֲ��ȴ�һ�ΰ���������ʤ����Ϣ
            {
                Painting(); //��ӡ����
                MessageBox(NULL,TEXT("�׷�ʤ����"),TEXT("��ʾ"),MB_OK);
                Text="��r���鿴�طţ�������������¿�ʼ";
                Painting();
                Replay_get();   //��ȡ�ַ����ж��Ƿ�ʼ�ط�
                return Now;
            }
            else if(count>=MAXSIZE*MAXSIZE*0.8)//����غ�����������������80%����Ϊƽ��
            {
                Painting(); //��ӡ����
                MessageBox(NULL,TEXT("ƽ�֣�"),TEXT("��ʾ"),MB_OK);
                Text="��r���鿴�طţ�������������¿�ʼ";
                Painting();
                Replay_get();   //��ȡ�ַ����ж��Ƿ�ʼ�ط�
                Clean_Rcd();    //��մ�����Ϣ
                return 0;
            }
        }
    }
    else if(input==0xE0)//������µ��Ƿ������������������룬��һ��Ϊ0xE0��ʾ���µ��ǿ��Ƽ�
    {
        input=getch();//��õڶ���������Ϣ
        switch(input)//�жϷ���������ƶ����λ��
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
        if(Cx<0)Cx=MAXSIZE-1;//������λ��Խ�����ƶ����Բ�
        if(Cy<0)Cy=MAXSIZE-1;
        if(Cx>MAXSIZE-1)Cx=0;
        if(Cy>MAXSIZE-1)Cy=0;
    }
        Exiting=0;//δ�ٴΰ���ESC��׼���˳�
		Text="";
    }
}

int Attention()         //��ʾ��ǰΪ�ķ�����
{
    if(Now == 1)
        system("title ��ǰΪ�׷�����");
    else if(Now == 2)
        system("title ��ǰΪ�ڷ�����");
}

int main()      //������
{
    Look();     //��������Լ�ʹ�ý̳�
    while(1)    //ѭ����Ϸ
    {
        RunGame();
    }
    return 0;
}


