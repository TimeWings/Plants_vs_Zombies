#include "Doom_shroom.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>

Doom_shroom::Doom_shroom()
{
}

Doom_shroom::Doom_shroom(Point position, int row, int col)
{
	this->thisIsEnd = false;
	this->position = position;
	this->setRow(row);
	this->setCol(col);
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Doom_shroom.png"));
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(0);
	//添加到植物层
	addLayer(sp);
	readyPlants.push_back(this);
}

void Doom_shroom::thisDie()
{
	//死亡动画(拉伸)
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(1.0f, preScale + 0.05, preScale + 0.01);
	//拉伸和爆炸函数合成队列
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::Effect, this));
	Sequence *sequence = Sequence::create(scaleup, actionDone, NULL);
	sp->runAction(sequence);
}

void Doom_shroom::Effect(Node * pSender)
{
	//把旧精灵移除
	this->getImg()->removeFromParent();
	//把hp设为-1
	this->setHp(-1);
	//火焰效果
	this->creatSprite();
	//清除范围僵尸
	this->zombiesDie();
}

void Doom_shroom::creatSprite()
{
	//爆炸动画
	SpriteFrame *sp1;
	char str[100] = { 0 };
	Vector<SpriteFrame*> allframe;
	for (int i = 1; i <= 11; i++)
	{
		sprintf(str, "Doom\\Boom%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	auto sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Doom\\Boom1.png"));
	sp->retain();
	sp->setScale(1.5);
	sp->setPosition(Point(this->position.x, this->position.y + 20));
	addLayer(sp);
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::clearSprite, this, sp));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);

}

void Doom_shroom::zombiesDie()
{
	//清除范围内僵尸
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		//判断范围
		//if(pow(zombie->getImg()->getPositionX() - this->position.x, 2) + pow(zombie->getImg()->getPositionY() - this->position.y, 2) <= 90 * 90)
		if (fabs(map::Point2Rank(zombie->getImg()->getPosition()).first - this->getRow()) <= 2 && fabs(map::Point2Rank(zombie->getImg()->getPosition()).second - this->getCol()) <= 2)
		{
			std::cout << "清除僵尸" << std::endl;
			///
			//记录下原本僵尸的必要信息
			Node* pSender = zombie->getImg();
			Point zombiePoint = pSender->getPosition();
			float scale = pSender->getScaleX();
			//停止僵尸所有动作
			pSender->getActionManager()->removeAllActionsFromTarget(pSender);
			//僵尸渐渐消灭
			ActionInterval * fadeout = FadeOut::create(0.5);
			//僵尸被颜色覆盖
			CCActionInterval * tintby = CCTintTo::create(0.2, 0, 0, 0);
			auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::clearNode, this));
			Sequence *sequence = Sequence::create(tintby, fadeout, actionDone, NULL);
			pSender->runAction(sequence);
			//僵尸死亡粒子效果
			CCParticleSystem* particleSystem = CCParticleExplosion::create();
			particleSystem->setStartColor(Color4F(0, 0, 0, 255));
			particleSystem->setPosition(zombiePoint);
			particleSystem->setLife(1);
			particleSystem->setGravity(Point(zombiePoint.x - this->position.x, zombiePoint.y - this->position.y + 50));
			particleSystem->setTexture(CCTextureCache::sharedTextureCache()->addImage("grain1.png"));
			particleSystem->setScale(0.3);
			particleSystem->setStartSize(90.0f);
			particleSystem->setEndSize(5.0f);
			addLayer(particleSystem);
			//移除出数组
			readyZombies.erase(readyZombies.begin() + i);
			i--;
		}
	}
}

void Doom_shroom::clearSprite(Node* pSender, Sprite* sp)
{
	std::cout << "清除特效" << std::endl;
	sp->removeFromParent();
}