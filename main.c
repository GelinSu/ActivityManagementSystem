#include<windows.h>
#include<stdio.h>
#include<string.h>
#include<conio.h>
#include<stdlib.h>
#include<malloc.h>
#define ENTER 13
#define BACKSPACE 8
#define OK 1
#define ERROR 0

char filename[20];
void Register();
void Login();
void User_choice(int l,char *user,char *pwd);
struct activity_list * Read();

struct activity_list
{
    char number[100];
    char content[100];                  //�����
    int count;                          //�����
    int join;                           //�μӻ
    char demand[100];                   //�Ҫ��
    char time1[100];                    //�ʱ��
    char Cname[100];                    //�������
    char pwd3[15];                      //���������
    struct activity_list * next;        /*�����ָ����*/
};

//�����������Ϣ
void save(struct activity_list * head)
{
    struct activity_list *p;
    FILE *fp;

    p=head;
    fp=fopen("ȫ���.txt","w+");
    fprintf(fp,"%30s%30s%30d%30d%30s%30s%30s",p->number,p->content,p->count,p->join,p->demand,p->time1,p->Cname);
    while(p->next!= NULL)
    {
        p=p->next;
        fprintf(fp,"%20s%20s%20d%20d%20s%20s%20s",p->number,p->content,p->count,p->join,p->demand,p->time1,p->Cname);
    }
    fclose(fp);
}
//����
struct activity_list * InsertDoc(struct activity_list * head,struct activity_list * book)
{
    struct activity_list * ptr,* p;

    p=head;
    ptr=book;
    if(head==NULL)
    {
        head=ptr;
        head->next=NULL;
    }
    else
    {
        while(p->next!=NULL)
            p=p->next;
        p->next=ptr;
        ptr->next=NULL;
    }
    save(head);
    return head;
}
//�������ַ�תΪ"*"
char *Get_password(const char *prompt)
{
    char ch;
    static char p[15];
    int i=0;
    puts(prompt);
    while((ch=getch())!=ENTER && ch != -1)
    {
        if(i == 14 && ch != BACKSPACE)
        {
            continue;
        }
        if(ch==BACKSPACE)
        {
            if(i==0)
            {
                continue;
            }
            else		             //�����˼�����һλ���Ե���*",�ٺ���һλ
            {
                i--;
                putchar(BACKSPACE);
                putchar(' ');
                putchar(BACKSPACE);
            }
        }
        else		//���ַ��浽����
        {
            p[i]=ch;
            putchar('*');
            i++;
        }
    }
    printf("\n");
    p[i]='\0';
    return p;
}

//�ж��û����Ƿ�Ϸ�
int Judge_user(char *user)
{
    int flag=0;
    FILE *fp;
    char user1[21],pwd[15];
    if((fp=fopen("��½��Ϣ.txt","r"))==NULL) flag=1;       //�ж��ļ��Ƿ����
    if(flag==0)
    {

        while(!(feof(fp)))
        {
            fscanf(fp,"%s %s",user1,pwd);     //��ȡ�����û�����Ϣ
            if(strcmp(user1,user)==0)   break;
        }

        if(!(feof(fp)))
        {
            printf("���û����Ѵ��ڣ��뻻һ���û���:\n");
            return ERROR;
        }
        else
        {
            return OK;            //�����жϽ��
        }

    }
    else return OK;


    if(fclose(fp))
    {
        printf("Can not close the file!����ʧ�ܣ�\n");
        exit(0);
    }
}

//��ҳ��
void Ledge_ment()
{
    printf("\t\t ============�����============\n");
    printf("\t\t *��*��*��*��*��*��*��*��*��*��*\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *    ��1�������            *\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *    ��2������            *\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *    ��3��ɾ���            *\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *    ��4���μӻ            *\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *    ��5���鿴�μӻ������  *\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *    ��6����������        *\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *    ��7���鿴�ѽ����Ļ    *\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *    ��8��ע���û�            *\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *    ��0���˳�����            *\n");
    printf("\t\t��                             ��\n");
    printf("\t\t *��*��*��*��*��*��*��*��*��*��*\n");
    printf("\t\t ================================\n");
}

