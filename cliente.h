#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include "nacionalidade.h"
#include "naturalidade.h"
#include "empresa.h"

class Cliente
{
public:
    Cliente();
    void setNome(QString nome);
    void setNacionalidade(Nacionalidade nacionalidade);
    Nacionalidade getNacionalidade();
    QString getNome();
    Naturalidade getNaturalidade();
    void setNaturalidade(Naturalidade naturalidade);
private:
    Nacionalidade nacionalidade;
    Empresa empresa;
    Naturalidade naturalidade;
    QString nome;
};

#endif // CLIENTE_H
