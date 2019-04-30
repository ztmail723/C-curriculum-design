#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include"structtype.h"
#include"smallfunction.h"
#include"mainfunction.h"
#include"interface.h"
void initialize();//初始化函数
int main(void)
{
    initialize();//初始化
    main_title();
    return 0;
}
void initialize()
{
    if(leap_year(nowyear()))//如果是闰年，二月为29天
        monthday[2]=29;
    money = 5000000;//初始资金五百万
    datapart=loadpart("data\\part.txt");//读取配件信息
    datasupply=loadsupply("data\\supply.txt");//读取供货商信息
    dataclient=loadclient("data\\client.txt");//读取客户信息
    headvalue(recordall);//新建记录头结点并初始化
    load_record_from_file("save\\savedata.txt");//读取记录
    unit_price_change();//价格动态变化
}
