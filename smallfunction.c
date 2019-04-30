#include"smallfunction.h"

Part *key_part_list(char *part_name)//��������������Ƶ����ݿ�
{
    Part_list *p=datapart;
    while(p!=NULL&&strcmp(p->data.name,part_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("��ȡ�������ݿ��в���������Ϊ%s�������\n",part_name);
        return NULL;
    }
    return &(p->data);
}

Parttype_list *key_part_parttype(char *part_name)//��������������Ƶ�����ͺ����ݿ�ͷ
{
    Part_list *p=datapart;
    while(p!=NULL&&strcmp(p->data.name,part_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("��ȡ�������ݿ��в���������Ϊ%s�������\n",part_name);
        return NULL;
    }
    return p->type_list;
}

Parttype *key_parttype_list(char *part_name,char *parttype_name)//������������ͺ����Ƶ����ݿ�
{
    Part_list *p=datapart;
    while(p!=NULL&&strcmp(p->data.name,part_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("��ȡ�������ݿ��в���������Ϊ%s�������\n",part_name);
        return NULL;
    }
    Parttype_list *p1=p->type_list;
    while(p1!=NULL&&strcmp(p1->data.name,parttype_name)!=0)
        p1=p1->next;
    if(p1==NULL)
    {
        printf("��ȡ�������ݿ��в���������Ϊ%s������ͺţ�\n",parttype_name);
        return NULL;
    }
    return &(p1->data);
}

Supply *key_supply_list(char *supply_name)//��������������Ƶ����ݿ�
{
    Supply *p=datasupply;
    while(p!=NULL&&strcmp(p->name,supply_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("��ȡ�������ݿ��в���������Ϊ%s�Ĺ����̣�\n",supply_name);
        return NULL;
    }
    return p;
}

Client *key_client_list(char *client_name)//��������ͻ����Ƶ����ݿ�
{
    Client *p=dataclient;
    while(p!=NULL&&strcmp(p->name,client_name)!=0)
        p=p->next;
    if(p==NULL)
    {
        printf("��ȡ�������ݿ��в���������Ϊ%s�Ĺ����̣�\n",client_name);
        return NULL;
    }
    return p;
}

int output_record(Record** choose_record)//�����¼
{
    Record *p=recordall;
    int i=0;
    error_judge_2();//�����ж�
    output_chart_head(6);//��������
    while(p->b_recordnext!=NULL)
    {
        p=p->b_recordnext;
        output_one(p,0,++i);//���������¼
        choose_record[i]=p;
        printf("\n");
    }
    return i;
}

void output_chart_head(int mode)//������üͷ
{
    switch(mode)
    {
    case 0:
        printf("���\tʱ��\t\t���\t\t����ͺ�\t����\t\t�ܼ�\t\t������\t\t��Ʒ\n");
        break;
    case 1:
        printf("���\tʱ��\t\t���\t\t����ͺ�\t����\t\t�ܼ�\t\t�ͻ�\t\t��Ʒ\n");
        break;
    case 2:
        printf("���\t�������\n");
        break;
    case 3:
        printf("���\t����ͺ�\t������\t\t���\t\tƽ����������\n");
        break;
    case 4:
        printf("���\t�ͻ�����\t����\t\t�Ա�\t\t��λ\n");
        break;
    case 5:
        printf("���\t����������\n");
        break;
    case 6:
        printf("���\tģʽ\tʱ��\t\t���\t\t����ͺ�\t����\t\t�ܼ�\t\t������/�ͻ�\t��Ʒ\n");
    }
}

void output_chart_head_1(int mode)//�����ѯ��¼�б�ı��üͷ
{
    switch(mode)
    {
    case 0:
        printf("���\t����\tʱ��\t\t���\t\t����ͺ�\t����\t\t�ܼ�\t\t������\t\t��Ʒ\n");
        break;
    case 1:
        printf("���\t����\tʱ��\t\t���\t\t����ͺ�\t����\t\t�ܼ�\t\t�ͻ�\t\t��Ʒ\n");
        break;
    case 2:
        printf("���\t����\tģʽ\tʱ��\t\t���\t\t����ͺ�\t����\t\t�ܼ�\t\t������/�ͻ�\t��Ʒ\n");
    }
}

void output_parttype_dataone(Parttype *head,int i)//���һ������ͺ�����
{
    printf("%d\t%s%s%s%s%d%s%.2f",i,head->name,tabs(head->name),\
           head->partman,tabs(head->partman),\
           head->store,tabi(head->store),\
           head->stock_price);
}

int output_parttype_data(Parttype_list *head,Parttype_list **choose_parttype)//�������ͺ����ݿ�
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

int output_part_data(Part_list **choose_part)//���������ݿ⣬������Ŵ洢��������
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

void output_part_dataone(Part *head,int i)//���һ���������
{
    printf("%d\t%s",i,head->name);
}

int output_client_data(Client *head,Client** choose_client)//����ͻ����ݿ�
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

void output_client_dataone(Client *head,int i)//���һ���ͻ�����
{
    printf("%d\t%s\t\t%s%s%s\t\t%s",i,head->c_clienttype==group?"����":"����",\
           head->name,tabs(head->name),\
           head->gender==male?"��":(head->gender==female?"Ů":"��"),\
           head->unit);
}

int output_supply_data(Supply *head,Supply** choose_supply)//������������ݿ�
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

void output_supply_dataone(Supply *head,int i)//���һ������������
{
    printf("%d\t%s",i,head->name);
}

void output_one(Record *head,int mode,int i)//���һ����¼��mode 0:���Լ�¼ mode 1:������¼��
{
    char tempstr[size];
    if(head->color==1)
    {
        color_change(10);//�����ɫ�ı䣬�������ɫ
    }
    if(mode==0)
    {
        timestr(tempstr,head->b_date,0);
        printf("%d\t%s\t",i,head->recordtype==stock?"����":(head->recordtype==wholesale?"����":"����"));
        printf("%s%s",tempstr,tabs(tempstr));
        printf("%s%s",head->b_part->name,tabs(head->b_part->name));
        printf("%s%s",head->b_parttype->name,tabs(head->b_parttype->name));
        printf("%d%s",head->amount,tabi(head->amount));
        printf("%.2f%s",head->total_price,tabf(head->total_price));
        switch(head->recordtype)
        {
            case stock:
/*������*/      printf("%s%s",head->b_supply->name,tabs(head->b_supply->name));
                break;
            case wholesale:
/*�ͻ�*/        printf("%s%s",head->b_client->name,tabs(head->b_client->name));
                break;
            case retail:
/*�ͻ�*/        printf("%s%s",head->b_client->name,tabs(head->b_client->name));
                break;
            default:
                ;
        }
        if(head->b_present->next!=NULL)
        {
            printf("��");
        }
        else
        {
            printf("��");
        }
    }
    else if(mode==1)
    {
        timestr(tempstr,head->b_date,1);
        printf("ʱ�䣺%s\n\
ģʽ��%s\n\
�����%s\n\
�ͺţ�%s\n\
������%d\n\
���ۣ�%.2f\n\
�ܼۣ�%.2f\n",\
        tempstr,\
        head->recordtype==stock?"����":(head->recordtype==wholesale?"����":"����"),\
        head->b_part->name,\
        head->b_parttype->name,\
        head->amount,
        head->unit_price,
        head->total_price);
        switch(head->recordtype)
        {
            case stock:
                printf("�����̣�%s\n",head->b_supply->name);
                break;
            case wholesale:
                printf("�ͻ���%s\n",head->b_client->name);
                break;
            case retail:
                printf("�ͻ���%s\n",head->b_client->name);
                break;
            default:
                ;
        }
        if(head->b_present->next!=NULL)
        {
            int j=0;
            Present* pre=head->b_present->next;
            printf("��Ʒ��\n");//����Ҫ��һ����ϸ����
            while(pre!=NULL)
            {
                j++;
                printf("%d.%d��%s�ͺ�%s\n",j,pre->amount,pre->part->name,pre->parttype->name);
                pre=pre->next;
            }
        }
        else
        {
            printf("��Ʒ����\n");
        }
    }
    color_change(7);//��ɫ�Ļ�
}

void outputmod1(Record **sdata,int cnt,int typ)//��ѯ���
{
    int det;
    system("cls");
    output_money();
    outrec_mod0(1,sdata,cnt,typ);
    printf("�����¼����Բ�ѯ������Ϣ������%d������ѯ\n",cnt+1);
    det=judge_choice(cnt+1);
    error_judge_2();//�����ж�
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
        printf("�����¼����Բ�ѯ������Ϣ������%d������ѯ\n",cnt+1);
        det=judge_choice(cnt+1);
    }
}

void outrec_mod0(int flag,Record **save,int cnt,int typ)//������Բ�ѯ���
{
    int i;
    error_judge_2();//�����ж�
    if(flag==0)
        printf("��¼Ϊ�գ�\n");
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

void sorttime(Record *p)//����ʱ��˳�����ָ����㣨��īܰ��
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

void dropoff(Record *p)//��ĳһ�ڵ�ժ��
{
    Record *p0=recordall;
    while(p0->b_recordnext!=p)p0=p0->b_recordnext;
    p0->b_recordnext=p->b_recordnext;
}

void headvalue()//�ڱ����ĳ�ʼ��
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

int leap_year(int year)//�ж�����
{
    return (year%400==0||(year%100!=0&&year%4==0))?1:0;
}

int nowyear()//�����ǰ���
{
    time_t t;
    struct tm * lt;
    time (&t);
    lt = localtime (&t);
    return lt->tm_year+1900;
}

int judgedate(Date date)//�жϸ��������Ƿ�Ϸ�
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

/*�Ƚ��������ڵ��Ⱥ�t1�󷵻�1��t2�󷵻�-1����ȷ���0����īܰ��*/
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

/*������ת��Ϊ�ַ�����������savestr�����У����ţ�*/
void timestr(char *savestr,Date date,int mode)//ģʽ0������ ģʽ1������ ģʽ2�����
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
            strcpy(savestr,strmonth);strcat(savestr,"��");
            strcat(savestr,strday);strcat(savestr,"��");
            strcat(savestr,strhour);strcat(savestr,"ʱ");
            strcat(savestr,strmin);strcat(savestr,"��");break;
        case 2:
            strcpy(savestr,strmonth);strcat(savestr,"/");
            strcat(savestr,strday);strcat(savestr,"\t");
            strcat(savestr,strhour);strcat(savestr,":");
            strcat(savestr,strmin);strcat(savestr,"\t");
    }
    return;
}


/*���ݳ��ȷ��ز�ͬ���Ʊ�������ţ�*/
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
        printf("������������ԣ�\n");
        while(getchar()!='\n');
        fflush(stdin);
    }
    //setbuf(stdin, NULL);
    fflush(stdin);
    return option_choice;
}

