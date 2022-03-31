#include "types.h"
#include "user.h"

void periodic();

int main()
{
    periodic();
    exit();
}

void periodic() {
    printf(1, "alarm!\n");
}
