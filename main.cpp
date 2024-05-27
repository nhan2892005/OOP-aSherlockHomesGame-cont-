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
void copyFile(const std::string& sourcePath, const std::string& destinationPath);
void printTestFail(int i);
void comparefile(int start, int end);
bool isNumber(string str);

ofstream OUTPUT;
string folder_output = "Testcase/output/output";
string input = "Testcase/input/input";
string folder_expect = "Testcase/expect/expect";

class TestStudyInPink {
public:
    TestStudyInPink() = default;

    static void checkMap(string input_file) {
        OUTPUT << "----- Testcase Init Map -----" << endl;
        ifstream in_file(input + input_file);
        int map_size_row, map_size_col, num_walls, num_fake_walls;
        in_file >> map_size_row >> map_size_col;
        in_file >> num_walls;
        Position arr_walls[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_walls[i] = Position(u, v);
        }

        in_file >> num_fake_walls;
        Position arr_fake_walls[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_fake_walls[i] = Position(u, v);
        }
        Map * map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        OUTPUT << "Size of Map: " << map_size_row << " " << map_size_col << endl;
        OUTPUT << "Number of Walls: " << num_walls << endl;
        OUTPUT << "Number of FakeWalls: " << num_fake_walls << endl; 
        OUTPUT << "Read Map Successfully";
        delete map;
    }

    static void checkSherlock(string input_file) {
        OUTPUT << "----- Testcase Init Sherlock -----" << endl;
        ifstream in_file(input + input_file);
        int map_size_row, map_size_col, num_walls, num_fake_walls;
        in_file >> map_size_row >> map_size_col;
        in_file >> num_walls;
        Position arr_walls[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_walls[i] = Position(u, v);
        }

        in_file >> num_fake_walls;
        Position arr_fake_walls[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_fake_walls[i] = Position(u, v);
        }
        Map * map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        string moving_rule;
        in_file >> moving_rule;
        int u, v, hp, exp;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Sherlock * sherlock = new Sherlock(1, moving_rule, Position(u, v), map, hp, exp);
        OUTPUT << sherlock->str() << endl;
        OUTPUT << "* Sherlock make a move" << endl;
        sherlock->move();
        OUTPUT << sherlock->str();
        delete map;
        delete sherlock;
    }

    static void checkWatson(string input_file){
        OUTPUT << "----- Testcase Init Watson -----" << endl;
        ifstream in_file(input + input_file);
        int map_size_row, map_size_col, num_walls, num_fake_walls;
        in_file >> map_size_row >> map_size_col;
        in_file >> num_walls;
        Position arr_walls[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_walls[i] = Position(u, v);
        }

        in_file >> num_fake_walls;
        Position arr_fake_walls[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_fake_walls[i] = Position(u, v);
        }
        Map * map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        string moving_rule;
        in_file >> moving_rule;
        int u, v, hp, exp;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Watson * watson = new Watson(2, moving_rule, Position(u, v), map, hp, exp);
        OUTPUT << watson->str() << endl;
        OUTPUT << "* Watson make a move" << endl;
        watson->move();
        OUTPUT << watson->str();
        delete map;
        delete watson;
    }

