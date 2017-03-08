#ifndef  _BASEENTITY_H_
#define  _BASEENTITY_H_

#include <iostream>
#include <cmath>
#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Data.h"

USING_NS_CC;

#define ENEMY_ONE_STEP 5
#define BULLET_ONE_STEP 10

/*
// 向量坐标
struct MyVec
{
int m_x;
int m_y;
MyVec(int x = 0, int y = 0)
{
m_x = x;
m_y = y;
}
};

// 打印向量坐标
void PrintMyVec(MyVec myVec)
{
std::cout << "(" << myVec.m_x << ", " << myVec.m_y << ")\n";
}
*/



/*****************************************
* 敌人、子弹、防御塔基类
*****************************************/

// 敌人基类
class EnemyBase
{
public:
	// @para: 生命值，速度矢量，移动状态
	EnemyBase(int health = 100, Vec2 velocity = Vec2(0, 0), bool isMoving = false)
	{
		m_health = health;
		m_velocity = velocity;
		m_isMoving = isMoving;
		m_sprite = NULL;
		m_oneStep = ENEMY_ONE_STEP;
	}
	~EnemyBase() {}

	int GetHealth() { return m_health; }
	void SetHealth(int health) { m_health = health; }

	Vec2 GetVelocity() { return m_velocity; }
	void SetVelocity(Vec2 velocity) { m_velocity = velocity; }

	bool GetIsMoving() { return m_isMoving; }
	void SetIsMoving(bool isMoving) { m_isMoving = isMoving; }

	Node* GetSprite() { return m_sprite; }
	void SetSprite(Node* sprite) { m_sprite = sprite; }

	int GetOneStep() { return m_oneStep; }
	void SetOneStep(int oneStep) { m_oneStep = oneStep; }

	void Rotate(Vec2 destPos); // 敌人旋转至面向目的地
	bool MoveOneStep(Vec2 destPos); // 敌人朝向目的地移动一步
	bool IsReach(Vec2 destPos); // 判断是否达到目的地
	void SetSptBitmask(Node* pEnemySpt); // 给刚体设置掩码

private:
	int m_health; // 血量
	Vec2 m_velocity; // 速度矢量
	bool m_isMoving; // 是否在移动
	Node* m_sprite; // 精灵
	int m_oneStep; // 精灵一步最大所占的像素
};



// 弓箭、导弹等攻击道具的基类
class BulletBase
{
public:
	// @para: 目标精灵指针，伤害值，速度矢量
	BulletBase(Node* targetSpt = NULL, int damage = 1, Vec2 velocity = Vec2(0, 0))
	{
		m_targetSpt = targetSpt;
		m_damage = damage;
		m_velocity = velocity;
		m_sprite = NULL;
		m_oneStep = BULLET_ONE_STEP;
	}
	~BulletBase() {}

	int GetDamage() { return m_damage; }
	void SetDamage(int damage) { m_damage = damage; }

	Vec2 GetVelocity() { return m_velocity; }
	void SetVelocity(Vec2 velocity) { m_velocity = velocity; }

	Node* GetSprite() { return m_sprite; }
	void SetSprite(Node* sprite) { m_sprite = sprite; }

	Node* GetTargetSpt() { return m_targetSpt; }
	void SetTargetSpt(Node* targetSpt) { m_targetSpt = targetSpt; }

	int GetOneStep() { return m_oneStep; }
	void SetOneStep(int oneStep) { m_oneStep = oneStep; }

	void Rotate(Vec2 destPos); // 子弹旋转至面向目的地
	void MoveOneStep(); // 子弹射向目标，与EnemyBase不同的是一旦确定目标则不会改变

	void SetSptBitmask(Node* pEnemySpt); // 给刚体设置掩码

private:
	int m_damage; // 攻击道具的伤害值
	Vec2 m_velocity; // 速度矢量
	Node* m_sprite; // 自身精灵的指针
	Node* m_targetSpt; // 射向目标精灵的指针
	Vec2 m_lastPos; // 上一次射向目标精灵的位置
	int m_oneStep; // 精灵一步最大所占的像素
};



// 防御塔基类
class TowerBase
{
public:
	// @para: 防御塔造价，射程半径
	TowerBase(int cost = 0, int range = 0)
	{
		m_cost = cost;
		m_range = range;
		m_sprite = NULL;
		m_targetSpt = NULL;
		m_CDTime = 0.0;
	}
	~TowerBase() {}

	int GetCost() { return m_cost; }
	void SetCost(int cost) { m_cost = cost; }

	int GetRange() { return m_range; }
	void SetRange(int range) { m_range = range; }

	Node* GetSprite() { return m_sprite; }
	void SetSprite(Node* sprite) { m_sprite = sprite; }

	Node* GetTargetSpt() { return m_targetSpt; }
	void SetTargetSpt(Node* targetSpt) { m_targetSpt = targetSpt; }

	double GetCDTime() { return m_CDTime; }
	void SetCDTime(double CDTime) { m_CDTime = CDTime; }

	double GetMaxCDTime() { return m_MaxCDTime; }
	void SetMaxCDTime(double MaxCDTime) { m_MaxCDTime = MaxCDTime; }

	bool IsInRange(Node* pEnemySpt);

private:
	int m_cost; // 防御塔造价
	int m_range; // 射程半径
	Node* m_sprite; // 精灵
	Node* m_targetSpt; // 射向目标精灵的指针
	double m_CDTime; // 防御塔当前冷却时间
	double m_MaxCDTime; // 防御塔总冷却时间
};

