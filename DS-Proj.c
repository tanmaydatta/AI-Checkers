struct possible_moves
{
	int x[4],y[4],numturns[4],total_num;
};
struct possible_moves check(int i,int j,int n,int board[8][8])
{
	int t=0;
	// n=0 -> Computer Turn
	// n=1 -> Player Turn
	// board[i][j]= -1  - Empty
	//               0  - Computer Goti
	//               1  - Player Goti
	//
	//
	//
	// Variable t is for --> ((FILL SPACE LATER))
	//
	//
	//
	//	
	//
	//
	//
	//
	struct possible_moves moves;
	moves.total_num=0;
	int ctr=0;
	if(n==0)
	{
		if(i+1<8 && i+1>=0 && j-1<8 && j-1>=0)
		{
			if(board[i+1][j-1]==-1)                           // j+1   i-1
			{
				moves.x[ctr]=1;
				moves.y[ctr]=-1;
				moves.numturns[ctr]=1;
				ctr++;
				moves.total_num++;	 
			}
		}

		if(i+1<8 && i+1>=0 && j+1<8 && j+1>=0)
		{
			if(board[i+1][j+1]==-1)
			{
				moves.x[ctr]=1;
				moves.y[ctr]=1;
				moves.numturns[ctr]=1;
				ctr++;
				moves.total_num++;	
			}
		}

		if(i+2<8 && i+2>=0 && j-2<8 && j-2>=0)
		{
			int turn=1;
			if(board[i+2][j-2]==-1 && board[i+1][j-1]==1)
			{
				int temp=4;;
				while(1)
				{
					if(i+temp<8 && i+temp>=0 && j-temp<8 && j-temp>=0)
					{
						if(board[i+temp][j-temp]==-1 && board[i+temp-1][j-temp+1]==1)
						{
							temp+=2;
							turn++;
						}
						else break;
					}
					else break;
				}
				moves.x[ctr]=2;
			moves.y[ctr]=-2;
			moves.numturns[ctr]=turn;
			ctr++;
			moves.total_num++;
			}
				
		}

		if(i+2<8 && i+2>=0 && j+2<8 && j+2>=0)
		{
			int turn=1;
			if(board[i+2][j+2]==-1 && board[i+1][j+1]==1)
			{
				int temp=4;;
				while(1)
				{
					if(i+temp<8 && i+temp>=0 && j+temp<8 && j+temp>=0)
					{
						if(board[i+temp][j+temp]==-1 && board[i+temp-1][j+temp-1]==1)
						{
							temp+=2;
							turn++;
						}
						else break;
					}
					else break;
				}
				moves.x[ctr]=2;
			moves.y[ctr]=2;
			moves.numturns[ctr]=turn;
			ctr++;
			moves.total_num++;	
			}
			
		}
	}


	else if(n==1)
	{
		if(i-1<8 && i-1>=0 && j-1<8 && j-1>=0)
		{
			if(board[i-1][j-1]==-1)                           // j+1   i-1
			{
				moves.x[ctr]=-1;
				moves.y[ctr]=-1;
				moves.numturns[ctr]=1;
				ctr++;
				moves.total_num++;	 
			}
		}

		if(i-1<8 && i-1>=0 && j+1<8 && j+1>=0)
		{
			if(board[i-1][j+1]==-1)
			{
				moves.x[ctr]=-1;
				moves.y[ctr]=1;
				moves.numturns[ctr]=1;
				ctr++;
				moves.total_num++;	
			}
		}

		if(i-2<8 && i-2>=0 && j-2<8 && j-2>=0)
		{
			int turn =1;
			if(board[i-2][j-2]==-1 && board[i-1][j-1]==0)
			{
				int temp=4;;
				while(1)
				{
					if(i-temp<8 && i-temp>=0 && j-temp<8 && j-temp>=0)
					{
						if(board[i-temp][j-temp]==-1 && board[i-temp+1][j-temp+1]==0)
						{
							temp+=2;
							turn++;
						}
						else break;
					}
					else break;
				}
			}
			moves.x[ctr]=-2;
			moves.y[ctr]=-2;
			moves.numturns[ctr]=turn;
			ctr++;
			moves.total_num++;	
		}

		if(i-2<8 && i-2>=0 && j+2<8 && j+2>=0)
		{
			int turn =1;
			if(board[i-2][j+2]==-1 && board[i-1][j+1]==0)
			{
				int temp=4;;
				while(1)
				{
					if(i+temp<8 && i+temp>=0 && j-temp<8 && j-temp>=0)
					{
						if(board[i-temp][j+temp]==-1 && board[i-temp+1][j+temp-1]==0)
						{
							temp+=2;
							turn++;
						}
						else break;
					}
					else break;
				}
			}
			moves.x[ctr]=-2;
			moves.y[ctr]=2;
			moves.numturns[ctr]=turn;
			ctr++;
			moves.total_num++;	
		}
	}
	return moves;
}