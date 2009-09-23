#ifndef CIDADE_H
#define CIDADE_H
#include <QString>

class Cidade
{
public:
    Cidade();
    void setId(int id);
    void setNome(QString nome);
    QString getNome();
    int getId();
private:
    int id;
    QString nome;
};

#endif // CIDADE_H
