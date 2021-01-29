#include "Screen.h"
#include <algorithm>
#include <memory>

namespace TGUI
{
  Screen::Screen(TFT_t *device)
  {
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

  void Screen::load_font(const char *font_path)
  {
    m_font = new FontPSF1(font_path, &context);
  }

  void Screen::draw_char(char c, Point p, uint16_t color)
  {
    m_font->draw_char(c, p, color);
  }

  void Screen::draw_text(const char *text, Point p, uint16_t color)
  {
    m_font->draw_text(text, p, color);
  }

  void Screen::update()
  {
    if (m_widgets.size() == 0)
      return;

    for (auto &widget : m_widgets)
    {
      //        widget->update();
      widget->paint(&context);
    }
  }

  Screen::~Screen()
  {
    delete (m_font);
  }

} // namespace TGUI
