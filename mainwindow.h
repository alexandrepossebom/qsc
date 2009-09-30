#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include "compraaddview.h"
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
    CompraAddView *m_compraAddWidget;
    ClienteAddView *m_clienteAdWidget;

private slots:
    void compraAdd();
    void clienteAdd();
    void configSystem();
};

#endif // MAINWINDOW_H
