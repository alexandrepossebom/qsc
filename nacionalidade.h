#ifndef NACIONALIDADE_H
#define NACIONALIDADE_H

#include <QString>

class Nacionalidade
{
public:
    Nacionalidade();
    void setNome(QString nome);
    QString getNome();
    void setId(int id);
    int getId();
private:
    QString nome;
    int id;
};

#endif // NACIONALIDADE_H
