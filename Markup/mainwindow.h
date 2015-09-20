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

void aSlot(QString& st1, QString& st2);
QString Parser (QString str);

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
    QTextEdit *left_pane = NULL;
    QWebView *right_pane = NULL;

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QMenu *fileMenu;
};

#endif // MAINWINDOW_H