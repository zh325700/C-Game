#ifndef ASTAR_H
#define ASTAR_H

#include <memory>
#include <vector>
#include <world.h>

#include "Node.h"

class Astar
{
public:
    Astar();

    void find_path(int startP_x, int startP_y, int goalP_x, int goalP_y,
                   const std::vector<std::unique_ptr<Tile>> &tiles,
                   const int &world_rows, const int &world_cols);
    void smartInsert(std::vector<std::shared_ptr<Node>> &aVector,
                     std::shared_ptr<Node> newNode);

    void clearSolution();

    /*getters and setters*/
    bool getIsFound() const;
    bool getIsDone() const;
    std::vector<std::shared_ptr<Node> > getSolution() const;

private:
    bool isDone;    //might be useful if we are going to use multi-thread later
    bool isFound;

    std::vector<std::shared_ptr<Node>> open;
    std::vector<std::shared_ptr<Node>> solution;
};

#endif // ASTAR_H
