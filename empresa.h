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
    void setNome(QString nome);
    QString getNome();
    void setId(int id);
    int getId();

    QString nome;
    int id;
    QList<Telefone> telefones;
    Cep cep;
    int numero;
};

#endif // EMPRESA_H
