#ifndef  _ACTION_H_
#define  _ACTION_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include "Data.h"
#include "BaseEntity.h"

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

	void MoveToDestination(EnemyBase pEnemy, Vec2 destPos);

	EnemyBase CreateEnemy(Node* pLayer);

private:
	MyActionManager();
};


#endif