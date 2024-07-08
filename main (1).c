#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#define staffIDLen 9       //工号长度为8位 （不包括'\0'）
#define otherLen 65      //表示长度不固定类型最大值为64位（不包括'\0'）
#define phoneNumLen 12  //表示11位电话号码 (不包括'\0'）
#define passwordLen 9 //密码长度为8位 （不包括'\0'）
//管理员结构体
typedef struct Administrator{
    char staffID[staffIDLen];   //工号
    char password[passwordLen]; //密码
    char staffName[otherLen];   //姓名2
    char phoneNumber[phoneNumLen];// 绑定号码
    struct Administrator* next; //指向下一个节点
}Adm;
//用户结构体
struct users
{
    char cardnum[17];//银行卡号
    char name[20];//用户姓名
    char DID[100];//身份证号
    float Balance;//余额
    int  password;//银行卡密码
    struct users* next;//指向下一个结点//
};
//全局变量
int PEOPLENUM=0;//银行总用户数量
char MONEY_S[20];
float MONEY;//银行总资金
char title[500];  //用户数据第一行说明
char title2[500];  //管理员数据文件第一行说明
char title3[500];  //银行余额数据文件第一行说明
char C[3];
int  B=0;
//随机生成银行卡号
void getMoney(){
    FILE *file;
    file= fopen("银行金钱存储柜.txt","r");
    if(file==NULL){
        printf("存储柜打不开\n");
    }
    else{
        fgets(title3, 200, file);
        fgets(MONEY_S,20,file);
    }
    MONEY= atof(MONEY_S);
    fclose(file);
}
// 把每次操作完之后的钱再一次写入文件
void PutMoney(){
    FILE *file;
    file= fopen("银行金钱存储柜.txt","w");
    if(file==NULL){
        printf("存储柜打不开\n");
    }
    else{
        fputs(title3,file);
        sprintf(MONEY_S,"%f",MONEY);
        fputs(MONEY_S,file);
    }
    fclose(file);
}

//随机生成银行卡号
void randc(){
    int j, m;
    j = B % 10;
    m = B / 10;
    C[0] = m + '0';
    C[1] = j + '0';
}

//显示当前日期
void date()
{
    system("date");

}

//功能结束：用于清屏防止刷屏太快
void over()

{
    int choice;
    char c;
    printf("输入任意数字退出！\n");
    printf("请输入数字:");
    scanf("%d", &choice);
    c = getchar();
}

