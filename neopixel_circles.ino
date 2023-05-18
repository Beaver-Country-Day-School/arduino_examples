/*
 This is a relatively complex arduino program that creates a ripple effect on an 8x8 
 neopixel LED array.
*/

#include <Adafruit_NeoPixel.h>
 
// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6
#define ROWS 8
#define COLS 8
// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64
 
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
 
int delayval = 10; // delay for half a second
int colors[COLS][3] = {{255, 0, 0}, {255, 127, 0}, {255, 255, 0}, {127, 255, 0}, {0, 255, 0}, {0, 0, 255}, {46, 43, 95}, {139, 0, 255}};
int offset = 0;

const int CIRCLE_ONE_DIM = 1;
int circle_one[CIRCLE_ONE_DIM][CIRCLE_ONE_DIM] = {{1}};

const int CIRCLE_TWO_DIM = 3;
int circle_two[CIRCLE_TWO_DIM][CIRCLE_TWO_DIM] = {
  {1, 1, 1},
  {1, 0, 1},
  {1, 1, 1}
};

const int CIRCLE_THREE_DIM = 5;
int circle_three[CIRCLE_THREE_DIM][CIRCLE_THREE_DIM] = {
  {0, 1, 1, 1, 0},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {1, 0, 0, 0, 1},
  {0, 1, 1, 1, 0}
};

const int CIRCLE_FOUR_DIM = 7;
int circle_four[CIRCLE_FOUR_DIM][CIRCLE_FOUR_DIM] = {
  {0, 0, 1, 1, 1, 0, 0},
  {0, 1, 0, 0, 0, 1, 0},
  {1, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 1, 0},
  {0, 0, 1, 1, 1, 0, 0}
};

const int CIRCLE_FIVE_DIM = 9;
int circle_five[CIRCLE_FIVE_DIM][CIRCLE_FIVE_DIM] = {
  {0, 0, 0, 1, 1, 1, 0, 0, 0},
  {0, 1, 1, 0, 0, 0, 1, 1, 0},
  {0, 1, 0, 0, 0, 0, 0, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 1, 0, 0, 0, 0, 0, 1, 1},
  {0, 1, 1, 0, 0, 0, 1, 1, 0},
  {0, 0, 0, 1, 1, 1, 0, 0, 0},
};

const int CIRCLE_SIX_DIM = 11;
int circle_six[CIRCLE_SIX_DIM][CIRCLE_SIX_DIM] = {
  {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
  {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
  {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
  {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1},
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
  {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 1, 1, 0, 1, 1, 0, 0, 0},
  {0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0}
};


void clear_screen(uint32_t* screen) {
  for(int r = 0; r < ROWS; r++) {
    for(int c = 0; c < COLS; c++) {
      *(screen + (r * ROWS) + c) = pixels.Color(0, 0, 0);
    }
  }
}
void draw_circle(uint32_t* screen, int center_row, int center_col, int radius, uint32_t color) {
  int* circle;
  int dim;

  clear_screen(screen);

  switch(radius) {
    case 1:
      circle = (int*)circle_one;
      dim = CIRCLE_ONE_DIM;
      break;
    case 2:
      circle = (int*)circle_two;
      dim = CIRCLE_TWO_DIM;
      break;
    case 3:
      circle = (int*)circle_three;
      dim = CIRCLE_THREE_DIM;
      break;
    case 4:
      circle = (int*)circle_four;
      dim = CIRCLE_FOUR_DIM;
      break;
    case 5:
      circle = (int*)circle_five;
      dim = CIRCLE_FIVE_DIM;
      break;
    case 6:
      circle = (int*)circle_six;
      dim = CIRCLE_SIX_DIM;
      break;
  }

  Serial.println("Chose dim " + String(dim));

  int image_start_col = min(0, center_col - radius + 1) * -1;
  int image_start_row = min(0, center_row - radius + 1) * -1;
  //image_end_col = dim + min(0, COLS - center_col - radius);
  //image_end_row = dim + min(0, COLS - center_col - radius);

  int screen_start_col = max(0, center_col - radius + 1);
  int screen_start_row = max(0, center_row - radius + 1);
  int screen_end_col = min(COLS - 1, center_col + radius - 1);
  int screen_end_row = min(ROWS - 1, center_row + radius - 1);

  int rows = screen_end_row - screen_start_row + 1;
  int cols = screen_end_col - screen_start_col + 1;

  for(int r = 0; r < rows; r++) {
    for(int c = 0; c < cols; c++) {
      //Serial.println("r: " + String(r) + " c: " + String(c) + " circle val: " + String(*(circle + ((image_start_row + r) * dim) + (image_start_col + c))) + " circle r: " + String(image_start_row + r) + " circle c: " + String(image_start_col + c) + " screen r: " + String(screen_start_row + r) + " screen c: " + String(screen_start_col + c));
      if(*(circle + ((image_start_row + r) * dim) + (image_start_col + c)) == 1) {
        //Serial.println("Setting screen r: " + String(screen_start_row + r) + " c: " + String(screen_start_col + c) + " to: " + color);
        *(screen + ((screen_start_row + r) * ROWS) + (screen_start_col + c)) = color;
      }
    }
  }
  draw_screen(screen);
}

void draw_screen(uint32_t* screen) {
  for(int r = 0; r < ROWS; r++) {
    for(int c = 0; c < COLS; c++) {
      //Serial.println("Set pixel r: " + String(r) + " c: " + String(c) + " ind: " + String(r*8+c) + " to " + String(*(screen + (r * ROWS) + c)));
      pixels.setPixelColor(r*8+c, *(screen + (r * ROWS) + c));
    }
  }
  pixels.show();
}

void draw_rainbow() {
  offset = (offset + 1) % ROWS;
  for(int r = 0; r < ROWS; r++) {
    for(int c = 0; c < COLS; c++) {
      int col = (c + r + offset) % COLS;
      pixels.setPixelColor(r*8+c, pixels.Color(colors[col][0], colors[col][1], colors[col][2]));
    }
  }
  pixels.show();
  delay(250);
}

void setup() 
{
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(20);
  Serial.begin(9600);
}

void loop() {
  
  int r = random(1, ROWS-1);
  int c = random(1, COLS-1);
  int diam = 3;
  uint32_t screen[ROWS][COLS];
  
  pixels.clear();
  pixels.show();

  Serial.println("Drawing circle r: " + String(r) + " c: " + String(c) + " diam: " + String(diam));
  
  uint32_t color = pixels.Color(random(0, 255), random(0, 255), random(0, 255));
  int brightness = 90;

  for(int i = 1; i < 7; i++) { 
    pixels.setBrightness(brightness);
    brightness -= 15;
    draw_circle((uint32_t*)screen, r, c, i, color);
    delay(250);
  }
