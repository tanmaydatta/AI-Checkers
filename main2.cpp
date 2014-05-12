#include<stdlib.h>
#include<math.h>
#include<stdio.h>
#include<iostream>
using namespace std;
#include "DS-Proj.c"
struct node
{
	int score, board [8][8],num_of_coins/*will have 0 if number of coins are same on boh sides */;
	int turn,is_score;
	struct node* next[5];
	void calc_score();
	void generate(int n);
	void change(int n,int i,int j,struct possible_moves t);
	void copy(int ctr);
};

void assign_score();
void assign_moves(struct node * ptr)
{
	if(!ptr)
		return ;
	if(ptr->next[0])
	{
		if(ptr->next[0]->is_score==1)
		{
			int temp1=100,temp=0;
			for(int i=0;i<5;i++)
			{
				if(ptr->next[i]&&ptr->turn==1)
					temp=max(temp,ptr->next[i]->num_of_coins);
				else if(ptr->next[i]&&ptr->turn==0)
					temp1=min(temp1,ptr->next[i]->num_of_coins);
			}
			if(ptr->turn == 1)
			{
				
				ptr->num_of_coins=temp;
				if(temp==0)
					ptr->score=ptr->next[0]->score;
			}
			
			else 
				{
					ptr->num_of_coins=temp1;
					if(temp1==0)
					ptr->score=ptr->next[0]->score;
	
				}
			ptr->is_score=1;
		}
		else 
		{
			for(int i=0;i<5;i++)
			{
				assign_moves(ptr->next[i]);
			}
			if(ptr->next[0]->is_score==1)
		{
			int temp1=100,temp=0;
			for(int i=0;i<5;i++)
			{
				if(ptr->next[i]&&ptr->turn==1)
					temp=max(temp,ptr->next[i]->num_of_coins);
				else if(ptr->next[i]&&ptr->turn==0)
					temp1=min(temp1,ptr->next[i]->num_of_coins);
			}
			if(ptr->turn == 1)
			{
				
				ptr->num_of_coins=temp;
				if(temp==0)
					ptr->score=ptr->next[0]->score;
			}
			
			else 
				{
					ptr->num_of_coins=temp1;
					if(temp1==0)
					ptr->score=ptr->next[0]->score;
				}
			ptr->is_score=1;
		}
		}	
	}
}
void assign_score(struct  node *ptr,int n)
{
	if(!ptr)
		return ;
	if(!ptr->next[0]&&!ptr->next[1]&&!ptr->next[2]&&!ptr->next[3]&&!ptr->next[4])
	{
		ptr->calc_score();
		ptr->is_score=1;
	}
	else 
	{
		for(int i=0;i<5;i++)
		{
			assign_score(ptr->next[i],n+1);
		}
		if(n%2==0)
		{
			ptr->num_of_coins=0;
			for(int i=0;i<5;i++)
			{
				if(ptr->next[i])
				ptr->num_of_coins=min(ptr->num_of_coins,ptr->next[i]->num_of_coins);
			}
			if(ptr->num_of_coins>=0)
			{
				ptr->score=ptr->next[0]->score;
			}
		}
		else 
		{
			ptr->num_of_coins=0;
			for(int i=0;i<5;i++)
			{
				if(ptr->next[i])
				ptr->num_of_coins=max(ptr->num_of_coins,ptr->next[i]->num_of_coins);
			}
			if(ptr->num_of_coins<=0)
			{
				ptr->score=ptr->next[0]->score;
			}
		}
	}
}

  void  node :: calc_score()
{
	int temp=0;
	score=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(board[i][j]==1)
				temp++;
			else if(board[i][j]==0)
				temp--;
		}
	}
	num_of_coins=temp;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(board[i][j]==1)
			{
				if(i==0||j==0||j==7||i==7)
				{
					score+=4;
				}
				else if(i==1&&j>=i&&j<7)
				{
					score+=3;
				}
				else if(i==6&&j<=i&&j>=1)
				{
					score+=3;
				}
				else if(j==1&&i>=j&&i<7)
				{
					score+=3;
				}
				else if(j==6&&i<=j&&i>=1)
				{
					score+=3;
				}

				else if(i==2&&j>=i&&j<6)
				{
					score+=2;
				}
				else if(i==5&&j<=i&&j>=2)
				{
					score+=2;
				}
				else if(j==2&&i>=j&&i<6)
				{
					score+=2;
				}
				else if(j==5&&i<=j&&i>=2)
				{
					score+=2;
				}

				else if(i==3&&j>=i&&j<5)
				{
					score++;
				}
				else if(i==4&&j<=i&&j>=3)
				{
					score++;
				}
				else if(j==3&&i>=j&&i<5)
				{
					score++;
				}
				else if(j==4&&i<=j&&i>=3)
				{
					score++;
				}
			}
		}
	}
}
void tree(struct node * ptr, int n) // need to malloc root inside main
{
	int i;
	if(n>9)
		return;
	if(!ptr)
	{
		return ;
	}
	for(i=0;i<5;i++)
	{
		ptr->next[i]=NULL;
	}																																																																																																																																																																																																																																																																																																										
	ptr->generate(n%2);
	ptr->turn=n%2;																																																																																																																																																																																																																																																													
	
	for(i=0;i<5;i++)
	{
		tree(ptr->next[i],(n+1));
	}
}

void node :: generate(int n)
{
	int flag=0,i,j;
	for(i=0;i<8;i++)
	{
		for(j=0;j<8;j++)
		{
			if(board[i][j]==n%2)
			{
				struct possible_moves t=check(i,j,n,board);
				if(t.total_num)
					change(n,i,j,t);
			}
		}
	}
}

void node :: change(int n,int i,int j,struct possible_moves t)
{
	for(int k=0;k<t.total_num;k++)
	{
		next[k]=(struct node *)malloc(sizeof(struct node));
		copy(k);
		int I=i,J=j;
		while(t.numturns[k]--)
		{
			I+=t.x[k];
			J+=t.y[k];
			if(t.x[k]>1||t.x[k]<-1)
			{
				if(t.x[k]>0&&t.y[k]>0)
				{
					next[k]->board[I-1][J-1]=-1;	
				}
				else if(t.x[k]>0&&t.y[k]<0)
				{
					next[k]->board[I-1][J+1]=-1;	
				}
				else if(t.x[k]<0&&t.y[k]<0)
				{
					next[k]->board[I+1][J+1]=-1;	
				}
				else if(t.x[k]<0&&t.y[k]>0)
				{
					next[k]->board[I+1][J-1]=-1;	
				}
			}
		}
		next[k]->board[i][j]=-1;
		next[k]->board[I][J]=n%2;

	}
}

void node :: copy(int ctr)
{
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			next[ctr]->board[i][j]=board[i][j];
		}
	}
}

void delete_tree(struct node * ptr)
{
	if(ptr==NULL)
	{
		return ;
	}
	for(int i=0;i<5;i++)
	{
		if(ptr->next[i])
		{
		delete_tree(ptr->next[i]);
		}
	}
	if(ptr)
	{
		free(ptr);
	}
}