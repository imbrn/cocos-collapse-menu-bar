#include "collapse_action.h"
#include "collapse_menu_bar.h"

namespace collapsemenubar {

CollapseAction::CollapseAction(CollapseMenuBar *collapse_menu_bar): collapse_menu_bar_(collapse_menu_bar) {
}

void CollapseAction::Show(float time) {
  collapse_menu_bar_->get_menu_bar()->stopAllActions();
  float x = collapse_menu_bar_->getPositionX();
  float y = collapse_menu_bar_->getContentSize().height;
  auto animation = cocos2d::EaseCubicActionOut::create(cocos2d::MoveTo::create(0.25f, {x, y}));
  collapse_menu_bar_->get_menu_bar()->runAction(animation);
}

void CollapseAction::Hide(float time) {
  auto menu_bar = collapse_menu_bar_->get_menu_bar();
  menu_bar->stopAllActions();
  float x = collapse_menu_bar_->getPositionX();
  float y = collapse_menu_bar_->getContentSize().height + menu_bar->getContentSize().height - 6;
  auto animation = cocos2d::EaseCubicActionOut::create(cocos2d::MoveTo::create(time, {x, y}));
  menu_bar->runAction(animation);
}

}