//�ж���"ȫ���.txt"�л����Ƿ��Ѵ���
int Judge_number2(char *number)
{
    FILE *fp;
    int flag=0,flag1=0;
    struct activity_list *p1;
    if((fp=fopen("ȫ���.txt","r"))==NULL) flag=1;
    if(flag==0)
    {
        p1=(struct activity_list *)malloc(sizeof(struct activity_list));                               //���ļ��ж�ȡ���л��Ϣ
        while(!(feof(fp)))
        {

            fscanf(fp,"%20s%20s%20d%20d%20s%20s%20s",p1->number,p1->content,&p1->count,&p1->join,p1->demand,p1->time1,p1->Cname);
            if((strcmp(p1->number,number))==0)
            {
                flag1=1;
                //�жϻ����Ƿ��Ѵ��� ������������
            }

        }

        if(flag1==1)
        {
            system("cls");
            printf("\n");
            printf("�����Ѵ���! \n");
            printf("\n");
            return ERROR;

        }
        else return OK;
    }

    else  return OK;
    //�����жϽ��
    if(fclose(fp))
    {
        printf("Can not close the file!\n");
        exit(0);
    }
}
//����������ҶԻ�������룬�Է���ɾ
void Create_activity(char *user,char *pwd)
{
    FILE *fp;
    char *pwd3,pwd4[15],*num,s2[50];
    int i,n;
    struct activity_list * head, * p;
    head=Read();
    int size=sizeof(struct activity_list);
    p=(struct activity_list * )malloc(size);

    do
    {
        printf("�������ı�ţ�");
        scanf("%s",p->number);
    }
    while(!(Judge_number2(p->number)));
    printf("����������:");
    scanf("%s",p->content);
    printf("������������");
    scanf("%d",&p->count);
    do
    {
        printf("������0��");
        scanf("%d",&p->join);
    }
    while((p->join)!=0);
    printf("������Ҫ��");
    scanf("%s",p->demand);
    printf("������ʱ��(eg:2015/04/23)��");
    scanf("%s",p->time1);
    printf("�����봴��������");
    scanf("%s",p->Cname);
    num=p->number;
    pwd3=Get_password("�����������룬�Է���ɾ(<=14)��");
    for(i=0; *pwd3!='\0'; i++)
    {
        pwd4[i]=*pwd3;
        pwd3++;
    }
    pwd4[i]='\0';
    pwd3=Get_password("��ȷ������(<=14):");
    while(strcmp(pwd4,pwd3)!=0)
    {
        pwd3=Get_password("���벻һ��,����������(<=14):");
        for(i=0; *pwd3!='\0'; i++)
        {
            pwd4[i]=*pwd3;
            pwd3++;
        }
        pwd4[i]='\0';
        pwd3=Get_password("��ȷ������(<=14):");
    }
    //�����ź�������� ������ļ� ��,�Ա�ɾ�����޸Ļ
    if((fp=fopen("�����.txt","a+"))==NULL) exit(0);
    fprintf(fp,"%s %s\n",num,pwd3);
    if(fclose(fp)) exit(0);
    //�������
    head=InsertDoc(head,p);
    strcpy(s2,p->number);
    strcat(s2,"��Ż.txt");
    strcpy(filename,s2);
    if((fp=fopen(filename,"a+"))==NULL)
    {
        printf("File open error!\n");
        exit(0);
    }
    if(fclose(fp))
    {
        printf("Can not close the file!\n");
        exit(0);
    }
    system("cls");
    printf("\n");
    Ledge_ment();
    printf("\t\t\t������ɹ�!\n");
    printf("���������ѡ��(0~8):");
    scanf("%d",&n);
    User_choice(n,user,pwd);
}
/*���ļ�*/
struct activity_list * Read()
{
    struct activity_list *p1,*head=NULL,*tail;
    FILE * fp;

    if((fp=fopen("ȫ���.txt","r"))==NULL)
    {
        goto here1;
    }

