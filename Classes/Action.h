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
	// ����
	static MyActionManager* getInstance()
	{
		static MyActionManager instance;
		return &instance;
	}

	void MoveToDestination(EnemyBase pEnemy, Vec2 destPos); // �����ƶ�·��
	bool IsInside(Vec2 vPos1, Vec2 vPos2, double fDistance); // �жϵ���Ƿ��ڷ�Χ��
	void CloseIcon(); // �ر�ͼ��
	void ShowChosenItem(Vec2 vPos, Node* pLayer); // չʾ�����������ͼ��
	int IsClickIcon(Vec2 vPos, Node* pLayer); // �ж��Ƿ���ͼ��

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