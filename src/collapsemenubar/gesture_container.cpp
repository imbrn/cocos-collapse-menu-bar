#include "gesture_container.h"
#include "collapse_menu_bar.h"

namespace collapsemenubar {

GestureContainer::GestureContainer(CollapseMenuBar *collapse_menu_bar):
      collapse_menu_bar_(collapse_menu_bar) {
}

GestureContainer *GestureContainer::create(CollapseMenuBar *collapse_menu_bar) {
  GestureContainer *obj = new GestureContainer(collapse_menu_bar);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete obj;
    return nullptr;
  }
}

bool GestureContainer::init() {
  if (!cocos2d::ui::Widget::init()) {
    return false;
  }
  DoInit();
  return true;
}

void GestureContainer::DoInit() {
  FitScreen();
  CreateTouchListener();
  RegisterTouchListener();
}

void GestureContainer::FitScreen() {
  auto director = cocos2d::Director::getInstance();
  auto visible_area = director->getOpenGLView()->getVisibleRect();
  setContentSize(visible_area.size);
  setAnchorPoint({0, 0});
  setPosition(visible_area.origin);
}

void GestureContainer::CreateTouchListener() {
  touch_listener_ = cocos2d::EventListenerTouchOneByOne::create();
  touch_listener_->onTouchBegan = [this](cocos2d::Touch *t, cocos2d::Event *e) { return OnTouchBegan(t); };
}

void GestureContainer::RegisterTouchListener() {
  getEventDispatcher()->addEventListenerWithSceneGraphPriority(touch_listener_, this);
}

bool GestureContainer::OnTouchBegan(cocos2d::Touch *t) {
  if (ShouldShow(t->getLocation())) {
    ShowMenu();
  } else if (ShouldHide(t->getLocation())) {
    HideMenu();
  }
  return false;
}

void GestureContainer::ShowMenu() {
  collapse_menu_bar_->Show();
}

void GestureContainer::HideMenu() {
  collapse_menu_bar_->Hide();
}

bool GestureContainer::ShouldShow(const cocos2d::Vec2 &touch_point) const {
  return IsHide() && IsShowingArea(touch_point);
}

bool GestureContainer::ShouldHide(const cocos2d::Vec2 &touch_point) const {
  return IsShowing() && IsHideArea(touch_point);
}

bool GestureContainer::IsShowing() const {
  return collapse_menu_bar_->is_showing();
}

bool GestureContainer::IsHide() const {
  return !IsShowing();
}

bool GestureContainer::IsShowingArea(const cocos2d::Vec2 &point) const {
  return point.y >= getContentSize().height - 50;
}

bool GestureContainer::IsHideArea(const cocos2d::Vec2 &point) const {
  auto box = collapse_menu_bar_->get_menu_bar()->getBoundingBox();
  if (box.containsPoint(point)) {
    return false;
  } else {
    return true;
  }
}

CollapseMenuBar *GestureContainer::get_collapse_menu_bar() {
  return collapse_menu_bar_;
}

}
