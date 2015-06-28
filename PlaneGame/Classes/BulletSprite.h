#ifndef __BULLET_SPRITE_H__
#define __BULLET_SPRITE_H__

#include "cocos2d.h"
USING_NS_CC;

/**
 * 
    对于子弹层的渲染有两种机制，一种是直接从缓存中进行精灵创建，创建后的精灵直接添加并使用，第二种机制为将创建的精灵加入到SpriteBatchNode中，这样进行渲染效率更高。对于这样渲染的机制我在这里稍微提一下：
 
    普通的渲染机制为：准备，渲染，清除。准备，渲染，清除。...
 
    批次渲染机制为：准备，渲染，渲染....渲染，清除
 
    看以看到上面两种区别，批次渲染中只进行一次准备一次清除，要节省好多硬件消耗，这是游戏优化的一个重要指标。
 */

class BulletSprite : public cocos2d::Layer
{
public:
    BulletSprite();
	~BulletSprite();
    virtual bool init();  
    CREATE_FUNC(BulletSprite);

	Animation* f_createAnimate(int count,int fps);//创建子弹运行的动画
	void removeBullet( Node* pNode );//移除超出屏幕可视范围的子弹或者碰撞后的子弹清除
	void ShootBullet(float dt);//发射子弹，在其中进行子弹的渲染和子弹的飞行动作

public:
	Vector <Sprite *>vecBullet;//子弹容器
	SpriteBatchNode* bulletBatchNode;//批次渲染节点
};

#endif // __HELLOWORLD_SCENE_H__
