#ifndef TELEFONECONTROLLER_H
#define TELEFONECONTROLLER_H
#include "dbutil.h"
#include "telefone.h"
#include <QList>
#include "cliente.h"

class TelefoneController
{
public:
    TelefoneController();
    bool Add(Telefone *telefone);
    QList<Telefone> getByCliente(Cliente cliente);
};

#endif // TELEFONECONTROLLER_H
