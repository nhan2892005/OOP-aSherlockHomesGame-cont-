/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Submit code for Assignment 1
* Programming Fundamentals Spring 2024
* Author: Nguyen Phuc Nhan
* ID: 2312438
* Date: 10.03.2024
*/

#ifndef _H_STUDY_IN_PINK_2_H_
#define _H_STUDY_IN_PINK_2_H_

#include "main.h"

////////////////////////////////////////////////////////////////////////
// STUDENT'S ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////

// Forward declaration
//Check init Map
 class MapElement;
 class Map;
 class Position;
 
 //Check init Objects
 class MovingObject;
 class Sherlock;
 class Watson;
 class Criminal;

 //Check init array
 class ArrayMovingObject;

 //Chech config
 class Configuration;

 //Recheck Object
 class Character;

 //Check init Robot
 class Robot;
 class RobotC;
 class RobotS;
 class RobotW;
 class RobotSW;

 //Check init Item
 class BaseItem;
 class MagicBook;
 class EnergyDrink;
 class FirstAid;
 class ExcemptionCard;
 class PassingCard;

 //Check init Bag
 class BaseBag;
 class SherlockBag;
 class WatsonBag;
 class StudyPinkProgram;

//TestStudyInPink declare in main.cpp
//We call it to avoid error calling 
 class TestStudyInPink;

//Set up max_hp and max_exp to easy call
const int max_hp = 500;
const int max_exp = 900;

//if value (hp | exp) out of range (>max) 
//then set it = max
void checkValue(int &value, int max_value);

//In this assignment, distance of two object is Manhattan Distance
//|x1-x2|+|y1+y2|
int ManhattanDistance(const Position &pos1, const Position &pos2);
/*
    Set up global function to easy call and manager code
*/


enum ItemType   {
                MAGIC_BOOK, 
                ENERGY_DRINK, 
                FIRST_AID, 
                EXCEMPTION_CARD, 
                PASSING_CARD 
                };
enum ElementType{PATH, WALL, FAKE_WALL};
enum RobotType  {C=0, S, W, SW};

class MapElement
{
    public:
        friend class TestStudyInPink;
        MapElement() = default;
        MapElement(ElementType in_type);
        virtual ~MapElement();
        virtual ElementType getType() const;
    protected:
        ElementType type;
};

// All objects can move in a PATH element 
class Path : public MapElement
{
    public:
        friend class TestStudyInPink;
        Path();
        ~Path();
};
// All objects cannot move in a WALL element
class Wall : public MapElement
{
    public:
        friend class TestStudyInPink;
        Wall();
        ~Wall();
};
// Criminal create fake walls, so
// Criminal can move in a FAKE_WALL element
// Sherlock always has to have enough experience to move in a FAKE_WALL element
// Waston need exp > req_exp to move in a FAKE_WALL element
// All other objects cannot move in a FAKE_WALL element
class FakeWall : public MapElement
{
    public:
        friend class TestStudyInPink;
        FakeWall(int in_req_exp);
        ~FakeWall();
        int getReqExp() const;
    private:
        int req_exp;
};
                            /*
                                HCMUT 13:58 10/03/2024
                                Class MapElement
                                Done
                            */
class Map
{
    public:
        friend class TestStudyInPink;
        Map(int num_rows , 
            int num_cols , 
            int num_walls , 
            Position * array_walls , 
            int num_fake_walls , 
            Position * array_fake_walls);
        ~Map();
        bool isValid(const Position & pos , MovingObject * mv_obj) const;
    private:
        int num_rows, num_cols;
        MapElement*** map;
};
                            /*
                                HCMUT 14:19 10/03/2024
                                Class Map
                                Done
                            */

class Position
{
    public:
        friend class TestStudyInPink;
        Position(int r=0, int c=0);
        Position(const string & str_pos);
        int getRow() const;
        int getCol() const;
        void setRow(int r);
        void setCol(int c);
        string str() const;
        bool isEqual(int in_r, int in_c) const;
        static const Position npos;
    private:
        int r, c;
};
                            /*
                                HCMUT 14:36 10/03/2024
                                Class Position
                                Done
                            */
