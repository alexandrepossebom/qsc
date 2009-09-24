#ifndef ENDERECOCONTROLLER_H
#define ENDERECOCONTROLLER_H
#include "endereco.h"
#include <QList>

class EnderecoController
{
public:
    EnderecoController();
    bool add(Endereco *endereco);
    QString getError();
    Endereco getByCep(int cep);
    QList<Endereco> getAll();
    QList<Endereco> getAll(QString nome);
private:
    Endereco endereco;
    QString error;
};

#endif // ENDERECOCONTROLLER_H
