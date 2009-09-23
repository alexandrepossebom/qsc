#ifndef ENDERECO_H
#define ENDERECO_H
#include <QString>
#include "estado.h"

class Endereco
{
public:
    Endereco();
    void setNome(QString nome);
    void setId(int id);
    int getId();
    QString getNome();

private:
    int id;
    QString nome;
};

#endif // ENDERECO_H
