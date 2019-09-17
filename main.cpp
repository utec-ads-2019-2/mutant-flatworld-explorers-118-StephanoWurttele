#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class Robot{
private:
	unsigned short int x;
	unsigned short int y;
	char dir;
	unsigned short int xlimit;
	unsigned short int ylimit;
	bool dead;
public:
	Robot(unsigned short int x1, unsigned short int y1, char dire, unsigned short int xl, unsigned int yl):x(x1),y(y1),dir(dire),xlimit(xl),ylimit(yl){
		dead=false;
	};

	void moveForward(int move){
		if(this->dir=='N'){
			if(move==1 and this->y==ylimit)
				return;
			if(this->y+1>ylimit){
				dead=true;
				return;
			}
			this->y++;
		}

		else if(this->dir=='W'){
			if(move==1 and this->x==0)
				return;
			if(this->x-1<0){
				dead=true;
				return;
			}
			this->x--;
		}

		else if(this->dir=='S'){	
			if(move==1 and this->y==0)
				return;
			if(this->y-1<0){
				dead=true;
				return;
			}
			this->y--;	
		}

		else if(this->dir=='E'){
			if(move==1 and this->x==xlimit)
				return;
			if(this->x+1>xlimit){
				dead=true;
				return;
			}
			this->x++;
		}
	};
	void turnLeft(){
		if(this->dir=='N')
			this->dir='W';
		else if(this->dir=='W')
			this->dir='S';
		else if(this->dir=='S')
			this->dir='E';
		else if(this->dir=='E')
			this->dir='N';
	};
	void turnRight(){
		if(this->dir=='N')
			this->dir='E';
		else if(this->dir=='E')
			this->dir='S';
		else if(this->dir=='S')
			this->dir='W';
		else if(this->dir=='W')
			this->dir='N';
	};

	void move(char instruction,bool move){
		if(!dead){
			if(instruction=='R')
				turnRight();
			else if(instruction=='L')
				turnLeft();
			else if(instruction=='F')
				moveForward(move);
		}
	}
	char getDir(){
		return dir;
	};
	unsigned short int getX(){
		return this->x;
	};
	unsigned short int getY(){
		return this->y;
	};
	bool printbot(){
		cout<<this->x<<" "<<this->y<<" "<<this->dir;
		if(dead){
			cout<<" LOST"<<endl;
			return true;
		}
		cout<<endl;
		return false;
	}
};

int main(){
	unsigned short int x,y,xlimit,ylimit;
	char init;
	string dir;
	string s;
	cin>>xlimit>>ylimit;
	vector<bool> temp(ylimit+1,0);
	vector<vector<bool>> safezone;
	for (int i=0;i<xlimit+1;i++){
		safezone.push_back(temp);
	}
	cin.ignore();
	while(cin.peek()!=-1){
		cin>>x>>y>>init;
		Robot bot(x,y,init,xlimit,ylimit);
		cin>>dir;
		for(auto it=dir.begin();it!=dir.end();it++){
			bot.move(*it,safezone[bot.getX()][bot.getY()]!=0);
		}
		if(bot.printbot()){
			safezone[bot.getX()][bot.getY()]=bot.getDir();
		}
		cin.ignore();
	}
	return 0;
}
