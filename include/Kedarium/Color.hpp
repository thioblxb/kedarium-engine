#ifndef KDR_COLOR_HPP
#define KDR_COLOR_HPP

#include <stdint.h>

namespace kdr
{
  namespace Color
  {
    /**
     * Represents a color with red, green, blue, and alpha components.
     */
    struct RGBA
    {
      float red;
      float green;
      float blue;
      float alpha;

      /**
       * Constructs an RGBA color with specified components.
       *
       * @param red   The red component (0-255).
       * @param green The green component (0-255).
       * @param blue  The blue component (0-255).
       * @param alpha The alpha component (0.0-1.0).
       */
      RGBA(
        const uint8_t red,
        const uint8_t green,
        const uint8_t blue,
        const float alpha
      ) : red(red / 255.f), green(green / 255.f), blue(blue / 255.f), alpha(alpha)
      {}
    };

    /**
     * Constant representing the color white.
     */
    inline const kdr::Color::RGBA White {255, 255, 255, 1.f};
    /**
     * Constant representing the color black.
     */
    inline const kdr::Color::RGBA Black {0, 0, 0, 1.f};
    /**
     * Constant representing the color red.
     */
    inline const kdr::Color::RGBA Red {255, 0, 0, 1.f};
    /**
     * Constant representing the color green.
     */
    inline const kdr::Color::RGBA Green {0, 255, 0, 1.f};
    /**
     * Constant representing the color blue.
     */
    inline const kdr::Color::RGBA Blue {0, 0, 255, 1.f};
    /**
     * Constant representing the color yellow.
     */
    inline const kdr::Color::RGBA Yellow {255, 255, 0, 1.f};
    /**
     * Constant representing the color cyan.
     */
    inline const kdr::Color::RGBA Cyan {0, 255, 255, 1.f};
    /**
     * Constant representing the color magenta.
     */
    inline const kdr::Color::RGBA Magenta {255, 0, 255, 1.f};
  }
}

#endif // KDR_COLOR_HPP
