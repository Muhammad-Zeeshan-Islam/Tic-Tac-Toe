#include<iostream>
#include<fstream>
#include<stack>
#include<conio.h>
#define RESET       "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      // Bold Red 
#define BOLDCYAN    "\033[1m\033[36m"      // Bold Cyan 
#define BOLDWHITE   "\033[1m\033[37m"      // Bold White
using namespace std;
class CPU
{
	char board[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};  //2D Array
	int row,column;
	stack<pair<int,int>>moveStack; // to store moves for undo, to store the pair of int representing rows & columns
    char turn='X';
    bool draw = false;
    char PlayerScore = '0';
	char CPU_Score = '0';
	public:
	void displayBoard()
	{
		system("cls");
		cout<<BOLDWHITE<<"     TICK TACK TOE\n"<<endl;
		cout<<RESET<<BOLDRED<<"\tPlayer [X]: "<<PlayerScore<<endl<<RESET<<BOLDCYAN<<"\tCPU [O]: "<<CPU_Score<<endl<<RESET<<BOLDWHITE<<endl;
		cout<<"\t\t     |     |     \n";
		for(int i=0;i<3;i++)
		{
			cout<<BOLDWHITE<<"\t\t   ";
			for(int j=0;j<3;j++)
			{
				cout<<BOLDWHITE;
				if(j!=0)
				{
					cout<<" |   ";
				}
				if(board[i][j]=='X')
				{
					cout<<RESET<<BOLDRED<< board[i][j]<<RESET;
				}
				else if(board[i][j]=='O')
				{
					cout<<RESET<<BOLDCYAN<< board[i][j]<<RESET;
				}
				else
				{
					cout<<board[i][j];
				}
			}
			cout<<"\n";
			if(i!=2)
			{
				cout<<BOLDWHITE;
				cout<<"\t\t_____|_____|_____\n";
				cout<<"\t\t     |     |     \n";
			}
		}
		cout<<"\t\t     |     |     \n"<<RESET;
	}
	void playerTurn() {
    int choice;
    if (turn == 'X') {
        cout << BOLDRED << "\n\t Player [X] turn: ";
        cin >> choice;

        switch (choice) {
            case 1: row = 0; column = 0; break;
            case 2: row = 0; column = 1; break;
            case 3: row = 0; column = 2; break;
            case 4: row = 1; column = 0; break;
            case 5: row = 1; column = 1; break;
            case 6: row = 1; column = 2; break;
            case 7: row = 2; column = 0; break;
            case 8: row = 2; column = 1; break;
            case 9: row = 2; column = 2; break;
            default:
                cout << "Invalid choice" << endl;
                getch();
                INTERFACE();
                break;
        }

        if (board[row][column] != 'X' && board[row][column] != 'O') {
            board[row][column] = 'X';
            moveStack.push({row, column});
            turn = 'O';
        } else {
            cout << "Box already filled! \n Please try again\n\n";
            playerTurn();
        }
    }
    else // CPU Turn
	{
		cout<<BOLDCYAN<<"\n\t CPU [O] Turn: "<<endl;
		pair<int,int> bestMove = findBestMove();
		row = bestMove.first;
		column = bestMove.second;
		board[row][column] = 'O';
		turn = 'X';
	}
    displayBoard();
}

