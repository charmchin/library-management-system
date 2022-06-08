#include <stdlib.h>
#include <stdio.h>
//#include <conio.h>
#include "math.h"
//#define m 1       
struct Date                     /*日期结构*/
{ 
	int m_nYear;                /*年*/
    int m_nMonth;               /*月*/    
    int m_nDay;                 /*日*/   
};

struct Reader                   /*读者结构*/
{
	char         num[20];       /*借书证号*/
	struct Date  bro;           /*借出时间*/     
	struct Date  back;          /*归还时间*/        
};

struct  Book                     /*书本结构*/
{
	int  m_iBook_Number;         /*对应书本号*/           
	char m_strTitle[150];        /*书名*/
	char m_strWroter[150];       /*作者*/   
	int  m_nMoreNum;             /*当前在架册数*/    
	int  m_nTotalHoldNum;        /*馆藏册数*/      
	char m_strComment[300];      /*图书简介*/   
	struct Reader reader[200]; 
};
struct Info                      /*借书信息结构*/
{
	struct Info *m_pParentPoint; /*前驱结点*/      
	struct Book *m_pBookInfo;    /*对应书本的信息*/    
	struct Info *m_pSun;         /*后继结点*/
	
};

struct Book *InputNode();
struct Info *Search(struct Info *bth,int x,int *k,int *flag);/*查找图书*/
struct Info *Insert_BookInfo(struct Info *bth);/*图书上架*/
struct Info *Delete_BookInfo(struct Info *bth);/*图书下架*/
void   Output_BookInfo(struct Info *bth);/*打印输出书本信息*/
void   Borrow_TheBook(struct Info *bth);/*图书出借*/
void   TurnBack_TheBook(struct Info *bth);/*图书归还*/
char   Select_Menu();/*图书馆管理系统主菜单*/
struct Info *Search(struct Info *bth,int x,int *k,int *flag)
{
	struct Info *p=NULL;
	/*当前工作指针*/
	p=bth; /*每次查询前,将工作指针指向双向链表头部结点*/
	*flag=0; /*是否查找到指定书个号的标志,初始化置为0*/
	while(p)
	{
		if(p->m_pBookInfo->m_iBook_Number==x)
		{
			/*找到相同的书号,置找到的标志*/
			*flag = 1;
			return p;
		}
		else
		{
			/*未找到相同的书号,置未找到标志*/
			*flag = 0;
		}
		if(p->m_pSun!=NULL)
		{
			p = p->m_pSun;
			/*没到双向链表的尾部时,向后移动当前指针*/
		}
		else
		{
			break;/*到达链表尾部,跳出循环*/
		}
		
	}

