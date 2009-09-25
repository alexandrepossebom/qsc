#ifndef BAIRROCONTROLLER_H
#define BAIRROCONTROLLER_H
#include <QList>
#include <QString>
#include "bairro.h"
#include "dbutil.h"

class BairroController
{
public:
    BairroController();
    QList<Bairro> getAll(bool *ok,QString *error);
};

#endif // BAIRROCONTROLLER_H
