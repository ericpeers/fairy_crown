//updated, new and improved by: Eric Peers / peers@mtnboy.net
//
//original from:
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
                         {228, 30, 235},   // purple
                         {0, 255, 0}, //green
                         {26, 237, 227},   // turquoise
                         {0, 0, 255}, //blue
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
//    sparkle();
    single_color();
//    for (int i=0;i<10;i++) {
//      knight_rider(100);
//    }
//    flashRandom(10, 20);

    /*
    flashRandom(10, 1);  // first number is 'wait' delay, shorter num == shorter twinkle
    flashRandom(10, 1);  // second number is how many neopixels to simultaneously light up
    flashRandom(10, 1);
    */
}


//this isn't truly random. I'll just pick a random starting position.
void random_assortment() {
    int color = random(FAVCOLORS);

    for (int i=0;i<NUM_PIXELS;i++) {
        uint8_t red = myColors[color][0];
        uint8_t green = myColors[color][1];
        uint8_t blue = myColors[color][2];

        color++;
        if (color >= FAVCOLORS) color = 0;

        strip.setPixelColor(i, strip.Color(red, green, blue));
    }
    strip.show();
}


int pixel = 0;

void flashRandom(int wait, uint8_t howmany) {
    random_assortment();
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

void single_color() {

    random_assortment();
    delay(1000);
}

void sparkle() {
    random_assortment();

    for (int i=0;i<20;i++) {
        int pixel = random(NUM_PIXELS);
        sparkle_pixel(pixel);
    }
}


#define SPARKLE_STEPS 5

void sparkle_pixel(int pixel) {
    int i;
    uint32_t packed = strip.getPixelColor(pixel);
    uint8_t red   = packed >> 16 & 0xff;
    uint8_t green = packed >> 8  & 0xff;
    uint8_t blue  = packed       & 0xff;

    int r = red;
    int g = green;
    int b = blue;

    int inc_r = (255 - red) / SPARKLE_STEPS;
    int inc_g = (255 - green) / SPARKLE_STEPS;
    int inc_b = (255 - blue) / SPARKLE_STEPS;

    for (i=0;i<SPARKLE_STEPS;i++) {
        strip.setPixelColor(pixel, strip.Color(r, g, b));
        r+= inc_r;
        g+= inc_g;
        b+= inc_b;
        strip.show();
        delay(100);
    }
    for (i=0;i<SPARKLE_STEPS;i++) {
        strip.setPixelColor(pixel, strip.Color(r, g, b));
        r+= inc_r;
        g+= inc_g;
        b+= inc_b;
        strip.show();
        delay(100);
    }

    //just in case "math is hard". or imprecise.
    strip.setPixelColor(pixel, strip.Color(red, green, blue));
}
