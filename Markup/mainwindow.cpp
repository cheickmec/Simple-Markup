#include "mainwindow.h"
#include <QHBoxLayout>
#include <iostream> //TOREMOVE

//+++++++++++++++++++++++++++++++++++++++++++++++++++
/////////////////  Constructor  ////////////////////+
//+++++++++++++++++++++++++++++++++++++++++++++++++++
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //Set Fixed size for main window
    this->resize(1000,1000);
    ///////////////////////////////////////////////
    //Declare Horizontal Layout and set spacing
    QHBoxLayout *hbox = new QHBoxLayout;

    ///////////////////////////////////////////////
    /////////Set Text Edit Region
    ///////////////////////////////////////////////
    left_pane = new QTextEdit(this);
    left_pane->setFixedSize((this->width()/2)-2 , this->height());
    right_pane = new QWebView(this);
    right_pane->setFixedSize((this->width()/2)-2,this->height());

    ////////////////////////////////////////////////
    //////// Add both regions to horizontal Layout
    ///////////////////////////////////////////////
    hbox->addWidget(left_pane);
    hbox->setSpacing(4);
    hbox->addWidget(right_pane);

    ////////////////////////////////////////////////
    /////////// Set layout in QWidget
    ///////////////////////////////////////////////
    QWidget *window = new QWidget();
    window->setLayout(hbox);

    ////////////////////////////////////////////////////////
    // Set QWidget as the central layout of the main window
    ////////////////////////////////////////////////////////
    setCentralWidget(window);

    ////////////////////////////////////////////////////////////////////
    ///// CONNECT SIGNAL TO EVENT //////////////////////////////////////
    connect(left_pane, SIGNAL(textChanged()), this , SLOT(updateView()));

}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////Destructor//////////////////////////////++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MainWindow::~MainWindow()
{
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////// Parser /////////////////////////////////////////+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
QString Parser (QString str){
    //TODO
    QString str2 = "<html> <body>" + str + "<body> </html>";
    return str2;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////// SLOT: update WebView /////////////////////////////+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::updateView(){
    QString text = left_pane->toPlainText();
    text = Parser(text);
    right_pane->setHtml(text);
}

