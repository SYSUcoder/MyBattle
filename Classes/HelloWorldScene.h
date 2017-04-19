#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BaseEntity.h"
#include "Action.h"
#include "Data.h"

#include <vector>

using std::vector;

class HelloWorld : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	virtual bool onContactBegin(PhysicsContact& contact);
	// a selector callback
	void menuCloseCallback(cocos2d::Ref* pSender);

	// implement the "static create()" method manually
	CREATE_FUNC(HelloWorld);

	void EnemyMove(float dt); // 敌人行动
	void BulletMove(float dt); // 子弹行动
	void TowerAttack(float dt); // 防御塔进攻

	void RefreshMoney(); // 刷新金币数量

private:
	MyActionManager* actionManager; // 处理相关行为的指针
	vector<EnemyBase> EnemyVec; // 敌人的集合
	vector<BulletBase> BulletVec; // 子弹的集合
	vector<TowerBase> TowerVec; // 防御塔的集合
	vector<BasementBase> BasementVec; // 防御塔基地的集合
	int PlayerMoney; // 玩家的金币数量
	vector<BasementBase>::iterator pLastBasement; // 上一次点击的基地指针
	Label* MoneyLabel; // 测试文本
	int WaveCount; // 记录波次
	int IntervalCount; // 间隔计数
};

#endif // __HELLOWORLD_SCENE_H__
