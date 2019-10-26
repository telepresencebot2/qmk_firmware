#include "rgblight.h"

#define ignore_mode -1
#define static_mode 0
#define satcyc_mode 1
#define satcir_mode 2
#define huecyc_mode 3
#define huecir_mode 4
#define bricyc_mode 5
#define bricir_mode 6

#define led_groups 4

uint16_t led_count[] = {6,4,3,14};
uint16_t led_speed[] = {1,1,1,1};
uint16_t led_hue[] = {0,0,0,0};
uint16_t led_brightness[] = {0,0,0,0};
uint16_t led_saturation[] = {0,0,0,0};
uint16_t led_mode[] = {0,0,0,0};

//{ under, arrow, thumb, other }
static const uint16_t leds[4][14] = {\
  {0,1,2,3,4,5},\
  {11,16,19,22},\
  {6,13,14},\
  {17,18,23,24,25,26,21,20,15,12,7,8,9,10}\
};
static uint16_t rgbcounter = 0;
static uint16_t mode_counter[] = {0,0,0,0};
static uint16_t mode_direction[] = {1,1,1,1};
static uint16_t temp;


//todo
// save to eeprom?
// second league layer
//   need chat, missing ping, quick chat, alt?

void mode_static(uint16_t group) {
  for(int i = 0; i < led_count[group]; i++) {
    sethsv(led_hue[group], led_saturation[group], led_brightness[group], (LED_TYPE *)&led[leds[group][i]]);
  }
}
void mode_satcyc(uint16_t group){
  if (!(rgbcounter%led_speed[group])) {
    if (mode_counter[group] > led_saturation[group] - 1) {mode_direction[group] = -1;}
    if (mode_counter[group] < 1) {mode_direction[group] = 1;}
    mode_counter[group] = mode_counter[group] + mode_direction[group];
  }
  for(int i = 0; i < led_count[group]; i++) {
    sethsv(led_hue[group], mode_counter[group], led_brightness[group], (LED_TYPE *)&led[leds[group][i]]);
  }
}
void mode_satcir(uint16_t group){
  if (!(rgbcounter%led_speed[group])) {
    if (mode_counter[group] > led_saturation[group]*2 - 1) {mode_counter[group] = 0;}
    mode_counter[group]++;
  }
  for(int i = 0; i < led_count[group]; i++) {
    temp = mode_counter[group] + (led_saturation[group] * i / 6);
    temp = temp % ((led_saturation[group] * 2)-1);
    if (temp > led_saturation[group]) { temp = (led_saturation[group]*2)-temp; }
    sethsv(led_hue[group], temp, led_brightness[group], (LED_TYPE *)&led[leds[group][i]]);
  }
}
void mode_huecyc(uint16_t group){
  if (!(rgbcounter%led_speed[group])) {
    mode_counter[group]++;
    mode_counter[group] = mode_counter[group]%360;
  }
  for(int i = 0; i < led_count[group]; i++) {
    sethsv(mode_counter[group], led_saturation[group], led_brightness[group], (LED_TYPE *)&led[leds[group][i]]);
  }
}
void mode_huecir(uint16_t group){
  if (!(rgbcounter%led_speed[group])) {
    mode_counter[group] = mode_counter[group]%360;
    mode_counter[group]++;
  }
  for(int i = 0; i < led_count[group]; i++) {
    temp = mode_counter[group] + (20 * i);
    temp = temp % 360;
    sethsv(temp, led_saturation[group], led_brightness[group], (LED_TYPE *)&led[leds[group][i]]);
  }
}
void mode_bricyc(uint16_t group){
  if (!(rgbcounter%led_speed[group])) {
    if (mode_counter[group] > led_brightness[group] - 1) {mode_direction[group] = -1;}
    if (mode_counter[group] < 1) {mode_direction[group] = 1;}
    mode_counter[group] = mode_counter[group] + mode_direction[group];
  }
  for(int i = 0; i < led_count[group]; i++) {
    sethsv(led_hue[group], led_saturation[group], mode_counter[group], (LED_TYPE *)&led[leds[group][i]]);
  }
}
void mode_bricir(uint16_t group){
  int deadzone = led_brightness[group] * led_count[group] / 10;
  uint16_t bright = led_brightness[group] + deadzone;
  if (!(rgbcounter%led_speed[group])) {
    if (mode_counter[group] > bright*2 - 1) {mode_counter[group] = 0;}
    mode_counter[group]++;
  }
  for(int i = 0; i < led_count[group]; i++) {
    temp = mode_counter[group] + (bright * 2 * i / led_count[group]);
    temp = temp % ((bright * 2)-1);
    if (temp > bright) { temp = (bright*2)-temp; }
    if (temp > deadzone/2) { temp = temp - deadzone/2; }
    else { temp = 0; }
    if (temp > led_brightness[group]) { temp = led_brightness[group]; }
    sethsv(led_hue[group], led_saturation[group], temp, (LED_TYPE *)&led[leds[group][i]]);
  }
}


