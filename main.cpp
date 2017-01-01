// Program: Reversi.cpp
// Course : Bachelors in Computer Science
// Year: 2015/2016 Trimester 1
// Name: Mahmoud Abdelazim Ali Eldewaletly
// ID: 1132702480
// Email: 7oda95@live.com
// Phone: 0132184233

#include <iostream>
#include <string>
#include<fstream>
using namespace std;
//Global Constants
const int COLS = 8;
const int ROWS = 8;
//Function Prototypes
void displayTop();
void displayNumColumn();
void displayNumRow();
int displayMenu();
void displayBoard();
char displayHelp();
void playGame(char player, int plB, int plW);
void goToMenu(char x ,char y);
int saveFile(char x, char y, char board[][COLS], char player, int plB, int plW);
void loadGame();
void clearBoard();
int flipDown(int x, int y, char board[][COLS], char player);
int flipUp(int x, int y, char board[][COLS], char player);
int flipRight(int x, int y, char board[][COLS], char player);
int flipLeft (int x, int y, char board[][COLS], char player);
int flipUpLeft(int x, int y, char board[][COLS], char player);
int flipUpRight(int x, int y, char board[][COLS], char player);
int flipDownLeft(int x, int y, char board[][COLS], char player);
int flipDownRight(int x, int y, char board[][COLS], char player);
void superPower1(char board[][COLS], char player);
void superPower2(char board[][COLS], char player);
bool endOfGame();

//Global Variables
int num = 1;
char board [COLS][ROWS] = {
    
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ','W','B',' ',' ',' ',
    ' ',' ',' ','B','W',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    ' ',' ',' ',' ',' ',' ',' ',' ',
    
};

