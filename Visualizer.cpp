#include "Visualizer.h"

using namespace std;
using namespace cv;

Visualizer::Visualizer(){
    m_background = Mat(Size(MAP_WIDTH*BLOCK_WIDTH+200, MAP_HEIGHT*BLOCK_WIDTH), CV_8UC3, Scalar(125, 134, 79));
    rectangle(m_background, Rect(MAP_WIDTH*BLOCK_WIDTH, 0, 200, MAP_HEIGHT*BLOCK_WIDTH/2), Scalar(134, 247, 234), 5);
    rectangle(m_background, Rect(MAP_WIDTH*BLOCK_WIDTH, MAP_HEIGHT*BLOCK_WIDTH/2, 200, MAP_HEIGHT*BLOCK_WIDTH/2), Scalar(134, 247, 234), 5);
    cv::putText(m_background, "MOVE(left/right)", Point(MAP_WIDTH*BLOCK_WIDTH + 25, MAP_HEIGHT*BLOCK_WIDTH/2 + 50), 1, 1, Scalar(134, 247, 234), 2);
    cv::putText(m_background, "TRANSFORM(up)", Point(MAP_WIDTH*BLOCK_WIDTH + 25, MAP_HEIGHT*BLOCK_WIDTH/2 + 100), 1, 1, Scalar(134, 247, 234), 2);
    cv::putText(m_background, "FALL(down)", Point(MAP_WIDTH*BLOCK_WIDTH + 25, MAP_HEIGHT*BLOCK_WIDTH/2 + 150), 1, 1, Scalar(134, 247, 234), 2);


    // add text
    imshow("Tetris", m_background);
}

void Visualizer::visualize(bool map[MAP_HEIGHT][MAP_WIDTH]) {
    Mat unitBlock(Size(BLOCK_WIDTH, BLOCK_WIDTH), CV_8UC3, Scalar(161, 181, 255));
    rectangle(unitBlock, Rect(0, 0, BLOCK_WIDTH, BLOCK_WIDTH), Scalar(134, 247, 234), 4);
    m_map = Mat(Size(MAP_WIDTH*BLOCK_WIDTH, MAP_HEIGHT*BLOCK_WIDTH), CV_8UC3, Scalar(205, 217, 95));
    for(int i=0;i<MAP_HEIGHT;i++){
        for(int j=0;j<MAP_WIDTH;j++){
            if(map[i][j])
                unitBlock.copyTo(m_map(Rect(j*BLOCK_WIDTH, i*BLOCK_WIDTH, BLOCK_WIDTH, BLOCK_WIDTH)));
        }
    }
    m_map.copyTo(m_background(Rect(0,0,MAP_WIDTH*BLOCK_WIDTH, MAP_HEIGHT*BLOCK_WIDTH)));
    imshow("Tetris", m_background);
}