    while(!feof(fp))
    {
        p1=(struct activity_list *)malloc(sizeof(struct activity_list));
        fscanf(fp,"%20s%20s%20d%20d%20s%20s%20s",p1->number,p1->content,&p1->count,&p1->join,p1->demand,p1->time1,p1->Cname);
        if(head==NULL)
            head=p1;
        else
            tail->next=p1;
        tail=p1;
    }
    tail->next=NULL;
    fclose(fp);

here1:
    return head;
}
//���ȫ���
void Search_activity(char *user,char *pwd,struct activity_list *head)
{
    struct activity_list * p1;
    head=Read();
    int n;
    if(head==NULL)
    {
        system("cls");
        Ledge_ment();
        printf("\t\t���޻���ڣ�����ѡ�񴴽����\n");
        printf("�������������ѡ��(0~8):");
        scanf("%d",&n);
        User_choice(n,user,pwd);
    }
    for(p1=head; p1; p1=p1->next)
    {
        printf("\n");
        printf("���ţ�%s\n����ݣ�%s\n�������%d\n�ѲμӸû��������%d\n�Ҫ��%s\n����ڣ�%s\n������ߣ�%s\n",p1->number,p1->content,p1->count,p1->join,p1->demand,p1->time1,p1->Cname);
        printf("\n\n");
    }
    Ledge_ment();
    printf("\t\t��ܰ��ʾ������ϻ����ɼ��!\n");
    printf("���������ѡ��(0~8):");
    scanf("%d",&n);
    User_choice(n,user,pwd);
}

