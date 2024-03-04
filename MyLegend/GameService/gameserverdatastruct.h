#ifndef GAMESERVERDATASTRUCT_H
#define GAMESERVERDATASTRUCT_H

#include <QtGlobal>

#pragma pack(push)
#pragma pack(1)

enum EQUIPMENTTYPE{
    WEAPON = 0, //武器
    JACKET,     //上衣
    SHOULDER,   //护肩
    CUIRASS,    //胸甲
    WAIST,      //护腰
    TROUSERS,   //裤子
    LEGGUARD,   //护腿
    SHOES,      //鞋
    WRIST,      //护腕
    GLOVES,     //手套
    PENDANT,    //项链
    RING,       //戒指
};

typedef struct EQUIPMENTCHARACTER
{
    QString id;
    int type;
    QString name;    
    int qualityLevel;
    int rebirthLevel;
    int attackMin;
    int attackMax;
    int defense;
    int hp;
    int reinforceLevel;
    int starLevel;

    EQUIPMENTCHARACTER(){
        id = "-";
        type = 0;
        name = "-";
        qualityLevel = 0;
        rebirthLevel = 0;
        attackMin = 0;
        attackMax = 0;
        defense = 0;
        hp = 0;
        reinforceLevel = 0;
        starLevel = 0;
    }

    EQUIPMENTCHARACTER(QString _id, int _type, QString _name, int _qualityLevel, int _rebirthLevel, int _attackMin, int _attackMax,
                       int _defense, int _hp, int _reinforceLevel, int _starLevel){
        id = _id;
        type = _type;
        name = _name;
        qualityLevel = _qualityLevel;
        rebirthLevel = _rebirthLevel;
        attackMin = _attackMin;
        attackMax = _attackMax;
        defense = _defense;
        hp = _hp;       
        reinforceLevel = _reinforceLevel;
        starLevel = _starLevel;
    }
}EQUIPMENTCHARACTER;

typedef struct ROLEEQUIPMENT
{
    EQUIPMENTCHARACTER *weapon;
    EQUIPMENTCHARACTER *jacket;
    EQUIPMENTCHARACTER *shoulder;
    EQUIPMENTCHARACTER *cuirass;
    EQUIPMENTCHARACTER *waist;
    EQUIPMENTCHARACTER *trousers;
    EQUIPMENTCHARACTER *legguard;
    EQUIPMENTCHARACTER *shoes;
    EQUIPMENTCHARACTER *wrist;
    EQUIPMENTCHARACTER *gloves;
    EQUIPMENTCHARACTER *pendant;
    EQUIPMENTCHARACTER *ring;
    QList<EQUIPMENTCHARACTER *> equipmentList;
}ROLEEQUIPMENT;

typedef struct MONSTERCHARACTER
{
    QString id;
    int type;
    QString name;
    int level;
    int attackMin;
    int attackMax;
    int defense;
    int hp;

    MONSTERCHARACTER(){
        id = "-";
        type = 0;
        name = "-";
        level = 0;
        attackMin = 0;
        attackMax = 0;
        defense = 0;
        hp = 0;
    }

    MONSTERCHARACTER(QString _id, int _type, QString _name, int _level,
                     double _attackMin, double _attackMax, double _defense, double _hp){
        id = _id;
        type = _type;
        name = _name;
        level = _level,
        attackMin = _attackMin;
        attackMax = _attackMax;
        defense = _defense;
        hp = _hp;
    }
}MONSTERCHARACTER;

typedef struct LEVELMONSTER
{
    MONSTERCHARACTER *exp;
    MONSTERCHARACTER *rune;
    MONSTERCHARACTER *dragonBorn;
    MONSTERCHARACTER *monsterSoul;

    QList<MONSTERCHARACTER *> monsterList;
}LEVELMONSTER;

#pragma pack()

#endif // GAMESERVERDATASTRUCT_H
