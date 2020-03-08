#ifndef RUSSIASQUARE_CONTROLLER_H
#define RUSSIASQUARE_CONTROLLER_H

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include <iostream>
#include <string>
#include <vector>
#include <time.h>

#include "CMyBlock.h"
#include "Visualizer.h"

#define MAP_HEIGHT 24
#define MAP_WIDTH 12

using namespace std;
using namespace cv;

class Controller {
public:
    Controller(int stepTime);
    void InitBlocks();

    bool m_map[MAP_HEIGHT][MAP_WIDTH] = {0};
    int m_curBlockId;
    int m_nextBlockId;

    Visualizer m_visualizer;

    void run();
    bool genBlock(int id);
    bool checkBlock(const int& posX, const int& posY, const CMyBlock& block);
    void copyBlockToMap(const int& posX, const int& posY, const CMyBlock& block);
    void deleteBlockFromMap(const int& posX, const int& posY, const CMyBlock& block);

    bool removeLines();

private:
    int m_stepTime;
    vector<CMyBlock> vecBlockList;




};


#endif //RUSSIASQUARE_CONTROLLER_H
