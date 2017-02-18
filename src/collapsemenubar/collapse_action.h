#ifndef COLLAPSEMENUBAR_H
#define COLLAPSEMENUBAR_H

namespace collapsemenubar {

// Forward reference.
class CollapseMenuBar;

///
/// CollapseAction class.
///
class CollapseAction {
  CollapseMenuBar *collapse_menu_bar_ = nullptr;
  
public:
  CollapseAction(CollapseMenuBar *collapse_menu_bar);
  virtual ~CollapseAction() {}
  void Show(float time = 0);
  void Hide(float time = 0);

private:
  void MoveProgressively(float x, float y, float time);
  void MoveInstantly(float x, float y);
};

}

#endif
