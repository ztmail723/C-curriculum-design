#include"smallfunction.h"
#include"mainfunction.h"
Part_list* loadpart(char *filename)//从数据库中读取配件
{
    char tempname[size]="#";
    Part_list *head=(Part_list*)malloc(sizeof(Part_list));//新建头结点
    Part_list *p=head;
        head->data.id=0;
        strcpy(head->data.name,"#");
        head->type_list=(Parttype_list*)malloc(sizeof(Parttype_list));
    Parttype_list *temphead[size];
    temphead[0]=head->type_list;
    int i=0,j=0;
    FILE *fp=fopen(filename,"r");
    if(fp==NULL)//错误判断
    {
        printf("打开文件%s失败！\n",filename);
        return 0;
    }
    fscanf(fp,"%*[^\n]%*[\n]");//略去第一行
    while(!feof(fp))
    {
        fscanf(fp,"%[^\t]%*[\t]",tempname);
        if(strcmp(tempname,p->data.name)!=0)//如果读取的下一个配件与上一个配件不同，则新建配件链表
        {
            p->type_list->next=NULL;//上一个配件的的型号指向NULL
            temphead[p->data.id]->data.id=j;//头结点的id存储的是数量
            p->next=(Part_list*)malloc(sizeof(Part_list));//新建配件
            p=p->next;
            p->data.id=++i;//编号初始化
            strcpy(p->data.name,tempname);
            j=0;//配件型号编号初始化
            p->type_list=(Parttype_list*)malloc(sizeof(Parttype_list));//新建配件型号
            p->type_list->data.id=0;
            p->type_list->data.keynum=0;
            p->type_list->data.modify=1.00;
            strcpy(p->type_list->data.name,"#");
            temphead[i]=p->type_list;
        }
        p->type_list->next=(Parttype_list*)malloc(sizeof(Parttype_list));
        p->type_list=p->type_list->next;
        p->type_list->data.id=++j;
        p->type_list->data.modify=1.00;//修正指数初始为1.00
        fscanf(fp,"%[^\t]%*[\t]",p->type_list->data.name);//读名字
        fscanf(fp,"%[^\t]%*[\t]",p->type_list->data.partman);
        fscanf(fp,"%d%*[\t]",&p->type_list->data.store);
        fscanf(fp,"%d%*[\t]",&p->type_list->data.keynum);
        fscanf(fp,"%lf/%lf/%lf%*[\n]",&p->type_list->data.stock_price,&p->type_list->data.wholesale_price,&p->type_list->data.retail_price);
    }
    p->next=NULL;
    p->type_list->next=NULL;
    temphead[p->data.id]->data.id=j;//头结点的id存储的是数量
    fclose(fp);
    for(p=head->next;p!=NULL;p=p->next)
    {
        p->type_list=temphead[p->data.id];
    }
    head->data.id=i;
    return head;
}

Supply *loadsupply(char *filename)//从数据库中读取供货商
{
    Supply *head=(Supply*)malloc(sizeof(Supply));
    Supply *p=head;
        head->id=0;
    FILE *fp=fopen(filename,"r");
    int i=0;
    if(fp==NULL)//错误判断
    {
        printf("打开文件%s失败！\n",filename);
        return 0;
    }
    fscanf(fp,"%*[^\n]%*[\n]");//略去第一行
    while(!feof(fp))
    {
        p->next=(Supply*)malloc(sizeof(Supply));
        p=p->next;
        fscanf(fp,"%[^\t]%*[\t]%lf%*[\n]",p->name,&p->modify);
        p->id=++i;
    }
    p->next=NULL;
    fclose(fp);
    return head;
}

Client *loadclient(char *filename)//从数据库中读取客户
{
    Client *head=(Client*)malloc(sizeof(Client));
    Client *p=head;
        head->id=0;
    FILE *fp=fopen(filename,"r");
    int i=0;
    char temptype[size],tempgender[size];
    if(fp==NULL)//错误判断
    {
        printf("打开文件%s失败！\n",filename);
        return 0;
    }
    fscanf(fp,"%*[^\n]%*[\n]");//略去第一行
    while(!feof(fp))
    {
        p->next=(Client*)malloc(sizeof(Client));
        p=p->next;
        p->id=++i;
        fscanf(fp,"%[^\t]%*[\t]",temptype);
        if(strcmp(temptype,"individual")==0)
            p->c_clienttype=individual;
        else
            p->c_clienttype=group;
        fscanf(fp,"%[^\t]%*[\t]",p->name);
        fscanf(fp,"%[^\t]%*[\t]",tempgender);
        if(strcmp(tempgender,"male")==0)
            p->gender=male;
        else if(strcmp(tempgender,"female")==0)
            p->gender=female;
        else
            p->gender=nullgender;
        fscanf(fp,"%[^\t]%lf%*[\n]",p->unit,&p->modify);
    }
    p->next=NULL;
    fclose(fp);
    return head;
}

void load_record_from_file(char *filename)//从文件中读取记录
{
    int temp;
    char tempname[size];//存放临时字符串
    Record *key_record;
    Present *key_present;
    FILE *fp=fopen(filename,"r");
    if(fp==NULL)//错误判断
    {
        printf("打开文件%s失败！\n",filename);
        return;
    }
    fscanf(fp,"%*[^\n]%*[\n]");//略去第一行
    while(!feof(fp))
    {
        key_record=(Record*)malloc(sizeof(Record));
        key_record->color=0;//颜色默认为0
        fscanf(fp,"%d%*[^\t]",&temp);//读入记录类型
        switch(temp)
        {
        case 0:key_record->recordtype=stock;break;
        case 1:key_record->recordtype=wholesale;break;
        case 2:key_record->recordtype=retail;
        }
        fscanf(fp,"%d/%d %d:%d%*[\t]",&key_record->b_date.month,&key_record->b_date.day,\
               &key_record->b_date.hour,&key_record->b_date.minute);//读入日期
        if(judgedate(key_record->b_date)==0)
        {
            printf("读取到的日期不合法！\n");
            wait_enter(4);
            free(key_record);
            fclose(fp);
            return;
        }
        fscanf(fp,"%[^\t]%*[\t]",tempname);//读入配件
        key_record->b_part=key_part_list(tempname);
        if(key_record->b_part==NULL)//如果发现这个配件找不到，则终止
        {
            free(key_record);
            wait_enter(4);
            fclose(fp);
            return;
        }
        fscanf(fp,"%[^\t]%*[\t]",tempname);//读入配件型号
        key_record->b_parttype=key_parttype_list(key_record->b_part->name,tempname);
        if(key_record->b_parttype==NULL)//如果发现这个配件型号找不到，则终止
        {
            free(key_record);
            wait_enter(4);
            fclose(fp);
            return;
        }
        fscanf(fp,"%lf%*[\t]%d%*[\t]",&key_record->unit_price,&key_record->amount);//读入单价和数量
        key_record->total_price=key_record->unit_price*key_record->amount;//计算出总价
        fscanf(fp,"%[^\t]%*[\t]",tempname);//读入供货商或客户
        switch(key_record->recordtype)
        {
        case stock:
            key_record->b_supply=key_supply_list(tempname);
            if(key_record->b_supply==NULL)//如果发现这个供货商找不到，则终止
            {
                free(key_record);
                wait_enter(4);
                fclose(fp);
                return;
            }
            break;
        case wholesale:
            key_record->b_client=key_client_list(tempname);
            if(key_record->b_client==NULL)//如果发现这个供货商找不到，则终止
            {
                free(key_record);
                wait_enter(4);
                fclose(fp);
                return;
            }
            break;
        case retail:
            key_record->b_client=key_client_list(tempname);
            if(key_record->b_client==NULL)//如果发现这个供货商找不到，则终止
            {
                free(key_record);
                wait_enter(4);
                fclose(fp);
                return;
            }
            break;
        default:;
        }
        key_present=(Present*)malloc(sizeof(Present));//新建赠品头结点
        key_present->amount=0;
        key_present->next=NULL;
        key_present->part=NULL;
        key_present->parttype=NULL;
        key_record->b_present=key_present;
        while(1)
        {
            fscanf(fp,"%d",&temp);
            if(temp==0)break;
            fscanf(fp,"%*[\t]");
            key_present->next=(Present*)malloc(sizeof(Present));
            key_present=key_present->next;
            key_present->amount=temp;
            fscanf(fp,"%[^\t]%*[\t]",tempname);//读入配件
            key_present->part=key_part_list(tempname);
            fscanf(fp,"%[^\t]%*[\t]",tempname);//读入配件型号
            key_present->parttype=key_parttype_list(key_present->part->name,tempname);
            key_present->next=NULL;
        }
        fscanf(fp,"%*[\n]");
        solve_record(key_record,1);
        sorttime(key_record);
    }
    fclose(fp);
    return;
}

