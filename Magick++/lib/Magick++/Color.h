// This may look like C code, but it is really -*- C++ -*-
//
// Copyright Bob Friesenhahn, 1999, 2000, 2001, 2002, 2003, 2008
//
// Color Implementation
//
#if !defined (Magick_Color_header)
#define Magick_Color_header

#include "Magick++/Include.h"
#include <string>

namespace Magick
{
  class MagickPPExport Color;

  // Compare two Color objects regardless of LHS/RHS
  int MagickPPExport operator ==
    (const Magick::Color& left_,const Magick::Color& right_);
  int MagickPPExport operator !=
    (const Magick::Color& left_,const Magick::Color& right_);
  int MagickPPExport operator >
    (const Magick::Color& left_,const Magick::Color& right_);
  int MagickPPExport operator <
    (const Magick::Color& left_,const Magick::Color& right_);
  int MagickPPExport operator >=
    (const Magick::Color& left_,const Magick::Color& right_);
  int MagickPPExport operator <=
    (const Magick::Color& left_,const Magick::Color& right_);

  // Base color class stores RGBA components scaled to fit Quantum
  // All double arguments have a valid range of 0.0 - 1.0.
  class MagickPPExport Color
  {
  public:

    // Default constructor
    Color(void);

    // Construct Color using the specified RGB values
    Color(const Quantum red_,const Quantum green_,const Quantum blue_);

    // Construct Color using the specified RGBA values
    Color(const Quantum red_,const Quantum green_,const Quantum blue_,
      const Quantum alpha_);

    // Construct Color using the specified color string
    Color(const char *color_);

    // Copy constructor
    Color(const Color &color_);

    // Construct color via ImageMagick PixelInfo
    Color(const PixelInfo &color_);

    // Constructor Color using the specified color string
    Color(const std::string &color_);

    // Destructor
    virtual ~Color(void);

    // Assignment operator
    Color& operator=(const Color &color_);

    // Set color via X11 color specification string
    const Color& operator=(const char *color);

    // Set color via ImageMagick PixelInfo
    const Color& operator=(const PixelInfo &color_);

    // Set color via color specification string
    const Color& operator=(const std::string &color);

    // Return ImageMagick PixelInfo
    operator PixelInfo() const;

    // Return color specification string
    operator std::string() const;

    // Alpha level (range 0.0=0 to 1.0=QuantumRange)
    void alpha(const double alpha_);
    double alpha(void) const;

    // Does object contain valid color?
    void isValid(const bool valid_);
    bool isValid(void) const;

    // Alpha level (range OpaqueAlpha=0 to TransparentAlpha=QuantumRange)
    void quantumAlpha(const Quantum alpha_);
    Quantum quantumAlpha(void) const;

    // Blue color (range 0 to QuantumRange)
    void quantumBlue(const Quantum blue_);
    Quantum quantumBlue(void) const;

    // Green color (range 0 to QuantumRange)
    void quantumGreen(const Quantum green_);
    Quantum quantumGreen(void) const;

    // Red color (range 0 to QuantumRange)
    void quantumRed(const Quantum red_);
    Quantum quantumRed(void) const;

  protected:

    // PixelType specifies the interpretation of PixelInfo members
    // CYMKPixel:
    //   Cyan     = red
    //   Yellow   = green
    //   Magenta  = blue
    //   Black(K) = alpha
    // RGBPixel:
    //   Red      = red;
    //   Green    = green;
    //   Blue     = blue;
    // RGBAPixel:
    //   Red      = red;
    //   Green    = green;
    //   Blue     = blue;
    //   Alpha    = alpha;
    enum PixelType
    {
      CYMKPixel,
      RGBPixel,
      RGBAPixel
    };

    // Constructor to construct with PixelInfo*
    // Used to point Color at a pixel in an image
    Color(PixelInfo *rep_,PixelType pixelType_);

    // Set pixel
    // Used to point Color at a pixel in an image
    void pixel(PixelInfo *rep_,PixelType pixelType_);

    // Scale a value expressed as a double (0-1) to Quantum range (0-QuantumRange)
    static Quantum scaleDoubleToQuantum(const double double_);

    // Scale a value expressed as a Quantum (0-QuantumRange) to double range (0-1)
    static double scaleQuantumToDouble(const Quantum quantum_);

    // PixelInfo represents a color pixel:
    //  red     = red   (range 0 to QuantumRange)
    //  green   = green (range 0 to QuantumRange)
    //  blue    = blue  (range 0 to QuantumRange)
    //  alpha   = alpha (range OpaqueAlpha=0 to TransparentAlpha=QuantumRange)
    //  index   = PseudoColor colormap index
    PixelInfo *_pixel;

  private:

