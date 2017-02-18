#include "collapse_menu_bar.h"

namespace collapsemenubar {

CollapseMenuBar::CollapseMenuBar(menubar::MenuBar *menu_bar, float showing, float pinned):
      menu_bar_(menu_bar),
      showing_(showing),
      pinned_(pinned),
      collapse_action_(this) {
}

CollapseMenuBar *CollapseMenuBar::create(menubar::MenuBar *menu_bar, float showing, float pinned) {
  CollapseMenuBar *obj = new CollapseMenuBar(menu_bar, showing, pinned);
  if (obj->init()) {
    obj->autorelease();
    return obj;
  } else {
    delete menu_bar;
    delete obj;
    return nullptr;
  }
}

bool CollapseMenuBar::init() {
  if (!cocos2d::ui::Widget::init()) {
    return false;
  }
  DoInit();
  return true;
}

void CollapseMenuBar::DoInit() {
  FitScreen();
  InitGestureContainer();
  InitMenuBar();
  ApplyInitialVisibility();
}

void CollapseMenuBar::FitScreen() {
  auto director = cocos2d::Director::getInstance();
  auto visible_area = director->getOpenGLView()->getVisibleRect();
  setAnchorPoint({0, 0});
  setPosition(visible_area.origin);
  setContentSize(visible_area.size);
}

void CollapseMenuBar::InitGestureContainer() {
  gesture_container_ = GestureContainer::create(this);
  addChild(gesture_container_);
}

void CollapseMenuBar::InitMenuBar() {
  menu_bar_->setAnchorPoint({0, 1});
  menu_bar_->setPosition({0, getContentSize().height});
  addChild(menu_bar_);
}

void CollapseMenuBar::ApplyInitialVisibility() {
  if (showing_ || pinned_) {
    ShowInstantly();
  } else {
    HideInstantly();
  }
}

void CollapseMenuBar::ShowInstantly() {
  showing_ = true;
  collapse_action_.Show();
}

void CollapseMenuBar::HideInstantly() {
  showing_ = false;
  collapse_action_.Hide();
}

void CollapseMenuBar::Show() {
  showing_ = true;
  collapse_action_.Show(0.15f);
}

void CollapseMenuBar::Hide() {
  if (!pinned_) {
    showing_ = false;
    collapse_action_.Hide(0.15f);
  }
}

void CollapseMenuBar::Pin() {
  pinned_ = true;
  ShowInstantly();
}

void CollapseMenuBar::Unpin() {
  pinned_ = false;
}

menubar::MenuBar *CollapseMenuBar::get_menu_bar() {
  return menu_bar_;
}

bool CollapseMenuBar::is_showing() const {
  return showing_;
}

bool CollapseMenuBar::is_pinned() const {
  return pinned_;
}

}
