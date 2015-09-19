#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QtWebKit/QWebView>

void aSlot(QString& st1, QString& st2);
QString Parser (QString str);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void updateView();
private:
    QTextEdit *left_pane = NULL;
    QWebView *right_pane = NULL;
};

#endif // MAINWINDOW_H
