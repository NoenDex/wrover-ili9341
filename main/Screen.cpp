#include "Screen.h"
#include <algorithm>
#include <memory>

namespace TGUI
{
  Screen::Screen(TFT_t *device){
    context = DrawingContext(device);
  }

  void Screen::clear(uint16_t color)
  {
    context.fill_screen(color);
  }

  void Screen::add_widget(Widget *widget)
  {
    m_widgets.push_back(widget);
  }

  void Screen::update()
  {
    if (m_widgets.size() == 0)
      return;

    for(auto& widget: m_widgets)
      {
//        widget->update();
        widget->paint(&context);
      }
  }
} // namespace TGUI
