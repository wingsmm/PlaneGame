#ifndef __ENEMY_SPRITE_H__
#define __ENEMY_SPRITE_H__
#include "cocos2d.h"
#include "EnemyInfo.h"

USING_NS_CC;
class EnemySprite : public Node
{
public:
	EnemySprite();//构造函数
	~EnemySprite();//析构函数
	virtual bool init();//初始化函数
	CREATE_FUNC(EnemySprite);//create函数宏定义，系统已经实现

	void setEnemyByType(EnemyType enType);//设置敌人的种类

	Sprite* getSprite();//获得已经创建的敌人
	int getLife();//获得生命值
	void loseLife();//被子弹击中后,生命值减少
	Rect getBoundingBox();//获得敌人的包装矩形
	Point getcurPoint();// 获得敌人的位置

private:
	Sprite *pEnemySprite;
	int nLife;
};

#endif
