#ifndef SMALLFUNCTION_H_INCLUDED
#define SMALLFUNCTION_H_INCLUDED
#include"structtype.h"

/*���ݿ����*/
Part *key_part_list(char *part_name);//��������������Ƶ����ݿ�
Parttype_list *key_part_parttype(char *part_name);//��������������Ƶ�����ͺ����ݿ�ͷ
Parttype *key_parttype_list(char *part_name,char *parttype_name);//������������ͺ����Ƶ����ݿ�
Supply *key_supply_list(char *supply_name);//�������빩�������Ƶ����ݿ�
Client *key_client_list(char *client_name);//��������ͻ����Ƶ����ݿ�

/*������*/
int output_record(Record** choose_record);//�����¼������ֵΪ��¼��ŵ����ֵ�����ţ�
void output_chart_head(int mode);//������üͷ
void output_chart_head_1(int mode);//�����ѯ��¼�б�ı��üͷ
int output_part_data(Part_list** choose_part);//���������ݿ⣬����ֵΪ������ݿ�����ֵ�����ţ�
void output_part_dataone(Part *head,int i);//���һ��������ݿ⣨���ţ�
int output_parttype_data(Parttype_list *head,Parttype_list** choose_parttype);//�������ͺ����ݿ⣨���ţ�
void output_parttype_dataone(Parttype *head,int i);//���һ������ͺ����ݣ����ţ�
int output_client_data(Client *head,Client** choose_client);//����ͻ����ݿ⣨���ţ�
void output_client_dataone(Client *head,int i);//���һ���ͻ����ݿ⣨���ţ�
int output_supply_data(Supply *head,Supply** choose_supply);//������������ݿ⣨���ţ�
void output_supply_dataone(Supply *head,int i);//���һ�������̼�¼�����ţ�
void output_one(Record *head,int mode,int i);//���һ����¼�����ţ�
void outputmod1(Record **sdata,int cnt,int pj);//���Ҽ�¼������Ϣ
void outrec_mod0(int flag,Record **save,int cnt,int typ);//������Բ�ѯ���
void output_money();//�����Ǯ

/*�����޸����*/
void sorttime(Record *p);//����ʱ��˳�����ָ����㣨��īܰ��
void dropoff(Record *p);//��ĳһ�ڵ�ժ��
void randpre(int amount,Present *pre);//�����������������
void solve_record(Record *key_record,int mode);//�����¼
void solve_record_vir(Record *key_record,double *virmoney);//ģ������¼���������ã�

/*�������*/
double all_sell_amount(Part *keypart);//����ͬ�����ͬ�ͺŲ�Ʒ������������
void linear_regression(double x[], double y[], double *b, double *a);//����һ�����Իع鷽��
int KmpSearch(char* s, char* p);//KMP�㷨
double total_sales(Record *p);//�ӣ����ۣ���¼�����ܼۺ� ���������ܶ��κ����
double total_profit(Record* p);//�ӣ����ۣ���¼������ӯ����κ����

/*�������*/
int leap_year(int year);//�ж����꣨���ţ�
int nowyear();//���ص�ǰ��ݣ����磩
int judgedate(Date date);//�жϸ��������Ƿ�Ϸ������ţ�
int timecmp(Date t1,Date t2);//�Ƚ��������ڵ��Ⱥ� t1�󷵻�1��t2�󷵻�-1����ȷ���0����īܰ��
void timestr(char *savestr,Date date,int mode);//������ת��Ϊ�ַ��������ţ�

/*�Ʊ����ʽ����*/
char *tabs(char *str);//�����ַ������ȷ��ز�ͬ���Ʊ�������ţ�
char *tabi(int num);//���������Ĵ�С���ز�ͬ���Ʊ�������ţ�
char *tabf(double num);//���ݸ������Ĵ�С���ز�ͬ���Ʊ�������ţ�

/*�����ж�*/
int judge_choice(int maxid);//������ı�Ž����ж�
int error_judge();//�����жϣ����˵���
int error_judge_2();//����ʾ��ʾ�Ĵ�����
void wait_enter();//�����ɹ����ȴ�

/*���ù���*/
void headvalue();//�ڱ�����ʼ��
void randnum(int maxnum,int amount,int *a);//����amount����1��maxnum����������洢��a������
void color_change(short x);//�޸�������ɫ��10��Ϊ��ɫ
void strtrans(Record *p,char *recstr);//����¼ת�����ַ���

#endif // SMALLFUNCTION_H_INCLUDED
