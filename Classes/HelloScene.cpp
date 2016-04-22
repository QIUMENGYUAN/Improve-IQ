#include"HelloScene.h"

Scene* HelloScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelloScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	//
	// return the scene
	return scene;
}
  
// on "init" you need to initialize your instance
bool HelloScene::init()
{

	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	IQ = Label::createWithTTF("", "fonts/Futura (Light).ttf", 86);
	IQ->setString("IQ:" + Value(UserDefault::getInstance()->getIntegerForKey("IQ")).asString());
	IQ->setColor(Color3B(214, 215, 250));
	IQ->setPosition(220, 280);
	IQ->setVisible(false);
	
	addChild(IQ, 2);
	
	BackGround = Sprite::create("b6.png");
	BackGround->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	BackGround->setVisible(false);
	addChild(BackGround, 0);

	Home = Sprite::createWithSpriteFrameName("home.png");
	Home->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	Home->setVisible(false);
	addChild(Home, 1);

	Start = Sprite::createWithSpriteFrameName("start1.png");
	Start->setAnchorPoint(Point(0,0));
	Start->setPosition(516, visibleSize.height- 334-53);
	Start->setVisible(false);
	addChild(Start, 2);



	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = [=](Touch* touch, Event* event)
	{
		if (Start->getBoundingBox().containsPoint(touch->getLocation()))
		{
			Director::getInstance()->replaceScene(LevelSelect::createScene());
		}
		return true;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	if (!UserDefault::getInstance()->getIntegerForKey("IQ", 0))
		scheduleOnce(schedule_selector(HelloScene::my_update), 0.0);
	else
	{
		IQ->setVisible(true);
		BackGround->setVisible(true);
		Start->setVisible(true);
		Home->setVisible(true);
	}

	setKeyboardEnabled(true);
	auto BacklListener = EventListenerKeyboard::create();
	BacklListener->onKeyReleased = CC_CALLBACK_2(HelloScene::onKeyReleased, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(BacklListener, this);

	return true;
}
void HelloScene::my_update(float dt)
{
	Director::getInstance()->replaceScene(TestIQ::createScene());
}
void HelloScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event * pEvent)
{
	Director::getInstance()->end();
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		exit(0);
	#endif
}