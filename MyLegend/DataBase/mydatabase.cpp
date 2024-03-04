#include "mydatabase.h"
#include <QDebug>

MyDataBase::MyDataBase(QObject *parent)
    :DataBase(parent)
{
    connectSignalSlot();
}

MyDataBase::~MyDataBase()
{

}

void MyDataBase::connectSignalSlot()
{
    connect(this, &DataBase::tableInitSignal, this, &MyDataBase::tableInitSlot);
}

void MyDataBase::tableInitSlot()
{
    userTableInit();
    roleTableInit();
    roleCharacterTableInit();
    roleEquipmentTableInit();
    equipmentTableInit();
    monsterTableInit();
}

void MyDataBase::userTableInit()
{
    QString createTableSql;

    if(!isTableExist("UserInfo"))
    {
        createTableSql = "CREATE TABLE UserInfo ("
                         "UserId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                         "Name TEXT NOT NULL,"
                         "Password TEXT NOT NULL,"
                         "CreateTime DATETIME DEFAULT CURRENT_TIMESTAMP)";

        execSql(createTableSql, QString("用户信息表创建"));
    }
}

void MyDataBase::roleTableInit()
{
    QString createTableSql;

    if(!isTableExist("RoleInfo"))
    {
        createTableSql = "CREATE TABLE RoleInfo ("
                         "RoleId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                         "UserId INTEGER NOT NULL,"
                         "Name TEXT NOT NULL,"
                         "Occupation INTEGER NOT NULL,"
                         "Sex INTEGER NOT NULL,"
                         "CreateTime DATETIME DEFAULT CURRENT_TIMESTAMP,"
                         "Level INTEGER DEFAULT 1,"
                         "RebirthLevel INTEGER DEFAULT 0,"
                         "CurrentExp INTEGER DEFAULT 0,"
                         "EnterTime DATETIME,"
                         "FOREIGN KEY (UserId) REFERENCES UserInfo(UserId))";

        execSql(createTableSql, QString("角色信息表创建"));
    }
}

void MyDataBase::roleCharacterTableInit()
{
    QString createTableSql;

    if(!isTableExist("RoleCharacterInfo"))
    {
        createTableSql = "CREATE TABLE RoleCharacterInfo ("
                         "RoleCharacterId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                         "UserId INTEGER NOT NULL,"
                         "RoleId INTEGER NOT NULL,"
                         "HitPoint INTEGER NOT NULL,"
                         "AttackMax INTEGER NOT NULL,"
                         "AttackMin INTEGER NOT NULL,"
                         "Defense INTEGER NOT NULL,"
                         "FOREIGN KEY (UserId) REFERENCES UserInfo(UserId), "
                         "FOREIGN KEY (RoleId) REFERENCES RoleInfo(RoleId))";

        execSql(createTableSql, QString("角色属性表创建"));
    }
}

void MyDataBase::roleEquipmentTableInit()
{
    QString createTableSql;

    if(!isTableExist("RoleEquipmentInfo"))
    {
        createTableSql = "CREATE TABLE RoleEquipmentInfo ("
                         "RoleEquipmentId INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,"
                         "UserId INTEGER NOT NULL,"
                         "RoleId INTEGER NOT NULL,"
                         "WeaponId TEXT NOT NULL,"
                         "JacketId TEXT NOT NULL,"
                         "ShoulderId TEXT NOT NULL,"
                         "CuirassId TEXT NOT NULL,"
                         "WaistId TEXT NOT NULL,"
                         "TrousersId TEXT NOT NULL,"
                         "LegguardId TEXT NOT NULL,"
                         "ShoesId TEXT NOT NULL,"
                         "WristId TEXT NOT NULL,"
                         "GlovesId TEXT NOT NULL,"
                         "PendantId TEXT NOT NULL,"
                         "RingId TEXT NOT NULL,"
                         "FOREIGN KEY (UserId) REFERENCES UserInfo(UserId), "
                         "FOREIGN KEY (RoleId) REFERENCES RoleInfo(RoleId))";

        execSql(createTableSql, QString("角色装备表创建"));
    }
}

