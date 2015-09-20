#include "mainwindow.h"
#include <QHBoxLayout>
#include <iostream> //TOREMOVE

//+++++++++++++++++++++++++++++++++++++++++++++++++++
/////////////////  Constructor  ////////////////////+
//+++++++++++++++++++++++++++++++++++++++++++++++++++
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    ////////////// WINDOW ICON ///////////////////
    this->setWindowIcon(QIcon("../resources/icon.png"));

    ////////////// WINDOW TITLE ///////////////////
    setWindowTitle("CHEICK BERTHE | Simple Markup");

    ///////////////////////////////////////////////
    openAction = new QAction("&Open", this);
    saveAction = new QAction("Save", this);
    exitAction = new QAction("Exit", this);
    //Resize main window
    this->resize(1000,1000);
    ///////////////////////////////////////////////
    //Declare Horizontal Layout and set spacing
    QHBoxLayout *hbox = new QHBoxLayout;

    ///////////////////////////////////////////////
    /////////Set Text Edit Region
    ///////////////////////////////////////////////
    left_pane = new QTextEdit(this);
    left_pane->resize((this->width()/2)-2 , this->height());
    right_pane = new QWebView(this);
    right_pane->resize((this->width()/2)-2,this->height());

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
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////Destructor//////////////////////////////++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MainWindow::~MainWindow()
{
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////// Parser //////////////////////////////////////////+
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
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
