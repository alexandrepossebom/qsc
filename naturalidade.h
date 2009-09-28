#ifndef NATURALIDADE_H
#define NATURALIDADE_H
#include <QString>

class Naturalidade
{
public:
    Naturalidade();
    QString getNome();
    QString getUF();
    void setUF(QString UF);
    void setNome(QString nome);
private:
    QString nome;
    QString UF;

};

#endif // NATURALIDADE_H