void MyDataBase::equipmentTableInit()
{
    QString createTableSql;

    if(!isTableExist("EquipmentInfo"))
    {
        createTableSql = "CREATE TABLE EquipmentInfo ("
                         "EquipmentId TEXT NOT NULL PRIMARY KEY,"
                         "EquipmentType INTEGER NOT NULL,"
                         "EquipmentName TEXT NOT NULL,"
                         "EquipmentQuality INTEGER NOT NULL,"
                         "RebirthLevel INTEGER NOT NULL,"
                         "BasicAttackMin INTEGER NOT NULL,"
                         "BasicAttackMax INTEGER NOT NULL,"
                         "BasicDefense INTEGER NOT NULL,"
                         "BasicHp INTEGER NOT NULL,"
                         "ReinforceLevel INTEGER NOT NULL,"
                         "ReinforceAttackMax INTEGER NOT NULL,"
                         "ReinforceAttackMin INTEGER NOT NULL,"
                         "ReinforceDefense INTEGER NOT NULL,"
                         "ReinforceHp INTEGER NOT NULL,"
                         "StartLevel INTEGER NOT NULL,"
                         "StartAttackMax INTEGER NOT NULL,"
                         "StartAttackMin INTEGER NOT NULL,"
                         "StartDefense INTEGER NOT NULL,"
                         "StartHp INTEGER NOT NULL)";

        execSql(createTableSql, QString("装备属性表创建"));
    }

    QFile file("./equipmentInfo.ini");
    if(file.open(QIODevice::ReadOnly))
    {
        QList<QString> insertEquipmentSqlList;
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QByteArray strArr = QByteArray::fromBase64(in.readLine().toUtf8());
            QString str = QString(strArr);
            QStringList strList = str.split(',');
            QString sqlStr = QString("INSERT INTO EquipmentInfo VALUES(\"%1\", %2, \"%3\", %4,"
                                     "%5, %6, %7, %8, %9, %10, %11, %12, %13, %14,"
                                     "%15, %16, %17, %18, %19)")
                                    .arg(strList.at(0)).arg(strList.at(1)).arg(strList.at(2)).arg(strList.at(3))
                                    .arg(strList.at(4)).arg(strList.at(5)).arg(strList.at(6)).arg(strList.at(7)).arg(strList.at(8))
                                    .arg(strList.at(9)).arg(strList.at(10)).arg(strList.at(11)).arg(strList.at(12)).arg(strList.at(13))
                                    .arg(strList.at(14)).arg(strList.at(15)).arg(strList.at(16)).arg(strList.at(17)).arg(strList.at(18));
            insertEquipmentSqlList.append(sqlStr);
        }
        file.close();

        if(!execSqlList(insertEquipmentSqlList, ""))
            qDebug()<<"插入失败!";
    }
    else
    {
        qDebug()<<"文件打开异常! "<<file.errorString();
    }
}

void MyDataBase::monsterTableInit()
{
    QString createTableSql;

    if(!isTableExist("MonsterInfo"))
    {
        createTableSql = "CREATE TABLE MonsterInfo ("
                         "MonsterId TEXT NOT NULL PRIMARY KEY,"
                         "MonsterType INTEGER NOT NULL,"
                         "MonsterName TEXT NOT NULL,"
                         "MonsterLevel INTEGER NOT NULL,"
                         "MonsterAttackMin INTEGER NOT NULL,"
                         "MonsterAttackMax INTEGER NOT NULL,"
                         "MonsterDefense INTEGER NOT NULL,"
                         "MonsterHp INTEGER NOT NULL)";

        execSql(createTableSql, QString("怪物属性表创建"));
    }

    QFile file("./monsterInfo.ini");
    if(file.open(QIODevice::ReadOnly))
    {
        QList<QString> insertMonsterSqlList;
        QTextStream in(&file);
        while(!in.atEnd())
        {
            QByteArray strArr = QByteArray::fromBase64(in.readLine().toUtf8());
            QString str = QString(strArr);
            QStringList strList = str.split(',');
            QString sqlStr = QString("INSERT INTO MonsterInfo VALUES(\"%1\", %2, \"%3\", %4, %5, %6, %7, %8)")
                                    .arg(strList.at(0)).arg(strList.at(1)).arg(strList.at(2)).arg(strList.at(3))
                                    .arg(strList.at(4)).arg(strList.at(5)).arg(strList.at(6)).arg(strList.at(7));
            insertMonsterSqlList.append(sqlStr);
        }
        file.close();

        if(!execSqlList(insertMonsterSqlList, ""))
            qDebug()<<"插入失败!";
    }
    else
    {
        qDebug()<<"文件打开异常! "<<file.errorString();
    }
}

