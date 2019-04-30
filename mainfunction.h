#ifndef MAINFUNCTION_H_INCLUDED
#define MAINFUNCTION_H_INCLUDED
#include"structtype.h"
/*数据库的处理*/
Part_list *loadpart(char *filename);//从数据库中读取配件
Supply *loadsupply(char *filename);//从数据库中读取供货商
Client *loadclient(char *filename);//从数据库中读取客户
void load_record_from_file(char *filename);//从文件中读取记录
void save_record_to_file(char *filename);//把记录存在文件中
void save_supply_to_file(char *filename);//把当前供货商信息存入文件
void save_client_to_file(char *filename);//把当前客户信息存入文件

void Client_add();//增加客户
void Client_delete();//删除客户
void Supply_add();//增加供货商
void Supply_delete();//删除供货商

void add_record_from_system();//实时贸易
void add_record_present(Present *pre_way[3][5],int present_amount);//生成三种方案，存于二维指针数组中，每种方案最多有5种配件

void change_time(Record *p);//修改时间
void change_recordtype(Record *p);//修改记录类型
void change_part(Record *p);//修改配件
void change_parttype(Record *p);//修改配件型号
void change_unitprice(Record *p);//修改单价
void change_amount(Record *p);//修改数量
void change_supply(Record *p);//修改供货商
void change_client(Record *p);//修改客户
void change_present(Record *p);//修改赠品

void del_one_record(Record *key);//删除一条记录
void add_record_from_file();//从文件中添加记录

void history_file();//保存历史记录

void store_form(Part_list* p);//生成库存报表（魏来）
void present_form(Record *p);//统计所有赠品情况（魏来）

void searchall();//查询所有记录
void searchpart();//配件对应记录查找
void searchclient();//客户对应记录查找
void searchsupply();//供货商对应记录查找
void searchperiod();//时间段内记录查找
void fuzzysearch();//模糊查询

void unit_price_change();//单价的动态变化
void suggest_in();//进货建议

void price_predict(Part* key_part,Parttype* key_parttype);//价格预测

void del_all();//删除所有记录
#endif // MAINFUNCTION_H_INCLUDED
