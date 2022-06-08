#include <stdlib.h>
#include <stdio.h>
//#include <conio.h>
#include "math.h"
//#define m 1       
struct Date                     /*���ڽṹ*/
{ 
	int m_nYear;                /*��*/
    int m_nMonth;               /*��*/    
    int m_nDay;                 /*��*/   
};

struct Reader                   /*���߽ṹ*/
{
	char         num[20];       /*����֤��*/
	struct Date  bro;           /*���ʱ��*/     
	struct Date  back;          /*�黹ʱ��*/        
};

struct  Book                     /*�鱾�ṹ*/
{
	int  m_iBook_Number;         /*��Ӧ�鱾��*/           
	char m_strTitle[150];        /*����*/
	char m_strWroter[150];       /*����*/   
	int  m_nMoreNum;             /*��ǰ�ڼܲ���*/    
	int  m_nTotalHoldNum;        /*�ݲز���*/      
	char m_strComment[300];      /*ͼ����*/   
	struct Reader reader[200]; 
};
struct Info                      /*������Ϣ�ṹ*/
{
	struct Info *m_pParentPoint; /*ǰ�����*/      
	struct Book *m_pBookInfo;    /*��Ӧ�鱾����Ϣ*/    
	struct Info *m_pSun;         /*��̽��*/
	
};

struct Book *InputNode();
struct Info *Search(struct Info *bth,int x,int *k,int *flag);/*����ͼ��*/
struct Info *Insert_BookInfo(struct Info *bth);/*ͼ���ϼ�*/
struct Info *Delete_BookInfo(struct Info *bth);/*ͼ���¼�*/
void   Output_BookInfo(struct Info *bth);/*��ӡ����鱾��Ϣ*/
void   Borrow_TheBook(struct Info *bth);/*ͼ�����*/
void   TurnBack_TheBook(struct Info *bth);/*ͼ��黹*/
char   Select_Menu();/*ͼ��ݹ���ϵͳ���˵�*/
struct Info *Search(struct Info *bth,int x,int *k,int *flag)
{
	struct Info *p=NULL;
	/*��ǰ����ָ��*/
	p=bth; /*ÿ�β�ѯǰ,������ָ��ָ��˫������ͷ�����*/
	*flag=0; /*�Ƿ���ҵ�ָ������ŵı�־,��ʼ����Ϊ0*/
	while(p)
	{
		if(p->m_pBookInfo->m_iBook_Number==x)
		{
			/*�ҵ���ͬ�����,���ҵ��ı�־*/
			*flag = 1;
			return p;
		}
		else
		{
			/*δ�ҵ���ͬ�����,��δ�ҵ���־*/
			*flag = 0;
		}
		if(p->m_pSun!=NULL)
		{
			p = p->m_pSun;
			/*û��˫�������β��ʱ,����ƶ���ǰָ��*/
		}
		else
		{
			break;/*��������β��,����ѭ��*/
		}
		
	}

