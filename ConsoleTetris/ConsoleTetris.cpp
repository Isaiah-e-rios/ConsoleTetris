// ConsoleTetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

#define MAX_ROW 24
#define MAX_COL 10


void initMap();
void printMap();
void get_L_reg_up(int row, int col, int* movingBlockIndex);
void get_L_reg_down(int row, int col, int* movingBlockIndex);
void setMovingBlock(int *movingBlock);


using namespace std;


class Shape {
    private:
        int shapeIndecies[4];
        int shapeColor;

    public:
        Shape() {
            shapeIndecies[0] = 0;
            shapeIndecies[1] = 0;
            shapeIndecies[2] = 0;
            shapeIndecies[3] = 0;
            shapeColor = 0;
        };
        Shape(int blockOne, int blockTwo, int blockThree, int blockFour) {
            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
            shapeColor = 0;
        };
        Shape(int blockOne, int blockTwo, int blockThree, int blockFour, int color) {
            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
            shapeColor = color;
        };

        void setShape(int blockOne, int blockTwo, int blockThree, int blockFour, int color) {
            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
        };

        //rotates will be defined by shapes
        virtual void rotateShapeLeft() = 0;
        virtual void rotateShapeRight() = 0;
        
        void shiftDown() {
            shapeIndecies[0] += 10;
            shapeIndecies[1] += 10;
            shapeIndecies[2] += 10;
            shapeIndecies[3] += 10;
        };
        void shiftLeft() {
            shapeIndecies[0] -= 1;
            shapeIndecies[1] -= 1;
            shapeIndecies[2] -= 1;
            shapeIndecies[3] -= 1;
        };
        void shiftRight() {
            shapeIndecies[0] += 1;
            shapeIndecies[1] += 1;
            shapeIndecies[2] += 1;
            shapeIndecies[3] += 1;
        };


        int getBlockOneIndex() { return shapeIndecies[0]; };
        int getBlockTwoIndex() { return shapeIndecies[1]; };
        int getBlockThreeIndex() { return shapeIndecies[2]; };
        int getBlockFourIndex() { return shapeIndecies[3]; };

        ~Shape() {};
};

class ShapeL : public Shape {
public:
    void rotateShapeLeft() {};
    void rotateShapeRight() {};
};

class Tetris{
    private:
        int map[MAX_ROW * MAX_COL][2];
        int score;
        Shape *shape;
        
        bool checkBounds() {}
        void initGame();
        void printMap();
        bool checkCompletedRow(int row) {}
        void deleteRow(int row) {};
        void shiftDown(int row) {}

    public:
        void play() {
            initGame();
            printMap();
        };
        void restart() {};
};

void Tetris::initGame() {
    for (int i = 0; i < MAX_ROW * MAX_COL; i++) {
        map[i][0] = 0;
        map[i][1] = 0;
    }
};

void Tetris::printMap(){
    for(int i = 0; i < MAX_ROW; i++) {
        for (int j = 0; j < MAX_COL; j++) {
            cout.width(3);
            cout << map[i * MAX_COL + j][0];
        }
        cout << endl;
    }
};



int main()
{
    Tetris *game = new Tetris();
    game->play();
    cout << "Hello World!\n";
}
