#ifndef CEPCONTROLLER_H
#define CEPCONTROLLER_H
#include "bairro.h"
#include "estado.h"
#include "cidade.h"
#include "endereco.h"
#include "cep.h"


class CepController
{
public:
    CepController();
    Cep getByCep(bool *ok,QString *error,int cep);
    void add(bool *ok,QString *error,Cep cep);
};

#endif // CEPCONTROLLER_H
