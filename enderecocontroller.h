#ifndef ENDERECOCONTROLLER_H
#define ENDERECOCONTROLLER_H
#include "endereco.h"

class EnderecoController
{
public:
    EnderecoController();
    bool add(Endereco *endereco);
    QString getError();
    Endereco getByCep(int cep);
private:
    Endereco endereco;
    QString error;
};

#endif // ENDERECOCONTROLLER_H
