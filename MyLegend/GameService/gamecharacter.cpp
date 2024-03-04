#include "gamecharacter.h"

GameCharacter::GameCharacter()
    :m_staFlag(false)
{

}

bool GameCharacter::getStaFlag()
{
    return m_staFlag;
}

void GameCharacter::setStaFlag(bool flag)
{
    m_staFlag = flag;
}

QString GameCharacter::getName()
{
    return m_name;
}

void GameCharacter::setName(QString name)
{
    m_name = name;
}

int GameCharacter::getLevel()
{
    return m_level;
}

void GameCharacter::setLevel(int level)
{
    m_level = level;
}

double GameCharacter::getHitPoint()
{
    return m_hitPoint;
}

void GameCharacter::setHitPoint(double hitPoint)
{
    m_hitPoint = hitPoint;
}

double GameCharacter::getAttackMax()
{
    return m_attackMax;
}

void GameCharacter::setAtttackMax(double attackMax)
{
    m_attackMax = attackMax;
}

double GameCharacter::getAttackMin()
{
    return m_attackMin;
}

void GameCharacter::setAtttackMin(double attackMin)
{
    m_attackMin = attackMin;
}

double GameCharacter::getDefense()
{
    return m_defense;
}

void GameCharacter::setDefense(double defense)
{
    m_defense = defense;
}

double GameCharacter::getPhysicalAttackMax()
{
    return m_physicalAttackMax;
}

double GameCharacter::getPhysicalAttackMin()
{
    return m_physicalAttackMin;
}

double GameCharacter::getMagicAttackMax()
{
    return m_magicAttackMax;
}

double GameCharacter::getMagicAttackMin()
{
    return m_magicAttackMin;
}

double GameCharacter::getPhysicalDefense()
{
    return m_physicalDefense;
}

double GameCharacter::getMagicDefense()
{
    return m_magicDefense;
}
