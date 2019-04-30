#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED
#include"structtype.h"
void main_title();//主菜单
void searchfunc();//查询记录
void change_record();//更改记录
void add_record();//增加记录
void trans_record();//修改记录（区别于change，是change的子功能）
void trans_one_record(Record *p);//修改记录项目
void del_record();//删除记录
void count_data();//统计数据
void smart_analyse();//智能分析
void price_predict_choose();//价格预测选择菜单
void high_change();//高级设置
void high_change_supply();//供货商管理菜单
void high_change_client();//客户管理菜单
void high_change_del();//清空记录
void high_change_replace();//替换记录
#endif // INTERFACE_H_INCLUDED
