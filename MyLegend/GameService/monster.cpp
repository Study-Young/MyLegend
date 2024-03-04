#include "monster.h"
#include "ui_monster.h"

Monster::Monster(MONSTERCHARACTER *info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Monster)
{
    ui->setupUi(this);

    monsterInfoInit(info);
}

Monster::~Monster()
{
    delete ui;
}

void Monster::monsterInfoInit(MONSTERCHARACTER *info)
{
    m_info = *info;
    ui->label_type->setText(m_monsterType[m_info.type - 1]);
    ui->label_name->setText(m_info.name);

    setName(m_info.name);
    setLevel(m_info.level);
    setAtttackMin(m_info.attackMin);
    setAtttackMax(m_info.attackMax);
    setDefense(m_info.defense);
    setHitPoint(m_info.hp);

    this->setStyleSheet(QString("QWidget#widget_background{background-color: rgba(%1, 50);}")
                                .arg(m_colorList[m_info.type - 1]));
}

void Monster::on_pushButton_attack_clicked()
{
    if(ui->checkBox_autoAttack->isChecked())
    {
        emit attackSignal(true);
    }
    else
    {
        emit attackSignal(false);
    }
}
