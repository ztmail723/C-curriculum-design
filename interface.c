#include"smallfunction.h"
#include"mainfunction.h"
#include"interface.h"
void main_title()                   //���˵�
{
    while(1)
    {
    system("cls");//����
    output_money();
    printf("��ӭʹ�ø��˹�˾������������/����ϵͳ��\n");
    printf("1.��ѯ��¼\n\
2.���ļ�¼\n\
3.ͳ������\n\
4.���ܷ���\n\
5.�߼�����\n\
6.���浱ǰ��¼״̬\n\
7.�˳�ϵͳ\n");
    error_judge();//�����ж�
    int option_choice=judge_choice(7);
    switch(option_choice)
    {
    case 1:
        if(recordall->b_recordnext==NULL)
        {
            printf("��ǰ��¼Ϊ�գ��޷���ѯ��");
            wait_enter(0);
            break;
        }
        searchfunc();
        break;
    case 2:
        change_record();//���ļ�¼
        break;
    case 3:
        if(recordall->b_recordnext==NULL)
        {
            printf("��ǰ��¼Ϊ�գ��޷�ͳ�ƣ�");
            wait_enter(0);
            break;
        }
        count_data();//ͳ������
        break;
    case 4:
        if(recordall->b_recordnext==NULL)
        {
            printf("��ǰ��¼Ϊ�գ��޷�������");
            wait_enter(0);
            break;
        }
        smart_analyse();//���ܷ���
        break;
    case 5:
        high_change();
        break;
    case 6:
        history_file();
        save_record_to_file("save\\savedata.txt");
        printf("�����ļ��ɹ���\n������¼�Ѵ�����ʷ�ļ��У�\n");
        wait_enter(4);
        break;
    default:
        //history_file();
        //save_record_to_file("save\\savedata.txt");
        //printf("�����ļ��ɹ�����������˳���\n");
        //wait_enter();
        return;
    }
    }
}

