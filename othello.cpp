#include<iostream>
#include<stdio.h>
#include<graphics.h>
#include<vector>

using namespace std;

struct triplet
{
    int first;
    int second;
    int third;
};
triplet make_triplet(int x,int y,int z)
{
    triplet T;
    T.first=x;
    T.second=y;
    T.third=z;

    return T;
}

class OthelloGame
{
    int mat[8][8];
    int blackScore;
    int whiteScore;

    int maxx=getmaxx();
    int maxy=getmaxy();

    int len=min(maxx-100,maxy-100)/8;

    int x1=50,y1=50;
    int x2=x1+len*8,y2=y1+len*8;


    void updateScore()
    {
        int p1=0,p2=0;
        for(int i=0;i<8;i++)
        {   for(int j=0;j<8;j++)
            {
                if(mat[i][j]==-1)
                    p1++;
                else if(mat[i][j]==1)
                    p2++;

            }
        }
        blackScore=p1;
        whiteScore=p2;
    }
    void showScore()
    {
        cout<<"\tBLACK SCORE :"<<blackScore<<endl;
        cout<<"\tWHITE SCORE :"<<whiteScore<<endl;
        cout<<endl;
    }
    void displayScore()
    {
        char arr[10];
        sprintf(arr,"SCORES");
        setcolor(WHITE);
        outtextxy(x2+50,y1,arr);

        int x,y;
        x=x2+50,y=y1+50;
        setfillstyle(SOLID_FILL,GREEN);
        bar(x+2,y+2,x+len-2,y+len-2);

        setfillstyle(SOLID_FILL,BLACK);
        setcolor(BLACK);
        circle(x+(len/2),y+(len/2),len/2-6);
        floodfill(x+(len/2),y+(len/2),BLACK);

        sprintf(arr,"%d",blackScore);
        setcolor(WHITE);
        outtextxy(x+len+1,y+len/2-1,arr);

        x=x2+50,y=y1+100;
        setfillstyle(SOLID_FILL,GREEN);
        bar(x+2,y+2,x+len-2,y+len-2);

        setfillstyle(SOLID_FILL,WHITE);
        setcolor(WHITE);
        circle(x+(len/2),y+(len/2),len/2-6);
        floodfill(x+(len/2),y+(len/2),WHITE);

        sprintf(arr,"%d",whiteScore);
        outtextxy(x+len+1,y+len/2-1,arr);

    }

    bool isBoardFull()
    {
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                if(mat[i][j]==0)
                    return false;
            }
        }
        return true;
    }

