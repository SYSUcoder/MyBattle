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

private:
	MyActionManager* actionManager; // 处理相关行为的指针
	vector<EnemyBase> EnemyVec; // 敌人的精灵集合
	vector<BulletBase> BulletVec; // 子弹的精灵集合
	Label* label; // 测试文本
};

#endif // __HELLOWORLD_SCENE_H__
