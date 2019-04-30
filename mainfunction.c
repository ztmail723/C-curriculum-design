#include"smallfunction.h"
#include"mainfunction.h"
Part_list* loadpart(char *filename)//�����ݿ��ж�ȡ���
{
    char tempname[size]="#";
    Part_list *head=(Part_list*)malloc(sizeof(Part_list));//�½�ͷ���
    Part_list *p=head;
        head->data.id=0;
        strcpy(head->data.name,"#");
        head->type_list=(Parttype_list*)malloc(sizeof(Parttype_list));
    Parttype_list *temphead[size];
    temphead[0]=head->type_list;
    int i=0,j=0;
    FILE *fp=fopen(filename,"r");
    if(fp==NULL)//�����ж�
    {
        printf("���ļ�%sʧ�ܣ�\n",filename);
        return 0;
    }
    fscanf(fp,"%*[^\n]%*[\n]");//��ȥ��һ��
    while(!feof(fp))
    {
        fscanf(fp,"%[^\t]%*[\t]",tempname);
        if(strcmp(tempname,p->data.name)!=0)//�����ȡ����һ���������һ�������ͬ�����½��������
        {
            p->type_list->next=NULL;//��һ������ĵ��ͺ�ָ��NULL
            temphead[p->data.id]->data.id=j;//ͷ����id�洢��������
            p->next=(Part_list*)malloc(sizeof(Part_list));//�½����
            p=p->next;
            p->data.id=++i;//��ų�ʼ��
            strcpy(p->data.name,tempname);
            j=0;//����ͺű�ų�ʼ��
            p->type_list=(Parttype_list*)malloc(sizeof(Parttype_list));//�½�����ͺ�
            p->type_list->data.id=0;
            p->type_list->data.keynum=0;
            p->type_list->data.modify=1.00;
            strcpy(p->type_list->data.name,"#");
            temphead[i]=p->type_list;
        }
        p->type_list->next=(Parttype_list*)malloc(sizeof(Parttype_list));
        p->type_list=p->type_list->next;
        p->type_list->data.id=++j;
        p->type_list->data.modify=1.00;//����ָ����ʼΪ1.00
        fscanf(fp,"%[^\t]%*[\t]",p->type_list->data.name);//������
        fscanf(fp,"%[^\t]%*[\t]",p->type_list->data.partman);
        fscanf(fp,"%d%*[\t]",&p->type_list->data.store);
        fscanf(fp,"%d%*[\t]",&p->type_list->data.keynum);
        fscanf(fp,"%lf/%lf/%lf%*[\n]",&p->type_list->data.stock_price,&p->type_list->data.wholesale_price,&p->type_list->data.retail_price);
    }
    p->next=NULL;
    p->type_list->next=NULL;
    temphead[p->data.id]->data.id=j;//ͷ����id�洢��������
    fclose(fp);
    for(p=head->next;p!=NULL;p=p->next)
    {
        p->type_list=temphead[p->data.id];
    }
    head->data.id=i;
    return head;
}

