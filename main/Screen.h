#pragma once

#include "Widget.h"
#include "Point.h"
#include "DrawingContext.h"
#include <vector>
#include <memory>

extern "C" {
#include "ili9340.h"
}

namespace TGUI
{
  class Screen
  {
  public:
    Screen(TFT_t *device);
    void clear(uint16_t color = 0x00);
    void add_widget(Widget *widget);
    size_t widgets_count() { return m_widgets.size();}
    void update();
    DrawingContext get_context() const { return context; }
  private:
    std::vector<Widget*> m_widgets;
    DrawingContext context;
  };

} // namespace TGUI
