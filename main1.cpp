#include "main2.cpp"

struct node * root;
int count(int b[8][8])
{
	int temp=0;
	for(int i=0;i<8;i++)
	{
		for(int j=0;j<8;j++)
		{
			if(b[i][j]==0)
				temp--;
			else if(b[i][j]==1)
				temp++;
		}
	}
	return temp;
}
int checkers()
{
	int f1=0;
	freopen("in.txt", "rt", stdin);
    freopen("out.txt", "wt", stdout);
    int b[8][8];
	root=(struct node *)malloc(sizeof(struct node));
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			cin>>b[i][j];
	for(int i=0;i<8;i++)
		for(int j=0;j<8;j++)
			root->board[i][j]=b[i][j];
	tree(root,0);
	assign_score(root,0);
	assign_moves(root);
	struct node * temp=NULL,*ptr=NULL;
	//temp=(struct node *)malloc(sizeof(struct node));
	int num_of_coins=100;
	int Min=100,min1=100,min2=100;
	for(int i=0;i<5;i++)
	{
		if(root->next[i])
		{
			
			Min=min(Min,root->next[i]->num_of_coins);
			min1=min(min1,count(root->next[i]->board));
			if(Min<num_of_coins)
			{
				num_of_coins=Min;
				temp=root->next[i];
				f1++;
			}
			if(min1<min2)
			{
				min2=min1;
				ptr=root->next[i];
			}
			/*for(int k=0;k<8;k++)
			{
			for(int j=0;j<8;j++)
			{
				cout<<root->next[i]->board[k][j]+1<<" ";
			}
			cout<<"\n";
			}*/
			if(Min>=-1)
			temp=ptr;
			//cout<<"\n"<<count(root->next[i]->board)<<"\n";
			//system("PAUSE");
		}
	}
	if(temp)
	{
		for(int i=0;i<8;i++)
		{
			for(int j=0;j<8;j++)
			{
				cout<<temp->board[i][j]<<" ";
			}
			cout<<"\n";
		}
	}
	if(f1>0)
	{
		cout<<"\n"<<f1<<endl;
	}
	else cout<<"\n0"<<endl;
	delete_tree(root);
	return 0;
}