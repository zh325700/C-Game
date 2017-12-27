#include "Node.h"
#include "math.h"
#include "iostream"


std::shared_ptr<Node> Node::getParent() const
{
    return parent;
}

void Node::setParent(const std::shared_ptr<Node> &value)
{
    parent = value;
}

int Node::getPos_x() const
{
    return pos_x;
}

void Node::setPos_x(int value)
{
    pos_x = value;
}

int Node::getPos_y() const
{
    return pos_y;
}

void Node::setPos_y(int value)
{
    pos_y = value;
}


void Node::computeHeuristic(const int &goalP_x, const int &goalP_y)
{
//    float cost = sqrt(pow((this->getPos_x() - goalP_x),2)+pow((this->getPos_y() - goalP_y),2));
    int cost = abs(this->getPos_x() - goalP_x)+abs(this->getPos_y() - goalP_y);
    this->setHcost(cost);
}

void Node::computeGivenCost(const std::vector<std::unique_ptr<Tile> > &tiles)
{
    std::shared_ptr<Node> parentNode = this -> getParent();
    float oneStepCost = 0.0;
    int currentIndex = this->getTileIndex();
    int parentIndex = parentNode->getTileIndex();
    oneStepCost = abs(tiles[currentIndex]->getValue()-tiles[parentIndex]->getValue());
    if(this->getPos_x()!=parentNode->getPos_x() && this->getPos_y()!=parentNode->getPos_y())
    {
        oneStepCost = oneStepCost * 1.4142;
    }
    this->setGivenCost(oneStepCost + parentNode->getGivenCost());
}

void Node::computeTotalCost(const int &goalP_x, const int &goalP_y, const std::vector<std::unique_ptr<Tile> > &tiles)
{
    /*compute hcost*/
    int newHcost = abs(this->getPos_x() - goalP_x)+abs(this->getPos_y() - goalP_y);
    this->setHcost(newHcost);
    /*compute givenCost*/
    std::shared_ptr<Node> parentNode = this -> getParent();
    float oneStepCost = 0.0;
    int currentIndex = this->getTileIndex();
    int parentIndex = parentNode->getTileIndex();
    oneStepCost = abs(tiles[currentIndex]->getValue()-tiles[parentIndex]->getValue());
    if(this->getPos_x()!=parentNode->getPos_x() && this->getPos_y()!=parentNode->getPos_y())
    {
        oneStepCost = oneStepCost * 1.4142;
    }
    float newGivenCost = oneStepCost + parentNode->getGivenCost();
    this->setGivenCost(newGivenCost);
    /*compute totalCost*/
    this->setTotalCost(w*newHcost+newGivenCost);
}

int Node::getTileIndex() const
{
    return tileIndex;
}

void Node::setTileIndex(int value)
{
    tileIndex = value;
}

int Node::getHcost() const
{
    return hcost;
}

void Node::setHcost(int value)
{
    hcost = value;
}

float Node::getGivenCost() const
{
    return givenCost;
}

void Node::setGivenCost(float value)
{
    givenCost = value;
}

bool Node::getIsInOpen() const
{
    return isInOpen;
}

void Node::setIsInOpen(bool value)
{
    isInOpen = value;
}

bool Node::getIsInClosed() const
{
    return isInClosed;
}

void Node::setIsInClosed(bool value)
{
    isInClosed = value;
}

float Node::getTotalCost() const
{
    return totalCost;
}

void Node::setTotalCost(float value)
{
    totalCost = value;
}

void Node::setW(float value)
{
    w = value;
}

float Node::getW() const
{
    return w;
}

Node::Node(int apos_x, int apos_y) :
    pos_x{apos_x},pos_y{apos_y},hcost{0},tileIndex{0},givenCost{0.0},isInOpen{false},isInClosed{false},totalCost{0.0}
{

}
