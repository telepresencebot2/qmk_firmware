const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_NAV] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     L,     R,     T,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,     A,     S,     N,     F,   ENT,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL, GUIEI,     Z,     X,     C,     V,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LSFT , LOWER,  RALT,    XXXXX, XXXXX, XXXXX\
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
        ESC,     1,     2,     3,     4,     5,                 QWERTY, XXXXX, XXXXX, XXXXX, XXXXX,   ESC,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
        TAB,     Q,     W,     E,     R,     T,                 QWERTY, XXXXX, XXXXX, XXXXX, XXXXX,     P,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
          B,     A,     S,     D,     F,     G,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, GUIEI,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                    LSFT,  LCTL,  SPC,    XXXXX, XXXXX, XXXXX\
                              //`--------------------'  `--------------------'
  ),

  [_MAPLE] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        ESC,     Q,     W,     E,     R,     T,                 QWERTY, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      GUIEI,     A,     S,     D,     F,     G,                 QWERTY, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LCTL,     Z,     X,     C,     V,     B,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LSFT , LOWER,   SPC,    XXXXX, XXXXX, XXXXX\
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
       LCTL, TAB  , XXXXX, XXXXX, XXXXX, XXXXX,                   MINS,   EQL,  LCBR,  RCBR,  PIPE,   GRV,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
      GUIEI, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,                   UNDS,  PLUS,  LBRC,  RBRC,  BSLS,  TILD,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                  LSFT , LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_kc( \
  //,-----------------------------------------.                ,-----------------------------------------.
        RST,  LRST, XXXXX, XXXXX, XXXXX, RESET,                    LOL,  PGUP,    UP, PGDN , XXXXX,   DEL,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LTOG,  LHUI,  LSAI,  LVAI, XXXXX, XXXXX,                  MAPLE,  LEFT,  DOWN, RIGHT, XXXXX, XXXXX,\
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
       LMOD,  LHUD,  LSAD,  LVAD, XXXXX, XXXXX,                  XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,\
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                   LSFT, LOWER,   SPC,      ENT, RAISE, RALT \
                              //`--------------------'  `--------------------'
  )
};