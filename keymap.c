#include "erwand.h"
#include <math.h>
#include "print.h"

static uint16_t base_timer, rythm_timer;
// RGB LED locations
enum led_location_map {
    LED_ESC, // 0, ESC, k13
    LED_GRV, // 1, ~, k16
    LEB_TAB, // 2, Tab, k11
    LED_CAPS, // 3, Caps, k21
    LED_LSFT, // 4, Sh_L, k00
    LED_LCTL, // 5, Ct_L, k06
    LED_F1, // 6, F1, k26
    LED_1, // 7, 1, k17
    LED_Q, // 8, Q, k10
    LED_A, // 9, A, k12
    LED_Z, // 10, Z, k14
    LED_LWIN, // 11, Win_L, k90
    LED_F2, // 12, F2, k36
    LED_2, // 13, 2, k27
    LED_W, // 14, W, k20
    LED_S, // 15, S, k22
    LED_X, // 16, X, k24
    LED_LALT, // 17, Alt_L, k93
    LED_F3, // 18, F3, k31
    LED_3, // 19, 3, k37
    LED_E, // 20, E, k30
    LED_D, // 21, D, k32
    LED_C, // 22, C, k34
    LED_F4, // 23, F4, k33
    LED_4, // 24, 4, k47
    LED_R, // 25, R, k40
    LED_F, // 26, F, k42
    LED_V, // 27, V, k44
    LED_F5, // 28, F5, k07
    LED_5, // 29, 5, k46
    LED_T, // 30, T, k41
    LED_G, // 31, G, k43
    LED_B, // 32, B, k45
    LED_SPC, // 33, SPACE, k94
    LED_F6, // 34, F6, k63
    LED_6, // 35, 6, k56
    LED_Y, // 36, Y, k51
    LED_H, // 37, H, k53
    LED_N, // 38, N, k55
    LED_F7, // 39, F7, k71
    LED_7, // 40, 7, k57
    LED_U, // 41, U, k50
    LED_J, // 42, J, k52
    LED_M, // 43, M, k54
    LED_F8, // 44, F8, k76
    LED_8, // 45, 8, k67
    LED_I, // 46, I, k60
    LED_K, // 47, K, k62
    LED_COMM, // 48, ,, k64
    LED_RALT, // 49, Alt_R, k95
    LED_F9, // 50, F9, ka6
    LED_9, // 51, 9, k77
    LED_O, // 52, O, k70
    LED_L, // 53, L, k72
    LED_DOT, // 54, ., k74
    LED_FN, // 55, FN, k92
    LED_F10, // 56, F10, ka7
    LED_0, // 57, 0, k87
    LED_P, // 58, P, k80
    LED_SCLN, // 59, ;, k82
    LED_SLSH, // 60, ?, k85
    LED_F11, // 61, F11, ka3
    LED_MINS, // 62, -, k86
    LED_LBRC, // 63, [, k81
    LED_QUOT, // 64, ", k83
    LED_RCTL, // 65, Ct_R, k04
    LED_F12, // 66, F12, ka5
    LED_L1, // 67, LED, l01
    LED_R1, // 68, LED, l11
    LED_INS, // 69, Prt, k97  -- remapped to INS
    LED_L2, // 70, LED, l02
    LED_R2, // 71, LED, l12
    LED_DEL, // 72, Del, k65
    LED_L3, // 73, LED, l03
    LED_R3, // 74, LED, l13
    LED_PGUP, // 75, PgUp, k15
    LED_L4, // 76, LED, l04
    LED_R4, // 77, LED, l14
    LED_EQL, // 78, =, k66
    LED_RIGHT, // 79, Right, k05
    LED_L5, // 80, LED, l05
    LED_R5, // 81, LED, l15
    LED_END, // 82, End, k75
    LED_L6, // 83, LED, l06
    LED_R6, // 84, LED, l16
    LED_BSPC, // 85, BSpc, ka1
    LED_PGDN, // 86, PgDn, k25
    LED_L7, // 87, LED, l07
    LED_R7, // 88, LED, l17
    LED_RBRC, // 89, ], k61
    LED_RSFT, // 90, Sh_R, k91
    LED_L8, // 91, LED, l08
    LED_R8, // 92, LED, l18
    LED_BSLS, // 93, \, ka2
    LED_UP, // 94, Up, k35
    LED_LEFT, // 95, Left, k03
    LED_ENT, // 96, Enter, ka4
    LED_DOWN // 97, Down, k73
};

