#include "endereco.h"

Endereco::Endereco()
{
}

void Endereco::setNome(QString nome)
{
    this->nome = nome;
}

void Endereco::setCep(int cep)
{
    this->cep = cep;
}

void Endereco::setBairro(QString bairro)
{
    this->bairro = bairro;
}

QString Endereco::getBairro()
{
    return bairro;
}

QString Endereco::getNome()
{
    return nome;
}

int Endereco::getCep()
{
    return cep;
}

QString Endereco::getCidade()
{
    return cidade;
}

void Endereco::setCidade(QString cidade)
{
    this->cidade = cidade;
}

void Endereco::setEstado(Estado estado)
{
    this->estado = estado;
}

Estado Endereco::getEstado()
{
    return estado;
}