void save_record_to_file(char *filename)//把当前记录存入文件
{
    char tempname[size];//存放临时字符串
    Record *key_record=recordall->b_recordnext;
    Present *key_present;
    FILE *fp=fopen(filename,"w");
    if(fp==NULL)//错误判断
    {
        printf("存入文件%s失败！\n",filename);
        return;
    }
    fprintf(fp,"类型\t时间\t\t配件\t\t型号\t\t单价\t\t数量\t\t供货商/客户\t赠品（类型0：进货 1：批发 2：零售）\n");//输出表格头
    while(key_record!=NULL)
    {
        fprintf(fp,"%d\t",key_record->recordtype==stock?0:(key_record->recordtype==wholesale?1:2));//记录类型
        timestr(tempname,key_record->b_date,0);
        fprintf(fp,"%s\t",tempname);//时间
        fprintf(fp,"%s%s",key_record->b_part->name,tabs(key_record->b_part->name));//配件
        fprintf(fp,"%s%s",key_record->b_parttype->name,tabs(key_record->b_parttype->name));//型号
        fprintf(fp,"%.2f%s",key_record->unit_price,tabf(key_record->unit_price));//单价
        fprintf(fp,"%d%s",key_record->amount,tabi(key_record->amount));//数量
        if(key_record->recordtype==stock)//供货商或客户
            fprintf(fp,"%s%s",key_record->b_supply->name,tabs(key_record->b_supply->name));
        else
            fprintf(fp,"%s%s",key_record->b_client->name,tabs(key_record->b_client->name));
        key_present=key_record->b_present->next;
        while(key_present!=NULL)
        {
            fprintf(fp,"%d\t%s\t%s\t",key_present->amount,key_present->part->name,key_present->parttype->name);
            key_present=key_present->next;
        }
        fprintf(fp,"0\n");
        key_record=key_record->b_recordnext;
    }
    fclose(fp);
}

void save_supply_to_file(char *filename)//把当前供货商信息存入文件
{
    Supply *key_supply=datasupply->next;
    FILE *fp=fopen(filename,"w");
    if(fp==NULL)//错误判断
    {
        printf("存入文件%s失败！\n",filename);
        return;
    }
    fprintf(fp,"供货商名称\t初始价格修正指数\n");//输出表格头
    while(key_supply!=NULL)
    {
        fprintf(fp,"%s%s",key_supply->name,tabs(key_supply->name));
        fprintf(fp,"%.2f\n",key_supply->modify);
        key_supply=key_supply->next;
    }
    fclose(fp);
}

void save_client_to_file(char *filename)//把当前客户信息存入文件
{
    Client *key_client=dataclient->next;
    FILE *fp=fopen(filename,"w");
    if(fp==NULL)//错误判断
    {
        printf("存入文件%s失败！\n",filename);
        return;
    }
    fprintf(fp,"类型\t\t客户\t\t性别\t\t单位\t\t初始价格修正指数\n");//输出表格头
    while(key_client!=NULL)
    {
        fprintf(fp,"%s\t\t",key_client->c_clienttype==individual?"individual\t":"group\t\t");
        fprintf(fp,"%s%s",key_client->name,tabs(key_client->name));
        fprintf(fp,"%s\t\t",key_client->gender==nullgender?"none":(key_client->gender==male?"male":"female"));
        fprintf(fp,"%s%s",key_client->unit,tabs(key_client->unit));
        fprintf(fp,"%.2f\n",key_client->modify);
        key_client=key_client->next;
    }
    fclose(fp);
}

void Client_add()//增加客户
{
    Client *p=dataclient;
    Client *q;
    Client *check=dataclient->next;
    int type;
    char name[size];
    printf("请输入您要增加的客户(个人或团体)姓名:（不超过10个字节）\n");
    fflush(stdin);
    while(scanf("%[^\n]",name))
    {
        if(strlen(name)>10)
        {
            printf("超过10个字节，请重新输入！\n");
            while(getchar()!='\n');
            fflush(stdin);
        }
        else
        {
            break;
        }
    }
    fflush(stdin);
    while(check!=NULL)
    {
        if(strcmp(name,check->name)==0)
        {
            printf("错误:数据库中已存在该客户信息!\n");
            return;
        }
        check=check->next;
    }
    while(p->next!=NULL)
    {
        p=p->next;
    }
    q=(Client *)malloc(sizeof(Client));
    p->next=q;
    printf("请选择您的客户类型:\n");
    printf("1.个人 2.团体\n");
    scanf("%d",&type);
    if(type==1||type==2)
    {
        switch(type)
        {
        case 1://个人客户的输入
            {
                strcpy(q->name,name);
                q->c_clienttype=individual;
                printf("请输入您的性别:\n");
                printf("1:男 2:女\n");
                int sex=0;
                scanf("%d",&sex);
                if(sex==1)
                {
                    p->gender=male;
                }
                else if(sex==2)
                {
                    p->gender=female;
                }
                else if(sex!=1&&sex!=2)
                {
                    printf("错误:您的性别输入不规范!\n");
                    return;
                }
                printf("请输入您的工作单位(若无请填写none)\n");
                fflush(stdin);
                while(scanf("%[^\n]",q->unit))
                {
                    if(strlen(q->unit)>10)
                    {
                        printf("超过10个字节，请重新输入！\n");
                        while(getchar()!='\n');
                        fflush(stdin);
                    }
                    else
                    {
                        break;
                    }
                }
                fflush(stdin);
                q->modify=(double)(rand()%75+75);
                q->modify/=100;
                q->next=NULL;
                printf("您的个人客户信息输入成功!\n");
                break;
            }
        case 2://团体客户的输入
            {
                strcpy(q->name,name);
                q->c_clienttype=group;
                q->modify=(double)(rand()%75+75);
                q->next=NULL;
                char charsex[]={"none"};
                strcpy(p->unit,charsex);
                q->gender=nullgender;
                printf("您的团体客户信息输入成功!\n");
                break;
            }
        }
    }
    else printf("您的客户类型输入不规范!\n");
    wait_enter(4);
    return;
}

