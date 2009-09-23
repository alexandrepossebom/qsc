#include "cep.h"

Cep::Cep()
{
}

void Cep::setCep(int cep)
{
    this->cep = cep;
}

void Cep::setEndereco(Endereco endereco)
{
    this->endereco = endereco;
}

Cidade Cep::getCidade()
{
    return cidade;
}

int Cep::getCep()
{
    return this->cep;
}

void Cep::setBairro(Bairro bairro)
{
    this->bairro = bairro;
}

Bairro Cep::getBairro()
{
    return bairro;
}

void Cep::setCidade(Cidade cidade)
{
    this->cidade = cidade;
}

Endereco Cep::getEndereco()
{
    return endereco;
}

void Cep::setEstado(Estado estado)
{
    this->estado = estado;
}

Estado Cep::getEstado()
{
    return estado;
}