void randnum(int maxnum,int amount,int *a)//����amount����1��maxnum����������洢��a������
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

void randpre(int amount,Present *pre)//��������������������
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

int judge_success(int success_rate)//����ɹ��ʣ����0��ʧ�ܣ���1���ɹ���
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

void wait_enter(int i)//�����󣬵ȴ�
{
    setbuf(stdin, NULL);
    switch(i)
    {
    case 0:
        printf("\n����ʧ�ܣ�\n���س���������");
        while(getchar()!='\n');
        break;
    case 1:
        printf("\n����������\n���س���������");
        while(getchar()!='\n');
        break;
    case 2:
        printf("\n������ȡ����\n���س���������");
        while(getchar()!='\n');
        break;
    case 3:
        printf("\n��������\n���س���������");
        while(getchar()!='\n');
        break;
    default:
        printf("\n���س���������");
        while(getchar()!='\n');
    }
    setbuf(stdin, NULL);
}

void output_money()//�����ǰ��Ǯ����
{
    printf("��ǰ��Ǯ��%.2f\n",money);
}

void color_change(short x)	//�Զ��庯���ݲ����ı���ɫ
{
    if(x>=0 && x<=15)//������0-15�ķ�Χ��ɫ
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), x);	//ֻ��һ���������ı�������ɫ
    else//Ĭ�ϵ���ɫ��ɫ
    	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}

