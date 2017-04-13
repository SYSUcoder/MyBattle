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

	// 调试用，显示红框
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

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

	actionManager = MyActionManager::getInstance();


	//*******************************************************************
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
	label->setPosition(Vec2(origin.x + visibleSize.width / 2,
		origin.y + visibleSize.height - label->getContentSize().height));
	//*******************************************************************


	// 地图背景
	auto pMapSprite = Sprite::create("Background/background.jpg");
	pMapSprite->setAnchorPoint(Vec2(0, 0));
	this->addChild(pMapSprite);


	// 防御塔基地
	auto pBasement = BasementBase(Vec2(715, 310), this);
	BasementVec.push_back(pBasement);
	pBasement = BasementBase(Vec2(780, 420), this);
	BasementVec.push_back(pBasement);
	pBasement = BasementBase(Vec2(400, 720), this);
	BasementVec.push_back(pBasement);


	/*
	auto pBullet = MagicBullet(pEnemy.GetSprite(), pTower.GetSprite()->getPosition(), this);
	BulletVec.push_back(pBullet);
	*/

	// 调度器
	schedule(schedule_selector(HelloWorld::EnemyMove), 0.5f); // 敌军行动
	schedule(schedule_selector(HelloWorld::BulletMove), 0.02f); // 子弹行动
	schedule(schedule_selector(HelloWorld::TowerAttack), 0.04f); // 防御塔调度器

																 /*
																 auto a = EnemyBase(30, Vec2(2, 1), true);
																 std::cout << a.GetHealth() << ",(" << a.GetVelocity().x << "," << a.GetVelocity().y << "), " << a.GetIsMoving() << std::endl;
																 */

																 // 测试文本，用来判断当前点击的位置
	label = Label::createWithTTF("", "fonts/Marker Felt.ttf", 40);
	label->setPosition(Vec2(50, visibleSize.height - 50));
	label->setAnchorPoint(Vec2::ZERO);
	label->setString("hello");
	addChild(label, 1);

	// 碰撞监听
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

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
	auto pEnemy = actionManager->CreateEnemy(this, 300);
	EnemyVec.push_back(pEnemy);
	actionManager->MoveToDestination(pEnemy, RIGHT_TOP_DESTINATION);
}

// 子弹行动
void HelloWorld::BulletMove(float dt)
{
	auto it = BulletVec.begin();
	while (it != BulletVec.end())
	{
		it->MoveOneStep();
		it++;
	}
}

// 防御塔进攻
void HelloWorld::TowerAttack(float dt)
{
	auto it = TowerVec.begin();
	while (it != TowerVec.end()) // 遍历所有防御塔
	{
		double MaxCDTime = it->GetMaxCDTime();
		double curCDTime = it->GetCDTime();
		if (curCDTime <= 0) // 处于可发射状态
		{
			auto pTargetSpt = it->GetTargetSpt();
			bool IsExistEnemy = false;
			if (pTargetSpt != NULL && it->IsInRange(pTargetSpt)) // 目标精灵存在且在射程范围内
			{
				BulletBase pBullet;
				if (it->GetSprite()->getTag() == MAGICTOWER_TAG) // 魔法塔射出魔法子弹
				{
					pBullet = MagicBullet(pTargetSpt, it->GetSprite()->getPosition(), this);
				}
				else if (it->GetSprite()->getTag() == ARROWTOWER_TAG) // 箭塔射出弓箭
				{
					pBullet = ArrowBullet(pTargetSpt, it->GetSprite()->getPosition(), this);
				}
				else if (it->GetSprite()->getTag() == CANNONTOWER_TAG) // 加农炮塔射出加农炮
				{
					pBullet = CannonBullet(pTargetSpt, it->GetSprite()->getPosition(), this);
				}
				else
				{
					std::cout << "something wrong\n";
					break;
				}
				pBullet.SetDamage(it->GetBulletDamage());
				BulletVec.push_back(pBullet);
				IsExistEnemy = true;
			}
			else
			{
				auto pEnemyIt = EnemyVec.begin();
				while (pEnemyIt != EnemyVec.end()) // 遍历所有敌人
				{
					auto pEnemySpt = pEnemyIt->GetSprite();
					if (it->IsInRange(pEnemySpt)) // 找到第一个在射程范围之内的目标
					{
						BulletBase pBullet;
						if (it->GetSprite()->getTag() == MAGICTOWER_TAG) // 魔法塔射出魔法子弹
						{
							pBullet = MagicBullet(pEnemySpt, it->GetSprite()->getPosition(), this);
						}
						else if (it->GetSprite()->getTag() == ARROWTOWER_TAG) // 箭塔射出弓箭
						{
							pBullet = ArrowBullet(pEnemySpt, it->GetSprite()->getPosition(), this);
						}
						else if (it->GetSprite()->getTag() == CANNONTOWER_TAG) // 加农炮塔射出加农炮
						{
							pBullet = CannonBullet(pEnemySpt, it->GetSprite()->getPosition(), this);
						}
						else
						{
							std::cout << "something wrong\n";
							break;
						}
						pBullet.SetDamage(it->GetBulletDamage());
						BulletVec.push_back(pBullet);
						it->SetTargetSpt(pEnemySpt);
						IsExistEnemy = true;
						break;
					}
					pEnemyIt++;
				}
			}
			if (IsExistEnemy)
				it->SetCDTime(curCDTime + dt);
		}
		else if (curCDTime >= MaxCDTime) // 恢复可发射状态
		{
			it->SetCDTime(0.0);
		}
		else
		{
			it->SetCDTime(curCDTime + dt);
		}
		it++;
	}
}

