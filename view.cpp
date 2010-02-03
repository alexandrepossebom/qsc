#include "view.h"

View::View(QWidget *parent) :
    QWidget(parent)
{
}

void View::closeEvent(QCloseEvent *e)
{
    QWidget::closeEvent(e);
    emit closed();
}
