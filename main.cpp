/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Initial code for Assignment 1
* Programming Fundamentals Spring 2023
* Author: Vu Van Tien
* Date: 01.03.2023
*/

//The library here is concretely set, students are not allowed to include any other libraries.

#include "study_in_pink2.h"

using namespace std;

void g_satc_02() { // global
    cout << "----- Sample Testcase 02 -----" << endl;
    Configuration * config = new Configuration("sa_tc_02_config");
    cout << config->str() << endl;
    delete config;
}

class TestStudyInPink {
public:
    TestStudyInPink() = default;

    static void satc_01() {
        cout << "----- Sample Testcase 01 -----" << endl;
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};

        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        
        Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
        cout << sherlock->str() << endl;

        Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
        cout << watson->str() << endl;

        Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);
        cout << criminal->str() << endl;

        cout << "* Sherlock makes a move" << endl;
        sherlock->move();
        cout << sherlock->str() << endl;

        cout << "* Watson makes a move" << endl;
        watson->move();
        cout << watson->str() << endl;

        cout << "* Criminal makes a move" << endl;
        criminal->move();
        cout << criminal->str() << endl;

        ArrayMovingObject * arr_mv_objs = new ArrayMovingObject(10);
        arr_mv_objs->add(criminal);
        arr_mv_objs->add(sherlock);
        arr_mv_objs->add(watson);
        cout << arr_mv_objs->str() << endl;
        
        delete arr_mv_objs;
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
    }

    static void satc_02() {
        g_satc_02();
    }

    static void satc_03() {
        // Sample test for RobotC
        cout << "----- Sample Testcase 03 -----" << endl;
        int num_walls = 3;
        Position arr_walls[] = {Position(1, 2), Position(2, 3), Position(3, 4)};
        int num_fake_walls = 1;
        Position arr_fake_walls[] = {Position(2, 0)};

        Map * map = new Map(10, 10, num_walls, arr_walls, num_fake_walls, arr_fake_walls);

        Sherlock * sherlock = new Sherlock(1, "RUU", Position(1, 3), map, 250, 450);
        Watson * watson = new Watson(2, "LU", Position(2, 1), map, 300, 350);
        Criminal * criminal = new Criminal(0, Position(7, 9), map, sherlock, watson);

        RobotC * robotC = new RobotC(3, criminal->getCurrentPosition(), map, criminal);
        cout << "Current position of robotC: " << robotC->str() << endl;
        cout << "RobotC makes a move" << endl;
        robotC->move();
        cout << "New position of robotC: " << robotC->str() << endl;

        RobotS * robotS = new RobotS(4, criminal->getCurrentPosition(), map, criminal,sherlock);
        cout << "Current position of robotS: " << robotS->str() << endl;
        cout << "RobotS makes a move" << endl;
        robotC->move();
        cout << "New position of robotS: " << robotS->str() << endl;

        RobotW * robotW = new RobotW(5, criminal->getCurrentPosition(), map, criminal,watson);
        cout << "Current position of robotW: " << robotW->str() << endl;
        cout << "RobotW makes a move" << endl;
        robotC->move();
        cout << "New position of robotW: " << robotW->str() << endl;

        RobotSW * robotSW = new RobotSW(6, criminal->getCurrentPosition(), map, criminal,sherlock,watson);
        cout << "Current position of robotSW: " << robotSW->str() << endl;
        cout << "RobotSW makes a move" << endl;
        robotC->move();
        cout << "New position of robotSW: " << robotSW->str() << endl;

        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
        delete robotC;
        delete robotS;
        delete robotW;
        delete robotSW;
    }

    /*static void satc_04() {
        BaseItem * Item1 = new MagicBook();
        BaseItem * Item2 = new EnergyDrink();
        BaseItem * Item3 = new ExcemptionCard();
        BaseItem * Item4 = new PassingCard();
        BaseItem * Item5 = new FirstAid();

        SherlockBag * SBag = new SherlockBag();
        SBag->insert(Item1);
        SBag->insert(Item2);
        SBag->insert(Item3);
        SBag->insert(Item4);
        SBag->insert(Item5);
        
        WatsonBag * WBag = new WatsonBag();
        WBag->insert(Item1);
        WBag->insert(Item2);
        WBag->insert(Item3);
        WBag->insert(Item4);
        WBag->insert(Item5);
    }*/
};

int main(int argc, const char * argv[]) {
    //TestStudyInPink::satc_01();
    //TestStudyInPink::satc_02();
    //TestStudyInPink::satc_03();
    TestStudyInPink::satc_03();
    return 0;
}