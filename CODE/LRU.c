#define MAXSIZE    20
#include <stdio.h>

void main()
{
	int input=0;                                   //用于输入作业号
	int worknum=0;                                 //输入的作业个数
	int storesize=0;                               //系统分配的存储区块数
	int interrupt=0;                               //缺页中断次数
	int stack[MAXSIZE];                            //栈，LRU算法的主要数据结构
	int workstep[MAXSIZE];                         //记录作业走向
	/*初始化*/
	for(int i=0;i<MAXSIZE;i++)
	{
		stack[i]=0;
		workstep[i]=0;
	}
	printf("请输入存储区块数：\n");
	scanf("%d",&storesize);
	
	printf("请输入作业的页面走向（输入0结束）：\n");
	for(int j=0;j<MAXSIZE;j++)
	{
		printf("页面号%d：",j+1);
		scanf("%d",&input);		
		workstep[j]=input;
		if(input==0)
		{
		    printf("输入结束！\n");
			break;
		}
		worknum++;
	}
	if(workstep[0]==0)
	{
		printf("未输入任何作业，系统将退出！\n");
		return 0;
	}
	printf("置换情况如下：\n");
	for(int k=0;k<worknum;k++)
	{
		/*在栈中找相等的页号或空位置*/
		for(int l=0;l<storesize;l++)
		{
			/*是否有相等的页号*/
			if(stack[l]==workstep[k])
			{
				printf("内存中有%d号页面，无需中断\n",workstep[k]);
			    goto step1;
			}
			/*找栈中是否有空位置*/
			if(stack[l]==0)
			{
				stack[l]=workstep[k];
				printf("发生中断，但内存中有空闲区，%d号页面直接调入！\n",workstep[k]);
				interrupt++;
				goto step1;
			}
		}
		/*上述情况都不成立则调出栈顶，将调入页面插入栈顶*/
		printf("发生中断，将%d号页面调出，%d号装入！\n",stack[0],workstep[k]);
		interrupt++;
		/*新掉入的页面放栈顶*/
step1:	for(int m=0;m<storesize;m++)
		{
			stack[m]=stack[m+1];
		}
		stack[storesize-1]=workstep[k];

	}
	printf("作业%d个，中断%d次，缺页率是%f\n",worknum,interrupt,float(interrupt)/float(worknum)*100);
    
}