#ifndef APPEARANCE_H_INCLUDED
#define APPEARANCE_H_INCLUDED

int MARK = 0; //��ʼ������Ϸʱ�ĸ�����ʾ

void Look()             //��������Լ�ʹ�ý̳�
{
    system("title ������-����׿");    //���ñ���
    system("mode con cols=63 lines=32");    //���ô��ڴ�С
    int ret;
    MessageBox(NULL,TEXT("��ӭ�������������������"),TEXT("��ʾ"),MB_OK);
    MessageBox(NULL,TEXT("�㽫�÷�������ƹ���ƶ�\n            �ո������"),TEXT("��ʾ"),MB_OK);
    MessageBox(NULL,TEXT("��Ϸ�а�ESC�����л���\n      ������0��ȡ������"),TEXT("��ʾ"),MB_OK);
    MessageBox(NULL,TEXT("һ�ֽ�������Խ��и��̻ط�"),TEXT("��ʾ"),MB_OK);
    MessageBox(NULL,TEXT("�������Ϸ����������ʾ��Ϣ"),TEXT("��ʾ"),MB_OK);
    ret=MessageBox(NULL,TEXT("��ϣ�������ǲ�ɫ����"),TEXT("����"),MB_YESNO|MB_ICONQUESTION);
    if(ret==IDYES)
    {
        printf("\a");
        MessageBox(NULL,TEXT("�õģ����̽�����Ϊ��ɫ"),TEXT("�ظ�"),MB_OK);
        MARK = 1;
    }
    else
    {
        printf("\a");
        MessageBox(NULL,TEXT("�õ����̽�����Ϊ�ڰ�ɫ"),TEXT("�ظ�"),MB_OK);
    }
    if(MARK)
        system("color E0");     //������ɫΪ�ƺ�
    else
        system("color F0");     //������ɫΪ�ڰ�
    MessageBox(NULL,TEXT("��ô����Ϸ��ʼ�ɣ�"),TEXT("��ʾ"),MB_OK);
}


#endif // APPEARANCE_H_INCLUDED
