#include "cliente.h"

Cliente::Cliente()
{
}

void Cliente::setNome(QString nome)
{
    this->nome = nome;
}

QString Cliente::getNome()
{
    return nome;
}

void Cliente::setNacionalidade(Nacionalidade nacionalidade)
{
    this->nacionalidade = nacionalidade;
}

Nacionalidade Cliente::getNacionalidade()
{
    return nacionalidade;
}

void Cliente::setNaturalidade(Naturalidade naturalidade)
{
    this->naturalidade = naturalidade;
}

Naturalidade Cliente::getNaturalidade()
{
    return naturalidade;
}

void Cliente::setCpf(int cpf)
{
    this->cpf = cpf;
}

int Cliente::getCpf()
{
    return cpf;
}

QString Cliente::getEstadoCivil()
{
    return estadoCivil;
}

void Cliente::setEstadoCivil(QString estadoCivil)
{
    this->estadoCivil = estadoCivil;
}

void Cliente::setNomeMae(QString nomeMae)
{
    this->nomeMae = nomeMae;
}

void Cliente::setNomePai(QString nomePai)
{
    this->nomePai = nomePai;
}

QString Cliente::getNomeMae()
{
    return nomeMae;
}

QString Cliente::getNomePai()
{
    return nomePai;
}

QString Cliente::getRg()
{
    return rg;
}

QString Cliente::getRgOrgaoEmissor()
{
    return rgOrgaoEmissor;
}

QDate Cliente::getRgDataEmissao()
{
    return rgDataEmissao;
}

void Cliente::setRg(QString rg)
{
    this->rg = rg;
}

void Cliente::setRgOrgaoEmissor(QString rgOrgaoEmissor)
{
    this->rgOrgaoEmissor = rgOrgaoEmissor;
}

void Cliente::setRgDataEmissao(QDate rgDataEmissao)
{
    this->rgDataEmissao = rgDataEmissao;
}

void Cliente::setEmpresa(Empresa empresa)
{
    this->empresa = empresa;
}
Empresa Cliente::getEmpresa()
{
    return empresa;
}

void Cliente::setRenda(double renda)
{
    this->renda = renda;
}
double Cliente::getRenda()
{
    return renda;
}
QString Cliente::getCargo()
{
    return cargo;
}
void Cliente::setCargo(QString cargo)
{
    this->cargo = cargo;
}

void Cliente::setEndercoNumero(int numero)
{
    this->enderecoNumero = numero;
}

int Cliente::getEnderecoNumero()
{
    return enderecoNumero;
}
void Cliente::setCep(Cep cep)
{
    this->cep = cep;
}
Cep Cliente::getCep()
{
    return cep;
}
QDate Cliente::getDataNascimento()
{
    return dataNascimento;
}
void Cliente::setDataNascimento(QDate dataNascimento)
{
    this->dataNascimento = dataNascimento;
}
