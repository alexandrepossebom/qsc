#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configuratorview.h"
#include <QRadioButton>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    m_compraAddWidget(NULL), m_clienteAdWidget(NULL), m_pagarAddWidget(NULL)
{
    ui->setupUi(this);
    connect(ui->actionComprar,SIGNAL(triggered(bool)),this,SLOT(compraAdd()));
    connect(ui->actionAdicionar,SIGNAL(triggered(bool)),this,SLOT(clienteAdd()));
    connect(ui->actionConfig,SIGNAL(triggered(bool)),this,SLOT(configSystem()));
    connect(ui->actionPagar,SIGNAL(triggered(bool)),this,SLOT(slotPagar()));


    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);
}

void MainWindow::slotPagar()
{
    if (m_pagarAddWidget == NULL)
    {
        m_pagarAddWidget = new PagarAddView();
        m_stackedWidget->addWidget(m_pagarAddWidget);
    }
    m_stackedWidget->setCurrentWidget(m_pagarAddWidget);
}

void MainWindow::compraAdd()
{
    if (m_compraAddWidget == NULL)
    {
        m_compraAddWidget = new CompraAddView();
        m_stackedWidget->addWidget(m_compraAddWidget);
    }
    m_stackedWidget->setCurrentWidget(m_compraAddWidget);
}

void MainWindow::clienteAdd()
{
    if (m_clienteAdWidget == NULL)
    {
        m_clienteAdWidget = new ClienteAddView();
        m_stackedWidget->addWidget(m_clienteAdWidget);
    }
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
