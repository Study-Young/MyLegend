#ifndef MYDATABASE_H
#define MYDATABASE_H

#include <QDateTime>
#include <QFile>
#include <QTextStream>

#include "database.h"
#include "GameService/gameserverdatastruct.h"
#include "GameService/role.h"
#include "GameService/monster.h"

class MyDataBase : public DataBase
{
    Q_OBJECT
public:
    explicit MyDataBase(QObject *parent = nullptr);
    ~MyDataBase();

signals:
    void checkUserNamePasswordCompleteSignal(int sta);
    void modifyPasswordCompleteSignal(bool flag);
    void addNewUserCompleteSignal(int sta);

    void updateRoleInfoTableSignal(QList<QString> nameList, QList<int> occupationList, QList<int> sexList,
                                   QList<int> levelList, QList<int> rebirthLevelList, QList<int> curExpList,
                                   QList<QString> lastEnterList);
    void createRoleCompleteSignal(int sta);
    void selectRoleCompleteSignal();
    void initRoleEquipmentInfoCompleteSignal();
    void initLevelMonsterInfoCompleteSignal();

public slots:
    void tableInitSlot();

    void checkUserNamePasswordSlot(QString name, QString password, bool flag);
    void modifyPasswordSlot(QString name, QString oldPassword, QString newPassword);
    void addNewUserSlot(QString name, QString password);

    void initRoleInfoTableSlot();
    void createRoleSlot(CREATEROLE role);
    void selectRoleSlot(Role *role);
    void initRoleEquipmentInfoSlot(ROLEEQUIPMENT *roleEquipment);
    void initLevelMonsterInfoSlot(LEVELMONSTER *levelMonster, int level);

    void updateRoleInfoSlot(Role *role);

private:
    void connectSignalSlot();
    void userTableInit();
    void roleTableInit();
    void roleCharacterTableInit();
    void roleEquipmentTableInit();
    void equipmentTableInit();
    void monsterTableInit();


private:
    bool m_checkUserNamePasswordSta;
};

#endif // MYDATABASE_H