public:
    OthelloGame()           //constructor to initialize the game
    {
        for(int i=0;i<8;i++)
        {   for(int j=0;j<8;j++)
                mat[i][j]=0;
        }
        mat[3][3]=1;
        mat[4][4]=1;
        mat[3][4]=-1;
        mat[4][3]=-1;

        blackScore=2;
        whiteScore=2;
    }
    void drawBoard()        //drawing board & displaying scores with graphics
    {
        cleardevice();

        setcolor(YELLOW);
        char arr[10];
        sprintf(arr,"  OTHELLO  ");
        outtextxy(x1 + len*3,y1-20,arr);


        setcolor(WHITE);
        for(int i=0;i<8;i++)
        {
            for(int j=0;j<8;j++)
            {
                int x=x1+j*len;
                int y=y1+i*len;

                setfillstyle(SOLID_FILL,GREEN);
                bar(x+2,y+2,x+len-2,y+len-2);

                if(mat[i][j]!=0)
                {
                    if(mat[i][j]==-1)
                    {   setfillstyle(SOLID_FILL,BLACK);
                        setcolor(BLACK);
                        circle(x+(len/2),y+(len/2),len/2-4);
                        floodfill(x+(len/2),y+(len/2),BLACK);
                    }
                    else if(mat[i][j]==1)
                    {
                        setfillstyle(SOLID_FILL,WHITE);
                        setcolor(WHITE);
                        circle(x+(len/2),y+(len/2),len/2-4);
                        floodfill(x+(len/2),y+(len/2),WHITE);
                    }


                }

            }
        }

        displayScore();

    }
    void printBoard()       //prints the board and shows the current score
    {
        for(int i=0;i<8;i++)
        {
            cout<<"\t";
            for(int j=0;j<8;j++)
            {
                if(mat[i][j]==0)
                    cout<<"_"<<" ";
                else if(mat[i][j]==-1)
                    cout<<"X"<<" ";
                else if(mat[i][j]==1)
                    cout<<"O"<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
        showScore();
    }
    void resetTiles()       //resets the tiles and the score
    {
        for(int i=0;i<8;i++)
        {   for(int j=0;j<8;j++)
                mat[i][j]=0;
        }
        mat[3][3]=-1;
        mat[4][4]=-1;
        mat[3][4]=1;
        mat[4][3]=1;

        blackScore=2;
        whiteScore=2;

    }
    void showCurrentTurn(int playerNo)
    {

        int x,y;
        char arr[10];
        if(playerNo==-1)
        {
            x=x2+50,y=y1+50;
            setcolor(YELLOW);
            sprintf(arr,"%d",blackScore);
            outtextxy(x+len+1,y+len/2-1,arr);
        }

        else
        {

            x=x2+50,y=y1+100;
            setcolor(YELLOW);
            sprintf(arr,"%d",whiteScore);
            outtextxy(x+len+1,y+len/2-1,arr);
        }

    }

    void findRowAndCol(int x,int y,int &i,int &j)
    {
        j=(x-x1)/len;
        i=(y-y1)/len;
    }
    vector<triplet> getLegalMovesForPlayer(int playerNo)
    {
        vector<triplet > legalMoves;
        for(int x=0;x<8;x++)
        {
            for(int y=0;y<8;y++)
            {
                if(mat[x][y]==playerNo)
                {
                        for(int i=-1;i<=1;i++)
                        {
                            if( ((x+i)>7) || ((x+i)<0))
                                continue;

                            for(int j=-1;j<=1;j++)
                            {
                                if( ((y+j)>7) || ((y+j)<0))
                                    continue;

                                if(mat[x+i][y+j]==-playerNo)
                                {
                                    int tx=x+i;
                                    int ty=y+j;

                                    while(mat[tx][ty]==-playerNo && (tx>=0 && tx <=7) && (ty>=0 && ty<=7))
                                    {
                                        tx=tx+i;
                                        ty=ty+j;
                                    }

                                    if( ((tx>=0 && tx <=7) && (ty>=0 && ty<=7)) && mat[tx][ty]!=playerNo)
                                    {
                                        int count=getNoOfFlips(tx,ty,playerNo);
                                        triplet P=make_triplet(tx,ty,count);
                                        legalMoves.push_back(P);
                                    }
                                }
                            }
                        }
                }
            }
        }
        return legalMoves;
    }
    int getNoOfFlips(int x,int y,int playerNo)
    {
        int startX=x;
        int startY=y;
        int count=0;

        for(int i=-1;i<=1;i++)
        {
            if( ((x+i)>7) || ((x+i)<0))
                continue;

            for(int j=-1;j<=1;j++)
            {
                if( ((y+j)>7) || ((y+j)<0))
                    continue;

                if(i==0 && j==0)
                    continue;

                if(mat[x+i][y+j]==-playerNo)
                {

                    int tx=x+i;
                    int ty=y+j;
                    while(mat[tx][ty]==-playerNo && ((tx>=0 && tx <=7) && (ty>=0 && ty<=7)))
                    {
                        tx=tx+i;
                        ty=ty+j;
                        //cout<<tx<<" "<<ty<<endl;
                    }

                    if( ((tx>=0 && tx <=7) && (ty>=0 && ty<=7)) && mat[tx][ty]==playerNo)
                    {
                        int destX=tx;
                        int destY=ty;
                        //cout<<startX<<" "<<destX<<" "<<i<<endl;
                        //cout<<startY<<" "<<destY<<" "<<j<<endl;

                        int k,l;
                        for(k=startX+i,l=startY+j; k!=destX || l!=destY ; k=k+i,l=l+j)
                        {
                                count++;
                        }
                    }
                }
            }
        }


        //cout<<count<<endl;        //this is the number of tiles that will flip
        return count;
    }
    void makeMove(int x,int y,int playerNo)     //makes move and updates the score
    {

        int startX=x;
        int startY=y;
        mat[x][y]=playerNo;

        int count=0;
        for(int i=-1;i<=1;i++)
        {
            if( ((x+i)>7) || ((x+i)<0))
                continue;

            for(int j=-1;j<=1;j++)
            {
                if( ((y+j)>7) || ((y+j)<0))
                    continue;

                if(i==0 && j==0)
                    continue;

                if(mat[x+i][y+j]==-playerNo)
                {

                    int tx=x+i;
                    int ty=y+j;
                    while(mat[tx][ty]==-playerNo && ((tx>=0 && tx <=7) && (ty>=0 && ty<=7)))
                    {
                        tx=tx+i;
                        ty=ty+j;
                        //cout<<tx<<" "<<ty<<endl;
                    }

                    if( ((tx>=0 && tx <=7) && (ty>=0 && ty<=7)) && mat[tx][ty]==playerNo)
                    {
                        int destX=tx;
                        int destY=ty;
                        //cout<<startX<<" "<<destX<<" "<<i<<endl;
                        //cout<<startY<<" "<<destY<<" "<<j<<endl;

                        int k,l;
                        for(k=startX+i,l=startY+j; k!=destX || l!=destY ; k=k+i,l=l+j)
                        {
                                mat[k][l]=playerNo;
                                count++;
                        }
                    }
                }
            }
        }

        //cout<<count<<endl;        //this is the number of tiles that will flip
        if(playerNo==-1)
        {
            blackScore=blackScore+count+1;
            whiteScore=whiteScore-count;
        }
        else if(playerNo==1)
        {
            whiteScore=whiteScore+count+1;
            blackScore=blackScore-count;
        }
    }

    void showLegalMoves(int playerNo)
    {
        vector<triplet> V=getLegalMovesForPlayer(playerNo);
        for(int i=0;i<V.size();i++)
        {
            int maxx=getmaxx();
            int maxy=getmaxy();

            int len=min(maxx-100,maxy-100)/8;

            int x=50+ (V[i].second)*len;
            int y=50+ (V[i].first)*len;

            setfillstyle(SOLID_FILL,YELLOW);
            setcolor(YELLOW);
            circle(x+(len/2),y+(len/2),len/2-18);
            floodfill(x+(len/2),y+(len/2),YELLOW);

        }

    }
    bool canMakeMove(int playerNo)
    {
        vector<triplet> V=getLegalMovesForPlayer(playerNo);
        if(V.size()!=0)
            return true;
        else
            return false;
    }
    bool isLegalMove(int x,int y,int playerNo)      //checks whether the move by the player is legal or not
    {
        if(x<0 || x>7 || y<0 || y>7)
            return false;

        vector<triplet> V=getLegalMovesForPlayer(playerNo);
        for(int i=0;i<V.size();i++)
        {
            if(V[i].first==x && V[i].second==y)
                return true;
        }
        return false;
    }
    bool isGameOver()
    {
        if(isBoardFull())
            return true;
        if(blackScore==0 || whiteScore==0)
            return true;
        return false;
    }
    int winner()
    {
        if(blackScore>whiteScore)
            return -1;
        else if(blackScore==whiteScore)
            return 0;
        else if(blackScore < whiteScore)
            return 1;
    }
};

int main()
{
    int gdriver=DETECT;
    int gmode;
    char str[]="C:\\TC\\BGI";
    initgraph(&gdriver,&gmode,str);

    OthelloGame G;
    cout<<"\n\t\tOTHELLO GAME \n";
    G.drawBoard();

    int playerTurn;
    cout<<"Enter the player that wants to start :"
        <<"\n\t -1: - Black "
        <<"\n\t  1: - White\n";
    cin>>playerTurn;

    while(!G.isGameOver())
    {
        if(!G.canMakeMove(playerTurn))
        {
            cout<<"\nSorry you have no legal moves ..Hence turn goes to your opponent\n";
            playerTurn=-playerTurn;
            continue;
        }

        //displaying the player whose turn is it
        /*if(playerTurn==-1)
            cout<<"BLACK'S TURN (X)";
        else if(playerTurn == 1)
            cout<<"WHITE'S TURN (O)";*/
        G.showCurrentTurn(playerTurn);

        //showing his legal moves
        G.showLegalMoves(playerTurn);

        /*cout<<"\nPossible Legal Moves :\n";
        vector<triplet> V=G.getLegalMovesForPlayer(playerTurn);
        for(int i=0;i<V.size();i++)
        {
            cout<<V[i].first+1<<" "<<V[i].second+1<<" : "<<V[i].third<<endl;
        }*/

        //entering a move from the player
        int x,y,i,j;
        const int DELAY = 50; // Milliseconds of delay between checks

        while (!ismouseclick(WM_LBUTTONDOWN))
            delay(DELAY);
        getmouseclick(WM_LBUTTONDOWN, x, y);
        G.findRowAndCol(x,y,i,j);
        //cout << "Latest left click at: " << i+1 << " " << j+1 << endl;


        /*cout<<"\nEnter row and column to make move :";
        cin>>x>>y*/

        while(!G.isLegalMove(i,j,playerTurn))
        {
            cout<<"\nNot a legal Move .Please try again : ";
            //cin>>x>>y;
            while (!ismouseclick(WM_LBUTTONDOWN))
            delay(DELAY);
            getmouseclick(WM_LBUTTONDOWN, x, y);
            G.findRowAndCol(x,y,i,j);
            //cout << "Latest left click at: " << i<< " " << j << endl;


        }

        G.makeMove(i,j,playerTurn);
        G.drawBoard();
        playerTurn=-playerTurn;
    }

    G.drawBoard();

    if(G.winner()==-1)
        cout<<"PLAYER 1 : BLACK WINS ";
    else if(G.winner()==1)
        cout<<"PLAYER 2: WHITE WINS ";
    else
        cout<<"Oops It's a draw !!";

    getch();
    closegraph();

}