    static void checkCriminal(string input_file){
        OUTPUT << "----- Testcase Init Criminal -----" << endl;
        ifstream in_file(input + input_file);
        int map_size_row, map_size_col, num_walls, num_fake_walls;
        in_file >> map_size_row >> map_size_col;
        in_file >> num_walls;
        Position arr_walls[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_walls[i] = Position(u, v);
        }

        in_file >> num_fake_walls;
        Position arr_fake_walls[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_fake_walls[i] = Position(u, v);
        }
        Map * map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        string moving_rule;
        in_file >> moving_rule;
        int u, v, hp, exp;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Sherlock * sherlock = new Sherlock(1, moving_rule, Position(u, v), map, hp, exp);
        in_file >> moving_rule;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Watson * watson = new Watson(2, moving_rule, Position(u, v), map, hp, exp);
        in_file >> u >> v;
        Criminal * criminal = new Criminal(0, Position(u, v), map, sherlock, watson);
        OUTPUT << criminal->str() << endl;
        OUTPUT << "* Criminal make a move" << endl;
        criminal->move();
        OUTPUT << criminal->str();
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
    }
    static void checkArrMovingObject(string input_file){
        OUTPUT << "----- Testcase Init ArrayMovingObject -----" << endl;
        ifstream in_file(input + input_file);
        int map_size_row, map_size_col, num_walls, num_fake_walls;
        in_file >> map_size_row >> map_size_col;
        in_file >> num_walls;
        Position arr_walls[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_walls[i] = Position(u, v);
        }

        in_file >> num_fake_walls;
        Position arr_fake_walls[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_fake_walls[i] = Position(u, v);
        }
        Map * map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        string moving_rule;
        in_file >> moving_rule;
        int u, v, hp, exp;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Sherlock * sherlock = new Sherlock(1, moving_rule, Position(u, v), map, hp, exp);
        in_file >> moving_rule;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Watson * watson = new Watson(2, moving_rule, Position(u, v), map, hp, exp);
        in_file >> u >> v;
        Criminal * criminal = new Criminal(0, Position(u, v), map, sherlock, watson);
        ArrayMovingObject * arr = new ArrayMovingObject(3);
        arr->add(criminal);
        arr->add(sherlock);
        arr->add(watson);
        arr->add(criminal);
        OUTPUT << arr->str();
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
        delete arr;
    }

    static void checkConfig(string input_file){
        OUTPUT << "----- Testcase Read Config -----" << endl;
        Configuration * config = new Configuration(input + input_file);
        OUTPUT << config->str() << endl;
        delete config;
    }

