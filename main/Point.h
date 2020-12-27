#pragma once

#include <stdint.h>

namespace TGUI
{
    class Point
    {
    public:
        Point(int16_t x, int16_t y);
        void set(int16_t x, int16_t y);
        void set_x(int16_t);
        void set_y(int16_t);
        int16_t get_x() const { return m_x; };
        int16_t get_y() const { return m_y; };
        void resize_by(int16_t units);
        void operator =(Point other);

    private:
        int16_t m_x{0};
        int16_t m_y{0};
    };
} // namespace TGUI
