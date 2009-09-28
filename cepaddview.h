#ifndef CEPADDVIEW_H
#define CEPADDVIEW_H
#include <QCompleter>

#include <QtGui/QDialog>

namespace Ui {
    class CepAddView;
}

class CepAddView : public QDialog {
    Q_OBJECT
public:
    CepAddView(QWidget *parent = 0);
    ~CepAddView();
    void setCep(QString cep);
    QString getCep();
    QString getError();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::CepAddView *m_ui;
    QString cep;
    QString error;


private slots:
    void enderecoChanged(QString nome);
    void addCep();
};

#endif // CEPADDVIEW_H
