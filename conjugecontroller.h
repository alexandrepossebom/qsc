#ifndef CONJUGECONTROLLER_H
#define CONJUGECONTROLLER_H
#include "conjuge.h"
#include "dbutil.h"

class ConjugeController
{
public:
    ConjugeController();
    void Add(bool *ok,QString *error,Conjuge *conjuge);
};

#endif // CONJUGECONTROLLER_H
