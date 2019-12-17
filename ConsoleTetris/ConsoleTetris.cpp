// ConsoleTetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>

#define MAX_ROW 24
#define MAX_COL 10



using namespace std;


class Shape {
    private:
        int previousIndecies[4];
        int shapeIndecies[4];
        int shapeColor;

        void setPevious() {
            previousIndecies[0] = shapeIndecies[0];
            previousIndecies[1] = shapeIndecies[1];
            previousIndecies[2] = shapeIndecies[2];
            previousIndecies[3] = shapeIndecies[3];
        }

    public:
        Shape() {
            shapeIndecies[0] = 0;
            shapeIndecies[1] = 0;
            shapeIndecies[2] = 0;
            shapeIndecies[3] = 0;
            this->setPevious();
            shapeColor = 0;
        }
        Shape(int blockOne, int blockTwo, int blockThree, int blockFour) {
            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
            this->setPevious();
            shapeColor = 0;
        }
        Shape(int blockOne, int blockTwo, int blockThree, int blockFour, int color) {
            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
            this->setPevious();
            shapeColor = color;
        }

        void setShape(int blockOne, int blockTwo, int blockThree, int blockFour) {
            this->setPevious();

            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
        }

        //rotates will be defined by shapes
        virtual void rotateShapeLeft() = 0;
        virtual void rotateShapeRight() = 0;


        void undoMove(){
            this->setPevious();
            shapeIndecies[0] = previousIndecies[0];
            shapeIndecies[1] = previousIndecies[1];
            shapeIndecies[2] = previousIndecies[2];
            shapeIndecies[3] = previousIndecies[3];
        }
        void shiftDown() {
            this->setPevious();
            shapeIndecies[0] += MAX_COL;
            shapeIndecies[1] += MAX_COL;
            shapeIndecies[2] += MAX_COL;
            shapeIndecies[3] += MAX_COL;
        }
        void shiftLeft() {
            if (shapeIndecies[0] / MAX_COL == (shapeIndecies[0] - 1) / MAX_COL && shapeIndecies[1] / MAX_COL == (shapeIndecies[1] - 1) / MAX_COL &&
                shapeIndecies[2] / MAX_COL == (shapeIndecies[2] - 1) / MAX_COL && shapeIndecies[3] / MAX_COL == (shapeIndecies[3] - 1) / MAX_COL)
            {
                shapeIndecies[0] -= 1;
                shapeIndecies[1] -= 1;
                shapeIndecies[2] -= 1;
                shapeIndecies[3] -= 1;
            }
        }
        void shiftRight() {
            if (shapeIndecies[0] / MAX_COL == (shapeIndecies[0] + 1) / MAX_COL && shapeIndecies[1] / MAX_COL == (shapeIndecies[1] + 1) / MAX_COL &&
                shapeIndecies[2] / MAX_COL == (shapeIndecies[2] + 1) / MAX_COL && shapeIndecies[3] / MAX_COL == (shapeIndecies[3] + 1) / MAX_COL)
            {
                shapeIndecies[0] += 1;
                shapeIndecies[1] += 1;
                shapeIndecies[2] += 1;
                shapeIndecies[3] += 1;
            }
        }

        int getColor() { return shapeColor; }
        int getBlockOneIndex() { return shapeIndecies[0]; }
        int getBlockTwoIndex() { return shapeIndecies[1]; }
        int getBlockThreeIndex() { return shapeIndecies[2]; }
        int getBlockFourIndex() { return shapeIndecies[3]; }

        ~Shape() {};
};

//Shape L
//0(Right) 1(up) 2(Left) 3(Down)
// * * *    *          *    * *
// *     -> *   -> * * * ->   *
//          * *               *
class ShapeL : public Shape {
private: 
    int orientation;


