#ifndef FORMAPAGAMENTO_H
#define FORMAPAGAMENTO_H
#include <QString>

class FormaPagamento
{
public:
    FormaPagamento();
    void setId(int id);
    int getId();
    void setParcelas(int parcelas);
    int getParcelas();
    bool isEntrada();
    void setEntrada(bool entrada);
    double getDesconto();
    double getJuro();
    void setJuro(double juro);
    void setDesconto(double desconto);
    QString getNome();
    void setNome(QString nome);
    QString nome;
    int id;
    int parcelas;
    bool entrada;
    double desconto;
    double juro;
};

#endif // FORMAPAGAMENTO_H
