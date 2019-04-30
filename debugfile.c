#include"debugfile.h"
void putchart()
{
    printf("编号\t时间\t\t配件\t\t配件型号\t数量\t\t总价\t\t供货商\t\t赠品\n");
            printf("%d\t%s%s%s%s%s%s%d%s%.2f%s%s%s%s",\
/*编号*/        1,\
/*时间*/        "12.12  08:15",\
                tabs("12.12 08:15"),\
/*配件*/        "Graphics card",\
                tabs("Graphics card"),\
/*型号*/        "Quadro GT",\
                tabs("Quadro GT"),\
/*数量*/        555,\
                tabi(555),\
/*总价*/        6660.00,\
                tabf(6660.00),\
/*供货商*/      "Alpha",\
                tabs("Alpha"),
/*赠品*/        "有\n");
}
