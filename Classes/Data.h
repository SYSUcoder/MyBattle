#ifndef  _DATA_H_
#define  _DATA_H_

#include "SimpleAudioEngine.h"
#include "cocos2d.h"
#include <vector>

using std::vector;

USING_NS_CC;

#define RIGHT_TOP_DESTINATION ( Vec2(1300, 520) ) // �����յ�����
#define LEFT_TOP_DESTINATION ( Vec2(-10, 480) ) // �����յ�����
#define VELOCITY_RATE 0.05 // �ٶȱ���

#define MAGIC_TOWER_CDTIME 1.0 // ħ������ȴʱ��
#define ARROW_TOWER_CDTIME 0.7 // ������ȴʱ��
#define CANNON_TOWER_CDTIME 1.8 // ��ũ������ȴʱ��

#define ARMOUR_TAG 1 // ���ױ��ı�ǩ
#define MONSTER_TAG 2 // ����ı�ǩ
#define BOSS_TAG 3 // ͷĿ�ı�ǩ
#define ENEMY_TAG 10 // �о���λ��ǩ

#define ARMOUR_VALUE 30 // ��ɱ���ױ���õĽ��
#define MONSTER_VALUE 60 // ��ɱ�����õĽ��
#define BOSS_VALUE 100 // ��ɱͷĿ��õĽ��

#define MAGICBULLET_TAG 11 // ħ���ӵ��ı�ǩ
#define ARROWBULLET_TAG 12 // ���������ı�ǩ
#define CANNONBULLET_TAG 13 // ��ũ�ڵ����ı�ǩ
#define BULLET_TAG 30 // �ӵ��ı�ǩ

#define MAGICTOWER_TAG 101 // ħ�����ı�ǩ
#define ARROWTOWER_TAG 102 // �������ı�ǩ
#define CANNONTOWER_TAG 103 // ��ũ�����ı�ǩ

#define BASEMENT_RANGE 20 // ���������ص����Χ�İ뾶
#define ARROW_ICON_RANGE 50 // ����������ê�㵽����ͼ��ê��ľ���
#define ICON_RANGE 15 // ͼ��뾶

#define NONE_ICON_TAG 100 // û�е��ͼ���ǩ
#define ARROW_ICON_TAG 101 // ������ͼ���ǩ
#define CANNON_ICON_TAG 102 // ��ũ����ͼ���ǩ
#define MAGIC_ICON_TAG 103 // ħ����ͼ���ǩ

#define ARROW_DAMAGE_LEVEL1 80 // �ȼ�1�������˺�ֵ

#define MAGIC_DAMAGE_LEVEL1 200 // �ȼ�1ħ�������˺�ֵ

#define CANNON_DAMAGE_LEVEL1 400 // �ȼ�1��ũ�������˺�ֵ

#define PLAYER_INIT_MONEY 100 // ��ҳ�ʼ�������
#define MAGICTOWER_COST 100 // ħ�������
#define ARROWTOWER_COST 50 // �������
#define CANNONTOWER_COST 150 // ��ũ�������

#define RIGHT_TOP_DIR 1 //  �о��ұ߷����ʶ
#define LEFT_TOP_DIR 2 //  �о���߷����ʶ

#define WAVECOUNT 15 // �ܲ�����



// ******************************************

struct SeqNode
{
	int EnemyTag;
	int TimeInterval;
	int EnemyDir;
	SeqNode(int tag, int interval, int enemyDir = RIGHT_TOP_DIR)
	{
		EnemyTag = tag;
		TimeInterval = interval;
		EnemyDir = enemyDir;
	}
};

extern vector<SeqNode> NodeVec;


#endif