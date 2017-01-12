#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "BaseEntity.h"

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
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void EnemyMove(float dt); // �����ж�
	void BulletMove(float dt); // �ӵ��ж�

private:
	vector<EnemyBase> EnemyVec; // ���˵ľ��鼯��
	vector<BulletBase> BulletVec; // �ӵ��ľ��鼯��
	Label* label; // �����ı�
};

#endif // __HELLOWORLD_SCENE_H__