#include "sudoku.h"
#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <set>
/**
 * @brief sudoku::sudoku fills the board with zeros as empty
 */
sudoku::sudoku()
{
    std::fill(&board[0][0], &board[0][0] + N*N, 0);
}

/**
 * @brief sudoku::IsSafe checks if the nummer is in row, column or in the box 3x3
 * @param row
 * @param col
 * @param num
 * @return bool
 */
bool sudoku::IsSafe(int row, int col, int num) {
    return !CheckRow(row, num) && !CheckCol(col, num) && !CheckBox(row - row % 3, col - col % 3, num);
}

bool sudoku::CheckRow(int row, int num) {
    for (int col = 0; col < N; ++col) {
        if (board[row][col] == num) {
            return true;
        }
    }
    return false;
}

bool sudoku::CheckCol(int col, int num) {
    for (int row = 0; row < N; ++row) {
        if (board[row][col] == num) {
            return true;
        }
    }
    return false;
}

bool sudoku::CheckBox(int boxStartRow, int boxStartCol, int num) {
    for (int row = 0; row < 3; ++row) {
        for (int col = 0; col < 3; ++col) {
            if (board[row + boxStartRow][col + boxStartCol] == num) {
                return true;
            }
        }
    }
    return false;
}
/**
 * @brief sudoku::FindUnassignedLocation find the location of zeros
 * @param row
 * @param col
 * @return bool
 */
bool sudoku::FindUnassignedLocation(int &row, int &col) {
    for (row = 0; row < N; ++row) {
        for (col = 0; col < N; ++col) {
            if (board[row][col] == UNASSIGNED) {
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief sudoku::at
 * @param x
 * @param y
 * @return
 */
int sudoku::at(int x,int y)
{
    return this->board[x][y];
}
/**
 * @brief sudoku::SolveSudoku solves the puzzle
 * @return bool
 */
bool sudoku::SolveSudoku(){
    int row, col;
    if (!FindUnassignedLocation(row, col)) {
        return true;
    }
    for (int num = 1; num <= 9; num++) {
        if (IsSafe(row, col, num)) {
            board[row][col] = num;
            if (SolveSudoku()) {
                return true;
            }
            board[row][col] = UNASSIGNED; //else do backtracking by putting back 0
        }
    }
    return false;
}
/**
 * @brief sudoku::generate creating sudoku puzzle
 * @param mode is the level of puzzle
 */
void sudoku::generate(int mode){
    std::random_device rd;
    std::default_random_engine rng(rd());
    std::vector<int>v1{1,2,3,4,5,6,7,8,9};
    std::shuffle(v1.begin(),v1.end(),rng);
    int col=0;
    for (auto e: v1) {
        board[0][col] =e;
        col++;
    }
    SolveSudoku();

    if(mode==1)
    {//easy 46
        for (int i = 0; i < N; i = i + 3)
        {
            for (int j = 0; j < N; j=j+3)
            {
                for (int k= i; k < i+3; k+=3)
                {
                    for (int l = j; l < j+3; l+=2)
                    {
                        int r=arc4random()%3+i;
                        int c=arc4random()%3+j;
                        board[r][c]=0;
                    }
                }

            }

        }
    }
    else if(mode == 2){//medium 52
        for (int i = 0; i < N; i = i + 3) {
            for (int j = 0; j < N; j=j+3) {
                for (int k= i; k < i+3; k+=2) {
                    for (int l = j; l < j+3; l+=2) {
                        int r=arc4random()%3+i;
                        int c=arc4random()%3+j;
                        board[r][c]=0;
                    }
                }
            }
        }
    }
    else if(mode == 3){//hard 53
        for (int i = 0; i < N; i = i + 3) {
            for (int j = 0; j < N; j=j+3) {
                for (int k= i; k < i+3; k++) {
                    for (int l = j; l < j+3; l++) {
                        int r=arc4random()%3+i;
                        int c=arc4random()%3+j;
                        board[r][c]=0;
                    }
                }
            }
        }
    }
    else {
        for(int row = 0; row < 9; row = row + 3)
        {
            for(int col = 0; col < 9; col = col + 3)
            {
                for(int var = 0; var<2; var++){
                    board[arc4random()%3+row][arc4random()%3+col]=0;
                }

            }
        }
    }




}
/**
 * @brief sudoku::isFull checks if the board is full
 * @return true or false
 */
bool sudoku::isFull()
{
    for(int i = 0 ; i < N ; i++){
        for(int j = 0 ; j <N ; j++){
            if(board[i][j] ==0){
                return false;
            }
        }
    }
    return true;
}

/**
 * @brief sudoku::valid_row
 * @param row
 * @param grid
 * @return
 */
int sudoku:: valid_row(int row, int grid[][9]){
    std::set<int> s;
    for(int i = 0; i < 9; i++){
        if(grid[row][i] < 0 || grid[row][i] > 9){
            return -1;
        }
        else
        { //Checking for repeated values.
            if(grid[row][i] != 0){
                if(s.insert(grid[row][i]).second == false){
                    return 0;
                }
            }
        }
    }
    return 1;
}
/**
 * @brief sudoku::valid_col checking  values in column if they are valid
 * @param col column
 * @param grid sudoku board
 * @return if its valid or not
 */

int sudoku:: valid_col(int col, int grid[][9]){
    std::set<int> s;
    for(int i = 0; i < 9; i++){
        // Checking for values outside 0 and 9;
        // 0 is considered valid because it
        // denotes an empty cell.
        // Removing zeros and the checking for values and
        // outside 1 and 9 is another way of doing
        // the same thing.
        if(grid[i][col] < 0 || grid[i][col] > 9){
            return -1;
        }
        else
        { // Checking for repeated values.
            if(grid[i][col] != 0){
                if(s.insert(grid[i][col]).second == false){
                    return 0;
                }
            }
        }
    }
    return 1;
}
/**
 * @brief sudoku::valid_subsquares
 * @param grid
 * @return
 */
bool sudoku::valid_subsquares(int grid [][9]){
    for(int row = 0; row < 9; row = row + 3){
        for(int col = 0; col < 9; col = col + 3){
            std::set<int> s;
            for(int r = row; r < row + 3; r++){
                for(int c = col; c < col + 3; c++){
                    if(grid[r][c] < 0 || grid[r][c] > 9){
                        return false;
                    }
                    else{
                        // Checking for repeated values
                        if(grid[r][c] != 0){
                            if(s.insert(grid[r][c]).second == false){
                                return false;
                            }
                        }
                    }
                }
            }
        }
    }
    return true;
}


/**
 * @brief sudoku::valid_board checking the values in the board(if the board is valid or not)
 * @param grid
 * @return
 */
bool sudoku::valid_board(int grid [][N]){
    for(int i = 0; i < 9; i++){
        int res1 = valid_row(i, grid);
        int res2 = valid_col(i, grid);
        // If a row or a column is invalid, then the board is invalid.
        if(res1 < 1 || res2 < 1){
            return false;
        }
    }
    // if any one the subsquares is invalid, then the board is invalid.
    int res3 = valid_subsquares(grid);
    if(res3){
        return false;
    }
    else{
        return true;
    }
}


