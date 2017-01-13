#include "Action.h"

#include <cmath>

USING_NS_CC;

MyActionManager::MyActionManager() {}

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


EnemyBase MyActionManager::CreateEnemy(Node* pLayer)
{
	auto pEnemy = ArmourEnemy(Point(-10, 255), pLayer);
	return pEnemy;
}