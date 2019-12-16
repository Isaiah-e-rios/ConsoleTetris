// ConsoleTetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cstdlib>

#define MAX_ROW 24
#define MAX_COL 10



using namespace std;


class Shape {
    private:
        int previousIndecies[4];
        int shapeIndecies[4];
        int shapeColor;

    public:
        Shape() {
            shapeIndecies[0] = 0;
            shapeIndecies[1] = 0;
            shapeIndecies[2] = 0;
            shapeIndecies[3] = 0;
            this->setPevious();
            shapeColor = 0;
        };
        Shape(int blockOne, int blockTwo, int blockThree, int blockFour) {
            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
            this->setPevious();
            shapeColor = 0;
        };
        Shape(int blockOne, int blockTwo, int blockThree, int blockFour, int color) {
            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
            this->setPevious();
            shapeColor = color;
        };

        void setShape(int blockOne, int blockTwo, int blockThree, int blockFour) {
            this->setPevious();

            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
        };
        void setPevious() {
            previousIndecies[0] = shapeIndecies[0];
            previousIndecies[1] = shapeIndecies[1];
            previousIndecies[2] = shapeIndecies[2];
            previousIndecies[3] = shapeIndecies[3];
        };

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
            shapeIndecies[0] += 10;
            shapeIndecies[1] += 10;
            shapeIndecies[2] += 10;
            shapeIndecies[3] += 10;
        };
        void shiftLeft() {
            if (shapeIndecies[0] / MAX_COL == (shapeIndecies[0] - 1) / MAX_COL && shapeIndecies[1] / MAX_COL == (shapeIndecies[1] - 1) / MAX_COL &&
                shapeIndecies[2] / MAX_COL == (shapeIndecies[2] - 1) / MAX_COL && shapeIndecies[3] / MAX_COL == (shapeIndecies[3] - 1) / MAX_COL)
            {
                shapeIndecies[0] -= 1;
                shapeIndecies[1] -= 1;
                shapeIndecies[2] -= 1;
                shapeIndecies[3] -= 1;
            }
        };
        void shiftRight() {
            if (shapeIndecies[0] / MAX_COL == (shapeIndecies[0] + 1) / MAX_COL && shapeIndecies[1] / MAX_COL == (shapeIndecies[1] + 1) / MAX_COL &&
                shapeIndecies[2] / MAX_COL == (shapeIndecies[2] + 1) / MAX_COL && shapeIndecies[3] / MAX_COL == (shapeIndecies[3] + 1) / MAX_COL)
            {
                shapeIndecies[0] += 1;
                shapeIndecies[1] += 1;
                shapeIndecies[2] += 1;
                shapeIndecies[3] += 1;
            }
        };


        int getBlockOneIndex() { return shapeIndecies[0]; };
        int getBlockTwoIndex() { return shapeIndecies[1]; };
        int getBlockThreeIndex() { return shapeIndecies[2]; };
        int getBlockFourIndex() { return shapeIndecies[3]; };

        ~Shape() {};
};

//L shape with Starting orientation
//0(Right) 1(up) 2(Left) 3(Down)
// * * *    *          *    * *
// *     -> *   -> * * * ->   *
//          * *               *
class ShapeL : public Shape {
private: 
    int orientation;
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



    void setUp(int origin) {
        if ((origin + MAX_COL + 1) / MAX_COL == (origin + MAX_COL) / MAX_COL) {
            orientation = 1;
            this->setShape(origin - MAX_COL, origin, origin + MAX_COL, origin + MAX_COL + 1);
        }
    }
    void setDown(int origin) {
        if ((origin - MAX_COL - 1) / MAX_COL == (origin - MAX_COL) / MAX_COL) {
            orientation = 3;
            this->setShape(origin + MAX_COL, origin, origin - MAX_COL, origin - MAX_COL - 1);
        }
    }
    void setLeft(int origin) {
        orientation = 2;
        if ((origin + 1) / MAX_COL == (origin) / MAX_COL && (origin - 1) / MAX_COL == (origin) / MAX_COL) {
            this->setShape(origin - 1, origin, origin + 1, origin - MAX_COL + 1);
        }
    }
    void setRight(int origin) {
        if ((origin + 1) / MAX_COL == (origin) / MAX_COL && (origin - 1) / MAX_COL == (origin) / MAX_COL) {
            orientation = 0;
            this->setShape(origin + 1, origin, origin - 1, origin + MAX_COL - 1);
        }
    }
};

