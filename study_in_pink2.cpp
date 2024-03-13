#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
// My ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////
void checkValue(int &value, int max_value){
    if (value > max_value)
        value = max_value;
}

int ManhattanDistance(const Position &pos1, const Position &pos2){
    return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
}
// global function

MapElement::MapElement(ElementType in_type) 
    : type(in_type) {}

MapElement::~MapElement() 
{
    return;
}

ElementType MapElement::getType() const 
{
    return type;
}

Path::Path() 
    : MapElement(ElementType::PATH) {}

Path::~Path()
{
    return;
}

Wall::Wall()
    : MapElement(ElementType::WALL) {}

Wall::~Wall()
{
    return;
}

FakeWall::FakeWall(int in_req_exp)
    : MapElement(ElementType::FAKE_WALL), req_exp(in_req_exp) {}

FakeWall::~FakeWall()
{
    return;
}

int FakeWall::getReqExp() const 
{
    return req_exp;
}

                            /*
                                HCMUT 14:02 10/03/2024
                                Class MapElement
                                Done
                            */
Map::Map(int num_rows, 
         int num_cols,
         int num_walls,
         Position *array_walls,
         int num_fake_walls,
         Position *array_fake_walls)
    : num_rows(num_rows), num_cols(num_cols)
{
    //Create a 2D array of MapElement pointers
    map = new MapElement **[num_rows];
    for (int i = 0; i < num_rows; i++)
    {
        map[i] = new MapElement*[num_cols];
    }
    for (int row = 0; row < num_rows; row++)
    {
        for (int col = 0; col < num_cols; col++)
        {
            map[row][col] = new Path();
        }
    }

    //Change Type of MapElement -> Wall at the given positions
    for (int i = 0; i < num_walls; i++)
    {
        int row = array_walls[i].getRow();
        int col = array_walls[i].getCol();
        delete map[row][col];
        map[row][col] = new Wall();
    }
    //Change Type of MapElement ->FakeWall at the given positions
    for (int i = 0; i < num_fake_walls; i++)
    {
        int row = array_fake_walls[i].getRow();
        int col = array_fake_walls[i].getCol();
        delete map[row][col];
        map[row][col] = new FakeWall((row * 257 + col * 139 + 89) % 900 + 1);
    }
}

Map::~Map()
{
    for (int i = 0; i < num_rows; i++)
    {
        delete[] map[i];
    }
    delete[] map;
}
bool Map::isValid(const Position &pos, MovingObject *mv_obj) const
{
    //Out of Map
    if (pos.getRow() < 0 || pos.getRow() >= num_rows || 
        pos.getCol() < 0 || pos.getCol() >= num_cols )
    {
        return false;
    }

    //Meet Fake Wall
    if (map[pos.getRow()][pos.getCol()]->getType() == ElementType::FAKE_WALL)
    {
        //Criminal & Sherlock can pass
        //Waston need have enough exp to pass
        if (mv_obj->getName() == "Watson")
        {
            Watson * w = (Watson*)mv_obj;
            FakeWall * fake = (FakeWall*)map[pos.getRow()][pos.getCol()];
            if(w->getEXP() <= fake->getReqExp())
            {
                //delete w;
                //delete fake;
                return false;
            }
            else
            {
                //delete w;
                //delete fake;
            }
        }
    }

    //Meet Wall
    if (map[pos.getRow()][pos.getCol()]->getType() == ElementType::WALL)
    {
        return false;
    }
    return true;
}
                            /*
                                HCMUT 14:19 10/03/2024
                                Class Map
                                Done
                            */

const Position Position::npos = Position(-1, -1);

Position::Position(int r, int c) 
    : r(r), c(c) {}

Position::Position(const string &str_pos)
{
    int pos = str_pos.find(",");
    r = stoi(str_pos.substr(1, pos - 1));
    c = stoi(str_pos.substr(pos + 1, str_pos.size() - pos - 2));
}

int Position::getRow() const
{
    return r;
}

int Position::getCol() const
{
    return c;
}

void Position::setRow(int row)
{
    this->r = row;
}

void Position::setCol(int col)
{
    this->c = col;
}

string Position::str() const
{
    return "(" + to_string(r) + "," + to_string(c) + ")";
}

bool Position::isEqual(int in_r, int in_c) const{
    return (r == in_r && c == in_c);
}
                            /*
                                HCMUT 13:58 10/03/2024
                                Class Position
                                Done
                            */
