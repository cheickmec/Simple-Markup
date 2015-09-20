#include "mainwindow.h"
#include <QHBoxLayout>
#include <iostream> //TOREMOVE

//+++++++++++++++++++++++++++++++++++++++++++++++++++
/////////////////  Constructor  ////////////////////+
//+++++++++++++++++++++++++++++++++++++++++++++++++++
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
<<<<<<< HEAD
    ////////////// WINDOW ICON ///////////////////
    this->setWindowIcon(QIcon("../resources/icon.png"));

    ////////////// WINDOW TITLE ///////////////////
    setWindowTitle("CHEICK BERTHE | Simple Markup");

    ///////////////////////////////////////////////
    openAction = new QAction("&Open", this);
    saveAction = new QAction("Save", this);
    exitAction = new QAction("Exit", this);
    //Resize main window
=======
    //Set Fixed size for main window
>>>>>>> d5f7148a7540593a15f32e6cdfc4e97e6eed2735
    this->resize(1000,1000);
    ///////////////////////////////////////////////
    //Declare Horizontal Layout and set spacing
    QHBoxLayout *hbox = new QHBoxLayout;

    ///////////////////////////////////////////////
    /////////Set Text Edit Region
    ///////////////////////////////////////////////
    left_pane = new QTextEdit(this);
<<<<<<< HEAD
    left_pane->resize((this->width()/2)-2 , this->height());
    right_pane = new QWebView(this);
    right_pane->resize((this->width()/2)-2,this->height());
=======
    left_pane->setFixedSize((this->width()/2)-2 , this->height());
    right_pane = new QWebView(this);
    right_pane->setFixedSize((this->width()/2)-2,this->height());
>>>>>>> d5f7148a7540593a15f32e6cdfc4e97e6eed2735

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
<<<<<<< HEAD
    connect(openAction, SIGNAL(triggered()),this,SLOT(open()));
    connect(saveAction, SIGNAL(triggered()),this,SLOT(save()));
    connect(exitAction, SIGNAL(triggered()),qApp,SLOT(quit()));

    ////////////////////////////////////////////////////////////////////
    ///// FileMenu /////////////////////////////////////////////////////
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
=======

>>>>>>> d5f7148a7540593a15f32e6cdfc4e97e6eed2735
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////Destructor//////////////////////////////++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MainWindow::~MainWindow()
{
}
<<<<<<< HEAD

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////// Parser //////////////////////////////////////////+
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
=======
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////// Parser /////////////////////////////////////////+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
>>>>>>> d5f7148a7540593a15f32e6cdfc4e97e6eed2735
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
<<<<<<< HEAD
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//////////////// SLOT: File Opener //////////////////////////////////+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this, "Open File","","Text Files(*.sm)");
    if(fileName != "") {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly)) {
            QMessageBox::critical(this,"Error","Could not open file");
            return;
        }
        QTextStream in(&file);
        left_pane->setText(in.readAll());
        file.close();
    }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//////////////// SLOT: File Saver ///////////////////////////////////+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::save(){

}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//////////////// SLOT: Exit Application /////////////////////////////+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::quit(){
    //TODO
  QMessageBox messageBox;
  messageBox.setWindowTitle("CHEICK BERTHE | Simple Markup");
  messageBox.setText("You are about to close this application");
  messageBox.setStandardButtons(QMessageBox::Yes);
  messageBox.setDefaultButton(QMessageBox::No);
  if(messageBox.exec() == QMessageBox::Yes)
      this->quit();
}
=======

>>>>>>> d5f7148a7540593a15f32e6cdfc4e97e6eed2735
