#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

#include <iostream>
#include <string>
#include <sstream>

using std::string;
using std::stringstream;

string VecToStr(Vec2 vVec);

USING_NS_CC;

Scene* HelloWorld::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::createWithPhysics();

	// 'layer' is an autorelease object
	auto layer = HelloWorld::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}


// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2,
		origin.y + closeItem->getContentSize().height / 2));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);


	auto label = Label::createWithTTF("Hello World", "fonts/Marker Felt.ttf", 24);

	// position the label on the center of the screen
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));

	auto pMapSprite = Sprite::create("Background/background.jpg");

	pMapSprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(pMapSprite);

	auto pEnemy = ArmourEnemy(Point(50, 50), this);
	EnemyVec.push_back(pEnemy);

	pEnemy = ArmourEnemy(Point(100, 100), this);
	EnemyVec.push_back(pEnemy);

	auto pTower = MagicTower(Point(780, 420), this);

	auto pBullet = MagicBullet(pEnemy.GetSprite(), pTower.GetSprite()->getPosition(), this);
	BulletVec.push_back(pBullet);


	schedule(schedule_selector(HelloWorld::EnemyMove), 0.04f); // 敌军行动
	schedule(schedule_selector(HelloWorld::BulletMove), 0.04f); // 敌军行动


	auto a = EnemyBase(30, Vec2(2, 1), true);
	std::cout << a.GetHealth() << ",(" << a.GetVelocity().x << "," << a.GetVelocity().y << "), " << a.GetIsMoving() << std::endl;


	// 测试文本，用来判断当前点击的位置
	label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(50, visibleSize.height - 50));
	label->setAnchorPoint(Vec2::ZERO);
	label->setString("hello");
	addChild(label, 1);


	// 设为可触摸
	setTouchEnabled(true);
	// 设置为单点触摸
	setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

	return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

// 敌军行动
void HelloWorld::EnemyMove(float dt)
{
	auto it = EnemyVec.begin();
	while (it != EnemyVec.end())
	{
		(*it).MoveOneStep(Vec2(400, 400));
		it++;
	}
}

// 子弹行动
void HelloWorld::BulletMove(float dt)
{
	auto it = BulletVec.begin();
	while (it != BulletVec.end())
	{
		(*it).MoveOneStep();
		it++;
	}
}

// 触摸回调
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	auto vCurPos = touch->getLocation();
	string str = VecToStr(vCurPos);
	std::cout << str << std::endl;
	return true;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
	auto vCurPos = touch->getLocation();
	string str = VecToStr(vCurPos);
	std::cout << str << std::endl;
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
	auto vCurPos = touch->getLocation();
}


// 将Vec2变成字符串
string VecToStr(Vec2 vVec)
{
	string str;
	stringstream ss;
	ss << "X: " << vVec.x << ", Y:" << vVec.y;
	std::cout << ss.str() << std::endl;
	str = ss.str();
	return str;
}