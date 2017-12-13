#ifndef ASTAR_H
#define ASTAR_H

#include "Node.h"
#include <list>
#include <memory>
#include <vector>
#include <world.h>

class Astar
{
public:

    bool isDone;

    std::vector<std::shared_ptr<Node>> open;   // sorted list of nodes open for consideration
    std::list<std::shared_ptr<Node>> solution; // the nodes along the path from start to goal

    Astar();

    void find_path(int startP_x, int startP_y, int goalP_x, int goalP_y,
                   const std::vector<std::unique_ptr<Tile>> &tiles,
                   const int &world_rows, const int &world_cols);
    void smartInsert(std::vector<std::shared_ptr<Node>> &aVector,
                           std::shared_ptr<Node> newNode);
};

#endif // ASTAR_H
