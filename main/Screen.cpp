#include "Screen.h"
#include <algorithm>
#include <memory>
#include "esp_log.h"

static const char *TAG = "Screen";

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

  bool Screen::is_PSF1_font(const char *font_path)
  {
    unsigned char magic[2];
    FILE *font_file;
    font_file = fopen(font_path, "rb");
    if (!font_file)
    {
      ESP_LOGE(TAG, "\"%s\" could not be opened!", font_path);
      return false;
    }
    if (!fread((char *)&magic, sizeof(char), 2, font_file))
    {
      ESP_LOGE(TAG, "Reading font header failed");
      fclose(font_file);
      return false;
    }
    fclose(font_file);
    if (magic[0] != PSF1_MAGIC0 || magic[1] != PSF1_MAGIC1)
    {
      return false;
    }
    return true;
  }

  bool Screen::is_PSF2_font(const char *font_path)
  {
    unsigned char magic[4];
    FILE *font_file;
    font_file = fopen(font_path, "rb");
    if (!font_file)
    {
      ESP_LOGE(TAG, "\"%s\" could not be opened!", font_path);
      return false;
    }
    if (!fread((char *)&magic, sizeof(char), 4, font_file))
    {
      ESP_LOGE(TAG, "Reading font header failed");
      fclose(font_file);
      return false;
    }
    fclose(font_file);
    if (magic[0] != PSF2_MAGIC0 || magic[1] != PSF2_MAGIC1)
    {
      return false;
    }
    return true;
  }

  void Screen::load_font(const char *font_path)
  {
    if (is_PSF1_font(font_path))
    {
      m_font = new FontPSF1(font_path, &context);
      return;
    }

    if (is_PSF2_font(font_path))
    {
      m_font = new FontPSF2(font_path, &context);
      return;
    }
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