MovingObject::MovingObject( int index, 
                            const Position pos, 
                            Map *map, 
                            const string &name)
    : index(index), pos(pos), map(map), name(name) {}

void MovingObject::getStep(int istep){
    this->step = istep;
}
MovingObject::~MovingObject() 
{
    ;
}

string MovingObject::getName() const
{
    return name;
}
Position MovingObject::getCurrentPosition() const
{
    return pos;
}
                            /*
                                HCMUT 14:41 10/03/2024
                                Class MovingObject
                                Done
                            */
Sherlock::Sherlock( int index, 
                    const string &moving_rule, 
                    const Position &init_pos, 
                    Map *map, 
                    int init_hp, 
                    int init_exp)
    :   Character(index, init_pos, map, 1,"Sherlock"),
        moving_rule(moving_rule),
        hp(init_hp),
        exp(init_exp)
{
    checkValue(hp, max_hp);
    checkValue(exp, max_exp);
}
char Sherlock::getNextMoving()
{
    return moving_rule[(this->step - 1) % this->moving_rule.size()];
}
Position Sherlock::getNextPosition()
{
    if (moving_rule.empty())
    {
        return Position::npos;
    }
    Position next_pos = getCurrentPosition();
    char next_move = getNextMoving();
    switch (next_move)
    {
        case 'L':
            next_pos.setCol(next_pos.getCol() - 1);
            break;
        case 'R':
            next_pos.setCol(next_pos.getCol() + 1);
            break;
        case 'U':
            next_pos.setRow(next_pos.getRow() - 1);
            break;
        case 'D':
            next_pos.setRow(next_pos.getRow() + 1);
            break;
        default:
            break;
    }
    if (map->isValid(next_pos, this))
    {
        return next_pos;
    }
    return Position::npos;
}
void Sherlock::move()
{
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos.getRow(), Position::npos.getCol()))
    {
        pos = next_pos;
    }
}

string Sherlock::str() const
{
    return "Sherlock[index=" + to_string(index) + 
           ";pos=" + pos.str() + 
           ";moving_rule=" + moving_rule + "]";
}

Sherlock::~Sherlock()
{
    return;
}
                            /*
                                HCMUT 14:47 10/03/2024
                                Class Sherlock
                                Done
                            */
Watson::Watson( int index, 
                const string &moving_rule, 
                const Position &init_pos, 
                Map *map, 
                int init_hp, 
                int init_exp)
    :   Character(index, init_pos, map, 1,"Watson"),
        moving_rule(moving_rule),
        hp(init_hp),
        exp(init_exp)
{
    checkValue(hp, max_hp);
    checkValue(exp, max_exp);
}
char Watson::getNextMoving()
{
    return moving_rule[(this->step - 1) % this->moving_rule.size()];
}
Position Watson::getNextPosition()
{
    if (moving_rule.empty())
    {
        return Position::npos;
    }
    Position next_pos = getCurrentPosition();
    char next_move = getNextMoving();
    switch (next_move)
    {
        case 'L':
            next_pos.setCol(next_pos.getCol() - 1);
            break;
        case 'R':
            next_pos.setCol(next_pos.getCol() + 1);
            break;
        case 'U':
            next_pos.setRow(next_pos.getRow() - 1);
            break;
        case 'D':
            next_pos.setRow(next_pos.getRow() + 1);
            break;
        default:
            break;
    }
    if (map->isValid(next_pos, this))
    {
        return next_pos;
    }
    return Position::npos;
}

void Watson::move()
{
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos.getRow(), Position::npos.getCol()))
    {
        pos = next_pos;
    }
}

string Watson::str() const
{
    return  "Watson[index=" + to_string(index) + 
            ";pos=" + pos.str() + 
            ";moving_rule=" + moving_rule + "]";
}

int Watson::getEXP()
{
    return exp;
}
int Watson::getHP()
{
    return hp;
}
int Sherlock::getEXP()
{
    return exp;
}
int Sherlock::getHP()
{
    return hp;
}
Watson::~Watson()
{
    return;
}
                            /*
                                HCMUT 14:48 10/03/2024
                                Class Watson
                                Done
                            */
Criminal::Criminal( int index , 
                    const Position & init_pos , 
                    Map * map , Sherlock * sherlock , 
                    Watson * watson)
    :Character(index,init_pos,map,1,"Criminal"),
    sherlock(sherlock),
    watson(watson){}