Supply *loadsupply(char *filename)//�����ݿ��ж�ȡ������
{
    Supply *head=(Supply*)malloc(sizeof(Supply));
    Supply *p=head;
        head->id=0;
    FILE *fp=fopen(filename,"r");
    int i=0;
    if(fp==NULL)//�����ж�
    {
        printf("���ļ�%sʧ�ܣ�\n",filename);
        return 0;
    }
    fscanf(fp,"%*[^\n]%*[\n]");//��ȥ��һ��
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

Client *loadclient(char *filename)//�����ݿ��ж�ȡ�ͻ�
{
    Client *head=(Client*)malloc(sizeof(Client));
    Client *p=head;
        head->id=0;
    FILE *fp=fopen(filename,"r");
    int i=0;
    char temptype[size],tempgender[size];
    if(fp==NULL)//�����ж�
    {
        printf("���ļ�%sʧ�ܣ�\n",filename);
        return 0;
    }
    fscanf(fp,"%*[^\n]%*[\n]");//��ȥ��һ��
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

void load_record_from_file(char *filename)//���ļ��ж�ȡ��¼
{
    int temp;
    char tempname[size];//�����ʱ�ַ���
    Record *key_record;
    Present *key_present;
    FILE *fp=fopen(filename,"r");
    if(fp==NULL)//�����ж�
    {
        printf("���ļ�%sʧ�ܣ�\n",filename);
        return;
    }
    fscanf(fp,"%*[^\n]%*[\n]");//��ȥ��һ��
    while(!feof(fp))
    {
        key_record=(Record*)malloc(sizeof(Record));
        key_record->color=0;//��ɫĬ��Ϊ0
        fscanf(fp,"%d%*[^\t]",&temp);//�����¼����
        switch(temp)
        {
        case 0:key_record->recordtype=stock;break;
        case 1:key_record->recordtype=wholesale;break;
        case 2:key_record->recordtype=retail;
        }
        fscanf(fp,"%d/%d %d:%d%*[\t]",&key_record->b_date.month,&key_record->b_date.day,\
               &key_record->b_date.hour,&key_record->b_date.minute);//��������
        if(judgedate(key_record->b_date)==0)
        {
            printf("��ȡ�������ڲ��Ϸ���\n");
            wait_enter(4);
            free(key_record);
            fclose(fp);
            return;
        }
        fscanf(fp,"%[^\t]%*[\t]",tempname);//�������
        key_record->b_part=key_part_list(tempname);
        if(key_record->b_part==NULL)//��������������Ҳ���������ֹ
        {
            free(key_record);
            wait_enter(4);
            fclose(fp);
            return;
        }
        fscanf(fp,"%[^\t]%*[\t]",tempname);//��������ͺ�
        key_record->b_parttype=key_parttype_list(key_record->b_part->name,tempname);
        if(key_record->b_parttype==NULL)//��������������ͺ��Ҳ���������ֹ
        {
            free(key_record);
            wait_enter(4);
            fclose(fp);
            return;
        }
        fscanf(fp,"%lf%*[\t]%d%*[\t]",&key_record->unit_price,&key_record->amount);//���뵥�ۺ�����
        key_record->total_price=key_record->unit_price*key_record->amount;//������ܼ�
        fscanf(fp,"%[^\t]%*[\t]",tempname);//���빩���̻�ͻ�
        switch(key_record->recordtype)
        {
        case stock:
            key_record->b_supply=key_supply_list(tempname);
            if(key_record->b_supply==NULL)//�����������������Ҳ���������ֹ
            {
                free(key_record);
                wait_enter(4);
                fclose(fp);
                return;
            }
            break;
        case wholesale:
            key_record->b_client=key_client_list(tempname);
            if(key_record->b_client==NULL)//�����������������Ҳ���������ֹ
            {
                free(key_record);
                wait_enter(4);
                fclose(fp);
                return;
            }
            break;
        case retail:
            key_record->b_client=key_client_list(tempname);
            if(key_record->b_client==NULL)//�����������������Ҳ���������ֹ
            {
                free(key_record);
                wait_enter(4);
                fclose(fp);
                return;
            }
            break;
        default:;
        }
        key_present=(Present*)malloc(sizeof(Present));//�½���Ʒͷ���
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
            fscanf(fp,"%[^\t]%*[\t]",tempname);//�������
            key_present->part=key_part_list(tempname);
            fscanf(fp,"%[^\t]%*[\t]",tempname);//��������ͺ�
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

void save_record_to_file(char *filename)//�ѵ�ǰ��¼�����ļ�
{
    char tempname[size];//�����ʱ�ַ���
    Record *key_record=recordall->b_recordnext;
    Present *key_present;
    FILE *fp=fopen(filename,"w");
    if(fp==NULL)//�����ж�
    {
        printf("�����ļ�%sʧ�ܣ�\n",filename);
        return;
    }
    fprintf(fp,"����\tʱ��\t\t���\t\t�ͺ�\t\t����\t\t����\t\t������/�ͻ�\t��Ʒ������0������ 1������ 2�����ۣ�\n");//������ͷ
    while(key_record!=NULL)
    {
        fprintf(fp,"%d\t",key_record->recordtype==stock?0:(key_record->recordtype==wholesale?1:2));//��¼����
        timestr(tempname,key_record->b_date,0);
        fprintf(fp,"%s\t",tempname);//ʱ��
        fprintf(fp,"%s%s",key_record->b_part->name,tabs(key_record->b_part->name));//���
        fprintf(fp,"%s%s",key_record->b_parttype->name,tabs(key_record->b_parttype->name));//�ͺ�
        fprintf(fp,"%.2f%s",key_record->unit_price,tabf(key_record->unit_price));//����
        fprintf(fp,"%d%s",key_record->amount,tabi(key_record->amount));//����
        if(key_record->recordtype==stock)//�����̻�ͻ�
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

void save_supply_to_file(char *filename)//�ѵ�ǰ��������Ϣ�����ļ�
{
    Supply *key_supply=datasupply->next;
    FILE *fp=fopen(filename,"w");
    if(fp==NULL)//�����ж�
    {
        printf("�����ļ�%sʧ�ܣ�\n",filename);
        return;
    }
    fprintf(fp,"����������\t��ʼ�۸�����ָ��\n");//������ͷ
    while(key_supply!=NULL)
    {
        fprintf(fp,"%s%s",key_supply->name,tabs(key_supply->name));
        fprintf(fp,"%.2f\n",key_supply->modify);
        key_supply=key_supply->next;
    }
    fclose(fp);
}

void save_client_to_file(char *filename)//�ѵ�ǰ�ͻ���Ϣ�����ļ�
{
    Client *key_client=dataclient->next;
    FILE *fp=fopen(filename,"w");
    if(fp==NULL)//�����ж�
    {
        printf("�����ļ�%sʧ�ܣ�\n",filename);
        return;
    }
    fprintf(fp,"����\t\t�ͻ�\t\t�Ա�\t\t��λ\t\t��ʼ�۸�����ָ��\n");//������ͷ
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

void Client_add()//���ӿͻ�
{
    Client *p=dataclient;
    Client *q;
    Client *check=dataclient->next;
    int type;
    char name[size];
    printf("��������Ҫ���ӵĿͻ�(���˻�����)����:��������10���ֽڣ�\n");
    fflush(stdin);
    while(scanf("%[^\n]",name))
    {
        if(strlen(name)>10)
        {
            printf("����10���ֽڣ����������룡\n");
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
            printf("����:���ݿ����Ѵ��ڸÿͻ���Ϣ!\n");
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
    printf("��ѡ�����Ŀͻ�����:\n");
    printf("1.���� 2.����\n");
    scanf("%d",&type);
    if(type==1||type==2)
    {
        switch(type)
        {
        case 1://���˿ͻ�������
            {
                strcpy(q->name,name);
                q->c_clienttype=individual;
                printf("�����������Ա�:\n");
                printf("1:�� 2:Ů\n");
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
                    printf("����:�����Ա����벻�淶!\n");
                    return;
                }
                printf("���������Ĺ�����λ(��������дnone)\n");
                fflush(stdin);
                while(scanf("%[^\n]",q->unit))
                {
                    if(strlen(q->unit)>10)
                    {
                        printf("����10���ֽڣ����������룡\n");
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
                printf("���ĸ��˿ͻ���Ϣ����ɹ�!\n");
                break;
            }
        case 2://����ͻ�������
            {
                strcpy(q->name,name);
                q->c_clienttype=group;
                q->modify=(double)(rand()%75+75);
                q->next=NULL;
                char charsex[]={"none"};
                strcpy(p->unit,charsex);
                q->gender=nullgender;
                printf("��������ͻ���Ϣ����ɹ�!\n");
                break;
            }
        }
    }
    else printf("���Ŀͻ��������벻�淶!\n");
    wait_enter(4);
    return;
}

void Client_delete()//ɾ���ͻ�
{
    Client *p=dataclient;
    Client *p0=dataclient;
    Client *choose_client[size];
    Record *q=recordall->b_recordnext;
    char supname[size];
    int maxrecord,option_client;
    maxrecord=output_client_data(dataclient,choose_client);
    printf("��ѡ����Ҫɾ���Ŀͻ���������%d������һ����\n",maxrecord+1);
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
                printf("��¼�д��ڸÿͻ���Ϣ,�޷�ɾ��!\n");
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
                printf("�ͻ���Ϣɾ���ɹ�!\n");
                return;
            }
            p0=p;
            p=p->next;
    }
    return;
}

void Supply_add()//���ӹ�����
{
    Supply *p=datasupply;
    Supply *q;
    Supply *check=datasupply;
    char name[size];

    printf("��������Ҫ���ӵĹ���������:��������10���ֽڣ�\n");
    fflush(stdin);
    while(scanf("%[^\n]",name))
    {
        if(strlen(name)>10)
        {
            printf("����10���ֽڣ����������룡\n");
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
            printf("����:���ݿ����Ѵ��ڸÿͻ���Ϣ!\n");
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
    printf("���Ĺ�������Ϣ����ɹ�!\n");
    wait_enter(4);
    return;
}

void Supply_delete()//ɾ��������
{
    Record *q;
    Supply *p=datasupply;
    Supply *p0=datasupply;
    Supply *choose_supply[size];
    char supname[size];
    int maxrecord,option_supply;
    maxrecord=output_supply_data(datasupply,choose_supply);
    printf("��ѡ����Ҫɾ���Ĺ����̣�������%d������һ����\n",maxrecord+1);
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
                printf("��¼�д��ڸù�������Ϣ,�޷�ɾ��!\n");
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
                printf("��������Ϣɾ���ɹ�!\n");
                return;
            }
            p0=p;
            p=p->next;
    }
    return;
}

void add_record_from_file()//���ļ������Ӽ�¼
{
    printf("��������Ҫ¼����ļ���������������data233.txt��\n");
    char filename[size];
    fflush(stdin);//��ջ�����
    while(scanf("%[^\n]",filename)!=1)
    {
        printf("������������ԣ�\n");
        while(getchar()!='\n');
        fflush(stdin);
    }
    fflush(stdin);//��ջ�����
    load_record_from_file(filename);
    printf("¼�������");
    wait_enter(4);
    return;
}

void add_record_from_system()//�ӿ���̨ʵʱó��
{
    Date tempdate;
    Present* newpresent;
    Present *pre[3][5];//�������͵Ķ�ά����
    char datestr[size];//id����� id2������ͺ� id3��������/�ͻ�
    int maxrecord,choose_id,choose_id2,choose_id3,choose_amount,choose_type,choose_present,i,j,randx;
    double finalprice;//������ĵ���
    Part_list* choose_part[size];
    Parttype_list* choose_parttype[size];
    Supply *choose_supply[size];
    Client *choose_client[size];
    printf("������ó��ʱ�䣺�������ʽ���� �� ʱ �֣�\n");
    fflush(stdin);//��ջ�����
    while(scanf("%d%d%d%d",&tempdate.month,&tempdate.day,&tempdate.hour,&tempdate.minute)!=4||judgedate(tempdate)==0)
    {
        printf("������������ԣ�\n");
        fflush(stdin);
    }
    fflush(stdin);//��ջ�����
    system("cls");//����
    output_money();
    timestr(datestr,tempdate,1);
    printf("%s\n",datestr);//ʱ��
    maxrecord=output_part_data(choose_part);//���������ݿ�
    printf("��ѡ����Ҫó�׵������\n");
    choose_id=judge_choice(maxrecord);
    system("cls");//����
    output_money();
    printf("%s\n�����%s\n",datestr,choose_part[choose_id]->data.name);//ʱ������
    maxrecord=output_parttype_data(choose_part[choose_id]->type_list,choose_parttype);//�������ͺ����ݿ�
    printf("��ѡ����Ҫó�׵�����ͺţ�\n");
    choose_id2=judge_choice(maxrecord);
//    if(choose_parttype[choose_id2]->data.store<=0)
//    {
//        printf("��ǰ����������㣬�޷����ۣ�\n");
//        return;
//    }//ȡ����������жϣ��������������������
    printf("��ѡ�����ó�����ͣ�\n\
1.����\n\
2.����\n\
3.����\n");
    choose_type=judge_choice(3);
    switch(choose_type)
    {
    case 1:
        printf("��ѡ�񹩻��̣�\n");
        maxrecord=output_supply_data(datasupply,choose_supply);
        choose_id3=judge_choice(maxrecord);
        finalprice=choose_parttype[choose_id2]->data.stock_price*choose_supply[choose_id3]->modify*choose_parttype[choose_id2]->data.modify;//�۸�����
        finalprice=(double)((long long int)(finalprice*100))/100;//������λС��
        printf("��ǰ�������ṩ�ĵ���Ϊ%.2fԪ����ң�\n",finalprice);
        break;
    case 2:
        printf("��ѡ��ͻ���\n");
        maxrecord=output_client_data(dataclient,choose_client);
        choose_id3=judge_choice(maxrecord);
        finalprice=choose_parttype[choose_id2]->data.wholesale_price*choose_client[choose_id3]->modify*choose_parttype[choose_id2]->data.modify;//���ܴ��ڼ۸���������ʱ���ټ�������ܣ�
        printf("�������ÿͻ��ĵ���Ϊ%.2fԪ����ң�\n",finalprice);
        break;
    default:
        printf("��ѡ��ͻ���\n");
        maxrecord=output_client_data(dataclient,choose_client);
        choose_id3=judge_choice(maxrecord);
        finalprice=choose_parttype[choose_id2]->data.retail_price*choose_client[choose_id3]->modify*choose_parttype[choose_id2]->data.modify;//���ܴ��ڼ۸���������ʱ���ټ�������ܣ�
        printf("���۸��ÿͻ��ĵ���Ϊ%.2fԪ����ң�\n",finalprice);
    }
    if(choose_type==1)
    {
//        int limit=money/finalprice;
//        if(limit<=0)
//       {
//            printf("��ǰ�ʽ��㣬�޷�������\n");
//            return;
//        }//ȡ��������趨
        printf("��ѡ�����������\n");
        choose_amount=judge_choice(maxsize);
            newpresent=(Present*)malloc(sizeof(Present));//�½���Ʒͷ���
            newpresent->amount=0;
            newpresent->part=NULL;
            newpresent->parttype=NULL;
            newpresent->next=NULL;
    }
    else
    {
        printf("��ѡ�����������\n");
        choose_amount=judge_choice(maxsize);//���������
        if(choose_type==2&&choose_amount>=choose_parttype[choose_id2]->data.keynum)
        {
            printf("Ϊ�˻����ÿͻ���������·���ѡ��һ����Ϊ��Ʒ��\n");
            newpresent=(Present*)malloc(sizeof(Present));//�½���Ʒͷ���
            newpresent->amount=0;
            newpresent->part=NULL;
            newpresent->parttype=NULL;
            newpresent->next=NULL;
            //���ܴ����
            for(i=0;i<3;i++)
                for(j=0;j<5;j++)
                pre[i][j]=NULL;
            if(choose_parttype[choose_id2]->data.store>=choose_amount*10)
            {
                srand((unsigned)time(0));
                randx=rand()%4+2;//2-5����Ʒ
            }
            else
            {
                randx=1;//1����Ʒ
            }
            add_record_present(pre,randx);
            for(i=0;i<3;i++)
            {
                if(pre[i][0]!=NULL)
                {
                    printf("����%d.\n",i+1);
                    for(j=0;j<5;j++)
                    {
                        if(pre[i][j]==NULL)
                        {
                            break;
                        }
                        else
                        {
                            printf("%d��%s�ͺ�%s\n",pre[i][j]->amount,pre[i][j]->part->name,pre[i][j]->parttype->name);
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
            printf("��Ʒ��ӳɹ���\n\n");
        }
        else
        {
            newpresent=(Present*)malloc(sizeof(Present));//�½���Ʒͷ���
            newpresent->amount=0;
            newpresent->part=NULL;
            newpresent->parttype=NULL;
            newpresent->next=NULL;
        }
    }
    double finaltotal=finalprice*choose_amount;
    printf("��Ʒ�ܼ�Ϊ%.2f\n",finaltotal);
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
    newrecord->color=0;//��ɫĬ��Ϊ0
    solve_record(newrecord,1);
    sorttime(newrecord);//��ʱ��˳������½��
    wait_enter(1);
    return;
}

void add_record_present(Present *pre_way[3][5],int present_amount)//�������ַ��������ڶ�άָ�������У�ÿ�ַ��������5�����
{
    int part_num=0,parttype_num=0;//�������������ͺŵ�����
    int i,j,k=0;
    Part_list *p;//��ʱ�������������ݿ��е����
    Parttype_list *pt;//��ʱ�������������ݿ��е�����ͺ�
    Present pre[size];//����һ���������飬��������ݿ����������
    for(p=datapart->next;p!=NULL;p=p->next)
    {
        for(pt=p->type_list->next;pt!=NULL;pt=pt->next)
        {
            pre[parttype_num].amount=rand()%5+1;//��ʼ��Ϊ1����֮����ܻ��޸�
            pre[parttype_num].part=&(p->data);
            pre[parttype_num].parttype=&(pt->data);
            pre[parttype_num].next=NULL;
            parttype_num++;
        }
        part_num++;
    }
    randpre(parttype_num,pre);//��ָ����������������
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
                if(i>0)//���i>0����Խ���������
                {
                    pre_way[j][i-1]->next=pre_way[j][i];
                }
            }
            k++;
        }
    }

}

void del_one_record(Record *key)//ɾ��һ����¼
{
    Record *p,*p0=recordall;
    Present* pre0=key->b_present,*pre;
    for(p=recordall->b_recordnext;p!=key;p=p->b_recordnext)
        p0=p;
    p0->b_recordnext=p->b_recordnext;
    solve_record(p,0);//��ԭ������¼
    for(pre=key->b_present->next;pre!=NULL;pre=pre->next)
    {
        free(pre0);
        pre0=pre;
    }
    free(pre);
    free(p);
}

void change_time(Record* p)//�޸�ʱ��
{
    char tempstr[size],tempstr2[size];//tempstr�洢�޸�ǰ��ʱ���ַ�����tempstr2�洢�޸ĺ��ʱ���ַ���
    Date tempdate;//��ʱ�������洢�޸ĺ��ʱ��
    timestr(tempstr,p->b_date,0);
    printf("��ǰʱ��Ϊ%s���������޸ĺ��ʱ�䣺\n",tempstr);
    fflush(stdin);
    while(scanf("%d%d%d%d",&tempdate.month,&tempdate.day,\
        &tempdate.hour,&tempdate.minute)!=4||\
        judgedate(tempdate)==0)//������洢����ʱ������
    {
        printf("������������ԣ�\n");
        while(getchar()!='\n');
        fflush(stdin);
    }
    fflush(stdin);
    timestr(tempstr,p->b_date,1);
    timestr(tempstr2,tempdate,1);
    p->b_date=tempdate;
    printf("������¼��ʱ����\n\
%s\n�޸���\n%s\n",tempstr,tempstr2);
    dropoff(p);//ժ�¸ýڵ�
    sorttime(p);//����ʱ��˳��Ż�����
}

void change_recordtype(Record* p)//�޸Ľ�������
{
    Present *pre0,*pre;
    solve_record(p,0);//����
    printf("��ǰ����Ϊ��%s���������޸ĺ�����ͱ��\n",\
           p->recordtype==stock?"����":(p->recordtype==wholesale?"����":"����"));
    printf("1.����\t2.����\t3.����\t4.��һ��\n");
    int tempid=judge_choice(4);
    if((tempid==1&&p->recordtype==stock)||\
       (tempid==2&&p->recordtype==wholesale)||
       (tempid==3&&p->recordtype==retail))
    {
        printf("�޸�ǰ��������ͬ��\n");
        wait_enter(1);
        return;
    }
    switch(tempid)
    {
    case 1:
        change_supply(p);
        if(p->recordtype==wholesale&&p->b_present->next!=NULL)//���ԭ������������Ҫɾ����Ʒ��δ��ɣ�
        {
            printf("�����ͱ任��ԭ�ȵ���Ʒɾ����\n");
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
        if(p->recordtype==wholesale&&p->b_present->next!=NULL)//���ԭ������������Ҫɾ����Ʒ��δ��ɣ�
        {
            printf("�����ͱ任��ԭ�ȵ���Ʒɾ����\n");
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
    solve_record(p,1);//����
}

void change_part(Record *p)//�޸����
{
    int maxrecord,choose_id;
    Part_list* choose_part[size];
    maxrecord=output_part_data(choose_part);//���������ݿ�
    printf("��ѡ����Ҫ�޸ĵ������\n");
    choose_id=judge_choice(maxrecord);
    p->b_part=&choose_part[choose_id]->data;
    change_parttype(p);
}

void change_parttype(Record *p)//�޸�����ͺ�
{
    int maxrecord,choose_id;
    Parttype_list* temp;
    Parttype_list* choose_parttype[size];
    temp=key_part_parttype(p->b_part->name);
    maxrecord=output_parttype_data(temp,choose_parttype);//�������ͺ����ݿ�
    printf("��ѡ����Ҫ�޸ĵ�����ͺţ�\n");
    choose_id=judge_choice(maxrecord);
    p->b_parttype=&choose_parttype[choose_id]->data;
}

void change_unitprice(Record *p)//�޸ĵ���
{
    solve_record(p,0);
    double tempprice;
    printf("��ǰ����Ϊ%.2fԪ���������޸ĺ�ĵ���\n",p->unit_price);
    setbuf(stdin, NULL);
    while(scanf("%lf",&tempprice)!=1||tempprice<=0)
    {
        printf("������������ԣ�\n");
        while(getchar()!='\n');
    }
    setbuf(stdin, NULL);
    printf("������¼�ĵ�����%.2fԪ�޸���%.2fԪ��\n",p->unit_price,tempprice);
    p->unit_price=tempprice;
    p->total_price=p->amount*p->unit_price;
    printf("�ܼ۱�Ϊ%.2fԪ��\n",p->total_price);
    solve_record(p,1);
}

void change_amount(Record *p)//�޸�����
{
    solve_record(p,0);
    int temp;
    printf("��ǰ����Ϊ%d���������޸ĺ������\n",p->amount);
    setbuf(stdin, NULL);
    while(scanf("%d",&temp)!=1||temp<=0)
    {
        printf("������������ԣ�\n");
        while(getchar()!='\n');
    }
    setbuf(stdin, NULL);
    printf("������¼��������%d�޸���%d��\n",p->amount,temp);
    p->amount=temp;
    p->total_price=temp*p->unit_price;
    printf("�ܼ۱�Ϊ%.2fԪ��\n",p->total_price);
    solve_record(p,1);
}

void change_supply(Record *p)//�޸Ĺ�����
{
    int maxrecord,chooseid;
    Supply *choose_key[size];
    printf("��ѡ���޸ĺ�Ĺ����̣�\n");
    maxrecord=output_supply_data(datasupply,choose_key);
    chooseid=judge_choice(maxrecord);
    p->b_supply=choose_key[chooseid];
}

void change_client(Record *p)//�޸Ŀͻ�
{
    int maxrecord,chooseid;
    Client *choose_key[size];
    printf("��ѡ���޸ĺ�Ŀͻ���\n");
    maxrecord=output_client_data(dataclient,choose_key);
    chooseid=judge_choice(maxrecord);
    p->b_client=choose_key[chooseid];
}

void change_present(Record *p)//�޸���Ʒ
{
    Present *pre0,*pre;
    int maxrecord,choose_id,choose_id2,choose_id3,i,num,tempid,tempid2;
    Part_list* choose_part[size];
    Parttype_list* choose_parttype[size];
    Present* choose_present[size];
    while(1)
    {
        system("cls");//����
        output_money();
        output_one(p,1,1);
        i=0;
        choose_present[0]=p->b_present;
        for(pre0=p->b_present->next;pre0!=NULL;pre0=pre0->next)
        {
            choose_present[++i]=pre0;
        }
        pre0=p->b_present;
        printf("��ѡ����еĲ�����\n\
1.������Ʒ\t2.ɾ����Ʒ\t3.�޸���Ʒ\t4.��һ��\n");
        tempid=judge_choice(4);
        switch(tempid)
        {
        case 1:
            pre=(Present*)malloc(sizeof(Present));
            pre->next=NULL;
            maxrecord=output_part_data(choose_part);//���������ݿ�
            printf("��ѡ�������\n");
            choose_id=judge_choice(maxrecord);
            pre->part=&choose_part[choose_id]->data;
            maxrecord=output_parttype_data(choose_part[choose_id]->type_list,choose_parttype);//�������ͺ����ݿ�
            printf("��ѡ������ͺţ�\n");
            choose_id2=judge_choice(maxrecord);
            pre->parttype=&choose_parttype[choose_id2]->data;
            printf("��������Ʒ������\n");
            num=judge_choice(maxsize);
            pre->amount=num;
            choose_present[i]->next=pre;
            wait_enter(1);
            break;
        case 2:
            if(pre0->next==NULL)
            {
                printf("��ǰ����Ʒ���޷�ɾ����");
                wait_enter(0);
                break;
            }
            printf("��������Ҫɾ������Ʒ��ţ�\n");
            choose_id=judge_choice(i);
            choose_present[choose_id-1]->next=choose_present[choose_id]->next;
            free(choose_present[choose_id]);
            wait_enter(1);
            break;
        case 3:
            if(pre0->next==NULL)
            {
                printf("��ǰ����Ʒ���޷��޸ģ�");
                wait_enter(0);
                break;
            }
            printf("��ѡ����Ҫ�޸ĵ���Ʒ��ţ�\n");
            choose_id=judge_choice(i);
            printf("��ѡ����Ҫ�޸ĵ���Ŀ��\n");
            printf("1.���\t2.����ͺ�\t3.����\t4.��һ��\n");
            tempid2=judge_choice(4);
            switch(tempid2)
            {
            case 1:
                maxrecord=output_part_data(choose_part);//���������ݿ�
                printf("��ѡ�������\n");
                choose_id2=judge_choice(maxrecord);
                choose_present[choose_id]->part=&choose_part[choose_id2]->data;
                maxrecord=output_parttype_data(choose_part[choose_id2]->type_list,choose_parttype);//�������ͺ����ݿ�
                printf("��ѡ������ͺţ�\n");
                choose_id3=judge_choice(maxrecord);
                choose_present[choose_id]->parttype=&choose_parttype[choose_id3]->data;
                wait_enter(1);
                break;
            case 2:
                maxrecord=output_parttype_data(key_part_parttype(choose_present[choose_id]->part->name),choose_parttype);//�������ͺ����ݿ�
                printf("��ѡ������ͺţ�\n");
                choose_id3=judge_choice(maxrecord);
                choose_present[choose_id]->parttype=&choose_parttype[choose_id3]->data;
                wait_enter(1);
                break;
            case 3:
                printf("������������\n");
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

void store_form(Part_list* p)//���ɿ�汨��
{
    Part_list *p0=p;
    Parttype_list *p1;
    printf("�����汨�����£�\n");
    printf("����\t\t�ͺ�\t\t������\t\t������\n");
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
    printf("��汨���������!\n");
    return;
}

void present_form(Record *p)//ͳ��������Ʒ���
{
    Record *p0=p;
    Present *p1;
    printf("��Ʒ���ͳ������:\n");
    printf("����ʱ��\t��Ʒ����\t��Ʒ�ͺ�\t����\n");
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

void searchall()//�ܼ�¼���ݲ���
{
    Record *choose_record[size];
    int maxrecord,choose_id;
    while(1)
    {
        system("cls");//����
        output_money();
        maxrecord=output_record(choose_record);
        printf("��ѡ����Ҫ�����ѯ�ļ�¼���(����%d�ص���һ��)��\n",maxrecord+1);
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

void searchpart()//�����Ӧ��¼����
{
    int flag1=0,flag2=0,count1=0,count2=0,count3=0,count4=0,j,i,m;
    Record *save1[size],*save2[size],*save3[size],*save4[size];
    Record *p;
    Part_list *p_list[size];

    int partid,maxpart;
    system("cls");
    output_money();
    printf("����б�:\n");
    maxpart=output_part_data(p_list);
    printf("����Ҫ��ѯ�������ţ�����%d������һ��\n",maxpart+1);
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
        printf("������¼��\n");
        outrec_mod0(flag1,save1,count1,0);
        printf("���ۼ�¼��\n");
        if(flag2==0)
            printf("��¼Ϊ�գ�\n");
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
            printf("���س�������\n");
            while(getchar()!='\n');
            return;
        }
        printf("\n\n�����¼��Ų�ѯ������Ϣ������%d������ͺ�Ϊ���ݽ��в�ѯ������%d������һ��\n",count1+count2+1,count1+count2+2);
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
        printf("����������ͺ�����Բ�ѯ��Ӧ�ͺŵļ�¼������\"%d\"����\n",typemax+1);
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
            printf("������¼��\n");
            outrec_mod0(flag1,save3,count3,0);
            printf("\n\n");
            printf("���ۼ�¼��\n");
            if(flag2==0)
                printf("��¼Ϊ�գ�\n");
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
                printf("����������ͺ�����Բ�ѯ��Ӧ�ͺŵļ�¼������\"%d\"����\n",typemax+1);
                partid=judge_choice(typemax+1);
                continue;
            }
            printf("\n\n�����¼��Ų�ѯ������Ϣ������%d������һ��\n",count3+count4+1);
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
            printf("������¼��\n");
            outrec_mod0(flag1,save3,count3,0);
            printf("\n\n");
            printf("���ۼ�¼��\n");
            if(flag2==0)
                printf("��¼Ϊ�գ�\n");
            else
            {
                output_chart_head_1(1);
                for(i=0;i<count4;i++)
                {
                    output_one(save4[i],0,count3+i+1);
                    printf("\n");
                }
            }
            printf("\n\n�����¼��Ų�ѯ������Ϣ������%d������һ��\n",count3+count4+1);
            }
            system("cls");
            output_money();
            output_parttype_data(kptype,ptype_list);
            printf("����������ͺ�����Բ�ѯ��Ӧ�ͺŵļ�¼������%d����\n",typemax+1);
            partid=judge_choice(typemax+1);
        }
        break;
        }
        output_one(save1[m-1],1,1);
        wait_enter();
    }
    system("cls");
    output_money();
    printf("����б�:\n");
    output_part_data(p_list);
    printf("����Ҫ��ѯ�������ţ�����%d������һ��\n",maxpart+1);
    partid=judge_choice(maxpart+1);
    p=recordall->b_recordnext;
    }
}

void searchclient()//�ͻ���Ӧ��¼����
{
    int flag=0,count=0,clmax;
    Record *p,*save[size];
    Client *c_list[size];
    system("cls");
    output_money();
    printf("�ͻ��б�\n");
    clmax=output_client_data(dataclient,c_list);
    p=recordall->b_recordnext;

    printf("������Ҫ��ѯ�Ŀͻ����,����%d������һ��\n",clmax+1);
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
            printf("����ؼ�¼\n");
            printf("���س�������\n");
            getchar();
            return;
        }
        system("cls");
        outputmod1(save,count,1);
        system("cls");
        output_money();
        printf("�ͻ��б�\n");
        output_client_data(dataclient,c_list);
        p=recordall->b_recordnext;
        printf("������Ҫ��ѯ�Ŀͻ����,����%d�Է�����һ��\n",clmax+1);
        clid=judge_choice(clmax+1);
    }
    return;
}

void searchsupply()//�����̶�Ӧ��¼����
{
    int flag=0,count=0,supmax,spid;
    Record *save[size];
    Record *p;
    Supply *sup_list[size];
    system("cls");
    output_money();
    printf("�������б�\n");
    supmax=output_supply_data(datasupply,sup_list);
    p=recordall->b_recordnext;
    printf("������Ҫ��ѯ�Ĺ����̱��,����%d������һ��\n",supmax+1);
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
            printf("����ؼ�¼\n");
            printf("���س�������\n");
            getchar();
            return;
        }
        system("cls");
        outputmod1(save,count,0);
        system("cls");
        output_money();
        printf("�������б�\n");
        output_supply_data(datasupply,sup_list);
        p=recordall->b_recordnext;
        printf("������Ҫ��ѯ�Ĺ����̱��,����%d������һ��\n",supmax+1);
        spid=judge_choice(supmax+1);
    }
    return;
}

void searchperiod()//ʱ����ڼ�¼����
{
    int flag=0,count=0;
    double profit=0;
    Record *p,*save[size];
    p=recordall->b_recordnext;
    Date per1,per2,tempper;
    system("cls");
    output_money();
    fflush(stdin);//��ջ�����
    printf("��������ʼʱ�䣺����ʽ���� �� ʱ �֣�\n");
    while(scanf("%d%d%d%d",&per1.month,&per1.day,&per1.hour,&per1.minute)!=4||judgedate(per1)==0)
    {
        printf("������������ԣ�\n");
        fflush(stdin);//��ջ�����
    }
    fflush(stdin);//��ջ�����
    printf("��������ֹʱ�䣺����ʽ���� �� ʱ �֣�\n");
    while(scanf("%d%d%d%d",&per2.month,&per2.day,&per2.hour,&per2.minute)!=4||judgedate(per2)==0)
    {
        printf("������������ԣ�\n");
        fflush(stdin);//��ջ�����
    }
    fflush(stdin);//��ջ�����
    if(timecmp(per1,per2)>0)
    {
        tempper=per1;
        per1=per2;
        per2=tempper;
        printf("���������෴���������������෴�����ڽ��в�ѯ\n");
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
        printf("����ؼ�¼\n���س�������\n");
        while(getchar()!='\n');
        return;
    }
    printf("�ʽ��ܶ�仯��%lf\n\n",profit);
    outputmod1(save,count,2);
    return;
}

void fuzzysearch()//ģ����ѯ
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
    printf("������Ҫ���ҵĹؼ���,����4�������/����ͺ�/�ͻ�/�����̣�\n");
    gets(word);
    totlen=strlen(word);
    while(i<totlen&&cnt<4)
    {
        j=0;
        while(word[i]==' '&&i<totlen)
            i++;
        if(i==totlen&&cnt==0)
        {
         printf("������������Ϊ�գ�\n");
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
        printf("����ؼ�¼\n���س�������\n");
        while(getchar()!='\n');
        return;
    }
    system("cls");
    outputmod1(save,count,0);
    return;
}

void unit_price_change()//���۵Ķ�̬�仯
{
    Part_list* p;
    Parttype_list* pt;
    Record* pr;
    double average_amount;
    double target_amount;
    double temp_modify;//��ʱ�仯����
    error_judge_2();//�����ж�
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

void suggest_in()//��������
{
    error_judge_2();//�����ж�
    Part *temp_part[size];// *min_part_price=&(datapart->next->data);
    Part_list *p_part;
    Parttype *temp_type[size], *min_parttype_price=&(datapart->next->type_list->next->data);//�����ʱ������ͺ�ָ��
    Parttype_list *p_parttype;
    Record *p;
    double benefit[size];
    int count=0,i=0,maxbenefit;
    /*�ʽ���;���*/
    if(money<1000)
    {
        printf("��ǰ�ʽ���ͣ����鲹���ʽ���ٽ���ó�ף�\n");
    }

    /*�������ӯ���ߵ���Ʒ*/
    for(p=recordall->b_recordnext;p!=NULL;p=p->b_recordnext)
    {
        for(i=0;i<count;i++)
        {
            if(temp_part[i]==p->b_part&&temp_type[i]==p->b_parttype)//���������Ѵ��ַ�ظ�����ֹͣѭ��
                break;
        }
        if(i==count)//����������͵��������ѵ�ַ������ʱ����
        {
            count++;
            temp_part[i]=p->b_part;
            temp_type[i]=p->b_parttype;
            benefit[i]=0;//��ʼ��
        }
        if(p->recordtype==stock)
        {
            benefit[i]-=p->total_price;//������-
        }
        else
        {
            benefit[i]+=p->total_price;//�۳���+
        }
    }
    for(i=0;i<count;i++)
    {
        if(i==0)maxbenefit=0;
        else maxbenefit=(benefit[maxbenefit]<benefit[i])?i:maxbenefit;
    }
    printf("%s�����%s�ͺ�ȫ��%s��Ϊ%.2f���������ӽ���\n",\
           temp_part[maxbenefit]->name,temp_type[maxbenefit]->name,\
           benefit[maxbenefit]>0?"�������":"�������",fabs(benefit[maxbenefit]));

    /*�ڻ�����*/
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
        printf("%s�����%s�ͺ������ڵͼۣ��������ӽ���\n",p_part->data.name,min_parttype_price->name);
    }
    wait_enter(4);
}

void price_predict(Part* key_part, Parttype* key_parttype)//�۸�Ԥ�⣨���Իع鷽�̣�
{
    system("cls");
    Record *p=recordall->b_recordnext;
    int p_month,i,j;
    double month12[12]={1,2,3,4,5,6,7,8,9,10,11,12};//ʮ������
    double a,b;//���Իع鷽�̵Ĳ���a,b
    double key_unit[3][12];//ͳ��ÿ���µ�ƽ�����ۣ�����/����/����
    double all_unit[3][2];//ͳ��ÿ���µ��ܵ��ۣ����ڼ���ƽ��ֵ������/����
    for(i=0;i<3;i++)//��ʼ��
    {
        for(j=0;j<12;j++)
        {
            key_unit[i][j]=0;//��ʼ����ȫ��Ϊ0
        }
    }
    for(i=0;i<3;i++)//��ʼ��
    {
        for(j=0;j<2;j++)
        {
            all_unit[i][j]=0;//��ʼ����ȫ��Ϊ0
        }
    }
    for(p_month=1;;p=p->b_recordnext)
    {
        if(p==NULL||p->b_date.month!=p_month)//�����������һ���£����߼�¼�������
        {
            for(j=0;j<3;j++)
            {
                if(all_unit[j][1]!=0)//������Ϊ0
                    key_unit[j][p_month-1]=all_unit[j][0]/all_unit[j][1];//����ƽ������
                //printf("%d��ƽ������%.2f\n",p_month,key_unit[j][p_month-1]);
            }
            for(i=0;i<3;i++)
            {
                for(j=0;j<2;j++)
                {
                    all_unit[i][j]=0;//��ʼ����ȫ��Ϊ0
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
                printf("%d��ƽ��%s���ۣ�%.2f\n",j+1,\
                       (i==0)?"����":((i==1)?"����":"����"),key_unit[i][j]);
            }
        }
        if(b*13+a!=0)
            printf("\tԤ������1�¸���Ʒ��%s����Ϊ%.2f\n\n",(i==0)?"����":((i==1)?"����":"����"),b*13+a);
    }
}


void history_file()//�����¼��ʷ��Ϣ
{
    int i=0;
    char word1[size]="save\\history",word2[size];
    while(1)
    {
        i++;
        strcpy(word1,"save\\history");
        itoa(i,word2,10);//������ת�����ַ���
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

void del_all()//ɾ�����м�¼
{
    Record *p=recordall->b_recordnext;
    while(p!=NULL)
    {
        del_one_record(p);
        p=recordall->b_recordnext;
    }
}