void searchfunc()                   //1.��ѯ��¼
{
    int s_choice;
    while(1)
    {
    system("cls");
    output_money();
    printf("��¼��ѯ\n");
    printf("1.��ѯ���м�¼\n2.��������������ͺŲ�ѯ\n3.���ݿͻ����Ʋ�ѯ\n4.���ݹ��������Ʋ�ѯ\n5.���ݼ�¼ʱ���ѯ\n6.ģ����ѯ\n7.������һ��\n");
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

void change_record()                //2.���ļ�¼
{
    while(1)
    {
        system("cls");//����
        output_money();
        printf("1.���Ӽ�¼\n\
2.ɾ����¼\n\
3.�޸ļ�¼\n\
4.��һ��\n");
        int option_choice=judge_choice(4);
        switch(option_choice)
        {
        case 1:
            add_record();
            break;
        case 2:
            if(recordall->b_recordnext==NULL)
            {
                printf("��ǰ��¼Ϊ�գ��޷�ɾ����");
                wait_enter(0);
                break;
            }
            del_record();
            break;
        case 3:
            if(recordall->b_recordnext==NULL)
            {
                printf("��ǰ��¼Ϊ�գ��޷��޸ģ�");
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

void add_record()                   //2.1.���Ӽ�¼
{
    while(1)
    {
        system("cls");//����
        output_money();
        printf("1.���ļ�������������Ϣ\n\
2.��ϵͳ�н���ʵʱó��\n\
3.��һ��\n");
        int option_choice=judge_choice(3);
        switch(option_choice)
        {
        case 1:
            add_record_from_file();
            break;
        case 2:
            unit_price_change();//����ǰ���۸������̬�仯
            add_record_from_system();
            break;
        case 3:
            return;
        }
    }
}

void trans_record()                 //2.2.�޸ļ�¼
{
    Record *choose_record[size];
    int maxrecord,choose_id;
    while(1)
    {
        system("cls");//����
        output_money();
        maxrecord=output_record(choose_record);
        printf("��ѡ����Ҫ�޸ĵļ�¼���(����%d�ص���һ��)��\n",maxrecord+1);
        choose_id=judge_choice(maxrecord+1);
        if(choose_id==maxrecord+1)
            return;
        else
            trans_one_record(choose_record[choose_id]);
    }
}

void trans_one_record(Record *p)    //2.2.�޸ļ�¼��Ŀ
{
    int tempid;
    while(1)
    {
        system("cls");//����
        output_money();
        output_one(p,1,1);
        printf("��ѡ���޸ĵ���Ŀ��\n\
1.ʱ��\t\t2.��������\t3.���\n\
4.����ͺ�\t5.����\t\t6.����\n\
7.%s\t8.��Ʒ\t\t9.��һ��\n",p->recordtype==stock?"������":"�ͻ�\t");
        tempid=judge_choice(9);
        switch(tempid)
        {
        case 1://ʱ��
            change_time(p);
            break;
        case 2://��������
            change_recordtype(p);
            break;
        case 3://��������������ͺ�������⣬���������ߣ�
            solve_record(p,0);//����
            change_part(p);
            solve_record(p,1);//����
            break;
        case 4://����ͺ�
            solve_record(p,0);//����
            change_parttype(p);
            solve_record(p,1);//����
            break;
        case 5://����
            change_unitprice(p);
            break;
        case 6://����
            change_amount(p);
            break;
        case 7://������/�ͻ�
            if(p->recordtype==stock)
                change_supply(p);
            else
                change_client(p);
            break;
        case 8://��Ʒ
            if(p->recordtype!=wholesale)
            {
                printf("��¼���Ͳ����������޷��޸���Ʒ��\n");
                break;
            }
            solve_record(p,0);//����
            change_present(p);
            solve_record(p,1);//����
            break;
        default:
            return;
        }
        wait_enter(1);
    }
}

void del_record()                   //2.3.ɾ����¼
{
    Record *choose_record[size];
    int tempid;
    int maxrecord=output_record(choose_record);
    printf("��ѡ����Ҫɾ���ļ�¼��ţ�����%d������һ������\n",maxrecord+1);
    int choose_id=judge_choice(maxrecord+1);
    if(choose_id==maxrecord+1)
    {
        return;
    }
    output_one(choose_record[choose_id],1,choose_id);
    printf("ȷ��Ҫɾ��������¼�𣿣�1.�� 2.��\n");
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

void count_data()                   //3.ͳ������
{
    while(1)
    {
        system("cls");//����
        output_money();
        printf("1.ͳ��Ӫҵ����ӯ����\n\
2.ͳ����Ʒ���\n\
3.���ɿ�汨��\n\
4.��һ��\n");
        int option_choice=judge_choice(4);
        switch(option_choice)
        {
        case 1:
            if(recordall->b_recordnext==NULL)
            {
                printf("��ǰ��¼Ϊ�գ��޷�ͳ�ƣ�");
                wait_enter(0);
                break;
            }
            printf("Ӫҵ�%.2f\nӯ���%.2f\n",total_sales(recordall),total_profit(recordall));
            break;
        case 2:
            if(recordall->b_recordnext==NULL)
            {
                printf("��ǰ��¼Ϊ�գ��޷�ͳ�ƣ�");
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

void smart_analyse()                //4.���ܷ���
{
    while(1)
    {
        system("cls");//����
        output_money();
        printf("1.�۸�Ԥ��\n\
2.���ܽ�������\n\
3.��һ��\n");
        int option_choice=judge_choice(3);
        switch(option_choice)
        {
        case 1:
            price_predict_choose();//�۸����
            break;
        case 2:
            suggest_in();
            break;
        default:
            return;
        }
    }
}

void price_predict_choose()         //4.1.�۸�Ԥ��
{
    Part_list* choose_part[size];
    Parttype_list* choose_parttype[size];
    int maxrecord,choose_id,choose_id2;
    error_judge_2();//�����ж�
    while(1)
    {
        system("cls");
        printf("��ϵͳ����Ͻ���12���µ����ݣ�Ԥ�������1�¸���Ʒ�ļ۸�\n");
        maxrecord=output_part_data(choose_part);//���������ݿ�
        printf("��ѡ����ҪԤ��۸�����������%d������һ������\n",maxrecord+1);
        choose_id=judge_choice(maxrecord+1);
        if(choose_id==maxrecord+1)
            return;
        maxrecord=output_parttype_data(choose_part[choose_id]->type_list,choose_parttype);//�������ͺ����ݿ�
        printf("��ѡ����ҪԤ��۸������ͺţ�����%d������һ������\n",maxrecord+1);
        choose_id2=judge_choice(maxrecord+1);
        if(choose_id2==maxrecord+1)
            break;
        price_predict(&(choose_part[choose_id]->data),&(choose_parttype[choose_id2]->data));
        wait_enter(4);
    }
}

void high_change()                  //5.�߼�����
{
    int option_choice;
    while(1)
    {
        system("cls");//����
        output_money();
        printf("1.��������Ϣ����\n\
2.�ͻ���Ϣ����\n\
3.��¼�������\n\
4.��¼�����滻\n\
5.��һ��\n");
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

void high_change_supply()           //5.1.��������Ϣ����
{
    int option_choice;
    while(1)
    {
        system("cls");//����
        output_money();
        printf("1.�����µĹ�������Ϣ\n\
2.ɾ����������Ϣ\n\
3.���浱ǰ�Ĺ�����״̬\n\
4.��һ��\n");
        option_choice=judge_choice(4);
        switch(option_choice)
        {
        case 1:
            Supply_add();
            break;
        case 2:
            if(datasupply->next==NULL||datasupply->next->name==NULL)
            {
                printf("�޷�ɾ����\n������Ҫ����һ����������Ϣ��\n");
                break;
            }
            Supply_delete();
            break;
        case 3:
            save_supply_to_file("data\\supply.txt");
            printf("�����ɹ���");
            wait_enter(4);
        default:
            return;
        }
    }
}

void high_change_client()           //5.2.�ͻ���Ϣ����
{
    int option_choice;
    while(1)
    {
        system("cls");//����
        output_money();
        printf("1.�����µĿͻ���Ϣ\n\
2.ɾ���ͻ���Ϣ\n\
3.���浱ǰ�Ŀͻ�״̬\n\
4.��һ��\n");
        option_choice=judge_choice(4);
        switch(option_choice)
        {
        case 1:
            Client_add();
            break;
        case 2:
            if(dataclient->next==NULL||dataclient->next->name==NULL)
            {
                printf("�޷�ɾ����\n������Ҫ����һ���ͻ���Ϣ��\n");
                break;
            }
            Client_delete();
            break;
        case 3:
            save_client_to_file("data\\client.txt");
            printf("�����ɹ���");
            wait_enter(4);
        default:
            return;
        }
    }
}

void high_change_del()              //5.3.��ռ�¼
{
    int option_choice;
    printf("�����ܽ���ռ�¼���������ݣ�ȷ��ʹ����(1.�� 2.��)\n");
    option_choice=judge_choice(2);
    switch(option_choice)
    {
    case 1:
        del_all();
        printf("��¼����գ�\n");
        wait_enter(4);
        break;
    default:
        return;
    }
}

void high_change_replace()          //5.4.�滻��¼
{
    printf("�����ܽ��滻��¼���������ݣ���������Ҫ�滻�ļ�¼�ļ���\n");
    char filename[size];
    fflush(stdin);//��ջ�����
    while(scanf("%[^\n]",filename)!=1)
    {
        printf("������������ԣ�\n");
        while(getchar()!='\n');
        fflush(stdin);
    }
    fflush(stdin);//��ջ�����
    del_all();
    load_record_from_file(filename);
    printf("��¼���滻��\n");
    wait_enter(4);
}
