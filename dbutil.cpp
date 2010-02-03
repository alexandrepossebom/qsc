#include "dbutil.h"
#include <QDebug>

const QString DBUtil::DATABASE_CONNECT_NAME ( "QscDatabase" );

QSqlDatabase DBUtil::m_db;

DBUtil::DBUtil()
{

}

QSqlDatabase DBUtil::getDatabase() {
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
