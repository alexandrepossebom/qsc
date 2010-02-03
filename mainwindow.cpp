#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configuratorview.h"
#include "dbutil.h"
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionComprar,SIGNAL(triggered(bool)),this,SLOT(compraAdd()));
    connect(ui->actionAdicionar,SIGNAL(triggered(bool)),this,SLOT(clienteAdd()));
    connect(ui->actionConfig,SIGNAL(triggered(bool)),this,SLOT(configSystem()));
    connect(ui->actionPagar,SIGNAL(triggered(bool)),this,SLOT(slotPagar()));
    connect(ui->actionListar,SIGNAL(triggered(bool)),this,SLOT(slotClientList()));

//    setWindowState(Qt::WindowMaximized);
    showWidget();
}

void MainWindow::slotClientList()
{
    showWidget(new ClienteList());
}

void MainWindow::slotPagar()
{
    showWidget(new PagarAddView());
}

void MainWindow::compraAdd()
{
    showWidget(new CompraAddView());
}

void MainWindow::clienteAdd()
{
    showWidget(new ClienteAddView());
}

void MainWindow::configSystem()
{
    ConfiguratorView cv;
    cv.exec();
}


MainWindow::~MainWindow()
{
    delete ui;
    DBUtil::removeDatabase();
}

void MainWindow::showWidget(QWidget *w)
{
    delete centralWidget();

    if (!w)
    {
        QLabel *l = new QLabel();
        l->setPixmap(QPixmap(":/images/images/qsc.png"));
        l->setAlignment(Qt::AlignCenter);
        w = l;
    }

    View *v = dynamic_cast<View*>(w);
    if (v)
        connect(v, SIGNAL(closed()), this, SLOT(slotClearView()));
    setCentralWidget(w);
}

void MainWindow::slotClearView()
{
    showWidget();
}
