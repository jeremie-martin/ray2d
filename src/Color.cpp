#include "Color.hpp"
#include <stdio.h>
namespace Ray2d {
    namespace Graphics {
            glm::vec3 wavelengthToRGB(int wavelength) {
            float red, green, blue;
            float factor;

            switch (wavelength) {
                case 380 ... 439:
                red = -((float) wavelength - (float) 440) / ((float) 440 - (float) 380);
                green = 0.0;
                blue = 1.0;
                break;

                case 440 ... 489:
                red = 0.0;
                green = ((float) wavelength - (float) 440) / ((float) 490 - (float) 440);
                blue = 1.0;
                break;

                case 490 ... 509:
                red = 0.0;
                green = 1.0;
                blue = -((float) wavelength - (float) 510) / ((float) 510 - (float) 490);
                break;

                case 510 ... 579:
                red = ((float) wavelength - (float) 510) / ((float) 580 - (float) 510);
                green = 1.0;
                blue = 0.0;
                break;

                case 580 ... 644:
                red = 1.0;
                green = -((float) wavelength - (float) 645) / ((float) 645 - (float) 580);
                blue = 0.0;
                break;

                case 645 ... 780:
                red = 1.0;
                green = 0.0;
                blue = 0.0;
                break;
            }

            switch (wavelength) {
                case 380 ... 419:
                factor = 0.3 + 0.7 * ((float) wavelength - (float) 380) / ((float) 420 - (float) 380);
                break;

                case 420 ... 700:
                factor = 1.0;
                break;

                case 701 ... 780:
                factor = 0.3 + 0.7 * ((float) 780 - (float) wavelength) / ((float) 780 - (float)700);
                break;
            }

            red = Adjust(red, factor);
            green = Adjust(green, factor);
            blue = Adjust(blue, factor);

            return glm::vec3(red, green, blue);
        }

        float Adjust(float colour, float factor) {
            if (colour == 0.0) {
                colour = 0;
            }
            else {
                colour = colour * factor;
            }
            return colour;
        }
    }
}