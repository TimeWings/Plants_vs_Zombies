#include "Zomboni.h"
#include "Global.h"
Vector<Sprite*> Zomboni::IceSprite;
Zomboni::Zomboni()
{
}

Zomboni::Zomboni(Point position, int row, int col)
{
	this->setRow(row);
	this->setCol(col);
	this->setEquip(nullptr);
	setWalkSpeed(8);
	setHp(14);
	setHead(true);
	setMeeting(false);
	setInterval(100);
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Card\\Zomboni.png"));
	this->setSche(sp);
	this->setImg(sp);
	sp->retain();
	sp->setScale(2);
	sp->setPosition(position);
	this->Move();
	addLayer(sp);
	readyZombies.push_back(this);
}
void Zomboni::work()
{
	Check_Attack();
	ProductIce(Vec2(this->getImg()->getPositionX()+20,map::Rank2Point(this->getRow(),this->getCol()).y));
}
void Zomboni::Check_Attack()
{
	for (auto x : readyPlants)
	{
		if (this->getRow() == x->getRow() && this->getImg()->boundingBox().intersectsRect(x->getImg()->getBoundingBox()))
		{
			PlantStatus* plantstatus = map::find(x->getRow(),x->getCol());
			if (plantstatus != NULL)
			{
				DamagePlant(plantstatus);
			}
		}
	}
}
void Zomboni::Attack(PlantStatus * plantstatus)
{

}

void Zomboni::Die(Node * pSender)
{
	Sprite *sp = this->getImg();
	sp->getActionManager()->removeAllActionsFromTarget(sp);
	for (unsigned i = 0; i < readyZombies.size(); i++)
	{
		if (readyZombies.at(i) == this)
		{
			readyZombies.erase(readyZombies.begin() + i);
			break;
		}
	}
	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	for (int i = 1; i <= 7; i++)
	{
		sprintf(str, "Zombies\\Zomboni\\Death\\%d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.1);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zomboni::clear, this));
	Sequence *sequence = Sequence::create(Animate::create(an), actionDone, NULL);
	sp->runAction(sequence);
}

void Zomboni::Attacked()
{
	Sprite* sp = this->getImg();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
}

void Zomboni::LostHead()
{
	Die(this->getImg());
	return;
}

void Zomboni::Move()
{
	Stop_Animation();
	Sprite *sp = this->getImg();
	float distance = sp->getPositionX() + sp->getContentSize().width / 2 * sp->getScaleX();
	double time = distance / getPreWalkSpeed();
	Point a = ccp(-sp->getContentSize().width / 2 * sp->getScaleX(), sp->getPositionY());
	MoveTo *moveTo = MoveTo::create(time, a);
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(Zomboni::Die, this));

	Vector<SpriteFrame*> allframe;
	char str[100] = { 0 };
	for (int i = 1; i <= 12; i++)
	{
		sprintf(str, "Zombies\\Zomboni\\Self_Animation\\%02d.png", i);
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage(str));
		auto frame = sprite->getSpriteFrame();
		allframe.pushBack(frame);
	}
	Animation* an = Animation::createWithSpriteFrames(allframe, 0.03);
	CCSequence *sequence = CCSequence::create(moveTo, actionDone, NULL);
	sequence->setTag(Animation_Tag);
	sp->runAction(sequence);
	RepeatForever* re = RepeatForever::create(Animate::create(an));
	re->setTag(Animation_Tag);
	sp->runAction(re);

}
void Zomboni::ProductIce(Point position)
{
	Sprite* sp = Sprite::createWithTexture(TextureCache::getInstance()->addImage("Zombies\\Zomboni\\Ice.png"));
	sp->setPosition(position);
	sp->setScaleX(4);
	sp->setScaleY(2.8);
	if (!Check_Ice(sp))
	{
		return;
	}
	//std::cout << "制冰成功"<<std::endl;
	EntityLayer* zl = EntityLayer::getInstance();
	zl->addChild(sp, 0);
	IceSprite.pushBack(sp);
	PlantStatus* plantstatus = map::find(map::Point2Rank(position).first, map::Point2Rank(position).second);
	if (plantstatus != NULL)
	{
		plantstatus->Enabled = false;
	}
}
bool Zomboni::Check_Ice(Sprite* sp)
{
	for (auto x : IceSprite)
	{
		if (map::Point2Rank(x->getPosition()).first != map::Point2Rank(sp->getPosition()).first)
		{
			continue;
		}
		if (fabs(sp->getPositionX()-x->getPositionX())<sp->getContentSize().width)
		{
			//std::cout << "已经有冰，不能制冰" << std::endl;
			return false;
		}
	}
	return true;
}
void Zomboni::DamageZombie(int damage)
{
	setHp(getHp() - damage);
	Attacked();
}

void Zomboni::DamageEquip(int damage)
{
	DamageZombie(damage);
}

void Zomboni::DamageBoth(int damage)
{
	DamageZombie(damage);
}

Sprite * Zomboni::MagnetEquip()
{
	return nullptr;
}

void Zomboni::DamagePlant(PlantStatus * plantstatus)
{
	if (plantstatus->plantVector.size() == 0 || strcmp(typeid(*(plantstatus->plantVector.at(0))).name(), "class Lucker") == 0 || strcmp(typeid(*(plantstatus->plantVector.at(0))).name(), "class Tomb") == 0) {
		this->Move();
		this->setMeeting(false);
		return;
	}
	for (int i = 0; i < plantstatus->plantVector.size(); i++)
	{
		Press(plantstatus->plantVector.at(i));
		plantstatus->plantVector.erase(plantstatus->plantVector.begin() + i);
		i--;
	}
}
void Zomboni::Press(Plants* plant)
{
	std::cout << "压死！！！" << std::endl; 
	plant->getImg()->getActionManager()->removeAllActionsFromTarget(plant->getImg());
	float preScale = plant->getImg()->getScaleX();
	//压扁
	CCScaleBy * scaleupx_ZB = CCScaleBy::create(0.4f, 3, 0.01);
	//僵尸位置稍微下坠
	MoveTo *moveTo = MoveTo::create(0.5, ccp(plant->getImg()->getPositionX(), plant->getImg()->getPositionY() - 20));
	//合成队列
	CCFiniteTimeAction * spawn = CCSpawn::create(scaleupx_ZB, moveTo, NULL);
	auto actionDone1 = CallFuncN::create(CC_CALLBACK_1(Zomboni::clearPlant, this, plant));
	Sequence *sequence = Sequence::create(spawn, actionDone1, NULL);
	plant->getImg()->runAction(sequence);
}
void Zomboni::clearPlant(Node* pSender,Plants* plant)
{
	plant->Die();
}

void Zomboni::clear(Node* pSender) 
{
	pSender->removeFromParent();
	pSender->removeAllChildrenWithCleanup(true);
}
