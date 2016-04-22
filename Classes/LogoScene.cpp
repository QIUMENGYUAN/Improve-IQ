#include"LogoScene.h"
Scene* LogoScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = LogoScene::create();

	// add layer as a child to scene
	scene->addChild(layer);
	//
	// return the scene
	return scene;
}

bool LogoScene::init()
{
	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile("all.plist","all.png");

	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto BackGround = Sprite::createWithSpriteFrameName("logo.png");
	BackGround->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	addChild(BackGround, 0);
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sound1.mp3", false);
	scheduleOnce(schedule_selector(LogoScene::my_update), 2.0);

	return true;
}
void LogoScene::my_update(float dt)
{
	Scene *scene;

	if (!UserDefault::getInstance()->getIntegerForKey("IQ", 0))
		scene = TransitionFade::create(2.6, TestIQ::createScene());
	else
		scene = TransitionFade::create(2.6, HelloScene::createScene());

	Director::getInstance()->replaceScene(scene);
}