#include "encoder.h"
#include "erwand.h"

static uint8_t state = ENCODER_DEFAULT;

const encoder_callback encoder_mapping[][2] = {
    [ENCODER_VOLUME] = {&volume_up, &volume_down},
};

void volume_up() { tap_code(KC_VOLU); }

void volume_down() { tap_code(KC_VOLD); }

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        (*encoder_mapping[state][0])();
    } else {
        (*encoder_mapping[state][1])();
    }

    return true;
}
