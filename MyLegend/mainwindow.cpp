#include "mainwindow.h"
#include "ui_mainwindow.h"

#define SOFTVERSION "V0.0.3"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mainInit();
    connectSignalSlot();

    setWindowTitle(QString("传奇 %1").arg(SOFTVERSION));

    m_realTimerId = startTimer(1000);
}

MainWindow::~MainWindow()
{
    delete ui;

    delete m_dataBase;
    delete m_userManagement;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    switch(QMessageBox::information(NULL, "提示", "确认退出游戏？",
                                    QMessageBox::Yes | QMessageBox::Default,
                                    QMessageBox::No | QMessageBox::Escape))
    {
        case QMessageBox::Yes:
        {
            GameServiceGlobal::getInstance()->stopAttack();
            event->accept();
            break;
        }
        case QMessageBox::No:
        {
            event->ignore();
            break;
        }
    }
}

void MainWindow::timerEvent(QTimerEvent *event)
{
    if(event->timerId() == m_realTimerId)
    {
        ui->label_time->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
    }
}

void MainWindow::updateCurrentUserInfo()
{
    updateMsg(__FILE__, __FUNCTION__, MESSAGE_OPERATOR, QString("当前用户:%1").arg(g_userName));
}

void MainWindow::mainInit()
{
    memberValueInit();
    uiInit();
}

void MainWindow::connectSignalSlot()
{
    connect(GameServiceGlobal::getInstance(), &GameServiceGlobal::updateAttackInfoSignal, this, &MainWindow::updateAttackInfoSlot);
    connect(GameServiceGlobal::getInstance(), &GameServiceGlobal::updateAttackResultSignal, this, &MainWindow::updateAttackResultSlot);
}

void MainWindow::memberValueInit()
{
    styleSheetInit();

    signalSlotInit();

    databaseInit();
    buttonInit();
    tableInit();
    userManagementInit();

}

void MainWindow::uiInit()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::signalSlotInit()
{
    qRegisterMetaType<EN_MessageType>("EN_MessageType");
    qRegisterMetaType<QList<QString>>("QList<QString>");
    qRegisterMetaType<QList<int>>("QList<int>");
    qRegisterMetaType<CREATEROLE>("CREATEROLE");
    qRegisterMetaType<EQUIPMENTCHARACTER>("EQUIPMENTCHARACTER");
}

void MainWindow::buttonInit()
{
    m_homeBtnList.append(ui->pushButton_character);
    m_homeBtnList.append(ui->pushButton_equipment);
    m_homeBtnList.append(ui->pushButton_rune);
    m_homeBtnList.append(ui->pushButton_dragonBorn);
    m_homeBtnList.append(ui->pushButton_monsterSoul);
    m_homeBtnList.append(ui->pushButton_bag);
    m_homeBtnList.append(ui->pushButton_fieldHook);
    m_homeBtnList.append(ui->pushButton_bossHome);

    connect(ui->pushButton_character, &QPushButton::clicked, this, &MainWindow::homeBtnListClicked);
    connect(ui->pushButton_equipment, &QPushButton::clicked, this, &MainWindow::homeBtnListClicked);
    connect(ui->pushButton_rune, &QPushButton::clicked, this, &MainWindow::homeBtnListClicked);
    connect(ui->pushButton_dragonBorn, &QPushButton::clicked, this, &MainWindow::homeBtnListClicked);
    connect(ui->pushButton_monsterSoul, &QPushButton::clicked, this, &MainWindow::homeBtnListClicked);
    connect(ui->pushButton_bag, &QPushButton::clicked, this, &MainWindow::homeBtnListClicked);
    connect(ui->pushButton_fieldHook, &QPushButton::clicked, this, &MainWindow::homeBtnListClicked);
    connect(ui->pushButton_bossHome, &QPushButton::clicked, this, &MainWindow::homeBtnListClicked);
}

void MainWindow::tableInit()
{
    roleTableInit();
}