void Client_delete()//删除客户
{
    Client *p=dataclient;
    Client *p0=dataclient;
    Client *choose_client[size];
    Record *q=recordall->b_recordnext;
    char supname[size];
    int maxrecord,option_client;
    maxrecord=output_client_data(dataclient,choose_client);
    printf("请选择您要删除的客户：（输入%d返回上一步）\n",maxrecord+1);
    option_client=judge_choice(maxrecord+1);
    if(option_client==maxrecord+1)
    {
        return;
    }
    strcpy(supname,choose_client[option_client]->name);
    while(q!=NULL)
    {
        if(q->recordtype==wholesale||q->recordtype==retail)
        {
         if(strcmp(supname,q->b_client->name)==0)
            {
                printf("记录中存在该客户信息,无法删除!\n");
                wait_enter(4);
                return;
            }
        }
        q=q->b_recordnext;
    }
    p=dataclient->next;
    while(p!=NULL)
    {
        if(strcmp(supname,p->name)==0)
            {
                p0->next=p->next;
                free(p);
                printf("客户信息删除成功!\n");
                return;
            }
            p0=p;
            p=p->next;
    }
    return;
}

void Supply_add()//增加供货商
{
    Supply *p=datasupply;
    Supply *q;
    Supply *check=datasupply;
    char name[size];

    printf("请输入您要增加的供货商名称:（不超过10个字节）\n");
    fflush(stdin);
    while(scanf("%[^\n]",name))
    {
        if(strlen(name)>10)
        {
            printf("超过10个字节，请重新输入！\n");
            while(getchar()!='\n');
            fflush(stdin);
        }
        else
        {
            break;
        }
    }
    fflush(stdin);
    while(check!=NULL)
    {
        if(strcmp(name,check->name)==0)
        {
            printf("错误:数据库中已存在该客户信息!\n");
            return;
        }
            check=check->next;
    }
    while(p->next!=NULL)
    {
        p=p->next;
    }
    q=(Supply *)malloc(sizeof(Supply));
    p->next=q;
    strcpy(q->name,name);
    q->modify=(double)(rand()%75+75);
    q->modify/=100;
    q->next=NULL;
    printf("您的供货商信息输入成功!\n");
    wait_enter(4);
    return;
}

void Supply_delete()//删除供货商
{
    Record *q;
    Supply *p=datasupply;
    Supply *p0=datasupply;
    Supply *choose_supply[size];
    char supname[size];
    int maxrecord,option_supply;
    maxrecord=output_supply_data(datasupply,choose_supply);
    printf("请选择您要删除的供货商：（输入%d返回上一步）\n",maxrecord+1);
    option_supply=judge_choice(maxrecord+1);
    if(option_supply==maxrecord+1)
    {
        return;
    }
    strcpy(supname,choose_supply[option_supply]->name);
    q=recordall->b_recordnext;

    while(q!=NULL)
    {
        if(q->recordtype==stock)
        {
         if(strcmp(supname,q->b_supply->name)==0)
            {
                printf("记录中存在该供货商信息,无法删除!\n");
                wait_enter(4);
                return;
            }
        }

        q=q->b_recordnext;
    }
    p=datasupply->next;
    while(p!=NULL)
    {
        if(strcmp(supname,p->name)==0)
            {
                p0->next=p->next;
                free(p);
                printf("供货商信息删除成功!\n");
                return;
            }
            p0=p;
            p=p->next;
    }
    return;
}

void add_record_from_file()//从文件中增加记录
{
    printf("请输入需要录入的文件名（输入样例：data233.txt）\n");
    char filename[size];
    fflush(stdin);//清空缓冲区
    while(scanf("%[^\n]",filename)!=1)
    {
        printf("输入错误，请重试！\n");
        while(getchar()!='\n');
        fflush(stdin);
    }
    fflush(stdin);//清空缓冲区
    load_record_from_file(filename);
    printf("录入结束！");
    wait_enter(4);
    return;
}

