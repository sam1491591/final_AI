#include <iostream>
#include <fstream>
#include <array>
#include <vector>
#include <cstdlib>
#include <ctime>

struct Point {
    int x, y;
};

int player, nonplayer;
const int SIZE = 8;

std::array<std::array<int, SIZE>, SIZE> board;
std::vector<Point> next_valid_spots;
std::vector<int> value;
std::vector<int> same;

void read_board(std::ifstream& fin) {
    fin >> player;
    if(player==1)nonplayer=2;
    else nonplayer=1;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void read_valid_spots(std::ifstream& fin) {
    int n_valid_spots, blackwhite[3];
    int temp=0;
    fin >> n_valid_spots;
    ///if(player==1)player = 2;
    ///else player = 1;
    int x, y;
    for (int i = 0; i < n_valid_spots; i++) {
        int form[8][8] = {1000, -400, 70, 60, 60, 70, -400, 1000, -400, -500, 3, 3, 3, 3, -500, -400, 70, 3, 25, 4, 4, 25, 3, 70, 60, 3, 4, 0, 0, 4, 3, 60, 60, 3, 4, 0, 0, 4, 3, 60, 70, 3, 25, 4, 4, 25, 3, 70, -400, -500, 3, 3, 3, 3, -500, -400, 1000, -400, 70, 60, 60, 70, -400, 1000};
        blackwhite[0]=0;
        blackwhite[1]=0;
        blackwhite[2]=0;
        temp=0;
        fin >> x >> y;
        next_valid_spots.push_back({x, y});
        if(board[0][0]==player){
            form[0][1] =200;form[1][0] = 200;form[1][1] = 150;}
        if(board[0][7]==player){
            form[0][6] =200;form[1][7] = 200;form[1][6] = 150;}
        if(board[7][0]==player){
            form[6][0] =200;form[7][1] = 200;form[6][1] = 150;}
        if(board[7][7]==player){
            form[7][6] =200;form[6][7] = 200;form[6][6] = 150;}
        for(int b=1;b<8;b++){
            if(y+b<8 && board[x][y+b] == nonplayer){
                temp += form[x][y+b];
                continue;
            }
            else if(board[x][y+b] == 0){
                if(board[x][y]==nonplayer && board[x][y+b+1]==nonplayer)
                    blackwhite[player]+= 4;
                //else if((board[x][y]==nonplayer && board[x][y+b+1]== 0) || (board[x][y]==0 && board[x][y+b+1]==nonplayer))
                   // blackwhite[player]-= 4;
                break;
            }
            else if(b!=1 && y+b<8 && board[x][y+b] == player){
                blackwhite[player] += temp;
                break;
            }
        }
        temp=0;
        for(int b=1;b<8;b++){
            if(x+b<8 && board[x+b][y] != player){
                temp += form[x+b][y];
                continue;
            }
            else if(b!=1 && x+b<8 && board[x+b][y] == player){
                blackwhite[player] += temp;
                break;
            }
            else if(board[x+b][y] == 0){
                if(board[x][y]==nonplayer && board[x+b+1][y]==nonplayer)
                    blackwhite[player]+= 4;
               // else if((board[x][y]==nonplayer && board[x+b+1][y]== 0) || (board[x][y]==0 && board[x+b+1][y]==nonplayer))
                   // blackwhite[player]-= 4;
                break;
            }
        }
        temp=0;
        for(int b=1;b<8;b++){
            if(y-b>=0 && board[x][y-b] != player){
                temp += form[x][y-b];
                continue;
            }
            else if(b!=1 && y-b>=0 && board[x][y-b] == player){
                blackwhite[player] += temp;
                break;
            }
            else if(board[x][y-b] == 0){
                if(board[x][y]==nonplayer && board[x][y-b-1]==nonplayer)
                    blackwhite[player]+= 4;
                //else if((board[x][y]==nonplayer && board[x][y-b-1]== 0) || (board[x][y]==0 && board[x][y-b-1]==nonplayer))
                   // blackwhite[player]-= 4;
                break;
            }
        }
        temp=0;
        for(int b=1;b<8;b++){
            if(x-b>=0 && board[x-b][y] != player){
                temp += form[x-b][y];
                continue;
            }
            else if(b!=1 && x-b>=0 && board[x-b][y] == player){
                blackwhite[player] += temp;
                break;
            }
            else if(board[x-b][y] == 0){
                if(board[x][y]==nonplayer && board[x-b-1][y]==nonplayer)
                    blackwhite[player]+= 4;
               // else if((board[x][y]==nonplayer && board[x-b-1][y]== 0) || (board[x][y]==0 && board[x-b-1][y]==nonplayer))
                  //  blackwhite[player]-= 4;
                break;
            }
        }
        temp=0;
        for(int b=1;b<8;b++){
            if(y+b<8 && x+b<8 && board[x+b][y+b] != player){
                temp += form[x+b][y+b];
                continue;
            }
            else if(b!=1 && y+b<8 && x+b<8 && board[x+b][y+b] == player){
                blackwhite[player] += temp;
                break;
            }
            else if(board[x+b][y+b] == 0){
                if(board[x][y]==nonplayer && board[x+b+1][y+b+1]==nonplayer)
                    blackwhite[player]+= 4;
                //else if((board[x][y]==nonplayer && board[x+b+1][y]== 0) || (board[x][y]==0 && board[x+b+1][y]==nonplayer))
                  //  blackwhite[player]-= 4;
                break;
            }
        }
        temp=0;
        for(int b=1;b<8;b++){
            if(y+b<8 && x-b>=0 && board[x-b][y+b] != player){
                temp += form[x-b][y+b];
                continue;
            }
            else if(b!=1 && y+b<8 && x-b>=0 && board[x-b][y+b] == player){
                blackwhite[player] += temp;
                break;
            }
            else if(board[x-b][y+b] == 0){
                if(board[x][y]==nonplayer && board[x-b-1][y+b+1]==nonplayer)
                    blackwhite[player]+= 4;
               // else if((board[x][y]==nonplayer && board[x-b-1][y+b+1]== 0) || (board[x][y]==0 && board[x-b-1][y+b+1]==nonplayer))
                 //   blackwhite[player]-= 4;
                break;
            }
        }
        temp=0;
        for(int b=1;b<8;b++){
            if(y-b>=0 && x+b<8 && board[x+b][y-b] != player){
                temp += form[x+b][y-b];
                continue;
            }
            else if(b!=1 && y-b>=0 && x+b<8 && board[x+b][y-b] == player){
                blackwhite[player] += temp;
                break;
            }
            else if(board[x+b][y-b] == 0){
                if(board[x][y]==nonplayer && board[x+b+1][y-b-1]==nonplayer)
                    blackwhite[player]+= 4;
               // else if((board[x][y]==nonplayer && board[x+b+1][y-b-1]== 0) || (board[x][y]==0 && board[x+b+1][y-b-1]==nonplayer))
                   // blackwhite[player]-= 4;
                break;
            }
        }
        temp=0;
        for(int b=1;b<8;b++){
            if(y-b>=0 && x-b>=0 && board[x-b][y-b] != player){
                temp += form[x-b][y-b];
                continue;
            }
            else if(b!=1 && y-b>=0 && x-b>=0 && board[x-b][y-b] == player){
                blackwhite[player] += temp;
                break;
            }
            else if(board[x-b][y-b] == 0){
                if(board[x][y]==nonplayer && board[x-b-1][y-b-1]==nonplayer)
                    blackwhite[player]+= 4;
               // else if((board[x][y]==nonplayer && board[x-b-1][y-b-1]== 0) || (board[x][y]==0 && board[x-b-1][y-b-1]==nonplayer))
                   // blackwhite[player]-= 4;
                break;
            }
        }
        value.push_back(form[x][y] + blackwhite[player]);
        same.push_back(blackwhite[player]);
    }
}

void write_valid_spot(std::ofstream& fout){
    int n_valid_spots = next_valid_spots.size();
    int ans, temp=-2000, /*same1,*/ a=0;
    Point p;
    /// Keep updating the output until getting killed.
    while (true) {
        /// Choose random spot. (Not random uniform here)
        for(a=0;a<n_valid_spots;a++){
            if(temp == -2000){
                ans = a;
                //same1 = same[a];
                temp = value[a];
            }
            else if(temp < value[a]){
                ans = a;
                //same1 = same[a];
                temp = value[a];
            }
            /*else if(temp == value[a]){
                if(same1 < same[a]){
                    ans = a;
                    same1 = same[a];
                    temp = value[a];
                }
            }*/
        }
        p = next_valid_spots[ans];
        /// Remember to flush the output to ensure the last action is written to file.
        fout << p.x << " " << p.y << std::endl;
        fout.flush();
        value.clear();
        same.clear();
        next_valid_spots.clear();
    }
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    read_valid_spots(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