void MainWindow::databaseInit()
{
    m_dataBase = new MyDataBase();

    connect(this, &MainWindow::databaseInitSignal, m_dataBase, &DataBase::databaseInitSlot);
    connect(m_dataBase, &DataBase::databaseInitCompleteSignal, this, &MainWindow::databaseInitCompleteSlot);
    connect(m_dataBase, &DataBase::updateMsgSignal, this, &MainWindow::updateMsg);

    connect(this, &MainWindow::initRoleInfoTableSignal, m_dataBase, &MyDataBase::initRoleInfoTableSlot);
    connect(m_dataBase, &MyDataBase::updateRoleInfoTableSignal, this, &MainWindow::updateRoleInfoTableSlot);
    connect(this, &MainWindow::createRoleSignal, m_dataBase, &MyDataBase::createRoleSlot);
    connect(m_dataBase, &MyDataBase::createRoleCompleteSignal, this, &MainWindow::createRoleCompleteSlot);

    connect(this, &MainWindow::selectRoleSignal, m_dataBase, &MyDataBase::selectRoleSlot);

    connect(this, &MainWindow::initRoleEquipmentInfoSignal, m_dataBase, &MyDataBase::initRoleEquipmentInfoSlot);
    connect(this, &MainWindow::initLevelMonsterInfoSignal, m_dataBase, &MyDataBase::initLevelMonsterInfoSlot);

    connect(this, &MainWindow::updateRoleInfoSignal, m_dataBase, &MyDataBase::updateRoleInfoSlot);

    emit databaseInitSignal();
}

void MainWindow::databaseInitCompleteSlot(bool sta)
{
    if(sta)
        ui->label_databaseSta->setProperty("status", "online");
    else
        ui->label_databaseSta->setProperty("status", "error");
    updateStyleSheet();
}

void MainWindow::userManagementInit()
{
    m_userManagement = UserManagement::getInstance();

    connect(m_userManagement, &UserManagement::checkUserNamePasswordSignal, m_dataBase, &MyDataBase::checkUserNamePasswordSlot);
    connect(m_dataBase, &MyDataBase::checkUserNamePasswordCompleteSignal, m_userManagement, &UserManagement::checkUserNamePasswordCompleteSlot);
    connect(m_userManagement, &UserManagement::modifyPasswordSignal, m_dataBase, &MyDataBase::modifyPasswordSlot);
    connect(m_dataBase, &MyDataBase::modifyPasswordCompleteSignal, m_userManagement, &UserManagement::modifyPasswordCompleteSlot);
    connect(m_userManagement, &UserManagement::addNewUserSignal, m_dataBase, &MyDataBase::addNewUserSlot);
    connect(m_dataBase, &MyDataBase::addNewUserCompleteSignal, m_userManagement, &UserManagement::addNewUserCompleteSlot);
}

void MainWindow::styleSheetInit()
{
    QFile file(":/Legend.qss");
    if (file.open(QIODevice::ReadOnly))
    {
        m_qssByteArray = file.readAll();
        updateStyleSheet();
    }
    else
    {
        qDebug()<<file.errorString();
    }
}

void MainWindow::updateStyleSheet()
{
    this->setStyleSheet(m_qssByteArray);
}

void MainWindow::roleTableInit()
{
    m_roleInfoTableModel = new RoleInfoTableModel();
    ui->tableView_selectRole_roleInfo->setModel(m_roleInfoTableModel);

    ui->tableView_selectRole_roleInfo->verticalHeader()->setVisible(false);
    ui->tableView_selectRole_roleInfo->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);
    ui->tableView_selectRole_roleInfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_selectRole_roleInfo->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Fixed);
    ui->tableView_selectRole_roleInfo->setColumnWidth(0, 50);
    ui->tableView_selectRole_roleInfo->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Fixed);
    ui->tableView_selectRole_roleInfo->setColumnWidth(1, 150);
    ui->tableView_selectRole_roleInfo->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Fixed);
    ui->tableView_selectRole_roleInfo->setColumnWidth(2, 70);
    ui->tableView_selectRole_roleInfo->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Fixed);
    ui->tableView_selectRole_roleInfo->setColumnWidth(3, 70);
    ui->tableView_selectRole_roleInfo->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    ui->tableView_selectRole_roleInfo->setColumnWidth(4, 70);
    ui->tableView_selectRole_roleInfo->horizontalHeader()->setSectionResizeMode(5, QHeaderView::Fixed);
    ui->tableView_selectRole_roleInfo->setColumnWidth(5, 70);
    ui->tableView_selectRole_roleInfo->horizontalHeader()->setSectionResizeMode(6, QHeaderView::Fixed);
    ui->tableView_selectRole_roleInfo->setColumnWidth(6, 100);
    ui->tableView_selectRole_roleInfo->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_selectRole_roleInfo->setSelectionMode(QAbstractItemView::SingleSelection);

    emit initRoleInfoTableSignal();
}

