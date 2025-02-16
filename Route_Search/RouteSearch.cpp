#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <algorithm>  // std::reverse���g�p���邽�߂ɕK�v
#include <cfloat>     // FLT_MAX���g�p���邽�߂ɕK�v

// DLL�Ƃ��ăG�N�X�|�[�g����֐���錾
extern "C" __declspec(dllexport) int* FindPath(int startX, int startY, int goalX, int goalY, int* map, int width, int height, int* pathLength);

// �m�[�h��\���\����
struct Node {

    // �m�[�h�̍��W
    int x, y;   

    // g: �J�n�m�[�h����̃R�X�g, h: �q���[���X�e�B�b�N�R�X�g�i����R�X�g�j
    float g, h;   

    // �e�m�[�h�ւ̃|�C���^
    Node* parent;     

    // �R���X�g���N�^
    Node(int x, int y, float g, float h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent) {}

    // f�l���擾����if = g + h�j
    float getF() const
    {
        return g + h;
    }
};

// �m�[�h�̔�r�֐��i�D��x�L���[�p�j
struct CompareNode {
    bool operator()(const Node* a, const Node* b)
    {
        // f�l�������������D��
        return a->getF() > b->getF();
    }
};

// �q���[���X�e�B�b�N�֐��i���[�N���b�h�����j
float Heuristic(int x1, int y1, int x2, int y2)
{
    return std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
}

// �o�H���č\�z���A���I�z��Ƃ��ĕԂ��֐�
int* ReconstructPath(Node* node, int width, int* pathLength)
{
    std::vector<int> path;

    while (node != nullptr)
    {
        // �m�[�h�̃O���b�h�C���f�b�N�X��ǉ�
        path.push_back(node->y * width + node->x);

        // �e�m�[�h�Ɉړ�
        node = node->parent;
    }

    // �o�H���t���ɂ���
    std::reverse(path.begin(), path.end());

    *pathLength = path.size();
    int* result = new int[*pathLength];

    for (int i = 0; i < *pathLength; ++i)
    {
        result[i] = path[i];
    }

    return result;
}

// A*�A���S���Y���Ōo�H��T������֐�
extern "C" __declspec(dllexport) int* FindPath(int startX, int startY, int goalX, int goalY, int* map, int width, int height, int* pathLength)
{
    // �J���Ă���m�[�h�̗D��x�L���[
    std::priority_queue<Node*, std::vector<Node*>, CompareNode> openList;  

    // ���ׂẴm�[�h���i�[����}�b�v
    std::unordered_map<int, Node*> allNodes;  

    // �m�[�h���擾���郉���_�֐�
    auto getNode = [&](int x, int y) -> Node*
        {
            // �O���b�h�C���f�b�N�X
            int idx = y * width + x;

            if (allNodes.find(idx) == allNodes.end())
            {
                // �V�����m�[�h���쐬
                allNodes[idx] = new Node(x, y, FLT_MAX, Heuristic(x, y, goalX, goalY));
            }

            return allNodes[idx];  // �����̃m�[�h��Ԃ�
        };

    // �J�n�m�[�h���擾
    Node* startNode = getNode(startX, startY);

    // �J�n�m�[�h��g�l��0�ɐݒ�
    startNode->g = 0;

    // �J�n�m�[�h��D��x�L���[�ɒǉ�
    openList.push(startNode);

    // �ړ������̒�`�i�㉺���E�j
    std::vector<std::pair<int, int>> directions = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    // �T�����[�v
    while (!openList.empty())
    {
        // �D��x�L���[���猻�݂̃m�[�h���擾
        Node* current = openList.top();

        // �D��x�L���[����폜
        openList.pop();

        // �ڕW�ɓ��B�����ꍇ
        if (current->x == goalX && current->y == goalY)
        {
            // �o�H���č\�z
            int* path = ReconstructPath(current, width, pathLength);

            // ���ׂẴm�[�h���폜
            for (auto& pair : allNodes) delete pair.second;

            // �o�H��Ԃ�
            return path;  
        }

        // �אڃm�[�h��T��
        for (const auto& direction : directions)
        {
            // �V����x���W
            int newX = current->x + direction.first;

            // �V����y���W
            int newY = current->y + direction.second;

            // �}�b�v�͈͓̔����ړ��\�ȃ^�C���ł��邩���m�F
            if (newX >= 0 && newX < width && newY >= 0 && newY < height && map[newY * width + newX] == 0)
            {
                // �אڃm�[�h���擾
                Node* neighbor = getNode(newX, newY);

                // ����g�l���v�Z
                float tentativeG = current->g + 1;

                // ���ǂ��o�H�����������ꍇ
                if (tentativeG < neighbor->g)
                {
                    // g�l���X�V
                    neighbor->g = tentativeG;

                    // �e�m�[�h��ݒ�
                    neighbor->parent = current;

                    // �אڃm�[�h��D��x�L���[�ɒǉ�
                    openList.push(neighbor);
                }
            }
        }
    }

    // ���ׂẴm�[�h���폜
    for (auto& pair : allNodes) 
    {
        delete pair.second;
    }

    // �o�H��������Ȃ������ꍇ��0��ݒ�
    *pathLength = 0;  

    // �o�H��������Ȃ������ꍇ��nullptr��Ԃ�
    return nullptr;  
}