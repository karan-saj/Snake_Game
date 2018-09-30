#include<iostream>
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<windows.h>

using namespace std;

struct Snake
{
	int x;
	int y;
	struct  Snake *next;
};


class Game
{
	char p;
	char mat[20][60];
	struct Snake *head;

public:
	Game()
	{
		head=NULL;
		createBoard();

		int a=(rand()%(5-1))+1;
		int b=(rand()%(50-1))+1;

		for(int i=0;i<5;i++)
		{
		 ins(a,b);
		 a=a,b=b+1;
		}
		createFood();
		createPoison();
		printSnake();
		printBoard();
		option(a,b);
	}

	struct Snake *create(int a,int b)
	{
	  struct Snake *ptr = new Snake();
	  ptr->x=a;
	  ptr->y=b;
	  ptr->next=NULL;
	  return(ptr);
	}

	void createBoard()
	{
		for(int i=0;i<20;i++)
		{
				for(int j=0;j<60;j++)
				{
						if(j==0||j==59||i==19)
						{
								mat[i][j]='#';
						}
						else
						{
								mat[i][j]=' ';
						}
				}
		}
	}

	void clearScreen()
	{
			HANDLE hOut;
			COORD Position;

			hOut = GetStdHandle(STD_OUTPUT_HANDLE);

			Position.X = 0;
			Position.Y = 0;
			SetConsoleCursorPosition(hOut, Position);
	}

	void createFood()
	{
	  int x=(rand()%(20-1))+(1);
		int y=(rand()%(60-1))+(1);
	  if(x>0&&x<20||y>0&&y<80)
	  {
	    if(mat[x][y]=='*'||mat[x][y]=='#'||mat[x][y]=='P')
				createFood();
	    else
				mat[x][y]='F';
	  }
	}

	void createPoison()
	{
	  int x=(rand()%(20-1))+(1);
		int y=(rand()%(60-1))+(1);
	  if(x>0&&x<20||y>0&&y<80)
	  {
	    if(mat[x][y]=='*'||mat[x][y]=='#'||mat[x][y]=='F')
				createPoison();
	    else
				mat[x][y]='P';
	  }
	}

	void ins(int x,int y)
	{
	  struct Snake *t,*temp;
	  temp=create(x,y);
	  if(head==NULL)
	  {
	      head=temp;
	  }
	  else
	  {
	   temp->next=head;
	   head=temp;
	  }
	}

	void printSnake()
	{
	struct Snake *t;
	t=head;
	mat[head->x][head->y]='H';
	t=t->next;
	while(t->next!=NULL)
	{
	   mat[t->x][t->y]='*';
	   t=t->next;
	}
	mat[t->x][t->y]='T';
	}
	void printBoard()
	{
	  int i,j;
	  cout<<"Welcome To The Snake Game\nPress 'a' to move left\nPress 'd' to move right\nPress 's' to move down\nPress 'w' to move up\n";
	  cout<<"Eat F to increase length\nCaution length decreases if you eat P\n";
	  for(i=0;i<20;i++)
	  {
	      for(j=0;j<60;j++)
	      {
	          cout<<mat[i][j];
	      }
	      cout<<endl;
	  }
	}
	void shift()
	{
	  struct Snake *t,*temp;
	  t=head;
	  while(t->next!=NULL)
	  {
	      temp=t;
	      t=t->next;
	  }
	  temp->next=NULL;
	  mat[t->x][t->y]=' ';
	}
	int check(int a,int b)
	{
	  if(mat[a][b]=='*')
	      return 1;
	}
	void option(int a,int b)
	{
	  int c;
	  shift();
	  b=b-1;
	  if(b==0)
	  {
	   b=58;
	  }
	  ins(a,b);

	  char ch;
    while(1)
    {
    	if(kbhit())
        ch=getch();
      switch(ch)
      {
      case 'a':
          {
						if(p=='d')
						{
							ch='d';
							break;
						}
            shift();
            b=b-1;
            if(b==0)
            {
              b=58;
            }
            ins(a,b);
            c=check(a,b);
						p=ch;
            break;
        }
      case 'd':
          {
						if(p=='a')
						{
							ch='a';
							break;
						}
            shift();
            b=b+1;
            if(b==59)
            {
                b=1;
            }
            ins(a,b);
            c=check(a,b);
						p=ch;
            break;
        }
      case 's':
          {
						if(p=='w')
						{
							ch='w';
							break;
						}
            shift();
            a=a+1;
            if(a==19)
            {
                a=1;
            }
            ins(a,b);
            c=check(a,b);
						p=ch;
						break;
        }
      case 'w':
          {
						if(p=='s')
						{
							ch='s';
							break;
						}
            shift();
            a=a-1;
            if(a==0)
            {
                a=18;
            }
            ins(a,b);
            c=check(a,b);
						p=ch;
            break;
        }
      }
      if(mat[a][b]=='F')
      {
          ins(a,b);
          createFood();
      }
      else if(mat[a][b]=='P')
      {
          shift();
          createPoison();
      }
      if(c==1)
      {
          cout<<"\n\n*************GAME OVER*************";
          break;
      }
      else
      {
				clearScreen();
				printSnake();
				printBoard();
      }
    }
	}
};

int main()
{
	Game g;
	return 0;
}
