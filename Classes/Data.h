#ifndef  _DATA_H_
#define  _DATA_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <vector>

using std::vector;

USING_NS_CC;

#define RIGHT_TOP_DESTINATION ( Vec2(1300, 520) ) // 右上终点坐标
#define VELOCITY_RATE 0.03 // 速度倍率

#define MAGIC_TOWER_CDTIME 1.0 // 魔法塔冷却时间
#define ARROW_TOWER_CDTIME 0.7 // 箭塔冷却时间
#define CANNON_TOWER_CDTIME 1.8 // 加农炮塔冷却时间

#define ARMOUR_TAG 1 // 盔甲兵的标签
#define MAGICBULLET_TAG 11 // 魔法子弹的标签

#define BASEMENT_RANGE 20 // 防御塔基地点击范围的半径
#define ARROW_ICON_RANGE 50 // 防御塔基地锚点到弓箭图标锚点的距离
#define ICON_RANGE 15 // 图标半径

#define NONE_ICON_TAG 100 // 没有点击图标标签
#define ARROW_ICON_TAG 101 // 弓箭塔图标标签
#define CANNON_ICON_TAG 102 // 加农炮塔图标标签
#define MAGIC_ICON_TAG 103 // 魔法塔图标标签


#endif