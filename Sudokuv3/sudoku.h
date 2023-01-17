#ifndef SUDOKU_H
#define N 9
#define UNASSIGNED 0
#define SUDOKU_H

class sudoku
{
public:
    sudoku();
    void generate(int mode);
    bool SolveSudoku();
    int at(int,int);
    int board[N][N];
    bool isFull();
    bool valid_board(int grid [][N]);
    ~sudoku()=default;
private:
    int valid_row(int row, int grid[][N]);
    int valid_col(int col, int grid[][N]);
    bool valid_subsquares(int grid [][N]);
    bool IsSafe(int row, int col, int num);
    bool CheckRow(int row, int num);
    bool CheckCol(int col, int num);
    bool CheckBox(int boxStartRow, int boxStartCol, int num);
    bool FindUnassignedLocation(int &row, int &col);

};

#endif // SUDOKU_H
