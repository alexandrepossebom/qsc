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
    void Add(bool *ok,QString *error,Telefone *telefone);
    bool Add(Telefone * telefone);
    QList<Telefone> getByCliente(Cliente cliente);
private:
    bool ok;
    QString error;
};

#endif // TELEFONECONTROLLER_H
