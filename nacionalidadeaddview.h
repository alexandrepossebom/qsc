#ifndef NACIONALIDADEADDVIEW_H
#define NACIONALIDADEADDVIEW_H
#include "nacionalidade.h"

#include <QtGui/QDialog>

namespace Ui {
    class NacionalidadeAddView;
}

class NacionalidadeAddView : public QDialog {
    Q_OBJECT
public:
    NacionalidadeAddView(QWidget *parent = 0);
    ~NacionalidadeAddView();
    Nacionalidade getNew();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::NacionalidadeAddView *m_ui;
    Nacionalidade nacionalidade;

private slots:
    void add();
};

#endif // NACIONALIDADEADDVIEW_H
