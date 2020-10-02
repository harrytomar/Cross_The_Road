#include<iostream>
#include<conio.h >
#include<vector>
#include<bits/stdc++.h>
#include<graphics.h>
#include<time.h>
#include<deque>   // doubly Ended queue can shrink and expand from both the sides
using namespace std;
class cPlayer
{
	public:
		int x,y;
		cPlayer(int width) // constructor
		{
			x = width/2;y=0;  //Player will be in top and mid of road
		}
};
class cLane
{
	private:
		deque<bool> cars;
		bool right;
	public:
		cLane(int width)
		{
			for(int i=0;i<width;i++)
			{
				cars.push_front(true);    // In deque we can push element in front and back also can pop from back and front
				
			}
			right = rand()%2;
		}
		void Move()    // moving of cars like 10000,01000,00100,00010,00001  // ar every time either "" or "#" either comes or not at first position due to that our
		{              // deque all element shift by one towards right then to avoid expanding the queue we pop out last element of that lane;
			if(right)
			{
			
			if(rand()%10 ==1)
			{
				cars.push_front(true);
			}
			else
			{
				cars.push_front(false);
			}
			cars.pop_back(); // removes the last element so that size of deque remains same otherwise 1 element will append each time
		    // 00000001 -> 000000010 remove last
			}
			else
			{
				if(rand()%10==1)
					cars.push_back(true);
				else
					cars.push_back(false);
				cars.pop_front();
			}	
		}
		bool checkpos(int pos)
		{
			return cars[pos];  //00010  position 3 is true
		}
		void changedir()
		{
			right = !right;
		}
};
class cGame
{
	private:
		bool quit;
		int numberOfLanes;
		int width;
	
		cPlayer *player;
		vector<cLane*>map;
	public:
			int score=0;
		cGame(int w =20,int h =10)
		{
			numberOfLanes =h;
			width =w;
			quit = false;
			for(int i=0;i<numberOfLanes;i++)
			{
				map.push_back(new cLane(width));
			}
			player = new cPlayer(width);
			
		}
		int score1()
		{
			return score;
		}
		void Draw()
		{
			system("cls");
			for(int i=0;i<numberOfLanes;i++)
			{
				for(int j=0;j<width;j++)
				{
					if(i==0 && (j==0 || j==width-1)) cout<<"S";
					if(i==numberOfLanes-1 && (j==0 || j==width-1)) cout<<"F";
					if(map[i]->checkpos(j) && i!=0 && i!=numberOfLanes-1)
					{
						cout<<"#";                    // if(00010) the at position 1 it will print #
					}
					else
					{
						if(player->x==j && player->y==i)
						{
							cout<<"V";                // when we press w,s,a,d then x and y changes so V also print on those x and y's;
						}
						else
						{
							cout<<" ";    // if(no # or we move V up,down etc the that place should become empty so " "; 
						}
					}
					
				}
				cout<<endl;
			}
		
		}
		void Input()
		{
			if(_kbhit())
			{
				char current = _getch();
				if(current == 'a')
					player->x--;
				if(current == 'd')
					player->x++;
				if(current == 's')
					player->y++;
				if(current == 'w')
					player->y--;
				if(current == 'q')
					quit = true;	
			}
		}
		void Logic()
		{
			for(int i=1;i<numberOfLanes-1;i++) // leave first and last lane
			{
				if(rand()%10==1)
					map[i]->Move();
				if(map[i]->checkpos(player->x) && player->y ==i)
				{
					quit = true;
					cout<<endl;
				}
					
			}
			if(player->y == numberOfLanes-1)
			{
				score++;
				player->y=0;
				map[rand()%numberOfLanes]->changedir();
			}
				
		}
		void Run()
		{
			while(!quit)
			{
				Input();
				Draw();
				Logic();
			}
		}
};
int main()
{
	srand(time(NULL));
	cGame game(40,5);
	game.Run();
	int x = game.score1();
	cout<<"Score:"<<x<<endl;
	cout<<"*******Game Over********\n";
	getchar();
	return 0;

}
