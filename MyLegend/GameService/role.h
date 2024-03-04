#ifndef ROLE_H
#define ROLE_H

#include "gamecharacter.h"

class Role : public GameCharacter
{
public:
    Role();

    int getOccupation();
    void setOccupation(int occupation);

    int getSex();
    void setSex(int sex);

    double getManaPoint();
    void setManaPoint(double manaPoint);

    int getRebirthLevel();
    void setRebirthLevel(int level);

    int getCurExp();
    void setCurExp(int exp);

private:   
    int m_occupation;
    int m_sex;
    double m_manaPoint;
    int m_rebirthLevel;
    int m_curExp;
};



#endif // ROLE_H
