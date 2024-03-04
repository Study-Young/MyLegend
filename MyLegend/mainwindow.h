#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QInputDialog>
#include <QCloseEvent>
#include <QFile>


#include "DataBase/database.h"
#include "DataBase/mydatabase.h"
#include "UserManagement/usermanagement.h"
#include "Model/roleinfotablemodel.h"
#include "GameService/gameserviceglobal.h"
#include "GameService/gameserverdatastruct.h"
#include "GameService/role.h"
#include "GameService/equipment.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void closeEvent(QCloseEvent *event);
    void timerEvent(QTimerEvent *event);
    void updateCurrentUserInfo();

signals:
    void databaseInitSignal();

    void initRoleInfoTableSignal();
    void createRoleSignal(CREATEROLE role);
    void selectRoleSignal(Role *role);

    void initRoleEquipmentInfoSignal(ROLEEQUIPMENT *roleEquipment);
    void initLevelMonsterInfoSignal(LEVELMONSTER *levelMonster, int level);

    void updateRoleInfoSignal(Role *role);

public slots:
    void updateMsg(const QString &fileName, const QString &functionName, EN_MessageType msgType, const QString &msg);

    void databaseInitCompleteSlot(bool sta);

    void updateRoleInfoTableSlot(QList<QString> nameList, QList<int> occupationList, QList<int> sexList,
                                 QList<int> levelList, QList<int> rebirthLevelList, QList<int> curExpList,
                                 QList<QString> lastEnterList);
    void createRoleCompleteSlot(int sta);

    void updateAttackInfoSlot(double roleHp, double monsterHp);
    void updateAttackResultSlot(int rlt);
    void attackSlot(bool autoFlag);

private slots:
    void on_pushButton_selectRole_enterGame_clicked();
    void on_pushButton_selectRole_createRole_clicked();
    void on_pushButton_selectRole_exitGame_clicked();
    void on_pushButton_createRole_create_clicked();
    void on_pushButton_createRole_return_clicked();

    void homeBtnListClicked();
    void monsterLevelBtnListClicked();

    void on_pushButton_speedUp_clicked();
    void on_pushButton_stop_clicked();

private:
    void mainInit();
    void connectSignalSlot();
    void memberValueInit();
    void uiInit();

    void styleSheetInit();
    void updateStyleSheet();

    void signalSlotInit();
    void buttonInit();
    void tableInit();
    void databaseInit();
    void userManagementInit();

    void roleTableInit();

    void roleInfoInit(int idx);
    void equipmentInfoInit();
    void updateHomePageRoleInfo();
    void bossHomeInit();
    void monsterInfoInit(int level);
    void updateBossHomePageMonsterInfo();

    void updateAttackResultInfo();

private:
    Ui::MainWindow *ui;
    QByteArray m_qssByteArray;
    int m_realTimerId;

    MyDataBase *m_dataBase;
    UserManagement *m_userManagement;

    QList<QPushButton *> m_homeBtnList;

    RoleInfoTableModel *m_roleInfoTableModel;
    QList<ROLEINFODATA> m_roleInfoList;
    CREATEROLE m_role;

    Role *m_curRole;
    ROLEEQUIPMENT *m_roleEquipment = nullptr;
    LEVELMONSTER *m_levelMonster = nullptr;
    Monster *m_curMonster;
    QList<Monster *> m_monsterList;

    QList<QPushButton *> m_monsterLevelBtnList;

    bool m_autoAttackFlag;
    int m_attackCnt;
};
#endif // MAINWINDOW_H
