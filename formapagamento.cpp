#include "formapagamento.h"

FormaPagamento::FormaPagamento()
{
}

void FormaPagamento::setId(int id)
{
    this->id = id;
}

int FormaPagamento::getId()
{
    return id;
}

void FormaPagamento::setParcelas(int parcelas)
{
    this->parcelas = parcelas;
}
int FormaPagamento::getParcelas()
{
    return parcelas;
}
bool FormaPagamento::isEntrada()
{
    return entrada;
}
void FormaPagamento::setEntrada(bool entrada)
{
    this->entrada = entrada;
}
double FormaPagamento::getDesconto()
{
    return desconto;
}
double FormaPagamento::getJuro()
{
    return juro;
}
void FormaPagamento::setJuro(double juro)
{
    this->juro = juro;
}
void FormaPagamento::setDesconto(double desconto)
{
    this->desconto = desconto;
}

QString FormaPagamento::getNome()
{
    return nome;
}
void FormaPagamento::setNome(QString nome)
{
    this->nome = nome;
}