void MyDataBase::checkUserNamePasswordSlot(QString name, QString password, bool flag)
{
    QString queryPassword = "";
    QSqlQuery query(*m_dataBase);
    QString sqlStr = QString("SELECT UserId, Password FROM UserInfo WHERE Name=\"%1\"").arg(name);
    query.prepare(sqlStr);
    m_checkUserNamePasswordSta = false;

    if(query.exec())
    {
        if(query.next())
        {
            g_userId = query.value(0).toInt();
            queryPassword = query.value(1).toString();

            if(queryPassword == password)
            {
                if(flag)
                {
                    g_userName = name;
                }
                emit checkUserNamePasswordCompleteSignal(1);
                m_checkUserNamePasswordSta = true;
            }
            else
            {
                emit checkUserNamePasswordCompleteSignal(2);
            }
        }
        else
        {
            emit checkUserNamePasswordCompleteSignal(0);
        }
    }
}

void MyDataBase::modifyPasswordSlot(QString name, QString oldPassword, QString newPassword)
{
    checkUserNamePasswordSlot(name, oldPassword, false);
    if(!m_checkUserNamePasswordSta)
        return;

    QString sqlStr = QString("UPDATE UserInfo set Password=\"%1\" WHERE Name=\"%2\"").arg(newPassword).arg(name);
    if(execSql(sqlStr, ""))
        emit modifyPasswordCompleteSignal(true);
    else
        emit modifyPasswordCompleteSignal(false);
}

void MyDataBase::addNewUserSlot(QString name, QString password)
{
    QSqlQuery query(*m_dataBase);

    QString sqlStr;
    sqlStr = QString("SELECT COUNT(*) FROM UserInfo WHERE Name=\"%1\"").arg(name);
    query.prepare(sqlStr);
    if(query.exec())
    {
        if(query.next())
        {
            if(query.value(0).toInt() != 0)
            {
                emit addNewUserCompleteSignal(0);
                return;
            }
        }
    }
    else
    {
        emit addNewUserCompleteSignal(-1);
    }

    sqlStr = QString("INSERT INTO UserInfo (Name, PassWord) VALUES (\"%1\", \"%2\")").arg(name).arg(password);
    if(execSql(sqlStr, ""))
        emit addNewUserCompleteSignal(1);
    else
        emit addNewUserCompleteSignal(-1);
}

void MyDataBase::initRoleInfoTableSlot()
{
    QSqlQuery query(*m_dataBase);

    QList<QString> nameList;
    QList<int> occupationList;
    QList<int> sexList;
    QList<int> levelList;
    QList<int> rebirthLevelList;
    QList<int> curExpList;
    QList<QString> lastEnterList;

    QString sqlStr = QString("SELECT * FROM RoleInfo");
    query.prepare(sqlStr);
    if(query.exec())
    {
        while(query.next())
        {
            nameList.append(query.value(2).toString());
            occupationList.append(query.value(3).toInt());
            sexList.append(query.value(4).toInt());
            levelList.append(query.value(6).toInt());
            rebirthLevelList.append(query.value(7).toInt());
            curExpList.append(query.value(8).toInt());
            lastEnterList.append(query.value(9).toString());
        }
    }
    emit updateRoleInfoTableSignal(nameList, occupationList, sexList, levelList, rebirthLevelList, curExpList, lastEnterList);
}

