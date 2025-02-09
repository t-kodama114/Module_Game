#include "SocialNetworkOptimizer.h"

void optimizeNetwork(float* positions, int count) {
    // 社会的ネットワークの最適化処理を実装
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