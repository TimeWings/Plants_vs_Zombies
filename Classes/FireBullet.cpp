#include "FireBullet.h"
#include "Global.h"
#include <iostream>
FireBullet::FireBullet(int Plant_row, Bullet * bullet,double plantWidth)
{
	this->getRange()->push_back(Plant_row);
	Sprite *sp = Sprite::createWithTexture(bullet->getImg()->getTexture());
	sp->setScale(bullet->getImg()->getScale());
	//方便以后获取子弹精灵
	this->setImg(sp);
	this->setDamage(bullet->getDamage() * 2);
	this->setSpeed(bullet->getSpeed());
	sp->retain();
	//std::cout << sp->getContentSize().width << std::endl;
	//子弹发射位置微调
	sp->setPosition(bullet->getImg()->getPositionX()+ plantWidth ,bullet->getImg()->getPositionY());
	this->addLayer(sp);
	//子弹的特效（产生时的特效，或者拖尾效果）
	this->attack_Animation();
	readyBullet.push_back(this);
	//移动函数
	this->Self_Animation();
	this->move();
}

void FireBullet::Self_Animation()
{
	
	ParticleSystem* ps = CCParticleFire::create();
	ps->setTexture(Director::getInstance()->getTextureCache()->addImage("Fire_Effect.png"));
	ps->setStartSize(3);
	ps->setEmissionRate(500);
	ps->setTotalParticles(2000);
	ps->setEmitterMode(ParticleSystem::Mode::GRAVITY);
	ps->setGravity(Point(-1000, 0));
	ps->setPositionType(kCCPositionTypeRelative);
	//ps->setColor(Color3B(255,7,12));
	ps->setPosition(0, this->getImg()->getContentSize().height / 2);
	this->getImg()->addChild(ps);
}

void FireBullet::attack_Animation()
{
	
}

void FireBullet::Hit_Animation(Zombie * zombie)
{
	std::cout << "火焰弹击中" << std::endl;
	////删除子弹
	Sprite*bulletSprite = this->getImg();
	bulletSprite->removeFromParent();
	for (int i = 0; i < readyBullet.size(); i++)
	{
		if (readyBullet.at(i) == this)
		{
			readyBullet.erase(readyBullet.begin() + i);
			break;
		}
	}
	ParticleSystem* ps = CCParticleFire::create();
	ps->setPosition(zombie->getImg()->getPosition());
	ps->setLife(1);
	ps->setStartSize(20);
	ps->setDuration(0.5);
	ps->setColor(Color3B(226, 17, 12));
	addLayer(ps);
}
