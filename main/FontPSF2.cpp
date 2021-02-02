#include "FontPSF2.h"
#include <stdio.h>
#include "esp_log.h"

static const char *TAG = "FontPSF2";

namespace TGUI
{

    FontPSF2::FontPSF2()
    {
    }

    FontPSF2::~FontPSF2()
    {
        free(m_font->header);
        free(m_font->glyphs);
        free(m_font);
    }

    FontPSF2::FontPSF2(const char *font_file, DrawingContext *context)
    {
        ESP_LOGI(TAG, "Loading \"%s\" font file", font_file);
        PSF2_header *m_header;
        m_context = context;
        FILE *font_file_h = fopen(font_file, "rb");

        if (!font_file_h)
        {
            ESP_LOGE(TAG, "\"%s\" could not be opened!", font_file);
            return;
        }

        m_font = (PSF2_font *)malloc(sizeof(PSF2_font));
        m_header = (PSF2_header *)malloc(sizeof(PSF2_header));
        size_t data_read = fread(m_header, sizeof(PSF2_header), 1, font_file_h);
        if (data_read == 0)
        {
            ESP_LOGE(TAG, "Data blocks read: %d", data_read);
            fclose(font_file_h);
            free(m_font);
            free(m_header);
            return;
        }
        if (m_header->magic[0] != PSF2_MAGIC0 || m_header->magic[1] != PSF2_MAGIC1)
        {
            ESP_LOGE(TAG, "Wrong magic number");
            fclose(font_file_h);
            free(m_font);
            free(m_header);
            return;
        }
        m_font->header = m_header;
        m_bytes_per_line = (m_font->header->width + 7) / 8;

        size_t glyph_data_size = (m_font->header->length) * (m_font->header->charsize);
        m_font->glyphs = (char *)malloc(glyph_data_size);
        if (!m_font->glyphs)
        {
            ESP_LOGE(TAG, "Not enough glyphs memory");
            fclose(font_file_h);
            free(m_font);
            free(m_header);
            return;
        }
        fseek(font_file_h, m_font->header->headersize, SEEK_SET);
        if (!fread((char *)m_font->glyphs, sizeof(char), glyph_data_size, font_file_h))
        {
            ESP_LOGE(TAG, "Couldn't read glyph data");
            fclose(font_file_h);
            free(m_font->glyphs);
            free(m_font);
            free(m_header);
            return;
        }
        fclose(font_file_h);
        ESP_LOGI(TAG, "Font file reading completed");
    }

    void FontPSF2::draw_char(const char c, Point p, uint16_t color)
    {
        assert(m_font);
        assert(m_context);
        assert(c < m_font->header->length);
        char *glyph_ptr = (m_font->glyphs + (c * m_font->header->charsize));
        const unsigned int glyph_height = m_font->header->height;
        const unsigned int glyph_width = m_font->header->width;

        for (size_t y = p.get_y(); y < (p.get_y() + glyph_height); y++)
        {
            uint8_t byte0 = *glyph_ptr;
            uint8_t byte1 = *(glyph_ptr + 1);
            uint32_t glyph_row = (byte0 << (glyph_width - 8)) | (byte1 >> (8 - (glyph_width - 8)));

            for (size_t x = p.get_x(); x < p.get_x() + glyph_width; x++)
            {
                uint32_t mask = (1 << (glyph_width - 1 - (x - p.get_x())));
                if (glyph_row & mask)
                {
                    m_context->put_pixel(Point(x, y), color);
                }
            }
            glyph_ptr += m_bytes_per_line;
        }
    }

    void FontPSF2::draw_text(const char *text, Point p, uint16_t color)
    {
        char *char_ptr = (char *)text;
        Point coord = p;
        while (*char_ptr != 0)
        {
            draw_char(*char_ptr, coord, color);
            coord.set(coord.get_x() + m_font->header->width, coord.get_y());
            char_ptr++;
        }
    }

} // namespace TGUI
