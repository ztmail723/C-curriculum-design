#include"smallfunction.h"

Part *key_part_list(char *part_name)//返回输入配件名称的数据库
{
    Part_list *p=datapart;
    while(p!=NULL&&strcmp(p->data.name,part_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("读取错误！数据库中不存在名称为%s的配件！\n",part_name);
        return NULL;
    }
    return &(p->data);
}

Parttype_list *key_part_parttype(char *part_name)//返回输入配件名称的配件型号数据库头
{
    Part_list *p=datapart;
    while(p!=NULL&&strcmp(p->data.name,part_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("读取错误！数据库中不存在名称为%s的配件！\n",part_name);
        return NULL;
    }
    return p->type_list;
}

Parttype *key_parttype_list(char *part_name,char *parttype_name)//返回输入配件型号名称的数据库
{
    Part_list *p=datapart;
    while(p!=NULL&&strcmp(p->data.name,part_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("读取错误！数据库中不存在名称为%s的配件！\n",part_name);
        return NULL;
    }
    Parttype_list *p1=p->type_list;
    while(p1!=NULL&&strcmp(p1->data.name,parttype_name)!=0)
        p1=p1->next;
    if(p1==NULL)
    {
        printf("读取错误！数据库中不存在名称为%s的配件型号！\n",parttype_name);
        return NULL;
    }
    return &(p1->data);
}

Supply *key_supply_list(char *supply_name)//返回输入配件名称的数据库
{
    Supply *p=datasupply;
    while(p!=NULL&&strcmp(p->name,supply_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("读取错误！数据库中不存在名称为%s的供货商！\n",supply_name);
        return NULL;
    }
    return p;
}

Client *key_client_list(char *client_name)//返回输入客户名称的数据库
{
    Client *p=dataclient;
    while(p!=NULL&&strcmp(p->name,client_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("读取错误！数据库中不存在名称为%s的供货商！\n",client_name);
        return NULL;
    }
    return p;
}

int output_record(Record** choose_record)//输出记录
{
    Record *p=recordall;
    int i=0;
    error_judge_2();//错误判断
    output_chart_head(6);//输出表格项
    while(p->b_recordnext!=NULL)
    {
        p=p->b_recordnext;
        output_one(p,0,++i);//输出该条记录
        choose_record[i]=p;
        printf("\n");
    }
    return i;
}

void output_chart_head(int mode)//输出表格眉头
{
    switch(mode)
    {
    case 0:
        printf("编号\t时间\t\t配件\t\t配件型号\t数量\t\t总价\t\t供货商\t\t赠品\n");
        break;
    case 1:
        printf("编号\t时间\t\t配件\t\t配件型号\t数量\t\t总价\t\t客户\t\t赠品\n");
        break;
    case 2:
        printf("编号\t配件名称\n");
        break;
    case 3:
        printf("编号\t配件型号\t制造商\t\t库存\t\t平均进货单价\n");
        break;
    case 4:
        printf("编号\t客户类型\t名称\t\t性别\t\t单位\n");
        break;
    case 5:
        printf("编号\t供货商名称\n");
        break;
    case 6:
        printf("编号\t模式\t时间\t\t配件\t\t配件型号\t数量\t\t总价\t\t供货商/客户\t赠品\n");
    }
}

void output_chart_head_1(int mode)//输出查询记录列表的表格眉头
{
    switch(mode)
    {
    case 0:
        printf("编号\t类型\t时间\t\t配件\t\t配件型号\t数量\t\t总价\t\t供货商\t\t赠品\n");
        break;
    case 1:
        printf("编号\t类型\t时间\t\t配件\t\t配件型号\t数量\t\t总价\t\t客户\t\t赠品\n");
        break;
    case 2:
        printf("编号\t类型\t模式\t时间\t\t配件\t\t配件型号\t数量\t\t总价\t\t供货商/客户\t赠品\n");
    }
}

void output_parttype_dataone(Parttype *head,int i)//输出一件配件型号数据
{
    printf("%d\t%s%s%s%s%d%s%.2f",i,head->name,tabs(head->name),\
           head->partman,tabs(head->partman),\
           head->store,tabi(head->store),\
           head->stock_price);
}

int output_parttype_data(Parttype_list *head,Parttype_list **choose_parttype)//输出配件型号数据库
{
    int i=0;
    Parttype_list *p=head;
    output_chart_head(3);
    while(p!=NULL)
    {
        if(p!=head)
        {
            output_parttype_dataone(&p->data,++i);
            choose_parttype[i]=p;
            printf("\n");
        }
        p=p->next;
    }
    return i;
}

int output_part_data(Part_list **choose_part)//输出配件数据库，并按编号存储在数组里
{
    int i=0;
    Part_list *p=datapart;
    output_chart_head(2);
    while(p!=NULL)
    {
        if(p!=datapart)
        {
            output_part_dataone(&p->data,++i);
            choose_part[i]=p;
            printf("\n");
        }
        p=p->next;
    }
    return i;
}

void output_part_dataone(Part *head,int i)//输出一条配件数据
{
    printf("%d\t%s",i,head->name);
}

int output_client_data(Client *head,Client** choose_client)//输出客户数据库
{
    int i=0;
    Client *p=head;
    output_chart_head(4);
    while(p!=NULL)
    {
        if(p!=head)
        {
            output_client_dataone(p,++i);
            choose_client[i]=p;
            printf("\n");
        }
        p=p->next;
    }
    return i;
}

void output_client_dataone(Client *head,int i)//输出一条客户数据
{
    printf("%d\t%s\t\t%s%s%s\t\t%s",i,head->c_clienttype==group?"团体":"个人",\
           head->name,tabs(head->name),\
           head->gender==male?"男":(head->gender==female?"女":"无"),\
           head->unit);
}

int output_supply_data(Supply *head,Supply** choose_supply)//输出供货商数据库
{
    int i=0;
    Supply *p=head;
    output_chart_head(5);
    while(p!=NULL)
    {
        if(p!=head)
        {
            output_supply_dataone(p,++i);
            choose_supply[i]=p;
            printf("\n");
        }
        p=p->next;
    }
    return i;
}

void output_supply_dataone(Supply *head,int i)//输出一条供货商数据
{
    printf("%d\t%s",i,head->name);
}

void output_one(Record *head,int mode,int i)//输出一条记录（mode 0:简略记录 mode 1:完整记录）
{
    char tempstr[size];
    if(head->color==1)
    {
        color_change(10);//如果颜色改变，则输出绿色
    }
    if(mode==0)
    {
        timestr(tempstr,head->b_date,0);
        printf("%d\t%s\t",i,head->recordtype==stock?"进货":(head->recordtype==wholesale?"批发":"零售"));
        printf("%s%s",tempstr,tabs(tempstr));
        printf("%s%s",head->b_part->name,tabs(head->b_part->name));
        printf("%s%s",head->b_parttype->name,tabs(head->b_parttype->name));
        printf("%d%s",head->amount,tabi(head->amount));
        printf("%.2f%s",head->total_price,tabf(head->total_price));
        switch(head->recordtype)
        {
            case stock:
/*供货商*/      printf("%s%s",head->b_supply->name,tabs(head->b_supply->name));
                break;
            case wholesale:
/*客户*/        printf("%s%s",head->b_client->name,tabs(head->b_client->name));
                break;
            case retail:
/*客户*/        printf("%s%s",head->b_client->name,tabs(head->b_client->name));
                break;
            default:
                ;
        }
        if(head->b_present->next!=NULL)
        {
            printf("有");
        }
        else
        {
            printf("无");
        }
    }
    else if(mode==1)
    {
        timestr(tempstr,head->b_date,1);
        printf("时间：%s\n\
模式：%s\n\
配件：%s\n\
型号：%s\n\
数量：%d\n\
单价：%.2f\n\
总价：%.2f\n",\
        tempstr,\
        head->recordtype==stock?"进货":(head->recordtype==wholesale?"批发":"零售"),\
        head->b_part->name,\
        head->b_parttype->name,\
        head->amount,
        head->unit_price,
        head->total_price);
        switch(head->recordtype)
        {
            case stock:
                printf("供货商：%s\n",head->b_supply->name);
                break;
            case wholesale:
                printf("客户：%s\n",head->b_client->name);
                break;
            case retail:
                printf("客户：%s\n",head->b_client->name);
                break;
            default:
                ;
        }
        if(head->b_present->next!=NULL)
        {
            int j=0;
            Present* pre=head->b_present->next;
            printf("赠品：\n");//（需要进一步详细化）
            while(pre!=NULL)
            {
                j++;
                printf("%d.%d个%s型号%s\n",j,pre->amount,pre->part->name,pre->parttype->name);
                pre=pre->next;
            }
        }
        else
        {
            printf("赠品：无\n");
        }
    }
    color_change(7);//颜色改回
}

void outputmod1(Record **sdata,int cnt,int typ)//查询输出
{
    int det;
    system("cls");
    output_money();
    outrec_mod0(1,sdata,cnt,typ);
    printf("输入记录编号以查询具体信息；输入%d结束查询\n",cnt+1);
    det=judge_choice(cnt+1);
    error_judge_2();//错误判断
    while(1)
    {
        if(det==cnt+1)
            return;
        system("cls");
        output_one(sdata[det-1],1,1);
        wait_enter();
        system("cls");
        output_money();
        outrec_mod0(1,sdata,cnt,typ);
        printf("输入记录编号以查询具体信息；输入%d结束查询\n",cnt+1);
        det=judge_choice(cnt+1);
    }
}

void outrec_mod0(int flag,Record **save,int cnt,int typ)//输出简略查询结果
{
    int i;
    error_judge_2();//错误判断
    if(flag==0)
        printf("记录为空！\n");
    else
    {
        output_chart_head_1(typ);
        for(i=0;i<cnt;i++)
        {
            output_one(save[i],0,i+1);
            printf("\n");
        }
    }
    return;
}

void sorttime(Record *p)//按照时间顺序插入指定结点（李墨馨）
{
    Record *p0=recordall;
    while(p0->b_recordnext!=NULL)
    {
        if(timecmp(p->b_date,p0->b_recordnext->b_date)<0)
            break;
        p0=p0->b_recordnext;
    }
    p->b_recordnext=p0->b_recordnext;
    p0->b_recordnext=p;
}

void dropoff(Record *p)//将某一节点摘下
{
    Record *p0=recordall;
    while(p0->b_recordnext!=p)p0=p0->b_recordnext;
    p0->b_recordnext=p->b_recordnext;
}

void headvalue()//哨兵结点的初始化
{
    recordall=(Record*)malloc(sizeof(Record));
    recordall->b_part=&(datapart->data);
    recordall->b_parttype=&(datapart->type_list->data);
    recordall->id=0;
    recordall->amount=0;
    recordall->unit_price=0;
    recordall->b_date.month=0;
    recordall->b_date.day=0;
    recordall->b_date.hour=0;
    recordall->b_date.minute=0;
    recordall->recordtype=nullrecord;
    recordall->b_client=NULL;
    recordall->b_supply=NULL;
    recordall->b_present=NULL;
    recordall->b_recordnext=NULL;
    return;
}

int leap_year(int year)//判断闰年
{
    return (year%400==0||(year%100!=0&&year%4==0))?1:0;
}

int nowyear()//输出当前年份
{
    time_t t;
    struct tm * lt;
    time (&t);
    lt = localtime (&t);
    return lt->tm_year+1900;
}

int judgedate(Date date)//判断给定日期是否合法
{
    if(date.month<1||date.month>12)
        return 0;
    if(date.day<1||date.day>monthday[date.month])
        return 0;
    if(date.hour<0||date.hour>23)
        return 0;
    if(date.minute<0||date.minute>59)
        return 0;
    return 1;
}

/*比较两个日期的先后，t1大返回1，t2大返回-1，相等返回0（李墨馨）*/
int timecmp(Date t1,Date t2)
{
    if(t1.month>t2.month)
        return 1;
    if(t1.month<t2.month)
        return -1;
    if(t1.month==t2.month)
    {
        if(t1.day>t2.day)
            return 1;
        if(t1.day<t2.day)
            return -1;
        if(t1.day==t2.day)
        {
            if(t1.hour>t2.hour)
                return 1;
            if(t1.hour<t2.hour)
                return -1;
            if(t1.hour==t2.hour)
            {
                if(t1.minute>t2.minute)
                    return 1;
                if(t1.minute<t2.minute)
                    return -1;
                if(t1.minute==t2.minute)
                    return 0;
            }
        }
    }
    return 0;
}

/*将日期转换为字符串，并存于savestr数组中（章门）*/
void timestr(char *savestr,Date date,int mode)//模式0：简略 模式1：汉字 模式2：表格
{
    char strmonth[10],strday[10],strhour[10],strmin[10];
    if(date.month<=9)
    {
        strmonth[0]='0';
        strmonth[1]='0'+date.month;
        strmonth[2]='\0';
    }
    else
    {
        strmonth[0]='0'+(date.month)/10;
        strmonth[1]='0'+(date.month)%10;
        strmonth[2]='\0';
    }

    if(date.day<=9)
    {
        strday[0]='0';
        strday[1]='0'+date.day;
        strday[2]='\0';
    }
    else
    {
        strday[0]='0'+(date.day)/10;
        strday[1]='0'+(date.day)%10;
        strday[2]='\0';
    }

    if(date.hour<=9)
    {
        strhour[0]='0';
        strhour[1]='0'+date.hour;
        strhour[2]='\0';
    }
    else
    {
        strhour[0]='0'+(date.hour)/10;
        strhour[1]='0'+(date.hour)%10;
        strhour[2]='\0';
    }

    if(date.minute<=9)
    {
        strmin[0]='0';
        strmin[1]='0'+date.minute;
        strmin[2]='\0';
    }
    else
    {
        strmin[0]='0'+(date.minute)/10;
        strmin[1]='0'+(date.minute)%10;
        strmin[2]='\0';
    }

    switch(mode)
    {
        case 0:
            strcpy(savestr,strmonth);strcat(savestr,"/");
            strcat(savestr,strday);strcat(savestr," ");
            strcat(savestr,strhour);strcat(savestr,":");
            strcat(savestr,strmin);break;
        case 1:
            strcpy(savestr,strmonth);strcat(savestr,"月");
            strcat(savestr,strday);strcat(savestr,"日");
            strcat(savestr,strhour);strcat(savestr,"时");
            strcat(savestr,strmin);strcat(savestr,"分");break;
        case 2:
            strcpy(savestr,strmonth);strcat(savestr,"/");
            strcat(savestr,strday);strcat(savestr,"\t");
            strcat(savestr,strhour);strcat(savestr,":");
            strcat(savestr,strmin);strcat(savestr,"\t");
    }
    return;
}


/*根据长度返回不同的制表符（章门）*/
char *tabs(char *str)
{
    return (strlen(str)<8)?"\t\t":"\t";
}
char *tabi(int num)
{
    return (num<10000000)?"\t\t":"\t";
}
char *tabf(double num)
{
    return (num<10000)?"\t\t":"\t";
}


int judge_choice(int maxid)
{
    int option_choice;
    //setbuf(stdin, NULL);
    fflush(stdin);
    while(scanf("%d",&option_choice)!=1||\
          option_choice>maxid||\
          option_choice<1)
    {
        printf("输入错误，请重试！\n");
        while(getchar()!='\n');
        fflush(stdin);
    }
    //setbuf(stdin, NULL);
    fflush(stdin);
    return option_choice;
}

void randnum(int maxnum,int amount,int *a)//生成amount个从1到maxnum的随机数，存储在a数组里
{
    int i,w,t;
    srand((unsigned)time(0));
    for(i=0;i<maxnum;i++)
        a[i]=i+1;
    for(i=0;i<amount;i++)
    {
        w=rand()%(maxnum-i)+i;
        t=a[i];
        a[i]=a[w];
        a[w]=t;
    }
}

void randpre(int amount,Present *pre)//对礼物数组进行随机排序
{
    int i,w;
    Present t;
    srand((unsigned)time(0));
    for(i=0;i<amount;i++)
    {
        w=rand()%amount;
        t=pre[i];
        pre[i]=pre[w];
        pre[w]=t;
    }
}

int judge_success(int success_rate)//输入成功率，输出0（失败）或1（成功）
{
    int a;
    srand((unsigned)time(0));
    a=rand()%100+1;
    if(success_rate>=a)
    {
        return 1;
    }
    return 0;
}

void wait_enter(int i)//操作后，等待
{
    setbuf(stdin, NULL);
    switch(i)
    {
    case 0:
        printf("\n操作失败！\n按回车键继续！");
        while(getchar()!='\n');
        break;
    case 1:
        printf("\n操作结束！\n按回车键继续！");
        while(getchar()!='\n');
        break;
    case 2:
        printf("\n操作已取消！\n按回车键继续！");
        while(getchar()!='\n');
        break;
    case 3:
        printf("\n操作错误！\n按回车键继续！");
        while(getchar()!='\n');
        break;
    default:
        printf("\n按回车键继续！");
        while(getchar()!='\n');
    }
    setbuf(stdin, NULL);
}

void output_money()//输出当前金钱数量
{
    printf("当前金钱：%.2f\n",money);
}

void color_change(short x)	//自定义函根据参数改变颜色
{
    if(x>=0 && x<=15)//参数在0-15的范围颜色
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//只有一个参数，改变字体颜色
    else//默认的颜色白色
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void linear_regression(double x[], double y[], double *b, double *a)//生成一个线性回归方程
{
	double xx=0,yy=0,b_on=0,b_down=0,num=0;
	int i=0;
	*b=0;
	*a=0;
	for(i=0;i<12;i++)
	{
		if(x[i]==0||y[i]==0)
		{
			num++;
			continue;
		}
		xx+=x[i];yy+=y[i];
	}
	if(num!=12)
    {
        xx=xx/(12-num);
        yy=yy/(12-num);
    }
    else
    {
        return;
    }
	for(i=0;i<12;i++)
	{
		if(x[i]==0||y[i]==0)
		{
			continue;
		}
		b_on+=(x[i]-xx)*(y[i]-yy);
		b_down+=(x[i]-xx)*(x[i]-xx);
	}
	if(b_down!=0)
        *b=b_on/b_down;
    else
    {
        *b=0;
        //yy=xx;
    }
	*a=yy-(*b)*xx;
}

double all_sell_amount(Part *keypart)//计算同配件不同型号产品的总销售数量
{
    Record *p;//遍历记录用的变量
    double all_amount=0;
    for(p=recordall->b_recordnext;p!=NULL;p=p->b_recordnext)
    {
        if(p->recordtype!=stock&&p->color==0&&p->b_part==keypart)//条件有3：1.为出售记录 2.记录合法 3.记录为指定配件
        {
            all_amount+=p->amount;
        }
    }
    return all_amount;
}

void solve_record(Record *key_record,int mode)//结算记录,mode0还原,mode1新增。
{
    double tempmoney=key_record->total_price;
    double tempstore=key_record->amount;
    Present *p=key_record->b_present;
    while(p->next!=NULL)
    {
        p=p->next;
        if(mode==0)
            p->parttype->store+=p->amount;
        else
            p->parttype->store-=p->amount;
    }
    if(key_record->recordtype==stock)//如果是买入，取反
    {
        tempmoney=-tempmoney;
        tempstore=-tempstore;
    }
    if(mode==0)//如果是还原，取反
    {
        tempmoney=-tempmoney;
        tempstore=-tempstore;
    }
    key_record->b_parttype->store-=tempstore;
    money+=tempmoney;
    return;
}

void solve_record_vir(Record *key_record,double *virmoney)//模拟结算记录（错误检测用）
{
    double tempmoney=key_record->total_price;
    double tempstore=key_record->amount;
    Present *p=key_record->b_present;
    while(p->next!=NULL)
    {
        p=p->next;
        p->parttype->store-=p->amount;
        if(p->parttype->store<0)
        {
            key_record->color=1;//发现错误，则标记
        }
    }
    if(key_record->recordtype==stock)//如果是买入，取反
    {
        tempmoney=-tempmoney;
        tempstore=-tempstore;
    }
    key_record->b_parttype->store-=tempstore;
    (*virmoney)+=tempmoney;
    if(key_record->b_parttype->store<0||(*virmoney)<0)
    {
        key_record->color=1;//发现错误标记
    }
    return;
}

int error_judge()//错误判断（主菜单）
{
    int yes=1;
    double tempmoney=5000000;
    Part_list *p0;
    Parttype_list *p;
    Record *p1;
    for(p0=datapart->next;p0!=NULL;p0=p0->next)//初始化
    {
        for(p=p0->type_list->next;p!=NULL;p=p->next)
        {
            p->data.store=0;
        }
    }
    for(p1=recordall->b_recordnext;p1!=NULL;p1=p1->b_recordnext)
    {
        p1->color=0;
        solve_record_vir(p1,&tempmoney);
        if(p1->color==1)yes=0;
    }
    if(yes==0)
    {
        printf("\n警告！\n当前记录存在错误！\n可能存在问题的记录已用");
        color_change(10);
        printf("绿色");
        color_change(7);
        printf("标记\n请尝试修改或完善您的记录！\n");
    }
    return yes;
}

int error_judge_2()//不显示提示的错误检测
{
    int yes=1;
    double tempmoney=5000000;
    Part_list *p0;
    Parttype_list *p;
    Record *p1;
    for(p0=datapart->next;p0!=NULL;p0=p0->next)//初始化
    {
        for(p=p0->type_list->next;p!=NULL;p=p->next)
        {
            p->data.store=0;
        }
    }
    for(p1=recordall->b_recordnext;p1!=NULL;p1=p1->b_recordnext)
    {
        p1->color=0;
        solve_record_vir(p1,&tempmoney);
        if(p1->color==1)yes=0;
    }
    return yes;
}

void strtrans(Record *p,char *recstr)//将记录转换成字符串
{
    //memset(recstr,0,sizeof(recstr));
    strcpy(recstr,p->b_part->name);
    strcat(recstr,p->b_parttype->name);
    if(p->recordtype==1)
        strcat(recstr,p->b_supply->name);
    if(p->recordtype==2||p->recordtype==3)
    {
        strcat(recstr,p->b_client->name);
    }
    return;
}

int KmpSearch(char* s, char* p)//KMP算法
{
	int i=0,j=0,k=-1,n=0;
	int slen=strlen(s);
	int plen =strlen(p);
	int next[slen];
	next[0]=-1;
    while(n<plen-1)
	{
		if(k==-1||p[n]==p[k])
		{
			k++;
			n++;
			next[n]=k;
		}
		else
		{
			k=next[k];
		}
	}
	while(i<slen&&j<plen)
	{
		if (j==-1||s[i]==p[j])
		{
			i++;
			j++;
		}
		else
		{
			j=next[j];
		}
	}
	if (j==plen)
		return i-j;
	else
		return -1;
}

double total_sales(Record *p)//从（销售）记录中求总价和 （求销售总额）
{
    double totalsaves=0;
    for(p=p->b_recordnext;p!=NULL;p=p->b_recordnext)
    {
        if(p->recordtype!=stock)totalsaves+=p->total_price;
    }
    return totalsaves;
}

double total_profit(Record* p)//从（销售）记录中求总盈利（魏来）
{
    //double onesave=0;
    double allsave=0;
    Record *p0;
//    Record *p1=p;
    for(p0=recordall->b_recordnext;p0!=NULL;p0=p0->b_recordnext)
    {
        if(p0->recordtype==stock)
            allsave-=p0->total_price;
        else
            allsave+=p0->total_price;
    }
    /*
    for(;p0!=NULL;p0=p0->b_recordnext)
    {
        if(p0->recordtype==wholesale||p0->recordtype==retail)
        {
            for(p1=p;p1!=p0;p1=p1->b_recordnext)
            {
                if((p1->recordtype==stock)&&(strcmp(p0->b_part->name,p1->b_part->name)==0)&&(strcmp(p0->b_parttype->name,p1->b_parttype->name)==0))
                {
                    onesave=p0->amount*(p0->unit_price-p1->unit_price);
                    allsave+=onesave;
                    break;
                }
            }
        }
    }
    */
    return allsave;
}