void MyDataBase::createRoleSlot(CREATEROLE role)
{
    QSqlQuery query(*m_dataBase);

    QString sqlStr;

    sqlStr = QString("SELECT * FROM RoleInfo WHERE Name=\"%1\"").arg(role.name);
    query.prepare(sqlStr);
    if(query.exec())
    {
        if(query.next())
        {
            emit createRoleCompleteSignal(0);
            return;
        }
    }
    int completeSta = 1;

    sqlStr = QString("INSERT INTO RoleInfo (UserId, Name, Occupation, Sex) VALUES (%1, \"%2\", %3, %4)")
                     .arg(g_userId).arg(role.name).arg(role.occupation).arg(role.sex);
    if(!execSql(sqlStr, ""))
        completeSta = -1;

    sqlStr = QString("SELECT RoleId FROM RoleInfo WHERE Name=\"%1\"").arg(role.name);
    query.prepare(sqlStr);
    if(query.exec())
    {
        if(query.next())
        {
            g_roleId = query.value(0).toInt();
        }
    }

    sqlStr = QString("INSERT INTO RoleCharacterInfo (UserId, RoleId, HitPoint, AttackMax, AttackMin, Defense) "
                     "VALUES (%1, %2, %3, %4, %5, %6)")
                     .arg(g_userId).arg(g_roleId).arg(10000).arg(100).arg(50).arg(80);
    if(!execSql(sqlStr, "创建角色"))
        completeSta = -1;

    emit createRoleCompleteSignal(completeSta);
}

void MyDataBase::selectRoleSlot(Role *role)
{
    QString sqlStr;

    QSqlQuery query(*m_dataBase);

    sqlStr = QString("SELECT RoleId FROM RoleInfo WHERE Name=\"%1\"").arg(role->getName());
    query.prepare(sqlStr);
    if(query.exec())
    {
        if(query.next())
        {
            g_roleId = query.value(0).toInt();
        }
    }

    sqlStr = QString("SELECT * FROM RoleCharacterInfo WHERE UserId=%1 AND RoleId=%2").arg(g_userId).arg(g_roleId);
    query.prepare(sqlStr);
    if(query.exec())
    {
        if(query.next())
        {
            role->setHitPoint(query.value(3).toDouble());
            role->setAtttackMax(query.value(4).toDouble());
            role->setAtttackMin(query.value(5).toDouble());
            role->setDefense(query.value(6).toDouble());
            role->setStaFlag(true);
        }
    }
    emit selectRoleCompleteSignal();
}

