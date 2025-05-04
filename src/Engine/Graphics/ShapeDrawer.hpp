#ifndef ENGINE_SHAPE_DRAWER_HPP
#define ENGINE_SHAPE_DRAWER_HPP

#include "Engine/Math/Math.hpp"
#include "Engine/Graphics/Color.hpp"

namespace shape_drawer
{
    void draw_rect(const Recti& rect, const Color& color);
    void draw_rect(const Rectf& rect, const Color& color);
} // namespace shape_drawer

#endif // ENGINE_SHAPE_DRAWER_HPP