#ifndef NACIONALIDADECONTROLLER_H
#define NACIONALIDADECONTROLLER_H
#include "nacionalidade.h"
#include <QString>
#include <QList>

class NacionalidadeController
{
public:
    NacionalidadeController();
    bool add(Nacionalidade *nacionalidade);
    QString getError();
    QList<Nacionalidade> getAll();
private:
    QString error;
    bool ok;
};

#endif // NACIONALIDADECONTROLLER_H