    void setUp(int origin) {
        if ((origin + MAX_COL + 1) / MAX_COL == (origin + MAX_COL) / MAX_COL) {
            orientation = 1;
            this->setShape(origin - MAX_COL, origin, origin + MAX_COL, origin + MAX_COL + 1);
        }
        else{
            setUp(origin - 1);
        }
        
    }
    void setDown(int origin) {
        if ((origin - MAX_COL - 1) / MAX_COL == (origin - MAX_COL) / MAX_COL) {
            orientation = 3;
            this->setShape(origin + MAX_COL, origin, origin - MAX_COL, origin - MAX_COL - 1);
        }
        else {
            //setDown(origin + 1);
        }
    }
    void setLeft(int origin) {
        orientation = 2;
        if ((origin + 1) / MAX_COL == (origin) / MAX_COL) {
            if ((origin - 1) / MAX_COL == (origin) / MAX_COL) {
                this->setShape(origin - 1, origin, origin + 1, origin - MAX_COL + 1);
            }
            else {
                setLeft(origin + 1);
            }
        }
        else {
            setLeft(origin - 1);
        }
    }
    void setRight(int origin) {
        if ((origin + 1) / MAX_COL == (origin) / MAX_COL) {
            if ((origin - 1) / MAX_COL == (origin) / MAX_COL) {
                orientation = 0;
                this->setShape(origin + 1, origin, origin - 1, origin + MAX_COL - 1);
            }
            else {
                setRight(origin + 1);
            }
        }
        else {
            setRight(origin - 1);
        }
    }
public:
    ShapeL(int color):Shape((MAX_COL / 2)-1, MAX_COL / 2, (MAX_COL / 2)+1, MAX_COL + (MAX_COL / 2) - 1, color){
        orientation = 0;
    }
    void rotateShapeLeft() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setUp(origin);

        }
        else if (orientation == 1) {
            setLeft(origin);
        }
        else if (orientation == 2){
            setDown(origin);
        }
        else {
            setRight(origin);
        }
    };
    void rotateShapeRight() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setDown(origin);
        }
        else if (orientation == 1) {
            setRight(origin);
        }
        else if (orientation == 2) {
            setUp(origin);
        }
        else {
            setLeft(origin);
        }
    };
};

//shape J
//   0(left)  1(up)   2(right)   3(down)
// * * *      *        *          * *
//     * ->   *   ->   * * * ->   *
//          * *                   *
class ShapeJ : public Shape {
private:
    int orientation;

    void setUp(int origin) {
        if ((origin + MAX_COL - 1) / MAX_COL == (origin + MAX_COL) / MAX_COL) {
            orientation = 1;
            this->setShape(origin - MAX_COL, origin, origin + MAX_COL, origin + MAX_COL - 1);
        }
        else {
            setUp(origin + 1);
        }
    }
    void setDown(int origin) {
        if ((origin - MAX_COL + 1) / MAX_COL == (origin - MAX_COL) / MAX_COL) {
            orientation = 3;
            this->setShape(origin + MAX_COL, origin, origin - MAX_COL, origin - MAX_COL + 1);
        }
        else {
            setDown(origin - 1);
        }
    }
    void setLeft(int origin) {
        orientation = 0;
        if ((origin + 1) / MAX_COL == (origin) / MAX_COL) {
            if ((origin - 1) / MAX_COL == (origin) / MAX_COL) {
                this->setShape(origin - 1, origin, origin + 1, origin + MAX_COL + 1);
            }
            else {
                setLeft(origin + 1);
            }
        }
        else {
            setLeft(origin - 1);
        }
    }
    void setRight(int origin) {
        if ((origin + 1) / MAX_COL == (origin) / MAX_COL && (origin - 1) / MAX_COL == (origin) / MAX_COL) {
            orientation = 2;
            this->setShape(origin + 1, origin, origin - 1, origin - MAX_COL - 1);
        }
    }
public:
    ShapeJ(int color) :Shape((MAX_COL / 2) - 1, MAX_COL / 2, (MAX_COL / 2) + 1, MAX_COL + (MAX_COL / 2) + 1, color) {
        orientation = 0;
    }
    void rotateShapeLeft() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setDown(origin);
        }
        else if (orientation == 1) {
            setLeft(origin);
        }
        else if (orientation == 2) {
            setUp(origin);
        }
        else {
            setRight(origin);
        }
    };
    void rotateShapeRight() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setUp(origin);
        }
        else if (orientation == 1) {
            setRight(origin);
        }
        else if (orientation == 2) {
            setDown(origin);
        }
        else {
            setLeft(origin);
        }
    };
};

