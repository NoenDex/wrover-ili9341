#include "Point.h"

namespace TGUI
{

  Point::Point(int16_t x, int16_t y)
  {
    m_x = x;
    m_y = y;
  }

  void Point::set(int16_t x, int16_t y)
  {
    m_x = x;
    m_y = y;
  }

  void Point::set_x(int16_t x)
  {
    m_x = x;
  }

  void Point::set_y(int16_t y)
  {
    m_y = y;
  }

  void Point::resize_by(int16_t units)
  {
    m_x += units;
    m_y += units;
  }

  void Point::operator=(Point other)
  {
    m_x = other.m_x;
    m_y = other.m_y;
  }

} // namespace TGUI
