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
// * // * // * // * // * // * // * /// 
// *  MY ANSWER BEGINS HERE         //
// * // * // * // * // * // * // * ///
#define FOR(i, a, b) for (int(i) = (a); i < (b); ++i)
#define UP(Position, i) Position.setRow(Position.getRow() - (i));
#define DOWN(Position, i) Position.setRow(Position.getRow() + (i));
#define LEFT(Position, i) Position.setCol(Position.getCol() - (i));
#define RIGHT(Position, i) Position.setCol(Position.getCol() + (i));
template <typename PHUCNHAN>PHUCNHAN Max(PHUCNHAN a, PHUCNHAN b) { return (a > b) ? a : b; }
template <typename PHUCNHAN>PHUCNHAN Min(PHUCNHAN a, PHUCNHAN b) { return (a < b) ? a : b; }
template <typename PHUCNHAN>void Swap(PHUCNHAN &a, PHUCNHAN &b){PHUCNHAN temp = a;a = b;b = temp;}
template <typename PHUCNHAN>int BinarySearch(PHUCNHAN arr[], int l, int r, PHUCNHAN x){
    if (r >= l)
    {
        int mid = l + (r - l) / 2;
        if (arr[mid] == x)
            return mid;
        if (arr[mid] > x)
            return BinarySearch(arr, l, mid - 1, x);
        return BinarySearch(arr, mid + 1, r, x);
    }
    return -1;
}
template <typename PHUCNHAN>int Partition(PHUCNHAN arr[], int low, int high){
    PHUCNHAN pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++)
    {
        if (arr[j] < pivot)
        {
            i++;
            Swap(arr[i], arr[j]);
        }
    }
    Swap(arr[i + 1], arr[high]);
    return (i + 1);
}
template <typename PHUCNHAN>void QuickSort(PHUCNHAN arr[], int low, int high)
{
    if (low < high)
    {
        int pi = Partition(arr, low, high);
        QuickSort(arr, low, pi - 1);
        QuickSort(arr, pi + 1, high);
    }
}

// * Forward declaration
class MapElement;
class Map;
class Position;

class MovingObject;
class Sherlock;
class Watson;
class Criminal;

class ArrayMovingObject;

class Configuration;

class Character;

class Robot;
class RobotC;
class RobotS;
class RobotW;
class RobotSW;

class BaseItem;
class MagicBook;
class EnergyDrink;
class FirstAid;
class ExcemptionCard;
class PassingCard;

class BaseBag;
class SherlockBag;
class WatsonBag;
class StudyPinkProgram;

// * We call it to avoid error calling
class TestStudyInPink;

// * Set up max_hp and max_exp to easy call
const int max_hp = 500;
const int max_exp = 900;

// * if value (hp | exp) out of range (>max)
// * then set it = max
void checkValue(int &, int);

// * In this assignment, distance of two object is Manhattan Distance
// * |x1-x2|+|y1+y2|
int ManhattanDistance(const Position &, const Position &);
/*
 * Set up global function to easy call and manager code
 */

enum ItemType
{
    MAGIC_BOOK,
    ENERGY_DRINK,
    FIRST_AID,
    EXCEMPTION_CARD,
    PASSING_CARD
};
enum ElementType
{
    PATH,
    WALL,
    FAKE_WALL
};
enum RobotType
{
    C = 0,
    S,
    W,
    SW
};

class MapElement
{
public:
    friend class TestStudyInPink;
    MapElement() = default;
    MapElement(ElementType);
    virtual ~MapElement();
    virtual ElementType getType() const;
protected:
    ElementType type;
};

// *  All objects can move in a PATH element
class Path : public MapElement
{
public:
    friend class TestStudyInPink;
    Path();
    ~Path();
};
// *  All objects cannot move in a WALL element
class Wall : public MapElement
{
public:
    friend class TestStudyInPink;
    Wall();
    ~Wall();
};
// *  Criminal create fake walls, so
// *  Criminal can move in a FAKE_WALL element
// *  Sherlock always has to have enough experience to move in a FAKE_WALL element
// *  Waston need exp > req_exp to move in a FAKE_WALL element
// *  All other objects cannot move in a FAKE_WALL element
class FakeWall : public MapElement
{
public:
    friend class TestStudyInPink;
    FakeWall(int);
    ~FakeWall();
    // * FakeWall has req_exp for Watson to move
    int getReqExp() const;

private:
    int req_exp;
};

class Map
{
public:
    friend class TestStudyInPink;
    Map(int, int, int, Position *, int, Position *);
    ~Map();
    // *  Check if the position where the object wants to move is valid
    bool isValid(const Position &, MovingObject *) const;

private:
    int num_rows, num_cols;
    MapElement ***map;
};

