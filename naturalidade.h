#ifndef NATURALIDADE_H
#define NATURALIDADE_H
#include <QString>

class Naturalidade
{
public:
    Naturalidade();
    QString getNome();
    int getId();
    void setId(int id);
    void setNome(QString nome);
private:
    QString nome;
    int id;

};

#endif // NATURALIDADE_H
