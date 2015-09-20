#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
<<<<<<< HEAD
#include <QApplication>
#include <QTextEdit>
#include <QtWebKit/QWebView>
#include <QAction>
#include <QMenuBar>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>
#include <QIcon>
=======
#include <QTextEdit>
#include <QtWebKit/QWebView>
>>>>>>> d5f7148a7540593a15f32e6cdfc4e97e6eed2735

void aSlot(QString& st1, QString& st2);
QString Parser (QString str);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
<<<<<<< HEAD
private slots:
    void open();
    void save();
    void quit();
=======
public slots:
>>>>>>> d5f7148a7540593a15f32e6cdfc4e97e6eed2735
    void updateView();
private:
    QTextEdit *left_pane = NULL;
    QWebView *right_pane = NULL;
<<<<<<< HEAD

    QAction *openAction;
    QAction *saveAction;
    QAction *exitAction;

    QMenu *fileMenu;
=======
>>>>>>> d5f7148a7540593a15f32e6cdfc4e97e6eed2735
};

#endif // MAINWINDOW_H