// 触摸回调
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
	auto vCurPos = touch->getLocation();
	string str = VecToStr(vCurPos);
	std::cout << str << std::endl;

	// 判断是否点击基地
	auto it = BasementVec.begin();
	while (it != BasementVec.end()) // 遍历所有
	{
		auto pSpt = it->GetSprite();
		auto vPos = pSpt->getPosition();
		bool bInside = actionManager->IsInside(vPos, vCurPos, BASEMENT_RANGE);
		if (bInside)
		{
			std::cout << "inside!" << std::endl;
			actionManager->ShowChosenItem(vPos, this);
			pLastBasement = it;
			return true;
		}
		else
		{
			std::cout << "not inside" << std::endl;
		}	
		it++;
	}

	// 判断是否点击建造
	auto nTag = actionManager->IsClickIcon(vCurPos, this);
	std::cout << nTag << std::endl;
	if (nTag == ARROW_ICON_TAG) // 点击弓箭塔图标
	{
		std::cout << "build arrow tower\n";
		auto pLastBasementSpt = pLastBasement->GetSprite();
		auto vLastBasementPos = pLastBasementSpt->getPosition();
		auto pTower = actionManager->CreateArrowTower(vLastBasementPos, this);
		TowerVec.push_back(pTower);
		// 清除基地
		pLastBasementSpt->removeFromParentAndCleanup(true);
		pLastBasement = BasementVec.erase(pLastBasement);
	}
	else if (nTag == CANNON_ICON_TAG) // 点击加农炮塔图标
	{
		std::cout << "build connon tower\n";
		auto pLastBasementSpt = pLastBasement->GetSprite();
		auto vLastBasementPos = pLastBasementSpt->getPosition();
		auto pTower = actionManager->CreateCannonTower(vLastBasementPos, this);
		TowerVec.push_back(pTower);
		// 清除基地
		pLastBasementSpt->removeFromParentAndCleanup(true);
		pLastBasement = BasementVec.erase(pLastBasement);
	}
	else if (nTag == MAGIC_ICON_TAG) // 点击魔法塔图标
	{
		std::cout << "build magic tower\n";
		auto pLastBasementSpt = pLastBasement->GetSprite();
		auto vLastBasementPos = pLastBasementSpt->getPosition();
		auto pTower = actionManager->CreateMagicTower(vLastBasementPos, this);
		// 清除基地
		pLastBasementSpt->removeFromParentAndCleanup(true);
		pLastBasement = BasementVec.erase(pLastBasement);
		TowerVec.push_back(pTower);

	}
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

// 碰撞监听
bool HelloWorld::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA && nodeB)
	{
		Node *pBullet, *pTarget;

		// 判断NodeA和NodeB的类型
		if (nodeA->getTag() < ENEMY_TAG)
		{
			pTarget = nodeA;
			pBullet = nodeB;
		}
		else
		{
			pBullet = nodeA;
			pTarget = nodeB;
		}

		int BulletDamage; // 导弹造成伤害值
		auto pBulletIt = BulletVec.begin();
		while (pBulletIt != BulletVec.end())
		{
			auto pBulletSpt = pBulletIt->GetSprite();
			if (pBulletSpt == pBullet)
			{
				std::cout << "delete!\n";
				BulletDamage = pBulletIt->GetDamage(); // 获取伤害值
				pBulletIt = BulletVec.erase(pBulletIt); // 移除导弹
				break;
			}
			else
				pBulletIt++;
		}

		auto pEnemyIt = EnemyVec.begin();
		while (pEnemyIt != EnemyVec.end())
		{
			auto pEnemySpt = pEnemyIt->GetSprite();
			if (pEnemySpt == pTarget) // 获取目标精灵
			{
				int finalHealth = pEnemyIt->GetHealth() - BulletDamage;
				if (finalHealth <= 0) // 血量降为0以下
				{
					auto pTowerIt = TowerVec.begin();
					while (pTowerIt != TowerVec.end()) // 清除防御塔的目标精灵
					{
						auto targetSpt = pTowerIt->GetTargetSpt();
						if (targetSpt == pTarget)
						{
							pTowerIt->SetTargetSpt(NULL);
						}
						pTowerIt++;
					}

					auto pBulletIt = BulletVec.begin();
					while (pBulletIt != BulletVec.end()) // 清除子弹的目标精灵
					{
						auto targetSpt = pBulletIt->GetTargetSpt();
						auto pBulletSpt = pBulletIt->GetSprite();
						if (targetSpt == pTarget)
						{
							pBulletIt->SetTargetSpt(NULL);
						}
						pBulletIt++;
					}

					auto pEnemyIt = EnemyVec.begin();
					while (pEnemyIt != EnemyVec.end()) // 清除敌人的目标精灵
					{
						auto targetSpt = pEnemyIt->GetSprite();
						if (targetSpt == pTarget)
						{
							pEnemyIt = EnemyVec.erase(pEnemyIt);
						}
						else
							pEnemyIt++;
					}

					pTarget->removeFromParentAndCleanup(true); // 移除敌人的精灵
				}
				else
				{
					pEnemyIt->SetHealth(finalHealth);
				}
				break;
			}
			pEnemyIt++;
		}

		pBullet->removeFromParentAndCleanup(true);
	}

	return true;
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