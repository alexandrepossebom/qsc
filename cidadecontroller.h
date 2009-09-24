#ifndef CIDADECONTROLLER_H
#define CIDADECONTROLLER_H
#include "cidade.h"


class CidadeController
{
public:
    CidadeController();
    QList<Cidade> getAll();
};

#endif // CIDADECONTROLLER_H