	return bth;
}
struct Book *InputNode()
{
	struct Book *p=NULL;
	int i;
	p=(struct Book *)malloc(sizeof(struct Book));   /*�����ڴ�*/
	system("cls");/*����*/
	fflush(stdin);  /*�����ǰ������*/
	printf("\n\t����������: ");   
	gets(p->m_strTitle);/*�Ӽ���ȡ������*/
	printf("\n\t����������: ");
	gets(p->m_strWroter);/*�Ӽ���ȡ�ó�����*/
	printf("\n\t�����뵱ǰ�ڼ�����: ");
	scanf("%d",&p->m_nMoreNum);/*�Ӽ���ȡ�õ�ǰ�ڼ�����*/
	printf("\n\t������������: ");
	scanf("%d",&p->m_nTotalHoldNum);/*�Ӽ���ȡ�õ�ǰ�������*/
	fflush(stdin);
	printf("\n\t������ͼ����: ");/*�Ӽ���ȡ�ø�ͼ�����ݼ�Ҫ����*/
	gets(p->m_strComment);
	/*���ϴ���������豸ȡ��Ҫ�����Ϣ*/
	for(i=0;i<20;i++)
		(p->reader[i]).num[0]='\0';/*��ʼ������ṹ��Ա����ض���ָ������Ϊ��*/
	return(p);  /*���سɹ������һ��ͼ����Ϣ*/
}
struct Info *Insert_BookInfo(struct Info *bth)
{
	int flag,j,k,t;
	int y,x,z;
	struct Info *p=NULL,*q=NULL,*u=NULL,*s=NULL;
	struct Book *r=NULL,*l=NULL;
	system("cls");/*����*/
	printf("\n\t�����������ϼܵ�ͼ����: ");
	scanf("%d",&x);/*ȡ���*/  
	q=Search(bth,x,&k,&flag);/*�����ϼܵ����Ƿ��Ѿ��ϼ�,�����Ѿ��ҵ��������Ϣ*/
	if(flag==1)   
    {/*���ҳɹ������ڴ���*/
		printf("\n\t��ǰ�������ͼ��%d��,����������һ��<<%s>>��?(y/n)\n",q->m_pBookInfo->m_nTotalHoldNum,q->m_pBookInfo->m_strTitle);
		z=getch();
		if(z=='y'||z=='Y')       
		{/*ȷ���ϼ���һ����Ʒ*/
			printf("\n\t���ݴ���һ����: %d ��",q->m_pBookInfo->m_nTotalHoldNum);
			printf("\n\t������: %d ����ͼ�������δ���.",q->m_pBookInfo->m_nMoreNum);
			q->m_pBookInfo->m_nTotalHoldNum++;
			q->m_pBookInfo->m_nMoreNum++;  
			printf("\n\t�ϼܺ�һ����:  %d ��",q->m_pBookInfo->m_nTotalHoldNum);
			printf("\n\t�ϼܺ�ǰ��:  %d ����ͼ�����.",q->m_pBookInfo->m_nMoreNum);
		}
		return(bth); 
    }
	r=InputNode(bth); /*�ɹ����������Ϣ,ָ��r��Ÿող�������*/
	if(bth==NULL) 
    {
		/*ָ��bthΪ��ʱ����ʾ��ǰ����Ϊ�գ���ʱ��Ҫ��������������ͷ�ڴ����*/
		bth=p=(struct Info *)malloc(sizeof(struct Info));/*�����ڴ�*/
		r->m_iBook_Number = x;/*����Ŵ��������Ϣ�ṹ��*/
		p->m_pParentPoint= NULL;/*ǰ������ÿ�*/
		p->m_pSun=NULL;/*��̽���ÿ�*/
		p->m_pBookInfo=r;
		return(p); /*�����³ɹ������������*/
    }
	else
	{
		/*˵���Ѿ���ͷָ��,���ڴ˿�ʼ�����²���Ľṹ��ָ��*/
		p=NULL; 
		p=bth;
		while(p->m_pSun!=NULL)
		{
			p = p->m_pSun;/*����̽�㲻Ϊ��ʱ,��ʾ��δ������β��*/
		}
		/*��ѭ��������,pָ��ľ������һ�����*/

		q=(struct Info *)malloc(sizeof(struct Info));/*�����ڴ�*/
		r->m_iBook_Number = x;/*����Ŵ��������Ϣ�ṹ��*/
		p->m_pSun = q;        /*˫�������ǰ�����̽������*/
		q->m_pParentPoint= p;/*ǰ�������Ϊp*/
		q->m_pSun=NULL;/*��̽���ÿ�,�൱�ڵ��߽ӵ�*/
		q->m_pBookInfo=r;/*ָ���²����ͼ�����Ϣ�ṹ��*/
	}
	return(bth);  
}
struct Info *Delete_BookInfo(struct Info *bth)
{
	int flag,j,k,t;
	int x,y;
	struct Info  *u=NULL,*s=NULL,*p=NULL,*q=NULL;
	struct Book  *Bookinfo=NULL;
		
