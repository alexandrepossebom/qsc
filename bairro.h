#ifndef BAIRRO_H
#define BAIRRO_H
#include <QString>

class Bairro
{
public:
    Bairro();
    void setId(int id);
    void setNome(QString nome);
    QString getNome();
    int getId();

private:
    int id;
    QString nome;
};

#endif // BAIRRO_H
