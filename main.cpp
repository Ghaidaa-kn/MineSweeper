#include<iostream>
#include<time.h>
#include<ctime>
#include<cstdlib>
using namespace std;

static char player_grid[10][10]; ///grid that visible to the player
static char mines_grid[10][10]; ///grid with the positions of the mines and the number of each square
static char input_ch; ///it must be 's'
static bool lose = false;

void input_char();
void create_grid();
void create_mines_grid(int);
void reveal(int , int);
void reveal_square();
void square_num(int , int);
void display_grid(char);
void check_game();


int main()
{

cout<<endl;
cout<<"START GAME  ^_^ "<<endl;
cout<<endl;

int num = 10;
create_grid();
create_mines_grid(num);
check_game();

return 0;
}



void input_char() ///to process the entered char
{
   cout<<" Enter S , Then Enter Positions of the Square "<<endl;
   cin >> input_ch;

    switch (input_ch){
    case 's': reveal_square();
    break;
    default : input_char();
    }
}


void create_grid() ///to fill the shown grid by '?' at the beginning of the game
{
    for(int i = 0 ; i < 10 ; i++)
        for(int j = 0 ; j < 10 ; j++)
            player_grid[i][j] = '?';
}


void create_mines_grid(int num) ///to create the hidden game grid which contain mines and numbers
{

  int c = 0;
  for(int i = 0 ; i < 10 ; i++)
        for(int j = 0 ; j < 10 ; j++)
            mines_grid[i][j] = '0';

        srand(time(NULL));
        int i = 0;
        int j = 0;
 while(c < num)
    {
        int i = rand()%10;
        int j = rand()%10;
        if(mines_grid[i][j] == '0'){
            mines_grid[i][j] = '*';

            square_num(i-1,j);
            square_num(i+1,j);
            square_num(i,j-1);
            square_num(i,j+1);
            square_num(i-1,j-1);
            square_num(i-1,j+1);
            square_num(i+1,j-1);
            square_num(i+1,j+1);
            c++;
        }
    }

}


void reveal(int i,int j) ///to reveal a square with given coordinates
{
if (player_grid[i][j] =='?' && mines_grid[i][j]!='*' && i>=0 && i<10 && j>=0 && j<10)
    {
    player_grid[i][j] = mines_grid[i][j];

    if(mines_grid[i][j] == '0')
        {
        reveal(i,j-1);
        reveal(i,j+1);
        reveal(i-1,j);
        reveal(i+1,j);
        reveal(i-1,j-1);
        reveal(i+1,j-1);
        reveal(i+1,j+1);
        reveal(i-1,j+1);
        }
    }
}


void reveal_square() ///to open specified coordinates
{
int i,j;

do
cin >> i >> j;
while(i<0 || i>9 || j<0 || j>9);

if(mines_grid[i][j] == '*')
    {
        player_grid[i][j] = '*';
        lose = true;

        for(int i = 0 ; i < 10 ; i++)
            for(int j = 0 ; j < 10 ; j++)
                if(mines_grid[i][j] == '*')
                    player_grid[i][j] = '*';
    }

    else
        reveal(i,j);
}


void square_num(int i,int j) ///increases the number of a square by 1
{
if(i>=0 && i<10 && j>=0 && j<10 && mines_grid[i][j]!= '*')
  mines_grid[i][j]++;
}


void display_grid(char arr[10][10]) ///to print the player grid
{

    cout<<"    ";
    for(int i = 0 ; i < 10 ; i++)
        cout<<"  "<< i;

    cout<<endl<<"  ";
    for(int i = 0 ; i < 32 ; i++)
        cout<< "_" ;
        cout<<endl;

    for(int i = 0 ; i < 10 ; i++){
            cout<< i <<"  "<<"|";
        for(int j = 0 ; j < 10 ; j++)
            cout<<"  "<< arr[i][j];
            cout<<endl;
    }
}


void check_game() ///to check the result of the game....lose or win
{
    while(!lose)
{
    display_grid(player_grid);
    cout<<endl;
    input_char();
}

if(lose)
    {
       display_grid(player_grid);
       cout<<endl<<"GAME OVER -_- "<<endl;
    }else
       cout<<endl<<"YOU WIN *_* ";
}