string Criminal::str() const
{
    return  "Criminal[index=" + to_string(index) + 
            ";pos=" + pos.str() + "]";
}

Position Criminal::getNextPosition()
{
    int maxDistance = -1;
    Position Sherlock_pos = sherlock->getCurrentPosition();
    Position Waston_pos = watson->getCurrentPosition();
    Position next_pos = Position::npos;
    for (int i = 1; i <= 4; i++){
        Position temp_pos = this->getCurrentPosition();
        switch (i)
        {
        case 1:
            temp_pos.setRow(temp_pos.getRow() - 1);
            break;
        case 2:
            temp_pos.setCol(temp_pos.getCol() + 1);
            break;
        case 3:
            temp_pos.setRow(temp_pos.getRow() + 1);
            break;
        case 4:
            temp_pos.setCol(temp_pos.getCol() - 1);
            break;
        default:
            break;
        }
        if (map->isValid(temp_pos,this)){
            if (ManhattanDistance(Sherlock_pos, temp_pos)+
                ManhattanDistance(Waston_pos, temp_pos)
                > maxDistance)
            {
                maxDistance =   ManhattanDistance(Sherlock_pos, next_pos)+
                                ManhattanDistance(Waston_pos, next_pos);
                next_pos = temp_pos;
            }
        
        }
    }
    return next_pos;
}

void Criminal::move()
{
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos.getRow(), Position::npos.getCol()))
    {
        pos = next_pos;
    }
}
Criminal::~Criminal(){
    return;
}
                            /*
                                HCMUT 14:48 10/03/2024
                                Class Criminal
                                Done
                            */
ArrayMovingObject::ArrayMovingObject(int capacity)
:capacity(capacity),count(0)
{
    arr_mv_objs = new MovingObject*[capacity];
}
ArrayMovingObject::~ArrayMovingObject()
{
    delete[] arr_mv_objs;
}
bool ArrayMovingObject::isFull() const
{
    return count == capacity;
}
bool ArrayMovingObject::add(MovingObject * mv_obj)
{
    if (isFull())
    {
        return false;
    }
    arr_mv_objs[count] = mv_obj;
    count++;
    return true;
}
string ArrayMovingObject::str() const
{
    string result = "ArrayMovingObject[count=" + to_string(count) + 
                    ";capacity=" + to_string(capacity) + ";";
    for (int i = 0; i < count; i++)
    {
        result += arr_mv_objs[i]->str() + ";";
    }
    result += "]";
    return result;
}

int ArrayMovingObject::maxSize(){
    return capacity;
}

