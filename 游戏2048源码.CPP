/*
           文件名称：main.c
		   文件的描述：实现2048游戏。
		   编译环境：VS2013
		   作者：高宇波
		   最后修改：2019年02月25日

		   2048：
		        规则：方格内会出现一个随机数：2，4，其他为0
				玩：玩家使用上下左右来控制游戏，比如上，所有的数字网上靠拢，如果有相同的数字相加合并。
				结束：成功：方格内出现2048这个数字。失败：方格内充满数字，并且相邻的数字都不相同。
*******************************************************************************************************************************/
//包含头文件
#include<stdio.h>
#include<string.h>
#include<conio.h>     //键盘的输入输出命令头文件
#include<windows.h>    //清屏函数头文件
#include<time.h>        //随机数函数
int MAP[4][4];
int ALLSORE;
void Print();
int Move();
void Add(int dir);
int Moveup();
int Movedown();
int Moveleft();
int Moveright();
void Givesore(int sore);
int Gameover();

//主函数
int main()
{
	memset(MAP,0,sizeof(MAP));  //对MAP指向的内存前面sizeof(MAP)初始化填充0,参数1：变量名，参数2：填充数，参数3：空间大小
	Print();
	while(Move())
	{
		fflush(stdin);     //清空缓冲
		system("CLS");    //清屏函数
		Print();
		if(Gameover()==16)
		{
			printf("游戏结束，按任意键继续\n");
			break;
		}
	}
	return 0;
}
//打印
void Print()
{
	printf("得分：%d\n",ALLSORE);
	printf("\t\t┌──────┐──────┐──────┐──────┐\n");
	printf("\t\t│  %3d │  %3d │  %3d │  %3d │\n",MAP[0][0],MAP[0][1],MAP[0][2],MAP[0][3]);
	printf("\t\t├──────┼──────┼──────┼──────┤\n");
	printf("\t\t│  %3d │  %3d │  %3d │  %3d │\n",MAP[1][0],MAP[1][1],MAP[1][2],MAP[1][3]);
	printf("\t\t├──────┼──────┼──────┼──────┤\n");
	printf("\t\t│  %3d │  %3d │  %3d │  %3d │\n",MAP[2][0],MAP[2][1],MAP[2][2],MAP[2][3]);
	printf("\t\t├──────┼──────┼──────┼──────┤\n");
	printf("\t\t│  %3d │  %3d │  %3d │  %3d │\n",MAP[3][0],MAP[3][1],MAP[3][2],MAP[3][3]);
	printf("\t\t└──────┴──────┴──────┴──────┘\n");
}
//控制
int Move()
{
	fflush(stdin);//清空缓存
	int flag=1;
	char key;
	key=_getch();  //getchar接受键盘，进入键盘的缓冲区，回车键之后接受。getch接受键盘，不需要缓冲区（区别getchar按下其他键不更新，只有按下回车才跟新数据）
	switch(key)
	{
	case 72:      //72上键
		flag=Moveup();
		break;
	case 80:
		flag=Movedown();//80下键
		break;
	case 75: 
		flag=Moveleft();//75左键
		break;
	case 77: //77右键
		flag=Moveright();
		break;
	}
	return flag;   
}
void Add(int dir)   //增加要么为2，要么为4      rand()%4;0到3的随机数    rand()%4+1;1到4的随机数
{
     srand((unsigned int)time(NULL));        //种下随机因子。
	 int num=rand();       //得到0-30000多的随机数
	 int row,col;
	 int flag=num%2;       //要么是0，要么是1的随机数
	 if(flag)
		 num=2;
	 else
		 num=4;
	 row=rand()%4;
	 col=rand()%4;
	 //dir为方向，0最开始没有方向    1上    2下    3左    4右
	 if(dir==0)
		 MAP[row][col]=num;
	 else if(dir==1)                  //如果为上
     {
		 if(MAP[3][col]==0)      //如果最后一行要出现的随机位置为0，则直接增加随机数
			 MAP[3][col]=num;
		 else
		 {
			 for(int i=0;i<4;i++)
				 if(MAP[3][i]==0)
				 {
					 MAP[3][i]=num;
					 break;
				 }	
		 }
	 }
	 else if(dir==2)             //如果为下
     {
		 if(MAP[0][col]==0)      //如果第一行要出现的随机位置为0，则直接增加随机数
			 MAP[0][col]=num;
		 else
		 {
			 for(int i=0;i<4;i++)
				 if(MAP[0][i]==0)
				 {
					 MAP[0][i]=num;
					 break;
				 }	
		 }
	 }
	 else if(dir==3)         //如果为左
     {
		 if(MAP[row][3]==0)      //如果最后一列要出现的随机位置为0，则直接增加随机数
			 MAP[row][3]=num;
		 else
		 {
			 for(int i=0;i<4;i++)
				 if(MAP[i][3]==0)
				 {
					 MAP[i][3]=num;
					 break;
				 }	
		 }
	 }
	  else if(dir==4)         //如果为右
     {
		 if(MAP[row][0]==0)      //如果第一列要出现的随机位置为0，则直接增加随机数
			 MAP[row][0]=num;
		 else
		 {
			 for(int i=0;i<4;i++)
				 if(MAP[i][0]==0)
				 {
					 MAP[i][0]=num;
					 break;
				 }	
		 }
	 }
}
//向上移动
int Moveup()
{
	int row,col;
	for(col=0;col<4;col++)
	{
		int n=4;
        while(n--)
		{
            for(row=0;row<3;row++)
			{
				if(MAP[row][col]==0)
				{
					for(int tep=row;tep<3;tep++)
					{
						MAP[tep][col]=MAP[tep+1][col];
						MAP[tep+1][col]=0;
					}
				}
			}
		}
		for(row=0;row<3;row++)
		{
			if(MAP[row][col]==MAP[row+1][col])
			{
				MAP[row][col]*=2;
				Givesore(MAP[row][col]);
				for(int tep=row+1;tep<3;tep++)
				{
					MAP[tep][col]=MAP[tep+1][col];
					MAP[tep+1][col]=0;
				}
			}

		}
	}
	Add(1);
	return 1;
}
//向下移动
int Movedown()
{
	int row,col;
	for(col=0;col<4;col++)
	{
		int n=4;
        while(n--)
		{
            for(row=3;row>0;row--)
			{
				if(MAP[row][col]==0)
				{
					for(int tep=row;tep>0;tep--)
					{
						MAP[tep][col]=MAP[tep-1][col];
						MAP[tep-1][col]=0;
					}
				}
			}
		}
		for(row=3;row>0;row--)
		{
			if(MAP[row][col]==MAP[row-1][col])
			{
				MAP[row][col]*=2;
				Givesore(MAP[row][col]);
				for(int tep=row-1;tep>0;tep--)
				{
					MAP[tep][col]=MAP[tep-1][col];
					MAP[tep-1][col]=0;
				}
			}

		}
	}
	Add(2);
	return 1;
}
//向左移动
int Moveleft()
{
	int row,col;
	for(row=0;row<4;row++)
	{
		int n=4;
        while(n--)
		{
            for(col=0;col<3;col++)
			{
				if(MAP[row][col]==0)
				{
					for(int tep=col;tep<3;tep++)
					{
						MAP[row][tep]=MAP[row][tep+1];
						MAP[row][tep+1]=0;
					}
				}
			}
		}
		for(col=0;col<3;col++)
		{
			if(MAP[row][col]==MAP[row][col+1])
			{
				MAP[row][col]*=2;
				Givesore(MAP[row][col]);
				for(int tep=col+1;tep<3;tep++)
				{
					MAP[row][tep]=MAP[row][tep+1];
					MAP[row][tep+1]=0;
				}
			}

		}
	}
	Add(3);
	return 1;
}
//向右移动
int Moveright()
{
	int row,col;
	for(row=0;row<4;row++)
	{
		int n=4;
        while(n--)
		{
            for(col=3;col>0;col--)
			{
				if(MAP[row][col]==0)
				{
					for(int tep=col;tep>0;tep--)
					{
						MAP[row][tep]=MAP[row][tep-1];
						MAP[row][tep-1]=0;
					}
				}
			}
		}
		for(col=3;col>0;col--)
		{
			if(MAP[row][col]==MAP[row][col-1])
			{
				MAP[row][col]*=2;
				Givesore(MAP[row][col]);
				for(int tep=col-1;tep>0;tep--)
				{
					MAP[row][tep]=MAP[row][tep-1];
					MAP[row][tep-1]=0;
				}
			}

		}
	}
	Add(4);
	return 1;
}
//得分
void Givesore(int sore)
{
	ALLSORE=ALLSORE+sore;
}
//游戏结束
int Gameover()
{
	int flag=0,row,col;
	for(row=0;row<3;row++)
		for(col=0;col<3;col++)
			if(MAP[row][col]!=0&&MAP[row][col]!=MAP[row+1][col]&&MAP[row][col]!=MAP[row][col+1])
				flag=flag+1;
	for(int i=0;i<3;i++)
		if(MAP[3][i]!=0&&MAP[i][3]!=0&&MAP[3][i]!=MAP[3][i+1]&&MAP[i][3]!=MAP[i+1][3])
			flag=flag+2;
	if(MAP[3][3]!=0)
		flag=flag+1;
		return flag;
 }
