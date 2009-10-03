#ifndef TELEFONE_H
#define TELEFONE_H
#include "tipotelefone.h"

class Telefone
{
public:
    Telefone();
    long long int numero;
    TipoTelefone tipoTelefone;
    int id;

};

#endif // TELEFONE_H
