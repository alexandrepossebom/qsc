#ifndef CEP_H
#define CEP_H
#include "cep.h"
#include "cidade.h"
#include "bairro.h"
#include "endereco.h"
#include "estado.h"

class Cep
{
public:
    Cep();
    void setCep(int cep);
    int getCep();
    void setBairro(Bairro bairro);
    Bairro getBairro();
    void setCidade(Cidade cidade);
    Endereco getEndereco();
    void setEndereco(Endereco endereco);
    void setEstado(Estado estado);
    Estado getEstado();
    Cidade getCidade();

private:
    int cep;
    Bairro bairro;
    Cidade cidade;
    Endereco endereco;
    Estado estado;
};

#endif // CEP_H
