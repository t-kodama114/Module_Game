#include <iostream>
#include <vector>
#include "Optimizer.h"

int main() {
    // �e�X�g�p�̓GMOB�̈ʒu�f�[�^
    std::vector<float> positions = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f };

    // �œK���O�̈ʒu��\��
    std::cout << "Before optimization:" << std::endl;
    for (size_t i = 0; i < positions.size() / 2; ++i) {
        std::cout << "Enemy " << i << ": (" << positions[2 * i] << ", " << positions[2 * i + 1] << ")" << std::endl;
    }

    // �œK���֐����Ăяo��
    Optimizer::optimizePositions(positions.data(), positions.size() / 2);

    // �œK����̈ʒu��\��
    std::cout << "After optimization:" << std::endl;
    for (size_t i = 0; i < positions.size() / 2; ++i) {
        std::cout << "Enemy " << i << ": (" << positions[2 * i] << ", " << positions[2 * i + 1] << ")" << std::endl;
    }

    return 0;
}