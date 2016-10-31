#include <iostream>

using namespace std;

//board size, set number for a different board size
const int bSize = 8;
//the actual board
string board [bSize][bSize];

int main() {

    cout<<board[0][0]<<"\n"<<endl;
    //used throughout as the random number
    int num;
    //helps make the seed for random numbers more random
    srand((unsigned) time(NULL));

    //top row and left column set to blank/X
    for(int h=0; h<bSize; h++){
        board[0][h] = "X";
        for(int w=0; w<1; w++){
            board[h][w] = "X";
        }
    }

    //cells set to X or O
    //X = blank or clue cells
    //O = play/value cells
    //cells are set on top half
    //then "symmetrically" mirrored and set on the bottom half
    for(int h=1; h<(bSize/2); h++) {
        //height and width symmetry
        int hs, ws;
        for (int w = 1; w < bSize; w++) {
            //the cell is on the far right
            if(w == bSize-1){
                //if the cell to the left is X then current cell must be X
                if(board[h][w-1]=="X"){
                    num = 0;
                }
            }
            //cell is not on the top or left most line
            else if(w != 1 && h!=1){
                if(board[h][w-1]=="O" && board[h][w-2]=="X"){
                    num = 1;
                }
                else if(board[h-1][w]=="O" && board[h-2][w]=="X"){
                    num = 1;
                }
                else{
                    num = rand()%2;
                }
            }
            //if the cell is on the top or left most line
            else{
                //cell is the uppermost left cell
                if(w==1 && h==1){
                    if(bSize == 4){
                        num = 1;
                    }
                    else{
                        num = rand()%2;
                    }
                }
                //cell is on the top line
                else if(h==1){
                    //if cell to the immediate left is O and cell left of that is X
                    //then the current cell must be O
                    if(board[h][w-1]=="O" && board[h][w-2]=="X"){
                        num = 1;
                    }
                    else{
                        num = rand()%2;
                    }
                }
                //cell is on the left line
                else{
                    //if cell to the immediate up is O and cell up of that is X
                    //then the current cell must be O
                    if(board[h-1][w]=="O" && board[h-2][w]=="X"){
                        num = 1;
                    }
                    else{
                        num = rand()%2;
                    }
                }
            }


            hs = abs(h-bSize);
            ws = abs(w-bSize);
            if(num == 0){
                board[h][w] = "X";
                board[hs][ws] = "X";
            }
            else{
                board[h][w] = "O";
                board[hs][ws] = "O";
            }
        }
    }

    //puzzle is even
    if(bSize%2 == 0){
        int hs, ws;
        for(int h=(bSize/2); h<(bSize/2)+1; h++) {
            for (int w = 1; w < (bSize/2)+1; w++) {
                if(board[h-1][w]=="X" && board[h+1][w]=="X"){
                    num = 0;
                }
                else if(board[h-1][w]=="O" && board[h-2][w]=="X" ||
                        board[h+1][w]=="O" && board[h+2][w]=="X"){
                    num = 1;
                }
                else{
                    if(w != 1){
                        if(board[h][w-1]=="O" && board[h][w-2]=="X"){
                            num = 1;
                        }
                    }
                    else{
                        num = rand()%3;
                    }
                }

                if(num == 0){
                    hs = abs(h-bSize);
                    ws = abs(w-bSize);
                    board[h][w] = "X";
                    board[hs][ws] = "X";
                }
                else{
                    hs = abs(h-bSize);
                    ws = abs(w-bSize);
                    board[h][w] = "O";
                    board[hs][ws] = "O";
                }
            }
        }
    }

    //assign numbers while also checking
    //if they are already in a line
    for(int h=0; h<bSize; h++){
        for(int w=0; w<bSize; w++){
            if(board[h][w] == "O"){
                //find a number to assign
                bool same;
                do{
                    same = false;
                    num = rand()%9+1;
                    //check numbers to the left
                    int pos = w;
                    while(board[h][pos] != "X"){
                        //starting spot doesn't have a number yet, it has an O
                        if(board[h][pos] != "O"){
                            //atoi used for typecasting string to int
                            if(num == atoi(board[h][pos].c_str())){
                                same = true;
                            }
                        }
                        pos = pos-1;
                    }
                    //check numbers above
                    pos = h;
                    while(board[pos][w] != "X"){
                        if(board[pos][w] != "O"){
                            if(num == atoi(board[pos][w].c_str())){
                                same = true;
                            }
                        }
                        pos = pos-1;
                    }
                    //numbers to the right and below are still O's
                }while(same);
                //assign the number/replace the O
                board[h][w] = to_string(num);
            }
        }
    }

    for(int h=0; h<bSize; h++) {
        for (int w = 0; w<bSize; w++) {
            if(h!=bSize-1){
                if(board[h+1][w]!="X" && board[h][w]=="X"){
                    int downValue  = 0;
                    int hPos = h+1;
                    int wPos = w;
                    bool loop = true;
                    while(loop){
                        downValue = downValue + atoi(board[hPos][wPos].c_str());
                        cout << "h:"<<hPos<<" w:"<<wPos<<" value:"<<board[hPos][wPos]<<" down:"<<downValue<<endl;
                        if(hPos==bSize-1){
                            loop = false;
                        }
                        else if(board[hPos+1][wPos]=="X"){
                            loop = false;
                        }
                        else{
                            hPos += 1;
                        }
                    }
                    if(downValue<10){
                        board[h][w] = "0" + to_string(downValue);
                    }
                    else{
                        board[h][w] = to_string(downValue);
                    }
                }
            }
        }
    }

    //print the X's and numbers
    for(int h=0; h<bSize; h++){
        for (int count = 0; count < bSize; count++)
        {
            //repeating this 5 times
            cout << "       ";
            if(count==bSize-1){
                cout << "\n";
            }
        }
        for (int count = 0; count < bSize; count++)
        {
            //repeating this 5 times
            cout << "       ";
            if(count==bSize-1){
                cout << "\n";
            }
        }
        for (int w = 0; w < bSize; w++) {
            if(board[h][w].length()==1){
                cout << "  "<< board[h][w] << "  ";
            }
            else{
                cout << board[h][w] << "/  " ;
            }
            cout << " ";
            if (w == bSize - 1) {
                cout << "\n";
            }
        }
    }
}
