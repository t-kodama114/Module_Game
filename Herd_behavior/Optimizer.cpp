#include <vector>
#include <cmath>

// �萔�̒�`
const float SEPARATION_RADIUS = 1.0f; // �����̂��߂̔��a
const float ALIGNMENT_RADIUS = 2.0f;  // ����̂��߂̔��a
const float COHESION_RADIUS = 2.0f;   // �����̂��߂̔��a
const float SEPARATION_WEIGHT = 1.5f; // �����̏d��
const float ALIGNMENT_WEIGHT = 1.0f;  // ����̏d��
const float COHESION_WEIGHT = 1.0f;   // �����̏d��

// �x�N�g�����Z�̂��߂̍\����
struct Vector2 {
    float x, y;

    // �x�N�g���̉��Z
    Vector2 operator+(const Vector2& other) const {
        return { x + other.x, y + other.y };
    }

    // �x�N�g���̌��Z
    Vector2 operator-(const Vector2& other) const {
        return { x - other.x, y - other.y };
    }

    // �X�J���[�Ƃ̏�Z
    Vector2 operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }

    // �x�N�g���̑傫�����v�Z
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // �x�N�g���𐳋K��
    Vector2 normalized() const {
        float mag = magnitude();
        return { x / mag, y / mag };
    }
};

// �ʒu�œK���֐�
void optimizePositions(float* positions, int count) {
    // �V�����ʒu���i�[����x�N�g��
    std::vector<Vector2> newPositions(count);

    // �e�̂̈ʒu���œK��
    for (int i = 0; i < count; ++i) {
        Vector2 position = { positions[2 * i], positions[2 * i + 1] };
        Vector2 separation = { 0, 0 }; // �����x�N�g��
        Vector2 alignment = { 0, 0 };  // ����x�N�g��
        Vector2 cohesion = { 0, 0 };   // �����x�N�g��
        int neighbors = 0;           // �ߖT�̌̂̐�

        // ���̂��ׂĂ̌̂Ƒ��ݍ�p
        for (int j = 0; j < count; ++j) {
            if (i == j) continue; // �������g�̓X�L�b�v
            Vector2 neighborPosition = { positions[2 * j], positions[2 * j + 1] };
            Vector2 diff = position - neighborPosition;
            float distance = diff.magnitude();

            // �����̂��߂̌v�Z
            if (distance < SEPARATION_RADIUS) {
                separation = separation + diff.normalized() * (SEPARATION_RADIUS - distance);
            }
            // ����̂��߂̌v�Z
            if (distance < ALIGNMENT_RADIUS) {
                alignment = alignment + neighborPosition;
            }
            // �����̂��߂̌v�Z
            if (distance < COHESION_RADIUS) {
                cohesion = cohesion + neighborPosition;
                neighbors++;
            }
        }

        // �ߖT�̌̂����݂���ꍇ
        if (neighbors > 0) {
            alignment = (alignment * (1.0f / neighbors)) - position;
            cohesion = (cohesion * (1.0f / neighbors)) - position;
        }

        // �e�͂��������ĐV�������x���v�Z
        Vector2 velocity = separation * SEPARATION_WEIGHT + alignment * ALIGNMENT_WEIGHT + cohesion * COHESION_WEIGHT;
        // �V�����ʒu���v�Z
        newPositions[i] = position + velocity;
    }

    // �œK�����ꂽ�V�����ʒu���X�V
    for (int i = 0; i < count; ++i) {
        positions[2 * i] = newPositions[i].x;
        positions[2 * i + 1] = newPositions[i].y;
    }
}