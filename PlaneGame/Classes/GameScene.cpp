#include "GameScene.h"

/**
 * 创建场景，并添加GameLayer层
 */
cocos2d::Scene* GameLayer::createScene() {
    auto scene = Scene::create();
    auto layer = GameLayer::create();
    scene->addChild(layer);
    return scene;
}

bool GameLayer::init() {
    if (!Layer::init()) {
        return false;
    }
    this->setTouchEnabled(true);//设置层中可触摸点击
    Size winSize = Director::getInstance()->getWinSize();
    /**
     * 随即加载背景图片，
     */
    char buff[15];
    int id = getRand(1, 5);//返回1~5之间的随机数
    sprintf(buff, "img_bg_%d.jpg", id);
    auto over = Sprite::create(buff);
    over->setPosition(Point(winSize.width / 2, winSize.height / 2));
    this->addChild(over);
    return true;
}

/**
 * 返回从start到end的随机整数
 */
int GameLayer::getRand(int start, int end) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    unsigned long int rand_seed = tv.tv_sec * 1000 + tv.tv_usec / 1000;//随机数种子
    srand(rand_seed);
    float i = CCRANDOM_0_1() * (end - start + 1) + start;
    return (int) i;
}

/**
 * 在onEnter函数之后调用
 * 功能：创建飞机、子弹、敌机并添加到层中
 */
void GameLayer::onEnterTransitionDidFinish() {
    planeLayer = PlaneLayer::create();
    this->addChild(planeLayer);
    bulletSprite = BulletSprite::create();
    this->addChild(bulletSprite);
    enemyLayer = EnemyLayer::create();
    this->addChild(enemyLayer);
    //设置每帧时都调用gameUpdate函数
    this->schedule(schedule_selector(GameLayer::gameUpdate));
    //添加menu，并设置回调函数
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    auto closeItem = MenuItemImage::create("CloseNormal.png","CloseSelected.png",CC_CALLBACK_1(GameLayer::menuCloseCallback, this));
    closeItem->setPosition(
                           Point(origin.x + visibleSize.width- closeItem->getContentSize().width / 2, origin.y + closeItem->getContentSize().height / 2));
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
}

/**
 * menu的回调函数
 */
void GameLayer::menuCloseCallback(Ref* pSender) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


/**
 * 子弹和敌机碰撞检测函数
 */
bool GameLayer::bulletCollisionEnemy(Sprite* pBullet) {
    //遍历场景中的所有敌机，看子弹是否和敌机的包装矩形有重叠
    for (auto& eEnemy : enemyLayer->vecEnemy) {
        EnemySprite* pEnemySprite = (EnemySprite*) eEnemy;
        //判断矩形是否有重叠
        if (pBullet->boundingBox().intersectsRect(
                                                  pEnemySprite->getBoundingBox())) {
            if (1 == pEnemySprite->getLife()) {
                pEnemySprite->loseLife();
                enemyLayer->blowupEnemy(pEnemySprite);
            } else {
                pEnemySprite->loseLife();
            }
            //有重叠则移除子弹
            bulletSprite->removeBullet(pBullet);
            return true;
        }
    }
    return false;
}


/**
 * 在每帧时都进行游戏逻辑检测，
 * 检测子弹和敌机是否有碰撞
 * 检测主角飞机和敌机是否有碰撞
 */
void GameLayer::gameUpdate(float dt) {
    bool bMoveButt = false;
    for (auto& eButtle : bulletSprite->vecBullet) {
        Sprite* pBullet = (Sprite*) eButtle;
        bMoveButt = bulletCollisionEnemy(pBullet);
        if (bMoveButt) {
            return;
        }
    }
    enemyCollisionPlane();
}

/**
 * 敌机和主角飞机是否有碰撞
 * 遍历所有敌机进行检测
 */
bool GameLayer::enemyCollisionPlane() {
    Sprite* pPlane = (Sprite*) planeLayer->getChildByTag(AIRPLANE);
    for (auto& eEnemy : enemyLayer->vecEnemy) {
        EnemySprite* pEnemySprite = (EnemySprite*) eEnemy;
        if (pPlane->boundingBox().intersectsRect(pEnemySprite->getBoundingBox()) && pEnemySprite->getLife() > 0) {
            //TODO,DO WHAT YOU WANT
            // this->unscheduleAllSelectors();
            // this->bulletLayer->StopBulletShoot();
            // this->planeLayer->blowUp();
            return true;
        }
    }
    
    return false;
    
}