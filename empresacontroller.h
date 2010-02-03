#ifndef EMPRESACONTROLLER_H
#define EMPRESACONTROLLER_H

#include "empresa.h"

#include <QList>


class EmpresaController
{
public:
    EmpresaController();
    bool addEmpresa(Empresa *empresa);
    QList<Empresa> getAll();
    Empresa getById(int id);
};

#endif // EMPRESACONTROLLER_H
