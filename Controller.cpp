#include "Controller.h"

using namespace std;

Controller::Controller(int stepTime):
m_stepTime(stepTime)
{
    for(int i=0; i<7; i++){
        vecBlockList.push_back(CMyBlock(i));
    }

    m_nextBlockId = rand()%7;


}

//void Controller::InitBlocks() {
//    // create a 2*3 square
//    Mat basicBlock(Size(60, 40), CV_8UC3, Scalar(255, 255, 0));
//    line(basicBlock, Point(0, 20), Point(60, 20), Scalar(1, 0, 200), 2);
//    line(basicBlock, Point(20, 0), Point(20, 40), Scalar(1, 0, 200), 2);
//    line(basicBlock, Point(40, 0), Point(40, 40), Scalar(1, 0, 200), 2);
//    rectangle(basicBlock, Rect(0, 0, 60, 40), Scalar(1, 0, 200), 4);
//
//    // create a 1*1 black square
//    Mat merge_block(Size(20, 20), CV_8UC3, Scalar(0, 0, 0));
//
//    //  *
//    // ***
//    Mat block0 = basicBlock.clone();
//    merge_block.convertTo(block1(Rect(0,0,20,20)));
//    merge_block.convertTo(block1(Rect(40,0,20,20)));
//    block_list_.push_back(block0);
//
//    //  **
//    // **
//    Mat block1 = basicBlock.clone();
//    merge_block.convertTo(block1(Rect(0,0,20,20)));
//    merge_block.convertTo(block1(Rect(40,20,20,20)));
//    block_list_.push_back(block1);
//
//    // **
//    //  **
//    Mat block2 = basicBlock.clone();
//    merge_block.convertTo(block1(Rect(40,0,20,20)));
//    merge_block.convertTo(block1(Rect(0,20,20,20)));
//    block_list_.push_back(block2);
//
//    // *
//    // ***
//    Mat block3 = basicBlock.clone();
//    merge_block.convertTo(block1(Rect(20,0,20,20)));
//    merge_block.convertTo(block1(Rect(40,0,20,20)));
//    block_list_.push_back(block3);
//
//    //   *
//    // ***
//    Mat block4 = basicBlock.clone();
//    merge_block.convertTo(block1(Rect(0,0,20,20)));
//    merge_block.convertTo(block1(Rect(20,0,20,20)));
//    block_list_.push_back(block4);
//
//    // **
//    // **
//    Mat block5 = basicBlock.clone();
//    merge_block.convertTo(block1(Rect(40,0,20,20)));
//    merge_block.convertTo(block1(Rect(40,20,20,20)));
//    block_list_.push_back(block5);
//
//    // ****
//    Mat block6(Size(80, 20), CV_8UC3, Scalar(255, 255, 0));
//    line(basicBlock, Point(20, 0), Point(20, 20), Scalar(1, 0, 200), 2);
//    line(basicBlock, Point(40, 0), Point(40, 20), Scalar(1, 0, 200), 2);
//    line(basicBlock, Point(60, 0), Point(60, 20), Scalar(1, 0, 200), 2);
//    block_list_.push_back(block6);
//}

void Controller::run(){
    m_nextBlockId = rand()%7;
    m_curBlockId = m_nextBlockId;
    while(genBlock(m_curBlockId))   // success down
    {
        m_nextBlockId = rand()%7;
        m_curBlockId = m_nextBlockId;

//        cout<<m_curBlockId<<endl;
        if(removeLines()){
            m_visualizer.visualize(m_map);
        }
    }
}

