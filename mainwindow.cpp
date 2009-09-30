#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "configuratorview.h"
#include <QRadioButton>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow),
    m_compraAddWidget(NULL), m_clienteAdWidget(NULL)
{
    ui->setupUi(this);
    connect(ui->actionComprar,SIGNAL(triggered(bool)),this,SLOT(compraAdd()));
    connect(ui->actionAdicionar,SIGNAL(triggered(bool)),this,SLOT(clienteAdd()));
    connect(ui->actionConfig,SIGNAL(triggered(bool)),this,SLOT(configSystem()));

//    QRadioButton *radio1 = new QRadioButton(tr("&Radio button 1"));
//    QRadioButton *radio2 = new QRadioButton(tr("R&adio button 2"));
//    QRadioButton *radio3 = new QRadioButton(tr("Ra&dio button 3"));
//
//    radio1->setChecked(true);
//
//    QVBoxLayout *vbox = new QVBoxLayout;
//    vbox->addWidget(radio1);
//    vbox->addWidget(radio2);
//    vbox->addWidget(radio3);
//    vbox->addStretch(1);
//    ui->groupBox_2->setLayout(vbox);

    m_stackedWidget = new QStackedWidget(this);
    setCentralWidget(m_stackedWidget);
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
