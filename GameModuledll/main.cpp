#include <iostream>
#include <vector>
#include "Optimizer.h"

int main() {
    // テスト用の敵MOBの位置データ
    std::vector<float> positions = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };

    // 最適化前の位置を表示
    std::cout << "Before optimization:" << std::endl;
    for (size_t i = 0; i < positions.size() / 2; ++i) {
        std::cout << "Enemy " << i << ": (" << positions[2 * i] << ", " << positions[2 * i + 1] << ")" << std::endl;
    }

    // 最適化関数を呼び出し
    Optimizer::optimizePositions(positions.data(), positions.size() / 2);

    // 最適化後の位置を表示
    std::cout << "After optimization:" << std::endl;
    for (size_t i = 0; i < positions.size() / 2; ++i) {
        std::cout << "Enemy " << i << ": (" << positions[2 * i] << ", " << positions[2 * i + 1] << ")" << std::endl;
    }

    return 0;
}