// 防御塔基地的基类
class BasementBase
{
public:
	// @para: 防御塔基地的位置，层节点指针
	BasementBase(Vec2 vPos, Node* pLayer)
	{
		auto pBasement = Sprite::create("Tower/Basement.png");
		pBasement->setPosition(vPos);
		pBasement->setScale(0.7, 0.7);
		pLayer->addChild(pBasement);
		m_sprite = pBasement;
	}

	Node* GetSprite() { return m_sprite; }
	void SetSprite(Node* sprite) { m_sprite = sprite; }
private:
	Node* m_sprite; // 精灵
};

/*****************************************
* 基类结束
*****************************************/



/*****************************************
* 敌人派生类
*****************************************/

// 盔甲兵
class ArmourEnemy : public EnemyBase
{
public:
	ArmourEnemy(Vec2 vPos, Node* pLayer, int Z = 0, int health = 100, Vec2 velocity = Vec2(0, 0), bool isMoving = false)\
		: EnemyBase(health, velocity, isMoving)
	{
		auto pEnemySpt = Sprite::create("Enemy/ArmourEnemy.png");
		pEnemySpt->setPosition(vPos);
		pEnemySpt->setAnchorPoint(Vec2(0.5, 0.5));
		pEnemySpt->setTag(ARMOUR_TAG);
		pLayer->addChild(pEnemySpt, Z);
		SetSprite(pEnemySpt);

		// 添加刚体
		auto pEnemyBody = PhysicsBody::createBox(Size(pEnemySpt->getContentSize().width, pEnemySpt->getContentSize().height));
		pEnemyBody->setDynamic(false);
		pEnemySpt->setPhysicsBody(pEnemyBody);

		// 设置掩码
		SetSptBitmask(pEnemySpt);

		// 设置移动速度
		SetOneStep(5);
	}
	~ArmourEnemy() {}

};


/*****************************************
* 敌人派生类结束
*****************************************/



/*****************************************
* 子弹派生类
*****************************************/

// 魔法子弹
class MagicBullet : public BulletBase
{
public:
	MagicBullet(Node* targetSpt = NULL, Vec2 vPos = Vec2(0, 0), Node* pLayer = NULL, int Z = 0, int damage = 1, Vec2 velocity = Vec2(0, 0))\
		: BulletBase(targetSpt, damage, velocity)
	{
		auto pBulletSpt = Sprite::create("Bullet/MagicBullet.png");
		pBulletSpt->setPosition(vPos);
		pBulletSpt->setAnchorPoint(Vec2(0.5, 0.5));
		pBulletSpt->setTag(MAGICBULLET_TAG);
		pLayer->addChild(pBulletSpt, Z);

		// 添加刚体
		auto pBulletBody = PhysicsBody::createBox(Size(pBulletSpt->getContentSize().width, pBulletSpt->getContentSize().height));
		pBulletBody->setDynamic(false);
		pBulletSpt->setPhysicsBody(pBulletBody);

		// 设置掩码
		SetSptBitmask(pBulletSpt);

		// 获取初始方向
		Vec2 vVector = targetSpt->getPosition() - vPos; // 精灵指向目的地的向量
		auto rotateRadians = vVector.getAngle(); // 获取向量与x轴的弧度
		auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians); // 将弧度转为角度
		pBulletSpt->setRotation(rotateDegrees);

		SetSprite(pBulletSpt);

		// 设置移动速度
		SetOneStep(10);
	}
	~MagicBullet() {}

};

/*****************************************
* 子弹派生类结束
*****************************************/



/*****************************************
* 防御塔派生类
*****************************************/

// 魔法塔
class MagicTower : public TowerBase
{
public:
	MagicTower(Vec2 vPos, Node* pLayer, int Z = 0, int cost = 0, int range = 0)\
		: TowerBase(cost, range)
	{
		auto pMagicTowerSpt = Sprite::create("Tower/MagicTower.png");
		pMagicTowerSpt->setPosition(vPos);
		pMagicTowerSpt->setAnchorPoint(Vec2(0.5, 0.5));
		pLayer->addChild(pMagicTowerSpt, Z);
		SetSprite(pMagicTowerSpt);

		SetMaxCDTime(MAGIC_TOWER_CDTIME);
		SetRange(300); // 设置射程
	}
	~MagicTower() {}

};

// 弓箭塔
class ArrowTower : public TowerBase
{
public:
	ArrowTower(Vec2 vPos, Node* pLayer, int Z = 0, int cost = 0, int range = 0)\
		: TowerBase(cost, range)
	{
		auto pArrowTowerSpt = Sprite::create("Tower/ArrowTower.png");
		pArrowTowerSpt->setPosition(vPos);
		pArrowTowerSpt->setAnchorPoint(Vec2(0.5, 0.5));
		pLayer->addChild(pArrowTowerSpt, Z);
		SetSprite(pArrowTowerSpt);

		SetMaxCDTime(ARROW_TOWER_CDTIME);
		SetRange(300); // 设置射程
	}
	~ArrowTower() {}

};

// 加农炮塔
class CannonTower : public TowerBase
{
public:
	CannonTower(Vec2 vPos, Node* pLayer, int Z = 0, int cost = 0, int range = 0)\
		: TowerBase(cost, range)
	{
		auto pCannonTowerSpt = Sprite::create("Tower/CannonTower.png");
		pCannonTowerSpt->setPosition(vPos);
		pCannonTowerSpt->setAnchorPoint(Vec2(0.5, 0.5));
		pLayer->addChild(pCannonTowerSpt, Z);
		SetSprite(pCannonTowerSpt);

		SetMaxCDTime(CANNON_TOWER_CDTIME);
		SetRange(300); // 设置射程
	}
	~CannonTower() {}

};


/*****************************************
* 防御塔派生类结束
*****************************************/


#endif