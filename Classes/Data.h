#ifndef  _DATA_H_
#define  _DATA_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <vector>

using std::vector;

USING_NS_CC;

#define RIGHT_TOP_DESTINATION ( Vec2(1300, 520) ) // 右上终点坐标
#define LEFT_TOP_DESTINATION ( Vec2(-10, 480) ) // 左上终点坐标
#define VELOCITY_RATE 0.05 // 速度倍率

#define MAGIC_TOWER_CDTIME 1.0 // 魔法塔冷却时间
#define ARROW_TOWER_CDTIME 0.7 // 箭塔冷却时间
#define CANNON_TOWER_CDTIME 1.8 // 加农炮塔冷却时间

#define ARMOUR_TAG 1 // 盔甲兵的标签
#define MONSTER_TAG 2 // 怪物的标签
#define BOSS_TAG 3 // 头目的标签
#define ENEMY_TAG 10 // 敌军单位标签

#define ARMOUR_VALUE 30 // 击杀盔甲兵获得的金币
#define MONSTER_VALUE 60 // 击杀怪物获得的金币
#define BOSS_VALUE 100 // 击杀头目获得的金币

#define MAGICBULLET_TAG 11 // 魔法子弹的标签
#define ARROWBULLET_TAG 12 // 弓箭导弹的标签
#define CANNONBULLET_TAG 13 // 加农炮导弹的标签
#define BULLET_TAG 30 // 子弹的标签

#define MAGICTOWER_TAG 101 // 魔法塔的标签
#define ARROWTOWER_TAG 102 // 弓箭塔的标签
#define CANNONTOWER_TAG 103 // 加农炮塔的标签

#define BASEMENT_RANGE 20 // 防御塔基地点击范围的半径
#define ARROW_ICON_RANGE 50 // 防御塔基地锚点到弓箭图标锚点的距离
#define ICON_RANGE 15 // 图标半径

#define NONE_ICON_TAG 100 // 没有点击图标标签
#define ARROW_ICON_TAG 101 // 弓箭塔图标标签
#define CANNON_ICON_TAG 102 // 加农炮塔图标标签
#define MAGIC_ICON_TAG 103 // 魔法塔图标标签

#define ARROW_DAMAGE_LEVEL1 80 // 等级1箭塔的伤害值

#define MAGIC_DAMAGE_LEVEL1 200 // 等级1魔法塔的伤害值

#define CANNON_DAMAGE_LEVEL1 400 // 等级1加农炮塔的伤害值

#define PLAYER_INIT_MONEY 100 // 玩家初始金币数量
#define MAGICTOWER_COST 100 // 魔法塔造价
#define ARROWTOWER_COST 50 // 箭塔造价
#define CANNONTOWER_COST 150 // 加农炮塔造价

#define RIGHT_TOP_DIR 1 //  敌军右边方向标识
#define LEFT_TOP_DIR 2 //  敌军左边方向标识

#define WAVECOUNT 15 // 总波次数



// ******************************************

struct SeqNode
{
	int EnemyTag;
	int TimeInterval;
	int EnemyDir;
	SeqNode(int tag, int interval, int enemyDir = RIGHT_TOP_DIR)
	{
		EnemyTag = tag;
		TimeInterval = interval;
		EnemyDir = enemyDir;
	}
};

extern vector<SeqNode> NodeVec;


#endif