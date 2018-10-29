#include "NutPlus.h"
#include "Global.h"

NutPlus::NutPlus(Point position, int row,int col)
{
	this->setRow(row);
	this->setCol(col);
	Sprite*sp = Sprite::create("Nut2.png");
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.4);
	sp->setPosition(position);
	this->setHp(25);
	this->setInterval(0);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

NutPlus::NutPlus()
{
}
void NutPlus::Attacked()
{
	Sprite *sp = this->getImg();
	Director::getInstance()->getActionManager()->removeAllActionsFromTarget(sp);
	float preScale = sp->getScaleX();
	CCActionInterval * tintto1 = CCTintTo::create(0.2, 255, 0, 0);
	CCActionInterval * tintto2 = CCTintTo::create(0.2, 255, 255, 255);
	Sequence *sequence = Sequence::create(tintto1, tintto2, NULL);
	sp->runAction(sequence);
	if (this->getHp() == 20)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("NutPlus\\Attacked\\1.png"));
		sprite->setPosition(this->getImg()->getPosition());
		sprite->setScaleX(this->getImg()->getScaleX());
		sprite->setScaleY(this->getImg()->getScaleY());
		this->getImg()->removeFromParent();
		this->setImg(sprite);
		addLayer(sprite);
	}
	else if (this->getHp() == 15)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("NutPlus\\Attacked\\1.png"));
		sprite->setPosition(this->getImg()->getPosition());
		sprite->setScaleX(this->getImg()->getScaleX());
		sprite->setScaleY(this->getImg()->getScaleY());
		this->getImg()->removeFromParent();
		this->setImg(sprite);
		addLayer(sprite);
	}
	else if (this->getHp() == 12)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("NutPlus\\Attacked\\2.png"));
		sprite->setPosition(this->getImg()->getPosition());
		sprite->setScaleX(this->getImg()->getScaleX());
		sprite->setScaleY(this->getImg()->getScaleY());
		this->getImg()->removeFromParent();
		this->setImg(sprite);
		addLayer(sprite);
	}
	else if (this->getHp() == 10)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("NutPlus\\Attacked\\3.png"));
		sprite->setPosition(this->getImg()->getPosition());
		sprite->setScaleX(this->getImg()->getScaleX());
		sprite->setScaleY(this->getImg()->getScaleY());
		this->getImg()->removeFromParent();
		this->setImg(sprite);
		addLayer(sprite);
	}
	else if (this->getHp() == 5)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("NutPlus\\Attacked\\4.png"));
		sprite->setPosition(this->getImg()->getPosition());
		sprite->setScaleX(this->getImg()->getScaleX());
		sprite->setScaleY(this->getImg()->getScaleY());
		this->getImg()->removeFromParent();
		this->setImg(sprite);
		addLayer(sprite);
	}
	else if (this->getHp() == 3)
	{
		auto sprite = Sprite::createWithTexture(TextureCache::getInstance()->addImage("NutPlus\\Attacked\\5.png"));
		sprite->setPosition(this->getImg()->getPosition());
		sprite->setScaleX(this->getImg()->getScaleX());
		sprite->setScaleY(this->getImg()->getScaleY());
		this->getImg()->removeFromParent();
		this->setImg(sprite);
		addLayer(sprite);
	}
}

