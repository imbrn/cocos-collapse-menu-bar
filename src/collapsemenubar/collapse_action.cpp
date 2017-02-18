#include "collapse_action.h"
#include "collapse_menu_bar.h"

namespace collapsemenubar {

CollapseAction::CollapseAction(CollapseMenuBar *collapse_menu_bar): collapse_menu_bar_(collapse_menu_bar) {
}

void CollapseAction::Show(float time) {
  float x = collapse_menu_bar_->getPositionX();
  float y = collapse_menu_bar_->getContentSize().height;
  if (time == 0) MoveInstantly(x, y);
  else MoveProgressively(x, y, time);
}

void CollapseAction::Hide(float time) {
  auto menu_bar = collapse_menu_bar_->get_menu_bar();
  float x = collapse_menu_bar_->getPositionX();
  float y = collapse_menu_bar_->getContentSize().height + menu_bar->getContentSize().height - 6;
  if (time == 0) MoveInstantly(x, y);
  else MoveProgressively(x, y, time);
}

void CollapseAction::MoveProgressively(float x, float y, float time) {
  auto menu_bar = collapse_menu_bar_->get_menu_bar();
  menu_bar->stopAllActions();
  auto animation = cocos2d::EaseCubicActionOut::create(cocos2d::MoveTo::create(time, {x, y}));
  menu_bar->runAction(animation);
}

void CollapseAction::MoveInstantly(float x, float y) {
  collapse_menu_bar_->get_menu_bar()->setPosition({x, y});
}

}
