#include "dbutil.h"
#include <QDebug>

const QString DBUtil::DATABASE_CONNECT_NAME ( "QscDatabase" );

QSqlDatabase DBUtil::m_db;

DBUtil::DBUtil()
{

}

void DBUtil::log(QString tag,QString texto)
{
    bool ok = true;
    QString *error = new QString();

    QSqlDatabase db = DBUtil::getDatabase(&ok, error);
    QSqlQuery query(db);

    QString sql;
    sql.append("insert into log (texto,tag) VALUES (:texto,:tag)");
    query.prepare(sql);
    query.bindValue(":tag",tag.toLower());
    query.bindValue(":texto",texto);

    query.exec();
}

QSqlDatabase DBUtil::getDatabase (bool  *ok, QString *error) {
    if (!QSqlDatabase::contains(DBUtil::DATABASE_CONNECT_NAME)) {
        QSettings settings("Possebom", "Qsc");
        QString databasename = settings.value("Database/DatabaseName").toString();

        m_db = QSqlDatabase::addDatabase("QSQLITE" , DBUtil ::DATABASE_CONNECT_NAME );
        m_db.setDatabaseName(databasename);
        m_db.open();
    }
    return m_db;
}

void  DBUtil::removeDatabase () {
    QSqlDatabase::removeDatabase(DBUtil ::DATABASE_CONNECT_NAME);
}
