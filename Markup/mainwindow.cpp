#include "mainwindow.h"
#include <QHBoxLayout>
#include <iostream>
#include <QTextStream>
#include <QStringList>
#include <QDebug>

QTextStream out(stdout);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
/////////////////  Constructor  //////////////////////////////////+
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{

    ////////////// WINDOW ICON ///////////////////
    this->setWindowIcon(QIcon("../resources/icon.png"));

    ////////////// WINDOW TITLE ////////////////////////////////////////
    setWindowTitle("CHEICK BERTHE | Simple Markup");

    ///////////////////////////////////////////////////////////////////
    openAction = new QAction("&Open", this);
    saveAction = new QAction("Save", this);
    exitAction = new QAction("Exit", this);
    //Resize main window

    //Set Fixed size for main window

    //this->resize(1000,1000);
    ///////////////////////////////////////////////
    //Declare Horizontal Layout and set spacing
    QHBoxLayout *hbox = new QHBoxLayout;

    ///////////////////////////////////////////////
    /////////Set Text Edit Region
    ///////////////////////////////////////////////
    left_pane = new QTextEdit(this);
    right_pane = new QWebView(this);

    left_pane->resize((this->width()/2)-2 , this->height());
    right_pane->resize((this->width()/2)-2,this->height());

    left_pane->setFixedSize((this->width()/2)-2 , this->height());
    right_pane->setFixedSize((this->width()/2)-2,this->height());

    //////////////////////////////////////////////////////////////////////
    //////// Add both regions to horizontal Layout
    //////////////////////////////////////////////////////////////////////
    hbox->addWidget(left_pane);
    hbox->setSpacing(4);
    hbox->addWidget(right_pane);

    ///////////////////////////////////////////////////////////////////////
    /////////// Set layout in QWidget
    ////////////////////////////////////////////////////////////////////////
    QWidget *window = new QWidget();
    window->setLayout(hbox);
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    ///////////////// SHORTCUTS //////////////////////////////////////////
    //++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
    QShortcut* openShortCut = new QShortcut(QKeySequence("Ctrl+O"),this);
    QShortcut* saveShortCut = new QShortcut(QKeySequence("Ctrl+S"),this);

    ///////////////////////////////////////////////////////////////////////
    // Set QWidget as the central layout of the main window
    //////////////////////////////////////////////////////////////////////
    setCentralWidget(window);

    ////////////////////////////////////////////////////////////////////
    ///// CONNECT SIGNAL TO EVENT //////////////////////////////////////
    connect(left_pane, SIGNAL(textChanged()), this , SLOT(updateView()));
    connect(openAction, SIGNAL(triggered()),this,SLOT(open()));
    connect(saveAction, SIGNAL(triggered()),this,SLOT(save()));
    connect(exitAction, SIGNAL(triggered()),qApp,SLOT(quit()));
    connect(openShortCut, SIGNAL(activated()), this, SLOT(open()));
    connect(saveShortCut, SIGNAL(activated()), this, SLOT(save()));
    ////////////////////////////////////////////////////////////////////
    ///// FileMenu /////////////////////////////////////////////////////
    fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAction);
    //////////////////////////////////////////////////////////////////////
    /// Open "open file" window at application startup
    ///
    QTimer::singleShot(0,this,SLOT(open()));
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////Destructor//////////////////////////////++++++++++++
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
MainWindow::~MainWindow()
{
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
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save File"), "",
    tr("Text Files (*.txt)"));

            if (fileName != "") {
                QFile file(fileName);
                if (!file.open(QIODevice::WriteOnly)) {
                    // error message
                } else {
                    QTextStream stream(&file);
                    stream << left_pane->toPlainText();
                    stream.flush();
                    file.close();
                }
           }
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//////////////// SLOT: Exit Application /////////////////////////////+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::quit(){
  QMessageBox messageBox;
  messageBox.setWindowTitle("CHEICK BERTHE | Simple Markup");
  messageBox.setText("You are about to close this application");
  messageBox.setStandardButtons(QMessageBox::Yes);
  messageBox.setDefaultButton(QMessageBox::No);
  if(messageBox.exec() == QMessageBox::Yes)
      this->quit();
}