	return bth;
}
struct Book *InputNode()
{
	struct Book *p=NULL;
	int i;
	p=(struct Book *)malloc(sizeof(struct Book));   /*分配内存*/
	system("cls");/*清屏*/
	fflush(stdin);  /*清除以前的输入*/
	printf("\n\t请输入书名: ");   
	gets(p->m_strTitle);/*从键盘取得书名*/
	printf("\n\t请输入作者: ");
	gets(p->m_strWroter);/*从键盘取得厂家名*/
	printf("\n\t请输入当前在架数量: ");
	scanf("%d",&p->m_nMoreNum);/*从键盘取得当前在架数量*/
	printf("\n\t请输入库存数量: ");
	scanf("%d",&p->m_nTotalHoldNum);/*从键盘取得当前库存数量*/
	fflush(stdin);
	printf("\n\t请输入图书简介: ");/*从键盘取得个图书内容简要介绍*/
	gets(p->m_strComment);
	/*以上从输入输出设备取得要求的信息*/
	for(i=0;i<20;i++)
		(p->reader[i]).num[0]='\0';/*初始化书个结构成员的相关读者指针内容为空*/
	return(p);  /*返回成功插入的一个图书信息*/
}
struct Info *Insert_BookInfo(struct Info *bth)
{
	int flag,j,k,t;
	int y,x,z;
	struct Info *p=NULL,*q=NULL,*u=NULL,*s=NULL;
	struct Book *r=NULL,*l=NULL;
	system("cls");/*清屏*/
	printf("\n\t请输入你想上架的图书编号: ");
	scanf("%d",&x);/*取书号*/  
	q=Search(bth,x,&k,&flag);/*查找上架的书是否已经上架,返回已经找到的书的信息*/
	if(flag==1)   
    {/*查找成功，存在此书*/
		printf("\n\t当前存在这个图书%d个,您想再增加一个<<%s>>书?(y/n)\n",q->m_pBookInfo->m_nTotalHoldNum,q->m_pBookInfo->m_strTitle);
		z=getch();
		if(z=='y'||z=='Y')       
		{/*确认上架另一个商品*/
			printf("\n\t个馆此书一共有: %d 个",q->m_pBookInfo->m_nTotalHoldNum);
			printf("\n\t并且有: %d 个在图书馆中内未借出.",q->m_pBookInfo->m_nMoreNum);
			q->m_pBookInfo->m_nTotalHoldNum++;
			q->m_pBookInfo->m_nMoreNum++;  
			printf("\n\t上架后一共有:  %d 个",q->m_pBookInfo->m_nTotalHoldNum);
			printf("\n\t上架后当前有:  %d 个在图书馆中.",q->m_pBookInfo->m_nMoreNum);
		}
		return(bth); 
    }
	r=InputNode(bth); /*成功插入书的信息,指针r存放刚刚插入的书个*/
	if(bth==NULL) 
    {
		/*指针bth为空时，表示当前链表为空，此时需要单独处理，即链表头内存分配*/
		bth=p=(struct Info *)malloc(sizeof(struct Info));/*申请内存*/
		r->m_iBook_Number = x;/*将书号存入书的信息结构体*/
		p->m_pParentPoint= NULL;/*前驱结点置空*/
		p->m_pSun=NULL;/*后继结点置空*/
		p->m_pBookInfo=r;
		return(p); /*返回新成功插入的书个结点*/
    }
	else
	{
		/*说明已经有头指针,则在此开始处理新插入的结构体指针*/
		p=NULL; 
		p=bth;
		while(p->m_pSun!=NULL)
		{
			p = p->m_pSun;/*当后继结点不为空时,表示还未到链表尾部*/
		}
		/*当循环结束后,p指向的就是最后一个结点*/

		q=(struct Info *)malloc(sizeof(struct Info));/*申请内存*/
		r->m_iBook_Number = x;/*将书号存入书的信息结构体*/
		p->m_pSun = q;        /*双向链表的前驱与后继结点链接*/
		q->m_pParentPoint= p;/*前驱结点置为p*/
		q->m_pSun=NULL;/*后继结点置空,相当于电线接地*/
		q->m_pBookInfo=r;/*指向新插入的图书的信息结构体*/
	}
	return(bth);  
}
struct Info *Delete_BookInfo(struct Info *bth)
{
	int flag,j,k,t;
	int x,y;
	struct Info  *u=NULL,*s=NULL,*p=NULL,*q=NULL;
	struct Book  *Bookinfo=NULL;
		
