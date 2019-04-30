#ifndef MAINFUNCTION_H_INCLUDED
#define MAINFUNCTION_H_INCLUDED
#include"structtype.h"
/*���ݿ�Ĵ���*/
Part_list *loadpart(char *filename);//�����ݿ��ж�ȡ���
Supply *loadsupply(char *filename);//�����ݿ��ж�ȡ������
Client *loadclient(char *filename);//�����ݿ��ж�ȡ�ͻ�
void load_record_from_file(char *filename);//���ļ��ж�ȡ��¼
void save_record_to_file(char *filename);//�Ѽ�¼�����ļ���
void save_supply_to_file(char *filename);//�ѵ�ǰ��������Ϣ�����ļ�
void save_client_to_file(char *filename);//�ѵ�ǰ�ͻ���Ϣ�����ļ�

void Client_add();//���ӿͻ�
void Client_delete();//ɾ���ͻ�
void Supply_add();//���ӹ�����
void Supply_delete();//ɾ��������

void add_record_from_system();//ʵʱó��
void add_record_present(Present *pre_way[3][5],int present_amount);//�������ַ��������ڶ�άָ�������У�ÿ�ַ��������5�����

void change_time(Record *p);//�޸�ʱ��
void change_recordtype(Record *p);//�޸ļ�¼����
void change_part(Record *p);//�޸����
void change_parttype(Record *p);//�޸�����ͺ�
void change_unitprice(Record *p);//�޸ĵ���
void change_amount(Record *p);//�޸�����
void change_supply(Record *p);//�޸Ĺ�����
void change_client(Record *p);//�޸Ŀͻ�
void change_present(Record *p);//�޸���Ʒ

void del_one_record(Record *key);//ɾ��һ����¼
void add_record_from_file();//���ļ�����Ӽ�¼

void history_file();//������ʷ��¼

void store_form(Part_list* p);//���ɿ�汨��κ����
void present_form(Record *p);//ͳ��������Ʒ�����κ����

void searchall();//��ѯ���м�¼
void searchpart();//�����Ӧ��¼����
void searchclient();//�ͻ���Ӧ��¼����
void searchsupply();//�����̶�Ӧ��¼����
void searchperiod();//ʱ����ڼ�¼����
void fuzzysearch();//ģ����ѯ

void unit_price_change();//���۵Ķ�̬�仯
void suggest_in();//��������

void price_predict(Part* key_part,Parttype* key_parttype);//�۸�Ԥ��

void del_all();//ɾ�����м�¼
#endif // MAINFUNCTION_H_INCLUDED