void MainWindow::updateRoleInfoTableSlot(QList<QString> nameList, QList<int> occupationList, QList<int> sexList,
                                         QList<int> levelList, QList<int> rebirthLevelList, QList<int> curExpList,
                                         QList<QString> lastEnterList)
{
    m_roleInfoList.clear();
    for(int i=0; i<nameList.size(); i++)
    {
        ROLEINFODATA roleInfo;
        roleInfo.seq = m_roleInfoList.size() + 1;
        roleInfo.name = nameList.at(i);
        roleInfo.occupation = GameServiceGlobal::getRoleOccupation(occupationList.at(i));
        roleInfo.sex = GameServiceGlobal::getRoleSex(sexList.at(i));
        roleInfo.level = levelList.at(i);
        roleInfo.rebirthLevel = rebirthLevelList.at(i);
        roleInfo.exp = QString("%1/%2").arg(curExpList.at(i)).arg(levelList.at(i)*1000);
        roleInfo.lastEnterTime = lastEnterList.at(i);
        m_roleInfoList.append(roleInfo);
    }
    m_roleInfoTableModel->updateModelData(m_roleInfoList);
}

void MainWindow::updateMsg(const QString& fileName, const QString& functionName, EN_MessageType msgType, const QString& msg)
{
    qDebug()<<fileName<<functionName<<msgType<<msg;
}