void set_purple(void){
  led_saturation[0] = 0;
  led_saturation[1] = 0;
  led_saturation[2] = 255;
  led_saturation[3] = 255;
  led_hue[0] = 160;
  led_hue[1] = 280;
  led_hue[2] = 280;
  led_hue[3] = 280;
  led_brightness[0] = 255;
  led_brightness[1] = 200;
  led_brightness[2] = 180;
  led_brightness[3] = 255;
  led_speed[0] = 10;
  led_speed[1] = 1;
  led_speed[2] = 1;
  led_speed[3] = 3;
  led_mode[0] = bricir_mode;
  led_mode[1] = static_mode;
  led_mode[2] = static_mode;
  led_mode[3] = bricir_mode;
}

void set_blue(void){
  led_saturation[0] = 255;
  led_saturation[1] = 0;
  led_saturation[2] = 0;
  led_saturation[3] = 255;
  led_hue[0] = 160;
  led_hue[1] = 160;
  led_hue[2] = 160;
  led_hue[3] = 160;
  led_brightness[0] = 255;
  led_brightness[1] = 120;
  led_brightness[2] = 120;
  led_brightness[3] = 180;
  led_speed[0] = 1;
  led_speed[1] = 1;
  led_speed[2] = 1;
  led_speed[3] = 1;
  led_mode[0] = static_mode;
  led_mode[1] = static_mode;
  led_mode[2] = static_mode;
  led_mode[3] = static_mode;
}

void set_vommit(void){
  led_saturation[0] = 255;
  led_saturation[1] = 255;
  led_saturation[2] = 255;
  led_saturation[3] = 255;
  led_hue[0] = 160;
  led_hue[1] = 160;
  led_hue[2] = 160;
  led_hue[3] = 160;
  led_brightness[0] = 255;
  led_brightness[1] = 255;
  led_brightness[2] = 255;
  led_brightness[3] = 255;
  led_speed[0] = 1;
  led_speed[1] = 1;
  led_speed[2] = 1;
  led_speed[3] = 1;
  led_mode[0] = huecir_mode;
  led_mode[1] = huecir_mode;
  led_mode[2] = huecir_mode;
  led_mode[3] = huecir_mode;
}

