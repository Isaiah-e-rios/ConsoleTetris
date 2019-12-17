// ConsoleTetris.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <time.h>

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
   
    protected:
        int mapCols;
        int mapRows;


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
        Shape(int blockOne, int blockTwo, int blockThree, int blockFour, int color,int rows,int cols) {
            shapeIndecies[0] = blockOne;
            shapeIndecies[1] = blockTwo;
            shapeIndecies[2] = blockThree;
            shapeIndecies[3] = blockFour;
            this->setPevious();
            shapeColor = color;
            mapRows = rows;
            mapCols = cols;

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
            shapeIndecies[0] = previousIndecies[0];
            shapeIndecies[1] = previousIndecies[1];
            shapeIndecies[2] = previousIndecies[2];
            shapeIndecies[3] = previousIndecies[3];
        }
        void shiftDown() {
            this->setPevious();
            shapeIndecies[0] += mapCols;
            shapeIndecies[1] += mapCols;
            shapeIndecies[2] += mapCols;
            shapeIndecies[3] += mapCols;
        }
        void shiftLeft() {
            if (shapeIndecies[0] / mapCols == (shapeIndecies[0] - 1) / mapCols && shapeIndecies[1] / mapCols == (shapeIndecies[1] - 1) / mapCols &&
                shapeIndecies[2] / mapCols == (shapeIndecies[2] - 1) / mapCols && shapeIndecies[3] / mapCols == (shapeIndecies[3] - 1) / mapCols)
            {
                shapeIndecies[0] -= 1;
                shapeIndecies[1] -= 1;
                shapeIndecies[2] -= 1;
                shapeIndecies[3] -= 1;
            }
        }
        void shiftRight() {
            if (shapeIndecies[0] / mapCols == (shapeIndecies[0] + 1) / mapCols && shapeIndecies[1] / mapCols == (shapeIndecies[1] + 1) / mapCols &&
                shapeIndecies[2] / mapCols == (shapeIndecies[2] + 1) / mapCols && shapeIndecies[3] / mapCols == (shapeIndecies[3] + 1) / mapCols)
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
        int getRows() { return mapRows; }
        int getCols() { return mapCols; }
        //add set rows set cols
        
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
        if ((origin + mapCols + 1) / mapCols == (origin + mapCols) / mapCols) {
            orientation = 1;
            this->setShape(origin - mapCols, origin, origin + mapCols, origin + mapCols + 1);
        }
        else{
            setUp(origin - 1);
        }
        
    }
    void setDown(int origin) {
        if ((origin - mapCols - 1) / mapCols == (origin - mapCols) / mapCols) {
            orientation = 3;
            this->setShape(origin + mapCols, origin, origin - mapCols, origin - mapCols - 1);
        }
        else {
            //setDown(origin + 1);
        }
    }
    void setLeft(int origin) {
        orientation = 2;
        if ((origin + 1) / mapCols == (origin) / mapCols) {
            if ((origin - 1) / mapCols == (origin) / mapCols) {
                this->setShape(origin - 1, origin, origin + 1, origin - mapCols + 1);
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
        if ((origin + 1) / mapCols == (origin) / mapCols) {
            if ((origin - 1) / mapCols == (origin) / mapCols) {
                orientation = 0;
                this->setShape(origin + 1, origin, origin - 1, origin + mapCols - 1);
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
    ShapeL(int rows,int cols,int color):Shape((cols / 2)-1, cols / 2, (cols / 2)+1, cols + (cols / 2) - 1, color,rows,cols){
        orientation = 0;
    }
    void undoMove() {
    }
    void rotateShapeLeft() {
        cout << "rotate Left" << endl;
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
        cout << "Shape rotated" << endl;
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
        if ((origin + mapCols - 1) / mapCols == (origin + mapCols) / mapCols) {
            orientation = 1;
            this->setShape(origin - mapCols, origin, origin + mapCols, origin + mapCols - 1);
        }
        else {
            setUp(origin + 1);
        }
    }
    void setDown(int origin) {
        if ((origin - mapCols + 1) / mapCols == (origin - mapCols) / mapCols) {
            orientation = 3;
            this->setShape(origin + mapCols, origin, origin - mapCols, origin - mapCols + 1);
        }
        else {
            setDown(origin - 1);
        }
    }
    void setLeft(int origin) {
        orientation = 0;
        if ((origin + 1) / mapCols == (origin) / mapCols) {
            if ((origin - 1) / mapCols == (origin) / mapCols) {
                this->setShape(origin - 1, origin, origin + 1, origin + mapCols + 1);
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
        if ((origin + 1) / mapCols == (origin) / mapCols && (origin - 1) / mapCols == (origin) / mapCols) {
            orientation = 2;
            this->setShape(origin + 1, origin, origin - 1, origin - mapCols - 1);
        }
    }
public:
    ShapeJ(int rows,int cols,int color) :Shape((cols / 2) - 1, cols / 2, (cols / 2) + 1, cols + (cols / 2) + 1, color,rows,cols) {
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
    ShapeO(int rows,int cols,int color) :Shape((cols / 2) - 1, cols / 2, cols + (cols / 2) -1, cols + (cols / 2), color,rows,cols) {}
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
        if ((origin + 1) / mapCols == origin / mapCols && (origin - 1 + mapCols) / mapCols == (origin + mapCols) / mapCols) {
            orientation = 0;
            this->setShape(origin + 1, origin, origin + mapCols, origin + mapCols - 1);
        }
    }
    void setUp(int origin) {
        if ((origin + 1) / mapCols == origin / mapCols) {
            orientation = 1;
            this->setShape(origin - mapCols, origin, origin + 1, origin + mapCols + 1);
        }
    }
public:
    ShapeS(int rows,int cols,int color) :Shape((cols / 2) + 1, cols / 2, cols + (cols / 2) - 1, cols + (cols / 2), color,rows,cols) {
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
        if ((origin - 1) / mapCols == origin / mapCols && (origin + 1 + mapCols) / mapCols == (origin + mapCols) / mapCols) {
            orientation = 0;
            this->setShape(origin - 1, origin, origin + mapCols, origin + mapCols + 1);
        }
    }
    void setUp(int origin) {
        if ((origin - 1) / mapCols == origin / mapCols) {
            orientation = 1;
            this->setShape(origin - mapCols, origin, origin - 1, origin + mapCols - 1);
        }
    }
public:
    ShapeZ(int rows,int cols,int color) :Shape((cols / 2) - 1, cols / 2, cols + (cols / 2) + 1, cols + (cols / 2), color,rows,cols) {
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
        if ((origin + 2) / mapCols == origin / mapCols && (origin - 1) / mapCols == origin / mapCols) {
            orientation = 0;
            this->setShape(origin - 1, origin, origin + 1, origin + 2);
        }
    };
    void setUp(int origin) {
        orientation = 1;
        this->setShape(origin - mapCols, origin, origin + mapCols, origin + mapCols * 2);
    }
public:
    ShapeI(int rows,int cols,int color) :Shape((cols / 2) - 2, (cols / 2)-1, (cols / 2), (cols / 2) + 1, color,rows,cols) {
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
        if ((origin - 1) / mapCols == (origin+1) / mapCols) {
            orientation = 2;
            this->setShape(origin - 1, origin, origin + 1, origin + mapCols);
        }
    }
    void setDown(int origin) {
        if ((origin - 1) / mapCols == (origin + 1) / mapCols) {
            orientation = 0;
            this->setShape(origin - 1, origin, origin + 1, origin - mapCols);
        }
    }
    void setLeft(int origin) {
        if ((origin + 1) / mapCols == (origin) / mapCols) {
            orientation = 3;
            this->setShape(origin - mapCols, origin, origin + mapCols, origin + 1);
        }
    }
    void setRight(int origin) {
        if ((origin - 1) / mapCols == (origin) / mapCols) {
            orientation = 1;
            this->setShape(origin + mapCols, origin, origin - mapCols, origin - 1);
        }
    }


public:
    ShapeT(int rows,int cols,int color) :Shape((cols / 2) - 1, cols / 2, (cols / 2) + 1, cols + (cols / 2), color,rows,cols) {
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
class LEDTetris{
    private:
        int **map;
        int mapRow;
        int mapCol;
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
        LEDTetris(int rows,int cols, int *ledIndexArray) {
            mapRow = rows;
            mapCol = cols;
            score = 0;
            shape = NULL;
            map = new int* [rows*cols];
            for(int i=0;i<rows*cols;i++){
                map[i] = new int[3];
                map[i][0] = ledIndexArray[i];
            }
        }
        void play();
        void restart() { initGame(); };

        ~LEDTetris() {
            for (int i = mapRow * mapCol-1; i >=0 ; i--) {
                delete map[i];
            }
            delete map;
        }
};

//Row Completion
void LEDTetris::checkCompletedRows() {
    int filledCount;
    for (int i = 0; i < mapRow; i++) {
        filledCount = 0;
        for (int j = 0; j < mapCol; j++) {
            if (map[i * mapCol + j][1] == 1) {
                filledCount++;
            }
            else {
                filledCount = 0;
                j = mapCol;
            }
        }
        if (filledCount == mapCol) {
            deleteRow(i);
            shiftBlocksDown(i);
        }
    }
}
void LEDTetris::deleteRow(int row) {
    for (int i = 0; i < mapCol; i++) {
        map[row * mapCol + i][1] = 0;
        map[row * mapCol + i][2] = 0;
    }
}
void LEDTetris::shiftBlocksDown(int emptyRow) {
    for (int i = emptyRow-1; i >= 0; i--) {
        for (int j = 0; j < mapCol; j++) {
            map[(i + 1) * mapCol + j][1] = map[i * mapCol + j][1];
            map[(i + 1) * mapCol + j][2] = map[i * mapCol + j][2];
        }
        deleteRow(i);
    }
}
void LEDTetris::switchLED(int ledIndex, int color) {
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
void LEDTetris::rotateShapeRight() {
    shapeOnOff(shape);
    shape->rotateShapeRight();
    if (!checkBound(0))
        shape->undoMove();
    shapeOnOff(shape);

}
void LEDTetris::rotateShapeLeft() {
    shapeOnOff(shape);
    shape->rotateShapeLeft();
    if (!checkBound(0))
        shape->undoMove();
    shapeOnOff(shape);
}
bool LEDTetris::moveShapeDown() {
    if (checkBound(mapCol))
    {
        shapeOnOff(shape);
        shape->shiftDown();
        shapeOnOff(shape);
        return true;
    }
    else
        return false;
}
void LEDTetris::moveShapeLeft() {
    if (checkBound(-1)) {
        shapeOnOff(shape);
        shape->shiftLeft();
        shapeOnOff(shape);
    }
}
void LEDTetris::moveShapeRight() {
    if (checkBound(+1)) {
        shapeOnOff(shape);
        shape->shiftRight();
        shapeOnOff(shape);

    }
}

void LEDTetris::shapeOnOff(Shape* currentShape) {
    int color = shape->getColor();
    switchLED(shape->getBlockOneIndex(), color);
    switchLED(shape->getBlockTwoIndex(), color);
    switchLED(shape->getBlockThreeIndex(), color);
    switchLED(shape->getBlockFourIndex(), color);
}



//game functions
void LEDTetris::createShape(){
    srand(time(NULL));
    int i = rand() % 1;
    
    if(i==0){
        shape = new ShapeL(mapRow,mapCol,0);
    }
    else if(i==1){
        shape = new ShapeJ(mapRow, mapCol, 0);
    }
    else if(i==2){
        shape = new ShapeZ(mapRow, mapCol, 0);
    }
    else if(i==3){
        shape = new ShapeS(mapRow, mapCol, 0);
    }
    else if(i==4){
        shape = new ShapeT(mapRow, mapCol, 0);
    }
    else if(i==5){
        shape = new ShapeI(mapRow, mapCol, 0);
    }
    else {
        shape = new ShapeO(mapRow, mapCol, 0);
    }
    shapeOnOff(shape);
}
void LEDTetris::initGame() {
    for (int i = 0; i < mapRow * mapCol; i++) {
        map[i][1] = 0;
        map[i][2] = 0;
    }
};
void LEDTetris::printMap(){
    cout << "     R0 R1 R2 R3 R4 R5 R6 R7 R8 R9" << endl;
    for(int i = 0; i < mapRow; i++) {
        cout << "C";
        cout.width(2);
        cout << i; 
        cout << " ";
        for (int j = 0; j < mapCol; j++) {
            cout.width(3);
            cout << map[i * mapCol + j][1];
        }
        cout << endl;
    }
};
void LEDTetris::play() {
    char a = 't';
    initGame();
    while (a != 'f') {
        createShape();
        system("CLS");
        cout << endl << endl;
        printMap();
        //while shapecan move down
        while (checkBound(mapCol))
        {
            cout << "Enter l to rotate left r to rotate right: ";
            cin >> a;
            if (a == 'l') { rotateShapeLeft(); }
            else if (a == 'r') { rotateShapeRight(); }
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
bool LEDTetris::checkBound(int moveValue) {
    int b1 = shape->getBlockOneIndex();
    int b2 = shape->getBlockTwoIndex();
    int b3 = shape->getBlockThreeIndex();
    int b4 = shape->getBlockFourIndex();
    if ((b1 + moveValue) >= (mapCol * mapRow) || (b2 + moveValue) >= (mapCol * mapRow) || (b3 + moveValue) >= (mapCol * mapRow) || (b4 + moveValue) >= (mapCol * mapRow))
        return false;
    if ((b1 + moveValue) < 0 || (b2 + moveValue) < 0 || (b3 + moveValue) < 0 || (b4 + moveValue) < 0)
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
    int rows = 10;
    int cols = 10;
    int* ledIndexes = new int[rows * cols];

    for (int i = 0; i < rows*cols; i++) {
        ledIndexes[i] = i;
    }

    LEDTetris *game = new LEDTetris(rows,cols,ledIndexes);
    game->play();
    cout << "Hello World!\n";
}