void linear_regression(double x[], double y[], double *b, double *a)//����һ�����Իع鷽��
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

double all_sell_amount(Part *keypart)//����ͬ�����ͬ�ͺŲ�Ʒ������������
{
    Record *p;//������¼�õı���
    double all_amount=0;
    for(p=recordall->b_recordnext;p!=NULL;p=p->b_recordnext)
    {
        if(p->recordtype!=stock&&p->color==0&&p->b_part==keypart)//������3��1.Ϊ���ۼ�¼ 2.��¼�Ϸ� 3.��¼Ϊָ�����
        {
            all_amount+=p->amount;
        }
    }
    return all_amount;
}

void solve_record(Record *key_record,int mode)//�����¼,mode0��ԭ,mode1������
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
    if(key_record->recordtype==stock)//��������룬ȡ��
    {
        tempmoney=-tempmoney;
        tempstore=-tempstore;
    }
    if(mode==0)//����ǻ�ԭ��ȡ��
    {
        tempmoney=-tempmoney;
        tempstore=-tempstore;
    }
    key_record->b_parttype->store-=tempstore;
    money+=tempmoney;
    return;
}

void solve_record_vir(Record *key_record,double *virmoney)//ģ������¼���������ã�
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
            key_record->color=1;//���ִ�������
        }
    }
    if(key_record->recordtype==stock)//��������룬ȡ��
    {
        tempmoney=-tempmoney;
        tempstore=-tempstore;
    }
    key_record->b_parttype->store-=tempstore;
    (*virmoney)+=tempmoney;
    if(key_record->b_parttype->store<0||(*virmoney)<0)
    {
        key_record->color=1;//���ִ�����
    }
    return;
}