void set_league(void){
  static uint16_t i;
  if(isLeftHand){
    led_saturation[0] = 0;
    led_saturation[1] = 255;
    led_saturation[2] = 255;
    led_saturation[3] = 255;
    led_hue[0] = 120;
    led_hue[1] = 0;
    led_hue[2] = 0;
    led_hue[3] = 120;
    led_brightness[0] = 255;
    led_brightness[1] = 180;
    led_brightness[2] = 150;
    led_brightness[3] = 150;
    led_mode[0] = static_mode;
    led_mode[1] = static_mode;
    led_mode[2] = static_mode;
    led_mode[3] = static_mode;
  } else {
    led_mode[0] = ignore_mode;
    led_mode[1] = ignore_mode;
    led_mode[2] = ignore_mode;
    led_mode[3] = ignore_mode;
    for(i = 0; i < 27; i++) {
      sethsv(0, 255, 0, (LED_TYPE *)&led[i]);
    }
    sethsv(0, 255, 100, (LED_TYPE *)&led[24]);
    sethsv(0, 255, 100, (LED_TYPE *)&led[26]);
    sethsv(120, 255, 100, (LED_TYPE *)&led[8]);
    sethsv(160, 255, 100, (LED_TYPE *)&led[10]);
    sethsv(280, 255, 100, (LED_TYPE *)&led[11]);
  }
  rgblight_set();
}

void set_ohl(void){
  static uint16_t i;
  if(isLeftHand){
    led_saturation[0] = 255;
    led_saturation[1] = 255;
    led_saturation[2] = 0;
    led_saturation[3] = 255;
    led_hue[0] = 100;
    led_hue[1] = 100;
    led_hue[2] = 100;
    led_hue[3] = 100;
    led_brightness[0] = 200;
    led_brightness[1] = 150;
    led_brightness[2] = 150;
    led_brightness[3] = 150;
    led_mode[0] = static_mode;
    led_mode[1] = static_mode;
    led_mode[2] = static_mode;
    led_mode[3] = static_mode;
  } else {
    led_saturation[1] = 255;
    led_hue[1] = 100;
    led_brightness[1] = 150;
    led_mode[0] = ignore_mode;
    led_mode[1] = static_mode;
    led_mode[2] = ignore_mode;
    led_mode[3] = ignore_mode;
    for(i = 0; i < 27; i++) {
      sethsv(0, 255, 0, (LED_TYPE *)&led[i]);
    }
    sethsv(190, 255, 100, (LED_TYPE *)&led[8]);
    sethsv(280, 255, 100, (LED_TYPE *)&led[9]);
  }
  rgblight_set();
}

void set_ohr(void){
  static uint16_t i;
  if(isLeftHand){
    led_saturation[0] = 255;
    led_saturation[1] = 255;
    led_saturation[2] = 0;
    led_saturation[3] = 255;
    led_hue[0] = 100;
    led_hue[1] = 100;
    led_hue[2] = 100;
    led_hue[3] = 100;
    led_brightness[0] = 200;
    led_brightness[1] = 150;
    led_brightness[2] = 150;
    led_brightness[3] = 150;
    led_speed[1] = 1;
    led_mode[0] = static_mode;
    led_mode[1] = bricyc_mode;
    led_mode[2] = static_mode;
    led_mode[3] = static_mode;
  } else {
    led_saturation[1] = 255;
    led_hue[1] = 100;
    led_brightness[1] = 150;
    led_mode[0] = ignore_mode;
    led_mode[1] = static_mode;
    led_mode[2] = ignore_mode;
    led_mode[3] = ignore_mode;
    for(i = 0; i < 27; i++) {
      sethsv(0, 255, 0, (LED_TYPE *)&led[i]);
    }
    sethsv(190, 255, 100, (LED_TYPE *)&led[8]);
    sethsv(280, 255, 100, (LED_TYPE *)&led[9]);
  }
  rgblight_set();
}

void process_rgb(void) {
  rgbcounter++;

  for(int i = 0; i < led_groups; i++) {
    switch(led_mode[i]) {
      case static_mode:
        mode_static(i);
        break;
      case satcyc_mode:
        mode_satcyc(i);
        break;
      case satcir_mode:
        mode_satcir(i);
        break;
      case huecyc_mode:
        mode_huecyc(i);
        break;
      case huecir_mode:
        mode_huecir(i);
        break;
      case bricyc_mode:
        mode_bricyc(i);
        break;
      case bricir_mode:
        mode_bricir(i);
        break;
    }
  }
  rgblight_set();
}
