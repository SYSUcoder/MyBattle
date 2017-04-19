#include "SettingScene.h"
#include "SimpleAudioEngine.h"
#include "MainScene.h"

using namespace CocosDenshion;

USING_NS_CC;

Scene* SettingScene::createScene()
{
	auto scene = Scene::create();

	auto layer = SettingScene::create();
	scene->addChild(layer);
	return scene;

}

bool SettingScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	isMusicOn = true;

	/*
	// background image
	auto mapSprite = Sprite::create("mainSceneBg.jpg");
	mapSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	mapSprite->setScale(1.1);
	addChild(mapSprite);
	*/

	// control table
	auto mapSprite = Sprite::create("Background/controlTable.png");
	mapSprite->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	mapSprite->setScale(0.5);
	addChild(mapSprite);

	// back menu
	auto onBack = MenuItemLabel::create(Label::createWithTTF("Back", "fonts/Marker Felt.ttf", 30), this, menu_selector(SettingScene::onBack));
	onBack->setColor(Color3B::WHITE);
	auto backMenu = Menu::create(onBack, NULL);
	backMenu->setPosition(50, visibleSize.height - 30);
	addChild(backMenu, 2);

	// processBar
	auto processBar = Sprite::create("Background/musicProcessBar.png");
	processBar->setPosition(visibleSize.width / 2, visibleSize.height / 2); // 蓄力条位置
	processBar->setScale(0.2, 0.2);
	addChild(processBar);

	// processBarCover
	auto processBarCover = Sprite::create("Background/musicProcessBarCover.png");
	timer = ProgressTimer::create(processBarCover); // progressTimer
	timer->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	timer->setType(kCCProgressTimerTypeBar);
	timer->setBarChangeRate(Vec2(1, 0));
	timer->setMidpoint(Vec2(0, 0));
	timer->setScale(0.2, 0.2);
	timer->setPercentage(100);
	addChild(timer, 1);

	// musicControl
	musicControl = Sprite::create("Background/musicControl.png");
	musicControl->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2); // 蓄力条位置
	musicControl->setScale(0.2, 0.2);
	addChild(musicControl, 1);

	setTouchEnabled(true);
	//设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}

bool SettingScene::onTouchBegan(Touch* touch, Event* event)
{
	return true;
}

void SettingScene::onTouchMoved(Touch* touch, Event* event)
{
	Point touchLocation = this->convertTouchToNodeSpace(touch);
	Point oldTouchLocation = touch->getPreviousLocation();
	oldTouchLocation = this->convertToNodeSpace(oldTouchLocation);
	Point translation = touchLocation - oldTouchLocation;


	if (musicControl->getBoundingBox().containsPoint(oldTouchLocation))
	{
		Point p = touchLocation;
		// right border
		if (touchLocation.x > 730)
		{
			p.x = 730;
		}
		// left border
		else if (touchLocation.x < 545)
		{
			p.x = 545;
		}
		else
		{
			float rate = (p.x - 545) / (730 - 545);
			timer->setPercentage(80 * rate + 5);
			/*
			if (p.x <= 525 && isMusicOn == true)
			{
				SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
				isMusicOn = false;
			}
			else if (p.x > 525 && isMusicOn == false)
			{
				SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
				isMusicOn = true;
			}
			*/
		}
		musicControl->setPosition(Point(p.x, musicControl->getPosition().y));
	}

	CCLOG("%lf", touchLocation.x);
}

void SettingScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{

}


void SettingScene::onBack(Ref *Sender)
{
	CCScene *scene = MainScene::createScene();

	CCDirector::sharedDirector()->replaceScene(TransitionPageTurn::create(1.0f, scene, true));


}

