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
private:
    QString error;
    bool ok;
};

#endif // EMPRESACONTROLLER_H
