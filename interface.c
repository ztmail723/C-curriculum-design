#include"smallfunction.h"
#include"mainfunction.h"
#include"interface.h"
void main_title()                   //主菜单
{
    while(1)
    {
    system("cls");//清屏
    output_money();
    printf("欢迎使用复兴公司计算机配件销售/管理系统！\n");
    printf("1.查询记录\n\
2.更改记录\n\
3.统计数据\n\
4.智能分析\n\
5.高级设置\n\
6.保存当前记录状态\n\
7.退出系统\n");
    error_judge();//错误判断
    int option_choice=judge_choice(7);
    switch(option_choice)
    {
    case 1:
        if(recordall->b_recordnext==NULL)
        {
            printf("当前记录为空，无法查询！");
            wait_enter(0);
            break;
        }
        searchfunc();
        break;
    case 2:
        change_record();//更改记录
        break;
    case 3:
        if(recordall->b_recordnext==NULL)
        {
            printf("当前记录为空，无法统计！");
            wait_enter(0);
            break;
        }
        count_data();//统计数据
        break;
    case 4:
        if(recordall->b_recordnext==NULL)
        {
            printf("当前记录为空，无法分析！");
            wait_enter(0);
            break;
        }
        smart_analyse();//智能分析
        break;
    case 5:
        high_change();
        break;
    case 6:
        history_file();
        save_record_to_file("save\\savedata.txt");
        printf("保存文件成功！\n过往记录已存于历史文件中！\n");
        wait_enter(4);
        break;
    default:
        //history_file();
        //save_record_to_file("save\\savedata.txt");
        //printf("保存文件成功，按任意键退出！\n");
        //wait_enter();
        return;
    }
    }
}

void searchfunc()                   //1.查询记录
{
    int s_choice;
    while(1)
    {
    system("cls");
    output_money();
    printf("记录查询\n");
    printf("1.查询所有记录\n2.根据配件名称与型号查询\n3.根据客户名称查询\n4.根据供货商名称查询\n5.根据记录时间查询\n6.模糊查询\n7.返回上一步\n");
    s_choice=judge_choice(7);
    switch(s_choice)
    {
    case 1:
        searchall();
        break;
    case 2:
        searchpart();
        break;
    case 3:
        searchclient();
        break;
    case 4:
        searchsupply();
        break;
    case 5:
        searchperiod();
        break;
    case 6:
        fuzzysearch();
        break;
    default:
        return;
    }
    }
}

void change_record()                //2.更改记录
{
    while(1)
    {
        system("cls");//清屏
        output_money();
        printf("1.增加记录\n\
2.删除记录\n\
3.修改记录\n\
4.上一步\n");
        int option_choice=judge_choice(4);
        switch(option_choice)
        {
        case 1:
            add_record();
            break;
        case 2:
            if(recordall->b_recordnext==NULL)
            {
                printf("当前记录为空，无法删除！");
                wait_enter(0);
                break;
            }
            del_record();
            break;
        case 3:
            if(recordall->b_recordnext==NULL)
            {
                printf("当前记录为空，无法修改！");
                wait_enter(0);
                break;
            }
            trans_record();
            break;
        case 4:
            return;
        }
    }
}

void add_record()                   //2.1.增加记录
{
    while(1)
    {
        system("cls");//清屏
        output_money();
        printf("1.从文件中增加完整信息\n\
2.在系统中进行实时贸易\n\
3.上一步\n");
        int option_choice=judge_choice(3);
        switch(option_choice)
        {
        case 1:
            add_record_from_file();
            break;
        case 2:
            unit_price_change();//买东西前，价格参数动态变化
            add_record_from_system();
            break;
        case 3:
            return;
        }
    }
}

void trans_record()                 //2.2.修改记录
{
    Record *choose_record[size];
    int maxrecord,choose_id;
    while(1)
    {
        system("cls");//清屏
        output_money();
        maxrecord=output_record(choose_record);
        printf("请选择你要修改的记录编号(输入%d回到上一步)：\n",maxrecord+1);
        choose_id=judge_choice(maxrecord+1);
        if(choose_id==maxrecord+1)
            return;
        else
            trans_one_record(choose_record[choose_id]);
    }
}

