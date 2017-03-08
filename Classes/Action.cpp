#include "Action.h"

#include <cmath>

USING_NS_CC;

MyActionManager::MyActionManager()
{
	isShowChosenItem = false;
}

void MyActionManager::MoveToDestination(EnemyBase pEnemy, Vec2 destPos)
{
	auto oneStep = pEnemy.GetOneStep();
	auto pEnemySpt = pEnemy.GetSprite();
	if (destPos == RIGHT_TOP_DESTINATION)
	{
		auto moveToPos1 = MoveTo::create((130 - pEnemySpt->getPosition().x)*1.0 / oneStep * VELOCITY_RATE, Vec2(130, 255));
		auto moveToPos2 = MoveTo::create(sqrt(70 * 70 + 45 * 45) / oneStep * VELOCITY_RATE, Vec2(200, 300));
		auto moveToPos3 = MoveTo::create(220 * 1.0 / oneStep * VELOCITY_RATE, Vec2(420, 300));
		auto moveToPos4 = MoveTo::create(sqrt(180 * 180 + 100 * 100) / oneStep * VELOCITY_RATE, Vec2(600, 200));
		auto moveToPos5 = MoveTo::create(100 * 1.0 / oneStep * VELOCITY_RATE, Vec2(700, 200));
		auto moveToPos6 = MoveTo::create(sqrt(200 * 200 + 80 * 80) / oneStep * VELOCITY_RATE, Vec2(900, 280));
		auto moveToPos7 = MoveTo::create(200 * 1.0 / oneStep * VELOCITY_RATE, Vec2(900, 480));
		auto moveToPos8 = MoveTo::create(sqrt(100 * 100 + 40 * 40) / oneStep * VELOCITY_RATE, Vec2(1000, 520));
		auto moveToPos9 = MoveTo::create(300 * 1.0 / oneStep * VELOCITY_RATE, Vec2(1300, 520));
		auto action = Sequence::create(moveToPos1, moveToPos2, moveToPos3, moveToPos4,
			moveToPos5, moveToPos6, moveToPos7, moveToPos8,
			moveToPos9, NULL);
		pEnemySpt->runAction(action);
	}
	else
	{

	}
}

bool MyActionManager::IsInside(Vec2 vPos1, Vec2 vPos2, double fDistance)
{
	auto fRealDistance = vPos1.distance(vPos2);
	if (fRealDistance <= fDistance)
	{
		return true; // 在点击范围内
	}
	else
	{
		return false; // 不在点击范围内
	}

}


EnemyBase MyActionManager::CreateEnemy(Node* pLayer)
{
	auto pEnemy = ArmourEnemy(Point(-10, 255), pLayer);
	return pEnemy;
}


TowerBase MyActionManager::CreateArrowTower(Vec2 vPos, Node* pLayer)
{
	auto pTower = ArrowTower(vPos, pLayer);
	return pTower;
}

TowerBase MyActionManager::CreateMagicTower(Vec2 vPos, Node* pLayer)
{
	auto pTower = MagicTower(vPos, pLayer);
	return pTower;
}

TowerBase MyActionManager::CreateCannonTower(Vec2 vPos, Node* pLayer)
{
	auto pTower = CannonTower(vPos, pLayer);
	return pTower;
}



void MyActionManager::CloseIcon()
{
	auto it = ChosenItemVec.begin();
	while (it != ChosenItemVec.end())
	{
		(*it)->removeFromParentAndCleanup(true);
		it++;
	}
	ChosenItemVec.clear();
	isShowChosenItem = false;
}

void MyActionManager::ShowChosenItem(Vec2 vPos, Node* pLayer)
{
	if (isShowChosenItem) // 已经展示状态，再次点击则关闭选项框
	{
		// CloseIcon();
		return;
	}
	// 弓箭塔图标
	auto pIcon = Sprite::create("icon/ArrowTower.png");
	pIcon->setPosition(vPos + Vec2(0, ARROW_ICON_RANGE));
	pIcon->setScale(0.7, 0.7);
	pIcon->setTag(ARROW_ICON_TAG);
	pLayer->addChild(pIcon);
	ChosenItemVec.push_back(pIcon);

	// 加农炮塔图标
	pIcon = Sprite::create("icon/CannonTower.png");
	pIcon->setPosition(vPos + Vec2(-ARROW_ICON_RANGE / 2 * 1.732, -ARROW_ICON_RANGE / 2));
	pIcon->setScale(0.7, 0.7);
	pIcon->setTag(CANNON_ICON_TAG);
	pLayer->addChild(pIcon);
	ChosenItemVec.push_back(pIcon);

	// 魔法塔图标
	pIcon = Sprite::create("icon/MagicTower.png");
	pIcon->setPosition(vPos + Vec2(ARROW_ICON_RANGE / 2 * 1.732, -ARROW_ICON_RANGE / 2));
	pIcon->setScale(0.7, 0.7);
	pIcon->setTag(MAGIC_ICON_TAG);
	pLayer->addChild(pIcon);
	ChosenItemVec.push_back(pIcon);

	isShowChosenItem = true;
}


// 返回Tag值，代表点击的图标
int MyActionManager::IsClickIcon(Vec2 vPos, Node* pLayer)
{
	auto it = ChosenItemVec.begin();
	while (it != ChosenItemVec.end())
	{
		auto vPos1 = (*it)->getPosition();
		auto nTag = (*it)->getTag();
		if (IsInside(vPos1, vPos, ICON_RANGE)) // 点在某个图标范围内
		{
			CloseIcon(); // 关闭图标
			return nTag;
		}
		it++;
	}
	CloseIcon(); // 关闭图标
	return NONE_ICON_TAG;
}