	struct Info *BookLeftPoint=NULL;/*ǰ�����*/
	struct Info *BookRightPoint = NULL;/*��̽��*/
	system("cls");/*����*/
	printf("\n\t�����������¼ܵ������: ");
	scanf("%d",&x);/*��������*/
	q=Search(bth,x,&k,&flag);/*����ָ�������Ƿ����*/       
	if(flag==0) 
	{ /*ͼ�鲻������,ֱ�������Ϣ������*/
		printf("\n\t���ͼ�鲻����!\n"); 
		return(bth);
	} 
	else
	{
		if(q==NULL)
		{
			printf("δ֪����");
			return bth;/*ȷ����ǰ����ָ������Ч��,��ֹ���ַǷ�����*/
		}
		else
		{
			Bookinfo=q->m_pBookInfo;
			printf("\n\t���¼ܵ������Ϣ: ");   
			printf("\n\t����:             %s",Bookinfo->m_strTitle);    
			printf("\n\t����:            %s",Bookinfo->m_strWroter);
			printf("\n\t��ǰ�ڼ�����:     %d",Bookinfo->m_nMoreNum);
			printf("\n\t�������:       %d",Bookinfo->m_nTotalHoldNum);
			printf("\n\tͼ����: %s\n",Bookinfo->m_strComment);
			/*ɾ��ָ���������Ϣ��˼·:�赱ǰ�ҵ��������еĽ����q,����ǰ��Ϊq-1,���Ϊq+1,
			��,ֻ��Ҫ����������:
			1.��Ҫɾ���Ľ��ĺ�̽���ǰ��ָ����ָ��Ҫɾ���Ľ���ǰ�����
			2.��Ҫɾ���Ľ���ǰ�����ĺ��ָ����ָ��Ҫɾ���Ľ��ĺ�̽��
			3.�ͷ�Ҫɾ���Ľ��������Ϣ����ڴ�,�ͷ�Ҫɾ���Ľ����ڴ�
			��Ҫע������������:Ҫɾ���Ľ�����׽���β���ʱ,��Ҫ�ֱ��жϴ���*/
			if(q->m_pParentPoint!=NULL && q->m_pSun!=NULL)
			{
				/*���������м�Ľ��*/
				BookLeftPoint = q->m_pParentPoint;/*Ҫɾ���Ľ���ǰ��ָ�򸳸�ǰ�����ָ�����*/
				BookRightPoint = q->m_pSun;/*Ҫɾ���Ľ��ĺ��ָ�򸳸���̽���ָ�����*/
				BookLeftPoint->m_pSun = BookRightPoint;/*����̽��ָ��ָ��ĵ�ַ��Ϊǰ��������º����*/
				BookRightPoint->m_pParentPoint = BookLeftPoint;/*����̽��ָ���ǰ�����趨ΪҪɾ���Ľ���ǰ�����*/
				q->m_pParentPoint = NULL;
				q->m_pSun = NULL;
				free(q->m_pBookInfo);/*�Ƚ������Ϣ�ṹ����ڴ��ͷ�*/
				q->m_pBookInfo = NULL;/*ʹָ��ָ��ȫ��ַ*/
				free(q);/*��Ҫɾ���Ľ軹����Ϣ�ṹ��ָ��ʹ�õ��ڴ�ռ��ͷ�*/
				q = NULL;/*Ҫϰ�߽���̬������ڴ���ʹ�ú�̬�ͷ�,����ָ����ָ���*/
				return bth;/*�����׽��*/
			}
			else if(q->m_pParentPoint==NULL)
			{
				/*�׽���ǰ��Ϊ��,���ﴦ���׽��ɾ������*/
				if(q->m_pSun==NULL)
				{/*ǰ��ָ�����Ϊ��ʱ,˵��ֻ��һ�����,��ʱֻ��Ҫ���˽��ɾ��*/
					free(q->m_pBookInfo);
					q->m_pBookInfo = NULL;
					free(q);
					q = NULL;
					return q;
				}
				bth = q->m_pSun;
				bth->m_pParentPoint = NULL;
				
				/*Ҫɾ���Ľ��ĺ��ָ�򸳸���̽���ָ�����*/
				BookRightPoint = q;
				BookRightPoint->m_pParentPoint = NULL;/*��������ָ���׽��ĺ��ָ���ǰ��ָ������Ϊ��,�������µ��׽��*/
				BookRightPoint->m_pSun = NULL;/*��������ָ���׽��ĺ��ָ���ǰ��ָ������Ϊ��,�������µ��׽��*/
				
				free(BookRightPoint->m_pBookInfo);/*�Ƚ������Ϣ�ṹ����ڴ��ͷ�*/
				BookRightPoint->m_pBookInfo = NULL;/*ʹָ��ָ��ȫ��ַ*/
				free(BookRightPoint);/*��Ҫɾ���Ľ軹����Ϣ�ṹ��ָ��ʹ�õ��ڴ�ռ��ͷ�*/
				BookRightPoint = NULL;/*Ҫϰ�߽���̬������ڴ���ʹ�ú�̬�ͷ�,����ָ����ָ���*/
				
				return bth;/*�����׽��*/
			}
			else if (q->m_pSun==NULL)
			{
				/*β���ĺ�̽��Ϊ��,���ﴦ��β����ɾ������*/

				BookLeftPoint = q->m_pParentPoint; /*��Ҫɾ���Ľ�㼴β����ǰ���򱣴浽ǰ��ָ�������*/
				BookLeftPoint->m_pSun = NULL;/*��Ҫɾ���Ľ���ǰ�����������Ͽ�,ǰ�������Ϊ�µ�β���*/
				q->m_pParentPoint = NULL;
				free(q->m_pBookInfo);/*�Ƚ������Ϣ�ṹ����ڴ��ͷ�*/
				q->m_pBookInfo = NULL;/*ʹָ��ָ��ȫ��ַ*/
				free(q);/*��Ҫɾ���Ľ軹����Ϣ�ṹ��ָ��ʹ�õ��ڴ�ռ��ͷ�*/
				q = NULL;/*Ҫϰ�߽���̬������ڴ���ʹ�ú�̬�ͷ�,����ָ����ָ���*/
				return bth;/*�����׽��*/
			}
		}
	}
}