class MovingObject
{
    public:
        friend class TestStudyInPink;
        MovingObject() = default;
        MovingObject(   int index , 
                        const Position pos , 
                        Map * map , 
                        const string & name="");
        virtual ~MovingObject();
        virtual Position getNextPosition() = 0;
        virtual Position getCurrentPosition() const;
        virtual void move() = 0;
        virtual string str() const = 0;
        // set up get Name
        string getName() const;
        // set up Step for Object
        void getStep(int istep);
    protected:
        int index;
        Position pos;
        Map * map;
        string name;      
        int step = 1;
};

class Character : public MovingObject
{
    public:
        Character(  int index,
                    const Position & init_pos,
                    Map * map,
                    bool pass,
                    const string & name="");
        
    private:
        bool pass;
};
                            /*
                                HCMUT 14:34 10/03/2024
                                Class Position
                                Done
                            */
class Sherlock : public Character
{
    public:
        friend class TestStudyInPink;
        Sherlock(int index , const string & moving_rule , const Position & init_pos , Map * map , int init_hp , int init_exp);
        ~Sherlock();
        Position getNextPosition();
        void move();
        string str() const;
        //////////////////////////
        char getNextMoving();
        int getEXP();
        int getHP();
        //////////////////////////
    private:
        string moving_rule;
        int hp, exp;
};
                            /*
                                HCMUT 14:48 10/03/2024
                                Class Sherlock
                                Done
                            */
class Watson : public Character
{
    public:
        friend class TestStudyInPink;
        Watson( int index , 
                const string & moving_rule , 
                const Position & init_pos , 
                Map * map , 
                int init_hp , 
                int init_exp);
        Position getNextPosition();
        void move();
        string str() const;
        ~Watson();
        //////////////////////
        char getNextMoving();
        int getEXP();
        int getHP();
        /////////////////////
    private:
        string moving_rule;
        int hp, exp;
};
                            /*
                                HCMUT 14:48 10/03/2024
                                Class Watson
                                Done
                            */
class Criminal : public Character
{
    public:
        friend class TestStudyInPink;
        Criminal(int index , const Position & init_pos , Map * map , Sherlock * sherlock , Watson * watson);
        Position getNextPosition();
        void move();
        string str() const;
        ~Criminal();
    private:
        Sherlock * sherlock;
        Watson * watson;
};
                            /*
                                HCMUT 14:48 10/03/2024
                                Class Criminal
                                Done
                            */

class Configuration
{
    public:
        friend class TestStudyInPink;
        Configuration(const string & filepath);
        ~Configuration();
        string str() const;
        /////////////////
        void init_info_program( Sherlock * &sherlock,
                                Watson * &watson,
                                Criminal * &criminal,
                                Map * &map,
                                ArrayMovingObject * &arr_mv_oj);
        int numElement(string temp);
        int getNumStep();
        void init_pos(Position &mv_obj_pos, string line);
        void init_array(Position *&arr, int &numArr, string line);
        ////////////////
    private:
        int map_num_rows, map_num_cols;
        int max_num_moving_objects;
        int num_walls = 0;
        Position* arr_walls;
        int num_fake_walls = 0;
        Position* arr_fake_walls;
        string sherlock_moving_rule;
        Position sherlock_init_pos;
        int sherlock_init_hp;
        int sherlock_init_exp;
        string watson_moving_rule;
        Position watson_init_pos;
        int watson_init_hp;
        int watson_init_exp;
        Position criminal_init_pos;
        int num_steps; 
};
class ArrayMovingObject
{
    public:
        friend class TestStudyInPink;
        ArrayMovingObject(int capacity);
        ~ArrayMovingObject();
        bool isFull() const;
        bool add(MovingObject * mv_obj);
        string str() const;
        ////////////////
        int maxSize();
        int getCount();
        MovingObject* get(int i);
        ////////////////
    private:
        MovingObject** arr_mv_objs;
        int count;
        int capacity;
};