void MainWindow::on_pushButton_selectRole_enterGame_clicked()
{
    int selectRow = ui->tableView_selectRole_roleInfo->currentIndex().row();

    roleInfoInit(selectRow);
    equipmentInfoInit();
    updateHomePageRoleInfo();
    bossHomeInit();

    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::roleInfoInit(int idx)
{
    QEventLoop loop;
    connect(m_dataBase, &MyDataBase::selectRoleCompleteSignal, &loop, &QEventLoop::quit);

    m_curRole = new Role();
    m_curRole->setName(m_roleInfoTableModel->index(idx, 1).data().toString());
    m_curRole->setLevel(m_roleInfoTableModel->index(idx, 4).data().toInt());
    m_curRole->setOccupation(GameServiceGlobal::getRoleOccupation(m_roleInfoTableModel->index(idx, 2).data().toString()));
    m_curRole->setSex(GameServiceGlobal::getRoleSex(m_roleInfoTableModel->index(idx, 3).data().toString()));
    m_curRole->setRebirthLevel(m_roleInfoTableModel->index(idx, 5).data().toInt());
    m_curRole->setCurExp(m_roleInfoTableModel->index(idx, 6).data().toString().split('/').at(0).toInt());
    emit selectRoleSignal(m_curRole);
    loop.exec();
}

void MainWindow::equipmentInfoInit()
{
    m_roleEquipment = new ROLEEQUIPMENT;

    QEventLoop loop;
    connect(m_dataBase, &MyDataBase::initRoleEquipmentInfoCompleteSignal, &loop, &QEventLoop::quit);
    emit initRoleEquipmentInfoSignal(m_roleEquipment);
    loop.exec();
}

void MainWindow::updateHomePageRoleInfo()
{
    if(m_curRole->getStaFlag())
    {
        ui->label_home_name->setText(m_curRole->getName());
        ui->label_home_occupation->setText(GameServiceGlobal::getRoleOccupation(m_curRole->getOccupation()));
        ui->label_home_sex->setText(GameServiceGlobal::getRoleSex(m_curRole->getSex()));
        ui->label_home_level->setText(QString::number(m_curRole->getLevel()));
        ui->label_home_level_rebirth->setText(QString::number(m_curRole->getRebirthLevel()));
        ui->label_home_cp->setText(QString("-"));
        ui->label_home_exp_cur->setText(QString::number(m_curRole->getCurExp()));
        ui->label_home_exp_max->setText(QString("/%1").arg(m_curRole->getLevel()*1000));

        int attackMin = m_curRole->getAttackMin();
        int attackMax = m_curRole->getAttackMax();
        int defense = m_curRole->getDefense();
        int hp = m_curRole->getHitPoint();

        for(int i=0; i<m_roleEquipment->equipmentList.size(); i++)
        {
            Equipment *pEquipment = new Equipment(m_roleEquipment->equipmentList[i]);
            ui->verticalLayout_equipment->insertWidget(i, pEquipment);
            attackMin += m_roleEquipment->equipmentList[i]->attackMin;
            attackMax += m_roleEquipment->equipmentList[i]->attackMax;
            defense += m_roleEquipment->equipmentList[i]->defense;
            hp += m_roleEquipment->equipmentList[i]->hp;
        }

        ui->label_home_hp->setText(QString::number(hp));
        ui->label_home_attackMin->setText(QString::number(attackMin));
        ui->label_home_attackMax->setText(QString::number(attackMax));
        ui->label_home_defense->setText(QString::number(defense));

        m_curRole->setAtttackMin(attackMin);
        m_curRole->setAtttackMax(attackMax);
        m_curRole->setDefense(defense);
        m_curRole->setHitPoint(hp);
    }
    else
        qDebug()<<__FILE__<<__FUNCTION__<<"读取角色信息错误!";

}

void MainWindow::bossHomeInit()
{
    for(int i=0; i<=m_curRole->getRebirthLevel()+1; i++)
    {
        QPushButton *pBtn = new QPushButton(QString("%1阶").arg(i));
        connect(pBtn, &QPushButton::clicked, this, &MainWindow::monsterLevelBtnListClicked);

        m_monsterLevelBtnList.append(pBtn);
        ui->verticalLayout_monsterLevel->insertWidget(i, pBtn);
    }

    m_monsterLevelBtnList.at(m_curRole->getRebirthLevel())->click();
}

void MainWindow::monsterLevelBtnListClicked()
{
    QString levelStr = ((QPushButton *)sender())->text();
    int monsterLevel= levelStr.remove(levelStr.size()-1,1).toInt();
    monsterInfoInit(monsterLevel);
    updateBossHomePageMonsterInfo();
}

void MainWindow::monsterInfoInit(int level)
{
    if(m_levelMonster)
    {
        delete m_levelMonster->exp;
        delete m_levelMonster->rune;
        delete m_levelMonster->dragonBorn;
        delete m_levelMonster->monsterSoul;
        m_levelMonster->monsterList.clear();
        m_levelMonster = nullptr;
    }

    if(m_monsterList.size() != 0)
    {
        for(int i=0; i<m_monsterList.size(); i++)
        {
            Monster *pMonster = m_monsterList[i];
            delete pMonster;
        }
        m_monsterList.clear();
    }

    m_levelMonster = new LEVELMONSTER;

    QEventLoop loop;
    connect(m_dataBase, &MyDataBase::initLevelMonsterInfoCompleteSignal, &loop, &QEventLoop::quit);
    emit initLevelMonsterInfoSignal(m_levelMonster, level);
    loop.exec();
}

void MainWindow::updateBossHomePageMonsterInfo()
{
    for(int i=0; i<m_levelMonster->monsterList.size(); i++)
    {
        Monster *pMonster = new Monster(m_levelMonster->monsterList[i]);
        m_monsterList.append(pMonster);
        connect(pMonster, &Monster::attackSignal, this, &MainWindow::attackSlot);
        ui->verticalLayout_monsterInfo->insertWidget(i, pMonster);
    }
}

void MainWindow::attackSlot(bool autoFlag)
{
    m_autoAttackFlag = autoFlag;
    m_curMonster = (Monster *)sender();
    if(m_curRole->getRebirthLevel() < m_curMonster->getLevel())
    {
        QMessageBox::warning(this, "错误", "当前转生等级小于怪物等级,无法攻击!");
        return;
    }

    ui->label_role_name->setText(m_curRole->getName());
    ui->label_monster_name->setText(m_curMonster->getName());

    ui->stackedWidget->setCurrentIndex(3);

    m_attackCnt = 0;
    if(m_autoAttackFlag)
    {
        while(m_autoAttackFlag)
        {
            GameServiceGlobal::getInstance()->attack(m_curRole, m_curMonster);
        }
    }
    else
    {
        GameServiceGlobal::getInstance()->attack(m_curRole, m_curMonster);
    }
}

void MainWindow::on_pushButton_selectRole_createRole_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_selectRole_exitGame_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_createRole_create_clicked()
{
    m_role.name = ui->lineEdit_createRole_name->text();

    if(ui->radioButton_createRole_z->isChecked())
        m_role.occupation = Occupation_ZHANSHI;
    else if(ui->radioButton_createRole_f->isChecked())
        m_role.occupation = Occupation_FASHI;
    else if(ui->radioButton_createRole_d->isChecked())
        m_role.occupation = Occupation_DAOSHI;

    if(ui->radioButton_createRole_man->isChecked())
        m_role.sex = Sex_Man;
    else if(ui->radioButton_createRole_woman->isChecked())
        m_role.sex = Sex_Woman;

    emit createRoleSignal(m_role);
}

void MainWindow::createRoleCompleteSlot(int sta)
{
    if(sta == 1)
    {
        QMessageBox::information(this, "成功", "创建角色成功!");
        ui->stackedWidget->setCurrentIndex(0);

        m_roleInfoList = m_roleInfoTableModel->getModelData();
        ROLEINFODATA roleInfo;
        roleInfo.seq = m_roleInfoList.size() + 1;
        roleInfo.name = m_role.name;
        roleInfo.occupation = GameServiceGlobal::getRoleOccupation(m_role.occupation);
        roleInfo.sex = GameServiceGlobal::getRoleSex(m_role.sex);
        roleInfo.level = 1;
        roleInfo.lastEnterTime = "";
        m_roleInfoList.append(roleInfo);
        m_roleInfoTableModel->updateModelData(m_roleInfoList);
    }
    else if(sta == 0)
    {
        QMessageBox::information(this, "失败", "角色名重复!");
    }
    else
    {
        QMessageBox::warning(this, "失败", "创建角色失败!");
    }
}

void MainWindow::on_pushButton_createRole_return_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::homeBtnListClicked()
{
    QPushButton *pBtn = dynamic_cast<QPushButton*>(sender());
    for(int i=0; i<m_homeBtnList.size(); i++)
    {
        auto pFunctionBtn = m_homeBtnList.at(i);
        if(pFunctionBtn == pBtn)
        {
            pFunctionBtn->setProperty("status", "selected");
            ui->stackedWidget_home->setCurrentIndex(i);
            updateMsg(__FILE__, __FUNCTION__, MESSAGE_OPERATOR, QString("点击按钮:%1;").arg(pFunctionBtn->text()));
        }
        else
        {
            pFunctionBtn->setProperty("status", "unselected");
        }
    }
    updateStyleSheet();
}

void MainWindow::updateAttackInfoSlot(double roleHp, double monsterHp)
{
    ui->label_role_hp->setText(QString::number(roleHp));
    ui->label_monster_hp->setText(QString::number(monsterHp));
}

void MainWindow::updateAttackResultSlot(int rlt)
{
    QString rltStr;
    if(rlt == 0)
    {
        rltStr = "退出战斗";
    }
    else if(rlt == 1)
    {
        rltStr = "战斗胜利";
        updateAttackResultInfo();
    }
    else if(rlt == 2)
    {
        rltStr = "战斗失败";
    }

    if(!m_autoAttackFlag)
    {
        QMessageBox::information(this, "结果", rltStr);
        ui->stackedWidget->setCurrentIndex(2);
        emit updateRoleInfoSignal(m_curRole);
    }
    else
    {
        QString infoStr = QString("%1: 当前第%2次战斗，%3")
                                  .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"))
                                  .arg(++m_attackCnt)
                                  .arg(rltStr);
        ui->textBrowser_attackInfo->append(infoStr);
    }
}

void MainWindow::on_pushButton_speedUp_clicked()
{
    if(ui->label_speed->text() == "x1")
    {
        ui->label_speed->setText("x2");
        GameServiceGlobal::getInstance()->setAttackFrequency(0.05);
    }
    else if(ui->label_speed->text() == "x2")
    {
        ui->label_speed->setText("x5");
        GameServiceGlobal::getInstance()->setAttackFrequency(0.02);
    }
    else if(ui->label_speed->text() == "x5")
    {
        ui->label_speed->setText("x10");
        GameServiceGlobal::getInstance()->setAttackFrequency(0.01);
    }
    else if(ui->label_speed->text() == "x10")
    {
        ui->label_speed->setText("x100");
        GameServiceGlobal::getInstance()->setAttackFrequency(0.001);
    }
    else if(ui->label_speed->text() == "x100")
    {
        ui->label_speed->setText("x1");
        GameServiceGlobal::getInstance()->setAttackFrequency(0.1);
    }
}

void MainWindow::updateAttackResultInfo()
{
    if(m_curRole->getRebirthLevel() == m_curMonster->getLevel())
    {
        int curMaxExp = m_curRole->getLevel()*1000;
        int curExp = m_curRole->getCurExp() + curMaxExp*0.02;
        if(curExp > curMaxExp)
        {
            curExp -= curMaxExp;

            m_curRole->setLevel(m_curRole->getLevel() + 1);
            ui->label_home_level->setText(QString::number(m_curRole->getLevel()));

            m_curRole->setAtttackMax(m_curRole->getAttackMax() * 2);
            ui->label_home_attackMax->setText(QString::number(m_curRole->getAttackMax()));

            m_curRole->setAtttackMin(m_curRole->getAttackMin() * 2);
            ui->label_home_attackMin->setText(QString::number(m_curRole->getAttackMin()));

            m_curRole->setDefense(m_curRole->getDefense() * 2);
            ui->label_home_defense->setText(QString::number(m_curRole->getDefense()));

            m_curRole->setHitPoint(m_curRole->getHitPoint() * 2);
            ui->label_home_hp->setText(QString::number(m_curRole->getHitPoint()));
        }

        m_curRole->setCurExp(curExp);
        ui->label_home_exp_cur->setText(QString::number(m_curRole->getCurExp()));
    }
}

void MainWindow::on_pushButton_stop_clicked()
{
    m_autoAttackFlag = false;
}