void Output_BookInfo(struct Info *bth)
{
	struct Info *q=NULL;
	struct Book *p=NULL;
	int k=0;
	int x=0;
	int flag=0;
	system("cls");
	printf("\n\t������������ҵ������: ");
	scanf("%d",&x);
	q=Search(bth,x,&k,&flag);    
	if(flag==1)
	{
		p=q->m_pBookInfo;
		printf("\n\t����:             %s",p->m_strTitle);    
		printf("\n\t����:            %s",p->m_strWroter);
		printf("\n\t��ǰ�ڼ�����:     %d",p->m_nMoreNum);
		printf("\n\t�������:       %d",p->m_nTotalHoldNum);
		printf("\n\tͼ����: %s\n",p->m_strComment);
	}
	else printf("\n\t���ͼ�鲻����!");
}
void Borrow_TheBook(struct Info *bth)
{
	struct Info *q=NULL;
	struct Book *p=NULL;
	int i,k, x, flag,t;
	system("cls");/*����*/
	printf("\n\t�����������������: ");/*��ӡ��Ϣ*/
	scanf("%d",&x);/*��������*/
	q=Search(bth,x,&k,&flag);  /*�������*/
	if(flag==1)  
	{
		p=q->m_pBookInfo;
		printf("\n\t������ͼ�� ?(y/n)");
		printf("\n\t����:             %s",p->m_strTitle);
		printf("\n\t����:            %s",p->m_strWroter);
		printf("\n\t��ǰ�ڼ�����:     %d",p->m_nMoreNum);
		printf("\n\t�������:       %d",p->m_nTotalHoldNum);
		printf("\n\tͼ����: %s\n",p->m_strComment);
		t=getch();
		if(t=='y'||t=='Y')
		{/*ȷ�Ͻ����ͼ��*/
			if( (p->m_nMoreNum)==0) printf("\n\t�Բ���,ͼ���Ѿ�ȫ�����...");
			else
			{
				system("cls");
				for(i=0;i<20;i++) if( (p->reader[i]).num[0]=='\0') break;
				printf("\n\t���������֤��: ");  
				scanf("%s",(p->reader[i]).num);
				printf("\n\t��������������: "); 
				printf("\n\t��:  ");
				scanf("%d",&((p->reader[i]).bro.m_nYear));
				printf("\t��: ");
				scanf("%d",&((p->reader[i]).bro.m_nMonth));
				printf("\t��:   ");
				scanf("%d",&((p->reader[i]).bro.m_nDay));
				
				printf("\n\t������黹����: ");
				printf("\n\t��:  ");
				scanf("%d",&((p->reader[i]).back.m_nYear));
				printf("\t��: ");
				scanf("%d",&((p->reader[i]).back.m_nMonth));
				printf("\t��:   ");
				scanf("%d",&((p->reader[i]).back.m_nDay));
				
				p->m_nMoreNum--;       
				printf("\n\t�ɹ��赽��ͼ��.");}
		}
		
	}
	else printf("\n\t���ͼ�鲻����!"); 
}
void TurnBack_TheBook(struct Info *bth)
{
	struct Info *q=NULL;
	struct Book *p=NULL;
	int i,k, x, flag,t,j;
	int year,month,day,d;
	float pay;
	char temp[20];
	system("cls");/*����*/
	printf("\n\t������黹�������: ");
	scanf("%d",&x);
	q=Search(bth,x,&k,&flag); /*�������*/   
	if(flag==1)
	{/*�ҵ���ͼ��*/
		p=q->m_pBookInfo;
		printf("\n\t����黹���ͼ�� ?(y/n)");
		printf("\n\t����:             %s",p->m_strTitle);
		printf("\n\t����:            %s",p->m_strWroter);
		printf("\n\t��ǰ�ڼ�����:     %d",p->m_nMoreNum);
		printf("\n\t�������:       %d",p->m_nTotalHoldNum);
		printf("\n\tͼ����: %s\n",p->m_strComment);
		t=getch();/*����ѡ��*/
		if(t=='y'||t=='Y')
		{/*ȷ�Ϲ黹���ͼ��*/
			if( (p->m_nMoreNum) >=(p->m_nTotalHoldNum) )
				printf("\n\t�����ϼ�һ��ͼ���� ??\n");
			else
			{
				system("cls");
				printf("\n\t���������֤��: ");
				scanf("%s",temp);
				j=0;
				for(i=0;i<20;i++)
				{
					if(! (strcmp(temp,(p->reader[i]).num))) {j=1;break;} 
				}
				if(j==0) {printf("\n\t�㲻�ܽ����ͼ�顣");return;}  
				printf("\n\t������:");   
				printf("\n\t��:  ");
				scanf("%d",&year);
				printf("\t��: ");
				scanf("%d",&month);
				printf("\t��:   ");
				scanf("%d",&day);
				
				
				d=0;
				if(year<(p->reader[i]).back.m_nYear) d=1; 
				if(year<=(p->reader[i]).back.m_nYear && month<(p->reader[i]).back.m_nMonth) d=1;
				if(year<=(p->reader[i]).back.m_nYear && month<=(p->reader[i]).back.m_nMonth && day<(p->reader[i]).back.m_nDay) d=1;
				if(d==0)
				{/*�����������ڣ��ڴ˻���*/
					system("cls");
					pay=(year-(p->reader[i]).back.m_nYear)*365+(month-(p->reader[i]).back.m_nMonth)*30+(day-(p->reader[i]).back.m_nDay);
					printf("\n\t��Ľ��������ǣ� %d-%d-%d",(p->reader[i]).bro.m_nYear,(p->reader[i]).bro.m_nMonth,(p->reader[i]).bro.m_nDay);  
					printf("\n\t��Ļ��������ǣ� %d-%d-%d֮ǰ",(p->reader[i]).back.m_nYear,(p->reader[i]).back.m_nMonth,(p->reader[i]).back.m_nDay);
					printf("\n\t������                   %d-%d-%d",year,month,day);
					printf("\n\n\t����㳬�����ڣ�");
					printf("\n\tӦ��֧��%2.1f Ԫ����.",0.1*pay); 
				}
				(p->reader[i]).num[0]='\0'; 
				p->m_nMoreNum++;  
				printf("\n\t���Ѿ��黹�����ͼ��.");
			}
		}
		
	}
	else printf("\n\t�㲻�ܹ黹�����ڵ�һ��ͼ��!!!");  
	
}

