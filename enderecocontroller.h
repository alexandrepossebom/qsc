#ifndef ENDERECOCONTROLLER_H
#define ENDERECOCONTROLLER_H
#include "endereco.h"
#include <QList>

class EnderecoController
{
public:
    EnderecoController();
    void add(Endereco *endereco);
    Endereco getByCep(int cep);
    QList<Endereco> getAll(QString nome = 0,int limit = 0);
private:
    Endereco endereco;
};

#endif // ENDERECOCONTROLLER_H
