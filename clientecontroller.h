#ifndef CLIENTECONTROLLER_H
#define CLIENTECONTROLLER_H

#include "cliente.h"

class ClienteController
{
public:
    ClienteController();
    void addCliente(bool *ok,QString *error,Cliente cliente);
    QList<Cliente> getClientesByName(bool *ok,QString *error,QString nome,int limit);
    Cliente getClienteByName(bool *ok,QString *error,QString nome);
};

#endif // CLIENTECONTROLLER_H
