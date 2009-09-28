#ifndef CLIENTECONTROLLER_H
#define CLIENTECONTROLLER_H

#include "cliente.h"

class ClienteController
{
public:
    ClienteController();
    bool addCliente(bool *ok,QString *error,Cliente cliente);
    QList<Cliente> getClientesByName(bool *ok,QString *error,QString nome,int limit);
};

#endif // CLIENTECONTROLLER_H
