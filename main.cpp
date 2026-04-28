#include<iostream>
#include<algorithm>
#include<climits>
#include<vector>
using namespace std;
class Game{
private:
    int b[5][5];
    int pointcount;
public:
    Game(){
        for(int i=0;i<5;i++){
            for(int j=0;j<5;j++){
                b[i][j]=0;
            }
        }
        pointcount=0;
    }
    void show()const{
        cout<<endl;
        cout<<" ----------------"<<endl;
        for(int i=1;i<=3;i++){
            cout<<" | ";
            for(int j=1;j<=3;j++){
                cout<<b[i][j]<<" ";
                cout<<" | ";
            }
            cout<<endl<<" ----------------"<<endl;
        }
    }
    int judge()const{//判断对局是否结束，0表示平局，1表示黑色赢了，2表示白色赢了,666表示没结束
        int ans=666;
        if(pointcount==9){//如果棋盘已经满了，先把ans设置为0(默认平局)，如果之后检测到行列或者对角线有一样的棋子再改ans
            ans=0;
        }
        for(int i=1;i<=3;i++){//判断行是否有一样的棋子
            if(b[i][1]==b[i][2]&&b[i][2]==b[i][3]&&b[i][1]!=0){
                ans=b[i][1];
                break;
            }
        }
        for(int i=1;i<=3;i++){//判断列是否有一样的棋子
            if(b[1][i]==b[2][i]&&b[2][i]==b[3][i]&&b[1][i]!=0){
                ans=b[1][i];
                break;
            }
        }

        //判断对角线上是否有一样的棋子
        if(b[1][1]==b[2][2]&&b[2][2]==b[3][3]&&b[1][1]!=0){
            ans=b[1][1];
        }
        if(b[1][3]==b[2][2]&&b[2][2]==b[3][1]&&b[1][3]!=0){
            ans=b[1][3];
        }

        return ans;
    }
    int score()const{//判断最终得分，如果黑色输了则是负数，赢了则是正数，平局则是0
        int temp=judge();
        if(temp==0){
            return temp;
        }else if(temp==1){
            return 10-pointcount;
        }else{
            return pointcount-10;
        }
    }
    void user_set(){//用户落子
        int x,y;
        cout<<"请输入你想下的位置的x坐标和y坐标(1<=x<=3,1<=y<=3)，中间用空格隔开"<<endl;
        while(cin>>x>>y){
            if(x<1||x>3||y<1||y>3){
                cout<<"请认真看x，y的范围哦TwT"<<endl;//检测x，y是否超出范围
                continue;
            }

            //检测x，y处是否有棋子
            if(b[x][y]==0){
                break;
            }else{
                cout<<"这个位置已经有棋子了！请重新输入"<<endl;
            }
        }
        b[x][y]=1;
        pointcount++;
    }
    void computer_set(){//电脑落子
        vector<int> temp=predict();
        int tarx=temp[1];
        int tary=temp[2];
        b[tarx][tary]=2;
        pointcount++;
    }
    void play(){
        int count=0;
        show();
        while(1){
            if(judge()==0){
                cout<<"你和电脑打平了!"<<endl;
                break;
            }else if(judge()==1){
                cout<<"你赢了!干得漂亮!"<<endl;
                break;
            }else if(judge()==2){
                cout<<"废物，你输给了电脑!"<<endl;
                cout<<"是时候精进你的棋艺了!^_^"<<endl;
                break;
            }
            if(count%2==0){
                user_set();
            }else{
                computer_set();
            }
            show();
            count++;
        }
    }
    vector<int> predict(){//帮助电脑预测下一步应该怎么走
        vector<int> finalans(3,0);
        if(judge()!=666){
            finalans[0]=score();
            finalans[1]=finalans[2]=0;
            return finalans;//如果对局已经结束，返回score
        }

        int pointcolor=pointcount%2+1;
        int ans;
        int ansx,ansy;
        if(pointcolor==1){
            ans=INT_MIN;
        }else{
            ans=INT_MAX;
        }
        for(int i=1;i<=3;i++){
            for(int j=1;j<=3;j++){

                if(b[i][j]!=0){
                    continue;//如果当前位置已经有棋子了，忽略
                }

                //放入棋子
                b[i][j]=pointcolor;
                pointcount++;

                //进入下一层
                int number=predict()[0];
                if(pointcolor==1){
                    if(number>ans){
                        ans=number;
                        ansx=i;
                        ansy=j;
                    }
                }else{
                    if(number<ans){
                        ans=number;
                        ansx=i;
                        ansy=j;
                    }
                }

                //回溯
                b[i][j]=0;
                pointcount--;


            }
        }
        finalans[0]=ans;
        finalans[1]=ansx;
        finalans[2]=ansy;
        return finalans;
    }
};
int main(){
    Game temp;
    temp.play();
}