void add_record_from_system()//从控制台实时贸易
{
    Date tempdate;
    Present* newpresent;
    Present *pre[3][5];//礼物赠送的二维数组
    char datestr[size];//id：配件 id2：配件型号 id3：供货商/客户
    int maxrecord,choose_id,choose_id2,choose_id3,choose_amount,choose_type,choose_present,i,j,randx;
    double finalprice;//修正后的单价
    Part_list* choose_part[size];
    Parttype_list* choose_parttype[size];
    Supply *choose_supply[size];
    Client *choose_client[size];
    printf("请输入贸易时间：（输入格式：月 日 时 分）\n");
    fflush(stdin);//清空缓冲区
    while(scanf("%d%d%d%d",&tempdate.month,&tempdate.day,&tempdate.hour,&tempdate.minute)!=4||judgedate(tempdate)==0)
    {
        printf("输入错误，请重试！\n");
        fflush(stdin);
    }
    fflush(stdin);//清空缓冲区
    system("cls");//清屏
    output_money();
    timestr(datestr,tempdate,1);
    printf("%s\n",datestr);//时间
    maxrecord=output_part_data(choose_part);//输出配件数据库
    printf("请选择你要贸易的配件：\n");
    choose_id=judge_choice(maxrecord);
    system("cls");//清屏
    output_money();
    printf("%s\n配件：%s\n",datestr,choose_part[choose_id]->data.name);//时间和配件
    maxrecord=output_parttype_data(choose_part[choose_id]->type_list,choose_parttype);//输出配件型号数据库
    printf("请选择你要贸易的配件型号：\n");
    choose_id2=judge_choice(maxrecord);
//    if(choose_parttype[choose_id2]->data.store<=0)
//    {
//        printf("当前配件数量不足，无法出售！\n");
//        return;
//    }//取消了这里的判断，允许配件数量不足的情况
    printf("请选择你的贸易类型：\n\
1.进货\n\
2.批发\n\
3.零售\n");
    choose_type=judge_choice(3);
    switch(choose_type)
    {
    case 1:
        printf("请选择供货商：\n");
        maxrecord=output_supply_data(datasupply,choose_supply);
        choose_id3=judge_choice(maxrecord);
        finalprice=choose_parttype[choose_id2]->data.stock_price*choose_supply[choose_id3]->modify*choose_parttype[choose_id2]->data.modify;//价格修正
        finalprice=(double)((long long int)(finalprice*100))/100;//保留两位小数
        printf("当前供货商提供的单价为%.2f元人民币！\n",finalprice);
        break;
    case 2:
        printf("请选择客户：\n");
        maxrecord=output_client_data(dataclient,choose_client);
        choose_id3=judge_choice(maxrecord);
        finalprice=choose_parttype[choose_id2]->data.wholesale_price*choose_client[choose_id3]->modify*choose_parttype[choose_id2]->data.modify;//可能存在价格修正（有时间再加这个功能）
        printf("批发给该客户的单价为%.2f元人民币！\n",finalprice);
        break;
    default:
        printf("请选择客户：\n");
        maxrecord=output_client_data(dataclient,choose_client);
        choose_id3=judge_choice(maxrecord);
        finalprice=choose_parttype[choose_id2]->data.retail_price*choose_client[choose_id3]->modify*choose_parttype[choose_id2]->data.modify;//可能存在价格修正（有时间再加这个功能）
        printf("零售给该客户的单价为%.2f元人民币！\n",finalprice);
    }
    if(choose_type==1)
    {
//        int limit=money/finalprice;
//        if(limit<=0)
//       {
//            printf("当前资金不足，无法进货！\n");
//            return;
//        }//取消了这个设定
        printf("请选择进货数量：\n");
        choose_amount=judge_choice(maxsize);
            newpresent=(Present*)malloc(sizeof(Present));//新建赠品头结点
            newpresent->amount=0;
            newpresent->part=NULL;
            newpresent->parttype=NULL;
            newpresent->next=NULL;
    }
    else
    {
        printf("请选择出售数量：\n");
        choose_amount=judge_choice(maxsize);//允许超过库存
        if(choose_type==2&&choose_amount>=choose_parttype[choose_id2]->data.keynum)
        {
            printf("为了回馈该客户，请从以下方案选择一个作为赠品：\n");
            newpresent=(Present*)malloc(sizeof(Present));//新建赠品头结点
            newpresent->amount=0;
            newpresent->part=NULL;
            newpresent->parttype=NULL;
            newpresent->next=NULL;
            //功能待添加
            for(i=0;i<3;i++)
                for(j=0;j<5;j++)
                pre[i][j]=NULL;
            if(choose_parttype[choose_id2]->data.store>=choose_amount*10)
            {
                srand((unsigned)time(0));
                randx=rand()%4+2;//2-5个赠品
            }
            else
            {
                randx=1;//1个赠品
            }
            add_record_present(pre,randx);
            for(i=0;i<3;i++)
            {
                if(pre[i][0]!=NULL)
                {
                    printf("方案%d.\n",i+1);
                    for(j=0;j<5;j++)
                    {
                        if(pre[i][j]==NULL)
                        {
                            break;
                        }
                        else
                        {
                            printf("%d个%s型号%s\n",pre[i][j]->amount,pre[i][j]->part->name,pre[i][j]->parttype->name);
                        }
                    }
                }
                else
                {
                    break;
                }
            }
            choose_present=judge_choice(i)-1;
            newpresent->next=pre[choose_present][0];
            for(i=(choose_present+1)%3;(i%3)!=choose_present;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(pre[i%3][j]==NULL)
                    {
                        break;
                    }
                    else
                    {
                        free(pre[i%3][j]);
                    }
                }
            }
            printf("赠品添加成功！\n\n");
        }
        else
        {
            newpresent=(Present*)malloc(sizeof(Present));//新建赠品头结点
            newpresent->amount=0;
            newpresent->part=NULL;
            newpresent->parttype=NULL;
            newpresent->next=NULL;
        }
    }
    double finaltotal=finalprice*choose_amount;
    printf("商品总价为%.2f\n",finaltotal);
    Record *newrecord=(Record*)malloc(sizeof(Record));
    newrecord->amount=choose_amount;
    switch(choose_type)
    {
    case 1:
        newrecord->recordtype=stock;
        newrecord->b_supply=choose_supply[choose_id3];
        break;
    case 2:
        newrecord->recordtype=wholesale;
        newrecord->b_client=choose_client[choose_id3];
        break;
    default:
        newrecord->recordtype=retail;
        newrecord->b_client=choose_client[choose_id3];
    }
    newrecord->b_date=tempdate;
    newrecord->b_part=&choose_part[choose_id]->data;
    newrecord->b_parttype=&choose_parttype[choose_id2]->data;
    newrecord->b_present=newpresent;
    newrecord->unit_price=finalprice;
    newrecord->total_price=finaltotal;
    newrecord->b_recordnext=NULL;
    newrecord->color=0;//颜色默认为0
    solve_record(newrecord,1);
    sorttime(newrecord);//按时间顺序插入新结点
    wait_enter(1);
    return;
}

void add_record_present(Present *pre_way[3][5],int present_amount)//生成三种方案，存于二维指针数组中，每种方案最多有5种配件
{
    int part_num=0,parttype_num=0;//配件数量和配件型号的数量
    int i,j,k=0;
    Part_list *p;//临时变量，遍历数据库中的配件
    Parttype_list *pt;//临时变量，遍历数据库中的配件型号
    Present pre[size];//生成一个礼物数组，把配件数据库存于数组中
    for(p=datapart->next;p!=NULL;p=p->next)
    {
        for(pt=p->type_list->next;pt!=NULL;pt=pt->next)
        {
            pre[parttype_num].amount=rand()%5+1;//初始化为1，但之后可能会修改
            pre[parttype_num].part=&(p->data);
            pre[parttype_num].parttype=&(pt->data);
            pre[parttype_num].next=NULL;
            parttype_num++;
        }
        part_num++;
    }
    randpre(parttype_num,pre);//对指针数组进行随机排序
    for(i=0;i<present_amount;i++)
    {
        for(j=0;j<3;j++)
        {
            if(k>=parttype_num)
            {
                pre_way[j][i]=NULL;
            }
            else
            {
                pre_way[j][i]=(Present*)malloc(sizeof(Present));
                *(pre_way[j][i])=pre[k];
                if(i>0)//如果i>0，则对结点进行连接
                {
                    pre_way[j][i-1]->next=pre_way[j][i];
                }
            }
            k++;
        }
    }

}

void del_one_record(Record *key)//删除一条记录
{
    Record *p,*p0=recordall;
    Present* pre0=key->b_present,*pre;
    for(p=recordall->b_recordnext;p!=key;p=p->b_recordnext)
        p0=p;
    p0->b_recordnext=p->b_recordnext;
    solve_record(p,0);//还原这条记录
    for(pre=key->b_present->next;pre!=NULL;pre=pre->next)
    {
        free(pre0);
        pre0=pre;
    }
    free(pre);
    free(p);
}

void change_time(Record* p)//修改时间
{
    char tempstr[size],tempstr2[size];//tempstr存储修改前的时间字符串，tempstr2存储修改后的时间字符串
    Date tempdate;//临时变量，存储修改后的时间
    timestr(tempstr,p->b_date,0);
    printf("当前时间为%s，请输入修改后的时间：\n",tempstr);
    fflush(stdin);
    while(scanf("%d%d%d%d",&tempdate.month,&tempdate.day,\
        &tempdate.hour,&tempdate.minute)!=4||\
        judgedate(tempdate)==0)//将输入存储在临时变量中
    {
        printf("输入错误，请重试！\n");
        while(getchar()!='\n');
        fflush(stdin);
    }
    fflush(stdin);
    timestr(tempstr,p->b_date,1);
    timestr(tempstr2,tempdate,1);
    p->b_date=tempdate;
    printf("该条记录的时间由\n\
%s\n修改至\n%s\n",tempstr,tempstr2);
    dropoff(p);//摘下该节点
    sorttime(p);//按照时间顺序放回链表
}