class Position
{
public:
    friend class TestStudyInPink;
    Position(int r = 0, int c = 0);
    Position(const string &);
    int getRow() const;
    int getCol() const;
    void setRow(int);
    void setCol(int);
    string str() const;
    bool isEqual(int, int) const; // *  Check if two positions are equal
    bool isEqual(Position pos);
    static const Position npos;

private:
    int r, c;
};

class MovingObject
{
public:
    friend class TestStudyInPink;
    MovingObject() = default;
    MovingObject(int, const Position, Map *, const string &name = "");
    virtual ~MovingObject();
    virtual Position getNextPosition() = 0;
    virtual Position getCurrentPosition() const;
    virtual void move() = 0;
    virtual string str() const = 0;
    string getName() const;
    int getStep() const;

protected:
    int index;
    Position pos;
    Map *map;
    string name;
    int step = 0;
};

class Character : public MovingObject
{
public:
    Character(int, const Position &, Map *, bool, const string &name = "");
    virtual ~Character();
    virtual int getEXP() = 0;
    virtual int getHP() = 0;
    virtual void changeEXP(double) = 0;
    virtual void changeHP(double) = 0;
    virtual void meetRobot(MovingObject *) = 0;
    void catchCriminal();
private:
    bool pass;
};

class Sherlock : public Character
{
public:
    friend class TestStudyInPink;
    Sherlock(int, const string &, const Position &, Map *, int, int);
    ~Sherlock();
    Position getNextPosition();
    void move();
    string str() const;
    void meetRobot(MovingObject *);
    int getEXP();
    int getHP();
    void changeEXP(double);
    void changeHP(double);
    SherlockBag *sherlock_bag;
private:
    string moving_rule;
    int hp, exp;
};

class Watson : public Character
{
public:
    friend class TestStudyInPink;
    Watson(int, const string &, const Position &, Map *, int, int);
    Position getNextPosition();
    void move();
    string str() const;
    ~Watson();
    void meetRobot(MovingObject *);
    int getEXP();
    int getHP();
    void changeEXP(double);
    void changeHP(double);
    WatsonBag *watson_bag;

private:
    string moving_rule;
    int hp, exp;
};

class Criminal : public Character
{
public:
    friend class TestStudyInPink;
    Criminal(int, const Position &, Map *, Sherlock *, Watson *);
    Position getNextPosition();
    void move();
    string str() const;
    ~Criminal();
    Position OldStep;
    int getEXP() { return 0; }
    int getHP() { return 0; }
    void changeEXP(double) {}
    void changeHP(double) {}
    void meetRobot(MovingObject *) {}

private:
    Sherlock *sherlock;
    Watson *watson;
};

class Configuration
{
public:
    friend class TestStudyInPink;
    Configuration(const string &);
    ~Configuration();
    string str() const;
    // * initial all object for program
    void init_info_program(Sherlock *&, Watson *&, Criminal *&, Map *&, ArrayMovingObject *&);
    int numElement(string);
    int getNumStep();
    void init_pos(Position &, string);
    void init_array(Position *&, int &, string);

private:
    int map_num_rows, map_num_cols;
    int max_num_moving_objects;
    int num_walls = 0;
    Position *arr_walls;
    int num_fake_walls = 0;
    Position *arr_fake_walls;
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
    ArrayMovingObject(int);
    ~ArrayMovingObject();
    bool isFull() const;
    bool add(MovingObject *);
    string str() const;
    int maxSize();
    int getCount();
    MovingObject *get(int);
    // void del();
private:
    MovingObject **arr_mv_objs;
    int count;
    int capacity;
};
class Robot : public MovingObject
{
public:
    friend class TestStudyInPink;
    Robot(int, const Position &, Map *, RobotType);
    virtual ~Robot() {}
    virtual Position getNextPosition() = 0;
    void move();
    virtual string str() const;
    RobotType getType();
    BaseItem *item;

protected:
    RobotType robot_type;
};
class BaseItem
{
public:
    friend class TestStudyInPink;
    BaseItem(ItemType);
    virtual ~BaseItem();
    virtual bool canUse(Character *, Robot *) const = 0;
    virtual void use(Character *const &, Robot *) const = 0;
    ItemType getType();
    string str() const;

protected:
    ItemType type;
};

class BaseBag
{
public:
    friend class TestStudyInPink;
    BaseBag();
    virtual ~BaseBag();
    virtual bool insert(BaseItem *); // *  return true if insert successfully
    virtual BaseItem *get();         // *  return the item as described above , if not found , return NULL
    virtual BaseItem *get(ItemType); // *  return the item as described above , if not found , return NULL
    virtual string str() const;
    bool ItemExist(ItemType);
    bool isFull();
    int getCount();
protected:
    BaseItem *item;
    BaseBag *next;
    BaseBag *head;
    BaseBag *tail;
    int capacity = 15;
    Character *obj;
    int count = 0; // * number of current item in bag
};
class RobotC : public Robot
{
public:
    friend class TestStudyInPink;
    RobotC(int, const Position &, Map *, Criminal *);
    Position getNextPosition();
    int getDistance(Sherlock *);
    int getDistance(Watson *);
    string str();
private:
    Criminal *criminal;
    const string name = "C";
};

