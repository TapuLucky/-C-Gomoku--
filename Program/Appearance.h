#ifndef APPEARANCE_H_INCLUDED
#define APPEARANCE_H_INCLUDED

int MARK = 0; //开始进入游戏时的各种提示

void Look()             //界面外观以及使用教程
{
    system("title 林煜涛-王少卓");    //设置标题
    system("mode con cols=63 lines=32");    //设置窗口大小
    int ret;
    MessageBox(NULL,TEXT("欢迎进入五子棋的奇妙世界"),TEXT("提示"),MB_OK);
    MessageBox(NULL,TEXT("你将用方向键控制光标移动\n            空格键落子"),TEXT("提示"),MB_OK);
    MessageBox(NULL,TEXT("游戏中按ESC键进行悔棋\n      按数字0键取消悔棋"),TEXT("提示"),MB_OK);
    MessageBox(NULL,TEXT("一局结束后可以进行复盘回放"),TEXT("提示"),MB_OK);
    MessageBox(NULL,TEXT("窗口坐上方会有相关提示信息"),TEXT("提示"),MB_OK);
    ret=MessageBox(NULL,TEXT("你希望棋盘是彩色的吗？"),TEXT("提问"),MB_YESNO|MB_ICONQUESTION);
    if(ret==IDYES)
    {
        printf("\a");
        MessageBox(NULL,TEXT("好的，棋盘将设置为彩色"),TEXT("回复"),MB_OK);
        MARK = 1;
    }
    else
    {
        printf("\a");
        MessageBox(NULL,TEXT("好的棋盘将设置为黑白色"),TEXT("回复"),MB_OK);
    }
    if(MARK)
        system("color E0");     //设置颜色为黄黑
    else
        system("color F0");     //设置颜色为黑白
    MessageBox(NULL,TEXT("那么，游戏开始吧！"),TEXT("提示"),MB_OK);
}


#endif // APPEARANCE_H_INCLUDED
