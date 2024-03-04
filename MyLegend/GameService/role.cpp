#include "role.h"

Role::Role()
{

}

int Role::getOccupation()
{
    return m_occupation;
}

void Role::setOccupation(int occupation)
{
    m_occupation = occupation;
}

int Role::getSex()
{
    return m_sex;
}

void Role::setSex(int sex)
{
    m_sex = sex;
}

double Role::getManaPoint()
{
    return m_manaPoint;
}

void Role::setManaPoint(double manaPoint)
{
    m_manaPoint = manaPoint;
}

int Role::getRebirthLevel()
{
    return m_rebirthLevel;
}

void Role::setRebirthLevel(int level)
{
    m_rebirthLevel = level;
}

int Role::getCurExp()
{
    return m_curExp;
}

void Role::setCurExp(int exp)
{
    m_curExp = exp;
}