void trans_one_record(Record *p)    //2.2.修改记录项目
{
    int tempid;
    while(1)
    {
        system("cls");//清屏
        output_money();
        output_one(p,1,1);
        printf("请选择修改的项目：\n\
1.时间\t\t2.交易类型\t3.配件\n\
4.配件型号\t5.单价\t\t6.数量\n\
7.%s\t8.赠品\t\t9.上一步\n",p->recordtype==stock?"供货商":"客户\t");
        tempid=judge_choice(9);
        switch(tempid)
        {
        case 1://时间
            change_time(p);
            break;
        case 2://交易类型
            change_recordtype(p);
            break;
        case 3://配件（配件和配件型号情况特殊，结算放在外边）
            solve_record(p,0);//结算
            change_part(p);
            solve_record(p,1);//结算
            break;
        case 4://配件型号
            solve_record(p,0);//结算
            change_parttype(p);
            solve_record(p,1);//结算
            break;
        case 5://单价
            change_unitprice(p);
            break;
        case 6://数量
            change_amount(p);
            break;
        case 7://供货商/客户
            if(p->recordtype==stock)
                change_supply(p);
            else
                change_client(p);
            break;
        case 8://赠品
            if(p->recordtype!=wholesale)
            {
                printf("记录类型不是批发，无法修改赠品！\n");
                break;
            }
            solve_record(p,0);//结算
            change_present(p);
            solve_record(p,1);//结算
            break;
        default:
            return;
        }
        wait_enter(1);
    }
}

void del_record()                   //2.3.删除记录
{
    Record *choose_record[size];
    int tempid;
    int maxrecord=output_record(choose_record);
    printf("请选择你要删除的记录编号（输入%d返回上一步）：\n",maxrecord+1);
    int choose_id=judge_choice(maxrecord+1);
    if(choose_id==maxrecord+1)
    {
        return;
    }
    output_one(choose_record[choose_id],1,choose_id);
    printf("确认要删除这条记录吗？（1.是 2.否）\n");
    tempid=judge_choice(2);
    switch(tempid)
    {
    case 1:
        del_one_record(choose_record[choose_id]);
        wait_enter(1);
        break;
    case 2:
        break;
    default:
        return;
    }
}

void count_data()                   //3.统计数据
{
    while(1)
    {
        system("cls");//清屏
        output_money();
        printf("1.统计营业额与盈利额\n\
2.统计赠品情况\n\
3.生成库存报表\n\
4.上一步\n");
        int option_choice=judge_choice(4);
        switch(option_choice)
        {
        case 1:
            if(recordall->b_recordnext==NULL)
            {
                printf("当前记录为空，无法统计！");
                wait_enter(0);
                break;
            }
            printf("营业额：%.2f\n盈利额：%.2f\n",total_sales(recordall),total_profit(recordall));
            break;
        case 2:
            if(recordall->b_recordnext==NULL)
            {
                printf("当前记录为空，无法统计！");
                wait_enter(0);
                break;
            }
            present_form(recordall);
            break;
        case 3:
            store_form(datapart);
            break;
        case 4:
            return;
        }
        wait_enter(4);
    }
}

void smart_analyse()                //4.智能分析
{
    while(1)
    {
        system("cls");//清屏
        output_money();
        printf("1.价格预测\n\
2.智能进货建议\n\
3.上一步\n");
        int option_choice=judge_choice(3);
        switch(option_choice)
        {
        case 1:
            price_predict_choose();//价格分析
            break;
        case 2:
            suggest_in();
            break;
        default:
            return;
        }
    }
}