void MyDataBase::initRoleEquipmentInfoSlot(ROLEEQUIPMENT *roleEquipment)
{
    QString sqlStr;

    sqlStr = QString("UPDATE RoleInfo SET EnterTime=\"%1\" WHERE RoleId=%2 AND UserId=%3")
                    .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")).arg(g_roleId).arg(g_userId);
    if(!execSql(sqlStr, ""))
        qDebug()<<"更新登录时间失败!";

    QList<QString> equipmentIdList;
    QSqlQuery query(*m_dataBase);

    sqlStr = QString("SELECT * FROM RoleEquipmentInfo WHERE UserId=%1 AND RoleId=%2").arg(g_userId).arg(g_roleId);
    query.prepare(sqlStr);
    if(query.exec())
    {
        if(query.next())
        {
            equipmentIdList.append(query.value(3).toString());
            equipmentIdList.append(query.value(4).toString());
            equipmentIdList.append(query.value(5).toString());
            equipmentIdList.append(query.value(6).toString());
            equipmentIdList.append(query.value(7).toString());
            equipmentIdList.append(query.value(8).toString());
            equipmentIdList.append(query.value(9).toString());
            equipmentIdList.append(query.value(10).toString());
            equipmentIdList.append(query.value(11).toString());
            equipmentIdList.append(query.value(12).toString());
            equipmentIdList.append(query.value(13).toString());
            equipmentIdList.append(query.value(14).toString());
        }
    }

    if(equipmentIdList.isEmpty())
    {
        emit initRoleEquipmentInfoCompleteSignal();
        return;
    }

    for(int i=0; i<12; i++)
    {
        sqlStr = QString("SELECT * FROM EquipmentInfo WHERE EquipmentId=\"%1\"").arg(equipmentIdList.at(i));
        query.prepare(sqlStr);
        if(query.exec())
        {
            if(query.next())
            {
                EQUIPMENTCHARACTER *pEquipment = new EQUIPMENTCHARACTER(query.value(0).toString(), query.value(1).toInt(),
                                                                        query.value(2).toString(), query.value(3).toInt(),
                                                                        query.value(4).toInt(), query.value(5).toInt(),
                                                                        query.value(6).toInt(), query.value(7).toInt(),
                                                                        query.value(8).toInt(), query.value(9).toInt(),
                                                                        query.value(14).toInt());
                roleEquipment->equipmentList.append(pEquipment);
            }
        }
    }

    roleEquipment->weapon = roleEquipment->equipmentList[0];
    roleEquipment->jacket = roleEquipment->equipmentList[1];
    roleEquipment->shoulder = roleEquipment->equipmentList[2];
    roleEquipment->cuirass = roleEquipment->equipmentList[3];
    roleEquipment->waist = roleEquipment->equipmentList[4];
    roleEquipment->trousers = roleEquipment->equipmentList[5];
    roleEquipment->legguard = roleEquipment->equipmentList[6];
    roleEquipment->shoes = roleEquipment->equipmentList[7];
    roleEquipment->wrist = roleEquipment->equipmentList[8];
    roleEquipment->gloves = roleEquipment->equipmentList[9];
    roleEquipment->pendant = roleEquipment->equipmentList[10];
    roleEquipment->ring = roleEquipment->equipmentList[11];

    emit initRoleEquipmentInfoCompleteSignal();
}

void MyDataBase::initLevelMonsterInfoSlot(LEVELMONSTER *levelMonster, int level)
{
    QString sqlStr;

    QSqlQuery query(*m_dataBase);

    sqlStr = QString("SELECT * FROM MonsterInfo WHERE MonsterLevel=%1").arg(level);
    query.prepare(sqlStr);
    if(query.exec())
    {
        while(query.next())
        {
            MONSTERCHARACTER *pMonster = new MONSTERCHARACTER(query.value(0).toString(), query.value(1).toInt(),
                                                              query.value(2).toString(), query.value(3).toInt(),
                                                              query.value(4).toInt(), query.value(5).toInt(),
                                                              query.value(6).toInt(), query.value(7).toInt());
            levelMonster->monsterList.append(pMonster);
        }
    }

    levelMonster->exp = levelMonster->monsterList[0];
    levelMonster->rune = levelMonster->monsterList[1];
    levelMonster->dragonBorn = levelMonster->monsterList[2];
    levelMonster->monsterSoul = levelMonster->monsterList[3];

    emit initLevelMonsterInfoCompleteSignal();
}

void MyDataBase::updateRoleInfoSlot(Role *role)
{
    QString sqlStr;
    sqlStr = QString("UPDATE RoleInfo SET Level=%1, RebirthLevel=%2, CurrentExp=%3 WHERE RoleId=%4 AND UserId=%5")
                     .arg(role->getLevel())
                     .arg(role->getRebirthLevel())
                     .arg(role->getCurExp())
                     .arg(g_roleId)
                     .arg(g_userId);
    if(!execSql(sqlStr, ""))
        qDebug()<<"更新角色信息失败";

    sqlStr = QString("UPDATE RoleCharacterInfo SET HitPoint=%1, AttackMax=%2, AttackMin=%3, Defense=%4 WHERE RoleId=%5 AND UserId=%6")
                     .arg(role->getHitPoint())
                     .arg(role->getAttackMax())
                     .arg(role->getAttackMin())
                     .arg(role->getDefense())
                     .arg(g_roleId)
                     .arg(g_userId);

    if(!execSql(sqlStr, ""))
        qDebug()<<"更新角色属性失败";
}
