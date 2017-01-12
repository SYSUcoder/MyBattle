#ifndef  _BASEENTITY_H_
#define  _BASEENTITY_H_

#include <iostream>
#include <cmath>
#include "SimpleAudioEngine.h"
#include "cocos2d.h"

USING_NS_CC;

#define ENEMY_ONE_STEP 5
#define BULLET_ONE_STEP 10

/*
// ��������
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

// ��ӡ��������
void PrintMyVec(MyVec myVec)
{
std::cout << "(" << myVec.m_x << ", " << myVec.m_y << ")\n";
}
*/



/*****************************************
* ���ˡ��ӵ�������������
*****************************************/

// ���˻���
class EnemyBase
{
public:
	// @para: ����ֵ���ٶ�ʸ�����ƶ�״̬
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

	void Rotate(Vec2 destPos); // ������ת������Ŀ�ĵ�
	void MoveOneStep(Vec2 destPos); // ���˳���Ŀ�ĵ��ƶ�һ��
	bool IsReach(Vec2 destPos); // �ж��Ƿ�ﵽĿ�ĵ�

private:
	int m_health; // Ѫ��
	Vec2 m_velocity; // �ٶ�ʸ��
	bool m_isMoving; // �Ƿ����ƶ�
	Node* m_sprite; // ����
	int m_oneStep; // ����һ�������ռ������
};



// �����������ȹ������ߵĻ���
class BulletBase
{
public:
	// @para: �˺�ֵ���ٶ�ʸ��
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

	void SetTargetSpt(Node* targetSpt) { m_targetSpt = targetSpt; }

	int GetOneStep() { return m_oneStep; }
	void SetOneStep(int oneStep) { m_oneStep = oneStep; }

	void Rotate(Vec2 destPos); // �ӵ���ת������Ŀ�ĵ�
	void MoveOneStep(); // �ӵ�����Ŀ�꣬��EnemyBase��ͬ����һ��ȷ��Ŀ���򲻻�ı�

private:
	int m_damage; // �������ߵ��˺�ֵ
	Vec2 m_velocity; // �ٶ�ʸ��
	Node* m_sprite; // �������ָ��
	Node* m_targetSpt; // ����Ŀ�꾫���ָ��
	int m_oneStep; // ����һ�������ռ������
};



// ����������
class TowerBase
{
public:
	// @para: ��������ۣ���̰뾶
	TowerBase(int cost = 0, int range = 0)
	{
		m_cost = cost;
		m_range = range;
		m_sprite = NULL;
	}
	~TowerBase() {}

	int GetCost() { return m_cost; }
	void SetCost(int cost) { m_cost = cost; }

	int GetRange() { return m_range; }
	void SetRange(int range) { m_range = range; }

	Node* GetSprite() { return m_sprite; }
	void SetSprite(Node* sprite) { m_sprite = sprite; }

private:
	int m_cost; // ���������
	int m_range; // ��̰뾶
	Node* m_sprite; // ����
};

/*****************************************
* �������
*****************************************/



/*****************************************
* ����������
*****************************************/

// ���ױ�
class ArmourEnemy : public EnemyBase
{
public:
	ArmourEnemy(Vec2 vPos, Node* pLayer, int Z = 0, int health = 100, Vec2 velocity = Vec2(0, 0), bool isMoving = false)\
		: EnemyBase(health, velocity, isMoving)
	{
		auto pEnemySpt = Sprite::create("Enemy/ArmourEnemy.png");
		pEnemySpt->setPosition(vPos);
		pEnemySpt->setAnchorPoint(Vec2(0.5, 0.5));
		pLayer->addChild(pEnemySpt, Z);
		SetSprite(pEnemySpt);

		// �����ƶ��ٶ�
		SetOneStep(5);
	}
	~ArmourEnemy() {}

};


/*****************************************
* �������������
*****************************************/



/*****************************************
* �ӵ�������
*****************************************/

// ħ���ӵ�
class MagicBullet : public BulletBase
{
public:
	MagicBullet(Node* targetSpt = NULL, Vec2 vPos = Vec2(0, 0), Node* pLayer = NULL, int Z = 0, int damage = 1, Vec2 velocity = Vec2(0, 0))\
		: BulletBase(targetSpt, damage, velocity)
	{
		auto pBulletSpt = Sprite::create("Bullet/MagicBullet.png");
		pBulletSpt->setPosition(vPos);
		pBulletSpt->setAnchorPoint(Vec2(0.5, 0.5));
		pLayer->addChild(pBulletSpt, Z);

		// ��ȡ��ʼ����
		Vec2 vVector = targetSpt->getPosition() - vPos; // ����ָ��Ŀ�ĵص�����
		auto rotateRadians = vVector.getAngle(); // ��ȡ������x��Ļ���
		auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians); // ������תΪ�Ƕ�
		pBulletSpt->setRotation(rotateDegrees);

		SetSprite(pBulletSpt);

		// �����ƶ��ٶ�
		SetOneStep(10);
	}
	~MagicBullet() {}

};

/*****************************************
* �ӵ����������
*****************************************/



/*****************************************
* ������������
*****************************************/

// ħ����
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
	}
	~MagicTower() {}

};


/*****************************************
* ���������������
*****************************************/


#endif