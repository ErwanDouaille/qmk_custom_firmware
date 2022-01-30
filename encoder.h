#include "quantum.h"

enum encoder_state {
    ENCODER_VOLUME = 0
};

#define ENCODER_DEFAULT ENCODER_VOLUME

typedef void (*encoder_callback)(void);

void volume_up(void);
void volume_down(void);