class StudyPinkProgram {
private:
    Configuration * config;
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    Map * map;
    ArrayMovingObject * arr_mv_objs;

public:
    StudyPinkProgram(const string & config_file_path);
    bool isStop() const;
    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual( criminal->getCurrentPosition().getRow(),
                                                    criminal->getCurrentPosition().getRow())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(  criminal->getCurrentPosition().getRow(),
                                                        criminal->getCurrentPosition().getRow())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose);

    ~StudyPinkProgram();

    friend class TestStudyInPink;
};

class Robot : public MovingObject
{
    public:
        Robot(  int index,
                const Position & init_pos,
                Map * map,
                RobotType robot_type);
        virtual Position getNextPosition() = 0;
        void move();
        virtual string str() const;
    protected:
        RobotType robot_type;
        BaseItem * item;
};

class RobotC : public Robot
{
    public:
        RobotC( int index, 
                const Position & init_pos,
                Map * map,
                RobotType robot_type,
                Criminal * criminal
                );
        Position getNextPosition();
        int getDistance(Sherlock * sherlock);
        int getDistance(Watson * watson);
        string str();
    private:
        Criminal * criminal;
};

class RobotS : public Robot
{
    public:
        RobotS( int index, 
                const Position & init_pos,
                Map * map,
                RobotType robot_type,
                Criminal * criminal,
                Sherlock * sherlock
                );
        Position getNextPosition();
        int getDistance();
        string str();
    private:
        Criminal * criminal;
        Sherlock * sherlock;
};

class RobotW : public Robot
{
    public:
        RobotW( int index, 
                const Position & init_pos,
                Map * map,
                RobotType robot_type,
                Criminal * criminal,
                Watson * watson
                );
        Position getNextPosition();
        int getDistance();
        string str();
    private:
        Criminal * criminal;
        Watson * watson;

};

class RobotSW : public Robot
{
    public:
        RobotSW( int index, 
                const Position & init_pos,
                Map * map,
                RobotType robot_type,
                Criminal * criminal,
                Sherlock * sherlock,
                Watson * watson
                );
        Position getNextPosition();
        int getDistance();
        string str();
    private:
        Criminal * criminal;
        Sherlock * sherlock;
        Watson * watson;
};
/*
class ArrayMovingObject {
private:
    // TODO

public:
    ArrayMovingObject(int capacity);

    ~ArrayMovingObject() ;
    bool isFull() const;
    bool add(MovingObject * mv_obj);
    MovingObject * get(int index) const;
    int size() const; // return current number of elements in the array
    string str() const;
};

class Configuration {
    friend class StudyPinkProgram;

private:
    // TODO

public:
    Configuration(const string & filepath);
    ~Configuration();
    string str() const;
};

// Robot, BaseItem, BaseBag,...

class StudyPinkProgram {
private:
    // Sample attributes
    Configuration * config;
    
    Sherlock * sherlock;
    Watson * watson;
    Criminal * criminal;
    
    Map * map;
    ArrayMovingObject * arr_mv_objs;


public:
    StudyPinkProgram(const string & config_file_path);

    bool isStop() const;

    void printResult() const {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())) {
            cout << "Watson caught the criminal" << endl;
        }
        else {
            cout << "The criminal escaped" << endl;
        }
    }

    void printStep(int si) const {
        cout << "Step: " << setw(4) << setfill('0') << si
            << "--"
            << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
    }

    void run(bool verbose) {
        // Note: This is a sample code. You can change the implementation as you like.
        // TODO
        for (int istep = 0; istep < config->num_steps; ++istep) {
            for (int i = 0; i < arr_mv_objs->size(); ++i) {
                arr_mv_objs->get(i)->move();
                if (isStop()) {
                    printStep(istep);
                    break;
                }
                if (verbose) {
                    printStep(istep);
                }
            }
        }
        printResult();
    }

    ~StudyPinkProgram();
};
*/
////////////////////////////////////////////////
/// END OF STUDENT'S ANSWER
////////////////////////////////////////////////
#endif /* _H_STUDY_IN_PINK_2_H_ */
