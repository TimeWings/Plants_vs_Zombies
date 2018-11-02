#include "Doom_shroom.h"
#include "Global.h"
#include "EntityLayer.h"
#include <iostream>

Doom_shroom::Doom_shroom(Point position, int row, int col)
{
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
	this->setInterval(90000);
	//添加到植物层
	addLayer(sp);
	//直接死亡
	Die();
}

bool Doom_shroom::isWorking()
{
	return false;
}

void Doom_shroom::work()
{
}

void Doom_shroom::Die()
{
	//死亡动画
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(1.0f, preScale + 0.05, preScale + 0.01);
	//拉伸和爆炸函数合成队列
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::Boom, this));
	Sequence *sequence = Sequence::create(scaleup, actionDone, NULL);
	sp->runAction(sequence);
}

void Doom_shroom::Boom(Node* pSender)
{
	//移除精灵
	this->getImg()->removeFromParent();
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
	Sprite* sp = Sprite::create("Doom\\Boom1.png");
	sp->retain();
	sp->setScale(1.5);
	sp->setPosition(Point(this->position.x, this->position.y + 20));
	addLayer(sp);
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::clearSprite, this, sp));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);
	//清除范围内僵尸
	for (int i = 0; i < readyZombies.size(); i++)
	{
		Zombie* zombie = readyZombies.at(i);
		std::cout << map::Point2Rank(this->position).first << " " << map::Point2Rank(this->position).second << std::endl;
		if (fabs(map::Point2Rank(zombie->getImg()->getPosition()).first - this->getRow()) <= 1 && fabs(map::Point2Rank(zombie->getImg()->getPosition()).second - this->getCol()) <= 1 )
		{
			std::cout << "清除僵尸" << std::endl;
			zombiesDie(readyZombies.at(i)->getImg());
			readyZombies.erase(readyZombies.begin() + i);
			i--;
		}
	}
}

void Doom_shroom::zombiesDie(Node* pSender)
{
	//记录下原本僵尸的必要信息
	Point zombiePoint = pSender->getPosition();
	float scale = pSender->getScale();
	//停止僵尸所有动作
	pSender->getActionManager()->removeAllActionsFromTarget(pSender);
	//僵尸渐渐消灭
	ActionInterval * fadeout = FadeOut::create(0.5);
	//僵尸被颜色覆盖
	CCActionInterval * tintby = CCTintTo::create(0.5, 0, 0, 0);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Doom_shroom::clear, this));
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
}


void Doom_shroom::clearSprite(Node* pSender, Sprite* sp)
{
	std::cout << "清除特效" << std::endl;
	sp->removeFromParent();
}

void Doom_shroom::Self_Animation()
{
}

void Doom_shroom::Attacked()
{
}

void Doom_shroom::CreateBullet()
{
}

void Doom_shroom::clear(Node * pSender)
{
	pSender->removeFromParent();
}