void change_recordtype(Record* p)//修改交易类型
{
    Present *pre0,*pre;
    solve_record(p,0);//结算
    printf("当前类型为：%s，请输入修改后的类型编号\n",\
           p->recordtype==stock?"进货":(p->recordtype==wholesale?"批发":"零售"));
    printf("1.进货\t2.批发\t3.零售\t4.上一步\n");
    int tempid=judge_choice(4);
    if((tempid==1&&p->recordtype==stock)||\
       (tempid==2&&p->recordtype==wholesale)||
       (tempid==3&&p->recordtype==retail))
    {
        printf("修改前后类型相同！\n");
        wait_enter(1);
        return;
    }
    switch(tempid)
    {
    case 1:
        change_supply(p);
        if(p->recordtype==wholesale&&p->b_present->next!=NULL)//如果原先是批发，则要删除赠品（未完成）
        {
            printf("因类型变换，原先的赠品删除！\n");
            pre0=p->b_present->next;
            pre=pre0->next;
            p->b_present->next=NULL;
            while(pre!=NULL)
            {
                free(pre0);
                pre0=pre;
                pre=pre->next;
            }
            free(pre0);
        }
        p->recordtype=stock;
        break;
    case 2:
        p->recordtype=wholesale;
        if(p->recordtype==stock)change_client(p);
        break;
    case 3:
        if(p->recordtype==stock)change_client(p);
        if(p->recordtype==wholesale&&p->b_present->next!=NULL)//如果原先是批发，则要删除赠品（未完成）
        {
            printf("因类型变换，原先的赠品删除！\n");
            pre0=p->b_present->next;
            pre=pre0->next;
            p->b_present->next=NULL;
            while(pre!=NULL)
            {
                free(pre0);
                pre0=pre;
                pre=pre->next;
            }
            free(pre0);
        }
        p->recordtype=retail;
        break;
    case 4:
        return;
    }
    solve_record(p,1);//结算
}

void change_part(Record *p)//修改配件
{
    int maxrecord,choose_id;
    Part_list* choose_part[size];
    maxrecord=output_part_data(choose_part);//输出配件数据库
    printf("请选择你要修改的配件：\n");
    choose_id=judge_choice(maxrecord);
    p->b_part=&choose_part[choose_id]->data;
    change_parttype(p);
}

void change_parttype(Record *p)//修改配件型号
{
    int maxrecord,choose_id;
    Parttype_list* temp;
    Parttype_list* choose_parttype[size];
    temp=key_part_parttype(p->b_part->name);
    maxrecord=output_parttype_data(temp,choose_parttype);//输出配件型号数据库
    printf("请选择你要修改的配件型号：\n");
    choose_id=judge_choice(maxrecord);
    p->b_parttype=&choose_parttype[choose_id]->data;
}

void change_unitprice(Record *p)//修改单价
{
    solve_record(p,0);
    double tempprice;
    printf("当前单价为%.2f元，请输入修改后的单价\n",p->unit_price);
    setbuf(stdin, NULL);
    while(scanf("%lf",&tempprice)!=1||tempprice<=0)
    {
        printf("输入错误，请重试！\n");
        while(getchar()!='\n');
    }
    setbuf(stdin, NULL);
    printf("该条记录的单价由%.2f元修改至%.2f元！\n",p->unit_price,tempprice);
    p->unit_price=tempprice;
    p->total_price=p->amount*p->unit_price;
    printf("总价变为%.2f元！\n",p->total_price);
    solve_record(p,1);
}

void change_amount(Record *p)//修改数量
{
    solve_record(p,0);
    int temp;
    printf("当前数量为%d，请输入修改后的数量\n",p->amount);
    setbuf(stdin, NULL);
    while(scanf("%d",&temp)!=1||temp<=0)
    {
        printf("输入错误，请重试！\n");
        while(getchar()!='\n');
    }
    setbuf(stdin, NULL);
    printf("该条记录的数量由%d修改至%d！\n",p->amount,temp);
    p->amount=temp;
    p->total_price=temp*p->unit_price;
    printf("总价变为%.2f元！\n",p->total_price);
    solve_record(p,1);
}

void change_supply(Record *p)//修改供货商
{
    int maxrecord,chooseid;
    Supply *choose_key[size];
    printf("请选择修改后的供货商：\n");
    maxrecord=output_supply_data(datasupply,choose_key);
    chooseid=judge_choice(maxrecord);
    p->b_supply=choose_key[chooseid];
}

void change_client(Record *p)//修改客户
{
    int maxrecord,chooseid;
    Client *choose_key[size];
    printf("请选择修改后的客户：\n");
    maxrecord=output_client_data(dataclient,choose_key);
    chooseid=judge_choice(maxrecord);
    p->b_client=choose_key[chooseid];
}

void change_present(Record *p)//修改赠品
{
    Present *pre0,*pre;
    int maxrecord,choose_id,choose_id2,choose_id3,i,num,tempid,tempid2;
    Part_list* choose_part[size];
    Parttype_list* choose_parttype[size];
    Present* choose_present[size];
    while(1)
    {
        system("cls");//清屏
        output_money();
        output_one(p,1,1);
        i=0;
        choose_present[0]=p->b_present;
        for(pre0=p->b_present->next;pre0!=NULL;pre0=pre0->next)
        {
            choose_present[++i]=pre0;
        }
        pre0=p->b_present;
        printf("请选择进行的操作：\n\
1.增加赠品\t2.删除赠品\t3.修改赠品\t4.上一步\n");
        tempid=judge_choice(4);
        switch(tempid)
        {
        case 1:
            pre=(Present*)malloc(sizeof(Present));
            pre->next=NULL;
            maxrecord=output_part_data(choose_part);//输出配件数据库
            printf("请选择配件：\n");
            choose_id=judge_choice(maxrecord);
            pre->part=&choose_part[choose_id]->data;
            maxrecord=output_parttype_data(choose_part[choose_id]->type_list,choose_parttype);//输出配件型号数据库
            printf("请选择配件型号：\n");
            choose_id2=judge_choice(maxrecord);
            pre->parttype=&choose_parttype[choose_id2]->data;
            printf("请输入赠品数量：\n");
            num=judge_choice(maxsize);
            pre->amount=num;
            choose_present[i]->next=pre;
            wait_enter(1);
            break;
        case 2:
            if(pre0->next==NULL)
            {
                printf("当前无赠品，无法删除！");
                wait_enter(0);
                break;
            }
            printf("请输入你要删除的赠品编号：\n");
            choose_id=judge_choice(i);
            choose_present[choose_id-1]->next=choose_present[choose_id]->next;
            free(choose_present[choose_id]);
            wait_enter(1);
            break;
        case 3:
            if(pre0->next==NULL)
            {
                printf("当前无赠品，无法修改！");
                wait_enter(0);
                break;
            }
            printf("请选择你要修改的赠品编号：\n");
            choose_id=judge_choice(i);
            printf("请选择你要修改的项目：\n");
            printf("1.配件\t2.配件型号\t3.数量\t4.上一步\n");
            tempid2=judge_choice(4);
            switch(tempid2)
            {
            case 1:
                maxrecord=output_part_data(choose_part);//输出配件数据库
                printf("请选择配件：\n");
                choose_id2=judge_choice(maxrecord);
                choose_present[choose_id]->part=&choose_part[choose_id2]->data;
                maxrecord=output_parttype_data(choose_part[choose_id2]->type_list,choose_parttype);//输出配件型号数据库
                printf("请选择配件型号：\n");
                choose_id3=judge_choice(maxrecord);
                choose_present[choose_id]->parttype=&choose_parttype[choose_id3]->data;
                wait_enter(1);
                break;
            case 2:
                maxrecord=output_parttype_data(key_part_parttype(choose_present[choose_id]->part->name),choose_parttype);//输出配件型号数据库
                printf("请选择配件型号：\n");
                choose_id3=judge_choice(maxrecord);
                choose_present[choose_id]->parttype=&choose_parttype[choose_id3]->data;
                wait_enter(1);
                break;
            case 3:
                printf("请输入数量：\n");
                num=judge_choice(maxsize);
                choose_present[choose_id]->amount=num;
                wait_enter(1);
                break;
            case 4:
                ;
            }
            break;
        case 4:
            return;
        }
    }
}