//////////////////////////////////////////////////////////////////////////////
/// Function Bank
///////////////////////////////////////////////////////////////////////////
bool isHeader(QString str){
    int topString = 0;
    int numberOfequalSign = 0;
    int i = 0;
    while(str[i].unicode()!=10){
        topString++;
        i++;
    }
    while(i < str.size()){
        numberOfequalSign++;
        i++;
    }
    //qDebug()<<"top: "<<topString<<" and bottom: "<<numberOfequalSign<<endl;
    if(numberOfequalSign -1 >= topString) return true;
    return false;
}
////////////////////////////////////////////////////////////////////////////////
void processHeaders(QString &str, QRegExp reg1, QRegExp reg2, QString headerType){
    QString dummyString;
    int index1 (-1),index2 (-1);
    str+=QChar('\n');
    for(int i = 0; i < str.size(); i++){
            if(str.indexOf(reg1)>-1)
            {
                index1 = str.indexOf(reg1);
                index2 = str.indexOf(reg2);
                dummyString = str.mid(index1,index2-index1+1);
                   if(isHeader(dummyString)) {
                    QString Replacement = "<"+headerType+">"+dummyString.left(dummyString.indexOf(QChar('\n')))+"</"+headerType+">";
                    str.replace(index1,dummyString.size(),Replacement);
                }//end if
                i +=7;
            }//end if
       }//end for-loop
}
/////////////////////////////////////////////////////////////////////////////////////
int findLastOf(const QString str, const QChar ch, int downFrom){
    int i = downFrom;
    if(i >= str.size()) return -1;
    while(i >= 0 && str[i] != ch ){
        i--;
    }
    if(i < 0) return i;
    else return i;
}
////////////////////////////////////////////////////////////////////////////////////
void processAsterix(QString &str){
    int index2 = str.size()-1;
    QRegExp oneAst("\\*{2,2}[\\S\\s]+\\*{2,2}");
    QRegExp reg2 ("\\*{2,2}");
    int index1 = str.indexOf(oneAst,0);
    index2 = findLastOf(str,'*',index2);
    index2 = findLastOf(str,'*',index2-1);
    qDebug()<<"index1: "<< index1;
    qDebug()<<"index2: "<<index2;
    if(index1 > -1){
        str = (str.replace(index2,2,"</b>")).replace(index1,2,"<b>");
    }
    qDebug()<<"new string is "<< str<<endl;
}
//////////////////////////////////////////////////////////////////////
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
////////////////// Parsers ///////////////////////////////////////////
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
void divideString(QString &str){
    //split text and store as strings containing multiples of any successive
    //characters separated by single 'newline' characters.
    QStringList list = str.split(QRegExp("\n\n+"));
    //join strings of the list into one string separated by 'html paragraph marks' characters
    conquerString(list);
    //qDebug()<<"list is"<<list<<endl;
    str = " <p> "+list.join(" <p> </p> ") + " </p> ";
}
///////////////////////////////////////////////////////////////////////////////
void StripHeadersAndAsterix(QStringList &list, QRegExp reg1, QRegExp reg2, QString headerType, bool AsterixSwitch){
    QString dummyString ;
    QStringList list2;
    foreach (dummyString, list) {
    /////////////////////////////////////////////////////////////////////
        processHeaders(dummyString,reg1,reg2,headerType);
        ///////////////////////////////////////////////////////////////////
        if(AsterixSwitch){

        processAsterix(dummyString);
        }
    //////////////////////////////////////////////////////////////////////
        list2.append(dummyString);
        //qDebug()<<dummyString<<endl;
    }//end foreach

    list = list2;

}
///////////////////////////////////////////////////////////////////////////////
void conquerString(QStringList &list){
    QRegExp rg1 ( QRegExp("[^\n]+\n{1,1}={1,}\n{1,}")), rg2( QRegExp("={1,1}\n{1,}"));
    QString H1 ="h1";
    QRegExp rg3 ( QRegExp("[^\n]+\n{1,1}-{1,}\n{1,}")), rg4( QRegExp("-{1,1}\n{1,}"));
    QString H2 = "h2";
    StripHeadersAndAsterix(list,rg1,rg2,H1,true);

    StripHeadersAndAsterix(list,rg3,rg4,H2,false);

}//end conquer
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
////////////////// SLOT: update WebView /////////////////////////////+
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void MainWindow::updateView(){
    qDebug()<<"*********************************************************"<<endl;
    QString text = left_pane->toPlainText();    //get text from TextEdit window
    divideString(text);
    qDebug()<<"text is: "<<text<<endl;
    text ="<html> <body>" + text + "</html> </body>";
    right_pane->setHtml(text);
    qDebug()<<"*********************************************************"<<endl;
}

