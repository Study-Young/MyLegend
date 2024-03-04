#include "gameserviceglobal.h"
#include <QDebug>

GameServiceGlobal::GameServiceGlobal(QObject *parent)
    :QObject(parent)
{
    mainInit();
}

GameServiceGlobal::~GameServiceGlobal()
{

}

GameServiceGlobal *GameServiceGlobal::m_pInstance = nullptr;
GameServiceGlobal *GameServiceGlobal::getInstance()
{
    if(m_pInstance == nullptr)
    {
        m_pInstance = new GameServiceGlobal();
    }
    return m_pInstance;
}

void GameServiceGlobal::mainInit()
{
    memberValueInit();
}

void GameServiceGlobal::memberValueInit()
{
    m_stopAttack = false;
    m_attackFrequency = 0.1;
}

QString GameServiceGlobal::getRoleOccupation(int occupation)
{
    if(occupation == Occupation_ZHANSHI)
        return QString("战士");
    else if(occupation == Occupation_FASHI)
        return QString("法师");
    else if(occupation == Occupation_DAOSHI)
        return QString("道士");
}

int GameServiceGlobal::getRoleOccupation(QString occupation)
{
    if(occupation == "战士")
        return Occupation_ZHANSHI;
    else if(occupation == "法师")
        return Occupation_FASHI;
    else if(occupation == "道士")
        return Occupation_DAOSHI;
}

QString GameServiceGlobal::getRoleSex(int sex)
{
    if(sex == Sex_Man)
        return QString("男");
    else if(sex == Sex_Woman)
        return QString("女");
}

int GameServiceGlobal::getRoleSex(QString sex)
{
    if(sex == "男")
        return Sex_Man;
    else if(sex == "女")
        return Sex_Woman;
}

void GameServiceGlobal::setAttackFrequency(double freq)
{
    m_attackFrequency = freq;
}

double GameServiceGlobal::getAttackFrequency()
{
    return m_attackFrequency;
}

void GameServiceGlobal::attack(Role *role, Monster *monster)
{
    double roleHp = role->getHitPoint();
    double roleAttackMax = role->getAttackMax();
    double roleAttackMin = role->getAttackMin();
    double roleDefense = role->getDefense();

    double monsterHp = monster->getHitPoint();
    double monsterAttackMax = monster->getAttackMax();
    double monsterAttackMin = monster->getAttackMin();
    double monsterDefense = monster->getDefense();

    while (!m_stopAttack)
    {
        monsterHp -= getDamage(roleAttackMax, roleAttackMin, monsterDefense);
        if(monsterHp < 0)
        {
            emit updateAttackResultSignal(1);
            return;
        }

        roleHp -= getDamage(monsterAttackMax, monsterAttackMin, roleDefense);
        if(roleHp < 0)
        {
            emit updateAttackResultSignal(2);
            return;
        }

        emit updateAttackInfoSignal(roleHp, monsterHp);
        QEventLoop loop;
        QTimer::singleShot(m_attackFrequency*1000, &loop, &QEventLoop::quit);
        loop.exec();
    }

    if(!m_stopAttack)
        emit updateAttackResultSignal(0);

    m_attackFrequency = 0.1;
}

double GameServiceGlobal::getRandomDivisor(double markup)
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int divisor = qrand()%100 + markup;
    if(divisor > 100)
        divisor = 100;

    return (double)divisor/100.0;
}

double GameServiceGlobal::getDamage(double attackMax, double attackMin, double defense)
{
    double realAttack = attackMin + (attackMax - attackMin) * getRandomDivisor();
    if(realAttack > defense)
    {
        return realAttack - defense;
    }
    else
    {
        return realAttack * (getRandomDivisor() / 10.0);
    }
}

void GameServiceGlobal::stopAttack()
{
    m_stopAttack = true;
}
