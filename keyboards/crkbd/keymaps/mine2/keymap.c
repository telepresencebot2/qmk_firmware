#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
  #include "rgb.c"
#endif
// #ifdef SSD1306OLED
//   #include "oled.h"
// #endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _NAV 0
#define _NAVLOW 1
#define _NAVHIGH 2
#define _QWERTY 3
#define _LEAGUE 4
#define _MAPLE 5
#define _LOWER 6
#define _RAISE 7
#define _GAMECHAT 8
#define _ONEHANDLEFT 9
#define _ONEHANDRIGHT 10
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST,
  LOL,
  GMCHAT,
  MAPLE,
  NAV,
  NAVLOW,
  NAVHIGH,
  OHR,
  OHL
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define KC_PSCREEN KC_PSCREEN
#define KC______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_LOWER LOWER
#define KC_QWERTY QWERTY
#define KC_RAISE RAISE
#define KC_LOL   LOL
#define KC_OHR   OHR
#define KC_OHL   OHL
#define KC_GMCHAT TG(_GAMECHAT)
#define KC_NAV   NAV
#define KC_NAVLOW   NAVLOW
#define KC_NAVHIGH  NAVHIGH
#define KC_MAPLE MAPLE
#define KC_RST   RESET
#define KC_RESET RESET
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_CTLTB CTL_T(KC_TAB)
#define KC_GUIEI GUI_T(KC_LANG2)
#define KC_ALTKN ALT_T(KC_LANG1)
#define KC_ALTTAB LALT(KC_TAB)

#define KC_CQ    LCTL(KC_Q)
#define KC_CW    LCTL(KC_W)
#define KC_CL    LCTL(KC_L)
#define KC_CR    LCTL(KC_R)
#define KC_CT    LCTL(KC_T)
#define KC_CA    LCTL(KC_A)
#define KC_CS    LCTL(KC_S)
#define KC_CN    LCTL(KC_N)
#define KC_CF    LCTL(KC_F)
#define KC_CZ    LCTL(KC_Z)
#define KC_CX    LCTL(KC_X)
#define KC_CC    LCTL(KC_C)
#define KC_CV    LCTL(KC_V)