void store_form(Part_list* p)//生成库存报表
{
    Part_list *p0=p;
    Parttype_list *p1;
    printf("配件库存报表如下：\n");
    printf("名称\t\t型号\t\t制造商\t\t配件库存\n");
    for(p0=p0->next;p0!=NULL;p0=p0->next)
    {
        for(p1=p0->type_list->next;p1!=NULL;p1=p1->next)
        {
            printf("%s%s",p0->data.name,tabs(p0->data.name));
            printf("%s%s",p1->data.name,tabs(p1->data.name));
            printf("%s%s",p1->data.partman,tabs(p1->data.partman));
            printf("%d\n",p1->data.store);
        }

    }
    printf("库存报表生成完毕!\n");
    return;
}

void present_form(Record *p)//统计所有赠品情况
{
    Record *p0=p;
    Present *p1;
    printf("赠品配件统计如下:\n");
    printf("订单时间\t赠品名称\t赠品型号\t数量\n");
    char datastr[size];
    for(;p0!=NULL;p0=p0->b_recordnext)
    {
        if(p0->b_present!=NULL)
        {
            for(p1=p0->b_present->next;p1!=NULL;p1=p1->next)
            {
                timestr(datastr,p0->b_date,0);
                printf("%s%s",datastr,tabs(datastr));
                printf("%s%s",p1->part->name,tabs(p1->part->name));
                printf("%s%s",p1->parttype->name,tabs(p1->parttype->name));
                printf("%d\n",p1->amount);
            }
        }
    }
    return;
}

void searchall()//总记录数据查找
{
    Record *choose_record[size];
    int maxrecord,choose_id;
    while(1)
    {
        system("cls");//清屏
        output_money();
        maxrecord=output_record(choose_record);
        printf("请选择你要具体查询的记录编号(输入%d回到上一步)：\n",maxrecord+1);
        choose_id=judge_choice(maxrecord+1);
        if(choose_id==maxrecord+1)
            return;
        else
        {
            output_one(choose_record[choose_id],1,1);
            wait_enter(1);
        }
    }

}

void searchpart()//配件对应记录查找
{
    int flag1=0,flag2=0,count1=0,count2=0,count3=0,count4=0,j,i,m;
    Record *save1[size],*save2[size],*save3[size],*save4[size];
    Record *p;
    Part_list *p_list[size];

    int partid,maxpart;
    system("cls");
    output_money();
    printf("配件列表:\n");
    maxpart=output_part_data(p_list);
    printf("输入要查询的配件编号，输入%d返回上一步\n",maxpart+1);
    partid=judge_choice(maxpart+1);
    p=recordall->b_recordnext;
    while(1)
    {
        count1=0;
        count2=0;
        count3=0;
        count4=0;
    if(partid==maxpart+1)
        return;
    while(p!=NULL)
    {
        if(strcmp(p->b_part->name,p_list[partid]->data.name)==0)
        {
            if(p->recordtype==1)
            {
                flag1=1;
                save1[count1]=p;
                count1++;
            }
            if((p->recordtype==2)||(p->recordtype==3))
            {
                flag2=1;
                save2[count2]=p;
                count2++;
            }
        }
        p=p->b_recordnext;
    }
    while(1)
    {
        system("cls");
        output_money();
        printf("进货记录：\n");
        outrec_mod0(flag1,save1,count1,0);
        printf("出售记录：\n");
        if(flag2==0)
            printf("记录为空！\n");
        else
        {
            output_chart_head_1(1);
            for(i=0;i<count2;i++)
            {
                output_one(save2[i],0,count1+i+1);
                printf("\n");
            }
        };
        for(i=0;i<count2;i++)
            save1[count1+i]=save2[i];
        if((flag1==0)&&(flag2==0))
        {
            printf("按回车键继续\n");
            while(getchar()!='\n');
            return;
        }
        printf("\n\n输入记录编号查询具体信息；输入%d以配件型号为依据进行查询；输入%d返回上一步\n",count1+count2+1,count1+count2+2);
        m=judge_choice(count1+count2+2);
        system("cls");
        if(m==count1+count2+2)
            break;
        if(m==count1+count2+1)
        {
        system("cls");
        output_money();
        Parttype_list *ptype_list[50];
        Parttype_list *kptype=key_part_parttype(p_list[partid]->data.name);
        int typemax=output_parttype_data(kptype,ptype_list);
        printf("请输入配件型号序号以查询对应型号的记录，输入\"%d\"结束\n",typemax+1);
        partid=judge_choice(typemax+1);

        while(partid!=typemax+1)
        {
            flag1=0;
            flag2=0;
            count3=0;
            count4=0;
            for(j=0;j<count1;j++)
            {
                if(strcmp(save1[j]->b_parttype->name,ptype_list[partid]->data.name)==0)
                {
                    save3[count3]=save1[j];
                    count3++;
                    flag1=1;
                }
            }

            for(j=0;j<count2;j++)
            {
                if(strcmp(save2[j]->b_parttype->name,ptype_list[partid]->data.name)==0)
                {
                    save4[count4]=save1[j];
                    count4++;
                    flag2=1;
                }
            }
            system("cls");
            output_money();
            printf("进货记录：\n");
            outrec_mod0(flag1,save3,count3,0);
            printf("\n\n");
            printf("出售记录：\n");
            if(flag2==0)
                printf("记录为空！\n");
            else
            {
                output_chart_head_1(1);
                for(i=0;i<count4;i++)
                {
                    output_one(save4[i],0,count3+i+1);
                    printf("\n");
                }
            }
            for(i=0;i<count4;i++)
                save3[count3+i]=save4[i];
            if(flag1==0&&flag2==0)
            {
                system("cls");
                output_parttype_data(kptype,ptype_list);
                printf("请输入配件型号序号以查询对应型号的记录，输入\"%d\"结束\n",typemax+1);
                partid=judge_choice(typemax+1);
                continue;
            }
            printf("\n\n输入记录编号查询具体信息；输入%d返回上一步\n",count3+count4+1);
            while(1)
            {
            m=judge_choice(count3+count4+1);
            if(m==count3+count4+1)
                break;
            system("cls");
            output_money();
            output_one(save1[m-1],1,1);
            wait_enter();
            system("cls");
            output_money();
            printf("进货记录：\n");
            outrec_mod0(flag1,save3,count3,0);
            printf("\n\n");
            printf("出售记录：\n");
            if(flag2==0)
                printf("记录为空！\n");
            else
            {
                output_chart_head_1(1);
                for(i=0;i<count4;i++)
                {
                    output_one(save4[i],0,count3+i+1);
                    printf("\n");
                }
            }
            printf("\n\n输入记录编号查询具体信息；输入%d返回上一步\n",count3+count4+1);
            }
            system("cls");
            output_money();
            output_parttype_data(kptype,ptype_list);
            printf("请输入配件型号序号以查询对应型号的记录，输入%d结束\n",typemax+1);
            partid=judge_choice(typemax+1);
        }
        break;
        }
        output_one(save1[m-1],1,1);
        wait_enter();
    }
    system("cls");
    output_money();
    printf("配件列表:\n");
    output_part_data(p_list);
    printf("输入要查询的配件编号，输入%d返回上一步\n",maxpart+1);
    partid=judge_choice(maxpart+1);
    p=recordall->b_recordnext;
    }
}

