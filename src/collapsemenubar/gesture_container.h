#ifndef COLLAPSEMENUBAR_GESTURE_CONTAINER_H
#define COLLAPSEMENUBAR_GESTURE_CONTAINER_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <functional>
#include <menubar/menu_bar.h>

namespace collapsemenubar {

// Forward reference.
class CollapseMenuBar;

///
/// GestureContainer class.
///
class GestureContainer: public cocos2d::ui::Widget {
protected:
  GestureContainer(CollapseMenuBar *collapse_menu_bar);

public:
  static GestureContainer *create(CollapseMenuBar *collapse_menu_bar);
  virtual ~GestureContainer() {}

  CollapseMenuBar *get_collapse_menu_bar();

protected:
  virtual bool init() override;

private:
  void DoInit();
  void FitScreen();
  void InitGestures();

  void CreateTouchListener();
  void RegisterTouchListener();
  bool OnTouchBegan(cocos2d::Touch *t);

  bool ShouldShow(const cocos2d::Vec2 &touch_point) const;
  bool ShouldHide(const cocos2d::Vec2 &touch_point) const;

  void ShowMenu();
  void HideMenu();

  bool IsShowing() const;
  bool IsHide() const;
  bool IsShowingArea(const cocos2d::Vec2 &point) const;
  bool IsHideArea(const cocos2d::Vec2 &point) const;

private:
  CollapseMenuBar *collapse_menu_bar_ = nullptr;
  cocos2d::EventListenerTouchOneByOne *touch_listener_ = nullptr;
  
};

}

#endif
