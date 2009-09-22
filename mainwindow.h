#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include "vendaaddview.h"
#include "clienteaddview.h"

namespace Ui
{
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStackedWidget *m_stackedWidget;
    VendaAddView *m_vendaAddWidget;
    ClienteAddView *m_clienteAdWidget;

private slots:
    void vendaAdd();
    void clienteAdd();
};

#endif // MAINWINDOW_H
