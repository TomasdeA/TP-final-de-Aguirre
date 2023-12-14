
#ifndef DIMMING_H
#define DIMMING_H

typedef enum {
    LUZ_INTERIOR,
    LUZ_GUARDABARRO,
} lucesPwm_t;


void setDimmingMode(lucesPwm_t ledIndex, bool mode);
bool getDimmingMode(lucesPwm_t ledIndex);
void setOnMode(lucesPwm_t ledIndex, bool mode);
bool getOnMode(lucesPwm_t ledIndex);
void dimmingInit();
void dimmingUpdate();

#endif  // DIMMING_H
