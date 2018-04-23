#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class MainScene : public cocos2d::Layer
{
public:
	// there's no 'id' in cpp, so we recommend returning the class instance pointer
	static cocos2d::Scene* createScene();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();

	virtual void onEnter();

	virtual void update(float dt);

	// implement the "static create()" method manually
	CREATE_FUNC(MainScene);
private:
	void gameOver();
	/*
	bool onSpriteTouchBegan(Touch* tTouch,Event* eEvent);//手指按下事件
	void onSpriteTouchMoved(Touch* tTouch,Event* eEvent);//手指移动事件
	void onSpriteTouchEnded(Touch* tTouch,Event* eEvent);//手指离开事件

	void addTouchListenerForSprite(Sprite *sprte);
	*/
	virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	virtual void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *unused_event);

	// callback
	void touchCardCallback(cocos2d::Ref * pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void menuCloseCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void changeSceneCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType touchType);
	void touchImgCallback(cocos2d::Ref* pSender, cocos2d::ui::Widget::TouchEventType touchType);

	bool setPlane(int type);

	int getVol(int max);
	int startRecord();
	int stopRecord();
	void fly_0();
	void fly_1();
	void fly_2();
	void prep();

private:
	//命名规范，界面资源用匈牙利命名法，其他用驼峰命名法
	cocos2d::ui::Widget* ui_root_prep = nullptr;
	cocos2d::ui::Widget* ui_root_fly_0 = nullptr;
	cocos2d::ui::Widget* ui_root_fly_1 = nullptr;
	cocos2d::ui::Widget* ui_root_fly_2 = nullptr;
	cocos2d::ui::Widget* ui_root_steam = nullptr;
	//cocos2d::Sprite* sp_plane = nullptr;
	//cocos2d::ui::Text *lbl_vol = nullptr;

	bool m_isRecord = false;
	bool m_isFly = false;
	bool m_isPrep = false;
	int m_maxDb = 0;
	int m_counter = 0;
};
#endif // __GAME_SCENE_H__