#ifndef SMALLFUNCTION_H_INCLUDED
#define SMALLFUNCTION_H_INCLUDED
#include"structtype.h"

/*数据库相关*/
Part *key_part_list(char *part_name);//返回输入配件名称的数据库
Parttype_list *key_part_parttype(char *part_name);//返回输入配件名称的配件型号数据库头
Parttype *key_parttype_list(char *part_name,char *parttype_name);//返回输入配件型号名称的数据库
Supply *key_supply_list(char *supply_name);//返回输入供货商名称的数据库
Client *key_client_list(char *client_name);//返回输入客户名称的数据库

/*输出相关*/
int output_record(Record** choose_record);//输出记录，返回值为记录编号的最大值（章门）
void output_chart_head(int mode);//输出表格眉头
void output_chart_head_1(int mode);//输出查询记录列表的表格眉头
int output_part_data(Part_list** choose_part);//输出配件数据库，返回值为配件数据库的最大值（章门）
void output_part_dataone(Part *head,int i);//输出一条配件数据库（章门）
int output_parttype_data(Parttype_list *head,Parttype_list** choose_parttype);//输出配件型号数据库（章门）
void output_parttype_dataone(Parttype *head,int i);//输出一条配件型号数据（章门）
int output_client_data(Client *head,Client** choose_client);//输出客户数据库（章门）
void output_client_dataone(Client *head,int i);//输出一条客户数据库（章门）
int output_supply_data(Supply *head,Supply** choose_supply);//输出供货商数据库（章门）
void output_supply_dataone(Supply *head,int i);//输出一条供货商记录（章门）
void output_one(Record *head,int mode,int i);//输出一条记录（章门）
void outputmod1(Record **sdata,int cnt,int pj);//查找记录具体信息
void outrec_mod0(int flag,Record **save,int cnt,int typ);//输出简略查询结果
void output_money();//输出金钱

/*链表修改相关*/
void sorttime(Record *p);//按照时间顺序插入指定结点（李墨馨）
void dropoff(Record *p);//将某一节点摘下
void randpre(int amount,Present *pre);//把礼物数组随机排序
void solve_record(Record *key_record,int mode);//结算记录
void solve_record_vir(Record *key_record,double *virmoney);//模拟结算记录（错误检测用）

/*计算相关*/
double all_sell_amount(Part *keypart);//计算同配件不同型号产品的总销售数量
void linear_regression(double x[], double y[], double *b, double *a);//生成一个线性回归方程
int KmpSearch(char* s, char* p);//KMP算法
double total_sales(Record *p);//从（销售）记录中求总价和 （求销售总额）（魏来）
double total_profit(Record* p);//从（销售）记录中求总盈利（魏来）

/*日期相关*/
int leap_year(int year);//判断闰年（章门）
int nowyear();//返回当前年份（网络）
int judgedate(Date date);//判断给定日期是否合法（章门）
int timecmp(Date t1,Date t2);//比较两个日期的先后 t1大返回1，t2大返回-1，相等返回0（李墨馨）
void timestr(char *savestr,Date date,int mode);//将日期转换为字符串（章门）

/*制表符格式控制*/
char *tabs(char *str);//根据字符串长度返回不同的制表符（章门）
char *tabi(int num);//根据整数的大小返回不同的制表符（章门）
char *tabf(double num);//根据浮点数的大小返回不同的制表符（章门）

/*错误判断*/
int judge_choice(int maxid);//对输入的编号进行判断
int error_judge();//错误判断（主菜单）
int error_judge_2();//不显示提示的错误检测
void wait_enter();//操作成功，等待

/*常用功能*/
void headvalue();//哨兵结点初始化
void randnum(int maxnum,int amount,int *a);//生成amount个从1到maxnum的随机数，存储在a数组里
void color_change(short x);//修改字体颜色，10号为绿色
void strtrans(Record *p,char *recstr);//将记录转换成字符串

#endif // SMALLFUNCTION_H_INCLUDED
