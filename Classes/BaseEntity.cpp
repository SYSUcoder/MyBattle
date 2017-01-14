#include "BaseEntity.h"

USING_NS_CC;

/************************************************
* 敌人基类函数实现
************************************************/

// 旋转，使精灵面向前进方向
void EnemyBase::Rotate(Vec2 destPos)
{
	Vec2 vPos = m_sprite->getPosition(); // 精灵当前坐标
	Vec2 vVector = destPos - vPos; // 精灵指向目的地的向量
	auto rotateRadians = vVector.getAngle(); // 获取向量与x轴的弧度
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians); // 将弧度转为角度
	auto speed = 0.5 / M_PI; // 旋转的速率
	auto rotateDuration = fabs(rotateRadians * speed); // 完成旋转的时间
	m_sprite->runAction(Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
		NULL)); // 旋转动画
}

// 前进一步，精灵移动的函数
// return: true代表到达终点
bool EnemyBase::MoveOneStep(Vec2 destPos)
{
	EnemyBase::Rotate(destPos); // 朝向目的地

	Vec2 vPos = m_sprite->getPosition(); // 精灵当前坐标
	Vec2 vVector = destPos - vPos; // 精灵指向目的地的向量
	auto rotateRadians = vVector.getAngle(); // 获取向量与x轴的弧度
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(1 * rotateRadians); // 将弧度转为角度（这里以y轴正半轴为正）
	// std::cout << rotateDegrees << std::endl;
	auto fDistance = vPos.distance(destPos); // 获取精灵当前所处位置与终点之间的距离
	// std::cout << fDistance << std::endl;

	if (fDistance > m_oneStep) // 当距离大于最大一步的距离
	{
		// std::cout << "rotateDegrees:" << rotateDegrees << std::endl;
		// std::cout << "cos(rotateDegrees):" << cos(rotateDegrees) << ",sin(rotateDegrees):" << sin(rotateDegrees) << std::endl;
		// cos和sin的参数为弧度，而不是角度
		Vec2 vOffset = Vec2(cos(rotateRadians)*m_oneStep, sin(rotateRadians)*m_oneStep); // 下一步的偏移值
		// std::cout << vOffset.x << "," << vOffset.y << std::endl;
		m_sprite->setPosition(vPos + vOffset); // 将精灵移到下一步的位置
		return false;
	}
	else
	{
		m_sprite->setPosition(destPos); // 小于最大一步则直接移到目的地
		return true;
	}
}

// 判断是否到达目的地
bool EnemyBase::IsReach(Vec2 destPos)
{
	Vec2 vPos = m_sprite->getPosition();
	std::cout << vPos.x << "," << vPos.y << std::endl;
	if (vPos == destPos)
		return true;
	else
		return false;
}



/************************************************
* 子弹函数实现
************************************************/

// 旋转，使精灵面向前进方向
void BulletBase::Rotate(Vec2 destPos)
{
	Vec2 vPos = m_sprite->getPosition(); // 精灵当前坐标
	Vec2 vVector = destPos - vPos; // 精灵指向目的地的向量
	auto rotateRadians = vVector.getAngle(); // 获取向量与x轴的弧度
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians); // 将弧度转为角度
	auto speed = 0.5 / M_PI; // 旋转的速率
	auto rotateDuration = fabs(rotateRadians * speed); // 完成旋转的时间
	m_sprite->runAction(Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
		NULL)); // 旋转动画
}

// 前进一步，精灵移动的函数
void BulletBase::MoveOneStep()
{
	auto destPos = m_targetSpt->getPosition();
	BulletBase::Rotate(destPos); // 朝向目的地

	Vec2 vPos = m_sprite->getPosition(); // 精灵当前坐标
	Vec2 vVector = destPos - vPos; // 精灵指向目的地的向量
	auto rotateRadians = vVector.getAngle(); // 获取向量与x轴的弧度
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(1 * rotateRadians); // 将弧度转为角度（这里以y轴正半轴为正）
	// std::cout << rotateDegrees << std::endl;
	auto fDistance = vPos.distance(destPos); // 获取精灵当前所处位置与终点之间的距离
	// std::cout << fDistance << std::endl;

	if (fDistance > m_oneStep) // 当距离大于最大一步的距离
	{
		// std::cout << "rotateDegrees:" << rotateDegrees << std::endl;
		// std::cout << "cos(rotateDegrees):" << cos(rotateDegrees) << ",sin(rotateDegrees):" << sin(rotateDegrees) << std::endl;
		// cos和sin的参数为弧度，而不是角度
		Vec2 vOffset = Vec2(cos(rotateRadians)*m_oneStep, sin(rotateRadians)*m_oneStep); // 下一步的偏移值
		// std::cout << vOffset.x << "," << vOffset.y << std::endl;
		m_sprite->setPosition(vPos + vOffset); // 将精灵移到下一步的位置
	}
	else
	{
		m_sprite->setPosition(destPos); // 小于最大一步则直接移到目的地
	}
}


/************************************************
* 防御塔函数实现
************************************************/

// 判断敌人是否在射程范围之内
bool TowerBase::IsInRange(Node* pEnemySpt)
{
	auto vEnemyPos = pEnemySpt->getPosition();
	auto vTowerPos = m_sprite->getPosition();
	auto fDistance = vTowerPos.distance(vEnemyPos);
	if (fDistance <= m_range) // 在射程范围之内
	{
		return true;
	}
	else
	{
		return false;
	}
}