void searchclient()//客户对应记录查找
{
    int flag=0,count=0,clmax;
    Record *p,*save[size];
    Client *c_list[size];
    system("cls");
    output_money();
    printf("客户列表：\n");
    clmax=output_client_data(dataclient,c_list);
    p=recordall->b_recordnext;

    printf("请输入要查询的客户编号,输入%d返回上一步\n",clmax+1);
    int clid;
    clid=judge_choice(clmax+1);
    while(1)
    {
        count=0;
        if(clid==clmax+1)
            return;
        while(p!=NULL)
        {
            if(p->recordtype==2||p->recordtype==3)
            {
                if(strcmp(p->b_client->name,c_list[clid]->name)==0)
                {
                    flag=1;
                    save[count]=p;
                    count++;
                }
            }
            p=p->b_recordnext;
        }
        if(flag==0)
        {
            printf("无相关记录\n");
            printf("按回车键继续\n");
            getchar();
            return;
        }
        system("cls");
        outputmod1(save,count,1);
        system("cls");
        output_money();
        printf("客户列表：\n");
        output_client_data(dataclient,c_list);
        p=recordall->b_recordnext;
        printf("请输入要查询的客户编号,输入%d以返回上一步\n",clmax+1);
        clid=judge_choice(clmax+1);
    }
    return;
}

void searchsupply()//供货商对应记录查找
{
    int flag=0,count=0,supmax,spid;
    Record *save[size];
    Record *p;
    Supply *sup_list[size];
    system("cls");
    output_money();
    printf("供货商列表：\n");
    supmax=output_supply_data(datasupply,sup_list);
    p=recordall->b_recordnext;
    printf("请输入要查询的供货商编号,输入%d返回上一步\n",supmax+1);
    spid=judge_choice(supmax+1);
    while(1)
    {
        count=0;
        if(spid==supmax+1)
            return;
        while(p!=NULL)
        {
            if(p->recordtype==1)
            {
                if(strcmp(p->b_supply->name,sup_list[spid]->name)==0)
                {
                    flag=1;
                    save[count]=p;
                    count++;
                }
            }
            p=p->b_recordnext;
        }
        if(flag==0)
        {
            printf("无相关记录\n");
            printf("按回车键继续\n");
            getchar();
            return;
        }
        system("cls");
        outputmod1(save,count,0);
        system("cls");
        output_money();
        printf("供货商列表：\n");
        output_supply_data(datasupply,sup_list);
        p=recordall->b_recordnext;
        printf("请输入要查询的供货商编号,输入%d返回上一步\n",supmax+1);
        spid=judge_choice(supmax+1);
    }
    return;
}

void searchperiod()//时间段内记录查找
{
    int flag=0,count=0;
    double profit=0;
    Record *p,*save[size];
    p=recordall->b_recordnext;
    Date per1,per2,tempper;
    system("cls");
    output_money();
    fflush(stdin);//清空缓冲区
    printf("请输入起始时间：（格式：月 日 时 分）\n");
    while(scanf("%d%d%d%d",&per1.month,&per1.day,&per1.hour,&per1.minute)!=4||judgedate(per1)==0)
    {
        printf("输入错误，请重试！\n");
        fflush(stdin);//清空缓冲区
    }
    fflush(stdin);//清空缓冲区
    printf("请输入终止时间：（格式：月 日 时 分）\n");
    while(scanf("%d%d%d%d",&per2.month,&per2.day,&per2.hour,&per2.minute)!=4||judgedate(per2)==0)
    {
        printf("输入错误，请重试！\n");
        fflush(stdin);//清空缓冲区
    }
    fflush(stdin);//清空缓冲区
    if(timecmp(per1,per2)>0)
    {
        tempper=per1;
        per1=per2;
        per2=tempper;
        printf("日期输入相反，将按照与输入相反的日期进行查询\n");
        wait_enter(4);
    }
    while(p!=NULL)
    {
        if((timecmp(p->b_date,per1)>=0)&&(timecmp(p->b_date,per2)<=0))
        {
            if(p->recordtype>0&&p->recordtype<4)
            {
                flag=1;
                save[count]=p;
                count++;
                switch(p->recordtype)
                {
                case stock:
                    profit-=p->amount*p->unit_price;
                    break;
                case retail:
                    profit+=p->amount*p->unit_price;
                    break;
                case wholesale:
                    profit+=p->amount*p->unit_price;
                    break;
                default:
                    ;
                }
            }
        }
        p=p->b_recordnext;
    }
    if(flag==0)
    {
        printf("无相关记录\n按回车键继续\n");
        while(getchar()!='\n');
        return;
    }
    printf("资金总额变化：%lf\n\n",profit);
    outputmod1(save,count,2);
    return;
}

void fuzzysearch()//模糊查询
{
    int i,j,cnt,count,f,flag,totlen;
    i=0;
    j=0;
    cnt=0;
    count=0;
    flag=0;
    char word[200],keyword[4][50],recstr[200];
    Record *p,*save[size];
    p=recordall->b_recordnext;
    system("cls");
    printf("请输入要查找的关键词,至多4个（配件/配件型号/客户/供货商）\n");
    gets(word);
    totlen=strlen(word);
    while(i<totlen&&cnt<4)
    {
        j=0;
        while(word[i]==' '&&i<totlen)
            i++;
        if(i==totlen&&cnt==0)
        {
         printf("错误：输入内容为空！\n");
         return;
        }
        while(word[i]!=' '&&i<totlen)
        {
            if(i==0||word[i-1]==' ')
                cnt++;
            keyword[cnt-1][j]=word[i];
            j++;
            i++;
        }
        if(j!=0)
            keyword[cnt-1][j]='\0';
    }
    while(p!=NULL)
    {
        strtrans(p,recstr);
        if(p->recordtype>0&&p->recordtype<4)
        {
            f=1;
            for(i=0;i<cnt;i++)
            {
                if(KmpSearch(recstr,keyword[i])==-1)
                    f=0;
            }
            if(f==1)
            {
                flag=1;
                save[count]=p;
                count++;
            }
        }
        p=p->b_recordnext;
    }
    if(flag==0)
    {
        system("cls");
        printf("无相关记录\n按回车键继续\n");
        while(getchar()!='\n');
        return;
    }
    system("cls");
    outputmod1(save,count,0);
    return;
}