//J shape with orientations
//   0(left)  1(up)   2(right)   3(down)
// * * *      *        *          * *
//     * ->   *   ->   * * * ->   *
//          * *                   *
class ShapeJ : public Shape {
private:
    int orientation;
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



    void setUp(int origin) {
        if ((origin + MAX_COL - 1) / MAX_COL == (origin + MAX_COL) / MAX_COL) {
            orientation = 1;
            this->setShape(origin - MAX_COL, origin, origin + MAX_COL, origin + MAX_COL - 1);
        }
    }
    void setDown(int origin) {
        if ((origin - MAX_COL + 1) / MAX_COL == (origin - MAX_COL) / MAX_COL) {
            orientation = 3;
            this->setShape(origin + MAX_COL, origin, origin - MAX_COL, origin - MAX_COL + 1);
        }
    }
    void setLeft(int origin) {
        orientation = 0;
        if ((origin + 1) / MAX_COL == (origin) / MAX_COL && (origin - 1) / MAX_COL == (origin) / MAX_COL) {
            this->setShape(origin - 1, origin, origin + 1, origin + MAX_COL + 1);
        }

    }
    void setRight(int origin) {
        if ((origin + 1) / MAX_COL == (origin) / MAX_COL && (origin - 1) / MAX_COL == (origin) / MAX_COL) {
            orientation = 2;
            this->setShape(origin + 1, origin, origin - 1, origin - MAX_COL - 1);
        }
    }
};

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

    void setDown(int origin) {
        if ((origin + 1) / MAX_COL == origin / MAX_COL && (origin - 1 + MAX_COL) / MAX_COL == (origin + MAX_COL) / MAX_COL) {
            orientation = 0;
            this->setShape(origin + 1, origin, origin + MAX_COL, origin + MAX_COL - 1);
        }
    }
    void setUp(int origin) {
        if ((origin + 1) / MAX_COL == origin / MAX_COL ) {
            orientation = 1;
            this->setShape(origin - MAX_COL, origin, origin + 1, origin + MAX_COL + 1);
        }
    }
};

//Z Shape
//0(down) 1(up)
//* *   ->   *
//  * * -> * *
//         *
class ShapeZ : public Shape {
private:
    int orientation;
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
    void rotateShapeRight() {};
    void setDown(int origin) {
        if ((origin + 2) / MAX_COL == origin/MAX_COL && (origin-1) / MAX_COL == origin / MAX_COL){
            orientation = 0;
            this->setShape(origin - 1, origin, origin + 1, origin + 2);
        }
    };
    void setUp(int origin){
        orientation = 1;
        this->setShape(origin-MAX_COL,origin, origin + MAX_COL, origin + MAX_COL*2);
    }
};
class ShapeT : public Shape {
public:
    ShapeT(int color) :Shape((MAX_COL / 2) - 1, MAX_COL / 2, (MAX_COL / 2) + 1, MAX_COL + (MAX_COL / 2), color) {}
    void rotateShapeLeft() {};
    void rotateShapeRight() {};
};

class Tetris{
    private:
        int map[MAX_ROW * MAX_COL][2];
        int score;
        Shape *shape;
        
        bool checkBound(int moveValue);
        void initGame(); 
        void printMap();



        void createShape();
        bool checkCompletedRow(int row) {};
        void deleteRow(int row) {};
        void shiftDown(int row) {};
        void switchLED(int ledNumber);

        //Controll Calls
        void moveShapeLeft();
        void moveShapeRight();
        bool moveShapeDown();

        void rotateShapeLeft();
        void rotateShapeRight();
    public:
        void play() {
            char a='t';
            initGame();
            switchLED(104);
            printMap();
            while (a != 'f') {
                createShape();
                while (checkBound(MAX_COL))
                {
                    cin >> a;
                    system("CLS");

                    rotateShapeLeft();
                    moveShapeRight();
                    moveShapeDown();
                    cout << endl << endl;
                    printMap();
                }
                cin >> a;
            }

        };
        void restart() {};
};

