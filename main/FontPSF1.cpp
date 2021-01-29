#include "FontPSF1.h"
#include <stdio.h>
#include "esp_log.h"

static const char *TAG = "FontPSF1";

namespace TGUI
{
    FontPSF1::FontPSF1(const char *font_file, DrawingContext *context)
    {
        ESP_LOGI(TAG, "Loading \"%s\" font file", font_file);
        PSF1_header *m_header;
        m_context = context;
        FILE *font_file_h = fopen(font_file, "rb");
        if (!font_file_h)
        {
            ESP_LOGE(TAG, "\"%s\" could not be opened!", font_file);
            return;
        }

        m_font = (PSF1_font *)malloc(sizeof(PSF1_font));
        m_header = (PSF1_header *)malloc(sizeof(PSF1_header));
        size_t data_read = fread(m_header, sizeof(PSF1_header), 1, font_file_h);
        if (data_read == 0)
        {
            ESP_LOGE(TAG, "Data blocks read: %d", data_read);
            fclose(font_file_h);
            free(m_font);
            free(m_header);
            return;
        }

        if (m_header->magic[0] != PSF1_MAGIC0 || m_header->magic[1] != PSF1_MAGIC1)
        {
            ESP_LOGE(TAG, "Wrong magic number");
            fclose(font_file_h);
            free(m_font);
            free(m_header);
            return;
        }
        m_font->header = m_header;
        size_t glyph_data_size = m_header->char_size * 256;
        if (m_header->mode == 3)
        { // 512 glyph mode
            ESP_LOGI(TAG, "512 chars glyph mode");
            glyph_data_size = m_header->char_size * 512;
        }

        void *m_glyphs = (void *)malloc(glyph_data_size);
        if (!m_glyphs)
        {
            ESP_LOGE(TAG, "Not enough memory");
            fclose(font_file_h);
            free(m_font);
            free(m_header);
            free(m_glyphs);
            return;
        }
        
        fseek(font_file_h, sizeof(PSF1_header), SEEK_SET);
        if (fread(m_glyphs, glyph_data_size, 1, font_file_h) == 0)
        {
            ESP_LOGE(TAG, "Couldn't read glyph data");
            fclose(font_file_h);
            free(m_font);
            free(m_header);
            free(m_glyphs);
            return;
        }
        m_font->glyphs = m_glyphs;

        fclose(font_file_h);
        ESP_LOGI(TAG, "Font file reading completed");
    }

    FontPSF1::~FontPSF1()
    {
        free(m_font->header);
        free(m_font->glyphs);
        free(m_font);
    }

    void FontPSF1::draw_char(const char c, Point p, uint16_t color)
    {
        assert(m_font);
        assert(m_context);
        char *font_ptr = (char *)((char *)m_font->glyphs + (c * m_font->header->char_size));
        for (size_t y = p.get_y(); y < (p.get_y() + m_font->header->char_size); y++)
        {
            for (size_t x = p.get_x(); x < p.get_x() + 8; x++)
            {
                uint8_t pixel = (uint8_t)(*font_ptr);
                if (pixel & (0x80 >> (x - p.get_x())))
                {
                    m_context->put_pixel(Point(x, y), color);
                }
            }
            font_ptr++;
        }
    }

    void FontPSF1::draw_text(const char *text, Point p, uint16_t color)
    {
        char *char_ptr = (char *)text;
        Point coord = p;
        while (*char_ptr != 0)
        {
            draw_char(*char_ptr, coord, color);
            coord.set(coord.get_x() + 8, coord.get_y());
            char_ptr++;
        }
    }
} // namespace TGUI
