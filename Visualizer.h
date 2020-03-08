#ifndef RUSSIASQUARE_VISUALIZER_H
#define RUSSIASQUARE_VISUALIZER_H

#define MAP_HEIGHT 24
#define MAP_WIDTH 12
#define BLOCK_WIDTH 30


#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

class Visualizer {
public:
    Visualizer();
    Mat m_background;
    Mat m_map;

    void visualize(bool map[MAP_HEIGHT][MAP_WIDTH]);

};


#endif //RUSSIASQUARE_VISUALIZER_H
