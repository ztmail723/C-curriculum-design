#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include"structtype.h"
void main_title();//���˵�
void searchfunc();//��ѯ��¼
void change_record();//���ļ�¼
void add_record();//���Ӽ�¼
void trans_record();//�޸ļ�¼��������change����change���ӹ��ܣ�
void trans_one_record(Record *p);//�޸ļ�¼��Ŀ
void del_record();//ɾ����¼
void count_data();//ͳ������
void smart_analyse();//���ܷ���
void price_predict_choose();//�۸�Ԥ��ѡ��˵�
void high_change();//�߼�����
void high_change_supply();//�����̹���˵�
void high_change_client();//�ͻ�����˵�
void high_change_del();//��ռ�¼
void high_change_replace();//�滻��¼
#endif // INTERFACE_H_INCLUDED