	bool gameOver()
	{
		// Win check
		for(int i=0;i<3;i++)
		{
			if(board[i][0]==board[i][1] && board[i][0]==board[i][2] || board[0][i]==board[1][i] && board[0][i]==board[2][i])
			{
				return false;
			}
		}
		if(board[0][0]==board[1][1] && board[0][0]==board[2][2] || board[0][2]==board[1][1] && board[0][2]==board[2][0] )
		{
			return false;
		}
		// If there is not filled any box
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(board[i][j]!='X' && board[i][j]!='O')
				{
					return true;
				}
			}
		}
		// Game draw
		draw=true;
		return false;
    }
    void saveGame()
    {
    	ofstream file("CPU.txt");
    	file<<turn<<"\n"; // Storing Turns Enter by the user on RunTime
    	for(int i=0;i<3;i++)
    	{
    		for(int j=0;j<3;j++)
    		{
    			file<<board[i][j];
			}
			file<<endl;
		}
		file<<PlayerScore<<"\n";
		file<<CPU_Score<<"\n";
		file.close();
	}
	void loadGame()
	{
		ifstream file("CPU.txt");
		if(file.is_open())
		{
			if(file.peek() == ifstream::traits_type::eof()) // Check if the file is Empty
			{
				cout<<"File is Empty"<<endl;
				getch();
				return;
			}
			file>>turn;
			for(int i=0;i<3;i++)
	    	{
	    		for(int j=0;j<3;j++)
	    		{
	    			file>>board[i][j];
				}
			}
			file>>PlayerScore;
			file>>CPU_Score;
			file.close();
			cout<<"Game Loaded"<<endl;
			displayBoard();
			INTERFACE();
		}
		else
		{
			cout<<"No File to Load"<<endl;
			getch();
		}
	}
	void INTERFACE()
	{
		char choice;
		while(gameOver())
		{
			displayBoard();
			playerTurn();
			gameOver();
			saveGame();
		}
		if(turn=='O' && draw==false)
		{
			PlayerScore++;
			displayBoard();
			cout<<BOLDRED<<"\n\tPlayer [X] Win the Game. Congratulations!"<<RESET<<endl;
		}
		else if(turn=='X'&& draw==false)
		{
			CPU_Score++;
			displayBoard();
			cout<<BOLDCYAN<<"\n\tCPU [O] Win the Game. Congratulations!"<<RESET<<endl;
		}
		else
		{
			cout<<BOLDWHITE<<"\n\t\t    Game Draw!"<<RESET<<endl;
		}
		cout<<BOLDWHITE<<"Do you want to play again (y/n) : ";
		cin>>choice;
		if(choice=='y' || choice=='Y')
		{
			resetBoard();
			INTERFACE();
		}
	}
	void resetBoard()
	{
		char initialBoard[3][3] = {{'1','2','3'},{'4','5','6'},{'7','8','9'}};
		for(int i=0; i<3 ;i++)
		{
			for(int j=0; j<3 ;j++)
			{
				board[i][j] = initialBoard[i][j];
			}
		}
		while(!moveStack.empty())
		{
			moveStack.pop();
		}
		turn = 'X';
		draw = false;
	}
	
	//-------------- MINIMAX ALGORITHM BODY ---------------------
	
	int evaluateBoard()
	{
		// Checking rows for Win
		for(int row=0 ;row<3 ;row++)
		{
			if(board[row][0] == board[row][1] && board[row][1] == board[row][2])
			{
				if(board[row][0] == 'X') return +10;
				else if(board[row][0] == 'O') return -10;
			}
		}
		// Checking columns for Win
		for(int col = 0; col<3 ;col++)
		{
			if(board[0][col] == board[1][col] && board[1][col] == board[2][col])
			{
				if(board[0][col] == 'X') return +10;
				else if(board[0][col] == 'O') return -10;
			}
		}
		// Check Diagonals for Win
		if(board[0][0] == board[1][1] && board[1][1] == board[2][2])
		{
			if(board[0][0] == 'X') return +10;
			else if(board[0][0] == 'O') return -10;
		}
		if(board[0][2] == board[1][1] && board[1][1] == board[2][0])
		{
			if(board[0][2] == 'X') return +10;
			else if(board[0][2] == 'O') return -10;
		}
		// No winner
		return 0;
	}
	int minimax(bool isMax)
	{
		int score = evaluateBoard();
		// If the Game is over, return the score
		if(score == 10 || score == -10) return score;
		if(!movesLeft()) return 0; // Draw
		// Maximizing Player (X)
		if(isMax)
		{
			int best = -1000;
			for(int i = 0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(board[i][j] != 'X' && board[i][j] != 'O')
					{
						char backup = board[i][j];
						board[i][j] = 'X';
						best = max(best, minimax(false));
						board[i][j] = backup;
					}
				}
			}
			return best;
		}
		else // Minimizing Player (O)
		{
			int best = 1000;
			for(int i = 0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					if(board[i][j] != 'X' && board[i][j] != 'O')
					{
						char backup = board[i][j];
						board[i][j] = 'O';
						best = min(best, minimax(true));
						board[i][j] = backup;
					}
				}
			}
			return best;
		}
	}
	bool movesLeft()
	{
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(board[i][j] != 'X' && board[i][j] != 'O')
				return true;
			}
		}
		return false;
	}
	pair<int,int> findBestMove()
	{
		int bestVal = 1000;
		pair<int,int> bestMove = {-1, -1};
		for(int i=0;i<3;i++)
		{
			for(int j=0;j<3;j++)
			{
				if(board[i][j] != 'X' && board[i][j] != 'O')
				{
					char backup = board[i][j];
					board[i][j] = 'O'; // CPU is 'O'
					int moveVal = minimax(true);
					board[i][j] = backup;
					if(moveVal < bestVal)
					{
						bestMove = {i,j};
						bestVal = moveVal;
					}
				}
			}
		}
		return bestMove;
	}
};