    bool _isValid; // Set true if pixel is "valid"
    bool _pixelOwn; // Set true if we allocated pixel
    PixelType _pixelType; // Color type supported by _pixel

    // Common initializer for PixelInfo representation
    void initPixel();
  };

  //
  // Grayscale RGB color
  //
  // Grayscale is simply RGB with equal parts of red, green, and blue
  // All double arguments have a valid range of 0.0 - 1.0.
  class MagickPPExport ColorGray: public Color
  {
  public:

    // Default constructor
    ColorGray(void);

    // Copy constructor
    ColorGray(const Color &color_);

    // Construct ColorGray using the specified shade
    ColorGray(const double shade_);

    // Destructor
    ~ColorGray();

    // Shade
    void shade(const double shade_);
    double shade(void) const;

    // Assignment operator from base class
    ColorGray& operator=(const Color& color_);

  protected:

    // Constructor to construct with PixelInfo*
    ColorGray(PixelInfo *rep_,PixelType pixelType_);
  };

  //
  // HSL Colorspace colors
  //
  // All double arguments have a valid range of 0.0 - 1.0.
  class MagickPPExport ColorHSL: public Color
  {
  public:

    // Default constructor
    ColorHSL(void);

    // Copy constructor
    ColorHSL(const Color &color_);

    // Construct ColorHSL using the specified HSL values
    ColorHSL(const double hue_,const double saturation_,
      const double luminosity_);

    // Destructor
    ~ColorHSL();

    // Assignment operator from base class
    ColorHSL& operator=(const Color& color_);

    // Hue color
    void hue(const double hue_);
    double hue(void) const;

    // Luminosity color
    void luminosity(const double luminosity_);
    double luminosity(void) const;

    // Saturation color
    void saturation(const double saturation_);
    double saturation(void) const;

  protected:

    // Constructor to construct with PixelInfo*
    ColorHSL(PixelInfo *rep_,PixelType pixelType_);
  };

  //
  // Monochrome color
  //
  // Color arguments are constrained to 'false' (black pixel) and 'true'
  // (white pixel)
  class MagickPPExport ColorMono: public Color
  {
  public:

    // Default constructor
    ColorMono(void);

    // Construct ColorMono (false=black, true=white)
    ColorMono(const bool mono_);

    // Copy constructor
    ColorMono(const Color &color_);

    // Destructor
    ~ColorMono();

    // Assignment operator from base class
    ColorMono& operator=(const Color& color_);

    // Mono color
    void mono(const bool mono_);
    bool mono(void) const;

  protected:

    // Constructor to construct with PixelInfo*
    ColorMono(PixelInfo* rep_,PixelType pixelType_);
  };

  class MagickPPExport ColorRGB: public Color
  {
  public:

    // Default constructor
    ColorRGB(void);

    // Copy constructor
    ColorRGB(const Color &color_);

    // Construct ColorRGBA using the specified RGB values
    ColorRGB(const double red_,const double green_,const double blue_);

    // Construct ColorRGBA using the specified RGBA values
    ColorRGB(const double red_,const double green_,const double blue_,
      const double alpha);

    // Destructor
    ~ColorRGB(void);

    // Assignment operator from base class
    ColorRGB& operator=(const Color& color_);

    // Blue color (range 0.0 to 1.0)
    void blue(const double blue_);
    double blue(void) const;

    // Green color (range 0 to QuantumRange)
    void green(const double green_);
    double green(void) const;

    // Red color (range 0 to 1.0)
    void red(const double red_);
    double red(void) const;

  protected:

    // Constructor to construct with PixelInfo*
    ColorRGB(PixelInfo *rep_,PixelType pixelType_);
  };

  //
  // YUV Colorspace color
  //
  // Argument ranges:
  //        Y:  0.0 through 1.0
  //        U: -0.5 through 0.5
  //        V: -0.5 through 0.5
  class MagickPPExport ColorYUV: public Color
  {
  public:

    // Default constructor
    ColorYUV(void);

    // Copy constructor
    ColorYUV(const Color &color_);

    // Construct ColorYUV using the specified YUV values
    ColorYUV(const double y_,const double u_,const double v_);

    // Destructor
    ~ColorYUV(void);

    // Assignment operator from base class
    ColorYUV& operator=(const Color& color_);

    // Color U (0.0 through 1.0)
    void u(const double u_);
    double u(void) const;

    // Color V (-0.5 through 0.5)
    void v(const double v_);
    double v(void) const;

    // Color Y (-0.5 through 0.5)
    void y(const double y_);
    double y(void) const;

  protected:

    // Constructor to construct with PixelInfo*
    ColorYUV(PixelInfo *rep_,PixelType pixelType_);

  private:

    void convert(const double y_,const double u_,const double v_);

  };
} // namespace Magick

#endif // Magick_Color_header
