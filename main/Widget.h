#pragma once

#include "DrawingContext.h"

namespace TGUI
{
  class Widget
  {
  public:
    Widget() {}
    virtual void update() {}
    virtual void paint(DrawingContext*) {}
  };

} // namespace TGUI
