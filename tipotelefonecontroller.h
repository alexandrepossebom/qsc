#ifndef TIPOTELEFONECONTROLLER_H
#define TIPOTELEFONECONTROLLER_H
#include <QList>
#include "tipotelefone.h"

class TipoTelefoneController
{
public:
    TipoTelefoneController();
    QList<TipoTelefone> getAll();
};

#endif // TIPOTELEFONECONTROLLER_H
