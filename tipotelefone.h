#ifndef TIPOTELEFONE_H
#define TIPOTELEFONE_H
#include <QString>

class TipoTelefone
{
public:
    TipoTelefone();
    QString getNome();
    int getId();
    void setNome(QString nome);
    void setId(int id);
    int id;
    QString nome;
};

#endif // TIPOTELEFONE_H
