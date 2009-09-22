#ifndef EMPRESA_H
#define EMPRESA_H

#include <QString>

class Empresa
{
public:
    Empresa();
    void setNome(QString nome);
    void setTelefone(QString telefone);
    QString getNome();
    QString getTelefone();
    void setId(int id);
    int getId();
private:
    QString nome;
    QString telefone;
    int id;
};

#endif // EMPRESA_H
