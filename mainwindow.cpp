#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow), m_doubleValidator(-1000, 1000, 2, this)
{
    ui->setupUi(this);
    m_doubleValidator.setNotation(QDoubleValidator::StandardNotation);
    listwid = new QListWidget(this);
    imageF = false;
    draw = false;
    draw2 = false;
    nal = false;
    listF = false;
    buttonF = false;
    drawline = false;
    tutF = false;
    saveF = false;
    count = 0;
    thickness = 3;
    hight = 100;
    wight = 200;
    radius = 200;
    radius2 = 300;
    currentW = this->width();
    currentH = this->height();

    label = new QLabel;
    menuBar = ui->menubar;
    button = new QPushButton("Список",this);
    button2 = new QPushButton("Редактировать",this);

    Act_1 = new QAction("Прямая", menuBar);
    Act_2 = new QAction("Кривая", menuBar);
    Act_3 = new QAction("Прямоугольник", menuBar);
    Act_4 = new QAction("Круг", menuBar);
    Act_5 = new QAction("Элипс",menuBar);
    save = new QAction("Сохранить", menuBar);
    download = new QAction("Загрузить", menuBar);
    erase = new QAction("Удалить", menuBar);
    move = new QAction("Переместить", menuBar);
    turn = new QAction("Повернуть", menuBar);
    character = new QAction("Изменить характеристики", menuBar);

    Act_1->setCheckable(true);
    Act_2->setCheckable(true);
    Act_3->setCheckable(true);
    Act_4->setCheckable(true);
    Act_5->setCheckable(true);
    erase->setCheckable(true);
    move->setCheckable(true);
    turn->setCheckable(true);
    character->setCheckable(true);
    character->setChecked(true);

    FileMenu = menuBar->addMenu("Файл");
    FigureMenu = menuBar->addMenu("Фигуры");
    ColorMenu = menuBar->addAction("Цвет");
    characteristics = menuBar->addAction("Характеристики");
    EditMenu = menuBar->addMenu("Редактирование");
    FigureMenu->addAction(Act_1);
    FigureMenu->addAction(Act_2);
    FigureMenu->addAction(Act_3);
    FigureMenu->addAction(Act_4);
    FigureMenu->addAction(Act_5);
    FileMenu->addAction(save);
    FileMenu->addAction(download);
    EditMenu->addAction(erase);
    EditMenu->addAction(move);
    EditMenu->addAction(turn);
    EditMenu->addAction(character);

    statusBar()->addWidget(label);
    connect(Act_1, SIGNAL(triggered()), this, SLOT(fig()));
    connect(Act_2, SIGNAL(triggered()), this, SLOT(fig()));
    connect(Act_3, SIGNAL(triggered()), this, SLOT(fig()));
    connect(Act_4, SIGNAL(triggered()), this, SLOT(fig()));
    connect(Act_5, SIGNAL(triggered()), this, SLOT(fig()));
    connect(ColorMenu, SIGNAL(triggered()), this, SLOT(rgb()));
    connect(save, SIGNAL(triggered()), this, SLOT(SAVE()));
    connect(download, SIGNAL(triggered()), this, SLOT(DOWNLOAD()));
    connect(characteristics, SIGNAL(triggered()), this, SLOT(dialog()));
    connect(button, SIGNAL(clicked()), this, SLOT(BUTTON()));
    connect(button2, SIGNAL(clicked()), this, SLOT(EDIT()));
    connect(erase, SIGNAL(triggered()), this, SLOT(fig2()));
    connect(move, SIGNAL(triggered()), this, SLOT(fig2()));
    connect(turn, SIGNAL(triggered()), this, SLOT(fig2()));
    connect(character, SIGNAL(triggered()), this, SLOT(fig2()));

    connect(listwid, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(LIST()));
    setMouseTracking(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::paintEvent(QPaintEvent *)
{


    buttonF = false;
    foreach (QListWidgetItem *wi,listwid->selectedItems())
        buttonF = true;
    if(currentW!=this->width()||currentH!=this->height())
    {
        for(auto a:FIGMAP)
            a->resize(this->width()/currentW,this->height()/currentH);
    }
    currentW = this->width();
    currentH = this->height();
    button->setGeometry(this->width()-200,24,200,30);
    if(buttonF)
    {
       button2->setGeometry(this->width()-200,this->height()-30,200,30);
    }
    else
    {
        button2->setGeometry(this->width(),this->height(),1,1);
    }
    if(listF)
    {
        if(buttonF)
            listwid->setGeometry(this->width()-200,54,200,this->height()-84);
        else
            listwid->setGeometry(this->width()-200,54,200,this->height()-54);
    }
    else
    {
        listwid->setGeometry(this->width(),54,1,this->height()-54);
    }
    if(saveF)
    {
        if(!imageF)
        {
            image = new QImage(width(),height(),QImage::Format_RGB32);
            image->fill(Qt::white);
            imageF = true;
        }
         QPainter painter(image);
        for(auto a:FIGMAP)
        {
            a->resize(image->width()/currentW,image->height()/currentH);
            a->draw(&painter);
            a->resize(currentW/image->width(),currentH/image->height());
        }
        QPainter painterr(this);
        painterr.drawImage(QRect(0,0,this->width(),this->height()),*image);
        saveF = false;
        FIGMAP.clear();
        listwid->clear();
    }
    else if(imageF)
    {
        QPainter painter(this);
        painter.drawImage(QRect(0,0,this->width(),this->height()),*image);
       // QPainter painterr(image);
        for(auto a:FIGMAP)
            a->draw(&painter);


    }
    else
    {
         QPainter painter(this);
         for(auto a:FIGMAP)
             a->draw(&painter);
    }
}
void MainWindow::fig()
{

    nal = true;
    Act_1->setChecked(0);
    Act_2->setChecked(0);
    Act_3->setChecked(0);
    Act_4->setChecked(0);
    Act_5->setChecked(0);
    QAction* temp = (QAction*)sender();
    temp->setChecked(true);
    label->setText(temp->text());
}
void MainWindow::fig2()
{
    erase->setChecked(0);
    move->setChecked(0);
    turn->setChecked(0);
    character->setChecked(0);
    QAction* temp = (QAction*)sender();
    temp->setChecked(true);

}

void MainWindow::rgb()
{
   rgbcolor=RGB->getRgba();
}

void MainWindow::SAVE()
{

    str_file = FILE->getSaveFileName();
    saveF = true;
    repaint();
    this->image->save(str_file);

}

void MainWindow::DOWNLOAD()
{

    str_file = FILE->getOpenFileName();

    image = new QImage(str_file);
    imageF = true;
    repaint();
}

void MainWindow::dialog()
{
    TEMP = new QDialog;
    TEMP->setModal(true);
    OK = new QPushButton("OK",TEMP);
    OK->setGeometry(120,100,100,30);
    connect(OK, SIGNAL(clicked()), this, SLOT(WRITE()));
    if(nal)
    {
        QLabel* label = new QLabel("Толщина пера(пикс) :",TEMP);
        label->setGeometry(70,20,200,30);
        linePEN = new QLineEdit(TEMP);
        linePEN->setValidator(&m_doubleValidator);
        linePEN->setGeometry(190,20,50,25);
        linePEN->setText(QString::number(thickness));
        if(Act_3->isChecked())
        {
        QLabel* label2 = new QLabel("Ширина(пикс) :",TEMP);
        QLabel* label3 = new QLabel("Высота(пикс) :",TEMP);
        lineW = new QLineEdit(TEMP);
        lineH = new QLineEdit(TEMP);
        lineW->setValidator(&m_doubleValidator);
        lineH->setValidator(&m_doubleValidator);
        label2->setGeometry(20,60,100,30);
        lineW->setGeometry(100,60,50,25);
        label3->setGeometry(180,60,100,30);
        lineH->setGeometry(260,60,50,25);
        lineW->setText(QString::number(wight));
        lineH->setText(QString::number(hight));
        }
        else if(Act_4->isChecked())
        {
         QLabel* label2 = new QLabel("Радиус(пикс) :",TEMP);
         lineR = new QLineEdit(TEMP);
         lineR->setValidator(&m_doubleValidator);
         label2->setGeometry(105,60,100,30);
         lineR->setGeometry(190,60,50,25);
         lineR->setText(QString::number(radius));
        }
        else if(Act_1->isChecked()||Act_2->isChecked())
        {

        }
        else if(Act_5->isChecked())
        {
            QLabel* label2 = new QLabel("Ширина(пикс) :",TEMP);
            QLabel* label3 = new QLabel("Высота(пикс) :",TEMP);
            lineW = new QLineEdit(TEMP);
            lineH = new QLineEdit(TEMP);
            lineW->setValidator(&m_doubleValidator);
            lineH->setValidator(&m_doubleValidator);
            label2->setGeometry(20,60,100,30);
            lineW->setGeometry(100,60,50,25);
            label3->setGeometry(180,60,100,30);
            lineH->setGeometry(260,60,50,25);
            lineW->setText(QString::number(radius));
            lineH->setText(QString::number(radius2));
        }
    }
    else
    {
        QLabel* L = new QLabel("не указана фигура(((",TEMP);
        L->setGeometry(120,40,100,30);
    }
    TEMP->show();
}

void MainWindow::BUTTON()
{
    if(listF)
    {
        listF = false;
    }
    else
    {
        listF = true;
    }
}

void MainWindow::LIST()
{
    repaint();
}

void MainWindow::EDIT()
{

    if(erase->isChecked())
    {
        item = listwid->takeItem(listwid->currentRow());
        QMap<QString,Figure*>::iterator it = FIGMAP.begin();
        while(it!=FIGMAP.end())
        {
            if(it.key()==item->text())
            {
                FIGMAP.erase(it);
                break;
            }
            it++;
        }
        delete item;
        repaint();
        if(listwid->count()==0)buttonF = false;

    }
    else
    {
        temp = new QDialog;
        temp->setModal(true);
        OK2 = new QPushButton("OK",temp);
        OK2->setGeometry(100,100,140,30);
        connect(OK2, SIGNAL(clicked()), this, SLOT(WRITE2()));

    if(turn->isChecked())
    {
        QLabel* lab = new QLabel("градус поворота : " , temp);
        lineR = new QLineEdit(temp);
        lineR->setValidator(&m_doubleValidator);

        lab->setGeometry(100,30,100,30);
        lineR->setGeometry(200,30,50,30);

    }
    else if(move->isChecked())
    {
        QLabel* lab = new QLabel("координаты базовой точки :                    X " , temp);
        lineW = new QLineEdit(temp);
        lineH = new QLineEdit(temp);
        lineW->setValidator(&m_doubleValidator);
        lineH->setValidator(&m_doubleValidator);
        lab->setGeometry(30,30,250,30);
        lineW->setGeometry(180,30,50,30);
        lineH->setGeometry(250,30,50,30);
        tut = new QPushButton("указать на виджете",temp);
        tut->setGeometry(100,80,140,30);
        OK2->setGeometry(100,120,140,30);
        connect(tut, SIGNAL(clicked()), this, SLOT(TUT()));
    }
    else
    {
       QLabel* label = new QLabel("Толщина пера(пикс) :",temp);
        label->setGeometry(70,20,200,30);
        linePEN = new QLineEdit(temp);
        linePEN->setValidator(&m_doubleValidator);
        linePEN->setGeometry(195,20,50,25);
        linePEN->setText(QString::number(thickness));
        item = listwid->takeItem(listwid->currentRow());
        if(item->text().endsWith("Прямоугольник"))
        {
        QLabel* label2 = new QLabel("Ширина(пикс) :",temp);
        QLabel* label3 = new QLabel("Высота(пикс) :",temp);
        lineW = new QLineEdit(temp);
        lineH = new QLineEdit(temp);
        lineW->setValidator(&m_doubleValidator);
        lineH->setValidator(&m_doubleValidator);
        label2->setGeometry(20,60,100,30);
        lineW->setGeometry(105,60,50,25);
        label3->setGeometry(180,60,100,30);
        lineH->setGeometry(260,60,50,25);
        lineW->setText(QString::number(wight));
        lineH->setText(QString::number(hight));
        }
        else if(item->text().endsWith("Линия")||item->text().endsWith("Кривая"))
        {
            OK2->setGeometry(100,70,140,30);
        }
        else if(item->text().endsWith("Круг"))
        {
            QLabel* label2 = new QLabel("Радиус(пикс) :",temp);
            lineR = new QLineEdit(temp);
            lineR->setValidator(&m_doubleValidator);
            label2->setGeometry(105,60,100,30);
            lineR->setGeometry(190,60,50,25);
            lineR->setText(QString::number(radius));
        }
        else if(item->text().endsWith("Элипс"))
        {
            QLabel* label2 = new QLabel("Ширина(пикс) :",temp);
            QLabel* label3 = new QLabel("Высота(пикс) :",temp);
            lineW = new QLineEdit(temp);
            lineH = new QLineEdit(temp);
            lineW->setValidator(&m_doubleValidator);
            lineH->setValidator(&m_doubleValidator);
            label2->setGeometry(20,60,100,30);
            lineW->setGeometry(100,60,50,25);
            label3->setGeometry(180,60,100,30);
            lineH->setGeometry(260,60,50,25);
            lineW->setText(QString::number(radius));
            lineH->setText(QString::number(radius2));
        }

        listwid->addItem(item);
    }
    temp->show();
    }
}

void MainWindow::WRITE()
{
    if(Act_1->isChecked()||Act_2->isChecked()||Act_3->isChecked()||Act_4->isChecked()||Act_5->isChecked())
    thickness = linePEN->text().toInt();
    if(Act_3->isChecked())
    {
    wight = lineW->text().toInt();
    hight = lineH->text().toInt();
    }
    if(Act_4->isChecked())
    {
    radius = lineR->text().toInt();
    }
    if(Act_5->isChecked())
    {
    radius = lineW->text().toInt()/2;
    radius2 = lineH->text().toInt()/2;
    }
    delete TEMP;
}

void MainWindow::WRITE2()
{


    if(turn->isChecked())
    {
        item = listwid->takeItem(listwid->currentRow());
        FIGMAP[item->text()]->degree += lineR->text().toInt();
        listwid->addItem(item->text());
    }
    if(move->isChecked())
    {
        item = listwid->takeItem(listwid->currentRow());
        FIGMAP[item->text()]->move(lineW->text().toInt(),lineH->text().toInt());
        listwid->addItem(item->text());
    }
    if(character->isChecked())
    {
         FIGMAP[item->text()]->setPenW(linePEN->text().toInt());

        if(item->text().endsWith("Прямоугольник"))
        {
           FIGMAP[item->text()]->setSize(lineW->text().toInt(),lineH->text().toInt());
        }
        if(item->text().endsWith("Элипс"))
        {
            FIGMAP[item->text()]->setSize(lineW->text().toInt()/2,lineH->text().toInt()/2);
        }
        if(item->text().endsWith("Круг"))
        {
            FIGMAP[item->text()]->setSize(lineR->text().toInt(),lineR->text().toInt());
        }
        if(item->text().endsWith("Линия"))
        {

        }
    }
    delete temp;
}

void MainWindow::TUT()
{
    tutF = true;
    delete temp;
}

void MainWindow::mousePressEvent(QMouseEvent * event)
{
    if(tutF)
    {
       tutF = false;
       item = listwid->takeItem(listwid->currentRow());
       FIGMAP[item->text()]->move(event->pos().x(),event->pos().y());
       listwid->addItem(item->text());
       repaint();

    }
    else if(nal)
    {
        QPoint temp = event->pos();
        QPen pen(rgbcolor);
        pen.setWidth(thickness);
        if(Act_1->isChecked())
        {
           if(!drawline)
            {
                drawline = true;
                first = temp;
                line = new Line(first.x(),first.y(),temp.x(),temp.y(),pen);

                FIGMAP[QString::number(count)+" Линия"]=(line);
                listwid->addItem(QString::number(count++)+" Линия");
            }
        }
        else if(Act_2->isChecked())
        {


                curve = new Curve(temp.x(),temp.y(),pen);
                FIGMAP[QString::number(count)+" Кривая"] = curve;
                draw2 = true;
                listwid->addItem(QString::number(count++)+" Кривая");
        }
        else if(Act_3->isChecked())
        {

            FIGMAP[QString::number(count)+" Прямоугольник"] = new Rectangle(temp.x(),temp.y(),wight,hight,pen);
             listwid->addItem(QString::number(count++)+" Прямоугольник");
        }
        else if(Act_4->isChecked())
        {

             FIGMAP[QString::number(count)+" Круг"] = new Circle(temp.x(),temp.y(),radius,radius,pen);
             listwid->addItem(QString::number(count++)+" Круг");
        }
        else if(Act_5->isChecked())
        {

             FIGMAP[QString::number(count)+" Элипс"] = new Circle(temp.x(),temp.y(),radius,radius2,pen);
             listwid->addItem(QString::number(count++)+" Элипс");
        }
        repaint();
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(draw2)
    {
        QPoint temp = event->pos();
        curve->addline(temp.x(),temp.y());
        repaint();
    }
    if(drawline)
    {
        line->X2 = event->pos().x();
        line->Y2 = event->pos().y();
        repaint();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *pe)
{
    draw2 = false;
    if(drawline)drawline = false;
}




