#include "telefonecontroller.h"

TelefoneController::TelefoneController()
{
}

bool TelefoneController::Add(Telefone *telefone)
{
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);

    QString sql;
    sql.append("insert into telefone (numero,tipo_telefone_id) VALUES (:numero,:tipo_telefone_id)");
    query.prepare(sql);
    query.bindValue(":tipo_telefone_id",telefone->tipoTelefone.id);
    query.bindValue(":numero",telefone->numero);

    if( !query.exec() )
    {
        query.prepare("select id from telefone where numero = :numero");
        query.bindValue(":numero",telefone->numero);
        if(query.exec())
        {
            query.next();
            telefone->id = query.value(0).toInt();
        }else{
           qDebug() << query.lastError().text();
           return false;
        }
    }else{
        telefone->id = query.lastInsertId().toInt();
    }
    return true;
}

QList<Telefone> TelefoneController::getByCliente(Cliente cliente)
{    
    QSqlDatabase db = DBUtil::getDatabase();
    QSqlQuery query(db);
    query.prepare("select t.numero,tt.nome from tipo_telefone tt,cliente c,cliente_has_telefone ct,telefone t where c.id = :id and ct.cliente_id = c.id and t.id = ct.telefone_id and tt.id = t.tipo_telefone_id");
    query.bindValue(":id",cliente.id);

    QList<Telefone> telefones;
    if( !query.exec() )
    {
        qDebug() << query.lastError().text();
        return telefones;
    }

    int fieldTipoNome = query.record().indexOf("nome");
    int fieldNumero = query.record().indexOf("numero");

    Telefone telefone;
    while (query.next()) {
        telefone.tipoTelefone.nome = query.value(fieldTipoNome).toString();
        telefone.numero = query.value(fieldNumero).toLongLong();
        telefones.append(telefone);
    }
    return telefones;
}