bool Controller::genBlock(int id) {
    CMyBlock curBlock(id);
    int curPosX = rand()%(MAP_WIDTH-1);
    if(curPosX + curBlock.m_width > MAP_WIDTH)
        curPosX = MAP_WIDTH - curBlock.m_width;
    cout<<curPosX<<endl;
    int curPosY = -curBlock.m_height;

    while(true){
        int key = waitKey(m_stepTime);
        switch(key){
            case 0:  // rotate
                deleteBlockFromMap(curPosX, curPosY, curBlock);
                curBlock.rotate();
                if(curPosX+curBlock.m_width > MAP_WIDTH || !checkBlock(curPosX, curPosY, curBlock))
                    curBlock.rotateBack();
                copyBlockToMap(curPosX, curPosY, curBlock);
                m_visualizer.visualize(m_map);
                break;

            case 1:   // down
                deleteBlockFromMap(curPosX, curPosY, curBlock);
                while(curPosY+1+curBlock.m_height<=MAP_HEIGHT && checkBlock(curPosX, curPosY+1, curBlock))
                    curPosY++;
                copyBlockToMap(curPosX, curPosY, curBlock);
                m_visualizer.visualize(m_map);
                if(curPosY>=0)
                    return true;
                else
                    return false;

            case 2:  // left
                deleteBlockFromMap(curPosX, curPosY, curBlock);
                if(curPosX - 1 >= 0 && checkBlock(curPosX - 1, curPosY, curBlock))
                    curPosX--;
                copyBlockToMap(curPosX, curPosY, curBlock);
                m_visualizer.visualize(m_map);
                break;

            case 3: // right
                deleteBlockFromMap(curPosX, curPosY, curBlock);
                if(curPosX + 1 + curBlock.m_width <= MAP_WIDTH && checkBlock(curPosX + 1, curPosY, curBlock))
                    curPosX++;
                copyBlockToMap(curPosX, curPosY, curBlock);
                m_visualizer.visualize(m_map);
                break;

            default: // fall
                deleteBlockFromMap(curPosX, curPosY, curBlock);
                if(curPosY+1+curBlock.m_height<=MAP_HEIGHT && checkBlock(curPosX, curPosY+1, curBlock)) {
                    curPosY++;
                    copyBlockToMap(curPosX, curPosY, curBlock);
                    m_visualizer.visualize(m_map);
                } else{
                    copyBlockToMap(curPosX, curPosY, curBlock);
                    m_visualizer.visualize(m_map);
                    if(curPosY<0)
                        return false;
                    else
                        return true;
                }
        }
    }


}

bool Controller::checkBlock(const int& posX, const int& posY, const CMyBlock& block){
    for(int i=0;i<block.m_height;i++){
        if(posY+i<0) continue;
        for(int j=0;j<block.m_width;j++){
            if(block.m_shape[i][j] && m_map[posY+i][posX+j])
                return false;
        }
    }
    return true;
}

void Controller::copyBlockToMap(const int& posX, const int& posY, const CMyBlock& block){
    for(int i=posY;i<posY+block.m_height;i++){
        if(i<0) continue;
        for(int j=posX;j<posX+block.m_width;j++){
            if(block.m_shape[i-posY][j-posX])
                m_map[i][j] = block.m_shape[i-posY][j-posX];
        }
    }
}

void Controller::deleteBlockFromMap(const int& posX, const int& posY, const CMyBlock& block){
    for(int i=posY;i<posY+block.m_height;i++){
        if(i<0) continue;
        for(int j=posX;j<posX+block.m_width;j++){
            if(block.m_shape[i-posY][j-posX])
                m_map[i][j] = 0;
        }
    }
}

bool Controller::removeLines() {
    bool isRemove = false;
    bool lineRemoveState[MAP_HEIGHT] = {0};
    int j;
    for(int i=0; i<MAP_HEIGHT; i++){
        for(j=0; j<MAP_WIDTH; j++){
            if(m_map[i][j]==0){
                break;
            }
        }

        if(j==MAP_WIDTH){
            lineRemoveState[i] = 1;
            isRemove = true;
        }
    }

    if(!isRemove)
        return isRemove;

    int downNum=0;
    for(int i=MAP_HEIGHT-1; i>0; i--){
        if(lineRemoveState[i])
            downNum++;
        if(downNum==0)
            continue;
        else{
            for(int j=0; j<MAP_WIDTH; j++)
                if(i-downNum>=0)
                    m_map[i][j]=m_map[i-downNum][j];
        }
    }

    if(lineRemoveState[0]){
        for(int j=0; j<MAP_WIDTH; j++)
            m_map[0][j]=0;
    }

    return isRemove;
}