int Configuration::numElement(string temp){
    int count = 0;
    for (int i = 0; i < temp.size(); ++i){
        if (temp[i] == ';'){
            ++count;
        }
    }
    return count+1;
}
Configuration::Configuration(const string & filepath)
{
    ifstream file(filepath);
    string line;
    if (!file.is_open()){
        cout << "File not found" << endl;
        return;
    }
    while (getline(file, line)){
        if (line.find("MAP_NUM_ROWS") != string::npos){
            map_num_rows = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("MAP_NUM_COLS") != string::npos){
            map_num_cols = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("MAX_NUM_MOVING_OBJECTS") != string::npos){
            max_num_moving_objects = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("ARRAY_WALLS") != string::npos){
            init_array(arr_walls, num_walls, line);
        }
        else if (line.find("ARRAY_FAKE_WALLS") != string::npos){
            init_array(arr_fake_walls, num_fake_walls, line);
        }
        else if (line.find("SHERLOCK_MOVING_RULE") != string::npos){
            sherlock_moving_rule = line.substr(line.find("=") + 1);
        }
        else if (line.find("SHERLOCK_INIT_POS") != string::npos){
            init_pos(sherlock_init_pos, line);
        }
        else if (line.find("SHERLOCK_INIT_HP") != string::npos){
            sherlock_init_hp = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("SHERLOCK_INIT_EXP") != string::npos){
            sherlock_init_exp = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("WATSON_MOVING_RULE") != string::npos){
            watson_moving_rule = line.substr(line.find("=") + 1);
        }
        else if (line.find("WATSON_INIT_POS") != string::npos){
            init_pos(watson_init_pos, line);
        }
        else if (line.find("WATSON_INIT_HP") != string::npos){
            watson_init_hp = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("WATSON_INIT_EXP") != string::npos){
            watson_init_exp = stoi(line.substr(line.find("=") + 1));
        }
        else if (line.find("CRIMINAL_INIT_POS") != string::npos){
            init_pos(criminal_init_pos, line);
        }
        else if (line.find("NUM_STEPS") != string::npos){
            num_steps = stoi(line.substr(line.find("=") + 1));
        }
        
    }
    file.close();
}
Configuration::~Configuration()
{
    delete[] arr_walls;
    delete[] arr_fake_walls;
}
void Configuration::init_pos(Position &mv_obj_pos, string line){
    int row = stoi( line.substr(line.find("(") + 1, 
                    line.find(",") - line.find("(") - 1));
    int col = stoi( line.substr(line.find(",") + 1, 
                    line.find(")") - line.find(",") - 1));
    mv_obj_pos.setRow(row);
    mv_obj_pos.setCol(col);
}
void Configuration::init_array(Position * &arr, int &numArr, string line){
    string temp =   line.substr(line.find("[") + 1, 
                    line.find("]") - line.find("[") - 1);
    int pos = 0;
    numArr = 0;
    int numEle = numElement(temp);
    arr = new Position[numEle];
    while (temp.find("(", pos) != string::npos)
    {
        int row = stoi( temp.substr(temp.find("(", pos) + 1, 
                        temp.find(",", pos) - temp.find("(", pos) - 1));
        int col = stoi( temp.substr(temp.find(",", pos) + 1, 
                        temp.find(")", pos) - temp.find(",", pos) - 1));
        arr[numArr].setRow(row);
        arr[numArr].setCol(col);
        numArr++;
        pos = temp.find(")", pos+1);
    }
}
string Configuration::str() const
{
    string result = "Configuration[\n";
    result += "MAP_NUM_ROWS=" + to_string(map_num_rows) + ";\n";
    result += "MAP_NUM_COLS=" + to_string(map_num_cols) + ";\n";
    result += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + ";\n";
    result += "NUM_WALLS=" + to_string(num_walls) + ";\n";
    result += "ARRAY_WALLS=[";
    for (int i = 0; i < num_walls; i++){
        result += "(" + to_string(arr_walls[i].getRow()) + "," + to_string(arr_walls[i].getCol()) + ")";
        if (i != num_walls - 1){
            result += ";";
        }
    }
    result += "];\n";
    result += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + ";\n";
    result += "ARRAY_FAKE_WALLS=[";
    for (int i = 0; i < num_fake_walls; i++){
        result += "(" + to_string(arr_fake_walls[i].getRow()) + "," + to_string(arr_fake_walls[i].getCol()) + ")";
        if (i != num_fake_walls - 1){
            result += ";";
        }
    }
    result += "];\n";
    result += "SHERLOCK_MOVING_RULE=" + sherlock_moving_rule + ";\n";
    result += "SHERLOCK_INIT_POS=(" + to_string(sherlock_init_pos.getRow()) + "," + to_string(sherlock_init_pos.getCol()) + ");\n";
    result += "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + ";\n";
    result += "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + ";\n";
    result += "WATSON_MOVING_RULE=" + watson_moving_rule + ";\n";
    result += "WATSON_INIT_POS=(" + to_string(watson_init_pos.getRow()) + "," + to_string(watson_init_pos.getCol()) + ");\n";
    result += "WATSON_INIT_HP=" + to_string(watson_init_hp) + ";\n";
    result += "WATSON_INIT_EXP=" + to_string(watson_init_exp) + ";\n";
    result += "CRIMINAL_INIT_POS=(" + to_string(criminal_init_pos.getRow()) + "," + to_string(criminal_init_pos.getCol()) + ");\n";
    result += "NUM_STEPS=" + to_string(num_steps) + ";\n";
    result += "]";

    return result;
}

int Configuration::getNumStep(){
    return num_steps;
}



void Configuration::init_info_program(  Sherlock * &sherlock,
                                        Watson * &watson,
                                        Criminal * &criminal,
                                        Map * &map,
                                        ArrayMovingObject * &arr_mv_oj)
{
    map = new Map(map_num_rows, 
                        map_num_cols, 
                        num_walls, 
                        arr_walls, 
                        num_fake_walls, 
                        arr_fake_walls);
    
    sherlock = new Sherlock( 1, 
                            sherlock_moving_rule, 
                            sherlock_init_pos, 
                            map,
                            sherlock_init_hp, 
                            sherlock_init_exp);
    watson = new Watson(   2,
                            watson_moving_rule, 
                            watson_init_pos, 
                            map, 
                            watson_init_hp, 
                            watson_init_exp);
    criminal = new Criminal( 0, 
                            criminal_init_pos, 
                            map, 
                            sherlock, 
                            watson);
    arr_mv_oj = new ArrayMovingObject(max_num_moving_objects);
    arr_mv_oj->add(criminal);
    arr_mv_oj->add(sherlock);
    arr_mv_oj->add(watson);
}