// looks like it´s limited to 32 macros ...
enum macros
{
  LOVEE = SAFE_RANGE,
  LOVED,
  LOVEH,
  LAST
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR,          MO(1),
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_PGUP,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_PGDN,
        KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_END,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_DEL,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, KC_APP,  KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    [1] = LAYOUT(
        KC_PWR,  KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   RGB_SPD,          KC_NO,
        KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,
        KC_NO,   KC_NO,   KC_NO,   LOVEE,    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,
        KC_NO,   KC_NO,   KC_NO,   LOVED,   KC_NO,   KC_NO,   LOVEH,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,            KC_INS,
        KC_NO,            KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,            KC_NO,   KC_NO,   KC_HOME,
        KC_NO,   KC_NO,   KC_NO,                              KC_NO,                              KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO
    )
};

// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  rythm_timer = timer_read();
  switch(keycode) {
    case LOVEE:
    if (record->event.pressed) {
      SEND_STRING("Erwan c' est le meilleur ... <3"); // testing macros
    }
    break;
    case LOVED:
    if (record->event.pressed) {
      SEND_STRING("Daouiya c' est la meilleure ... <3");
    }
    break;
    case LOVEH:
    if (record->event.pressed) {
      SEND_STRING("Hana\"e c' est la meilleure ... <3");
    }
    break;
  }
  return true;
};

void keyboard_post_init_user(void) {
  debug_enable=false;
  debug_matrix=false;
};

const uint8_t LED_LIST_WASD[] = { LED_W, LED_A, LED_S, LED_D };

const uint8_t LED_LIST_ARROWS[] = { LED_LEFT, LED_RIGHT, LED_UP, LED_DOWN };

const uint8_t LED_LIST_FUNCROW[] = { LED_ESC, LED_F1, LED_F2, LED_F3, LED_F4, LED_F5, LED_F6, LED_F7, LED_F8, LED_F9, LED_F10, LED_F11, LED_F12, LED_INS};

const uint8_t LED_LIST_NUMROW[] = { LED_GRV, LED_1, LED_2, LED_3, LED_4, LED_5, LED_6, LED_7, LED_8, LED_9, LED_0, LED_MINS, LED_EQL, LED_BSPC, LED_DEL};

const uint8_t LED_LIST_NUMPAD[] = {
    LED_7, LED_8, LED_9,
    LED_U, LED_I, LED_O,
    LED_J, LED_K, LED_L,
    LED_M, LED_COMM, LED_DOT
    };

const uint8_t LED_SIDE_LEFT[] = { LED_L1, LED_L2, LED_L3, LED_L4, LED_L5, LED_L6, LED_L7, LED_L8};

const uint8_t LED_SIDE_RIGHT[] = { LED_R1, LED_R2, LED_R3, LED_R4, LED_R5, LED_R6, LED_R7, LED_R8};


// Capslock, Scroll lock and Numlock  indicator on Left side lights.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    rgb_matrix_set_color_all(RGB_RED); // Default startup colour
    rgb_matrix_set_color(LED_ESC, 255,0,0);

    switch(get_highest_layer(layer_state)){  // special handling per layer
        case 1:  // on Fn layer select what the encoder does when pressed
            rgb_matrix_set_color_all(RGB_BLUE); // Default startup colour
            rgb_matrix_set_color(LED_ESC, RGB_RED);
            rgb_matrix_set_color(LED_E, RGB_RED);
            rgb_matrix_set_color(LED_D, RGB_RED);
            rgb_matrix_set_color(LED_H, RGB_RED);
            break;
    }

    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        for (uint8_t i = 0; i < 8; i++) {
            rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_WHITE);
            rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_WHITE);
        }
        rgb_matrix_set_color(LED_CAPS, RGB_WHITE);
    }
}

void keyboard_post_init_keymap(void) {
    base_timer = timer_read();
    rythm_timer = timer_read();
    // keyboard_post_init_user() moved to userspace
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_color_all(RGB_RED); // Default startup colour
}