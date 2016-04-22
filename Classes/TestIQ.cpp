#include"HelloScene.h"

Scene* TestIQ::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = TestIQ::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool TestIQ::init()
{
	if (!LayerColor::initWithColor(Color4B(30, 30, 30, 255)))
	{
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Test = Sprite::createWithSpriteFrameName("testiq.png");
	Test->setPosition(310, visibleSize.height - 154);
	addChild(Test, 1);

	Dian = Sprite::createWithSpriteFrameName("dian1.png");
	Dian->setPosition(310 + Test->getContentSize().width / 2 + 72, visibleSize.height - 168);
	addChild(Dian, 2);


	SpriteFrameCache *frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("dian.plist", "dian.png");
	Animation *animation = AnimationUtil::createWithSingleFrameName("dian", 0.8f, -1);
	Dian->runAction(Animate::create(animation));

	scheduleOnce(schedule_selector(TestIQ::my_update), 5.0);
	return true;
}
void TestIQ::my_update(float dt)
{
	srand(time(NULL));

	Dian->stopAllActions();
	Dian-> setVisible(false);	
	this->removeChild(Dian, false);

	Test->setSpriteFrame("testdone.png");
	Test->setPosition(400,240);

	Label *IQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 80);
	int iq = rand() % 10 + 60;
	//int iq = 60;
	UserDefault::getInstance()->setIntegerForKey("IQ",iq);
	IQ->setString(Value(iq).asString());
	IQ->setPosition(470,330);
	addChild(IQ,2);

	scheduleOnce(schedule_selector(TestIQ::my_update2), 4.0);

}
void TestIQ::my_update2(float dt)
{
	Director::getInstance()->replaceScene(HelloScene::createScene());
}