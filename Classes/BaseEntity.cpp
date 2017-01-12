#include "BaseEntity.h"

USING_NS_CC;

// ��ת��ʹ��������ǰ������
void EnemyBase::Rotate(Vec2 destPos)
{
	Vec2 vPos = m_sprite->getPosition(); // ���鵱ǰ����
	Vec2 vVector = destPos - vPos; // ����ָ��Ŀ�ĵص�����
	auto rotateRadians = vVector.getAngle(); // ��ȡ������x��Ļ���
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians); // ������תΪ�Ƕ�
	auto speed = 0.5 / M_PI; // ��ת������
	auto rotateDuration = fabs(rotateRadians * speed); // �����ת��ʱ��
	m_sprite->runAction(Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
		NULL)); // ��ת����
}

// ǰ��һ���������ƶ��ĺ���
void EnemyBase::MoveOneStep(Vec2 destPos)
{
	EnemyBase::Rotate(destPos); // ����Ŀ�ĵ�

	Vec2 vPos = m_sprite->getPosition(); // ���鵱ǰ����
	Vec2 vVector = destPos - vPos; // ����ָ��Ŀ�ĵص�����
	auto rotateRadians = vVector.getAngle(); // ��ȡ������x��Ļ���
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(1 * rotateRadians); // ������תΪ�Ƕȣ�������y��������Ϊ����
																   // std::cout << rotateDegrees << std::endl;
	auto fDistance = vPos.distance(destPos); // ��ȡ���鵱ǰ����λ�����յ�֮��ľ���
											 // std::cout << fDistance << std::endl;

	if (fDistance > m_oneStep) // ������������һ���ľ���
	{
		// std::cout << "rotateDegrees:" << rotateDegrees << std::endl;
		// std::cout << "cos(rotateDegrees):" << cos(rotateDegrees) << ",sin(rotateDegrees):" << sin(rotateDegrees) << std::endl;
		// cos��sin�Ĳ���Ϊ���ȣ������ǽǶ�
		Vec2 vOffset = Vec2(cos(rotateRadians)*m_oneStep, sin(rotateRadians)*m_oneStep); // ��һ����ƫ��ֵ
																						 // std::cout << vOffset.x << "," << vOffset.y << std::endl;
		m_sprite->setPosition(vPos + vOffset); // �������Ƶ���һ����λ��
	}
	else
	{
		m_sprite->setPosition(destPos); // С�����һ����ֱ���Ƶ�Ŀ�ĵ�
	}
}

// �ж��Ƿ񵽴�Ŀ�ĵ�
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
* �ӵ�����ʵ��
************************************************/

// ��ת��ʹ��������ǰ������
void BulletBase::Rotate(Vec2 destPos)
{
	Vec2 vPos = m_sprite->getPosition(); // ���鵱ǰ����
	Vec2 vVector = destPos - vPos; // ����ָ��Ŀ�ĵص�����
	auto rotateRadians = vVector.getAngle(); // ��ȡ������x��Ļ���
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(-1 * rotateRadians); // ������תΪ�Ƕ�
	auto speed = 0.5 / M_PI; // ��ת������
	auto rotateDuration = fabs(rotateRadians * speed); // �����ת��ʱ��
	m_sprite->runAction(Sequence::create(RotateTo::create(rotateDuration, rotateDegrees),
		NULL)); // ��ת����
}

// ǰ��һ���������ƶ��ĺ���
void BulletBase::MoveOneStep()
{
	auto destPos = m_targetSpt->getPosition();
	BulletBase::Rotate(destPos); // ����Ŀ�ĵ�

	Vec2 vPos = m_sprite->getPosition(); // ���鵱ǰ����
	Vec2 vVector = destPos - vPos; // ����ָ��Ŀ�ĵص�����
	auto rotateRadians = vVector.getAngle(); // ��ȡ������x��Ļ���
	auto rotateDegrees = CC_RADIANS_TO_DEGREES(1 * rotateRadians); // ������תΪ�Ƕȣ�������y��������Ϊ����
																   // std::cout << rotateDegrees << std::endl;
	auto fDistance = vPos.distance(destPos); // ��ȡ���鵱ǰ����λ�����յ�֮��ľ���
											 // std::cout << fDistance << std::endl;

	if (fDistance > m_oneStep) // ������������һ���ľ���
	{
		// std::cout << "rotateDegrees:" << rotateDegrees << std::endl;
		// std::cout << "cos(rotateDegrees):" << cos(rotateDegrees) << ",sin(rotateDegrees):" << sin(rotateDegrees) << std::endl;
		// cos��sin�Ĳ���Ϊ���ȣ������ǽǶ�
		Vec2 vOffset = Vec2(cos(rotateRadians)*m_oneStep, sin(rotateRadians)*m_oneStep); // ��һ����ƫ��ֵ
																						 // std::cout << vOffset.x << "," << vOffset.y << std::endl;
		m_sprite->setPosition(vPos + vOffset); // �������Ƶ���һ����λ��
	}
	else
	{
		m_sprite->setPosition(destPos); // С�����һ����ֱ���Ƶ�Ŀ�ĵ�
	}
}