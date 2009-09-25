#ifndef ENDERECOCONTROLLER_H
#define ENDERECOCONTROLLER_H
#include "endereco.h"
#include <QList>

class EnderecoController
{
public:
    EnderecoController();
    bool add(bool *ok,QString *error,Endereco *endereco);
    QString getError();
    Endereco getByCep(bool *ok,QString *error,int cep);
    QList<Endereco> getAll(bool *ok,QString *error);
    QList<Endereco> getAll(bool *ok,QString *error,QString nome);
    QList<Endereco> getAll(bool *ok,QString *error,QString nome,int limit);
private:
    Endereco endereco;
};

#endif // ENDERECOCONTROLLER_H
