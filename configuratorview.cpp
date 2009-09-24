#include "configuratorview.h"
#include "ui_configuratorview.h"
#include <QSettings>

ConfiguratorView::ConfiguratorView(QWidget *parent) :
    QDialog(parent),
    m_ui(new Ui::ConfiguratorView)
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox,SIGNAL(accepted()),this,SLOT(configurar()));

    QSettings settings("Possebom", "Qsc");

    m_ui->usernameLineEdit->setText( settings.value("Database/UserName").toString() );
    m_ui->passwordLineEdit->setText( settings.value("Database/Password").toString() );
    m_ui->hostnameLineEdit->setText( settings.value("Database/HostName").toString() );
    m_ui->databaseLineEdit->setText( settings.value("Database/DatabaseName").toString() );


}

void ConfiguratorView::configurar()
{

    QSettings settings("Possebom", "Qsc");

    settings.setValue("Database/UserName", m_ui->usernameLineEdit->text());
    settings.setValue("Database/Password", m_ui->passwordLineEdit->text());
    settings.setValue("Database/HostName", m_ui->hostnameLineEdit->text());
    settings.setValue("Database/DatabaseName", m_ui->databaseLineEdit->text());

}

ConfiguratorView::~ConfiguratorView()
{
    delete m_ui;
}

void ConfiguratorView::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        m_ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
