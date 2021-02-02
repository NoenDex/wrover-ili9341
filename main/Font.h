#pragma once

#include "Point.h"
#include "DrawingContext.h"

namespace TGUI {

    class Font
    {
    public:
        Font(){}
        Font(const char *font_file, DrawingContext *context){}
        virtual void draw_char(const char, Point, uint16_t color);
        virtual void draw_text(const char *, Point, uint16_t color);
        virtual ~Font() {}
     private:
    };

}