void Tetris::rotateShapeRight() {
    switchLED(shape->getBlockOneIndex());
    switchLED(shape->getBlockTwoIndex());
    switchLED(shape->getBlockThreeIndex());
    switchLED(shape->getBlockFourIndex());
    shape->rotateShapeRight();
    if (!checkBound(0))
        shape->setPevious();
    switchLED(shape->getBlockOneIndex());
    switchLED(shape->getBlockTwoIndex());
    switchLED(shape->getBlockThreeIndex());
    switchLED(shape->getBlockFourIndex());

}
void Tetris::rotateShapeLeft() {
    switchLED(shape->getBlockOneIndex());
    switchLED(shape->getBlockTwoIndex());
    switchLED(shape->getBlockThreeIndex());
    switchLED(shape->getBlockFourIndex());
    shape->rotateShapeLeft();
    if (!checkBound(0))
        shape->setPevious();
    switchLED(shape->getBlockOneIndex());
    switchLED(shape->getBlockTwoIndex());
    switchLED(shape->getBlockThreeIndex());
    switchLED(shape->getBlockFourIndex());

}

bool Tetris::checkBound(int moveValue) {
    int b1 = shape->getBlockOneIndex();
    int b2 = shape->getBlockTwoIndex();
    int b3 = shape->getBlockThreeIndex();
    int b4 = shape->getBlockFourIndex();

    if ((b1 + moveValue) >= (MAX_COL * MAX_ROW) || (b2 + moveValue) >= (MAX_COL * MAX_ROW) || (b3 + moveValue) >= (MAX_COL * MAX_ROW) || (b4 + moveValue) >= (MAX_COL * MAX_ROW))
        return false;
    if(map[b1+moveValue][1] == 1){
        if ((b1 + moveValue) != b2 && (b1 + moveValue) != b3 && (b1 + moveValue) != b4){
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


bool Tetris::moveShapeDown() {
    if (checkBound(MAX_COL))
    {
        switchLED(shape->getBlockOneIndex());
        switchLED(shape->getBlockTwoIndex());
        switchLED(shape->getBlockThreeIndex());
        switchLED(shape->getBlockFourIndex());
        shape->shiftDown();
        switchLED(shape->getBlockOneIndex());
        switchLED(shape->getBlockTwoIndex());
        switchLED(shape->getBlockThreeIndex());
        switchLED(shape->getBlockFourIndex());
        return true;
    }
    else
        return false;
}
void Tetris::moveShapeLeft() {
    if (checkBound(-1)) {
        switchLED(shape->getBlockOneIndex());
        switchLED(shape->getBlockTwoIndex());
        switchLED(shape->getBlockThreeIndex());
        switchLED(shape->getBlockFourIndex());
        shape->shiftLeft();
        switchLED(shape->getBlockOneIndex());
        switchLED(shape->getBlockTwoIndex());
        switchLED(shape->getBlockThreeIndex());
        switchLED(shape->getBlockFourIndex());
    }
}

void Tetris::moveShapeRight() {
    if (checkBound(+1)) {
        switchLED(shape->getBlockOneIndex());
        switchLED(shape->getBlockTwoIndex());
        switchLED(shape->getBlockThreeIndex());
        switchLED(shape->getBlockFourIndex());
        shape->shiftRight();
        switchLED(shape->getBlockOneIndex());
        switchLED(shape->getBlockTwoIndex());
        switchLED(shape->getBlockThreeIndex());
        switchLED(shape->getBlockFourIndex());
    }
}
void Tetris::switchLED(int ledIndex) {
    if (map[ledIndex][1] == 1) {
        map[ledIndex][1] = 0;
    }
    else
        map[ledIndex][1] = 1;
}


void Tetris::createShape(){
    int i = rand()%1;
    
    if(i==0){
        shape = new ShapeI(0);
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
    switchLED(shape->getBlockOneIndex());
    switchLED(shape->getBlockTwoIndex());
    switchLED(shape->getBlockThreeIndex());
    switchLED(shape->getBlockFourIndex());
}

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
            cout << map[i * MAX_COL + j][1];
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
