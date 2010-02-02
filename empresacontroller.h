#ifndef EMPRESACONTROLLER_H
#define EMPRESACONTROLLER_H

#include "empresa.h"

#include <QList>


class EmpresaController
{
public:
    EmpresaController();
    bool addEmpresa(Empresa *empresa);
    QString getError();
    QList<Empresa> getAll();
    Empresa getById(int id);
private:
    QString error;
    bool ok;
};

#endif // EMPRESACONTROLLER_H
