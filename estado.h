#ifndef ESTADO_H
#define ESTADO_H
#include <QString>

class Estado
{
public:
    Estado();
    QString getUF();
    void setUF(QString UF);
    QString getNome();
    void setNome(QString nome);

    QString UF;
    QString nome;
};

#endif // ESTADO_H
