
#define BITMAP_HEIGHT 8
#define BITMAP_WIDTH  8

static const uint8_t PROGMEM
    //smile
    bmp[5][8] = {
    { B00111100,
      B01000010,
      B10100101,
      B10000001,
      B10100101,
      B10011001,
      B01000010,
      B00111100 },
    //normal
    { B00111100,
      B01000010,
      B10100101,
      B10000001,
      B10111101,
      B10000001,
      B01000010,
      B00111100 },
    //frown
    { B00111100,
      B01000010,
      B10100101,
      B10000001,
      B10011001,
      B10100101,
      B01000010,
      B00111100 },
    //heart1
    { B00000000,
      B01100110,
      B11111111,
      B11111111,
      B11111111,
      B01111110,
      B00111100,
      B00011000 },
    //heart2
    { B00000000,
      B00000000,
      B00100100,
      B01111110,
      B01111110,
      B00111100,
      B00011000,
      B00000000 }
    };