class RobotS : public Robot
{
public:
    friend class TestStudyInPink;
    RobotS(int, const Position &, Map *, Criminal *, Sherlock *);
    Position getNextPosition();
    int getDistance();
    string str();

private:
    Criminal *criminal;
    Sherlock *sherlock;
    const string name = "S";
};

class RobotW : public Robot
{
public:
    friend class TestStudyInPink;
    RobotW(int, const Position &, Map *, Criminal *, Watson *);
    Position getNextPosition();
    int getDistance();
    string str();

private:
    Criminal *criminal;
    Watson *watson;
    const string name = "W";
};

class RobotSW : public Robot
{
public:
    friend class TestStudyInPink;
    RobotSW(int, const Position &, Map *, Criminal *, Sherlock *, Watson *);
    Position getNextPosition();
    int getDistance();
    string str();

private:
    Criminal *criminal;
    Sherlock *sherlock;
    Watson *watson;
    const string name = "SW";
};

class MagicBook : public BaseItem
{
public:
    friend class TestStudyInPink;
    MagicBook();
    bool canUse(Character *, Robot *) const;
    void use(Character *const &, Robot *) const;
    ~MagicBook() {}
};
class EnergyDrink : public BaseItem
{
public:
    friend class TestStudyInPink;
    EnergyDrink();
    bool canUse(Character *, Robot *) const;
    void use(Character *const &, Robot *) const;
    ~EnergyDrink() {}
};

class FirstAid : public BaseItem
{
public:
    friend class TestStudyInPink;
    FirstAid();
    bool canUse(Character *, Robot *) const;
    void use(Character *const &, Robot *) const;
    ~FirstAid() {}
};

class ExcemptionCard : public BaseItem
{
public:
    friend class TestStudyInPink;
    ExcemptionCard();
    bool canUse(Character *, Robot *) const;
    void use(Character *const &, Robot *) const;
    ~ExcemptionCard() {}
};

class PassingCard : public BaseItem
{
public:
    string challenge;
    friend class TestStudyInPink;
    PassingCard();
    PassingCard(int);
    PassingCard(PassingCard *); // * Copy constructure
    PassingCard(string);
    bool canUse(Character *, Robot *) const;
    void use(Character *const &, Robot *) const;
    ~PassingCard() {}
};

class SherlockBag : public BaseBag
{
public:
    friend class TestStudyInPink;
    SherlockBag(Sherlock *);
};

class WatsonBag : public BaseBag
{
public:
    friend class TestStudyInPink;
    WatsonBag(Watson *);
};
class StudyPinkProgram
{
private:
    Configuration *config;
    Sherlock *sherlock;
    Watson *watson;
    Criminal *criminal;
    Map *map;
    ArrayMovingObject *arr_mv_objs;
    SherlockBag *sherlock_bag;
    WatsonBag *watson_bag;
    bool stop(bool, int);
    void exchangeCard();
public:
    StudyPinkProgram(const string &config_file_path);
    bool isStop() const;
    void createRobot(int &);
    void printResult() const
    {
        if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Sherlock caught the criminal" << endl;
        }
        else if (watson->getCurrentPosition().isEqual(criminal->getCurrentPosition()))
        {
            cout << "Watson caught the criminal" << endl;
        }
        else
        {
            cout << "The criminal escaped" << endl;
        }
    }
    void printStep(int si) const
    {
        cout << "Step: " << setw(4) << setfill('0') << si
             << "--"
             << sherlock->str() << "--|--" << watson->str() << "--|--" << criminal->str() << endl;
        
    }
    void run(bool);
    ~StudyPinkProgram();
    friend class TestStudyInPink;
};
#endif
// * END STUDENT'S ANSWER
// * // * // * // * // * // * // * // * // * // * // * // * // * // * // * // * //
// *  NGUYEN PHUC NHAN                                                          //
// *  Phone:     0*****3456                                                     //
// *  Email:     nhan.nguyen200phuyen@hcmut.edu.vn                              //
// *  Website:   http://phucnhan289.great-site.net/1/index.html                 //
// *  Github:    https://github.com/nhan2892005                                 //
// *  Facebook:  https://www.facebook.com/phucnhancshcmut/                      //
// *  Linkedin:  https://www.linkedin.com/in/phúc-nhân-nguyễn-778b26275/        //
// *  LeetCode:  https://leetcode.com/u/N289/                                   //
// * // * // * // * // * // * // * // * // * // * // * // * // * // * // * // * //