void unit_price_change()//单价的动态变化
{
    Part_list* p;
    Parttype_list* pt;
    Record* pr;
    double average_amount;
    double target_amount;
    double temp_modify;//临时变化参数
    error_judge_2();//错误判断
    for(p=datapart->next;p!=NULL;p=p->next)
    {
        average_amount=all_sell_amount(&(p->data))/p->type_list->data.id;
        for(pt=p->type_list->next;pt!=NULL;pt=pt->next)
        {
            target_amount=0;
            for(pr=recordall->b_recordnext;pr!=NULL;pr=pr->b_recordnext)
            {
                if(pr->recordtype!=stock&&pr->color==0&&pr->b_part==&p->data&&pr->b_parttype==&pt->data)
                {
                    target_amount+=pr->amount;
                }
            }
            if(average_amount!=0)
            {
                temp_modify=target_amount/average_amount;
            }
            else
            {
                temp_modify=1;
            }
            if(temp_modify<=0.75)
            {
                pt->data.modify=0.75;
            }
            else if(temp_modify>=1.5)
            {
                pt->data.modify=1.5;
            }
            else
            {
                pt->data.modify=temp_modify;
            }
        }
    }
}

void suggest_in()//进货建议
{
    error_judge_2();//错误判断
    Part *temp_part[size];// *min_part_price=&(datapart->next->data);
    Part_list *p_part;
    Parttype *temp_type[size], *min_parttype_price=&(datapart->next->type_list->next->data);//存放临时的配件型号指针
    Parttype_list *p_parttype;
    Record *p;
    double benefit[size];
    int count=0,i=0,maxbenefit;
    /*资金过低警告*/
    if(money<1000)
    {
        printf("当前资金过低，建议补充资金后再进行贸易！\n");
    }

    /*建议进货盈利高的商品*/
    for(p=recordall->b_recordnext;p!=NULL;p=p->b_recordnext)
    {
        for(i=0;i<count;i++)
        {
            if(temp_part[i]==p->b_part&&temp_type[i]==p->b_parttype)//如果配件和已存地址重复，则停止循环
                break;
        }
        if(i==count)//如果是新类型的配件，则把地址存入临时数组
        {
            count++;
            temp_part[i]=p->b_part;
            temp_type[i]=p->b_parttype;
            benefit[i]=0;//初始化
        }
        if(p->recordtype==stock)
        {
            benefit[i]-=p->total_price;//进货，-
        }
        else
        {
            benefit[i]+=p->total_price;//售出，+
        }
    }
    for(i=0;i<count;i++)
    {
        if(i==0)maxbenefit=0;
        else maxbenefit=(benefit[maxbenefit]<benefit[i])?i:maxbenefit;
    }
    printf("%s配件的%s型号全年%s，为%.2f，建议增加进货\n",\
           temp_part[maxbenefit]->name,temp_type[maxbenefit]->name,\
           benefit[maxbenefit]>0?"获利最高":"亏损最低",fabs(benefit[maxbenefit]));

    /*囤货建议*/
    for(p_part=datapart->next;p_part!=NULL;p_part=p_part->next)
    {
        min_parttype_price=&(p_part->type_list->next->data);
        for(p_parttype=p_part->type_list->next;p_parttype!=NULL;p_parttype=p_parttype->next)
        {
            if(p_parttype->data.modify<min_parttype_price->modify)
            {
                min_parttype_price=&(p_parttype->data);
            }
        }
        printf("%s配件的%s型号正处于低价，建议增加进货\n",p_part->data.name,min_parttype_price->name);
    }
    wait_enter(4);
}

void price_predict(Part* key_part, Parttype* key_parttype)//价格预测（线性回归方程）
{
    system("cls");
    Record *p=recordall->b_recordnext;
    int p_month,i,j;
    double month12[12]={1,2,3,4,5,6,7,8,9,10,11,12};//十二个月
    double a,b;//线性回归方程的参数a,b
    double key_unit[3][12];//统计每个月的平均单价，进货/批发/零售
    double all_unit[3][2];//统计每个月的总单价，用于计算平均值，单价/个数
    for(i=0;i<3;i++)//初始化
    {
        for(j=0;j<12;j++)
        {
            key_unit[i][j]=0;//初始化，全部为0
        }
    }
    for(i=0;i<3;i++)//初始化
    {
        for(j=0;j<2;j++)
        {
            all_unit[i][j]=0;//初始化，全部为0
        }
    }
    for(p_month=1;;p=p->b_recordnext)
    {
        if(p==NULL||p->b_date.month!=p_month)//如果进入了下一个月，或者记录读完继续
        {
            for(j=0;j<3;j++)
            {
                if(all_unit[j][1]!=0)//数量不为0
                    key_unit[j][p_month-1]=all_unit[j][0]/all_unit[j][1];//计算平均单价
                //printf("%d月平均单价%.2f\n",p_month,key_unit[j][p_month-1]);
            }
            for(i=0;i<3;i++)
            {
                for(j=0;j<2;j++)
                {
                    all_unit[i][j]=0;//初始化，全部为0
                }
            }
            p_month++;
            if(p==NULL)
                break;
        }
        if(p->b_part==key_part&&p->b_parttype==key_parttype&&p->color==0)
        {
            switch(p->recordtype)
            {
            case stock:
                all_unit[0][0]+=p->unit_price;
                all_unit[0][1]++;
                break;
            case wholesale:
                all_unit[1][0]+=p->unit_price;
                all_unit[1][1]++;
                break;
            default:
                all_unit[2][0]+=p->unit_price;
                all_unit[2][1]++;
                break;
            }
        }
    }
    for(i=0;i<3;i++)
    {
        linear_regression(month12,key_unit[i],&b,&a);
        for(j=0;j<12;j++)
        {
            if(key_unit[i][j]!=0)
            {
                printf("%d月平均%s单价：%.2f\n",j+1,\
                       (i==0)?"进货":((i==1)?"批发":"零售"),key_unit[i][j]);
            }
        }
        if(b*13+a!=0)
            printf("\t预测明年1月该商品的%s单价为%.2f\n\n",(i==0)?"进货":((i==1)?"批发":"零售"),b*13+a);
    }
}


void history_file()//保存记录历史信息
{
    int i=0;
    char word1[size]="save\\history",word2[size];
    while(1)
    {
        i++;
        strcpy(word1,"save\\history");
        itoa(i,word2,10);//把数字转换成字符串
        strcat(word1,word2);
        strcat(word1,".txt");
        if(access(word1,0)==0)
            continue;
        else
        {
            save_record_to_file(word1);
            break;
        }
    }
}

void del_all()//删除所有记录
{
    Record *p=recordall->b_recordnext;
    while(p!=NULL)
    {
        del_one_record(p);
        p=recordall->b_recordnext;
    }
}




