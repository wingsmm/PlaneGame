#ifndef __PIG_SPRITE_H__
#define __PIG_SPRITE_H__

#include "cocos2d.h"
USING_NS_CC;

class PigSprite : public cocos2d::Sprite
{
public:
    PigSprite();
    ~PigSprite();
    virtual bool init();  //精灵初始化
    CREATE_FUNC(PigSprite);//create函数宏
    void f_createAnimate(int count,int fps);//创建动画
    void f_followPlane(float dt);//跟随飞机
    Sprite *spritepig;
};

#endif // __HELLOWORLD_SCENE_H__
