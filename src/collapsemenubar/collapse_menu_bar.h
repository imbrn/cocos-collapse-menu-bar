#ifndef COLLAPSEMENUBAR_COLLAPSE_MENU_BAR_H
#define COLLAPSEMENUBAR_COLLAPSE_MENU_BAR_H

#include <cocos2d.h>
#include <ui/CocosGUI.h>
#include <menubar/menu_bar.h>
#include "gesture_container.h"
#include "collapse_action.h"

namespace collapsemenubar {

///
/// CollapseMenuBar class.
///
class CollapseMenuBar: public cocos2d::ui::Widget {
protected:
  CollapseMenuBar(menubar::MenuBar *menu_bar, float showing, float pinned);

public:
  static CollapseMenuBar *create(menubar::MenuBar *menu_bar, float showing = false, float pinned = false);
  virtual ~CollapseMenuBar() {}

  void ShowInstantly();
  void HideInstantly();
  void Show();
  void Hide();
  void Pin();
  void Unpin();

  menubar::MenuBar *get_menu_bar();
  bool is_showing() const;
  bool is_pinned() const;

protected:
  virtual bool init() override;

private:
  void DoInit();
  void FitScreen();
  void InitGestureContainer();
  void InitMenuBar();
  void ApplyInitialVisibility();

private:
  bool showing_;
  bool pinned_;
  menubar::MenuBar *menu_bar_ = nullptr;
  GestureContainer *gesture_container_ = nullptr;
  CollapseAction collapse_action_;
};

}

#endif
