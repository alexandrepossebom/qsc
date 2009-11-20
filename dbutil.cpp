#include "dbutil.h"
#include <QDebug>

const QString DBUtil::DATABASE_CONNECT_NAME ( "QscDatabase" );


DBUtil::DBUtil()
{

}

void DBUtil::log(QString tag,QString texto)
{
    bool ok = true;
    QString *error;

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
    QSqlDatabase db;
    bool a = true;
    ok = &a;
    if (!QSqlDatabase::contains(DBUtil::DATABASE_CONNECT_NAME)) {

        QSettings settings("Possebom", "Qsc");
        QString hostname = settings.value("Database/HostName").toString();
        QString password = settings.value("Database/Password").toString();
        QString username = settings.value("Database/UserName").toString();
        QString databasename = settings.value("Database/DatabaseName").toString();

        db = QSqlDatabase::addDatabase("QMYSQL" , DBUtil ::DATABASE_CONNECT_NAME );
        db.setHostName(hostname);
        db.setDatabaseName(databasename);
        db.setUserName(username);
        db.setPassword(password);
    } else {
        db = QSqlDatabase::database(DBUtil ::DATABASE_CONNECT_NAME , true );
    }

    if (!db.isOpen()) {
        bool result = db.open();
        if (0 != ok) {
            ok = &result;
        }
        if ((false == result) && (0 != error)) {
            error->clear();
            error->append(db.lastError().text());
        }
    }
    return db;
}

void  DBUtil::removeDatabase () {
    QSqlDatabase::removeDatabase(DBUtil ::DATABASE_CONNECT_NAME);
}