int error_judge()//�����жϣ����˵���
{
    int yes=1;
    double tempmoney=5000000;
    Part_list *p0;
    Parttype_list *p;
    Record *p1;
    for(p0=datapart->next;p0!=NULL;p0=p0->next)//��ʼ��
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
        printf("\n���棡\n��ǰ��¼���ڴ���\n���ܴ�������ļ�¼����");
        color_change(10);
        printf("��ɫ");
        color_change(7);
        printf("���\n�볢���޸Ļ��������ļ�¼��\n");
    }
    return yes;
}

int error_judge_2()//����ʾ��ʾ�Ĵ�����
{
    int yes=1;
    double tempmoney=5000000;
    Part_list *p0;
    Parttype_list *p;
    Record *p1;
    for(p0=datapart->next;p0!=NULL;p0=p0->next)//��ʼ��
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

void strtrans(Record *p,char *recstr)//����¼ת�����ַ���
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

int KmpSearch(char* s, char* p)//KMP�㷨
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

double total_sales(Record *p)//�ӣ����ۣ���¼�����ܼۺ� ���������ܶ
{
    double totalsaves=0;
    for(p=p->b_recordnext;p!=NULL;p=p->b_recordnext)
    {
        if(p->recordtype!=stock)totalsaves+=p->total_price;
    }
    return totalsaves;
}

double total_profit(Record* p)//�ӣ����ۣ���¼������ӯ����κ����
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


