#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"structtype.h"
#include"smallfunction.h"
#include"mainfunction.h"
#include"interface.h"
void initialize();//��ʼ������
int main(void)
{
    initialize();//��ʼ��
    main_title();
    return 0;
}
void initialize()
{
    if(leap_year(nowyear()))//��������꣬����Ϊ29��
        monthday[2]=29;
    money = 5000000;//��ʼ�ʽ������
    datapart=loadpart("data\\part.txt");//��ȡ�����Ϣ
    datasupply=loadsupply("data\\supply.txt");//��ȡ��������Ϣ
    dataclient=loadclient("data\\client.txt");//��ȡ�ͻ���Ϣ
    headvalue(recordall);//�½���¼ͷ��㲢��ʼ��
    load_record_from_file("save\\savedata.txt");//��ȡ��¼
    unit_price_change();//�۸�̬�仯
}
