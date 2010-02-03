#ifndef CLIENTECONTROLLER_H
#define CLIENTECONTROLLER_H

#include "cliente.h"

class ClienteController
{
public:
    ClienteController();
    void addCliente(bool *ok,QString *error,Cliente *cliente);
    QList<Cliente> getClientesByName(QString nome,int limit = 0);
    QList<Cliente> getClientesAtrasados(QString nome);
    Cliente getClienteByCpf(long long int cpf);
};

#endif // CLIENTECONTROLLER_H