/*
* 从指定文件读取用户数据并且构建链表存储数据
* *@param  head 传入的初始用户结构体指针
* *@return head 返回创建并且已存储有用户数据的结构体头指针
*/
struct users *readuser(struct users *u)
{
    struct users *r=NULL,*p=NULL;
    FILE *fp;//定义文件指针
    p=u=(struct users *)malloc(sizeof(struct users));
    if ((fp = fopen("userinformation.txt", "r")) == NULL)
        printf("ATM管理系统文件不存在 \n");
    else
    {
        fgets(title, 200, fp);//读取第一行说明:银行卡号，用户姓名，身份证号，余额，银行卡密码等;
        r=(struct users *)malloc(sizeof(struct users));
        while (fscanf(fp,"%s %s %s %d %f",&r->cardnum,&r->name,&r->DID,&r->password,&r->Balance)!=EOF)//如果文件没有读取结束，继续读取//
        {
            PEOPLENUM=PEOPLENUM+1;
            p->next=r;
            p=r;
            r=(struct users *)malloc(sizeof(struct users));
        }
        p->next=NULL;
    }
    fclose(fp);
    fp=NULL;
    return u;
}
void saveusers(struct users *u)
{
    struct users *r=NULL;
    FILE *fp;
    r=u->next;
    fp=fopen("userinformation.txt","w+");
    fputs(title,fp);
    while(r!=NULL)
    {
        fprintf(fp,"%18s\t %s\t\t %22s\t\t %8d\t\t %15.2f\t\t\n",r->cardnum,r->name,r->DID,r->password,r->Balance);
        r=r->next;
    }
    fclose(fp);
}
/*
* @param head :链表的头节点
* @return p   ：返回要查到的数据节点
* function    :判断用户卡号与密码判断用户系统里面是否存在该用户

*/
struct users* finduser(struct users* head)
{
    char card[17];
    char c;
    int pass;//密码
    struct users* pr = NULL;
    int i, t;
    while (1)
    {
        pr = head->next;
        system("clear");
        date();
        printf("\n#################################################################################\n");
        printf("\n▓                               * 欢迎使用  *                                 ▓\n");
        printf("\n##### ############################################################################\n");
        printf("请输入银行卡号：");
        fgets(card, sizeof(card), stdin);
        system("clear");
        date();
        printf("\n#################################################################################\n");
        printf("\n▓                               * 欢迎使用  *                                 ▓\n");
        printf("\n##### ############################################################################\n");
        printf("请输入密码：");
        scanf("%d", &pass);
        c = getchar();
        t = 0;//标记变量。查找到就标记为1，否则为0
        while (pr != NULL)
        {
            if (strcmp(pr->cardnum, card)==0 && pr->password==pass)
            {
                t = 1;//存在该用户
                return pr;//返回该数据节点
            }
            else
                pr = pr->next;
        }
        //没有查找到
        if (t == 0)
            printf("密码或银行卡号错误！\n");
        printf("\n#################################################################################\n");
        printf("\n▓                               * 请输入选项(点击任意键，继续输入)： *                     ▓\n");
        printf("\n##### ############################################################################\n");
        printf("\n                  ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
        printf("          |◆|******|◆|        ☆ 继续输入   请按 1         |◆|******|◆|\n");
        printf("          |◆|******|◆|        ☆ 退出       请按 2         |◆|******|◆|\n");
        printf("          |◆|******|◆|                                    |◆|******|◆|\n");
        printf("          ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
        printf("\n#################################################################################\n");
        printf("\n▓                          *******************************                    ▓\n");
        printf("\n#################################################################################\n");
        scanf("%d", &i);//让用户输入1或者2
        c = getchar();//接受用户可能使用换行符
        switch (i)
        {
            case 2:
                return NULL;//没有找到返回空
            default:
                break;
        }
    }
}

/*
* @param struct users* e ：表示某个用户的节点
* @return struct users* e:表示该用户存款后的节点
*/
struct users* deposit(struct users* e)//存款,
{
    int choose1, choose2; //choose1:表示确认信息用的   choose2:表示金额选择
    char c;// 处理非必要输入
    float amount1, amount2; //amount1:表示要存入的值，amount2:表示用户自定义要存入的值
    system("clear");
    date();
    printf("请确认账户信息！\n1.确定\n2.取消\n");
    printf("银行卡号：%s\n", e->cardnum);//显示用户银行卡号
    printf("姓名：%s\n", e->name);       //显示用户姓名
    printf("请输入选项：");
    scanf("%d", &choose1);
    c = getchar();//接受用户可能使用换行符
    system("clear");
    if (choose1 == 1)
    {
        money:
        printf("\t\t||================================================================||\n");
        printf("\t\t||                           *存款金额*                           ||\n");
        printf("\t\t||================================================================||\n");
        printf("\t\t||                                                                ||\n");
        printf("\t\t||                                                                ||\n");
        printf("\t\t||         1、200        2、400        3、600        4、800       ||\n");
        printf("\t\t||                                                                ||\n");
        printf("\t\t||                                                                ||\n");
        printf("\t\t||         5、1000       6、2000       7、4000       8、6000      ||\n");
        printf("\t\t||                    9、自定义：                                 ||\n");
        printf("\t\t||================================================================||\n");
        printf("\t\t||================================================================||\n");
        printf("请输入您的选择：");
        scanf("%d", &choose2);
        switch (choose2)
        {
            case 1:
                amount1 = 200;
                break;
            case 2:
                amount1 = 400;
                break;
            case 3:
                amount1 = 600;
                break;
            case 4:
                amount1 = 800;
                break;
            case 5:
                amount1 = 1000;
                break;
            case 6:
                amount1 = 2000;
                break;
            case 7:
                amount1 = 4000;
                break;
            case 8:
                amount1 = 6000;
                break;
            case 9:
                printf("请输入自定义金额：");
                scanf("%f", &amount2);
                c = getchar();
                if (amount2 < 100)
                {
                    system("clear");
                    printf("存储金额过少，请重新选择！\n");
                    goto money;//输入错误->转跳到选择界面
                }
                else
                    amount1 = amount2;
                break;
            default:
                system("clear");
                printf("您的选择不在服务范围内！！！！\n\n\n");
                printf("请重新选择业务：\n");
                goto money;//选择错误->，转跳到选择界面
        }
        e->Balance = e->Balance + amount1;//更新用户余额值
        MONEY+=amount1;   //更新银行余额
        printf("存入成功！\n");
    }
    else
    {
        printf("取消存款！\n");
    }
    return e;
}


/*
* @param struct users* e ：表示要取款用户的节点
* @return struct users* e：返回该用户取完款后的节点
*/
struct users* Withdrawal(struct users* e)//取款
{
    int choose1, choose2;//choose1:用于用户信息确认选择。choose2:表示用于取款金额值选择
    char c;
    float amount1, amount2;//amount1:表示要取款金额   amount2 ：表示用户自定义取款金额
    system("clear");
    date();
    printf("请确认账户信息！\n1.确定\n2.取消\n");
    printf("银行卡号：%s\n", e->cardnum);
    printf("姓名：%s\n", e->name);
    printf("请输入选项：");
    scanf("%d", &choose1);
    c = getchar();
    system("clear");
    if (choose1 == 1)
    {
        location:
        printf("\t\t||================================================================||\n");
        printf("\t\t||                           *取款金额*                           ||\n");
        printf("\t\t||================================================================||\n");
        printf("\t\t||                                                                ||\n");
        printf("\t\t||                                                                ||\n");
        printf("\t\t||         1、200        2、400        3、600        4、800       ||\n");
        printf("\t\t||                                                                ||\n");
        printf("\t\t||                                                                ||\n");
        printf("\t\t||         5、1000        6、2000        7、4000        8、6000   ||\n");
        printf("\t\t||                    9、自定义：                                 ||\n");
        printf("\t\t||================================================================||\n");
        printf("\t\t||================================================================||\n");

        printf("请输入您的选择:");
        scanf("%d", &choose2);
        c = getchar();
        switch (choose2)
        {
            case 1:
                amount1 = 200;
                break;
            case 2:
                amount1 = 400;
                break;
            case 3:
                amount1 = 600;
                break;
            case 4:
                amount1 = 800;
                break;
            case 5:
                amount1 = 1000;
                break;
            case 6:
                amount1 = 2000;
                break;
            case 7:
                amount1 = 4000;
                break;
            case 8:
                amount1 = 6000;
                break;
            case 9:
                printf("请输入自定义金额：");
                scanf("%f", &amount2);
                c = getchar();
                if (amount2 < 100)
                {
                    system("clear");
                    printf("取出金额过少，请重新选择！\n");
                    goto location; //输入错误->转跳到选择界面
                }
                else
                    amount1 = amount2;
                break;
            default:
                system("clear");
                printf("您的选择不在服务范围内！！！！\n\n\n");
                printf("请重新选择业务：\n");
                goto location;//转跳到选择界面
        }

        //余额判断
        while (amount1 > e->Balance)
        {
            printf("余额不足！请重新选择！\n");
            printf("1.重新输入金额\n");
            printf("2.取消取款\n");
            printf("请输入选项:");
            scanf("%d", &choose1);
            c = getchar();
            if (choose1 == 1)
            {
                printf("请输入取款金额:");
                scanf("%f", &amount1);
            }
            else
            {
                return e;//退出
            }
        }
        e->Balance = e->Balance - amount1;
        MONEY-=amount1;   //更新银行余额
        printf("取款成功！\n");
        return e;
    }
    else
        return e;
}


/*
* 转款，要求，转入方必须为系统中已经存在的用户
* @param struct users* e   ：代表发起转款的用户节点
* @param struct users* head：表示存储所有用户的链表的头节点
*/
struct users* Transfer(struct users* e, struct users* head)//转账
{
    char card[17];
    char c;
    struct users* pr = NULL;
    int choose1,  choose2;//choose1:表示确认信息选项   choose2：表示要界面功能选择
    int temp;               //用于标记待转入用户信息 temp=0 为0时：没有找到 1代表找到
    float amount1,amount2; //amount1表示转款金额   amount2:表示用户自定义转款金额
    while (1)
    {
        system("clear");
        pr = head->next;
        printf("请输入转账银行卡号：");
        fgets(card,sizeof(card),stdin);
        temp = 0;
        while (pr != NULL)//查找转入方，以及转款操作
        {
            if (strcmp(pr->cardnum, card) == 0)//查找转账账户
            {
                temp = 1; //查找到转入用户信息
                printf("请确认转账账户信息：\n");
                printf("银行卡号：%s\n", pr->cardnum);
                printf("姓名：%s\n", pr->name);
                printf("请确认账户信息！\n1.确定\n2取消\n");
                printf("请输入选项：");
                scanf("%d", &choose1);
                c = getchar();
                if (choose1 == 1)
                {
                    system("clear");
                    turn:
                    printf("\t\t||================================================================||\n");
                    printf("\t\t||                           *转款金额*                           ||\n");
                    printf("\t\t||================================================================||\n");
                    printf("\t\t||                                                                ||\n");
                    printf("\t\t||                                                                ||\n");
                    printf("\t\t||         1、200        2、400        3、600        4、800       ||\n");
                    printf("\t\t||                                                                ||\n");
                    printf("\t\t||                                                                ||\n");
                    printf("\t\t||         5、1000       6、2000       7、4000       8、6000      ||\n");
                    printf("\t\t||                    9、自定义：                                 ||\n");
                    printf("\t\t||================================================================||\n");
                    printf("\t\t||================================================================||\n");
                    printf("请输入选择：");
                    scanf("%d", &choose2);
                    c = getchar();
                    switch (choose2)
                    {
                        case 1:
                            amount1 = 200;
                            break;
                        case 2:
                            amount1 = 400;
                            break;
                        case 3:
                            amount1 = 600;
                            break;
                        case 4:
                            amount1 = 800;
                            break;
                        case 5:
                            amount1 = 1000;
                            break;
                        case 6:
                            amount1 = 2000;
                            break;
                        case 7:
                            amount1 = 4000;
                            break;
                        case 8:
                            amount1 = 6000;
                            break;
                        case 9:
                            printf("请输入自定义金额：");
                            scanf("%f", &amount2);
                            c = getchar();
                            if (amount2 < 100)
                            {
                                system("clear");
                                printf("转出金额过少，请重新选择！\n");
                                goto turn;  //输入不符合格式->转跳到选择界面
                            }
                            else
                                amount1 = amount2;
                            break;
                        default:
                            system("clear");
                            printf("您的选择不在服务范围内！！！！\n\n\n");
                            printf("请重新选择业务：\n");
                            goto turn;// 转跳到选择界面
                    }
                    while (amount1 > e->Balance)
                    {
                        printf("余额不足！请重新选择！\n");
                        printf("\t1.重新输入金额\n  2.取消转账\n");
                        printf("请输入选项:");
                        scanf("%d", &choose1);
                        c = getchar();
                        if (choose1 == 1)
                        {
                            goto turn;//用户选择重新输入->转跳到选择界面
                        }
                        else
                        {
                            printf("取消转款！\n");
                            return head;
                        }
                    }
                    //转账成功
                    e->Balance = e->Balance - amount1;//更新转出方余额值
                    pr->Balance = pr->Balance + amount1;//更新转入方余额值
                    printf("转款成功！\n");
                    return head;
                }
                else
                {
                    printf("取消转款！\n");
                    return head;
                }
            }
            else
            {
                pr = pr->next; //不断遍历，查找转入方
            }
        }
        //没有查找到转入方
        if (temp == 0)
        {
            printf("银行卡号错误！\n");
            printf("请选择  1.继续输入；\n\t2.退出；\n");
            printf("请输入选项(点击任意键，继续输入)：");
            scanf("%d", &choose1);
            c = getchar();
            switch (choose1)
            {
                case 2:
                    return head;
                default:
                    break;
            }
        }
    }
}

struct users *create(struct users *u)
{
    int i;
    struct users *s=NULL;
    s=(struct users *)malloc(sizeof(struct users));
    printf("请输入身份证(18位)：");
    scanf("%s",&s->DID);
    printf("请输入姓名：");
    scanf("%s",s->name);
    printf("请输入密码（6位）：");
    scanf("%d",&s->password);
    randc();
    strcpy(s->cardnum,"01234567890000");
    strcat(s->cardnum,C);
    s->Balance=0.00;
    system("clear");
    date();
    printf("\n#################################################################################\n");
    printf("\n▓                               * 是否确定创建用户 *                                 ▓\n");
    printf("\n##### ############################################################################\n");
    printf("\n                  ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
    printf("          |◆|******|◆|        ☆ 确定       请按 1         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 取消       请按 2         |◆|******|◆|\n");
    printf("          |◆|******|◆|                                    |◆|******|◆|\n");
    printf("                    ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
    printf("\n#################################################################################\n");
    printf("\n▓                          *******************************                    ▓\n");
    printf("\n#################################################################################\n");
    printf("请输入选项:");
    scanf("%d",&i);
    if(i==1)
    {
        s->next=u->next;
        u->next=s;
        PEOPLENUM+=1;
        printf("创建成功！\n");
        printf("%s",title);
        printf("%18s\t %s\t\t %22s\t\t %8d\t\t %15.2f\t\t\n",s->cardnum,s->name,s->DID,s->password,s->Balance);
    }
    else
    {
        free(s);
        printf("取消创建\n");
    }
    return u;
}

/*
* 通过查找信息，删除节点实现用户销功能
* @param struct users* head ：存储用户信息的链表的头节点
* @return head              ：返回销户后的链表头节点
*/
struct users* del(struct users* head)
{
    struct users* p = NULL, * pr = NULL;//p用于遍历 ,pr：代表当前正在操作的节点
    int choose;//用户选择
    char card[20];
    char ID[100];
    char c;
    p = head;
    pr=head;
    int password;
    //pr = p->next;
    printf("请输入银行卡号：");
//    fgets(card, sizeof(card), stdin);
    scanf("%s",card);
    printf("请输入密码：");
    scanf("%d",&password);
    while (pr != NULL)
    {
        if (strcmp(pr->cardnum, card) == 0 && pr->password ==password)
        {
            break;
        }
        p = pr;
        pr = pr->next;
    }
    if (pr == NULL)//查找账户失败！退出
    {
        printf("查找账户失败！");
        over();
        return head;
    }
    //通过输入身份证验证是本人正在操作，避免他人进行删除操作。
    printf("请输入身份证号：");
    scanf("%s",ID);
    while (1)
    {
        if(strcmp(pr->DID,ID)==0)
        {
            printf("取出余额%f\n", pr->Balance);
            PEOPLENUM-=1;
            printf("销户成功！\n");
            p->next = pr->next;//删除该用户节点-->销户
            free(pr);
            return head;// 返回销户后的节点
        }
        else
        {
            printf("身份证号错误！\n");
            printf("1.重新输入身份证号  2.取消注销\n");
            printf("请输入选项:");
            scanf("%d", &choose);
            c = getchar();
            if (choose == 1)
            {
                printf("请输入身份证号：");
                //fgets(ID, sizeof(ID), stdin);
                scanf("%s",ID);
            }
            else
            {
                printf("取消注销\n");
                return head;
            }
        }
    }
}

struct users* changPassword(struct users*head){
    int newPassword=0;
    int newPassword2=0;
    char carnum[18];
    int oldPassword=0;
    int digit;
    long  long IDI;
    printf("==========================\n");
    printf("请输入帐号：\n");
    scanf("%17s",carnum);
    struct users* turn =head;
    while(turn !=NULL){
        if(strcmp(turn->cardnum,carnum)==0){
            while(1){
                printf("======================\n");
                printf("请输入你的旧密码：\n");
                scanf("%d",&oldPassword);
                if(oldPassword==turn->password){
                    printf("=======================\n");
                    printf("请输入新密码\n");
                    scanf("%d",&newPassword);
                    printf("==========================\n");
                    printf("请再一次输入新密码：");
                    scanf("%d",&newPassword2);
                    if(newPassword==newPassword2){
                        turn->password=newPassword;
                        printf("=====================\n");
                        printf("修改成功\n");
                        return head;
                    }
                    else{
                        printf("=====================\n");
                        printf("两次密码不一致\n");
                        continue;
                    }
                }else{
                    printf("=====================\n");
                    printf("密码错误\n");
                }
            }
        }
        turn=turn->next;
    }
    printf("没有该用户\n");
    return head;
};
/*
 * @param Adm *head: 用于存储管理员数据的链表的头节点
 * */
struct Administrator *readManager(Adm *head){
    Adm *p=NULL,*pr=head;//pr用于遍历链表
    FILE *file;  //文件指针
    file= fopen("
        bank.txt","r");
    if(file==NULL){
        printf("bank文件打开失败\n");
    }
        //读取文件数据
    else{
        p=(Adm *) malloc(sizeof (Adm));//申请内存空间
        if(p==NULL){
            printf("内存申请失败！");
            exit(0);
        }
        else{
            fgets(title2, 200, file);//读取第一行说明:员工工号，密码，姓名，电话号码;
            //通过创建新节点存储数据，
            while(fscanf(file, "%s%s%s%11s",
                         p->staffID,p->password, p->staffName, p->phoneNumber) != EOF){
                pr->next = p;
                pr = p;
                p=(Adm *) malloc(sizeof (Adm));//申请内存空间
                if (!p) {
                    printf("No enough memory to allocate !\n");
                    exit(0);
                }
            }p->next = NULL;  //尾指针指向空指针
        }
    }
    fclose(file);
    file = NULL;
    return head;
}


bool verify(Adm *head,char *id,char *password){
    Adm *p=head->next;
    while(p!=NULL){
        if(strcmp(p->staffID,id)==0 && strcmp(p->password,password) == 0 ){
            return true;
        }
        p=p->next;
    }
    return false;
}

void login(Adm *head){
    char id[staffIDLen];
    char password[passwordLen];

    while(1){
        printf("请输入工号:\n");
        scanf("%s",id);
        printf("请输入密码：\n");
        scanf("%s",password);
        if(verify(head,id,password)) {
            printf("登录成功");
            break;
        } else{
            printf("密码或者帐号错误，重新输入");
        }
    }
}


void search(struct users* head ){
    char cardnum[19];
    printf("请输入你想查看账户的帐号");
    scanf("%18s",cardnum);
    struct users* p;
    p=head;
    while(p!=NULL){
        if(strcmp(p->cardnum,cardnum)==0){
            printf("卡号\t\t姓名\t\t身份证号\t\t余额\t\t银行卡密码\n");
            printf("%-18s\t%-16s\t%-22s\t%-12.2f\t%8d\t\n",p->cardnum,p->name,p->DID,p->Balance,p->password);
            return;
        }
        p=p->next;
    }
    if(p==NULL){
        printf("没有该用户\n");
    }
}
// 函数功能： 自定义查询（辅助statistic分析）
void selfstatistic(struct users *head, int number) {
    int left;
    int right;
    int num = 0;
    struct  users *p=head;
    printf("请输入你要查询的区间（格式：left,right）\n");
    scanf("%d,%d", &left, &right);
    while (p!=NULL) {
        if (left <= p->Balance && p->Balance <= right) {
            num += 1;
        }
        p=p->next;
    }
    printf("____________________________________\n");
    printf("|    ￥%2d--%2d      |   %12.2f%%   |\n", left, right, num /(float) number * 100);
    printf("------------------------------------\n");
}

/*
 * 对存款余额各区间人数占比进行分析
 * @param users *head,int number
 * */
void User_analytics(struct users *head,int number){
    int choose;
    int num1=0;
    int num2=0;
    int num3=0;
    int num4=0;
    struct  users* p=head->next;
    while(p!=NULL){
        if (p->Balance<10000.00){  //小于一万
            num1+=1;
        }
        else if(10000.00<=p->Balance&&p->Balance<100000.00){  //一万元到十万元
            num2+=1;
        }
        else if (100000.00<=p->Balance&&p->Balance<1000000.00){ //十万元到100万元
            num3+=1;
        }
        else if (p->Balance>=1000000.00){//大于100万元
            num4+=1;
        }
        p=p->next;
    }
    printf("________________________________________\n");
    printf("| ￥0--10000            | %12.2f%%      |\n", (float)num1 / PEOPLENUM * 100);
    printf("| ￥10000--100000       | %12.2f%%      |\n", (float)num2 / PEOPLENUM * 100);
    printf("| ￥100000--1000000     | %12.2f%%      |\n", (float)num3 / PEOPLENUM * 100);
    printf("| >=￥1000000           | %12.2f%%      |\n", (float)num4 / PEOPLENUM * 100);
    printf("----------------------------------------\n");

    printf("1.自定义查询  2.退出\n");
    printf("请输入选项(点击任意键，继续输入)：");
    scanf("%d",&choose);
    switch (choose) {
        case 1:
            selfstatistic(head,number);
            break;
        case 2:
            return;
        default:
            return;
    }
}

void swapUsers(struct users* user1, struct users* user2) {
    char tempCardnum[17];  // 交换卡号
    strncpy(tempCardnum, user1->cardnum, sizeof(tempCardnum) - 1);
    tempCardnum[sizeof(tempCardnum) - 1] = '\0';
    strncpy(user1->cardnum, user2->cardnum, sizeof(user1->cardnum) - 1);
    user1->cardnum[sizeof(user1->cardnum) - 1] = '\0';
    strncpy(user2->cardnum, tempCardnum, sizeof(user2->cardnum) - 1);
    user2->cardnum[sizeof(user2->cardnum) - 1] = '\0';

    char tempName[20];  // 交换姓名
    strncpy(tempName, user1->name, sizeof(tempName) - 1);
    tempName[sizeof(tempName) - 1] = '\0';
    strncpy(user1->name, user2->name, sizeof(user1->name) - 1);
    user1->name[sizeof(user1->name) - 1] = '\0';
    strncpy(user2->name, tempName, sizeof(user2->name) - 1);
    user2->name[sizeof(user2->name) - 1] = '\0';

    char tempID[100];  // 交换姓名
    strncpy(tempID, user1->DID, sizeof(tempID) - 1);
    tempID[sizeof(tempID) - 1] = '\0';
    strncpy(user1->DID, user2->DID, sizeof(user1->DID) - 1);
    user1->DID[sizeof(user1->DID) - 1] = '\0';
    strncpy(user2->DID, tempID, sizeof(user2->DID) - 1);
    user2->DID[sizeof(user2->DID) - 1] = '\0';

    float tempBalance = user1->Balance;  // 交换余额信息
    user1->Balance = user2->Balance;
    user2->Balance = tempBalance;

    int tempPassword = user1->password;  // 交换密码
    user1->password = user2->password;
    user2->password = tempPassword;
}

// 冒泡排序：
struct users *Sort(struct users* head, int choose) {
    struct users *save=NULL;
    struct users *move=NULL;
    for(struct users *turn=head->next;turn->next!=NULL;turn=turn->next){
        for(move=head->next;move->next!=NULL;move=move->next){
            switch (choose) {
                case 1:  // 通过姓名比较
                    if (strcmp(move->name, move->next->name) < 0) {
                        swapUsers(move, move->next);
                    }
                    break;

                case 2:  // 通过卡号比较
                    if (strcmp(move->cardnum, move->next->cardnum) < 0) {
                        swapUsers(move, move->next);
                    }
                    break;
                case 3:  // 通过余额比较
                    if (move->Balance < move->next->Balance) {
                        swapUsers(move, move->next);
                    }
                    break;
            }
        }
    } return head;
}

//管理员界面
void AdmMenu(){
    system("clear");
    date();
    printf("\n#################################################################################\n");
    printf("\n▓                                   * 用户管理系统 *                               ▓\n");
    printf("\n##### ############################################################################\n");
    printf("\n                  ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
    printf("          |◆|******|◆|        ☆ 查询用户数量        请按 1         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 查看用户数据        请按 2         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 用户数据分析        请按 3         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 用户花名册          请按 4         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 银行资金结余        请按 5         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 退出管理系统        请按 0         |◆|******|◆|\n");
    printf("          |◆|******|◆|                                          |◆|******|◆|\n");
    printf("                    ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
    printf("\n#################################################################################\n");
    printf("\n▓                          *******************************                    ▓\n");
    printf("\n#################################################################################\n");
}
void print(struct users*head){
    printf("------卡号---------------姓名-----------------身份证号------------存款--------------密码------\n");
    struct users *p=head->next;
    while(p!=NULL){
        printf("%-20s\t%-16s\t%-20s\t%-15.2f\t%-8d\n", p->cardnum, p->name, p->DID,p->Balance, p->password);
        p=p->next;
    }
}

void OutputMenu(struct users *head){
    int choose;
    while(1) {
        printf("\t\t||================================================================||\n");
        printf("\t\t||                            *用户花名册*                          ||\n");
        printf("\t\t||================================================================||\n");
        printf("\t\t||        排序方式：                                                ||\n");
        printf("\t\t||              1、按姓名排序                                       ||\n");
        printf("\t\t||              2、按卡号排序                                       ||\n");
        printf("\t\t||              3、按照存款余额排序                                  ||\n");
        printf("\t\t||              0、退出                                            ||\n");
        printf("\t\t||================================================================||\n");
        printf("\t\t||================================================================||\n");
        printf("请输入选择：");
        scanf("%d", &choose);
        //功能选择
        switch (choose) {
            case 1:
                head = Sort(head, 1);
                system("clear");
                printf("=======\n");
                print(head);
                system("cls");
                break;

            case 2:
                head = Sort(head, 2);
                system("clear");
                printf("=======\n");
                print(head);
                break;

            case 3:
                head = Sort(head, 3);
                system("clear");
                printf("=======\n");
                print(head);
                break;
            case 0:
                return;
            default:
                printf("输入的选项错误，请重新输入!\n");
                system("clear");
        }
    }
}

void Admmain(Adm *A_head,struct  users * U_head){
    int choose;//选择

    login(A_head);//先登陆，进入系统

    while(1) {
        AdmMenu();
        printf("请输入你的选择(回车代表结束)：\n");
        scanf("%d", &choose);//功能选择
        switch (choose) {
            case 1:
                system("clear");
                printf("================================\n");
                printf("||   用户数量：     %5d          ||\n", PEOPLENUM);
                printf("================================\n");
                break;

            case 2:
                system("clear");
                search(U_head);
                break;

            case 3:
                system("clear");
                User_analytics(U_head, PEOPLENUM);
                break;

            case 4:
                system("clear");
                OutputMenu(U_head);
                break;

            case 5:
                system("clear");
                printf("===============================\n");
                printf("|| 总计 ：   %12.4f             ||\n",MONEY);
                printf("===============================\n");
                break;
            case 0:
                return ;
            default:
                printf("输入的选项错误，请重新输入!\n");
                system("clear");
                AdmMenu();
                break;
        }
    }
}

void startUI(){
    printf("\n#################################################################################\n");
    printf("\n▓                               * 欢迎进入ATM管理系统  *                      ▓\n");
    printf("\n##### ############################################################################\n");
    printf("\n                  ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
    printf("          |◆|******|◆|        ☆ 管理员登录          请按 1         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 用户登录            请按 2         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 退  出  系  统      请按 0         |◆|******|◆|\n");
    printf("          |◆|******|◆|                                           |◆|******|◆|\n");
    printf("                    ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
    printf("\n##0123456789000001###############################################################################\n");
    printf("\n▓                          *******************************                    ▓\n");
    printf("\n#################################################################################\n");
}

//ATM显示界面
void menu()
{
    system("clear");
    date();
    printf("\n#################################################################################\n");
    printf("\n▓                               * 欢迎进入ATM管理系统  *                      ▓\n");
    printf("\n##### ############################################################################\n");
    printf("\n                  ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
    printf("          |◆|******|◆|        ☆ 查询账户余额         请按 1        |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 存款               请按 2         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 取款               请按 3         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 转账               请按 4         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 开户               请按 5         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 销户               请按 6         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 修改密码            请按 7         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 帮助               请按 8         |◆|******|◆|\n");
    printf("          |◆|******|◆|        ☆ 退  出  系  统      请按 9         |◆|******|◆|\n");
    printf("          |◆|******|◆|                                           |◆|******|◆|\n");
    printf("                    ◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆\n");
    printf("\n#################################################################################\n");
    printf("\n▓                          *******************************                    ▓\n");
    printf("\n#################################################################################\n");
}
//使用帮助
void help()
{
    system("clear");
    puts("                         <-使用ATM指南->                              \n");
    puts("使用本产品，请仔细阅读帮助说明\n");
    puts("ATM管理系统共有七大功能\n");
    puts("1、查询账户余额\n");
    puts("使用此功能，需要选择“ATM管理系统”中的第一个选项\n");
    puts("登录需要输入银行卡号(16位)以及密码\n");
    puts("若输入错误，则输入1即可重新输入，输入2可以返回“ATM管理系统”\n");
    puts("2、存款\n");
    puts("使用此功能，需要选择“ATM管理系统”中的第二个选项\n");
    puts("登录需要输入银行卡号(16位)以及密码\n");
    puts("若输入错误，则输入1即可重新输入，输入2可以返回“ATM管理系统”\n");
    puts("登录成功后，输入1确定信息，输入2取消并退至“ATM管理系统”\n");
    puts("确定信息后，输入1-9选择存款多少\n");
    puts("当选择自定义余额后，可输入预期存款\n");
    puts("自定义余额最小值为100元，否则需重新选择大小\n");
    puts("存款结束后，点击任意数字键退出并返回“ATM管理系统”\n");
    puts("3、取款\n");
    puts("使用此功能，需要选择“ATM管理系统”中的第三个选项\n");
    puts("登录需要输入银行卡号(16位)以及密码\n");
    puts("若输入错误，则输入1即可重新输入，输入2可以返回“ATM管理系统”\n");
    puts("登录成功后，输入1确定信息，输入2取消并退至“ATM管理系统”\n");
    puts("确定信息后，输入1-9选择取款多少\n");
    puts("当选择自定义余额后，可输入预期取款\n");
    puts("自定义余额最小值为100元，否则需重新选择大小\n");
    puts("取款结束后，点击任意数字键退出并返回“ATM管理系统”\n");
    puts("4、转账\n");
    puts("使用此功能，需要选择“ATM管理系统”中的第四个选项\n");
    puts("登录需要输入银行卡号(16位)以及密码\n");
    puts("若输入错误，则输入1即可重新输入，输入2可以返回“ATM管理系统”\n");
    puts("然后输入你想转账的用户\n");
    puts("转账结束后，则输入1即可重新输入，输入2可以返回“ATM管理系统”\n");
    puts("5、开户:\n");
    puts("使用本次产品之前，可以到工作人员处或者自行注册\n");
    puts("用户注册新储户，请选择“ATM管理系统”中的第五个选项“开户”\n");
    puts("进入“开户系统”后，需要自行输入身份证，姓名以及密码\n");
    puts("姓名的字符长度不超过20，身份证为18位，密码第一位不能为0");
    puts("注册新用户之后，一定要输入数字1进行保存储户信息\n");
    puts("6、销户\n");
    puts("使用此功能，需要选择“ATM管理系统”中的第六个选项\n");
    puts("登录需要输入银行卡号(16位)以及密码\n");
    puts("通过输入身份证验证是本人正在操作，避免他人进行删除操作\n");
    puts("然后需取出剩余存款\n");
    puts("取出存款后进行销户\n");
    puts("销户结束后，则输入1即可重新输入，输入2可以返回“ATM管理系统”\n");
    puts("7、修改密码\n");
    puts("登录需要输入银行卡号(16位)以及密码\n");
    puts("验证完身份后，输入新密码\n");
    puts("修改密码结束后，则输入1即可重新输入，输入2可以返回“ATM管理系统”\n");
    puts("8、如果忘记密码，请来到银行工作人员处，修改储户信息，也可以更改自己的密码\n");
    puts("9、欢迎使用本产品，若有不足之处，请拨打电话或者留言开发者，提出建议\n");
    puts("10、开发者联系方式：“QQ：1234567890”\n");
    system("pause");
    char choice;
    printf("是否已阅读以上指南（1-已阅读，0-未阅读并退出程序）\n");
    scanf("%s", &choice);
    switch (choice)
    {
        case '1':
            break;
        case '0':
            exit(0);
        default:
            printf("输入错误！！\n");
            system("pause");
            help();//再次输入选项
            //			system("color 07");	//白色
    }
}
//用户界面
void UI(struct users* u){
    struct users* e=NULL;
    int choose, i;
    char c;
    while (1)
    {
        menu();
        printf("请输入你的选择:");
        scanf("%d", &choose);
        c = getchar();
        switch (choose)
        {
            //查询账户余额
            case 1:
                e = finduser(u);//查找用户
                if (e == NULL)//查找账户失败！退出
                {
                    printf("查找账户失败！");
                    over();
                    break;
                }
                else
                {
                    printf("账户余额为：%f\n", e->Balance);
                    over();
                    break;
                }
                //存款
            case 2:
                e = finduser(u);//查找用户
                if (e == NULL)//查找账户失败！退出
                {
                    printf("查找账户失败！");
                    over();
                    break;
                }
                e = deposit(e);
                saveusers(u);
                over();
                break;
                //取钱
            case 3:
                e = finduser(u);//查找用户
                if (e == NULL)//查找账户失败！退出
                {
                    printf("查找账户失败！");
                    over();
                    break;
                }
                e = Withdrawal(e);
                saveusers(u);
                over();
                break;
                //转账
            case 4:
                e = finduser(u);//查找用户
                if (e == NULL)//查找账户失败！退出
                {
                    printf("查找账户失败！");
                    over();
                    break;
                }
                u = Transfer(e, u);
                saveusers(u);
                over();
                break;
                //开户
            case 5:
                u = create(u);
                saveusers(u);
                over();
                break;
                //销户
            case 6:
                u = del(u);
                saveusers(u);
                over();
                break;
            case 7:
                u = changPassword(u);
                saveusers(u);
                over();
                break;
            case 8:
                help();
                break;
            case 9:
                return ;
            default:
                printf("输入的选项错误，请重新输入!\n");
                break;
        }
        PutMoney();
    }
};

int main()
{
    int choose;
    getMoney();
    system("COLOR 0b");
    struct users* u = NULL;
    struct Administrator * head;
    head= readManager(head);
    u = readuser(u);//读取用户信息//
    B+=PEOPLENUM;
    while (1){
        date();
        startUI();
        printf("请输入你的选择:\n");
        scanf("%d",&choose);
        switch (choose) {
            case 1:
                Admmain(head,u);
                over();
                break;
            case  2:
                UI(u);
                break;

            case 0:
                return 0;

            default:
                printf("请重新输入：\n");
        }
    }
    PutMoney();
    return 0;
}
