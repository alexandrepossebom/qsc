#ifndef TELEFONECONTROLLER_H
#define TELEFONECONTROLLER_H
#include "dbutil.h"
#include "telefone.h"

class TelefoneController
{
public:
    TelefoneController();
    void Add(bool *ok,QString *error,Telefone *telefone);
    bool Add(Telefone * telefone);
};

#endif // TELEFONECONTROLLER_H
