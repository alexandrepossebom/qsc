#ifndef ENDERECO_H
#define ENDERECO_H
#include <QString>
#include "estado.h"

class Endereco
{
public:
    Endereco();
    void setNome(QString nome);
    void setBairro(QString bairro);
    void setCep(int cep);
    int getCep();
    void setCidade(QString cidade);
    QString getNome();
    QString getBairro();
    QString getCidade();
    Estado getEstado();
    void setEstado(Estado estado);
private:
    int cep;
    QString nome;
    QString bairro;
    QString cidade;
    Estado estado;
};

#endif // ENDERECO_H
