#ifndef COMPRA_H
#define COMPRA_H
#include "vendedor.h"
#include "formapagamento.h"
#include "cliente.h"
#include <QDate>

class Compra
{
public:
    Compra();
    Vendedor vendedor;
    Cliente cliente;
    FormaPagamento formaPagamento;
    double valor;
    QDate dataCompra;
    int itens;
    bool paga;
    int id;
};

#endif // COMPRA_H
