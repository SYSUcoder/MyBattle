#ifndef __MAINSCENE_H__
#define __MAINSCENE_H__


#include "cocos2d.h"
#include "HelloWorldScene.h"
USING_NS_CC;


class MainScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainScene);

	void onNewGame(Ref *Sender);
	void onSettings(Ref *Sender);
	void onHelp(Ref *Sender);
	void onQuit(Ref *Sender);


};


#endif 