#include "IRremote.h"

#define RED_LED 12
#define GREEN_LED 11
#define BLUE_LED 10

#define RED_PIN 6
#define GREEN_PIN 5
#define BLUE_PIN 3

#define BUTTON 8

#define RECEIVER 2

#define KEY_VOL_ADD 25245
#define KEY_VOL_DE -22441

int selectedColor = 0;

int values[3] = {0, 0, 0};

int led_pins[3] = {RED_LED, GREEN_LED, BLUE_LED};

IRrecv irrecv(RECEIVER);
decode_results results;

void setup() {
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BLUE_LED, OUTPUT);

  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);

  pinMode(BUTTON, INPUT_PULLUP);

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  irrecv.enableIRIn();

}

void loop() {

  int value = digitalRead(BUTTON);

  if (value == LOW) {
    selectedColor = (selectedColor + 1) % 3;
    delay(500);
  }

  lightLed(selectedColor);
  lightRgb();

  if (irrecv.decode(&results)) {
    int value = results.value;
    if (value == KEY_VOL_ADD) {
      increase(selectedColor);
    } else if (value == KEY_VOL_DE) {
      decrease(selectedColor);
    }
    irrecv.resume();
  }
}

void changeColor(int selectedColor, int value) {
  int currentValue = values[selectedColor];
  int newValue = currentValue + value;
  if (newValue < 0) {
    newValue = 0;
  } else if (newValue > 255) {
    newValue = 255;
  }
  values[selectedColor] = newValue;
}

void increase(int selectedColor) {
  changeColor(selectedColor, 16);
}

void decrease(int selectedColor) {
  changeColor(selectedColor, -16);
}

void lightLed(int color) {
  digitalWrite(RED_LED, LOW);
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(BLUE_LED, LOW);
  digitalWrite(led_pins[color], HIGH);
}

void lightRgb() {
  analogWrite(RED_PIN, values[0]);
  analogWrite(GREEN_PIN, values[1]);
  analogWrite(BLUE_PIN, values[2]);
}
