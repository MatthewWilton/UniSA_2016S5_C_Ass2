#include <iostream>

using namespace std;

//board size, set number for a different board size
const int bSize = 10;
//the actual board
string board [bSize][bSize];

int main() {
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
    //cells are set on left half
    //then "symmetrically" mirrored and set on the right half
    for(int h=1; h<bSize; h++){
        //height and width symmetry
        int hs,ws;
        for(int w=1; w<(bSize/2)+1; w++){
            //boards smaller than 4x4
            if(bSize < 5){
                num = 1;
            }
            else{
                //board is 5x5 and sets middle 4 cells to O's
                if(bSize==5 && (w==2&&h==2||w==2&&h==3)){
                    num = 1;
                }
                else{
                    num = rand()%4;
                }
            }
            //mirrored symmetry calculated to be:
            //the positive of the height take the board size and width take the board size
            //abs() turns negative integer into a positive one
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

    //prints X's and O's to the screen
    //uncomment if you want to see the layout of the puzzle
    //useful to see why bigger than 10x10 is an infinite loop(most of the time)
    /*for(int h=0; h<bSize; h++){
        for (int w = 0; w < bSize; w++) {
            cout << board[h][w] << " ";
            if (w == bSize - 1) {
                cout << "\n";
            }
        }
    }
    cout << "\n";*/

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
                            if(num == /*string to int*/atoi(board[h][pos].c_str())){
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

    //print the X's and numbers
    for(int h=0; h<bSize; h++){
        for (int w = 0; w < bSize; w++) {
            cout << board[h][w] << " ";
            if (w == bSize - 1) {
                cout << "\n";
            }
        }
    }
}
