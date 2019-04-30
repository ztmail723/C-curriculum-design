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
/*记录类型*/
typedef enum recordtype
{
    nullrecord,stock,wholesale,retail,present//空类型，进货,批发,零售,赠品
}Recordtype;

/*客户类型*/
typedef enum clienttype
{
    nullclient,individual,group//空类型，个人，团体
}Clienttype;

/*性别*/
typedef enum gender
{
    nullgender,male,female//无，男，女
}Gender;

/*供货商*/
struct b_supply
{
    int id;
    char name[size];
    double modify;
    struct b_supply *next;
};
typedef struct b_supply Supply;

/*配件型号*/
struct c_parttype
{
    int id;//配件型号编号，头结点编号为0
    char name[size];//配件型号名称
    int store;//配件库存
    char partman[size];//制造商
    int keynum;//临界数量，购买超过指定数量则有赠品
    double stock_price;//进货单价
    double wholesale_price;//批发单价
    double retail_price;//零售单价
    double modify;//单价动态修正指数
};
typedef struct c_parttype Parttype;

/*配件*/
struct b_part
{
    int id;//配件编号，头结点编号为0
    char name[size];//配件名称
//    Parttype *c_parttype;//配件型号
//    struct b_part *c_partnext;
};
typedef struct b_part Part;

/*日期*/
struct b_date
{
    int month;//月
    int day;//日
    int hour;//时
    int minute;//分
};
typedef struct b_date Date;

/*客户信息*/
struct b_client
{
    int id;//客户编号，头结点编号为0
    double modify;
    Clienttype c_clienttype;//客户类型:个人/团体
    Gender gender;//客户性别(若为个人)
    char name[size];//客户名称
    char unit[size];//客户单位
    struct b_client *next;
};
typedef struct b_client Client;

/*礼物*/
struct Present_node
{
    Part *part;
    Parttype *parttype;
    int amount;
    struct Present_node *next;
};
typedef struct Present_node Present;


/**记录**/
struct a_record
{
    int id;//记录编号，头结点编号为0
    Recordtype recordtype;//记录类型:空,进货,批发,零售
    Date b_date;//日期，赠品无日期
    Part *b_part;//配件
    Parttype *b_parttype;//配件型号
    Supply *b_supply;//供货商（不需要申请空间）
    Client *b_client;//客户（不需要申请空间）
    int amount;//数量
    double unit_price;//单价
    double total_price;//总价
    Present *b_present;//赠品链表
    int color;//颜色，默认为0
    struct a_record *b_recordnext;
};
typedef struct a_record Record;


/*数据库*/
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
