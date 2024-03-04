#ifndef GAMECHARACTER_H
#define GAMECHARACTER_H

#include <QObject>

class GameCharacter
{
public:
    GameCharacter();

    bool getStaFlag();
    void setStaFlag(bool flag);

    QString getName();
    void setName(QString name);

    int getLevel();
    void setLevel(int level);

    double getHitPoint();
    void setHitPoint(double hitPoint);

    double getAttackMax();
    void setAtttackMax(double attackMax);

    double getAttackMin();
    void setAtttackMin(double attackMin);

    double getDefense();
    void setDefense(double defense);

    double getPhysicalAttackMax();
    double getPhysicalAttackMin();

    double getMagicAttackMax();
    double getMagicAttackMin();

    double getPhysicalDefense();
    double getMagicDefense();

protected:
    bool m_staFlag;

    QString m_name;
    int m_level;

    double m_hitPoint;

    double m_attackMin;
    double m_attackMax;
    double m_defense;

    double m_physicalAttackMax;
    double m_physicalAttackMin;
    double m_magicAttackMax;
    double m_magicAttackMin;

    double m_physicalDefense;
    double m_magicDefense;
};

#endif // GAMECHARACTER_H
