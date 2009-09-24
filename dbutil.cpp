#include "dbutil.h"
#include <QDebug>

const QString DBUtil::DATABASE_CONNECT_NAME ( "QscDatabase" );


DBUtil::DBUtil()
{

}

QSqlDatabase DBUtil::getDatabase (bool  *ok, QString *error) {
    QSqlDatabase db;
    if (!QSqlDatabase::contains(DBUtil::DATABASE_CONNECT_NAME)) {

        QSettings settings("Possebom", "Qsc");

//        settings.setValue("Database/UserName", "root");
//        settings.setValue("Database/Password", "");
//        settings.setValue("Database/HostName", "localhost");
//        settings.setValue("Database/DatabaseName", "loja");

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
            *ok = result;
        }
        if ((false == result) && (0 != error)) {
            *error = db.lastError().text();
        }
    }
    return db;
}

void  DBUtil::removeDatabase () {
    QSqlDatabase::removeDatabase(DBUtil ::DATABASE_CONNECT_NAME);
}
