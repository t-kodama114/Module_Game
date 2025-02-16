#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>  // std::reverseを使用するために必要
#include <cfloat>     // FLT_MAXを使用するために必要

// DLLとしてエクスポートする関数を宣言
extern "C" __declspec(dllexport) int* FindPath(int startX, int startY, int goalX, int goalY, int* map, int width, int height, int* pathLength);

// ノードを表す構造体
struct Node {

    // ノードの座標
    int x, y;   

    // g: 開始ノードからのコスト, h: ヒューリスティックコスト（推定コスト）
    float g, h;   

    // 親ノードへのポインタ
    Node* parent;     

    // コンストラクタ
    Node(int x, int y, float g, float h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    // f値を取得する（f = g + h）
    float getF() const
    {
        return g + h;
    }
};

// ノードの比較関数（優先度キュー用）
struct CompareNode {
    bool operator()(const Node* a, const Node* b)
    {
        // f値が小さい方が優先
        return a->getF() > b->getF();
    }
};

// ヒューリスティック関数（ユークリッド距離）
float Heuristic(int x1, int y1, int x2, int y2)
{
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// 経路を再構築し、動的配列として返す関数
int* ReconstructPath(Node* node, int width, int* pathLength)
{
    std::vector<int> path;

    while (node != nullptr)
    {
        // ノードのグリッドインデックスを追加
        path.push_back(node->y * width + node->x);

        // 親ノードに移動
        node = node->parent;
    }

    // 経路を逆順にする
    std::reverse(path.begin(), path.end());

    *pathLength = path.size();
    int* result = new int[*pathLength];

    for (int i = 0; i < *pathLength; ++i)
    {
        result[i] = path[i];
    }

    return result;
}

// A*アルゴリズムで経路を探索する関数
extern "C" __declspec(dllexport) int* FindPath(int startX, int startY, int goalX, int goalY, int* map, int width, int height, int* pathLength)
{
    // 開いているノードの優先度キュー
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;  

    // すべてのノードを格納するマップ
    std::unordered_map<int, Node*> allNodes;  

    // ノードを取得するラムダ関数
    auto getNode = [&](int x, int y) -> Node*
        {
            // グリッドインデックス
            int idx = y * width + x;

            if (allNodes.find(idx) == allNodes.end())
            {
                // 新しいノードを作成
                allNodes[idx] = new Node(x, y, FLT_MAX, Heuristic(x, y, goalX, goalY));
            }

            return allNodes[idx];  // 既存のノードを返す
        };

    // 開始ノードを取得
    Node* startNode = getNode(startX, startY);

    // 開始ノードのg値を0に設定
    startNode->g = 0;

    // 開始ノードを優先度キューに追加
    openList.push(startNode);

    // 移動方向の定義（上下左右）
    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    // 探索ループ
    while (!openList.empty())
    {
        // 優先度キューから現在のノードを取得
        Node* current = openList.top();

        // 優先度キューから削除
        openList.pop();

        // 目標に到達した場合
        if (current->x == goalX && current->y == goalY)
        {
            // 経路を再構築
            int* path = ReconstructPath(current, width, pathLength);

            // すべてのノードを削除
            for (auto& pair : allNodes) delete pair.second;

            // 経路を返す
            return path;  
        }

        // 隣接ノードを探索
        for (const auto& direction : directions)
        {
            // 新しいx座標
            int newX = current->x + direction.first;

            // 新しいy座標
            int newY = current->y + direction.second;

            // マップの範囲内かつ移動可能なタイルであるかを確認
            if (newX >= 0 && newX < width && newY >= 0 && newY < height && map[newY * width + newX] == 0)
            {
                // 隣接ノードを取得
                Node* neighbor = getNode(newX, newY);

                // 仮のg値を計算
                float tentativeG = current->g + 1;

                // より良い経路が見つかった場合
                if (tentativeG < neighbor->g)
                {
                    // g値を更新
                    neighbor->g = tentativeG;

                    // 親ノードを設定
                    neighbor->parent = current;

                    // 隣接ノードを優先度キューに追加
                    openList.push(neighbor);
                }
            }
        }
    }

    // すべてのノードを削除
    for (auto& pair : allNodes) 
    {
        delete pair.second;
    }

    // 経路が見つからなかった場合は0を設定
    *pathLength = 0;  

    // 経路が見つからなかった場合はnullptrを返す
    return nullptr;  
}