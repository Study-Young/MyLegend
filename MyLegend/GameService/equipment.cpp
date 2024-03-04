#include "equipment.h"
#include "ui_equipment.h"

Equipment::Equipment(EQUIPMENTCHARACTER *info, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Equipment)
{
    ui->setupUi(this);

    equipmentInfoInit(info);
}

Equipment::~Equipment()
{
    delete ui;
}

void Equipment::equipmentInfoInit(EQUIPMENTCHARACTER *info)
{
    m_info = *info;

    ui->label_type->setText(m_equipmentName[m_info.type-1]);

    ui->label_name->setText(m_info.name);
    ui->label_attack->setText(QString("%1-%2").arg(m_info.attackMin).arg(m_info.attackMax));
    ui->label_defense->setText(QString::number(m_info.defense));
    ui->label_hp->setText(QString::number(m_info.hp));
    ui->label_rebirth->setText(QString("%1转").arg(m_info.rebirthLevel));

    ui->label_enhanceCnt->setText(QString("+%1").arg(m_info.reinforceLevel));
    ui->label_attack_enhance->setText(QString("%1-%2")
                                      .arg(m_info.attackMin/100*m_info.reinforceLevel)
                                      .arg(m_info.attackMax/100*m_info.reinforceLevel));
    ui->label_defense_enhance->setText(QString::number(m_info.defense/100*m_info.reinforceLevel));
    ui->label_hp_enhance->setText(QString::number(m_info.hp/100*m_info.reinforceLevel));

    ui->label_starLevel->setText(QString("%1星").arg(m_info.starLevel));
    ui->label_attack_star->setText(QString("%1-%2")
                                      .arg(m_info.attackMin/50*m_info.starLevel)
                                      .arg(m_info.attackMax/50*m_info.starLevel));
    ui->label_defense_star->setText(QString::number(m_info.defense/50*m_info.starLevel));
    ui->label_hp_star->setText(QString::number(m_info.hp/50*m_info.starLevel));

    this->setStyleSheet(QString("QWidget#widget_background{background-color: rgba(%1, 50);}")
                                .arg(m_colorList[info->qualityLevel-1]));
}
