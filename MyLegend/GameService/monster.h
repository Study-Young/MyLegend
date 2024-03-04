#ifndef MONSTER_H
#define MONSTER_H

#include <QWidget>

#include "gamecharacter.h"
#include "gameserverdatastruct.h"

namespace Ui {
class Monster;
}

class Monster : public QWidget, public GameCharacter
{
    Q_OBJECT
public:
    explicit Monster(MONSTERCHARACTER *info, QWidget *parent = nullptr);
    ~Monster();

signals:
    void attackSignal(bool autoFlag);

private slots:
    void on_pushButton_attack_clicked();

private:
    void monsterInfoInit(MONSTERCHARACTER *info);

private:
    Ui::Monster *ui;

    MONSTERCHARACTER m_info;
    QStringList m_monsterType = {"等级", "符文", "龙裔", "兽魂"};
    QStringList m_colorList = {"255,255,0", "255,0,0", "0,255,0", "0,0,255"};
};

#endif // MONSTER_H
