#include<iostream>
#include<fstream>
#include<stack>
#include<conio.h>
#include"CPU Mode.h"
#define RESET       "\033[0m"
#define BOLDRED     "\033[1m\033[31m"      // Bold Red 
#define BOLDCYAN    "\033[1m\033[36m"      // Bold Cyan 
#define BOLDWHITE   "\033[1m\033[37m"      // Bold White
using namespace std;
class tickTacToe
{
	char board[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};  //2D Array
	int row,column;
	stack<pair<int,int>>moveStack; // to store moves for undo, to store the pair of int representing rows & columns
	char turn='X';
	bool draw = false;
	char Player1Score = '0';
	char Player2Score = '0';
	public:
	void displayBoard()
	{
		system("cls");
		cout<<BOLDWHITE<<"     TICK TACK TOE\n"<<endl;
		cout<<RESET<<BOLDRED<<"\tPlayer 1 [X]: "<<Player1Score<<endl<<RESET<<BOLDCYAN<<"\tPlayer 2 [O]: "<<Player2Score<<endl<<RESET<<BOLDWHITE<<endl;
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
	void playerTurn()
	{
		int choice;
		if(turn=='X')
		cout<<BOLDRED<<"\n\t Player 1 [X] turn: ";
		if(turn=='O')
		cout<<BOLDCYAN<<"\n\t Player 2 [O] turn: ";
		cin>>choice;
		switch(choice)
		{
			case 1: row=0; column=0; break;
			case 2:	row=0; column=1; break;
			case 3:	row=0; column=2; break;
			case 4:	row=1; column=0; break;
			case 5:	row=1; column=1; break;
			case 6:	row=1; column=2; break;
			case 7:	row=2; column=0; break;
			case 8:	row=2; column=1; break;
			case 9:	row=2; column=2; break;
			default:
				cout<<"Invalid choice"<<endl;
				getch();
				INTERFACE();
				break;
		}
		if(turn=='X' && board[row][column]!='X' && board[row][column]!='O')
		{
			cout<<RESET<<BOLDRED<<"X";
			board[row][column]='X';
			moveStack.push({row,column}); // Pushing the Last move entered by the user
			turn='O';
		}
		else if(turn=='O' && board[row][column]!='X' && board[row][column]!='O')
		{
			cout<<RESET<<BOLDCYAN<<"O";
			board[row][column]='O';
			moveStack.push({row,column}); // Pushing the Last move entered by the user
			turn='X';
		}
		else
		{
			cout<<"Box already filled! \n Please try again\n\n";
			playerTurn();
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
    void undoMove()
    {
    	if(!moveStack.empty())
    	{
    		auto lastMove = moveStack.top();
    		moveStack.pop();
    		board[lastMove.first][lastMove.second] = '1' + (3 * lastMove.first + lastMove.second);
    		if(turn=='X')
    		{
    			turn = 'O';
			}
			else
			{
				turn = 'X';
			}
			displayBoard();
		}
		else
		{
			cout<<"No Moves to Undo"<<endl;
		}
	}
    void saveGame()
    {
    	ofstream file("Player vs Player.txt");
    	file<<turn<<"\n"; // Storing Turns Enter by the user on RunTime
    	for(int i=0;i<3;i++)
    	{
    		for(int j=0;j<3;j++)
    		{
    			file<<board[i][j];
			}
			file<<endl;
		}
		file<<Player1Score<<"\n";
		file<<Player2Score<<"\n";
		file.close();
	}
	void loadGame()
	{
		ifstream file("Player vs Player.txt");
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
			file>>Player1Score;
			file>>Player2Score;
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
			cout<<"Do you want to Undo Last Move? (y/n) : ";
			cin>>choice;
			if(choice=='y') undoMove();
			gameOver();
			saveGame();
		}
		if(turn=='O' && draw==false)
		{
			Player1Score++;
			displayBoard();
			cout<<BOLDRED<<"\n\tPlayer 1 [X] Win the Game. Congratulations!"<<RESET<<endl;
		}
		else if(turn=='X'&& draw==false)
		{
			Player2Score++;
			displayBoard();
			cout<<BOLDCYAN<<"\n\tPlayer 2 [O] Win the Game. Congratulations!"<<RESET<<endl;
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
	void mainGameInterface()
	{
		t:
		char choice;
		do
		{
			system("cls");
			cout<<BOLDWHITE<<"------------------------------"<<endl;
			cout<<"|         TIC TAC TOE        |"<<endl;
			cout<<"------------------------------"<<RESET<<endl;
			cout<<BOLDCYAN<<"1. Start Game"<<RESET<<endl;
			cout<<BOLDWHITE<<"2. Load Game"<<RESET<<endl;
			cout<<BOLDRED<<"3. Exit"<<RESET<<endl;
			cout<<"Select Option: ";
			cin>>choice;
			if(choice=='1')
			{
				x:
				system("cls");
				cout<<BOLDWHITE<<"Select Modes:"<<RESET<<endl;
				cout<<BOLDCYAN<<"1. Player vs Player"<<RESET<<endl;
				cout<<BOLDRED<<"2. Player vs CPU"<<RESET<<endl;
				cout<<"Select Option: ";
				cin>>choice;
				if(choice=='1') INTERFACE();
				else if(choice=='2')
				{
					CPU C1;
					C1.INTERFACE();
				}
				else
				{
					goto x;
				}
			}
			else if(choice=='2')
			{
				p:
				system("cls");
				cout<<BOLDWHITE<<"Select Modes to Load Game:"<<RESET<<endl;
				cout<<BOLDCYAN<<"1. Player vs Player"<<RESET<<endl;
				cout<<BOLDRED<<"2. Player vs CPU"<<RESET<<endl;
				cout<<"Select Option: ";
				cin>>choice;
				if(choice=='1') loadGame();
				else if(choice=='2')
				{
					CPU C1;
					C1.loadGame();
				}
				else
				{
					goto p;
				}
			}
			else if(choice=='3')
			{
				cout<<"Exiting"<<endl;
				break;
			}
			else
			{
				goto t;
			}
		}while(true);	
	}
};
int main()
{
	tickTacToe T1;
	T1.mainGameInterface();
	return 0;
}