//Shape O
// * *
// * *
class ShapeO : public Shape {
public:
    ShapeO(int color) :Shape((MAX_COL / 2) - 1, MAX_COL / 2, MAX_COL + (MAX_COL / 2) -1, MAX_COL + (MAX_COL / 2), color) {}
    void rotateShapeLeft() {};
    void rotateShapeRight() {};
};

//S Shape
//0(down) 1(up)
//  * * -> *
//* *   -> * *
//           *
class ShapeS : public Shape {
private:
    int orientation;

    void setDown(int origin) {
        if ((origin + 1) / MAX_COL == origin / MAX_COL && (origin - 1 + MAX_COL) / MAX_COL == (origin + MAX_COL) / MAX_COL) {
            orientation = 0;
            this->setShape(origin + 1, origin, origin + MAX_COL, origin + MAX_COL - 1);
        }
    }
    void setUp(int origin) {
        if ((origin + 1) / MAX_COL == origin / MAX_COL) {
            orientation = 1;
            this->setShape(origin - MAX_COL, origin, origin + 1, origin + MAX_COL + 1);
        }
    }
public:
    ShapeS(int color) :Shape((MAX_COL / 2) + 1, MAX_COL / 2, MAX_COL + (MAX_COL / 2) - 1, MAX_COL + (MAX_COL / 2), color) {
        orientation = 0;
    }
    void rotateShapeLeft() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setUp(origin);
        }
        else {
            setDown(origin);
        }
    };
    void rotateShapeRight() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setUp(origin);
        }
        else {
            setDown(origin);
        }
    };
};

//Z Shape
//0(down) 1(up)
//* *   ->   *
//  * * -> * *
//         *
class ShapeZ : public Shape {
private:
    int orientation;

    void setDown(int origin) {
        if ((origin - 1) / MAX_COL == origin / MAX_COL && (origin + 1 + MAX_COL) / MAX_COL == (origin + MAX_COL) / MAX_COL) {
            orientation = 0;
            this->setShape(origin - 1, origin, origin + MAX_COL, origin + MAX_COL + 1);
        }
    }
    void setUp(int origin) {
        if ((origin - 1) / MAX_COL == origin / MAX_COL) {
            orientation = 1;
            this->setShape(origin - MAX_COL, origin, origin - 1, origin + MAX_COL - 1);
        }
    }
public:
    ShapeZ(int color) :Shape((MAX_COL / 2) - 1, MAX_COL / 2, MAX_COL + (MAX_COL / 2) + 1, MAX_COL + (MAX_COL / 2), color) {
        orientation = 0;
    }
    void rotateShapeLeft() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setUp(origin);
        }
        else {
            setDown(origin);
        }
    };
    void rotateShapeRight() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setUp(origin);
        }
        else {
            setDown(origin);
        }
    };

    
};

//I shape
//  0(down)   1(up)
//             *
//* * * * ->   *
//             *
//             *
class ShapeI : public Shape {
private:
    int orientation;

    void setDown(int origin) {
        if ((origin + 2) / MAX_COL == origin / MAX_COL && (origin - 1) / MAX_COL == origin / MAX_COL) {
            orientation = 0;
            this->setShape(origin - 1, origin, origin + 1, origin + 2);
        }
    };
    void setUp(int origin) {
        orientation = 1;
        this->setShape(origin - MAX_COL, origin, origin + MAX_COL, origin + MAX_COL * 2);
    }
public:
    ShapeI(int color) :Shape((MAX_COL / 2) - 2, (MAX_COL / 2)-1, (MAX_COL / 2), (MAX_COL / 2) + 1, color) {
        orientation = 0;
    }
    void rotateShapeLeft() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0)
            setUp(origin);
        else
            setDown(origin);
    };
    void rotateShapeRight() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0)
            setUp(origin);
        else
            setDown(origin);
    };
};
//T shape
//(0)down  (1)right (2)up   (3)left
//            *       *       *
// * * * -> * * ->  * * * ->  * *
//   *        *               *
class ShapeT : public Shape {
private:
    int orientation;

