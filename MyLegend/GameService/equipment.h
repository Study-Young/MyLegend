#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QWidget>

#include "gameserverdatastruct.h"

namespace Ui {
class Equipment;
}

class Equipment : public QWidget
{
    Q_OBJECT

public:
    explicit Equipment(EQUIPMENTCHARACTER *info, QWidget *parent = nullptr);
    ~Equipment();

private:
    void equipmentInfoInit(EQUIPMENTCHARACTER *info);

private:
    Ui::Equipment *ui;

    int m_type;
    EQUIPMENTCHARACTER m_info;

    QStringList m_equipmentName = {"武器", "上衣", "护肩", "胸甲", "护腰", "裤子",
                                   "护腿", "鞋", "护腕", "手套", "项链", "戒指"};
    QStringList m_colorList = {"255,255,255", "255,0,0", "0,255,0", "0,0,255"};
};

#endif // EQUIPMENT_H