StudyPinkProgram::StudyPinkProgram(const string & config_file_path)
{

    config = new Configuration(config_file_path);
    config->init_info_program(sherlock, watson, criminal, map, arr_mv_objs);
};
bool StudyPinkProgram::isStop() const
{
    if (sherlock->getCurrentPosition().isEqual( criminal->getCurrentPosition().getRow(),
                                                criminal->getCurrentPosition().getRow())
      ||watson->getCurrentPosition().isEqual(   criminal->getCurrentPosition().getRow(),
                                                criminal->getCurrentPosition().getRow())
      ||sherlock->getHP() == 0 || watson->getHP() == 0)
    {
        return true;
    }
    return false;
}
int ArrayMovingObject::getCount(){
    return count;
}
MovingObject * ArrayMovingObject::get(int i)
{
    return arr_mv_objs[i];
}
void StudyPinkProgram::run(bool verbose){
    
    for (int istep = 1; istep <= config->getNumStep(); ++istep) {
        int numMovingObjects = arr_mv_objs->getCount();
        for (int i = 0; i < numMovingObjects; ++i) {
            MovingObject * mv_oj = arr_mv_objs->get(i);
            mv_oj->getStep(istep);
            mv_oj->move();
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
StudyPinkProgram::~StudyPinkProgram()
{
    delete config;
    delete arr_mv_objs;
    delete sherlock;
    delete watson;
    delete criminal;
    delete map;
}
string Robot::str() const
{
    return "";
}
string RobotC::str()
{
    return "";
}
string RobotSW::str()
{
    string s =  "Robot[pos=" + pos.str() + 
                ";type=" + 
                to_string(robot_type) + 
                ";dist=" + 
                to_string(getDistance());
    return s;
}
string RobotS::str()
{
    string s =  "Robot[pos=" + pos.str() + 
                ";type=" + 
                to_string(robot_type) + 
                ";dist=" + 
                to_string(getDistance());
    return s;
}
string RobotW::str()
{
    string s =  "Robot[pos=" + pos.str() + 
                ";type=" + 
                to_string(robot_type) + 
                ";dist=" + 
                to_string(getDistance());
    return s;
}

void Robot::move()
{
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos.getRow(), Position::npos.getCol()))
    {
        pos = next_pos;
    }
}

Position RobotC::getNextPosition()
{
    return criminal->getCurrentPosition();
}
Position RobotS::getNextPosition()
{
    int maxDistance = -1;
    Position Sherlock_pos = sherlock->getCurrentPosition();
    Position next_pos = Position::npos;
    for (int i = 1; i <= 4; i++){
        Position temp_pos = this->getCurrentPosition();
        switch (i)
        {
        case 1:
            temp_pos.setRow(temp_pos.getRow() - 1);
            break;
        case 2:
            temp_pos.setCol(temp_pos.getCol() + 1);
            break;
        case 3:
            temp_pos.setRow(temp_pos.getRow() + 1);
            break;
        case 4:
            temp_pos.setCol(temp_pos.getCol() - 1);
            break;
        default:
            break;
        }
        if (map->isValid(temp_pos,this)){
            if (ManhattanDistance(Sherlock_pos, temp_pos)
                > maxDistance)
            {
                maxDistance =   ManhattanDistance(Sherlock_pos, next_pos);
                next_pos = temp_pos;
            }
        
        }
    }
    return next_pos;
}
Position RobotW::getNextPosition()
{

    int maxDistance = -1;
    Position Watson_pos = watson->getCurrentPosition();
    Position next_pos = Position::npos;
    for (int i = 1; i <= 4; i++){
        Position temp_pos = this->getCurrentPosition();
        switch (i)
        {
        case 1:
            temp_pos.setRow(temp_pos.getRow() - 1);
            break;
        case 2:
            temp_pos.setCol(temp_pos.getCol() + 1);
            break;
        case 3:
            temp_pos.setRow(temp_pos.getRow() + 1);
            break;
        case 4:
            temp_pos.setCol(temp_pos.getCol() - 1);
            break;
        default:
            break;
        }
        if (map->isValid(temp_pos,this)){
            if (ManhattanDistance(Watson_pos, temp_pos)
                > maxDistance)
            {
                maxDistance =   ManhattanDistance(Watson_pos, next_pos);
                next_pos = temp_pos;
            }
        
        }
    }
    return next_pos;
}
Position RobotSW::getNextPosition()
{
    int maxDistance = -1;
    Position Sherlock_pos = sherlock->getCurrentPosition();
    Position Watson_pos = watson->getCurrentPosition();
    Position next_pos = Position::npos;
    for (int i = 1; i <= 4; i++){
        Position temp_pos = this->getCurrentPosition();
        switch (i)
        {
        case 1:
            temp_pos.setRow(temp_pos.getRow() - 2);
            break;
        case 2:
            temp_pos.setCol(temp_pos.getCol() + 2);
            break;
        case 3:
            temp_pos.setRow(temp_pos.getRow() + 2);
            break;
        case 4:
            temp_pos.setCol(temp_pos.getCol() - 2);
            break;
        default:
            break;
        }
        if (map->isValid(temp_pos,this)){
            if (ManhattanDistance(Sherlock_pos, temp_pos)+
                ManhattanDistance(Watson_pos, temp_pos)
                > maxDistance)
            {
                maxDistance =   ManhattanDistance(Sherlock_pos, next_pos)+
                                ManhattanDistance(Watson_pos, next_pos);
                next_pos = temp_pos;
            }
        }
    }
    return next_pos;
}

int RobotSW::getDistance()
{
    Position robot_pos = this->getCurrentPosition();
    Position sherlock_pos = sherlock->getCurrentPosition();
    Position watson_pos = watson->getCurrentPosition();
    return  ManhattanDistance(robot_pos, sherlock_pos)+
            ManhattanDistance(robot_pos, watson_pos);
}
int RobotS::getDistance()
{
    Position robot_pos = this->getCurrentPosition();
    Position sherlock_pos = sherlock->getCurrentPosition();
    return  ManhattanDistance(robot_pos, sherlock_pos);
}
int RobotW::getDistance()
{
    Position robot_pos = this->getCurrentPosition();    
    Position watson_pos = watson->getCurrentPosition();
    return ManhattanDistance(robot_pos, watson_pos);
}
int RobotC::getDistance(Sherlock * sherlock)
{
    Position robot_pos = this->getCurrentPosition();
    Position sherlock_pos = sherlock->getCurrentPosition();
    return  ManhattanDistance(robot_pos, sherlock_pos);
}

int RobotC::getDistance(Watson * watson)
{
    Position robot_pos = this->getCurrentPosition();    
    Position watson_pos = watson->getCurrentPosition();
    return ManhattanDistance(robot_pos, watson_pos);
}

Robot::Robot(  int index,
                const Position & init_pos,
                Map * map,
                RobotType robot_type)
    :MovingObject(index, pos, map), robot_type(robot_type)
{}
RobotC::RobotC(   int index,
                const Position & init_pos,
                Map * map,
                RobotType robot_type,
                Criminal * criminal)
    :Robot(index, pos, map, robot_type), criminal(criminal)
{}
RobotS::RobotS(   int index,
                const Position & init_pos,
                Map * map,
                RobotType robot_type,
                Criminal * criminal,
                Sherlock *sherlock)
    :Robot(index, pos, map, robot_type), criminal(criminal), sherlock(sherlock)
{}
RobotW::RobotW(   int index,
                const Position & init_pos,
                Map * map,
                RobotType robot_type,
                Criminal * criminal,
                Watson *watson)
    :Robot(index, pos, map, robot_type), criminal(criminal), watson(watson)
{}
RobotSW::RobotSW(   int index,
                const Position & init_pos,
                Map * map,
                RobotType robot_type,
                Criminal * criminal,
                Sherlock * sherlock,
                Watson * watson)
    :   Robot(index, pos, map, robot_type), 
        criminal(criminal), 
        sherlock(sherlock), 
        watson(watson)
{}

Character::Character(  int index,
                    const Position & init_pos,
                    Map * map,
                    bool pass,
                    const string & name)
    :MovingObject(index, init_pos, map, name), pass(pass)
{}
////////////////////////////////////////////////
// HCMUT 23:37 12/03/2024
// DONE
////////////////////////////////////////////////