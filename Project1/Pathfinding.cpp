#include "Pathfinding.hpp"
#include <queue>
#include <unordered_map>

class CompareNodePtr {
public:
    bool operator()(const Node* a, const Node* b) const {
        return a->fCost > b->fCost;
    }
};

struct Vector2iHash {
    size_t operator()(const Vector2i& v) const {
        return std::hash<int>()(v.x) ^ (std::hash<int>()(v.y) << 1);
    }
};

vector<Vector2i> Pathfinding::findPath(Grid& grid, Vector2i start, Vector2i end) {
    priority_queue<Node*, vector<Node*>, CompareNodePtr> openQueue;
    unordered_map<Vector2i, Node*, Vector2iHash> allNodes;
    vector<Vector2i> directions = {
        {0, 1}, {1, 0}, {0, -1}, {-1, 0},
        {-1, -1}, {1, -1}, {1, 1}, {-1, 1}
    };

    Node* startNode = new Node(start);
    startNode->gCost = 0;
    startNode->hCost = startNode->calculateHeuristic(end);
    startNode->fCost = startNode->gCost + startNode->hCost;

    openQueue.push(startNode);
    allNodes[start] = startNode;

    while (!openQueue.empty()) {
        Node* current = openQueue.top();
        openQueue.pop();

        if (current->position == end) {
            vector<Vector2i> path;
            while (current) {
                path.push_back(current->position);
                current = current->parent;
            }
            std::reverse(path.begin(), path.end());

            for (auto& pair : allNodes) delete pair.second;
            return path;
        }

        for (auto& dir : directions) {
            Vector2i neighborPos = current->position + dir;

            if (neighborPos.x < 0 || neighborPos.x >= GRID_WIDTH || neighborPos.y < 0 || neighborPos.y >= GRID_HEIGHT)
                continue;
            if (!grid.isWalkable(Vector2f(neighborPos.x * CELL_SIZE, neighborPos.y * CELL_SIZE)))
                continue;

            if ((dir.x != 0 && dir.y != 0) &&
                (!grid.isWalkable(Vector2f(current->position.x * CELL_SIZE, neighborPos.y * CELL_SIZE)) ||
                    !grid.isWalkable(Vector2f(neighborPos.x * CELL_SIZE, current->position.y * CELL_SIZE))))
                continue;

            int newGCost = current->gCost + ((dir.x != 0 && dir.y != 0) ? 14 : 10);

            Node* neighbor;
            if (allNodes.find(neighborPos) != allNodes.end()) {
                neighbor = allNodes[neighborPos];
                if (newGCost < neighbor->gCost) {
                    neighbor->gCost = newGCost;
                    neighbor->fCost = newGCost + neighbor->hCost;
                    neighbor->parent = current;
                    openQueue.push(neighbor);
                }
            }
            else {
                neighbor = new Node(neighborPos);
                neighbor->gCost = newGCost;
                neighbor->hCost = neighbor->calculateHeuristic(end);
                neighbor->fCost = neighbor->gCost + neighbor->hCost;
                neighbor->parent = current;
                openQueue.push(neighbor);
                allNodes[neighborPos] = neighbor;
            }
        }
    }

    for (auto& pair : allNodes) delete pair.second;
    return {};
}
