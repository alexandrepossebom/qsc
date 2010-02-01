#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include <QDate>
#include "nacionalidade.h"
#include "naturalidade.h"
#include "empresa.h"
#include "cep.h"
#include "telefone.h"
#include <QList>

class Cliente
{
public:
    Cliente();
    void setNome(QString nome);
    void setNacionalidade(Nacionalidade nacionalidade);
    Nacionalidade getNacionalidade();
    QString getNome();
    Naturalidade getNaturalidade();
    void setNaturalidade(Naturalidade naturalidade);
    void setCpf(long long int cpf);
    long long int getCpf();
    void setEstadoCivil(QString estadoCivil);
    QString getEstadoCivil();
    QString getNomePai();
    QString getNomeMae();
    void setNomePai(QString nomePai);
    void setNomeMae(QString nomeMae);
    QString getRg();
    QString getRgOrgaoEmissor();
    QDate getRgDataEmissao();
    void setRg(QString rg);
    void setRgOrgaoEmissor(QString rgOrgaoEmissor);
    void setRgDataEmissao(QDate rgDataEmissao);
    void setEmpresa(Empresa empresa);
    Empresa getEmpresa();
    void setRenda(double renda);
    double getRenda();
    QString getCargo();
    void setCargo(QString cargo);
    void setEndercoNumero(int numero);
    int getEnderecoNumero();
    void setCep(Cep cep);
    Cep getCep();
    QDate getDataNascimento();
    void setDataNascimento(QDate dataNascimento);
    void setId(int id);
    int getId();
    QString getCpfFormated();

    Nacionalidade nacionalidade;
    Empresa empresa;
    Naturalidade naturalidade;
    Cidade localNascimento;
    QString nome;
    long long int cpf;
    QString estadoCivil;
    QString nomePai;
    QString nomeMae;
    QString rg;
    QString rgOrgaoEmissor;
    QDate rgDataEmissao;
    QString cargo;
    double renda;
    int enderecoNumero;
    Cep cep;
    QDate dataNascimento;
    int id;
    QList<Telefone> telefones;
    int diasAtrasado;
    double valorAtraso;
    

};

#endif // CLIENTE_H
