#ifndef VENDEDOR_H
#define VENDEDOR_H
#include <QString>

class Vendedor
{
public:
    Vendedor();
    void setNome(QString nome);
    QString getNome();
    void setId(int id);
    int getId();

    QString nome;
    int id;
};

#endif // VENDEDOR_H
