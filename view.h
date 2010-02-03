#ifndef VIEW_H
#define VIEW_H

#include <QWidget>

class View : public QWidget
{
Q_OBJECT
public:
    explicit View(QWidget *parent = 0);

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent *e);

};

#endif // VIEW_H