#define KC_WL    LGUI(KC_L)
#define KC_WR    LGUI(KC_R)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NAV] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,  HOME,  PGUP,    UP, PGDN,PSCREEN,                    LOL, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        ESC,   END,  LEFT,  DOWN, RIGHT,   SPC,                  MAPLE,QWERTY, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT, GUIEI, XXXXX, XXXXX,    WL,    WR,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                NAVHIGH, NAVLOW,  RALT,    XXXXX, XXXXX, XXXXX\
                              //`--------------------'  `--------------------'
  ),

  [_NAVLOW] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,    CQ,    CW,    CL,    CR,    CT,                    LOL, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        ESC,    CA,    CS,    CN,    CF,   ENT,                  MAPLE,QWERTY, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LSFT,  LCTL,    CZ,    CX,    CC,    CV,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LSFT,NAVLOW,  LCTL,    XXXXX, XXXXX, XXXXX\
                              //`--------------------'  `--------------------'
  ),

  [_NAVHIGH] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     1,     2,     3,     4,     5,                    LOL, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     6,     7,     8,     9,     0,                  MAPLE,QWERTY, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       RALT, GUIEI,    F1,    F2,    F5,   F11,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                NAVHIGH,NAVLOW,  ENT,    XXXXX, XXXXX, XXXXX\
                              //`--------------------'  `--------------------'
  ),

  [_QWERTY] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL, GUIEI,     Z,     X,     C,     V,                      B,     N,     M,  COMM,   DOT,  SLSH,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LSFT , LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_LEAGUE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     1,     2,     3,     4,     5,                  XXXXX,   NAV, XXXXX, XXXXX, XXXXX,ALTTAB,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,     Q,     W,     E,     R,     T,                  MAPLE,QWERTY, XXXXX, XXXXX, XXXXX,     P,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
          B,     Z,     S,     D,     F,     G,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, GUIEI,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    LSFT,  SPC,  LCTL,    XXXXX, GMCHAT, XXXXX\
                              //`--------------------'  `--------------------'
  ),

  [_MAPLE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                    LOL,   NAV, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      GUIEI,     A,     S,     D,     F,     G,                  XXXXX,QWERTY, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     Z,     X,     C,     V,     B,                    NAV, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LSFT , LOWER,   SPC,    XXXXX, GMCHAT, XXXXX\
                              //`--------------------'  `--------------------'
  ),

  [_LOWER] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        TAB,     1,     2,     3,     4,     5,                      6,     7,     8,     9,     0,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,    F1,    F2,    F3,    F4,    F5,                     F6,    F7,    F8,    F9,   F10,  HOME,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LALT,   F11,   F12,   F13,   F14,  LSFT,                    F16,   F17,   F18,   F19,   F20,   END,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LSFT , LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_RAISE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,  EXLM,    AT,  HASH,   DLR,  PERC,                   CIRC,  AMPR,  ASTR,  LPRN,  RPRN,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,   TAB, XXXXX, XXXXX, XXXXX, XXXXX,                   MINS,   EQL,  LCBR,  RCBR,  PIPE,   GRV,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      GUIEI, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   UNDS,  PLUS,  LBRC,  RBRC,  BSLS,  TILD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LSFT , LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_GAMECHAT] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                      Y,     U,     I,     O,     P,  BSPC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,     A,     S,     D,     F,     G,                      H,     J,     K,     L,  SCLN,  QUOT,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL, GUIEI,     Z,     X,     C,     V,                      B,     N,     M,  COMM,   DOT,  SLSH,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LSFT , XXXXX,   SPC,      ENT, GMCHAT, RALT \
                              //`--------------------'  `--------------------'
  ),

    [_ONEHANDLEFT] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                 QWERTY, XXXXX,    UP, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,     A,     S,     D,     F,     G,                  GUIEI,  LEFT,  DOWN, RIGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     Z,     X,     C,     V,     B,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LSFT ,   OHR,   SPC,    LOWER, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_ONEHANDRIGHT] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        DEL,     P,     O,     I,     U,     Y,                 QWERTY, XXXXX,    UP, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       QUOT,  SCLN,     L,     K,     J,     H,                  GUIEI,  LEFT,  DOWN, RIGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,  SLSH,   DOT,  COMM,     M,     N,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  RALT ,   OHL,   ENT,    LOWER, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, RESET,                    LOL,   NAV,    UP, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                    OHL,  LEFT,  DOWN, RIGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LSFT, LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  )
};


int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    rgblight_enable();
    rgblight_sethsv(160, 255, 0);
    persistent_default_layer_set(1UL<<_QWERTY);
    set_purple();
    //rgblight_mode(1);

    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

const char *read_mode_icon(bool swap);
const char *read_host_led_state(void);
void set_timelog(void);
const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
   process_rgb();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
  //   // If you want to change the display of OLED, you need to change here
  //   matrix_write_ln(matrix, read_layer_state());
  //   matrix_write_ln(matrix, read_keylog());
  //   matrix_write_ln(matrix, read_keylogs());
  //   //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
  //   matrix_write_ln(matrix, read_host_led_state());
  //   //matrix_write_ln(matrix, read_timelog());
      char logo[] = {
      0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, 0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, 0x70, 0x71, 0x72, 0x73, 0x74,
      0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
      0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
      0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
      0};
    matrix_write(matrix, logo);
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
        set_purple();
        //rgblight_mode(30);
      }
      return false;
      break;
    case LOL:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_LEAGUE);
        set_league();
        //rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
      }
      return false;
      break;
    case OHR:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_ONEHANDRIGHT);
        set_ohr();
      }
      return false;
      break;
    case OHL:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_ONEHANDLEFT);
        set_ohl();
      }
      return false;
      break;
    // case GMCHAT:
    //   if (record->event.pressed) {
    //     TG(_GAMECHAT);
    //     //set_league();
    //     //rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
    //   }
    //   return false;
    //   break;
    case MAPLE:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_MAPLE);
        //rgblight_mode(RGBLIGHT_MODE_ALTERNATING);
      }
      return false;
      break;
    case NAV:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_NAV);
        set_blue();
        //rgblight_mode(RGBLIGHT_MODE_RGB_TEST);
      }
      return false;
      break;
    case NAVLOW:
      if (record->event.pressed) {
        layer_on(_NAVLOW);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_NAVLOW);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case NAVHIGH:
      if (record->event.pressed) {
        layer_on(_NAVHIGH);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_NAVHIGH);
        //update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        //TG(_ADJUST);
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
  }
  return true;
}

