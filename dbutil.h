#ifndef DBUTIL_H
#define DBUTIL_H

#include  <QString>
#include <QtSql>

class DBUtil {

private :
    DBUtil ();

public :
    static QSqlDatabase getDatabase (bool *ok = 0, QString *error = 0);
    static void log(QString tag,QString texto);
    static void removeDatabase ();

    static const QString DATABASE_CONNECT_NAME ;
};
#endif // DBUTIL_H
