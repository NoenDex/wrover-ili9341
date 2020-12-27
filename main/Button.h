#pragma once

#include "Point.h"
#include "Widget.h"
#include "Screen.h"
#include <string>

namespace TGUI
{
    class Button : public Widget
    {
    public:
        Button(std::string text) : m_text(text) {}
        void set_coordinates(Point p1, Point p2);
        void set_upper_left(Point p) { m_p1 = p; }
        void set_dimensions(uint16_t w, uint16_t h);
        void set_color(uint16_t color) { m_color = color; }
        void update() override;
        void paint(DrawingContext*) override;

    private:
        std::string m_text{};
        Point m_p1 {0, 0};
        Point m_p2 {0, 0};
        uint16_t m_width {0};
        uint16_t m_height {0};
        uint16_t m_color {0x4A49}; // Dark Grey
        uint16_t m_color_text {0xffff}; // White
    };
} // namespace TGUI
