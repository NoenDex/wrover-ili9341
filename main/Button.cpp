#include "Button.h"

namespace TGUI
{
  void Button::update()
  {
    m_p2.set_x(m_p1.get_x() + m_width);
    m_p2.set_y(m_p1.get_y() + m_height);
  }

  void Button::paint(DrawingContext *context)
  {
    context->fill_rectangle(m_p1, m_p2, m_color);
  }

  void Button::set_coordinates(Point p1, Point p2)
  {
    m_p1 = p1;
    m_width = p2.get_x() - p1.get_x();
    m_height = p2.get_y() - p1.get_y();
    update();
  }

  void Button::set_dimensions(uint16_t w, uint16_t h)
  {
    m_height = h;
    m_width = w;
    update();
  }

} // namespace TGUI