//��ɾ���в�ѯɾ���ı��
struct activity_list * Delete(char *user,char *pwd,char *temp)
{
    struct activity_list * ptr1,* ptr2,*head;
    int a=0,l;
    char b;
    head=Read();
    if(head==NULL)
    {
        printf("\n�Ϊ�գ��޷�ɾ����\n\n");
        return NULL;
    }
    while(head!=NULL&&strcmp(head->number,temp)==0)
    {
        ptr2=head;
        head=head->next;
        free(ptr2);
        a=1;
    }
    if(head==NULL)
    {
        printf("\n�Ϊ�գ��޷�ɾ����\n\n");
        return NULL;
    }
    ptr1=head;
    ptr2=head->next;
    while(ptr2!=NULL)
    {
        if(strcmp(ptr2->number,temp)==0)
        {
            ptr1->next=ptr2->next;
            free(ptr2);
            a=1;
        }
        else
            ptr1=ptr2;
        ptr2=ptr1->next;
    }
    if(ptr2==NULL&&a==0)
    {
        system("cls");
        Ledge_ment();
        printf("\t\t\t����Ҫɾ���Ļ�����ڣ�\n\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
        return head;
    }
    printf("\nȷ��ɾ���û����Y/N����");
    getchar();
    b=getchar();
    if(b=='Y'||b=='y')
    {
        save(head);
    }
    else
    {
        system("cls");
        Ledge_ment();
        printf("\t\t\tδɾ�����\n\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
    }
    return head;
}
//ɾ����������߲����ʸ�ɾ����
void Delete_activity(char *user,char *pwd1)
{
    char number[21],s2[26],num[21];
    FILE *fp;
    char *pwd,pwd3[15];
    int j=1,l;
    if((fp=fopen("�����.txt","r"))==NULL)
    {

        Ledge_ment();
        printf("\t\t\t�����Ѵ������\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd1);
    }
    printf("��������Ҫɾ���Ļ���:");
    scanf("%s",number);
    pwd=Get_password("����������(<=14):");         //��ȡ�û���������

    while(!(feof(fp)))
    {
        fscanf(fp,"%s %s",num,pwd3);
        if(strcmp(num,number)==0)  break;
    }
    if(!feof(fp))
    {
        while(strcmp(pwd,pwd3)!=0)
        {

            printf("�������!\n");
            pwd=Get_password("����������û����:");
            j++;
            //�ж��û����������Ƿ�ƥ��
            if(j>3) break;
        }
        if(j>=3)
        {
            system("cls");
            Ledge_ment();
            printf("\t\t��������������,���Ժ���ɾ��!\n");
            printf("���������ѡ��(0~8):");
            scanf("%d",&l);
            User_choice(l,user,pwd1);
        }
        else
        {

            Delete(user,pwd1,number);
            strcpy(s2,number);
            strcat(s2,"��Ż.txt");
            strcpy(number,s2);
            remove(number);
            system("cls");
            Ledge_ment();
            printf("\t\t\t�ɹ�ɾ���û��\n\n");
            printf("���������ѡ��(0~8):");
            scanf("%d",&l);
            User_choice(l,user,pwd);
        }
    }
    else
    {
        system("cls");
        Ledge_ment();
        printf("\t\t�˻������!\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
    }

    if(fclose(fp)) exit(0);

}


//�μӻ
void Join_activity(char *user,char *pwd,char *filename)
{
    char num[20],num1[20],s2[20],a;
    int l,m,n;
    FILE *fp,*fp1;
    struct activity_list * p,*head;
    head=Read();
    printf("����������μӵĻ�ı��: ");
    scanf("%s",num);
    if(head==NULL)
    {
        Ledge_ment();
        printf("\t\t\t���޻����!\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
    }
    for(p=head; p; p=p->next)
    {
        if(strcmp(p->number,num)==0)
        {
            printf("\n");
            printf("���ţ�%s\n����ݣ�%s\n�������%d\n�ѲμӸû��������%d\n�Ҫ��%s\n����ڣ�%s\n������ߣ�%s\n",p->number,p->content,p->count,p->join,p->demand,p->time1,p->Cname);
            printf("\n");
            m=p->join;
            n=p->count;
            if((fp=fopen(filename,"a+"))==NULL)
            {
                printf("File open error!\n");
                exit(0);
            }
            while(!feof(fp))
            {
                fscanf(fp,"%s",num1);
                if((strcmp(num1,num)==0))
                {
                    if(strcmp(num1,num)==0)
                    {
                        Ledge_ment();
                        printf("\t\t    �������ظ��μ�ͬһ���\n");
                        printf("���������ѡ��(0~8):");
                        scanf("%d",&l);
                        User_choice(l,user,pwd);
                        break;
                    }
                }
            }
            if(feof(fp))
            {
                if(strcmp(num1,num)!=0)
                {

                    if(m<n)
                    {
                        fclose(fp);
                        printf("ȷ���Ƿ�μӸû��(Y or N):");
                        getchar();
                        a=getchar();
                        if(a=='Y'||a=='y')
                        {
                            if((fp=fopen(filename,"a+"))==NULL) exit(0);
                            printf("1\n");
                            fprintf(fp,"%s\n",num);
                            printf("2\n");
                            fclose(fp);
                            strcpy(s2,num);
                            strcat(s2,"��Ż.txt");
                            strcpy(num,s2);
                            if((fp1=fopen(num,"a+"))==NULL)    exit(0);
                            fprintf(fp1,"%s\n",user);
                            fclose(fp1);
                            p->join++;
                            save(head);
                            Ledge_ment();
                            printf("\t\t\t�ɹ��μӸû!\n");
                            printf("���������ѡ��(0~8):");
                            scanf("%d",&l);
                            User_choice(l,user,pwd);
                        }
                        else
                        {
                            Ledge_ment();
                            printf("\t\t   ���ѷ����μӸû!\n");
                            printf("���������ѡ��(0~8):");
                            scanf("%d",&l);
                            User_choice(l,user,pwd);
                        }
                    }
                    else
                    {
                        Ledge_ment();
                        printf("\t\t�û��������������ѡ��μ�!\n");
                        printf("���������ѡ��(0~8):");
                        scanf("%d",&l);
                        User_choice(l,user,pwd);
                    }
                }
            }
            break;
        }
        if(p->next==NULL)
        {
            Ledge_ment();
            printf("\t\t    δ�ҵ�����Ҫ�μӵĻ!\n");
            printf("���������ѡ��(0~8):");
            scanf("%d",&l);
            User_choice(l,user,pwd);
        }
    }
}

//�����в��һ
int Search_activity1(char *user,char *pwd,char *temp)
{
    int a=0,l;
    struct activity_list * p1,*head;
    head=Read();
    p1=head;
    if(head==NULL)
    {
        Ledge_ment();
        printf("\t\t����δ�μӻ������ѡ��μӻ!\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
    }
    else
    {
        while(p1!= NULL)
        {
            if(strstr(p1->number,temp)!=NULL)
            {
                printf("\n");
                printf("���ţ�%s\n����ݣ�%s\n�������%d\n�ѲμӸû��������%d\n�Ҫ��%s\n����ڣ�%s\n������ߣ�%s\n",p1->number,p1->content,p1->count,p1->join,p1->demand,p1->time1,p1->Cname);
                printf("\n\n");
                return OK;
            }
            p1=p1->next;

        }
    }
    save(head);
}
//�鿴�μӵĻ������
void Look_and_Discuss_activity(char *user,char *pwd,char *filename)
{
    int l,a=0;
    FILE *fp,*fp1;
    char num[21],num1[21],discuss1[21];
    struct activity_list * p,*head;
    p=head;
    head=Read();
    if((fp=fopen(filename,"r"))==NULL)
    {
        Ledge_ment();
        printf("\t\t����δ�μӻ������ѡ��μӻ!\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
    }
    while(!(feof(fp)))
    {
        fscanf(fp,"%s\n",num);
        Search_activity1(user,pwd,num);
    }
    if(fclose(fp)) exit(0);
    if((fp=fopen(filename,"r"))==NULL) exit(0);
    printf("\n");
    printf("�������������۵Ļ��ţ�");
    scanf("%s",num1);
    while(!(feof(fp)))
    {
        fscanf(fp,"%s\n",num);
        if(strcmp(num,num1)==0) a++;

    }
    if(fclose(fp)) exit(0);
    if(a>0)
    {
        printf("�������������۵����ݣ�");
        scanf("%s",discuss1);
        if((fp1=fopen("�����.txt","a+"))==NULL) exit(0);
        fprintf(fp,"%s %s %s\n",num1,discuss1,user);
        if(fclose(fp1)) exit(0);
        Ledge_ment();
        printf("\t\t\t�ɹ����۸û��\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);

    }
    else
    {
        Ledge_ment();
        printf("\t\t����δ�μӸû������ѡ��μӸû��\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
    }

}
//�鿴�����۵Ļ����������
void Look_Discuss(char *user,char *pwd)
{
    int l;
    FILE *fp;
    char num[21],num1[21],discuss1[21];
    if((fp=fopen("�����.txt","r"))==NULL)
    {
        Ledge_ment();
        printf("\t\t\t���޻����!\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
    }
    while(!(feof(fp)))
    {
        fscanf(fp,"%s %s %s\n",num1,discuss1,user);
        {
            printf("\n");
            printf("���ţ�%s\n�������ݣ�%s\n������ߣ�%s\n",num1,discuss1,user);
            printf("\n");
        }

    }
    Ledge_ment();
    printf("\t\t ��ܰ��ʾ���ϻ���������!\n");
    printf("���������ѡ��(0~8):");
    scanf("%d",&l);
    User_choice(l,user,pwd);
    if(fclose(fp)) exit(0);
}
//�鿴�ѽ��������Ļ
void Look_Ended(char *user,char *pwd)
{
    FILE *fp,*fp1;
    struct activity_list * p,*head;
    int m,n,a=0,l;
    char *num1,joinname[100],s2[21];
    head=Read();
    p=head;
    if(head=NULL)
    {
        Ledge_ment();
        printf("\t\t\t���޻���ڣ�\n");
        printf("�������������ѡ��(0~8):");
        scanf("%d",&n);
        User_choice(n,user,pwd);
    }
    if((fp=fopen("ȫ���.txt","r"))==NULL)
    {
        Ledge_ment();
        printf("\t\t\t���޻���ڣ�\n");
        printf("�������������ѡ��(0~8):");
        scanf("%d",&n);
        User_choice(n,user,pwd);
    }
    while(!(feof(fp)))
    {
        fscanf(fp,"%30s%30s%30d%30d%30s%30s%30s",p->number,p->content,&p->count,&p->join,p->demand,p->time1,p->Cname);
        m=p->join;
        n=p->count;
        if(m==n)
        {
            printf("\n");
            printf("���ţ�%s\n����ݣ�%s\n�������%d\n�ѲμӸû��������%d\n�Ҫ��%s\n����ڣ�%s\n������ߣ�%s\n",p->number,p->content,p->count,p->join,p->demand,p->time1,p->Cname);
            num1=p->number;
            strcpy(s2,num1);
            strcat(s2,"��Ż.txt");
            strcpy(num1,s2);
            printf("��μ��ߣ�");
            if((fp1=fopen(num1,"r"))==NULL) exit(0);
            while(!(feof(fp1)))
            {
                fscanf(fp1,"%s ",joinname);
                printf("%s ",joinname);
            }
            if(fclose(fp1)) exit(0);
            printf("\n");
            a++;
        }

    }
    if(a==0)
    {
        printf("\n");
        Ledge_ment();
        printf("\t\tȫ��������������������������Ļ!\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
    }
    else
    {
        Ledge_ment();
        printf("\t\t��ܰ��ʾ���ϻ����ɼ����������Ļ��\n");
        printf("���������ѡ��(0~8):");
        scanf("%d",&l);
        User_choice(l,user,pwd);
    }
    if(fclose(fp)) exit(0);
}


//�û�ѡ��
void User_choice(int l,char *user,char *pwd)
{
    struct activity_list *head;
    head=Read();
    int n,k;
    k=l;
    while(k<0||k>8)
    {
        printf("��������!����������!");
        scanf("%d",&k);
    }
    switch(k)
    {
    case 1:
        Create_activity(user,pwd);
        break;
    case 2:
        Search_activity(user,pwd,head);
        break;
    case 3:
        Delete_activity(user,pwd);
        break;
    case 4:
        Join_activity(user,pwd,filename);
        break;
    case 5:
        Look_and_Discuss_activity(user,pwd,filename);
        break;
    case 6:
        Look_Discuss(user,pwd);
        break;
    case 7:
        Look_Ended(user,pwd);
        break;

    case 8:
        system("cls");
        printf("\t\t================�����================\n");
        printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
        printf("\t\t.                                      .\n");
        printf("\t\t*\t   1.ע�� 2.��¼ 0.�˳�        *\n");
        printf("\t\t.                                      .\n");
        printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
        printf("\t\t========================================\n");
        printf("���������ѡ��:");
        scanf("%d",&n);
        while(n>2||n<0)
        {
            printf("\n");
            printf("��������!����������!\n");
            printf("\n");
            scanf("%d",&n);
        }
        switch(n)
        {
        case 1:
            Register();
            break;
        case 2:
            Login();
            break;
        case 0:
            exit(0);

        }
        break;
    case 0:
        exit(0);
        break;

    }
}

//�û���¼
void Login()
{
    char user[21],s2[26],user1[21],ch;
    FILE *fp;
    char *pwd,pwd1[15];
    int j=1,n,l;
    printf("�������û���:\n");
    scanf("%s",&user);
    pwd=Get_password("����������(<=14):");         //��ȡ�û���������

    if((fp=fopen("��½��Ϣ.txt","r"))==NULL)
    {
        system("cls");
        printf("\t\t �����û���ע�ᣬ����ѡ����ע���ٵ�¼��\n");
        printf("\t\t================�����================\n");
        printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
        printf("\t\t.                                      .\n");
        printf("\t\t*\t   1.ע�� 2.��¼ 0.�˳�        *\n");
        printf("\t\t.                                      .\n");
        printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
        printf("\t\t========================================\n");
        printf("���������ѡ��:");
        scanf("%d",&n);
        switch(n)
        {
        case 1:
            Register();
            break;
        case 2:
            Login();
            break;
        case 0:
            exit(0);
        }
    }

    while(!(feof(fp)))
    {
        fscanf(fp,"%s%s",user1,pwd1);
        if(strcmp(user1,user)==0)  break;   //�ж��û����Ƿ����
    }
    if(!feof(fp))
    {
        while(strcmp(pwd,pwd1)!=0)
        {

            printf("�������!\n");
            pwd=Get_password("����������:");
            j++;
            //�ж��û����������Ƿ�ƥ��
            if(j>3) break;
        }
        if(j>=3)
        {
            printf("��������������,�Ժ��¼!");
            exit(0);
        }
        else
        {
            strcpy(s2,user);       //��¼�ɹ������û������ļ�����
            strcat(s2,".txt");
            strcpy(filename,s2);
            if((fp=fopen(filename,"a"))==NULL)
            {
                printf("File open error!\n");
                exit(0);
            }
            if(fclose(fp))
            {
                printf("Can not close the file!\n");
                exit(0);
            }
            system("cls");
            Ledge_ment();
            printf("���������ѡ��(0~8):");
            scanf("%d",&l);
            User_choice(l,user,pwd);                            //��¼�ɹ��������������
        }
    }
    else
    {
        system("cls");
        printf("\t\t\t     ���û���������!\n");
        printf("\t\t================�����================\n");
        printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
        printf("\t\t.                                      .\n");
        printf("\t\t*\t   1.ע�� 2.��¼ 0.�˳�        *\n");
        printf("\t\t.                                      .\n");
        printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
        printf("\t\t========================================\n");
        printf("���������ѡ��:");
        scanf("%d",&n);
        switch(n)
        {
        case 1:
            Register();
            break;
        case 2:
            Login();
            break;
        case 0:
            exit(0);
        }
    }

    if(fclose(fp)) exit(0);

}

//ע���û�
void Register()
{
    char user[21],s1[26];
    FILE *fp;
    int i,n;
    char *pwd1,pwd2[15];
    do
    {
        printf("�������û���(<=20):\n");                //�ж�������û����Ƿ񳬹��涨���������Ϸ���������
        scanf("%s",user);
        while(strlen(user)>20)
        {
            printf("�û��������涨����������������:");
            scanf("%s",&user);
        }
    }
    while(!(Judge_user(user)));                       //���� Judge_user()�������ж��û����Ƿ���ڣ�������������

    pwd1=Get_password("����������:");                  //�ж϶�������������Ƿ���ͬ ����ͬ��������
    for(i=0; *pwd1!='\0'; i++)
    {
        pwd2[i]=*pwd1;
        pwd1++;
    }
    pwd2[i]='\0';
    pwd1=Get_password("��ȷ������:");
    while(strcmp(pwd2,pwd1)!=0)
    {
        pwd1=Get_password("���벻һ��,����������(<=14):");
        for(i=0; *pwd1!='\0'; i++)
        {
            pwd2[i]=*pwd1;
            pwd1++;
        }
        pwd2[i]='\0';
        pwd1=Get_password("��ȷ������(<=14):");
    }
    if((fp=fopen("��½��Ϣ.txt","a"))==NULL)  	exit(0);

    fprintf(fp,"%s %s\n",user,pwd1);
    if(fclose(fp)) 	exit(0);

    system("cls");                                 //�����ɹ������������ش�������¼����
    printf("\t\t\t\t�����ɹ���\n");
    printf("\t\t================�����================\n");
    printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
    printf("\t\t.                                      .\n");
    printf("\t\t*\t   1.ע�� 2.��¼ 0.�˳�        *\n");
    printf("\t\t.                                      .\n");
    printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
    printf("\t\t========================================\n");
    printf("���������ѡ��:");
    scanf("%d",&n);
    switch(n)
    {
    case 1:
        Register();
        break;
    case 2:
        Login();
        break;
    case 0:
        exit(0);
    }
}


//������
int main()
{
    int n;
    system("Color 3f");
    printf("\t\t================�����================\n");
    printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
    printf("\t\t.                                      .\n");
    printf("\t\t*\t   1.ע�� 2.��¼ 0.�˳�        *\n");
    printf("\t\t.                                      .\n");
    printf("\t\t*��*��*��*��*��*��*��*��*��*��*��*��*��*\n");
    printf("\t\t========================================\n");
    printf("���������ѡ��:");
    scanf("%d",&n);
    while(n>2||n<0)
    {
        printf("\n");
        printf("��������!����������!\n");
        printf("\n");
        scanf("%d",&n);
    }
    switch(n)
    {
    case 1:
        Register();
        break;
    case 2:
        Login();
        break;
    case 0:
        exit(0);

    }
}