    void setUp(int origin) {
        if ((origin - 1) / MAX_COL == (origin+1) / MAX_COL) {
            orientation = 2;
            this->setShape(origin - 1, origin, origin + 1, origin + MAX_COL);
        }
    }
    void setDown(int origin) {
        if ((origin - 1) / MAX_COL == (origin + 1) / MAX_COL) {
            orientation = 0;
            this->setShape(origin - 1, origin, origin + 1, origin - MAX_COL);
        }
    }
    void setLeft(int origin) {
        if ((origin + 1) / MAX_COL == (origin) / MAX_COL) {
            orientation = 3;
            this->setShape(origin - MAX_COL, origin, origin + MAX_COL, origin + 1);
        }
    }
    void setRight(int origin) {
        if ((origin - 1) / MAX_COL == (origin) / MAX_COL) {
            orientation = 1;
            this->setShape(origin + MAX_COL, origin, origin - MAX_COL, origin - 1);
        }
    }


public:
    ShapeT(int color) :Shape((MAX_COL / 2) - 1, MAX_COL / 2, (MAX_COL / 2) + 1, MAX_COL + (MAX_COL / 2), color) {
        orientation = 0;
    }
    void rotateShapeLeft() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setRight(origin);
        }
        else if (orientation == 1) {
            setUp(origin);
        }
        else if (orientation == 2) {
            setLeft(origin);
        }
        else {
            setDown(origin);
        }

    };
    void rotateShapeRight() {
        int origin = this->getBlockTwoIndex();
        if (orientation == 0) {
            setLeft(origin);
        }
        else if (orientation == 1) {
            setDown(origin);
        }
        else if (orientation == 2) {
            setRight(origin);
        }
        else if (orientation == 3) {
            setUp(origin);
        }
    };
};

//Map has col*row items of [led index][on or off][color value]
class Tetris{
    private:
        int map[MAX_ROW * MAX_COL][3];
        int score;
        Shape *shape;


        bool checkBound(int moveValue);
        void initGame(); 
        void printMap();

        void createShape();
        void checkCompletedRows();
        void deleteRow(int row);
        void shiftBlocksDown(int row);
        void shapeOnOff(Shape *s);
        void switchLED(int ledNumber, int color);

        //Controll Calls
        void moveShapeLeft();
        void moveShapeRight();
        bool moveShapeDown();

        void rotateShapeLeft();
        void rotateShapeRight();
    public:
        Tetris() {

        }
        void play();
        void restart() {};
};

//Row Completion
void Tetris::checkCompletedRows() {
    int filledCount;
    for (int i = 0; i < MAX_ROW; i++) {
        filledCount = 0;
        for (int j = 0; j < MAX_COL; j++) {
            if (map[i * MAX_COL + j][1] == 1) {
                filledCount++;
            }
            else {
                filledCount = 0;
                j = MAX_COL;
            }
        }
        if (filledCount == MAX_COL) {
            deleteRow(i);
            shiftBlocksDown(i);
        }
    }
}
void Tetris::deleteRow(int row) {
    for (int i = 0; i < MAX_COL; i++) {
        map[row * MAX_COL + i][1] = 0;
        map[row * MAX_COL + i][2] = 0;
    }
}
void Tetris::shiftBlocksDown(int emptyRow) {
    for (int i = emptyRow-1; i >= 0; i--) {
        for (int j = 0; j < MAX_COL; j++) {
            map[(i + 1) * MAX_COL + j][1] = map[i * MAX_COL + j][1];
            map[(i + 1) * MAX_COL + j][2] = map[i * MAX_COL + j][2];
        }
        deleteRow(i);
    }
}
void Tetris::switchLED(int ledIndex, int color) {
    if (map[ledIndex][1] == 1) {
        map[ledIndex][1] = 0;
        map[ledIndex][2] = 0;
    }
    else {
        map[ledIndex][1] = 1;
        map[ledIndex][2] = color;
    }
}

//Shape Mutators
void Tetris::rotateShapeRight() {
    shapeOnOff(shape);
    shape->rotateShapeRight();
    if (!checkBound(0))
        shape->undoMove();
    shapeOnOff(shape);

}
void Tetris::rotateShapeLeft() {
    shapeOnOff(shape);
    shape->rotateShapeLeft();
    if (!checkBound(0))
        shape->undoMove();
    shapeOnOff(shape);
}
bool Tetris::moveShapeDown() {
    if (checkBound(MAX_COL))
    {
        shapeOnOff(shape);
        shape->shiftDown();
        shapeOnOff(shape);
        return true;
    }
    else
        return false;
}
void Tetris::moveShapeLeft() {
    if (checkBound(-1)) {
        shapeOnOff(shape);
        shape->shiftLeft();
        shapeOnOff(shape);
    }
}
void Tetris::moveShapeRight() {
    if (checkBound(+1)) {
        shapeOnOff(shape);
        shape->shiftRight();
        shapeOnOff(shape);

    }
}

