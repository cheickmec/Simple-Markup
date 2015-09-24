#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QApplication>
#include <QTextEdit>
#include <QtWebKit/QWebView>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QIcon>
#include <QShortcut>
#include <QTimer>
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
void aSlot(QString& st1, QString& st2);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void divideString(QString& str);
void conquerString(QStringList& list);
void StripHeadersAndAsterix(QStringList& list, QRegExp reg1, QRegExp reg2, QString headerType,bool AsterixSwitch);
void processHeaders(QString& str, QRegExp reg1, QRegExp reg2, QString headerType);
void processAsterix(QString& str);
bool isHeader(QString str);
int findLastOf(const QString str, const QChar ch,int downFrom);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private slots:
    void open();
    void save();
    void quit();
    void updateView();
private:
//******** LEFT AND RIGHT PANES ************//
//******************************************//
    QTextEdit *left_pane = NULL;
    QWebView *right_pane = NULL;
//******** SHORTCUTS ***********************//
    QShortcut* openShortCut;
    QShortcut* saveShortCut;

//******** FILE ACTIONS ********************//
//******************************************//
    QAction *openAction;    //Open File
    QAction *saveAction;    //Save File
//******** APP ACTION **********************//
    QAction *exitAction;    //Exit Application
//******************************************//
    QMenu *fileMenu;
};

#endif // MAINWINDOW_H