int main() {
    
    displayMenu();
    
}
//Function to draw and display the board
void displayBoard(){
    
    displayTop();
    num = 1;
    for (int row = 0; row < ROWS; row++){
        
        displayNumRow();
        cout << "   |";
        
        for (int column = 0; column < COLS; column++){
            cout << board[column][row] << "   |";
        }
        cout << endl;
        displayTop();
        
    }
    
    displayNumColumn();
    
}
// Function to display a horizontal line
void displayTop(){
    
    cout << "    ";
    
    for (int i = 0; i < ROWS; i++){
        cout << "+----";
    }
    
    cout << endl;
    
}
//Function to display the alphabets column
void displayNumColumn(){
    
    cout << "   ";
    
    for( int i = 1; i < COLS; i++ ) {
        cout << "    " << i ;
    }
}
//Function to display the numbers row
void displayNumRow(){
    
    if (num < (ROWS + 1)) {
        cout << num;
        num++;
        
    }
}
// Function to display the menu
int displayMenu(){
    
    int answer = 0;
    cout << "Othello\n\n"
    << "1.New Game\n2.Load Game\n3.Help\n4.Quit\nYour Choice: ";
    cin >> answer;
    //Switch statement to command the menu
    switch (answer) {
        case 1:
            system("clear");
            clearBoard();
            displayBoard();
            break;
        case 2:
            loadGame();
            break;
        case 3:
            displayHelp();
            break;
        case 4:
            return 0;
            break;
        default:
            cout << "Please enter a valid choice." << endl;
            break;
    }
    playGame('B', 2, 2);
    return 0;
    
}
// Function to display the help window
char displayHelp(){
    
    char answer = ' ';
    
    cout << "How to play Othello\n\nThe object of the game is to have the majority of your colour discs on the board at the end of the game.\n\nInput the cell where you want to place your disc in the form of (rowNumber columnNumber) without the bracket and includng the space.\n\nThe one with the most discs wins!!!!\n\nSo, are you ready to play? (y or n)\n\nYour Choice: ";
    cin >> answer;
    
    if (answer == 'y')
        displayBoard();
    else if (answer == 'n')
        displayHelp();
    else
        cout << "Invalid input" << endl << endl;;
    displayHelp();
    
    return answer;
}
// Function to act as the game engine
void playGame(char player, int plB, int plW){
    char x = 0;
    char y = 0;
    int noOfTimesB = 0;
    int noOfTimesW = 0;
    
    // Infinite for loop to keep switching between players and asking for moves
    while(endOfGame()){
        cout << "\n\nScore: W = " << plW << " B = " << plB;
        cout << "\nPlayer: " << player;
        cout << "\nPlease make your move : ";
        cin >> x;
        cin >> y;
        cout << endl;
        //To check if the user wanted to go to the menu before making the next move
        goToMenu(x, y);
        int xi = x -'0';
        int yi = y - '0';
        // If condition to check for the validity of the input
        if (xi <= ROWS && yi <= COLS && board[xi-1][yi-1] == ' ' && cin.good()) {
            if (flipDown(xi, yi, board, player) || flipUp(xi, yi, board, player) || flipRight(xi, yi, board, player) || flipLeft(xi, yi, board, player) || flipUpLeft(xi, yi, board, player) || flipUpRight(xi, yi, board, player) || flipDownLeft(xi, yi, board, player) || flipDownRight(xi, yi, board, player)) {
                
                board[xi - 1][yi - 1] = player;
            }else {
                cout << "Invalid Input" << endl;
                if (player == 'B') {
                    plB--;
                    
                } else {
                    plW--;
                    
                }
                
            }
            
            displayBoard();
        } else {
            cin.clear();
            cin.ignore(100,'\n');
            if (x == 's' && y == '1') {
                if ((noOfTimesB == 1 && player == 'B') || (noOfTimesW == 1 && player == 'W')) {
                    cout << "You've already used up your super power";
                } else {
                    superPower1(board, player);
                    displayBoard();
                    if (player == 'B') {
                        noOfTimesB++;
                        plB--;
                    } else {
                        noOfTimesW++;
                        plW--;
                    }
                }
                
            }else if (x == 's' && y == '2') {
                if ((noOfTimesB == 1 && player == 'B') || (noOfTimesW == 1 && player == 'W')) {
                    cout << "You've already used up your super power";
                } else {
                    superPower2(board, player);
                    displayBoard();
                    if (player == 'B') {
                        noOfTimesB++;
                        plB--;
                    } else {
                        noOfTimesW++;
                        plW--;
                    }
                }
            }else if (x == 's' && y == 'g') { //If statement to check if user wants to save file before making the next move
                if (saveFile(x, y, board, player, plB, plW)) {
                    cout << "Game Saved" << endl;
                    if (player == 'B') {
                        plW--;
                        player = 'W';
                    } else {
                        plB--;
                        player = 'B';
                    }
                }
            }
            else {
                cout << "Invalid Input" << endl;
                if (player == 'B') {
                    plB--;
                } else {
                    plW--;
                }
                
            }
            

        }
        
        // If condition to always change the players and add one to their score
        if (player == 'B') {
            plB++;
            player = 'W';
            
        } else {
            plW++;
            player = 'B';
        }
    }
    
}
//Function to go to the menu in the game itself
void goToMenu(char x, char y){
    if (x == 'm' && y == 'n') {
        displayMenu();
    }

}
// Function to save game progress
int saveFile(char x, char y, char board[][COLS], char player, int plB, int plW){
    string file;
    cout << "Enter the name of your file: ";
    cin >> file;
    ofstream savedGame(file + ".txt");

        for (int i = 0; i < ROWS; i++) {
            for (int j = 0; j < COLS; j++) {
                savedGame << board[i][j];
                
            }
        }
        
        savedGame << player;
        savedGame << plB;
        savedGame << plW;
    savedGame.close();
    return 1;
}
//Function to load previous game
void loadGame(){
    char player;
    char plB;
    char plW;
    int blck;
    int wht;
    string file;
    cout << "Enter the name of your file: ";
    cin >> file;
    ifstream savedGame(file + ".txt");
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            savedGame >> noskipws;
            savedGame >> board[i][j];
        }
    }
    savedGame >> player;
    savedGame >> plB;
    savedGame >> plW;
    blck = plB - '0';
    wht = plW - '0';
    displayBoard();
    savedGame.close();
    playGame(player, blck, wht);
    

}
//Function to clear the board whenever a new game starts to avoid any complications
void clearBoard(){
    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            board[i][j] = ' ';
        }
    }
    board[3][3] = 'W';
    board[3][4] = 'B';
    board[4][3] = 'B';
    board[4][4] = 'W';
}

