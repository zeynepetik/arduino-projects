#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

// button pins 
const int l_up_button = 2; // left paddle up
const int l_down_button = 3; //left paddle down
const int r_up_button = 13; //right button up
const int r_down_button = 12; // right button down

//screen width
int x_pixels = 128;
//screen height
int y_pixels = 32;

//paddle sizes
int paddle_height = 10;
int paddle_width = 6;

//buzzer pin 
int speakerPin = 8;

// ball velocity values
int x_vel = 5;
int y_vel = 5;
//start coordinate of ball
int x_pos = 5;
int y_pos = 32;

//paddles starting coordinate
int l_pos = 0;
int r_pos = 0;
//right and left side players scores
int l_score = 0;
int r_score = 0;

void setup() {
  //declared button input
  pinMode(l_up_button, INPUT);
  pinMode(l_down_button, INPUT);
  pinMode(r_up_button, INPUT);
  pinMode(r_down_button, INPUT);
  
  Serial.begin(9600);
  randomSeed(analogRead(0));
  //sets the screen
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  int textWidth = 64; // width of intro texts
  int textHeight = 16; // height of intro texts
  display.setCursor((display.width() - textWidth) / 2, (display.height() - textHeight) / 2);
  display.println("    GTU");
  display.setCursor((display.width() - textWidth) / 2, (display.height() - textHeight) / 2 + textHeight);
  display.println(" PONG GAME   ");
  display.display();
  delay(2000);
}

void loop() {
  //movement of left paddle up & down
  if (digitalRead(l_up_button) && l_pos < (y_pixels - paddle_height)) {
    l_pos += 2;
  } else if (digitalRead(l_down_button) && l_pos > 0) {
    l_pos -= 2;
  }
  // movement of right paddle up & down
  if (digitalRead(r_up_button) && r_pos < (y_pixels - paddle_height)) {
    r_pos += 2;
  } else if (digitalRead(r_down_button) && r_pos > 0) {
    r_pos -= 2;
  }
  // condition of goal situation, if ball hits right wall, left player get score
  if (x_pos > x_pixels ) {
    ball_reset(false);
    l_score++;
    tone(speakerPin, 50, 400);
    delay(50);
    tone(speakerPin, 50, 400);

    //if left player get 5 scores game ends and outro screen show up.
    if (l_score >= 5) {
      playGameOverMelody();
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(display.width() / 2 - 30, display.height() / 2 - 10);
      display.println("LEFT WINS!");
      display.setCursor(display.width() / 2 - 40, display.height() / 2 + 5);
      display.println("  GAME OVER");
      display.display();
      while (true); // end of the game
    }
  } 
  
  // condition of goal situation, if ball hits right wall, left player get score
  else if (x_pos < 0) {
    ball_reset(true);
    r_score++;
    tone(speakerPin, 50, 400);
    delay(50);
    tone(speakerPin, 50, 400);
   //if right player get 5 scores game ends and outro screen show up.
    if (r_score >= 5) {
      playGameOverMelody();
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(display.width() / 2 - 30, display.height() / 2 - 10);
      display.println("RIGHT WINS!");
      display.setCursor(display.width() / 2 - 40, display.height() / 2 + 5);
      display.println("  GAME OVER");
      display.display();
      while (true); // end of game
    }
  }
  // check whether the ball hits paddles then update velocity opposite direction
  if (y_pos > y_pixels - 1 || y_pos < 0) {
    y_vel = -y_vel;
  }

  x_pos += x_vel;
  y_pos += y_vel;
// create ball as  pixel
  display.clearDisplay();
  display.drawPixel(x_pos, y_pos, WHITE);
  display.fillRect(0, l_pos, paddle_width, paddle_height, WHITE);
  display.fillRect(x_pixels - paddle_width, r_pos, paddle_width, paddle_height, WHITE);
  //score board
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(display.width() / 4, 0);
  display.println(l_score);
  display.setCursor(display.width() * 3 / 4, 0);
  display.println(r_score);

  display.display();
// the sound when ball hit paddles
  if (ball_on_right_paddle()) {
    x_vel = -x_vel;
    tone(speakerPin, 600, 100);
  } else if (ball_on_left_paddle()) {
    x_vel = -x_vel;
    tone(speakerPin, 250, 100);
  }
}

bool ball_on_right_paddle() {
  return (x_pos == x_pixels - paddle_width - 1 && 
          y_pos + paddle_height >= r_pos && 
          y_pos <= r_pos + paddle_height && 
          x_vel > 0);
}

bool ball_on_left_paddle() {
  return (x_pos == paddle_width && 
          y_pos + paddle_height >= l_pos && 
          y_pos <= l_pos + paddle_height && 
          x_vel < 0);
}

void ball_reset(bool left) {
  y_pos = random(display.height());
  y_vel = random(2) > 0 ? 5 : -5;

  if (left) {
    x_vel = 5;
    x_pos = paddle_width;
  } else {
    x_vel = -5;
    x_pos = x_pixels - paddle_width - 1;
  }
}
//function of end game melody
void playGameOverMelody() {
  // 1. tone: E
  tone(speakerPin, 659, 200);  // frequency: 659 Hz, time: 200 ms
  delay(250);  // wait  a moment
  
  // 2. tone: C
  tone(speakerPin, 523, 200);  // frequency: 523 Hz, time: 200 ms
  delay(250);  // wait  a moment
  
  // 3. tone: G
  tone(speakerPin, 784, 200);  // frequency: 784 Hz, time: 200 ms
  delay(250);  // wait  a moment
  
  // 4. tone: E
  tone(speakerPin, 659, 200);  // frequency: 659 Hz, time: 200 ms
  delay(250);  // wait  a moment
    tone(speakerPin, 659, 200);  // frequency: 659 Hz, time: 200 ms
  delay(250);  // wait  a moment
  
  // 2. tone: C
  tone(speakerPin, 523, 200);  // frequency: 523 Hz, time: 200 ms
  delay(250);  // wait  a moment
  
  // 3. tone: G
  tone(speakerPin, 784, 200);  // frequency: 784 Hz, time: 200 ms
  delay(250);  // wait  a moment
  
  // 4. tone: E
  tone(speakerPin, 659, 200);  // frequency: 659 Hz, time: 200 ms
  delay(250);  // wait  a moment
  
  
  noTone(speakerPin);
}