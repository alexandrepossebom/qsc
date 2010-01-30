#include "configuratorview.h"
#include "ui_configuratorview.h"
#include <QSettings>
#include <QFileDialog>

ConfiguratorView::ConfiguratorView(QWidget *parent) :
        QDialog(parent),
        m_ui(new Ui::ConfiguratorView)
{
    m_ui->setupUi(this);

    connect(m_ui->buttonBox,SIGNAL(accepted()),this,SLOT(configurar()));

    QSettings settings("Possebom", "Qsc");
    m_ui->databaseLineEdit->setText( settings.value("Database/DatabaseName").toString() );
    connect(m_ui->toolButton,SIGNAL(clicked()),this,SLOT(chooseFile()));

}

void ConfiguratorView::chooseFile()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Database (*.db)"));
    if (dialog.exec())
        m_ui->databaseLineEdit->setText(dialog.selectedFiles().at(0));
}

void ConfiguratorView::configurar()
{

    QSettings settings("Possebom", "Qsc");
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
