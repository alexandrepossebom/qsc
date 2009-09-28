#ifndef CLIENTE_H
#define CLIENTE_H

#include <QString>
#include <QDate>
#include "nacionalidade.h"
#include "naturalidade.h"
#include "empresa.h"
#include "cep.h"

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
    void setCpf(int cpf);
    int getCpf();
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


private:
    Nacionalidade nacionalidade;
    Empresa empresa;
    Naturalidade naturalidade;
    QString nome;
    int cpf;
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

};

#endif // CLIENTE_H
