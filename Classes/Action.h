#ifndef  _ACTION_H_
#define  _ACTION_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Data.h"
#include "BaseEntity.h"

#include <vector>

using std::vector;

USING_NS_CC;

class MyActionManager
{
public:
	// 单例
	static MyActionManager* getInstance()
	{
		static MyActionManager instance;
		return &instance;
	}

	void MoveToDestination(EnemyBase pEnemy, Vec2 destPos); // 敌人移动路线
	bool IsInside(Vec2 vPos1, Vec2 vPos2, double fDistance); // 判断点击是否在范围内
	void CloseIcon(); // 关闭图标
	void ShowChosenItem(Vec2 vPos, Node* pLayer); // 展示建造防御塔的图标
	int IsClickIcon(Vec2 vPos, Node* pLayer); // 判断是否点击图标

	EnemyBase CreateEnemy(Node* pLayer, int enemyTag = ARMOUR_TAG, int enemyDir = RIGHT_TOP_DIR, int health = 300, Vec2 vPos = Vec2(-10, 255));
	TowerBase CreateArrowTower(Vec2 vPos, Node* pLayer);
	TowerBase CreateCannonTower(Vec2 vPos, Node* pLayer);
	TowerBase CreateMagicTower(Vec2 vPos, Node* pLayer);


private:
	MyActionManager();
	bool isShowChosenItem;
	vector<Node*> ChosenItemVec;
};


#endif