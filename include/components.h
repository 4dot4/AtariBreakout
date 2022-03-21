#include "raylib.h"
typedef struct blockers{
    Rectangle spec;
    bool state;
    Color blockColor;
}blockers;

typedef struct CompleteBall{
    Rectangle ballCords;
    float spdX;
    float spdY;
}CompleteBall;