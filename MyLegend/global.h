#ifndef GLOBAL_H
#define GLOBAL_H

#include "datastruct.h"

enum EN_MessageType
{
    MESSAGE_ERROR = 0,
    MESSAGE_EVENT,
    MESSAGE_OPERATOR,
};

enum EN_Occupation
{
    Occupation_ZHANSHI = 0,
    Occupation_FASHI,
    Occupation_DAOSHI,
};

enum EN_Sex
{
    Sex_Man = 0,
    Sex_Woman,
};

extern int g_userId;
extern QString g_userName;
extern int g_roleId;

#endif // GLOBAL_H
