#include "Optimizer.h"

void Optimizer::optimizePositions(float* positions, int count) {
    // Å“K‰»ˆ—‚ğÀ‘•
    float centerX = 0, centerY = 0;
    for (int i = 0; i < count; ++i) {
        centerX += positions[2 * i];
        centerY += positions[2 * i + 1];
    }
    centerX /= count;
    centerY /= count;

    for (int i = 0; i < count; ++i) {
        positions[2 * i] += (centerX - positions[2 * i]) * 0.1f;
        positions[2 * i + 1] += (centerY - positions[2 * i + 1]) * 0.1f;
    }
}