	struct Info *BookLeftPoint=NULL;/*前驱结点*/
	struct Info *BookRightPoint = NULL;/*后继结点*/
	system("cls");/*清屏*/
	printf("\n\t请输入你想下架的书个号: ");
	scanf("%d",&x);/*接受输入*/
	q=Search(bth,x,&k,&flag);/*查找指定的书是否存在*/       
	if(flag==0) 
	{ /*图书不存在是,直接输出消息并返回*/
		printf("\n\t这个图书不存在!\n"); 
		return(bth);
	} 
	else
	{
		if(q==NULL)
		{
			printf("未知错误");
			return bth;/*确保当前工作指针是有效的,防止出现非法操作*/
		}
		else
		{
			Bookinfo=q->m_pBookInfo;
			printf("\n\t想下架的书的信息: ");   
			printf("\n\t书名:             %s",Bookinfo->m_strTitle);    
			printf("\n\t作者:            %s",Bookinfo->m_strWroter);
			printf("\n\t当前在架数量:     %d",Bookinfo->m_nMoreNum);
			printf("\n\t库存数量:       %d",Bookinfo->m_nTotalHoldNum);
			printf("\n\t图书简介: %s\n",Bookinfo->m_strComment);
			/*删除指定的书的信息的思路:设当前找到的链表中的结点是q,它的前驱为q-1,后继为q+1,
			则,只需要作三部操作:
			1.将要删除的结点的后继结点的前驱指针域指向要删除的结点的前驱结点
			2.将要删除的结点的前驱结点的后继指针域指向要删除的结点的后继结点
			3.释放要删除的结点的书的信息域的内存,释放要删除的结点的内存
			需要注意两个特殊结点:要删除的结点是首结点或尾结点时,需要分别判断处理*/
			if(q->m_pParentPoint!=NULL && q->m_pSun!=NULL)
			{
				/*夹在链表中间的结点*/
				BookLeftPoint = q->m_pParentPoint;/*要删除的结点的前驱指向赋给前驱结点指针变量*/
				BookRightPoint = q->m_pSun;/*要删除的结点的后继指向赋给后继结点的指针变量*/
				BookLeftPoint->m_pSun = BookRightPoint;/*将后继结点指针指向的地址作为前驱结点中新后继域*/
				BookRightPoint->m_pParentPoint = BookLeftPoint;/*将后继结点指向的前驱域设定为要删除的结点的前驱结点*/
				q->m_pParentPoint = NULL;
				q->m_pSun = NULL;
				free(q->m_pBookInfo);/*先将书的信息结构体的内存释放*/
				q->m_pBookInfo = NULL;/*使指针指向安全地址*/
				free(q);/*将要删除的借还书信息结构体指针使用的内存空间释放*/
				q = NULL;/*要习惯将动态分配的内存在使用后动态释放,并将指针域指向空*/
				return bth;/*返回首结点*/
			}
			else if(q->m_pParentPoint==NULL)
			{
				/*首结点的前驱为空,这里处理首结点删除操作*/
				if(q->m_pSun==NULL)
				{/*前后指针域均为空时,说明只有一个结点,此时只需要将此结点删除*/
					free(q->m_pBookInfo);
					q->m_pBookInfo = NULL;
					free(q);
					q = NULL;
					return q;
				}
				bth = q->m_pSun;
				bth->m_pParentPoint = NULL;
				
				/*要删除的结点的后继指向赋给后继结点的指针变量*/
				BookRightPoint = q;
				BookRightPoint->m_pParentPoint = NULL;/*将链表中指向首结点的后继指针的前驱指针域置为空,表明是新的首结点*/
				BookRightPoint->m_pSun = NULL;/*将链表中指向首结点的后继指针的前驱指针域置为空,表明是新的首结点*/
				
				free(BookRightPoint->m_pBookInfo);/*先将书的信息结构体的内存释放*/
				BookRightPoint->m_pBookInfo = NULL;/*使指针指向安全地址*/
				free(BookRightPoint);/*将要删除的借还书信息结构体指针使用的内存空间释放*/
				BookRightPoint = NULL;/*要习惯将动态分配的内存在使用后动态释放,并将指针域指向空*/
				
				return bth;/*返回首结点*/
			}
			else if (q->m_pSun==NULL)
			{
				/*尾结点的后继结点为空,这里处理尾结点的删除操作*/

				BookLeftPoint = q->m_pParentPoint; /*将要删除的结点即尾结点的前驱域保存到前驱指针变量中*/
				BookLeftPoint->m_pSun = NULL;/*将要删除的结点的前驱结点与链表断开,前驱结点作为新的尾结点*/
				q->m_pParentPoint = NULL;
				free(q->m_pBookInfo);/*先将书的信息结构体的内存释放*/
				q->m_pBookInfo = NULL;/*使指针指向安全地址*/
				free(q);/*将要删除的借还书信息结构体指针使用的内存空间释放*/
				q = NULL;/*要习惯将动态分配的内存在使用后动态释放,并将指针域指向空*/
				return bth;/*返回首结点*/
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
	printf("\n\t请输入你想查找的书个号: ");
	scanf("%d",&x);
	q=Search(bth,x,&k,&flag);    
	if(flag==1)
	{
		p=q->m_pBookInfo;
		printf("\n\t书名:             %s",p->m_strTitle);    
		printf("\n\t作者:            %s",p->m_strWroter);
		printf("\n\t当前在架数量:     %d",p->m_nMoreNum);
		printf("\n\t库存数量:       %d",p->m_nTotalHoldNum);
		printf("\n\t图书简介: %s\n",p->m_strComment);
	}
	else printf("\n\t这个图书不存在!");
}
void Borrow_TheBook(struct Info *bth)
{
	struct Info *q=NULL;
	struct Book *p=NULL;
	int i,k, x, flag,t;
	system("cls");/*清屏*/
	printf("\n\t请输入你想借的书个号: ");/*打印消息*/
	scanf("%d",&x);/*接受输入*/
	q=Search(bth,x,&k,&flag);  /*查找书个*/
	if(flag==1)  
	{
		p=q->m_pBookInfo;
		printf("\n\t借出这个图书 ?(y/n)");
		printf("\n\t书名:             %s",p->m_strTitle);
		printf("\n\t作者:            %s",p->m_strWroter);
		printf("\n\t当前在架数量:     %d",p->m_nMoreNum);
		printf("\n\t库存数量:       %d",p->m_nTotalHoldNum);
		printf("\n\t图书简介: %s\n",p->m_strComment);
		t=getch();
		if(t=='y'||t=='Y')
		{/*确认借这个图书*/
			if( (p->m_nMoreNum)==0) printf("\n\t对不起,图书已经全部借出...");
			else
			{
				system("cls");
				for(i=0;i<20;i++) if( (p->reader[i]).num[0]=='\0') break;
				printf("\n\t请输入借书证号: ");  
				scanf("%s",(p->reader[i]).num);
				printf("\n\t请输入借出的日期: "); 
				printf("\n\t年:  ");
				scanf("%d",&((p->reader[i]).bro.m_nYear));
				printf("\t月: ");
				scanf("%d",&((p->reader[i]).bro.m_nMonth));
				printf("\t日:   ");
				scanf("%d",&((p->reader[i]).bro.m_nDay));
				
				printf("\n\t请输入归还日期: ");
				printf("\n\t年:  ");
				scanf("%d",&((p->reader[i]).back.m_nYear));
				printf("\t月: ");
				scanf("%d",&((p->reader[i]).back.m_nMonth));
				printf("\t日:   ");
				scanf("%d",&((p->reader[i]).back.m_nDay));
				
				p->m_nMoreNum--;       
				printf("\n\t成功借到个图书.");}
		}
		
	}
	else printf("\n\t这个图书不存在!"); 
}
void TurnBack_TheBook(struct Info *bth)
{
	struct Info *q=NULL;
	struct Book *p=NULL;
	int i,k, x, flag,t,j;
	int year,month,day,d;
	float pay;
	char temp[20];
	system("cls");/*清屏*/
	printf("\n\t请输入归还的书个号: ");
	scanf("%d",&x);
	q=Search(bth,x,&k,&flag); /*书个查找*/   
	if(flag==1)
	{/*找到个图书*/
		p=q->m_pBookInfo;
		printf("\n\t你想归还这个图书 ?(y/n)");
		printf("\n\t书名:             %s",p->m_strTitle);
		printf("\n\t作者:            %s",p->m_strWroter);
		printf("\n\t当前在架数量:     %d",p->m_nMoreNum);
		printf("\n\t库存数量:       %d",p->m_nTotalHoldNum);
		printf("\n\t图书简介: %s\n",p->m_strComment);
		t=getch();/*接受选择*/
		if(t=='y'||t=='Y')
		{/*确认归还这个图书*/
			if( (p->m_nMoreNum) >=(p->m_nTotalHoldNum) )
				printf("\n\t想再上架一个图书吗 ??\n");
			else
			{
				system("cls");
				printf("\n\t请输入借书证号: ");
				scanf("%s",temp);
				j=0;
				for(i=0;i<20;i++)
				{
					if(! (strcmp(temp,(p->reader[i]).num))) {j=1;break;} 
				}
				if(j==0) {printf("\n\t你不能借这个图书。");return;}  
				printf("\n\t今天是:");   
				printf("\n\t年:  ");
				scanf("%d",&year);
				printf("\t月: ");
				scanf("%d",&month);
				printf("\t日:   ");
				scanf("%d",&day);
				
				
				d=0;
				if(year<(p->reader[i]).back.m_nYear) d=1; 
				if(year<=(p->reader[i]).back.m_nYear && month<(p->reader[i]).back.m_nMonth) d=1;
				if(year<=(p->reader[i]).back.m_nYear && month<=(p->reader[i]).back.m_nMonth && day<(p->reader[i]).back.m_nDay) d=1;
				if(d==0)
				{/*超过还书日期，在此还书*/
					system("cls");
					pay=(year-(p->reader[i]).back.m_nYear)*365+(month-(p->reader[i]).back.m_nMonth)*30+(day-(p->reader[i]).back.m_nDay);
					printf("\n\t你的借书日期是： %d-%d-%d",(p->reader[i]).bro.m_nYear,(p->reader[i]).bro.m_nMonth,(p->reader[i]).bro.m_nDay);  
					printf("\n\t你的还书日期是： %d-%d-%d之前",(p->reader[i]).back.m_nYear,(p->reader[i]).back.m_nMonth,(p->reader[i]).back.m_nDay);
					printf("\n\t今天是                   %d-%d-%d",year,month,day);
					printf("\n\n\t因此你超出借期，");
					printf("\n\t应该支付%2.1f 元罚款.",0.1*pay); 
				}
				(p->reader[i]).num[0]='\0'; 
				p->m_nMoreNum++;  
				printf("\n\t你已经归还了这个图书.");
			}
		}
		
	}
	else printf("\n\t你不能归还不存在的一个图书!!!");  
	
}

char Select_Menu()
{/*主菜单显示函数*/
	system("cls");
    printf("/******************************************\\\n");
    printf("*                                          *\n");
    printf("*        图  书  馆  管  理  系  统        *\n");
    printf("*                  主菜单                  *\n");
    printf("*                                          *\n");
    printf("*               1. 图书上架                *\n");
    printf("*               2. 图书下架                *\n");
    printf("*               3. 查找图书                *\n");
    printf("*               4. 图书出借                *\n");
    printf("*               5. 图书归还                *\n");
    printf("*               6. 退出系统                *\n"); 
    printf("*                                          *\n");
    printf("*             请选择菜单项：(1~6)          *\n");
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
	    printf("您选择了：%c",c);
		getch();
		switch(c)  
		{
		case '1': 
			bth=Insert_BookInfo(bth);/*图书上架*/
            break;
		case '2': 
			bth=Delete_BookInfo(bth);/*图书下架*/
            break;
		case '3': Output_BookInfo(bth);/*查找图书*/
            break;
		case '4': Borrow_TheBook(bth);/*图书出借*/
            break;
		case '5': TurnBack_TheBook(bth);/*图书归还*/
            break;
		case '6':
		case '0': system("cls");
            printf("\n\t你想退出系统 ?(y/n)");
            t=getch();
            if(t=='y'||t=='Y') exit(0);
            break;
		}
		printf("\n\t按任意键返回主菜单....");
		getch();
	}
} 

