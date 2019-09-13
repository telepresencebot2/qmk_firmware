#ifndef RGB_H
#define RGB_H

const uint16_t underglow_leds[6] = {0,1,2,3,4,5};
const uint16_t arrow_leds[5] = {11,16,17,19,22};
const uint16_t thumb_leds[3] = {6,13,14};
const uint16_t other_leds[13] = {10,9,8,7,12,15,20,21,26,25,24,23,18};

void process_rgb(void);
void rgblight_effect_breath(void);
void rgblight_effect_base(void);
void rgblight_effect_league(void);
#endif
