#ifndef EMPRESA_H
#define EMPRESA_H

#include <QString>
#include <QList>
#include "telefone.h"
#include "cep.h"

class Empresa
{
public:
    Empresa();
    QString nome;
    int id;
    QList<Telefone> telefones;
    Cep cep;
    int numero;
};

#endif // EMPRESA_H
