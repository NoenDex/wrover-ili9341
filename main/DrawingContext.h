#pragma once

extern "C"
{
#include "bmpfile.h"
#include "decode_image.h"
#include "ili9340.h"
#include "pngle.h"
#include "dac_init.h"
}

#include "Point.h"

namespace TGUI
{

  class DrawingContext
  {
  public:
    DrawingContext() {}
    DrawingContext(TFT_t *device)
    {
      m_dev = device;
    }
    void put_pixel(Point p, uint16_t color);
    void rectangle(Point p1, Point p2, uint16_t color);
    void fill_rectangle(Point p1, Point p2, uint16_t color);
    void fill_screen(uint16_t color = BLACK);
    void line(Point p1, Point p2, uint16_t color);
    void circle(Point center, uint16_t radius, uint16_t color);

    uint16_t rgb565(uint16_t r, uint16_t g, uint16_t b);

  private:
    TFT_t *m_dev{nullptr};
  };

} // namespace TGUI
