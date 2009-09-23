#ifndef ESTADOCONTROLLER_H
#define ESTADOCONTROLLER_H
#include <QList>
#include <QString>
#include "estado.h"
class EstadoController
{
public:
    EstadoController();
    QList<Estado> getAll();
    Estado getEstadoByUF(QString UF);
private:
    QString error;
};

#endif // ESTADOCONTROLLER_H
