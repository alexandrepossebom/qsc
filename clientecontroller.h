#ifndef CLIENTECONTROLLER_H
#define CLIENTECONTROLLER_H

#include "cliente.h"

class ClienteController
{
public:
    ClienteController();
    bool addCliente(bool *ok,QString *error,Cliente cliente);
};

#endif // CLIENTECONTROLLER_H
