#ifndef GAMESERVICEGLOBAL_H
#define GAMESERVICEGLOBAL_H
#include <QObject>
#include <QtGlobal>
#include <QDateTime>
#include <QTimer>
#include <QEventLoop>

#include "global.h"
#include "role.h"
#include "monster.h"

class GameServiceGlobal : public QObject
{
    Q_OBJECT
public:
    static GameServiceGlobal *getInstance();
    ~GameServiceGlobal();

    static QString getRoleOccupation(int occupation);
    static int getRoleOccupation(QString occupation);
    static QString getRoleSex(int sex);
    static int getRoleSex(QString sex);

    void setAttackFrequency(double freq);
    double getAttackFrequency();

    void attack(Role *role, Monster *monster);
    void stopAttack();

signals:
    void updateAttackInfoSignal(double roleHp, double monsterHp);
    void updateAttackResultSignal(int rlt);

private:
    void mainInit();
    void memberValueInit();

    double getRandomDivisor(double markup=0);
    double getDamage(double attackMax, double attackMin, double defense);

private:
    explicit GameServiceGlobal(QObject *parent = nullptr);
    static GameServiceGlobal* m_pInstance;

    bool m_stopAttack;
    double m_attackFrequency;
};

#endif // GAMESERVICEGLOBAL_H
