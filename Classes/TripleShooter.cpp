#include "TripleShooter.h"
#include "TripleBullet.h"
#include "Global.h"
TripleShooter::TripleShooter(Point position, int row)
{
	this->setRow(row);
	Sprite*sp = Sprite::create("TripleShooter.png");
	this->setImg(sp);
	//一定要retain，否则会自动释放
	sp->retain();
	sp->setScale(0.3);
	sp->setPosition(position);
	this->setHp(6);
	this->setInterval(2000);
	//普通植物直接播放自身动画
	this->Self_Animation();
	//添加到植物层
	addLayer(sp);
	//添加到已创建植物容器，其他行为操作都在此处
	readyPlants.push_back(this);
}

bool TripleShooter::isWorking()
{
	return true;
}

void TripleShooter::work()
{
	if(isWorking())
	CreateBullet();
}

void TripleShooter::Die()
{
}

void TripleShooter::CreateBullet()
{
	CCScaleBy * scaleup = CCScaleBy::create(0.07f, 0.8f, 1.25f);
	CCScaleBy * scaledown = CCScaleBy::create(0.2f, 1.5625f, 0.64f);
	CCScaleBy * scaleup1 = CCScaleBy::create(0.1f, 0.8f, 1.25f);
	Sequence *sequence = Sequence::create(scaleup, scaledown, scaleup1, NULL);
	this->getImg()->runAction(sequence);
	Sprite *sp = this->getImg();
	//植物中心点X坐标，植物中心点+1/4植物高度的Y坐标
	Point a = ccp(sp->getPositionX(), sp->getContentSize().height*sp->getScaleY() / 4 + sp->getPositionY());
	Bullet *pb = new TripleBullet(a, this->getRow(),1);
	Bullet *pb1 = new TripleBullet(a, this->getRow(), 2);
	Bullet *pb2 = new TripleBullet(a, this->getRow(), 3);
	setNewBirthTime();
}
