#pragma once

#include "DrawingContext.h"
#include "Point.h"

namespace TGUI
{

#define PSF1_MAGIC0 0x36
#define PSF1_MAGIC1 0x04

#define PSF1_MODE512 0x01
#define PSF1_MODEHASTAB 0x02
#define PSF1_MODEHASSEQ 0x04
#define PSF1_MAXMODE 0x05

#define PSF1_SEPARATOR 0xFFFF
#define PSF1_STARTSEQ 0xFFFE

    struct PSF1_header
    {
        unsigned char magic[2];  /* Magic number */
        unsigned char mode;      /* PSF font mode */
        unsigned char char_size; /* Character size */
    };

    struct PSF1_font
    {
        PSF1_header *header;
        void *glyphs;
    };

    class FontPSF1
    {
    public:
        FontPSF1() {}
        FontPSF1(const char *font_file, DrawingContext *context);
        ~FontPSF1();
        void draw_char(const char, Point, uint16_t color);
        void draw_text(const char *, Point, uint16_t color);

    private:
        PSF1_font *m_font{nullptr};
        DrawingContext *m_context{nullptr};
    };

} // namespace TGUI