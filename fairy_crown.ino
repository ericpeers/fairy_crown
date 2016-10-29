//Random Flash animation for Neopixel circuits
//by Dano Wall and Becky Stern for Adafruit Industries
//based on the Sparkle Skirt, minus the accelerometer
#include <Adafruit_NeoPixel.h>

#define NUM_PIXELS 7
#define PIN 1

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_PIXELS, 4, NEO_GRB + NEO_KHZ800);

// Here is where you can put in your favorite colors that will appear!
// just add new {nnn, nnn, nnn}, lines. They will be picked out randomly
//                          R   G   B
uint8_t myColors[][3] = {
                         {255, 0, 0}, //red
                         {237, 189, 31}, //orange
                         {247, 243, 7}, //yellow
                         {0, 255, 0}, //green
                         {26, 237, 227},   // turquoise
                         {0, 0, 255}, //blue
                         {228, 30, 235},   // purple
                         {245, 10, 88}  // hot pink
                          };

// don't edit the line below
#define FAVCOLORS sizeof(myColors) / 3

void setup() {
  strip.begin();
  strip.setBrightness(30);
  strip.show(); // Initialize all pixels to 'off'
}

void loop() {
  single_color(500);
  /*
    up_down(100);
    up_down(100);
*/
    /*
    flashRandom(10, 1);  // first number is 'wait' delay, shorter num == shorter twinkle
    flashRandom(10, 1);  // second number is how many neopixels to simultaneously light up
    flashRandom(10, 1);
    */
}

int pixel = 0;

void flashRandom(int wait, uint8_t howmany) {

  for(uint16_t i=0; i<howmany; i++) {
    // pick a random favorite color!
    int c = random(FAVCOLORS);
    int red = myColors[c][0];
    int green = myColors[c][1];
    int blue = myColors[c][2];


    // now we will 'fade' it in 5 steps
    for (int x=0; x < 5; x++) {
      int r = red * (x+1); r /= 5;
      int g = green * (x+1); g /= 5;
      int b = blue * (x+1); b /= 5;

      strip.setPixelColor(pixel, strip.Color(r, g, b));
      strip.show();
      delay(wait);
    }
    delay(200);
    // & fade out in 5 steps
    for (int x=5; x >= 0; x--) {
      int r = red * x; r /= 5;
      int g = green * x; g /= 5;
      int b = blue * x; b /= 5;

      strip.setPixelColor(pixel, strip.Color(r, g, b));
      strip.show();
      delay(wait);
    }
    // get a random pixel from the list
    pixel++; if (pixel >= NUM_PIXELS) pixel = 0;

  }
  // LEDs will be off when done (they are faded to 0)
}

//knight rider style effect
void knight_rider(int wait) {
    uint8_t i;
    uint8_t color = random(FAVCOLORS);
    uint8_t red = myColors[color][0];
    uint8_t green = myColors[color][1];
    uint8_t blue = myColors[color][2];

    for (i=0;i<NUM_PIXELS;i++) {
        strip.setPixelColor(i, strip.Color(red,green,blue));
        strip.show();
        delay(wait);
        strip.setPixelColor(i, strip.Color(0,0,0));
    }
    for (i=NUM_PIXELS-2;i!=0;i--) {
        strip.setPixelColor(i, strip.Color(red,green,blue));
        strip.show();
        delay(wait);
        strip.setPixelColor(i, strip.Color(0,0,0));
    }
}

void single_color(int wait) {
    uint8_t i;

    for (i=0;i<NUM_PIXELS;i++) {
      uint8_t red = myColors[i][0];
      uint8_t green = myColors[i][1];
      uint8_t blue = myColors[i][2];

      strip.setPixelColor(i, strip.Color(red,green,blue));
      strip.show();
    }
}

typedef struct {
    int r;
    int g;
    int b;
    int inc_r;
    int inc_g;
    int inc_b;
    int step;
} sparkle_pixel;


void sparkle(int pixel, int color) {
    uint8_t red   = myColors[color][0];
    uint8_t green = myColors[color][1];
    uint8_t blue  = myColors[color][2];

    int r = red / 2;
    int g = green / 2;
    int b = blue / 2;
    int inc_r = red / 20;  //we need 1/10th of the remainder, which is 1/2 * 1/10 => 1/20.
    int inc_g = green / 20;
    int inc_b = blue / 20;

    for (i=0;i<10;i++) {
        strip.setPixelColor(pixel, strip.Color(r, g, b));
        r+= inc_r;
        g+= inc_g;
        b+= inc_b;
        strip.show();
        delay(50);
    }
    for (i=0;i<10;i++) {
        strip.setPixelColor(pixel, strip.Color(r, g, b));
        r+= inc_r;
        g+= inc_g;
        b+= inc_b;
        strip.show();
        delay(50);
    }

}

//this will increment the sparkle pixel.
bool inc_sparkle(sparkle_pixel *target) {
    step = step++;
    if (step < 10) {
        target->r+= target->inc_r;
        target->g+= target->inc_g;
        target->b+= target->inc_b;
    } else if (step < 12) {
        //flash it white for 2 time increments.
        target->r = 255;
        target->g = 255;
        target->b = 255;
    } else if (step < 22) {
        target->r-= target->inc_r;
        target->g-= target->inc_g;
        target->b-= target->inc_b;
    } else {
        //we are done. If you call this more than twice, you are dumb.
        return true;
    }
    strip.setPixelColor(pixel, strip.Color(target->r, target->g, target->b));
    strip.show();
    return false;
}

start_sparkel(sparkle_pixel *target, int color) {
    uint8_t red   = myColors[color][0];
    uint8_t green = myColors[color][1];
    uint8_t blue  = myColors[color][2];

    target->r = red / 2;
    target->g = green / 2;
    target->b = blue / 2;
    target->inc_r = red / 20;  //we need 1/10th of the remainder, which is 1/2 * 1/10 => 1/20.
    target->inc_g = green / 20;
    target->inc_b = blue / 20;
}
