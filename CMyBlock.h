#ifndef RUSSIASQUARE_CMYBLOCK_H
#define RUSSIASQUARE_CMYBLOCK_H

#include <opencv2/core/core.hpp>

#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

class CMyBlock {
public:
    CMyBlock(int id);
    int m_direction;
    bool m_shape[4][4]={0};
    bool m_backupShape[4][4]={0};
    int m_height;
    int m_width;
//    vector<Mat> vecPatterns;
    int m_posX;
    int m_posY;

    void rotate();
    void rotateBack();

private:
//    Mat genPattern();
};


#endif //RUSSIASQUARE_CMYBLOCK_H
