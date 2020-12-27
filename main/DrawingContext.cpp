#include "DrawingContext.h"

namespace TGUI {

  void DrawingContext::rectangle(Point p1, Point p2, uint16_t color)
  {
    assert(m_dev!=nullptr);
    lcdDrawRect(m_dev, p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y(), color);
  }

  void DrawingContext::fill_rectangle(Point p1, Point p2, uint16_t color)
  {
    assert(m_dev!=nullptr);
    lcdDrawFillRect(m_dev, p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y(), color);
  }

  void DrawingContext::fill_screen(uint16_t color)
  {
    assert(m_dev!=nullptr);
    lcdFillScreen(m_dev, color);
  }

  void DrawingContext::line(Point p1, Point p2, uint16_t color)
  {
    assert(m_dev!=nullptr);
    lcdDrawLine(m_dev, p1.get_x(), p1.get_y(), p2.get_x(), p2.get_y(), color);
  }

  void DrawingContext::circle(Point center, uint16_t radius, uint16_t color)
  {
    assert(m_dev!=nullptr);
    lcdDrawCircle(m_dev, center.get_x(), center.get_y(), radius, color);
  }

  uint16_t DrawingContext::rgb565(uint16_t r, uint16_t g, uint16_t b)
  {
    return rgb565_conv(r, g, b);
  }

}
