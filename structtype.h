#ifndef STRUCTTYPE_H_INCLUDED
#define STRUCTTYPE_H_INCLUDED
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<windows.h>
#include<io.h>
#define size 1000
#define maxsize 2000000000
/*��¼����*/
typedef enum recordtype
{
    nullrecord,stock,wholesale,retail,present//�����ͣ�����,����,����,��Ʒ
}Recordtype;

/*�ͻ�����*/
typedef enum clienttype
{
    nullclient,individual,group//�����ͣ����ˣ�����
}Clienttype;

/*�Ա�*/
typedef enum gender
{
    nullgender,male,female//�ޣ��У�Ů
}Gender;

/*������*/
struct b_supply
{
    int id;
    char name[size];
    double modify;
    struct b_supply *next;
};
typedef struct b_supply Supply;

/*����ͺ�*/
struct c_parttype
{
    int id;//����ͺű�ţ�ͷ�����Ϊ0
    char name[size];//����ͺ�����
    int store;//������
    char partman[size];//������
    int keynum;//�ٽ����������򳬹�ָ������������Ʒ
    double stock_price;//��������
    double wholesale_price;//��������
    double retail_price;//���۵���
    double modify;//���۶�̬����ָ��
};
typedef struct c_parttype Parttype;

/*���*/
struct b_part
{
    int id;//�����ţ�ͷ�����Ϊ0
    char name[size];//�������
//    Parttype *c_parttype;//����ͺ�
//    struct b_part *c_partnext;
};
typedef struct b_part Part;

/*����*/
struct b_date
{
    int month;//��
    int day;//��
    int hour;//ʱ
    int minute;//��
};
typedef struct b_date Date;

/*�ͻ���Ϣ*/
struct b_client
{
    int id;//�ͻ���ţ�ͷ�����Ϊ0
    double modify;
    Clienttype c_clienttype;//�ͻ�����:����/����
    Gender gender;//�ͻ��Ա�(��Ϊ����)
    char name[size];//�ͻ�����
    char unit[size];//�ͻ���λ
    struct b_client *next;
};
typedef struct b_client Client;

/*����*/
struct Present_node
{
    Part *part;
    Parttype *parttype;
    int amount;
    struct Present_node *next;
};
typedef struct Present_node Present;


/**��¼**/
struct a_record
{
    int id;//��¼��ţ�ͷ�����Ϊ0
    Recordtype recordtype;//��¼����:��,����,����,����
    Date b_date;//���ڣ���Ʒ������
    Part *b_part;//���
    Parttype *b_parttype;//����ͺ�
    Supply *b_supply;//�����̣�����Ҫ����ռ䣩
    Client *b_client;//�ͻ�������Ҫ����ռ䣩
    int amount;//����
    double unit_price;//����
    double total_price;//�ܼ�
    Present *b_present;//��Ʒ����
    int color;//��ɫ��Ĭ��Ϊ0
    struct a_record *b_recordnext;
};
typedef struct a_record Record;


/*���ݿ�*/
struct B_data_part_type
{
    Parttype data;
    struct B_data_part_type *next;
};
typedef struct B_data_part_type Parttype_list;

struct A_data_part
{
    Part data;
    struct A_data_part *next;
    Parttype_list *type_list;
};
typedef struct A_data_part Part_list;


extern int monthday[13];
extern double money;
extern Part_list *datapart;
extern Supply *datasupply;
extern Client *dataclient;
extern Record *recordall;
#endif // STRUCTTYPE_H_INCLUDED
