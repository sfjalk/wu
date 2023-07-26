#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMouseEvent>
#include <QMainWindow>
#include <QVector>
#include "chessitem.h"
#include <QMessageBox>
#define CHESS_R 15
#define CHESS_C 15
#define MAX_X   50
#define MAX_Y   50
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void paintEvent(QPaintEvent *event);
    void Initui();
    void Drawchessboard();//画棋盘
    void Drawhandboard();//画鼠标上的棋子
    void DrawChessItem();//画棋盘上的棋子
    void DrawChessAtPoint(QPainter &painter,QPoint &point);
    void mousePressEvent(QMouseEvent *event);//鼠标点击事件
    bool b_black;//定义棋子的颜色
    QVector<ChessItem> p_ChessItem;//定义棋子个数
    int CountNearitem(ChessItem item,QPoint pt);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
