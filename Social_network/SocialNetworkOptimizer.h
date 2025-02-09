#ifndef SOCIAL_NETWORK_OPTIMIZER_H
#define SOCIAL_NETWORK_OPTIMIZER_H

#include <vector>

extern "C" {
    __declspec(dllexport) void optimizeNetwork(float* positions, int count);
}

#endif // SOCIAL_NETWORK_OPTIMIZER_H
