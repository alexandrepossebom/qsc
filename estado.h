#ifndef ESTADO_H
#define ESTADO_H
#include <QString>

class Estado
{
public:
    Estado();
    int getId();
    void setId(int id);
    QString getNome();
    void setNome(QString nome);
private:
    int id;
    QString nome;
};

#endif // ESTADO_H