int flipDown(int x, int y, char board[][COLS], char player){
    int r = x ;
    int space = 0;
    if (player == 'B') {
        while (board[r][y-1]!= 'B' && board[r][y-1] != ' ' && r < ROWS) {
            space++;
            r++;
        }
        if (board[r][y-1] == 'B' && space >= 1) {
            for (int c = x; board[c][y-1]!= 'B' && board[c][y-1] != ' ' && c < ROWS; c++) {
                board[c][y-1] = 'B';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            
            return 1;
        }else if (board[r][y-1] == ' ' || r >= ROWS || space < 1)
            return 0;
    } else if (player == 'W') {
        while (board[r][y-1]!= 'W' && board[r][y-1] != ' ' && r < ROWS) {
            space++;
            r++;
        }
        if (board[r][y-1] == 'W' && space >= 1) {
            for (int c = x; board[c][y-1]!= 'W' && board[c][y-1] != ' ' && c < ROWS; c++) {
                board[c][y-1] = 'W';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[r][y-1] == ' ' || r >= ROWS || space < 1)
            return 0;
    }
    return 0;
}

int flipUp(int x, int y, char board[][COLS], char player){
    int r = x - 2;
    int space = 0;
    if (player == 'B') {
        while (board[r][y-1]!= 'B' && board[r][y-1] != ' ' && r < ROWS && r >= 0) {
            space++;
            r--;
        }
        if (board[r][y-1] == 'B' && space >= 1) {
            for (int c = x-2; board[c][y-1]!= 'B' && board[c][y-1] != ' ' && c < ROWS && c >= 0; c--) {
                board[c][y-1] = 'B';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipRight(x, y, board, player);
            flipDown(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[r][y-1] == ' ' || r >= ROWS || space < 1)
            return 0;
    } else if (player == 'W') {
        while (board[r][y-1]!= 'W' && board[r][y-1] != ' ' && r < ROWS && r >= 0) {
            space++;
            r--;
        }
        if (board[r][y-1] == 'W' && space >= 1) {
            for (int c = x-2; board[c][y-1]!= 'W' && board[c][y-1] != ' ' && c < ROWS && c >= 0; c--) {
                board[c][y-1] = 'W';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipRight(x, y, board, player);
            flipDown(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[r][y-1] == ' ' || r >= ROWS || space < 1)
            return 0;
    }
    
    return 0;
}

int flipRight(int x, int y, char board[][COLS], char player){
    int r = y;
    int space = 0;
    if (player == 'B') {
        while (board[x-1][r]!= 'B' && board[x-1][r] != ' ' && r < ROWS) {
            space++;
            r++;
        }
        if (board[x-1][r] == 'B' && space >= 1) {
            for (int c = y; board[x-1][c]!= 'B' && board[x-1][c] != ' ' && c < ROWS; c++) {
                board[x-1][c] = 'B';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipDown(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[x-1][r] == ' ' || r >= ROWS || space < 1)
            return 0;
    } else if (player == 'W') {
        while (board[x-1][r]!= 'W' && board[x-1][r] != ' ' && r < ROWS) {
            space++;
            r++;
        }
        if (board[x-1][r] == 'W' && space >= 1) {
            for (int c = y; board[x-1][c]!= 'W' && board[x-1][c] != ' ' && c < ROWS; c++) {
                board[x-1][c] = 'W';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipDown(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[x-1][r] == ' ' || r >= ROWS || space < 1)
            return 0;
    }
    return 0;
}

int flipLeft (int x, int y, char board[][COLS], char player){
    int r = y - 2;
    int space = 0;
    if (player == 'B') {
        while (board[x-1][r]!= 'B' && board[x-1][r] != ' ' && r < ROWS) {
            space++;
            r--;
        }
        if (board[x-1][r] == 'B' && space >= 1) {
            for (int c = y-2; board[x-1][c]!= 'B' && board[x-1][c] != ' ' && c < ROWS; c--) {
                board[x-1][c] = 'B';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipDown(x, y, board, player);
            flipRight(x, y, board, player);
            return 1;
        }else if (board[x-1][r] == ' ' || r >= ROWS || space < 1)
            return 0;
    } else if (player == 'W') {
        while (board[x-1][r]!= 'W' && board[x-1][r] != ' ' && r < ROWS) {
            space++;
            r--;
        }
        if (board[x-1][r] == 'W' && space >= 1) {
            for (int c = y-2; board[x-1][c]!= 'W' && board[x-1][c] != ' ' && c < ROWS; c--) {
                board[x-1][c] = 'W';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipDown(x, y, board, player);
            flipRight(x, y, board, player);
            return 1;
        }else if (board[x-1][r] == ' ' || r >= ROWS || space < 1)
            return 0;
    }
    
    return 0;
}

int flipUpLeft(int x, int y, char board[][COLS], char player){
    int r = y - 2;
    int s = x - 2;
    int space = 0;
    if (player == 'B') {
        while (board[s][r]!= 'B' && board[s][r] != ' ' && r < ROWS && s < ROWS) {
            space++;
            s--;
            r--;
        }
        if (board[s][r] == 'B' && space >= 1) {
            int c;
            int d;
            for (c = y-2, d = x-2; board[d][c]!= 'B' && board[d][c] != ' ' && c < ROWS && d < ROWS; c--, d--) {
                board[d][c] = 'B';
            }
            flipDown(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[s][r] == ' ' || r >= ROWS || s >= ROWS || space < 1)
            return 0;
    } else if (player == 'W') {
        while (board[s][r]!= 'W' && board[s][r] != ' ' && r < ROWS && s < ROWS) {
            space++;
            s--;
            r--;
        }
        if (board[s][r] == 'W' && space >= 1) {
            for (int c = y-2, d = x-2; board[d][c]!= 'W' && board[d][c] != ' ' && c < ROWS && d < ROWS; c--, d--) {
                board[d][c] = 'W';
            }
            flipDown(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[s][r] == ' ' || r >= ROWS || s >= ROWS || space < 1)
            return 0;
    }
    
    return 0;
}

int flipUpRight(int x, int y, char board[][COLS], char player){
    int r = y;
    int s = x - 2;
    int space = 0;
    if (player == 'B') {
        while (board[s][r]!= 'B' && board[s][r] != ' ' && r < ROWS && s < ROWS) {
            space++;
            s--;
            r++;
        }
        if (board[s][r] == 'B' && space >= 1) {
            int c;
            int d;
            for (c = y, d = x-2; board[d][c]!= 'B' && board[d][c] != ' ' && c < ROWS && d < ROWS; c++, d--) {
                board[d][c] = 'B';
            }
            flipUpLeft(x, y, board, player);
            flipDown(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[s][r] == ' ' || r >= ROWS || s >= ROWS || space < 1)
            return 0;
    } else if (player == 'W') {
        while (board[s][r]!= 'W' && board[s][r] != ' ' && r < ROWS && s < ROWS) {
            space++;
            s--;
            r++;
        }
        if (board[s][r] == 'W' && space >= 1) {
            for (int c = y, d = x-2; board[d][c]!= 'W' && board[d][c] != ' ' && c < ROWS && d < ROWS; c++, d--) {
                board[d][c] = 'W';
            }
            flipUpLeft(x, y, board, player);
            flipDown(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[s][r] == ' ' || r >= ROWS || s >= ROWS || space < 1)
            return 0;
    }
    
    return 0;

}

int flipDownLeft(int x, int y, char board[][COLS], char player){
    int r = y - 2;
    int s = x;
    int space = 0;
    if (player == 'B') {
        while (board[s][r]!= 'B' && board[s][r] != ' ' && r < ROWS && s < ROWS) {
            space++;
            s++;
            r--;
        }
        if (board[s][r] == 'B' && space >= 1) {
            int c;
            int d;
            for (c = y-2, d = x; board[d][c]!= 'B' && board[d][c] != ' ' && c < ROWS && d < ROWS; c--, d++) {
                board[d][c] = 'B';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipRight(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[s][r] == ' ' || r >= ROWS || s >= ROWS || space < 1)
            return 0;
    } else if (player == 'W') {
        while (board[s][r]!= 'W' && board[s][r] != ' ' && r < ROWS && s < ROWS) {
            space++;
            s++;
            r--;
        }
        if (board[s][r] == 'W' && space >= 1) {
            int c;
            int d;
            for ( c = y-2, d = x; board[d][c]!= 'W' && board[d][c] != ' ' && c < ROWS && d < ROWS; c--, d++) {
                board[d][c] = 'W';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipRight(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[s][r] == ' ' || r >= ROWS || s >= ROWS || space < 1)
            return 0;
    }
    
    return 0;
}

int flipDownRight(int x, int y, char board[][COLS], char player){
    int r = y;
    int s = x;
    int space = 0;
    if (player == 'B') {
        while (board[s][r]!= 'B' && board[s][r] != ' ' && r < ROWS && s < ROWS) {
            space++;
            s++;
            r++;
        }
        if (board[s][r] == 'B' && space >= 1) {
            int c;
            int d;
            for (c = y, d = x; board[d][c]!= 'B' && board[d][c] != ' ' && c < ROWS && d < ROWS; c++, d++) {
                board[d][c] = 'B';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDown(x, y, board, player);
            flipDownRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[s][r] == ' ' || r >= ROWS || s >= ROWS || space < 1)
            return 0;
    } else if (player == 'W') {
        while (board[s][r]!= 'W' && board[s][r] != ' ' && r < ROWS && s < ROWS) {
            space++;
            s++;
            r++;
        }
        if (board[s][r] == 'W' && space >= 1) {
            int c;
            int d;
            for ( c = y, d = x; board[d][c]!= 'W' && board[d][c] != ' ' && c < ROWS && d < ROWS; c++, d++) {
                board[d][c] = 'W';
            }
            flipUpLeft(x, y, board, player);
            flipUpRight(x, y, board, player);
            flipDownLeft(x, y, board, player);
            flipRight(x, y, board, player);
            flipUp(x, y, board, player);
            flipRight(x, y, board, player);
            flipLeft(x, y, board, player);
            return 1;
        }else if (board[s][r] == ' ' || r >= ROWS || s >= ROWS || space < 1)
            return 0;
    }
    
    return 0;




}

void superPower1(char board[][COLS], char player){
    int y;
    cout << "Please enter the row you want to cover: ";
    cin >> y;
    if (player == 'B') {
        for (int z = 0; z < COLS; z++) {
            board[y-1][z] = 'B';
        }
    }
    
    if (player == 'W') {
        for (int z = 0; z < COLS; z++) {
            board[y-1][z] = 'W';
        }
    }

}

void superPower2(char board[][COLS], char player){
    int y;
    cout << "Please enter the column you want to cover: ";
    cin >> y;
    if (player == 'B') {
        for (int z = 0; z < COLS; z++) {
            board[z][y-1] = 'B';
        }
    }
    
    if (player == 'W') {
        for (int z = 0; z < COLS; z++) {
            board[z][y-1] = 'W';
        }
    }
    
}

bool endOfGame(){
    int counter = 0;
    int counterB = 0;
    int counterW = 0;
    for(int i = 0; i < 8; i++){
        
        for(int j = 0; j < 8; j++){
            
            if (board[i][j] != ' ') {
                counter++;
            }
            if (board[i][j] == 'B') {
                counterB++;
            }
            if (board[i][j] != 'W') {
                counterW++;
            }
        }
        
    }
    if (counter == 64) {
        if (counterB > counterW) {
            cout << "End of game. Player B won" << endl;
        } else if(counterW > counterB) {
            cout << "End of game. Player W won" << endl;
        }else{
            cout << "End of game. It is a tie." << endl;
        }
        return false;
        
    } else {
        return true;
    }



}