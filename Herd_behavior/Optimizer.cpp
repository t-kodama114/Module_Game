#include <vector>
#include <cmath>

// 定数の定義
const float SEPARATION_RADIUS = 1.0f; // 分離のための半径
const float ALIGNMENT_RADIUS = 2.0f;  // 整列のための半径
const float COHESION_RADIUS = 2.0f;   // 結合のための半径
const float SEPARATION_WEIGHT = 1.5f; // 分離の重み
const float ALIGNMENT_WEIGHT = 1.0f;  // 整列の重み
const float COHESION_WEIGHT = 1.0f;   // 結合の重み

// ベクトル演算のための構造体
struct Vector2 {
    float x, y;

    // ベクトルの加算
    Vector2 operator+(const Vector2& other) const {
        return { x + other.x, y + other.y };
    }

    // ベクトルの減算
    Vector2 operator-(const Vector2& other) const {
        return { x - other.x, y - other.y };
    }

    // スカラーとの乗算
    Vector2 operator*(float scalar) const {
        return { x * scalar, y * scalar };
    }

    // ベクトルの大きさを計算
    float magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    // ベクトルを正規化
    Vector2 normalized() const {
        float mag = magnitude();
        return { x / mag, y / mag };
    }
};

// 位置最適化関数
void optimizePositions(float* positions, int count) {
    // 新しい位置を格納するベクトル
    std::vector<Vector2> newPositions(count);

    // 各個体の位置を最適化
    for (int i = 0; i < count; ++i) {
        Vector2 position = { positions[2 * i], positions[2 * i + 1] };
        Vector2 separation = { 0, 0 }; // 分離ベクトル
        Vector2 alignment = { 0, 0 };  // 整列ベクトル
        Vector2 cohesion = { 0, 0 };   // 結合ベクトル
        int neighbors = 0;           // 近傍の個体の数

        // 他のすべての個体と相互作用
        for (int j = 0; j < count; ++j) {
            if (i == j) continue; // 自分自身はスキップ
            Vector2 neighborPosition = { positions[2 * j], positions[2 * j + 1] };
            Vector2 diff = position - neighborPosition;
            float distance = diff.magnitude();

            // 分離のための計算
            if (distance < SEPARATION_RADIUS) {
                separation = separation + diff.normalized() * (SEPARATION_RADIUS - distance);
            }
            // 整列のための計算
            if (distance < ALIGNMENT_RADIUS) {
                alignment = alignment + neighborPosition;
            }
            // 結合のための計算
            if (distance < COHESION_RADIUS) {
                cohesion = cohesion + neighborPosition;
                neighbors++;
            }
        }

        // 近傍の個体が存在する場合
        if (neighbors > 0) {
            alignment = (alignment * (1.0f / neighbors)) - position;
            cohesion = (cohesion * (1.0f / neighbors)) - position;
        }

        // 各力を合成して新しい速度を計算
        Vector2 velocity = separation * SEPARATION_WEIGHT + alignment * ALIGNMENT_WEIGHT + cohesion * COHESION_WEIGHT;
        // 新しい位置を計算
        newPositions[i] = position + velocity;
    }

    // 最適化された新しい位置を更新
    for (int i = 0; i < count; ++i) {
        positions[2 * i] = newPositions[i].x;
        positions[2 * i + 1] = newPositions[i].y;
    }
}