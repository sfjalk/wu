#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPaintEvent>
#include <QPainter>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Initui();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Initui()
{
    this->resize((CHESS_C+1)*MAX_X,(CHESS_R)*MAX_Y);
    this->setWindowTitle("五子棋");
    this->setMaximumSize((CHESS_C+1)*MAX_X,(CHESS_R)*MAX_Y);
    this->setMinimumSize((CHESS_C+1)*MAX_X,(CHESS_R)*MAX_Y);
    b_black=false;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    Drawchessboard();
    Drawhandboard();
    DrawChessItem();
    update();
}
void MainWindow::Drawchessboard()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::black),2));
    painter.setBrush(Qt::yellow);
    for(int i=0;i<CHESS_C;i++)
    {
        for(int j=0;j<CHESS_R;j++)
        {
            painter.drawRect((i+0.5)*MAX_X,(j+0.5)*MAX_Y,MAX_X,MAX_Y);
        }
    }
}

void MainWindow::Drawhandboard()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    if(b_black)
    {
        painter.setBrush(Qt::black);
    }
    else
    {
        painter.setBrush(Qt::white);
    }
    painter.drawEllipse(mapFromGlobal(QCursor::pos()),MAX_X/2,MAX_Y/2);//QCursor::pos()是追踪鼠标的坐标。
    //mapfromglobal是将一个全局坐标系下的点转换为相对于对象本身坐标系下的点
}

void MainWindow::DrawChessItem()
{
    QPainter painter(this);
    painter.setPen(QPen(QColor(Qt::transparent)));
    for (int i = 0;i< p_ChessItem.size();i++)
    {
        ChessItem item=p_ChessItem[i];//当前的棋子的样式和位置赋值给棋子的这个类
        if(item._black)
        {
            painter.setBrush(Qt::black);
        }
        else
        {
            painter.setBrush(Qt::white);
        }
        DrawChessAtPoint(painter,item._pt);
    }
}

void MainWindow::DrawChessAtPoint(QPainter &painter,QPoint &point)
{
 //获取棋子的摆放位置
    QPoint ptcenter((point.x()+0.5)*MAX_X,(point.y()+0.5)*MAX_Y);
    painter.drawEllipse(ptcenter,MAX_X/2,MAX_Y/2);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    //获取鼠标点击的位置
    QPoint pt;
    pt.setX(event->pos().x()/MAX_X);
    pt.setY(event->pos().y()/MAX_Y);

    //判断棋子是否存在
    for(int i=0;i<p_ChessItem.size();i++)
    {
        ChessItem item=p_ChessItem[i];
        if(item._pt==pt)
        {
            return;      //如果存在则不进行操作
        }
    }
    //如果不存在则进行绘制棋子并进行判断是否连成
    ChessItem item(pt,b_black);
    p_ChessItem.append(item);
    int nleft         =CountNearitem(item,QPoint(-1, 0));
    int nright        =CountNearitem(item,QPoint( 1, 0));
    int nUp           =CountNearitem(item,QPoint( 0, 1));
    int nDown         =CountNearitem(item,QPoint( 0,-1));
    int nleftUp       =CountNearitem(item,QPoint(-1, 1));
    int nleftDown     =CountNearitem(item,QPoint(-1,-1));
    int nrightUp      =CountNearitem(item,QPoint( 1, 1));
    int nrightDown    =CountNearitem(item,QPoint( 1,-1));
    if((nleft+nright>=4)||(nUp+nDown>=4)||(nleftUp+nrightDown>=4)||(nleftDown+nrightUp>=4))
    {
        QString str=b_black?"Black victor":"White victor";
        QMessageBox::information(NULL,"GAME OVER",str,QMessageBox::Yes);
        p_ChessItem.clear();
        return;
    }
    b_black=!b_black;
}

int MainWindow::CountNearitem(ChessItem item,QPoint pt)
{
    int nCount=0;
    item._pt+=pt;
    while (p_ChessItem.contains(item)) {
        nCount++;
        item._pt+=pt;
    }
    return nCount;
}






