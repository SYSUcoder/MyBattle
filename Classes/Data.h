#ifndef  _DATA_H_
#define  _DATA_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <vector>

using std::vector;

USING_NS_CC;

#define RIGHT_TOP_DESTINATION ( Vec2(1300, 520) ) // �����յ�����
#define VELOCITY_RATE 0.03 // �ٶȱ���

#define MAGIC_TOWER_CDTIME 1.0 // ħ������ȴʱ��
#define ARROW_TOWER_CDTIME 0.7 // ������ȴʱ��
#define CANNON_TOWER_CDTIME 1.8 // ��ũ������ȴʱ��

#define ARMOUR_TAG 1 // ���ױ��ı�ǩ
#define MAGICBULLET_TAG 11 // ħ���ӵ��ı�ǩ

#define BASEMENT_RANGE 20 // ���������ص����Χ�İ뾶
#define ARROW_ICON_RANGE 50 // ����������ê�㵽����ͼ��ê��ľ���
#define ICON_RANGE 15 // ͼ��뾶

#define NONE_ICON_TAG 100 // û�е��ͼ���ǩ
#define ARROW_ICON_TAG 101 // ������ͼ���ǩ
#define CANNON_ICON_TAG 102 // ��ũ����ͼ���ǩ
#define MAGIC_ICON_TAG 103 // ħ����ͼ���ǩ


#endif