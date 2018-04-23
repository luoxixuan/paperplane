#include "cocostudio/CocoStudio.h"
#include "cocostudio/ActionTimeline/CCActionTimeline.h"
#include "ui/UIHelper.h"
#include "MainScene.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "platform\android\jni/JniHelper.h"
#endif

USING_NS_CC;
using ui::Widget;

cocos2d::Scene * MainScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = MainScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool MainScene::init()
{
	if (!Layer::init())
	{
		return false;
	}
	scheduleUpdate();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//加载界面以及界面组件
	ui_root_prep = static_cast<ui::Widget*> (CSLoader::createNode("Anim_Prep.csb"));
	ui_root_prep->setVisible(true);
	ui_root_fly_0 = static_cast<ui::Widget*> (CSLoader::createNode("Anim_Fly_0.csb"));
	ui_root_fly_0->setVisible(false);
	ui_root_fly_1 = static_cast<ui::Widget*> (CSLoader::createNode("Anim_Fly_1.csb"));
	ui_root_fly_1->setVisible(false);
	ui_root_fly_2 = static_cast<ui::Widget*> (CSLoader::createNode("Anim_Fly_2.csb"));
	ui_root_fly_2->setVisible(false);
	ui_root_steam = static_cast<ui::Widget*> (CSLoader::createNode("Anim_Steam.csb"));
	ui_root_steam->setVisible(false);
	this->addChild(ui_root_prep, 1);
	this->addChild(ui_root_fly_0, 1);
	this->addChild(ui_root_fly_1, 1);
	this->addChild(ui_root_fly_2, 1);
	this->addChild(ui_root_steam, 1);

	Vec2 pos = Vec2(0.0, 0.0);
	Size sp_size = Size(360.0, 220.0);

	CCASSERT(ui_root_prep != nullptr, "ui_root Load Failed!");

	auto img_begin = ui::Helper::seekWidgetByName(ui_root_prep, "img_begin");
	img_begin->setVisible(true);
	img_begin->addTouchEventListener(CC_CALLBACK_2(MainScene::touchImgCallback, this));

	auto img_bk_prep = ui::Helper::seekWidgetByName(ui_root_prep, "img_bk");
	img_bk_prep->setVisible(true);
	img_bk_prep->addTouchEventListener(CC_CALLBACK_2(MainScene::touchImgCallback, this));

	auto img_bk_fly_0 = ui::Helper::seekWidgetByName(ui_root_fly_0, "img_bk");
	img_bk_fly_0->setVisible(true);
	img_bk_fly_0->addTouchEventListener(CC_CALLBACK_2(MainScene::touchImgCallback, this));

	auto img_bk_fly_1 = ui::Helper::seekWidgetByName(ui_root_fly_1, "img_bk");
	img_bk_fly_1->setVisible(true);
	img_bk_fly_1->addTouchEventListener(CC_CALLBACK_2(MainScene::touchImgCallback, this));

	auto img_bk_fly_2 = ui::Helper::seekWidgetByName(ui_root_fly_2, "img_bk");
	img_bk_fly_2->setVisible(true);
	img_bk_fly_2->addTouchEventListener(CC_CALLBACK_2(MainScene::touchImgCallback, this));

	auto img_bk_steam = ui::Helper::seekWidgetByName(ui_root_fly_2, "img_bk");
	img_bk_steam->setVisible(true);
	img_bk_steam->addTouchEventListener(CC_CALLBACK_2(MainScene::touchImgCallback, this));
	
	//auto *anim_prep = CSLoader::createTimeline("Anim_Prep.csb");
	//img_bk_prep->runAction(anim_prep);
	//播放准备动画
	//anim_prep->gotoFrameAndPlay(0, 100, false); //弄到全屏去

	//float scaleX = CC_CONTENT_SCALE_FACTOR();
	//ui_root->setScale(scaleX);
	
	return true;
}

void MainScene::onEnter()
{
	Layer::onEnter();
}

void MainScene::gameOver()
{
}

bool MainScene::onTouchBegan(Touch * touch, Event * unused_event)
{
	//startRecord();
	return false;
}
void MainScene::onTouchMoved(Touch * touch, Event * unused_event)
{

}
void MainScene::onTouchEnded(Touch * touch, Event * unused_event)
{
	//stopRecord();
	//setPlane(2);
}
void MainScene::onTouchCancelled(Touch * touch, Event * unused_event)
{
}

void MainScene::touchCardCallback(cocos2d::Ref * pSender, ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
	}
}