    static void checkRobot(string input_file) {
        OUTPUT << "----- Testcase Init Robot -----" << endl;
        ifstream in_file(input + input_file);
        int map_size_row, map_size_col, num_walls, num_fake_walls;
        in_file >> map_size_row >> map_size_col;
        in_file >> num_walls;
        Position arr_walls[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_walls[i] = Position(u, v);
        }

        in_file >> num_fake_walls;
        Position arr_fake_walls[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_fake_walls[i] = Position(u, v);
        }
        Map * map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        string moving_rule;
        in_file >> moving_rule;
        int u, v, hp, exp;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Sherlock * sherlock = new Sherlock(1, moving_rule, Position(u, v), map, hp, exp);
        in_file >> moving_rule;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Watson * watson = new Watson(2, moving_rule, Position(u, v), map, hp, exp);
        in_file >> u >> v;
        Criminal * criminal = new Criminal(0, Position(u, v), map, sherlock, watson);
        //////////////////////////////////////////
        OUTPUT << "Check ROBOTC" << endl;
        OUTPUT << "Current position of Criminal: " << criminal->str() << endl;
        OUTPUT << "* Criminal make a move" << endl;
        criminal->move();
        OUTPUT << "New position of Criminal: " << criminal->str() << endl;
        //////////////////////////////////////////
        RobotC * robotC = new RobotC(3, criminal->getCurrentPosition(), map, criminal);
        OUTPUT << "* Criminal make a move" << endl;
        criminal->move();
        OUTPUT << "New position of Criminal: " << criminal->str() << endl;
        /////////////////////////////////////////
        OUTPUT << "Current position of robotC: " << robotC->str() << endl;
        OUTPUT << "RobotC makes a move" << endl;
        robotC->move();
        OUTPUT << "New position of robotC: " << robotC->str() << endl;

        //////////////////////////////////////////
        OUTPUT << "Check ROBOTS" << endl;
        RobotS * robotS = new RobotS(4, criminal->getCurrentPosition(), map, criminal,sherlock);
        OUTPUT << "Current position of robotS: " << robotS->str() << endl;
        OUTPUT << "RobotS makes a move" << endl;
        robotS->move();
        OUTPUT << "New position of robotS: " << robotS->str() << endl;

        //////////////////////////////////////////
        OUTPUT << "Check ROBOTW" << endl;
        RobotW * robotW = new RobotW(5, criminal->getCurrentPosition(), map, criminal,watson);
        OUTPUT << "Current position of robotW: " << robotW->str() << endl;
        OUTPUT << "RobotW makes a move" << endl;
        robotW->move();
        OUTPUT << "New position of robotW: " << robotW->str() << endl;

        ///////////////////////////////////////////
        OUTPUT << "Check ROBOTSW" << endl;
        RobotSW * robotSW = new RobotSW(6, criminal->getCurrentPosition(), map, criminal,sherlock,watson);
        OUTPUT << "Current position of robotSW: " << robotSW->str() << endl;
        OUTPUT << "RobotSW makes a move" << endl;
        robotSW->move();
        OUTPUT << "New position of robotSW: " << robotSW->str() << endl;

        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
        delete robotC;
        delete robotS;
        delete robotW;
        delete robotSW;
    }
    static void checkItem(string input_file){
        OUTPUT << "----- Testcase Init Item -----" << endl;
        ifstream in_file(input + input_file);
        int map_size_row, map_size_col, num_walls, num_fake_walls;
        in_file >> map_size_row >> map_size_col;
        in_file >> num_walls;
        Position arr_walls[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_walls[i] = Position(u, v);
        }

        in_file >> num_fake_walls;
        Position arr_fake_walls[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_fake_walls[i] = Position(u, v);
        }
        Map * map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        string moving_rule;
        in_file >> moving_rule;
        int u, v, hp, exp;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Sherlock * sherlock = new Sherlock(1, moving_rule, Position(u, v), map, hp, exp);
        in_file >> moving_rule;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Watson * watson = new Watson(2, moving_rule, Position(u, v), map, hp, exp);
        in_file >> u >> v;
        Criminal * criminal = new Criminal(0, Position(u, v), map, sherlock, watson);
        RobotC * robotC = new RobotC(3, criminal->getCurrentPosition(), map, criminal);
        RobotS * robotS = new RobotS(4, criminal->getCurrentPosition(), map, criminal,sherlock);
        RobotW * robotW = new RobotW(5, criminal->getCurrentPosition(), map, criminal,watson);
        RobotSW * robotSW = new RobotSW(6, criminal->getCurrentPosition(), map, criminal,sherlock,watson);
        ////////
        BaseItem * Item1 = new MagicBook();
        BaseItem * Item2 = new EnergyDrink();
        BaseItem * Item3 = new ExcemptionCard();
        BaseItem * Item4 = new PassingCard();
        BaseItem * Item5 = new FirstAid();
        ////////////////////////////////
        OUTPUT << "Sherlock can use MagicBook?" <<endl;
        if (Item1->canUse(sherlock, NULL)){
            OUTPUT << "can use" << endl;
            Item1->use(sherlock, NULL);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << sherlock->str() << endl;
        ////////////////////////////////
        OUTPUT << "Sherlock can use EnergyDrink?" <<endl;
        if (Item2->canUse(sherlock, NULL)){
            OUTPUT << "can use" << endl;
            Item2->use(sherlock, NULL);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << sherlock->str() << endl;
        //////////////////////////////////
        OUTPUT << "Sherlock can use FirstAid?" <<endl;
        if (Item5->canUse(sherlock, NULL)){
            OUTPUT << "can use" << endl;
            Item5->use(sherlock, NULL);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << sherlock->str() << endl;
        ///////////////////////////////////
        OUTPUT << "Sherlock can use ExcemptionCard with RobotC?" <<endl;
        if (Item3->canUse(sherlock, robotC)){
            OUTPUT << "can use" << endl;
            Item3->use(sherlock, robotC);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << sherlock->str() << endl;
        ///////////////////////////////////
        OUTPUT << "Sherlock can use ExcemptionCard with RobotS?" <<endl;
        if (Item3->canUse(sherlock, robotS)){
            OUTPUT << "can use" << endl;
            Item3->use(sherlock, robotS);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << sherlock->str() << endl;
        //////////////////////////////////
        OUTPUT << "Sherlock can use ExcemptionCard with RobotW?" <<endl;
        if (Item3->canUse(sherlock, robotW)){
            OUTPUT << "can use" << endl;
            Item3->use(sherlock, robotW);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << sherlock->str() << endl;
        //////////////////////////////////
        OUTPUT << "Sherlock can use ExcemptionCard with RobotSW?" <<endl;
        if (Item3->canUse(sherlock, robotSW)){
            OUTPUT << "can use" << endl;
            Item3->use(sherlock, robotSW);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << sherlock->str() << endl;
        //////////////////////////////////
        OUTPUT << "Sherlock can use PassingCard" <<endl;
        if (Item4->canUse(sherlock, NULL)){
            OUTPUT << "can use" << endl;
            Item4->use(sherlock, NULL);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << sherlock->str() << endl;
        ////////////////////////////////
        OUTPUT << "Watson can use MagicBook?" <<endl;
        if (Item1->canUse(watson, NULL)){
            OUTPUT << "can use" << endl;
            Item1->use(watson, NULL);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << watson->str() << endl;
        ////////////////////////////////
        OUTPUT << "Watson can use EnergyDrink?" <<endl;
        if (Item2->canUse(watson, NULL)){
            OUTPUT << "can use" << endl;
            Item2->use(watson, NULL);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << watson->str() << endl;
        //////////////////////////////////
        OUTPUT << "Watson can use FirstAid?" <<endl;
        if (Item5->canUse(watson, NULL)){
            OUTPUT << "can use" << endl;
            Item5->use(watson, NULL);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << watson->str() << endl;
        ///////////////////////////////////
        OUTPUT << "Watson can use PassingCard with RobotC?" <<endl;
        if (Item4->canUse(watson, robotC)){
            OUTPUT << "can use" << endl;
            Item4->use(watson, robotC);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << watson->str() << endl;
        ///////////////////////////////////
        OUTPUT << "Watson can use PassingCard with RobotS?" <<endl;
        if (Item4->canUse(watson, robotS)){
            OUTPUT << "can use" << endl;
            Item4->use(watson, robotS);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << watson->str() << endl;
        //////////////////////////////////
        OUTPUT << "Watson can use PassingCard with RobotW?" <<endl;
        if (Item4->canUse(watson, robotW)){
            OUTPUT << "can use" << endl;
            Item4->use(watson, robotW);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << watson->str() << endl;
        //////////////////////////////////
        OUTPUT << "Watson can use PassingCard with RobotSW?" <<endl;
        if (Item4->canUse(watson, robotSW)){
            OUTPUT << "can use" << endl;
            Item4->use(watson, robotSW);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << watson->str() << endl;
        //////////////////////////////////
        OUTPUT << "Watson can use ExcemptionCard" <<endl;
        if (Item3->canUse(watson, NULL)){
            OUTPUT << "can use" << endl;
            Item3->use(watson, NULL);
        }
        else{
            OUTPUT << "can not use" << endl;
        }
        OUTPUT << watson->str() << endl;
        delete sherlock;
        delete watson;
        delete criminal;
        delete map;
        delete robotC;
        delete robotS;
        delete robotW;
        delete robotSW;
        delete Item1;
        delete Item2;
        delete Item3;
        delete Item4;
        delete Item5;
    }
    static void checkBag(string input_file) {
        OUTPUT << "----- Testcase Init Bag -----" << endl;
        ifstream in_file(input + input_file);
        int map_size_row, map_size_col, num_walls, num_fake_walls;
        in_file >> map_size_row >> map_size_col;
        in_file >> num_walls;
        Position arr_walls[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_walls[i] = Position(u, v);
        }

        in_file >> num_fake_walls;
        Position arr_fake_walls[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            in_file >> u >> v;
            arr_fake_walls[i] = Position(u, v);
        }
        Map * map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        string moving_rule;
        in_file >> moving_rule;
        int u, v, hp, exp;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Sherlock * sherlock = new Sherlock(1, moving_rule, Position(u, v), map, hp, exp);
        in_file >> moving_rule;
        in_file >> u >> v;
        in_file >> hp >> exp;
        Watson * watson = new Watson(2, moving_rule, Position(u, v), map, hp, exp);

        BaseItem * Item1 = new MagicBook();
        BaseItem * Item2 = new EnergyDrink();
        BaseItem * Item3 = new ExcemptionCard();
        BaseItem * Item4 = new PassingCard();
        BaseItem * Item5 = new FirstAid();
        BaseBag * Bag = new BaseBag();
        Bag->insert(Item1);
        Bag->insert(Item2);
        Bag->insert(Item3);
        Bag->insert(Item4);
        Bag->insert(Item5);
        Bag->get(MAGIC_BOOK);
        Bag->get(ENERGY_DRINK);
        OUTPUT << Bag->str() << endl;
    
        SherlockBag * SBag = new SherlockBag(sherlock);
        SBag->insert(Item1);
        SBag->insert(Item2);
        SBag->insert(Item3);
        SBag->insert(Item4);
        SBag->insert(Item5);
        SBag->insert(Item5);
        SBag->insert(Item4);
        SBag->insert(Item3);
        SBag->insert(Item2);
        SBag->insert(Item1);
        SBag->get(PASSING_CARD);
        SBag->get(PASSING_CARD);
        SBag->get(PASSING_CARD);
        SBag->get();
        SBag->get();
        OUTPUT << SBag->str() << endl;

        WatsonBag * WBag = new WatsonBag(watson);
        WBag->insert(Item5);
        WBag->insert(Item4);
        WBag->insert(Item3);
        WBag->insert(Item2);
        WBag->insert(Item1);
        WBag->insert(Item5);
        WBag->insert(Item4);
        WBag->insert(Item3);
        WBag->insert(Item2);
        WBag->insert(Item1);
        WBag->get(EXCEMPTION_CARD);
        WBag->get(ENERGY_DRINK);
        WBag->get(PASSING_CARD);
        WBag->get(ENERGY_DRINK);
        WBag->get(EXCEMPTION_CARD);
        WBag->get();
        OUTPUT << WBag->str() << endl;

        delete Item1;
        delete Item2;
        delete Item3;
        delete Item4;
        delete Item5;
        
        delete map;
        delete sherlock;
        delete SBag;
        delete watson;
        delete WBag;
    }  

    static void TestProgram(string input_file){
        // Lưu trữ buffer hiện tại của std::cout
        std::streambuf* originalBuffer = std::cout.rdbuf();

        // Đặt buffer của std::cout tới file
        std::cout.rdbuf(OUTPUT.rdbuf());

        StudyPinkProgram * program = new StudyPinkProgram(input + input_file);
        program->run(1);
        delete program;
        //program = new StudyPinkProgram(input + input_file);
        //program->run(0);

        // Khôi phục buffer ban đầu của std::cout
        std::cout.rdbuf(originalBuffer);
    }

    static void TestProgram2(string input_file){
        // Lưu trữ buffer hiện tại của std::cout
        std::streambuf* originalBuffer = std::cout.rdbuf();

        // Đặt buffer của std::cout tới file
        std::cout.rdbuf(OUTPUT.rdbuf());

        StudyPinkProgram * program = new StudyPinkProgram(input + input_file);
        program->run(0);
        delete program;
        //program = new StudyPinkProgram(input + input_file);
        //program->run(0);
        // Khôi phục buffer ban đầu của std::cout
        std::cout.rdbuf(originalBuffer);
    }

    static void LocalTest(){

    }
};

void run(string input_file)
{
    int test = stoi(input_file);
    if(test <= 10)
    {   
        TestStudyInPink::checkMap(input_file);
    }
    else if(test <= 20)
    {    
        TestStudyInPink::checkSherlock(input_file);
    }
    else if (test <= 30)
    {
        TestStudyInPink::checkWatson(input_file);
    }
    else if(test <= 40)
    {      
        TestStudyInPink::checkCriminal(input_file);
    }
    else if(test <= 50)
    {
        TestStudyInPink::checkArrMovingObject(input_file);
    }
    else if(test <= 60)
    {
        TestStudyInPink::checkConfig(input_file);
    }
    else if(test <= 70)
    {
        TestStudyInPink::checkRobot(input_file);
    }
    else if(test <= 80)
    {
        TestStudyInPink::checkItem(input_file);
    }
    else if(test <= 90)
    {
        TestStudyInPink::checkBag(input_file);
    }
    else if(test <= 130)
    {
        TestStudyInPink::TestProgram(input_file);
    }
    else if (test <= 150)
    {
        TestStudyInPink::TestProgram2(input_file);
    }
}

int main(int argc, char *argv[])
{
	cout << "Start program assignments 2" << endl;


    int START = 1, END = 150;
    int fullTask = 150;

    if (argc == 1)
    {
        cout << "checking test : ";
        START = 1;
        END = 150;
        for (int i = START; i <= END; i++)
        {
            cout << i << " ";
            OUTPUT.open(folder_output + to_string(i) + ".txt");
            run(to_string(i));
            OUTPUT.close();
        }
    }

    else if(argc == 2)
    {
        string stringTask = argv[1];
        if (isNumber(stringTask))
        {
            cout << "checking test : " << argv[1];
            START = stoi(stringTask);
            END = stoi(stringTask);
            OUTPUT.open(folder_output + stringTask + ".txt");
            run(stringTask);
            OUTPUT.close();            
        }
        else if(stringTask == "local"){
            cout << "checking LocalTest : ";
            TestStudyInPink::LocalTest();
        }
        else if(stringTask == "me")
        {
            cout << "checking test : ";
            for (int i = 1; i <= 90; i++)
            {
                cout << i << " ";
                OUTPUT.open(folder_output + to_string(i) + ".txt");
                run(to_string(i));
                OUTPUT.close();
            }            
        }
        else if(stringTask.substr(0,4) != "task" || stringTask[4] <= '0' || stringTask[4] > '5')
        {
            cout << "Please re-enter the correct command" << endl;
            cout << "./main task1\n./main task2\n./main task3\n./main task4\n./main task5\n./main number" << endl;
            return 0;
        }
        else
        {
            cout << "checking test : ";

            START = fullTask * (stringTask[4] - '0' - 1) + 1;
            END = fullTask * (stringTask[4] - '0');
            if(stringTask[4] - '0' == 4){
                START = 401;
                END = 600;
            }
            else if (stringTask[4] - '0' == 3){
                START = 801;
                END = 1000;
            }
            else if(stringTask[4] - '0' == 5){
                START = 601;
                END = 800;
            }
            for (int i = START; i <= END; i++)
            {
                cout << i << " ";
                OUTPUT.open(folder_output + to_string(i) + ".txt");
                run(to_string(i));
                OUTPUT.close();
            }     
        }
    }
    else if (argc == 3 && isNumber(argv[1]) && isNumber(argv[2]))
    {
        cout << "checking test : ";
        START = stoi(argv[1]);
        END = stoi(argv[2]);
        for (int i = stoi(argv[1]); i <= stoi(argv[2]); i++)
        {
            cout << i << " ";
            OUTPUT.open(folder_output + to_string(i) + ".txt");
            run(to_string(i));
            OUTPUT.close();
        }           
    }
    else 
    {
        cout << "Please re-enter the correct command" << endl;
        cout << "./main task1\n./main task2\n./main task3\n./main task4\n./main task5\n./main number" << endl;
        return 0;
    }

	cout << "\nOK: runs without errors\n" << endl;
    comparefile(START, END);
    return 1;
}




bool isNumber(string str) {
    for (int i = 0; i < str.length(); i++) {
        char c = str[i];
        if (!isdigit(c)) return false;
    }
    return true;
}

void comparefile(int start, int end)
{
	vector<int> result;
	for (int i = start; i <= end; i++)
	{
		ifstream read_output(folder_output + to_string(i) + ".txt");
		ifstream read_expect(folder_expect + to_string(i) + ".txt");
		if (read_output.fail() || read_expect.fail())
		{
			cout << "Error reading file"<< end;
			return;
		}
		string s1, s2;
		while (read_output >> s1 && read_expect >> s2)
		{
			if (s1 != s2)
			{
				result.push_back(i);
				break;
			}
		}
		if (read_output >> s1 || read_expect >> s2)
		{
			if (result.size() == 0 || result.size() > 0 && result[result.size() - 1] != i)
				result.push_back(i);
		}
	}

	if (result.size() == 0)
	{
		cout << "Success: test " << start << " to " << end << endl;
	}
	else
	{
		cout << "percent success : " << (1 - result.size() * 1.0 / (end - start + 1)) * 100 << "%" << endl;
		cout << "Fail : test [";
		for (int i = 0; i < result.size() - 1; i++)
		{
			cout << result[i] << ", ";
		}
		cout << result[result.size() - 1] << "]\n";
        cout << "link check comparefile: https://www.diffchecker.com/text-compare/" << endl;
		//printTestFail(result[0]);
	}
}

void copyFile(const std::string& sourcePath, const std::string& destinationPath) {
    std::ifstream sourceFile(sourcePath, std::ios::binary);
    std::ofstream destinationFile(destinationPath, std::ios::binary);

    if (!sourceFile) {
        std::cerr << "Error opening source file: " << sourcePath << std::endl;
        return;
    }


    if (!destinationFile) {
        std::cerr << "Error opening destination file: " << destinationPath << std::endl;
        return;
    }

    destinationFile << sourceFile.rdbuf();

    if (!destinationFile) {
        std::cerr << "Error copying data from " << sourcePath << " to " << destinationPath << std::endl;
    }
}