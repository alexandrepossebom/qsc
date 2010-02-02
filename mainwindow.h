#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QStackedWidget>
#include <QWidget>
#include "compraaddview.h"
#include "clienteaddview.h"
#include "pagaraddview.h"
#include "clientelist.h"

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

    void showWidget(QWidget *w = 0);

private:
    Ui::MainWindow *ui;

private slots:
    void compraAdd();
    void clienteAdd();
    void configSystem();
    void slotPagar();
    void slotClientList();
};

#endif // MAINWINDOW_H
