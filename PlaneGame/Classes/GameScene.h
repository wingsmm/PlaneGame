#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "PlaneLayer.h"
#include "BulletSprite.h"
#include "EnemyLayer.h"

USING_NS_CC;

enum EnBackground {
	e_BackgroundA = 1,
	e_BackgroundB = 2,
};

class GameLayer: public cocos2d::Layer {
    
public:
    //创建GameLayer层所属的场景
    static cocos2d::Scene* createScene();
    virtual bool init();
    //在onEnter执行完成之后调用此函数
    virtual void onEnterTransitionDidFinish();
    CREATE_FUNC(GameLayer);
    
public:
    //根据每帧来更新游戏
    void gameUpdate(float dt);
    //子弹碰撞检测
    bool bulletCollisionEnemy(Sprite* pBullet);
    //飞机碰撞检测
    bool enemyCollisionPlane();
    //menu回调函数
    void menuCloseCallback(cocos2d::Ref* pSender);
    
public:
    PlaneLayer *planeLayer;//飞机层
    BulletSprite *bulletSprite;//子弹层
    EnemyLayer *enemyLayer;//敌机层
    
    int getRand(int start, int end);//获取从start到end的随机数
};

#endif // __HELLOWORLD_SCENE_H__
