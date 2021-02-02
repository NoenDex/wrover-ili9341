#pragma once

#include "Widget.h"
#include "Point.h"
#include "FontPSF1.h"
#include "FontPSF2.h"
#include "DrawingContext.h"
#include <vector>
#include <memory>

extern "C"
{
#include "ili9340.h"
}

namespace TGUI
{

  class Screen
  {
  public:
    Screen(TFT_t *device);
    ~Screen();
   
    void clear(uint16_t color = 0x00);
    void add_widget(Widget *widget);
    void load_font(const char *font_path);
    void draw_char(const char, Point, uint16_t color);
    void draw_text(const char*, Point, uint16_t color);
    size_t widgets_count() { return m_widgets.size(); }
    void update();
    DrawingContext get_context() const { return context; }

  private:
    bool is_PSF1_font(const char *font_path);
    bool is_PSF2_font(const char *font_path);

    std::vector<Widget *> m_widgets;
    DrawingContext context;
    Font *m_font;
  };

} // namespace TGUI
