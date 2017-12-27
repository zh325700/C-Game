#ifndef NODE_H
#define NODE_H

#include <memory>
#include <vector>
#include <world.h>

class Node
{
public:

    Node(int apos_x, int apos_y);

    void computeHeuristic(const int &goalP_x, const int &goalP_y);
    void computeGivenCost(const std::vector<std::unique_ptr<Tile> > &tiles);
    void computeTotalCost(const int &goalP_x, const int &goalP_y, const std::vector<std::unique_ptr<Tile> > &tiles);

    std::shared_ptr<Node> getParent() const;
    void setParent(const std::shared_ptr<Node> &value);
    int getPos_x() const;
    void setPos_x(int value);
    int getPos_y() const;
    void setPos_y(int value);
    int getTileIndex() const;
    void setTileIndex(int value);
    int getHcost() const;
    void setHcost(int value);
    float getGivenCost() const;
    void setGivenCost(float value);
    bool getIsInOpen() const;
    void setIsInOpen(bool value);
    bool getIsInClosed() const;
    void setIsInClosed(bool value);
    float getTotalCost() const;
    void setTotalCost(float value);

    void setW(float value);
    float getW() const;

private:

    int pos_x;
    int pos_y;
    int hcost;
    int tileIndex;
    float givenCost;
    bool isInOpen;
    bool isInClosed;
    float totalCost;

    /* This will control the CPU and memory usage vs. optimality of the solution.
     * The lager the value of w, the more Best-First the A* algorithm will behave.
     * The smaller the value of w, the more Dijkstra the A* algorithm will be. */
    float w = 1.0;

    std::shared_ptr<Node> parent;
};

#endif // NODE_H
