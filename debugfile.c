#include"debugfile.h"
void putchart()
{
    printf("���\tʱ��\t\t���\t\t����ͺ�\t����\t\t�ܼ�\t\t������\t\t��Ʒ\n");
            printf("%d\t%s%s%s%s%s%s%d%s%.2f%s%s%s%s",\
/*���*/        1,\
/*ʱ��*/        "12.12  08:15",\
                tabs("12.12 08:15"),\
/*���*/        "Graphics card",\
                tabs("Graphics card"),\
/*�ͺ�*/        "Quadro GT",\
                tabs("Quadro GT"),\
/*����*/        555,\
                tabi(555),\
/*�ܼ�*/        6660.00,\
                tabf(6660.00),\
/*������*/      "Alpha",\
                tabs("Alpha"),
/*��Ʒ*/        "��\n");
}
