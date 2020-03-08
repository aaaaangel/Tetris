#include "CMyBlock.h"

using namespace std;
using namespace cv;

CMyBlock::CMyBlock(int id){
    m_direction = 0;
    switch(id){
        //  *
        // ***
        case 0:
            m_height = 2; m_width = 3;
            m_shape[0][1] = 1; m_shape[1][0] = 1; m_shape[1][1] = 1; m_shape[1][2] = 1;
            break;

        //  **
        // **
        case 1:
            m_height = 2; m_width = 3;
            m_shape[0][1] = 1; m_shape[0][2] = 1; m_shape[1][0] = 1; m_shape[1][1] = 1;
            break;

        // **
        //  **
        case 2:
            m_height = 2; m_width = 3;
            m_shape[0][0] = 1; m_shape[0][1] = 1; m_shape[1][1] = 1; m_shape[1][2] = 1;
            break;

        // *
        // ***
        case 3:
            m_height = 2; m_width = 3;
            m_shape[0][0] = 1; m_shape[1][0] = 1; m_shape[1][1] = 1; m_shape[1][2] = 1;
            break;

        //   *
        // ***
        case 4:
            m_height = 2; m_width = 3;
            m_shape[0][2] = 1; m_shape[1][0] = 1; m_shape[1][1] = 1; m_shape[1][2] = 1;
            break;

        // **
        // **
        case 5:
            m_height = 2; m_width = 2;
            m_shape[0][0] = 1; m_shape[0][1] = 1; m_shape[1][0] = 1; m_shape[1][1] = 1;
            break;

        // ****
        case 6:
            m_height = 1; m_width = 4;
            m_shape[0][0] = 1; m_shape[0][1] = 1; m_shape[0][2] = 1; m_shape[0][3] = 1;
            break;
    }
}

void CMyBlock::rotate(){
    // back-up copy
    for(int i=0;i<m_height;i++){
        for(int j=0;j<m_width;j++){
            m_backupShape[i][j] = m_shape[i][j];
        }
    }

    bool temp[4][4]={0};
    int t = m_width;
    m_width = m_height;
    m_height = t;
    for(int i=0;i<m_height;i++){
        for(int j=0;j<m_width;j++){
            temp[i][j] = m_shape[j][i];
        }
    }
    for(int i=0;i<m_height;i++){
        for(int j=0;j<m_width;j++){
            m_shape[i][j] = temp[i][m_width-1-j];
        }
    }
    m_direction = (m_direction+1)%4;
}

void CMyBlock::rotateBack() {
    // back-up copy
    for(int i=0;i<m_height;i++){
        for(int j=0;j<m_width;j++){
            m_shape[i][j] = m_backupShape[i][j];
        }
    }
}