void MainScene::menuCloseCallback(cocos2d::Ref * pSender, ui::Widget::TouchEventType touchType)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void MainScene::changeSceneCallback(cocos2d::Ref * pSender, ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		auto director = Director::getInstance();
		auto scene = MainScene::createScene();

		director->replaceScene(scene);
	}
}

void MainScene::touchImgCallback(cocos2d::Ref* pSender, ui::Widget::TouchEventType touchType)
{
	if (touchType == ui::Widget::TouchEventType::BEGAN)
	{
		auto img_begin = ui::Helper::seekWidgetByName(ui_root_prep, "img_begin");
		img_begin->setVisible(false);
		m_counter = 0;
		if (m_isRecord)
		{
			return;
		}
		setPlane(0);
		int db = -3;
		db = startRecord();
	}
	if (touchType == ui::Widget::TouchEventType::ENDED)
	{
		auto img_begin = ui::Helper::seekWidgetByName(ui_root_prep, "img_begin");
		img_begin->setVisible(false);
		m_counter = 0;
		if (m_isRecord)
		{
			int db = -3;
			db = stopRecord();
			int fly = random(2, 4);
			/*
			if (m_maxDb > 80) //音量大
			{
				if (m_isFly)
				{
					return;
				}
				setPlane(fly); //2扔出去
			}
			*/
			if (m_isFly)
			{
				return;
			}
			//setPlane(fly); //2扔出去
			setPlane(1);
		}
	}
}

void MainScene::update(float dt)
{
	Layer::update(dt);
	CCCallFunc* act_fly;
	int fly_type = 0;
	if (m_isPrep)
	{
		m_counter++;
	}
	if (m_isPrep && m_counter > 100)
	{
		fly_type = random(1, 3);//本来准备根据哈气的声音响度值来设置飞行路径，现在取不到声音，随机来
		/*
		if (m_maxDb > 120)
		{
			fly_type = 1;
		}
		else if (m_maxDb > 100)
		{
			fly_type = 2;
		}
		else if (m_maxDb > 80)
		{
			fly_type = 3;
		}
		*/
		switch (fly_type)
		{
		case 1:
			act_fly = CCCallFunc::create(this, callfunc_selector(MainScene::fly_0));
			break;
		case 2:
			act_fly = CCCallFunc::create(this, callfunc_selector(MainScene::fly_1));
			break;
		case 3:
			act_fly = CCCallFunc::create(this, callfunc_selector(MainScene::fly_2));
			break;
		default:
			act_fly = CCCallFunc::create(this, callfunc_selector(MainScene::fly_0));
			break;
		}
		ui_root_prep->runAction(act_fly);
	}
	if (m_isRecord)
	{

		int db = -3;
		db = getVol(0);
		
		/*
		if (m_maxDb < db)
		{
			m_maxDb = db; //记录声音最大值
		}
		*/
		return;
	}
}

void MainScene::prep()
{
}

void MainScene::fly_0()
{
	auto *anim_fly_0 = CSLoader::createTimeline("Anim_Fly_0.csb");
	ui_root_fly_0->setVisible(true);
	ui_root_fly_1->setVisible(false);
	ui_root_fly_2->setVisible(false);
	ui_root_prep->setVisible(false);
	ui_root_steam->setVisible(false);
	ui_root_fly_0->runAction(anim_fly_0);
	anim_fly_0->gotoFrameAndPlay(0, 200, false);
	m_isFly = true;
	m_isPrep = false;
}

void MainScene::fly_1()
{
	auto *anim_fly_1 = CSLoader::createTimeline("Anim_Fly_1.csb");
	ui_root_fly_0->setVisible(true);
	ui_root_fly_1->setVisible(true);
	ui_root_fly_2->setVisible(false);
	ui_root_prep->setVisible(false);
	ui_root_steam->setVisible(false);
	ui_root_fly_1->runAction(anim_fly_1);
	anim_fly_1->gotoFrameAndPlay(0, 200, false);
	m_isFly = true;
	m_isPrep = false;
}

void MainScene::fly_2()
{
	auto *anim_fly_2 = CSLoader::createTimeline("Anim_Fly_2.csb");
	ui_root_fly_0->setVisible(false);
	ui_root_fly_1->setVisible(false);
	ui_root_fly_2->setVisible(true);
	ui_root_prep->setVisible(false);
	ui_root_steam->setVisible(false);
	ui_root_fly_2->runAction(anim_fly_2);
	anim_fly_2->gotoFrameAndPlay(0, 200, false);
	m_isFly = true;
	m_isPrep = false;
}

