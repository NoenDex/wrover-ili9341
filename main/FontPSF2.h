#pragma once

// PSF fonts from: https://www.zap.org.au/projects/console-fonts-zap/

#include "DrawingContext.h"
#include "Point.h"
#include "Font.h"

namespace TGUI
{

#define PSF2_MAGIC0 0x72
#define PSF2_MAGIC1 0xb5
#define PSF2_MAGIC2 0x4a
#define PSF2_MAGIC3 0x86

/* bits used in flags */
#define PSF2_HAS_UNICODE_TABLE 0x01

/* max version recognized so far */
#define PSF2_MAXVERSION 0

/* UTF8 separators */
#define PSF2_SEPARATOR 0xFF
#define PSF2_STARTSEQ 0xFE

    struct PSF2_header
    {
        unsigned char magic[4];
        unsigned int version;
        unsigned int headersize; /* offset of bitmaps in file */
        unsigned int flags;
        unsigned int length;        /* number of glyphs */
        unsigned int charsize;      /* number of bytes for each character */
        unsigned int height, width; /* max dimensions of glyphs */
                                    /* charsize = height * ((width + 7) / 8) */
    };

    struct PSF2_font
    {
        PSF2_header *header;
        char *glyphs;
    };

    class FontPSF2 : public Font
    {
    private:
        /* data */
    public:
        FontPSF2(const char *font_file, DrawingContext *context);
        ~FontPSF2();
        void draw_char(const char, Point, uint16_t color) override;
        void draw_text(const char *, Point, uint16_t color) override;

    private:
        FontPSF2();
        PSF2_font *m_font{nullptr};
        DrawingContext *m_context{nullptr};
        uint8_t m_bytes_per_line{0};
    };

} // namespace TGUI
