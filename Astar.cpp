#include "Astar.h"
#include <iostream>
#include <math.h>
#include <algorithm>

Astar::Astar()
{

}

bool AstarCompare(std::shared_ptr<Node> node1, std::shared_ptr<Node> node2)
{
    return (node1->getTotalCost()>node2->getTotalCost());
}

void Astar::smartInsert(std::vector<std::shared_ptr<Node>> &aVector,
                       std::shared_ptr<Node> newNode)
{
    std::vector<std::shared_ptr<Node>>::iterator it =
            std::lower_bound(aVector.end(),aVector.begin(),
                             newNode,AstarCompare);
    aVector.insert(it,newNode);
}

void Astar::find_path(int startP_x, int startP_y, int goalP_x, int goalP_y,
                      const std::vector<std::unique_ptr<Tile>> &tiles,
                      const int &world_rows, const int &world_cols)
{
    isDone = false;
    bool goalReached = false;
    int offset = world_cols*2 - 1;          //used in find successorNodes

    std::vector<std::shared_ptr<Node>> allNodes(world_cols*world_rows);
    for(int i = 0; i < world_rows; i++) {
        for(int j = 0; j < world_cols; j++) {
            auto newNode = std::make_shared<Node>(j,i);
            newNode->setTileIndex(newNode->getPos_x() + newNode->getPos_y()* world_cols);
            allNodes[j+i*world_cols]=newNode;
        }
    }

    auto rootNode = allNodes[startP_x+startP_y* world_cols];
    rootNode->setParent(nullptr);
    rootNode->setTileIndex(rootNode->getPos_x() + rootNode->getPos_y()* world_cols);
    rootNode->setGivenCost(0.0);
    rootNode->computeHeuristic(goalP_x,goalP_y);
    rootNode->setTotalCost(rootNode->getHcost()+rootNode->getGivenCost());
    auto currentNode = rootNode;
    open.push_back(rootNode);


    while(!open.empty()) {
        currentNode = open.back();  //pop from the back
        open.pop_back();         //remove currentNode from open list
        allNodes[currentNode->getTileIndex()]->setIsInOpen(false);
        int currentP_x = currentNode->getPos_x();
        int currentP_y = currentNode->getPos_y();


        if(currentP_x == goalP_x && currentP_y == goalP_y) {
            while(currentNode != nullptr)
            {
                solution.push_back(currentNode);
                currentNode = currentNode -> getParent();
            }
            goalReached = true;
            break;
        }

        int currentP_index = currentNode -> getTileIndex() - offset;      //used in tiles vector -997-1-1001
        for(int i = currentP_y - 1; i < currentP_y + 2; i++) {           //go through all the nearby points
            currentP_index = currentP_index + world_cols - 3;
            for(int j = currentP_x - 1; j < currentP_x + 2; j++) {
                currentP_index++;

                if(i == currentP_y && j == currentP_x) continue;     //except for the current point itself

                if(i < 0 || i >= world_cols || j < 0 || j >= world_rows) continue;

                if(isinf(tiles[currentP_index] -> getValue())) continue;      // if it is in an illegal spot



                auto successorNode = std::make_shared<Node>(j,i);
                successorNode->setTileIndex(successorNode->getPos_x() + successorNode->getPos_y()* world_cols);
                successorNode->setParent(currentNode);
                successorNode->computeTotalCost(goalP_x, goalP_y, tiles);


                if(allNodes[currentP_index]->getIsInOpen()) {                  //if it is in open list
                    if(successorNode->getGivenCost() < allNodes[currentP_index]->getGivenCost()){
                        allNodes[currentP_index]->setParent(successorNode->getParent());
                        allNodes[currentP_index]->setGivenCost(successorNode->getGivenCost());
                        allNodes[currentP_index]->setTotalCost(successorNode->getTotalCost());

                        smartInsert(open,successorNode);
                    }
                    goto NextPoint;
                }

                if(allNodes[currentP_index]->getIsInClosed()) {                  //if it is in closed list
                    if(successorNode->getGivenCost() < allNodes[currentP_index]->getGivenCost()){
                        allNodes[currentP_index]->setParent(successorNode->getParent());
                        allNodes[currentP_index]->setGivenCost(successorNode->getGivenCost());
                        allNodes[currentP_index]->setTotalCost(successorNode->getTotalCost());

                        allNodes[currentP_index]->setIsInClosed(false);
                        allNodes[currentP_index]->setIsInOpen(true);
                        smartInsert(open,successorNode);
                    }
                    goto NextPoint;
                }


                allNodes[currentP_index]->setIsInOpen(true);
                smartInsert(open,successorNode);

                NextPoint:
                continue;
            }
        }
                allNodes[currentNode->getTileIndex()]->setIsInClosed(true);
    }
    if(goalReached) {
        std::cout<<"solution found!"<<std::endl;
//        std::cout<<"starting point: ("<<startP_x<<","<<startP_y<<")"<<std::endl;
//        std::cout<<"goal point: ("<<goalP_x<<","<<goalP_y<<")"<<std::endl;
//        while(!solution.empty())
//        {
//            auto printNode = solution.back();
//            std::cout<<"-> ("<<printNode->getPos_x()<<","<<printNode->getPos_y()<<") ["<<printNode->getHcost()
//                    <<"] ["<<printNode->getGivenCost()<<"] {"<<printNode->getTotalCost()<<"}"<<std::endl;
//            solution.pop_back();
//        }
    }
    else {
        std::cout<<"the given goal point is unreachable!"<<std::endl;
//        std::cout<<"starting point: ("<<startP_x<<","<<startP_y<<")"<<std::endl;
//        std::cout<<"goal point: ("<<goalP_x<<","<<goalP_y<<")"<<std::endl;
    }
    isDone = true;
    return;
}