bool MainScene::setPlane(int state)
{
	auto *anim_steam = CSLoader::createTimeline("Anim_Steam.csb");
	auto *anim_prep = CSLoader::createTimeline("Anim_Prep.csb");
	auto *anim_fly_0 = CSLoader::createTimeline("Anim_Fly_0.csb");
	auto *anim_fly_1 = CSLoader::createTimeline("Anim_Fly_1.csb");
	auto *anim_fly_2 = CSLoader::createTimeline("Anim_Fly_2.csb");
	/*
	CCCallFunc* act_prep = CCCallFunc::create(this, callfunc_selector(MainScene::prep));
	CCCallFunc* act_fly; 
	CCSequence *prep_fly;
	*/
	switch (state)
	{
	case 0:
		m_isFly = false;
		m_isPrep = false;
		ui_root_fly_0->setVisible(false);
		ui_root_fly_1->setVisible(false);
		ui_root_fly_2->setVisible(false);
		ui_root_prep->setVisible(false);
		ui_root_steam->setVisible(true);
		ui_root_steam->runAction(anim_steam);
		anim_steam->gotoFrameAndPlay(0, 50, false);
		break;
	case 1:
		ui_root_fly_0->setVisible(false);
		ui_root_fly_1->setVisible(false);
		ui_root_fly_2->setVisible(false);
		ui_root_prep->setVisible(true);
		ui_root_steam->setVisible(false);
		ui_root_prep->runAction(anim_prep);
		anim_prep->gotoFrameAndPlay(0, 100, false);
		m_isPrep = true;
		m_isFly = false;
		break;
		/*
	case 2:
		ui_root_fly_0->setVisible(true);
		ui_root_fly_1->setVisible(false);
		ui_root_fly_2->setVisible(false);
		ui_root_prep->setVisible(false);
		ui_root_steam->setVisible(false);
		ui_root_fly_0->runAction(anim_fly_0);
		anim_fly_0->gotoFrameAndPlay(0, 200, false);
		m_isFly = true;
		m_isPrep = false;
		break;
	case 3:
		ui_root_fly_0->setVisible(false);
		ui_root_fly_1->setVisible(true);
		ui_root_fly_2->setVisible(false);
		ui_root_prep->setVisible(false);
		ui_root_steam->setVisible(false);
		ui_root_fly_1->runAction(anim_fly_1);
		anim_fly_1->gotoFrameAndPlay(0, 200, false);
		m_isFly = true;
		m_isPrep = false;
		break;
	case 4:
		ui_root_fly_0->setVisible(false);
		ui_root_fly_1->setVisible(false);
		ui_root_fly_2->setVisible(true);
		ui_root_prep->setVisible(false);
		ui_root_steam->setVisible(false);
		ui_root_fly_2->runAction(anim_fly_2);
		anim_fly_2->gotoFrameAndPlay(0, 160, false);
		m_isFly = true;
		m_isPrep = false;
		break;
		*/
	default:
		break;
	}
	//int db = 0;
	auto img_begin = ui::Helper::seekWidgetByName(ui_root_prep, "img_begin");
	img_begin->setVisible(false);
	return true;
}

int MainScene::getVol(int max)
{
	srand(unsigned(time(0)));
	if (!m_isRecord)
	{
		return -1;
	}
	int v = -2;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	//m_counter++;
	v = random(0, m_counter);
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
		"org/cocos2dx/cpp/JniRecorder",  //类的路径
		"jniGetVol",   //方法名
		"(I)I");   //括号里的是参数，后面的是返回值
	
	v = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID, max);
#endif
	return v;
}

int MainScene::startRecord()
{
	int l = 0; 
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_isRecord = true;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
		"org/cocos2dx/cpp/JniRecorder",  //类的路径
		"jniStartRecord",   //方法名
		"()I");   //括号里的是参数，后面的是返回值
	
	l = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
	m_isRecord = true;
#endif
	return l;
}

int MainScene::stopRecord()
{
	int l = 0;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	m_isRecord = false;
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	JniMethodInfo minfo;//定义Jni函数信息结构体
	bool isHave = JniHelper::getStaticMethodInfo(minfo,
		"org/cocos2dx/cpp/JniRecorder",  //类的路径
		"jniStopRecord",   //方法名
		"()I");   //括号里的是参数，后面的是返回值

	l = minfo.env->CallStaticIntMethod(minfo.classID, minfo.methodID);
	m_isRecord = false;
#endif
	return l;
}