void Tetris::shapeOnOff(Shape* currentShape) {
    int color = shape->getColor();
    switchLED(shape->getBlockOneIndex(), color);
    switchLED(shape->getBlockTwoIndex(), color);
    switchLED(shape->getBlockThreeIndex(), color);
    switchLED(shape->getBlockFourIndex(), color);
}



//game functions
void Tetris::createShape(){
    srand(time(NULL));
    int i = rand() % 1;
    
    if(i==0){
        shape = new ShapeO(0);
    }
    else if(i==1){
        shape = new ShapeJ(0);
    }
    else if(i==2){
        shape = new ShapeS(0);
    }
    else if(i==3){
        shape = new ShapeZ(0);
    }
    else if(i==4){
        shape = new ShapeT(0);
    }
    else if(i==5){
        shape = new ShapeI(0);
    }
    else {
        shape = new ShapeO(0);
    }
    shapeOnOff(shape);
}
void Tetris::initGame() {
    for (int i = 0; i < MAX_ROW * MAX_COL; i++) {
        map[i][0] = 0;
        map[i][1] = 0;
        map[i][2] = 0;
    }
};
void Tetris::printMap(){
    cout << "     R0 R1 R2 R3 R4 R5 R6 R7 R8 R9" << endl;
    for(int i = 0; i < MAX_ROW; i++) {
        cout << "C";
        cout.width(2);
        cout << i; 
        cout << " ";
        for (int j = 0; j < MAX_COL; j++) {
            cout.width(3);
            cout << map[i * MAX_COL + j][1];
        }
        cout << endl;
    }
};
void Tetris::play() {
    char a = 't';
    initGame();
    while (a != 'f') {
        createShape();
        system("CLS");
        cout << endl << endl;
        printMap();
        //while shapecan move down
        while (checkBound(MAX_COL))
        {
            //cout << "Enter l to rotate left r to rotate right: ";
            //cin >> a;
            //if (a == 'l') { rotateShapeLeft(); }
            //else if (a == 'r') { rotateShapeRight(); }
            cout << "Enter l to move left r to move right: ";
            cin >> a;
            if (a == 'l') { moveShapeLeft(); }
            else if (a == 'r') { moveShapeRight(); }

            moveShapeDown();
            system("CLS");
            cout << endl << endl;
            printMap();
        }
        checkCompletedRows();
        cout << "f to quit";
        cin >> a;
    }

};
bool Tetris::checkBound(int moveValue) {
    int b1 = shape->getBlockOneIndex();
    int b2 = shape->getBlockTwoIndex();
    int b3 = shape->getBlockThreeIndex();
    int b4 = shape->getBlockFourIndex();

    if ((b1 + moveValue) >= (MAX_COL * MAX_ROW) || (b2 + moveValue) >= (MAX_COL * MAX_ROW) || (b3 + moveValue) >= (MAX_COL * MAX_ROW) || (b4 + moveValue) >= (MAX_COL * MAX_ROW))
        return false;
    if (map[b1 + moveValue][1] == 1) {
        if ((b1 + moveValue) != b2 && (b1 + moveValue) != b3 && (b1 + moveValue) != b4) {
            return false;
        }
    }
    if (map[b2 + moveValue][1] == 1) {
        if ((b2 + moveValue) != b1 && (b2 + moveValue) != b3 && (b2 + moveValue) != b4) {
            return false;
        }
    }
    if (map[b3 + moveValue][1] == 1) {
        if ((b3 + moveValue) != b2 && (b3 + moveValue) != b1 && (b3 + moveValue) != b4) {
            return false;
        }
    }
    if (map[b4 + moveValue][1] == 1) {
        if ((b4 + moveValue) != b2 && (b4 + moveValue) != b3 && (b4 + moveValue) != b1) {
            return false;
        }
    }
    return true;
}



int main()
{
    Tetris *game = new Tetris();
    game->play();
    cout << "Hello World!\n";
}
