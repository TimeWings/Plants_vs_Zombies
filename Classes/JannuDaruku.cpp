#include "JannuDaruku.h"
#include "Global.h"
#include <iostream>
JannuDaruku::JannuDaruku(Point position,int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	Sprite*sp = Sprite::create("Jannu.png");
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.25);
	this->position = position;
	sp->setPosition(position);
	this->setHp(20);
	this->setInterval(2000);
	//添加到植物层（显示）
	addLayer(sp);
	//立即调用die
	Die();
}

bool JannuDaruku::isWorking()
{
	return false;
}

void JannuDaruku::work()
{
	
}

void JannuDaruku::Die()
{
	//贞德拉伸
	Sprite *sp = this->getImg();
	float preScale = sp->getScaleX();
	CCScaleTo * scaleup = CCScaleTo::create(1.0f, preScale + 0.05, preScale + 0.01);
	//贞德变大和放火函数合成队列
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::MyFire, this));
	Sequence *sequence = Sequence::create(scaleup, actionDone, NULL);

	sp->runAction(sequence);
}

void JannuDaruku::MyFire(Node *pSender)
{
	//把旧精灵移除
	this->getImg()->removeFromParent();
	//火焰效果
	creatFire();
	//清除同排僵尸
	for (int i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i)->getRow() == this->getRow())
		{
			std::cout << "清除僵尸" << std::endl;
			zombiesDie(readyZombies.at(i)->getImg());
			readyZombies.erase(readyZombies.begin() + i);
			i--;
		}
	}
}

void JannuDaruku::zombiesDie(Node* pSender)
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
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::clear, this));
	Sequence *sequence = Sequence::create(tintby, fadeout, actionDone,NULL);
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
//产生多个精灵，实现一列火焰
void JannuDaruku::creatFire()
{
	Sprite*sp = Sprite::create("Fire1.png");
	sp->retain();
	sp->setScale(1.5);

	SpriteFrame *sp1;
	Vector<SpriteFrame*> allframe;
	auto visibleSize = Director::getInstance()->getVisibleSize();
	char str[100] = { 0 };
	for (int i = 1; i <= 7; i++)
	{
		sprintf(str, "Fire%d.png", i);
		sp1 = SpriteFrame::create(str, sp->getDisplayFrame()->getRect());
		allframe.pushBack(sp1);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);

	for (int x = 0; x < visibleSize.width; x += 200)
	{
		Sprite*sp = Sprite::create("Fire8.png");
		sp->retain();
		sp->setScale(1.5);
		//sp->setPosition(this->position);
		sp->setPosition(Point(x, this->position.y - 10));
		addLayer(sp);
		auto actionDone = CallFuncN::create(CC_CALLBACK_1(JannuDaruku::clear, this));
		Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
		sp->runAction(sequence);
	}
}

void JannuDaruku::Attacked()
{
}

void JannuDaruku::CreateBullet()
{
}

void JannuDaruku::clear(Node * pSender)
{
	pSender->removeFromParent();
}
