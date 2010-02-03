#ifndef DBUTIL_H
#define DBUTIL_H

#include  <QString>
#include <QtSql>

class DBUtil {

private :
    DBUtil ();

public :
    static QSqlDatabase getDatabase();
    static void removeDatabase ();
    static const QString DATABASE_CONNECT_NAME ;
private:
    static QSqlDatabase m_db;
};
#endif // DBUTIL_H
