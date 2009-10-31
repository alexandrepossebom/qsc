#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configuratorview.h"
#include <QRadioButton>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionComprar,SIGNAL(triggered(bool)),this,SLOT(compraAdd()));
    connect(ui->actionAdicionar,SIGNAL(triggered(bool)),this,SLOT(clienteAdd()));
    connect(ui->actionConfig,SIGNAL(triggered(bool)),this,SLOT(configSystem()));
    connect(ui->actionPagar,SIGNAL(triggered(bool)),this,SLOT(slotPagar()));
    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);
    m_clienteAdWidget = NULL;
    m_compraAddWidget = NULL;
    m_pagarAddWidget = NULL;
}

void MainWindow::slotPagar()
{
    delete m_pagarAddWidget;
    m_pagarAddWidget = new PagarAddView();
    m_stackedWidget->addWidget(m_pagarAddWidget);
    m_stackedWidget->setCurrentWidget(m_pagarAddWidget);
}

void MainWindow::compraAdd()
{
    delete m_compraAddWidget;
    m_compraAddWidget = new CompraAddView();
    m_stackedWidget->addWidget(m_compraAddWidget);
    m_stackedWidget->setCurrentWidget(m_compraAddWidget);
}

void MainWindow::clienteAdd()
{
    delete m_clienteAdWidget;
    m_clienteAdWidget = new ClienteAddView();
    m_stackedWidget->addWidget(m_clienteAdWidget);
    m_stackedWidget->setCurrentWidget(m_clienteAdWidget);
}

void MainWindow::configSystem()
{
    ConfiguratorView cv;
    cv.exec();
}


MainWindow::~MainWindow()
{
    delete ui;
}