void price_predict_choose()         //4.1.价格预测
{
    Part_list* choose_part[size];
    Parttype_list* choose_parttype[size];
    int maxrecord,choose_id,choose_id2;
    error_judge_2();//错误判断
    while(1)
    {
        system("cls");
        printf("该系统将结合今年12个月的数据，预测出明年1月该商品的价格\n");
        maxrecord=output_part_data(choose_part);//输出配件数据库
        printf("请选择你要预测价格的配件（输入%d返回上一步）：\n",maxrecord+1);
        choose_id=judge_choice(maxrecord+1);
        if(choose_id==maxrecord+1)
            return;
        maxrecord=output_parttype_data(choose_part[choose_id]->type_list,choose_parttype);//输出配件型号数据库
        printf("请选择你要预测价格的配件型号（输入%d返回上一步）：\n",maxrecord+1);
        choose_id2=judge_choice(maxrecord+1);
        if(choose_id2==maxrecord+1)
            break;
        price_predict(&(choose_part[choose_id]->data),&(choose_parttype[choose_id2]->data));
        wait_enter(4);
    }
}

void high_change()                  //5.高级设置
{
    int option_choice;
    while(1)
    {
        system("cls");//清屏
        output_money();
        printf("1.供货商信息管理\n\
2.客户信息管理\n\
3.记录数据清空\n\
4.记录数据替换\n\
5.上一步\n");
        option_choice=judge_choice(5);
        switch(option_choice)
        {
        case 1:
            high_change_supply();
            break;
        case 2:
            high_change_client();
            break;
        case 3:
            high_change_del();
            break;
        case 4:
            high_change_replace();
            break;
        default:
            return;
        }
    }
}

void high_change_supply()           //5.1.供货商信息管理
{
    int option_choice;
    while(1)
    {
        system("cls");//清屏
        output_money();
        printf("1.增加新的供货商信息\n\
2.删除供货商信息\n\
3.保存当前的供货商状态\n\
4.上一步\n");
        option_choice=judge_choice(4);
        switch(option_choice)
        {
        case 1:
            Supply_add();
            break;
        case 2:
            if(datasupply->next==NULL||datasupply->next->name==NULL)
            {
                printf("无法删除！\n至少需要保留一个供货商信息！\n");
                break;
            }
            Supply_delete();
            break;
        case 3:
            save_supply_to_file("data\\supply.txt");
            printf("操作成功！");
            wait_enter(4);
        default:
            return;
        }
    }
}

void high_change_client()           //5.2.客户信息管理
{
    int option_choice;
    while(1)
    {
        system("cls");//清屏
        output_money();
        printf("1.增加新的客户信息\n\
2.删除客户信息\n\
3.保存当前的客户状态\n\
4.上一步\n");
        option_choice=judge_choice(4);
        switch(option_choice)
        {
        case 1:
            Client_add();
            break;
        case 2:
            if(dataclient->next==NULL||dataclient->next->name==NULL)
            {
                printf("无法删除！\n至少需要保留一个客户信息！\n");
                break;
            }
            Client_delete();
            break;
        case 3:
            save_client_to_file("data\\client.txt");
            printf("操作成功！");
            wait_enter(4);
        default:
            return;
        }
    }
}

void high_change_del()              //5.3.清空记录
{
    int option_choice;
    printf("本功能将清空记录的所有内容，确认使用吗？(1.是 2.否)\n");
    option_choice=judge_choice(2);
    switch(option_choice)
    {
    case 1:
        del_all();
        printf("记录已清空！\n");
        wait_enter(4);
        break;
    default:
        return;
    }
}

void high_change_replace()          //5.4.替换记录
{
    printf("本功能将替换记录的所有内容，请输入你要替换的记录文件名\n");
    char filename[size];
    fflush(stdin);//清空缓冲区
    while(scanf("%[^\n]",filename)!=1)
    {
        printf("输入错误，请重试！\n");
        while(getchar()!='\n');
        fflush(stdin);
    }
    fflush(stdin);//清空缓冲区
    del_all();
    load_record_from_file(filename);
    printf("记录已替换！\n");
    wait_enter(4);
}
