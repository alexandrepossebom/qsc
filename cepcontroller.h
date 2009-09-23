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
    Cep getByCep(int cep);
};

#endif // CEPCONTROLLER_H
