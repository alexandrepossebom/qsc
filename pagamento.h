#ifndef PAGAMENTO_H
#define PAGAMENTO_H
#include <QDate>

class Pagamento
{
public:
    Pagamento();
    QDate dataPagamento;
    double valor;
    int id;
    QString getValorFormatado();
};

#endif // PAGAMENTO_H
