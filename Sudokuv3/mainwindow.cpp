#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QComboBox>
#include "sudoku.h"
#include <QLabel>
#include <QDateTime>
#include <QTimer>

sudoku puzzle;
sudoku grid;
QDateTime start = QDateTime::currentDateTime();

/**
 * @brief MainWindow::MainWindow
 * @param parent
 */

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    display();


    QTimer* timer = new QTimer(this);
    connect(timer, &QTimer::timeout, [this](){
        QTime time = QTime::currentTime();
        ui->label->setText(time.toString("hh:mm:ss"));
    });
    timer->start(1000);

    connect(ui->easy_button,SIGNAL(released()),this,SLOT(gameLevel()));
    connect(ui->hard_buttom,SIGNAL(released()),this,SLOT(gameLevel()));
    connect(ui->medium_button,SIGNAL(released()),this,SLOT(gameLevel()));
    ui->easy_button->setCheckable(true);
    ui->medium_button->setCheckable(true);
    ui->hard_buttom->setCheckable(true);

    connect(ui->bush_button_1,SIGNAL(released()),this,SLOT(keypad_number_pressed()));
    connect(ui->bush_button_2,SIGNAL(released()),this,SLOT(keypad_number_pressed()));
    connect(ui->bush_button_3,SIGNAL(released()),this,SLOT(keypad_number_pressed()));
    connect(ui->bush_button_4,SIGNAL(released()),this,SLOT(keypad_number_pressed()));
    connect(ui->bush_button_5,SIGNAL(released()),this,SLOT(keypad_number_pressed()));
    connect(ui->bush_button_6,SIGNAL(released()),this,SLOT(keypad_number_pressed()));
    connect(ui->bush_button_7,SIGNAL(released()),this,SLOT(keypad_number_pressed()));
    connect(ui->bush_button_8,SIGNAL(released()),this,SLOT(keypad_number_pressed()));
    connect(ui->bush_button_9,SIGNAL(released()),this,SLOT(keypad_number_pressed()));

    ui->bush_button_1->setCheckable(true);
    ui->bush_button_2->setCheckable(true);
    ui->bush_button_3->setCheckable(true);
    ui->bush_button_4->setCheckable(true);
    ui->bush_button_5->setCheckable(true);
    ui->bush_button_6->setCheckable(true);
    ui->bush_button_7->setCheckable(true);
    ui->bush_button_8->setCheckable(true);
    ui->bush_button_9->setCheckable(true);
    ui->erase_button->setCheckable(true);

    ui->bush_button_1->setChecked(true);
    ui->medium_button->setChecked(true);


}

/**
 * @brief MainWindow::display generera och lägg färg på 3x3 så att man ser tydligt
 */
void MainWindow::display(){

    start = QDateTime::currentDateTime();
    puzzle.generate(level);
    grid= puzzle;
    for (int i = 0; i < 3; i++) {
        for (int j = 3; j < 6; ++j) {
            QTableWidgetItem* Cell=ui->sudoku_board->item(i,j);
            Cell->setBackground(QColor(115, 253, 255, 92));

        }
    }
    for (int i = 3; i < 6; i++) {
        for (int j = 0; j < 3; ++j) {
            QTableWidgetItem* Cell=ui->sudoku_board->item(i,j);
            Cell->setBackground(QColor(115, 253, 255, 92));

        }
    }
    for (int i = 3; i < 6; i++) {
        for (int j = 6; j < 9; ++j) {
            QTableWidgetItem* Cell=ui->sudoku_board->item(i,j);
            Cell->setBackground(QColor(115, 253, 255, 92));

        }
    }
    for (int i = 6; i < 9; i++) {
        for (int j = 3; j < 6; ++j) {
            QTableWidgetItem* Cell=ui->sudoku_board->item(i,j);
            Cell->setBackground(QColor(115, 253, 255, 92));

        }
    }


    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            QTableWidgetItem* Cell=ui->sudoku_board->item(i,j);
            Cell->setTextAlignment(Qt::AlignCenter);//visa siffran i mitten
            if (puzzle.at(i, j))
            {
                const QString str = QString::number(puzzle.at(i, j));
                Cell->setText(str);

                Cell->QTableWidgetItem::setForeground(Qt::white);

            }
            else
            {
                Cell->setText("");
            }

        }

    }

}
/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}
/**
 * @brief MainWindow::on_solve_button_clicked
 */
void MainWindow::on_solve_button_clicked()
{
    grid.SolveSudoku();
    for (int i = 0; i < N; ++i)
    {
        for (int j = 0; j < N; ++j)
        {
            QTableWidgetItem* Cell = ui->sudoku_board->item(i, j);
            const QString str = QString::number(grid.at(i,j));
            Cell->setText(str);
        }
    }
}
/**
 * @brief MainWindow::keypad_number_pressed
 */
void MainWindow::keypad_number_pressed()
{
    QPushButton * button=(QPushButton*) sender();
    activated_number = button->text().toUInt();
    button->setChecked(true);
}
/**
 * @brief MainWindow::on_sudoku_board_cellClicked
 * @param row
 * @param column
 */
void MainWindow::on_sudoku_board_cellClicked(int row, int column)
{

    QTableWidgetItem* cell=ui->sudoku_board->item(row,column);
    if(cell->foreground().color()==Qt::white){
        return;
    }


    else if(activated_number){
        const QString str = QString::number(activated_number);
        cell->setText(str);
        puzzle.board[row][column]=activated_number;
    }
    else
    {
        cell->setText("");
        puzzle.board[row][column]=activated_number;
    }


    if(puzzle.isFull()){


            QDateTime end = QDateTime::currentDateTime();
            qint64 elapsed = start.msecsTo(end);
            QTime time = QTime::fromMSecsSinceStartOfDay(elapsed);
            QString tid=time.toString("hh:mm:ss");

        if(puzzle.valid_board(puzzle.board)){

            QMessageBox::information(this,"it take you: "+tid ,QString("it take you: "+tid));
        }
        else {
            QMessageBox::information(this,"you failed, try again!",QString("you failed, try again! "+tid));
        }
    }
}
void MainWindow::on_erase_button_clicked()
{
    activated_number=0;
    ui->erase_button->setChecked(true);
}


void MainWindow::on_new_game_clicked()
{
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            QTableWidgetItem* cell=ui->sudoku_board->item(i,j);
            cell->setBackground(Qt::NoBrush);
            cell->setForeground(Qt::NoBrush);
            puzzle.board[i][j]=0;
        }
    }
    display();

}

void MainWindow::gameLevel(){
    QPushButton * button=(QPushButton*) sender();
    QString str=button->text();
    button->setChecked(true);
    if(str=="Easy"){
        level=1;
        on_new_game_clicked();
    }else if(str=="Medium"){
        level=2;
        on_new_game_clicked();

    }else if(str=="Hard"){
        level=3;
        on_new_game_clicked();
    }

}




