#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QPainter>
#include<QPoint>
#include"line.h"
#include"circle.h"
#include"rectangle.h"
#include"figure.h"
#include"curve.h"
#include<vector>
#include<QColorDialog>
#include<QFileDialog>
#include<QLabel>
#include<QLineEdit>
#include<QPushButton>
#include<QListWidget>
#include<QMouseEvent>
#include<QMap>
#include<QFile>
#include<QImage>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QDoubleValidator m_doubleValidator;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void fig();
    void fig2();
    void rgb();
    void SAVE();
    void DOWNLOAD();
    void dialog();
    void BUTTON();
    void LIST();
    void EDIT();
    void WRITE();
    void WRITE2();
    void TUT();
private:
    Curve* curve;
    QFile * file;
    QImage* image;
    bool imageF;
    bool tutF ;
    bool saveF;
    QString str_file;
    QListWidgetItem* item = NULL;
    double currentW;
    double currentH;
    int thickness;
    int hight;
    int wight;
    int radius;
    int radius2;
    int moveToW;
    int moweToH;
    QPushButton* OK;
    QPushButton* OK2;
    QLineEdit* linePEN;
    QDialog* TEMP;
    QLineEdit* lineW;
    QLineEdit* lineH;
    QLineEdit* lineR;
    int count;
    bool listF;
    bool buttonF;
    bool drawline;
    bool draw2;
    QPoint first;
    QListWidget* listwid;
    QLabel* label;
    Line* line;
    Circle* circle;
    Rectangle* rectangle;
    Ui::MainWindow *ui;
    QDialog* temp;
    QPushButton* tut;
    QMap<QString,Figure*>FIGMAP;
    QRgb rgbcolor;
    QPushButton* button;
    QPushButton* button2;
    QColorDialog* RGB = new QColorDialog;
    QFileDialog* FILE = new QFileDialog;
    QMenu *FigureMenu;
    QMenu *FileMenu;
    QMenu* EditMenu;
    QAction *ColorMenu;
    QAction *characteristics;
    QAction* Act_1;
    QAction* Act_2;
    QAction* Act_3;
    QAction* Act_4;
    QAction* Act_5;


    QAction* erase;
    QAction* move;
    QAction* turn;
    QAction* character;

    QAction* save;
    QAction* download;
    QMenuBar* menuBar;
    bool nal;
    bool draw;
    bool F;

    virtual void mousePressEvent (QMouseEvent* pe);
     virtual void mouseMoveEvent(QMouseEvent* pe);
    virtual void mouseReleaseEvent(QMouseEvent* pe);
protected:

    void paintEvent(QPaintEvent *);
};
#endif // MAINWINDOW_H
