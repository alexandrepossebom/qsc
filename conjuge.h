#ifndef CONJUGE_H
#define CONJUGE_H
#include "cliente.h"
#include "empresa.h"
#include <QDate>
#include <QString>

class Conjuge
{
public:
    Conjuge();
    Empresa empresa;
    Cliente cliente;
    QString nome;
    QDate dataNascimento;
    double renda;
    QString cargo;
    int id;
};

#endif // CONJUGE_H
