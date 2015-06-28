#pragma once
/*
 
 游戏中的敌人类主要有四种，三种不同的敌机和炸弹从上面随机的落下来，
 同时每个敌人都有自己的生命值，当生命值为0后会被从游戏中移除。

 这个文件中主要设置了枚举类型来区别不同的敌人，同时设置了得人的生命数和每个敌人的分数，定义常量可以方便程序的维护。

 
 */
const int ENEMY1_MAXLIFE=3;
const int ENEMY2_MAXLIFE=5;
const int ENEMY3_MAXLIFE=10;

const int ENEMY1_SCORE=1;
const int ENEMY2_SCORE=6;
const int ENEMY3_SCORE=30;

enum Level
{
	EASY,
	MIDDLE,
	HARD,
	MOREHARD,
};

enum EnemyType
{
	Enemy1 = 1,
	Enemy2,
	Enemy3,
	Enemy4,
};