char Select_Menu()
{/*���˵���ʾ����*/
	system("cls");
    printf("/******************************************\\\n");
    printf("*                                          *\n");
    printf("*        ͼ  ��  ��  ��  ��  ϵ  ͳ        *\n");
    printf("*                  ���˵�                  *\n");
    printf("*                                          *\n");
    printf("*               1. ͼ���ϼ�                *\n");
    printf("*               2. ͼ���¼�                *\n");
    printf("*               3. ����ͼ��                *\n");
    printf("*               4. ͼ�����                *\n");
    printf("*               5. ͼ��黹                *\n");
    printf("*               6. �˳�ϵͳ                *\n"); 
    printf("*                                          *\n");
    printf("*             ��ѡ��˵��(1~6)          *\n");
    printf("\\******************************************/\n");
	return getch();
}


void main()
{
	char c,t;
	int flag,p=1;
	struct Info *bth=NULL;
	while(1)
	{
		c=Select_Menu(); 
	    printf("��ѡ���ˣ�%c",c);
		getch();
		switch(c)  
		{
		case '1': 
			bth=Insert_BookInfo(bth);/*ͼ���ϼ�*/
            break;
		case '2': 
			bth=Delete_BookInfo(bth);/*ͼ���¼�*/
            break;
		case '3': Output_BookInfo(bth);/*����ͼ��*/
            break;
		case '4': Borrow_TheBook(bth);/*ͼ�����*/
            break;
		case '5': TurnBack_TheBook(bth);/*ͼ��黹*/
            break;
		case '6':
		case '0': system("cls");
            printf("\n\t�����˳�ϵͳ ?(y/n)");
            t=getch();
            if(t=='y'||t=='Y') exit(0);
            break;
		}
		printf("\n\t��������������˵�....");
		getch();
	}
} 

