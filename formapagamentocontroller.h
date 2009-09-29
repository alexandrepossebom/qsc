#ifndef FORMAPAGAMENTOCONTROLLER_H
#define FORMAPAGAMENTOCONTROLLER_H
#include <QList>
#include <QtSql>
#include "formapagamento.h"
#include "dbutil.h"

class FormaPagamentoController
{
public:
    FormaPagamentoController();
    QList<FormaPagamento> getAll(bool *ok,QString *error);
    FormaPagamento getById(bool *ok,QString *error,int id);
};

#endif // FORMAPAGAMENTOCONTROLLER_H
