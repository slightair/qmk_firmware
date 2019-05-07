#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _ADJUST 16

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
};

// Fillers to make layering more clear
#define KC_ KC_TRNS
#define _______ KC_TRNS
#define KC_XXXXX KC_NO
#define KC_AJST ADJUST
#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_CTLTB CTL_T(KC_TAB)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //,------+------+------+------+------+------+------.    ,------+------+------+------+------+------+------.
        ESC,     Q,     W,     E,     R,     T, XXXXX,      XXXXX,     Y,     U,     I,     O,     P,  BSPC,
  //|------+------+------+------+------+------+------|    |------+------+------+------+------+------+------|
      CTLTB,     A,     S,     D,     F,     G, XXXXX,      XXXXX,     H,     J,     K,     L,  SCLN,  QUOT,
  //|------+------+------+------+------+------+------|    |------+------+------+------+------+------+------|
       LSFT,     Z,     X,     C,     V,     B, XXXXX,      XXXXX,     N,     M,  COMM,   DOT,  SLSH,   GRV,
  //|------+------+------+------+------+------+------|    |------+------+------+------+------+------+------|
       AJST, XXXXX, XXXXX, XXXXX,  LGUI,  LOWR,   SPC,        ENT,  RASE,  LALT,  LEFT,  DOWN,    UP,  RGHT
  //`------+------+------+------+------+------+------'    `------+------+------+------+------+------+------'
  ),

  [_LOWER] = LAYOUT_kc(
  //,------+------+------+------+------+------+------.    ,------+------+------+------+------+------+------.
        ESC, XXXXX,    UP, XXXXX, XXXXX, XXXXX, XXXXX,      XXXXX,     7,     8,     9,     0,  BSLS,  BSPC,
  //|------+------+------+------+------+------+------|    |------+------+------+------+------+------+------|
      CTLTB,  LEFT,  DOWN,  RGHT, LANG2, LANG1, XXXXX,      XXXXX,     4,     5,     6,  MINS,   EQL, XXXXX,
  //|------+------+------+------+------+------+------|    |------+------+------+------+------+------+------|
       LSFT, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,      XXXXX,     1,     2,     3, XXXXX,  BSLS, XXXXX,
  //|------+------+------+------+------+------+------|    |------+------+------+------+------+------+------|
       AJST, XXXXX, XXXXX, XXXXX,  LGUI,  LOWR,   SPC,        ENT,  RASE,  LALT,  LEFT,  DOWN,    UP,  RGHT
  //`------+------+------+------+------+------+------'    `------+------+------+------+------+------+------'
  ),

  [_RAISE] = LAYOUT_kc(
  //,------+------+------+------+------+------+------.    ,------+------+------+------+------+------+------.
        ESC,  EXLM,    AT,  HASH,   DLR,  PERC, XXXXX,      XXXXX,  CIRC,  AMPR,  ASTR,  LPRN,  RPRN,  BSPC,
  //|------+------+------+------+------+------+------|    |------+------+------+------+------+------+------|
      CTLTB, XXXXX, XXXXX,  LALT, LANG2, LANG1, XXXXX,      XXXXX,  LEFT,  DOWN,    UP,  RGHT,  LBRC,  RBRC,
  //|------+------+------+------+------+------+------|    |------+------+------+------+------+------+------|
       LSFT, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX, XXXXX,      XXXXX, XXXXX,  MRWD,  MFFD,  VOLD,  VOLU,  MPLY,
  //|------+------+------+------+------+------+------|    |------+------+------+------+------+------+------|
       AJST, XXXXX, XXXXX, XXXXX,  LGUI,  LOWR,   SPC,        ENT,  RASE,  LALT,  LEFT,  DOWN,    UP,  RGHT
  //`------+------+------+------+------+------+------'    `------+------+------+------+------+------+------'
  ),

  [_ADJUST] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______, \
    _______, _______, RESET  , RGB_TOG, RGB_MOD, RGB_HUD, RGB_HUI, RGB_SAD, RGB_SAI, RGB_VAD, RGB_VAI, _______, KC_DEL,  _______, \
    _______, _______, _______, _______, AU_ON,   AU_OFF,  AG_NORM, AG_SWAP, QWERTY,  _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______ \
  )

};

#ifdef AUDIO_ENABLE
float tone_qwerty[][2]     = SONG(QWERTY_SOUND);
#endif

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        #ifdef AUDIO_ENABLE
          PLAY_NOTE_ARRAY(tone_qwerty, false, 0);
        #endif
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}
