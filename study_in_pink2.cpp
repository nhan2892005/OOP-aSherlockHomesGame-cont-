#include "study_in_pink2.h"

////////////////////////////////////////////////////////////////////////
// MY ANSWER BEGINS HERE
////////////////////////////////////////////////////////////////////////
void checkValue(int &value, int max_value){
    if (value > max_value) value = max_value;
    if (value < 0) value = 0;
}

int ManhattanDistance(const Position &pos1, const Position &pos2){
    return abs(pos1.getRow() - pos2.getRow()) + abs(pos1.getCol() - pos2.getCol());
}

int sumOfNum(int num){
    int sum = 0;
    while (num > 0){
        sum += num % 10;
        num /= 10;
    }
    if (sum > 9){
        return sumOfNum(sum);
    }
    return sum;
}
// global function

MapElement::MapElement(ElementType in_type) 
    : type(in_type) {}
Path::Path() 
    : MapElement(ElementType::PATH) {}
Wall::Wall()
    : MapElement(ElementType::WALL) {}
FakeWall::FakeWall(int in_req_exp)
    : MapElement(ElementType::FAKE_WALL), req_exp(in_req_exp) {}
MapElement::~MapElement(){}
Path::~Path(){}
Wall::~Wall(){}
FakeWall::~FakeWall(){}

ElementType MapElement::getType() const 
{
    return type;
}

int FakeWall::getReqExp() const 
{
    return req_exp;
}
/////////////////////////////////////////////////
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
    for (int i = 0; i < num_rows; i++){
        map[i] = new MapElement*[num_cols];
    }

    //Create Path at all positions
    for (int row = 0; row < num_rows; row++){
        for (int col = 0; col < num_cols; col++){
            map[row][col] = new Path();
        }
    }

    //Change Path -> Wall at the given positions
    for (int i = 0; i < num_walls; i++){
        int row = array_walls[i].getRow();
        int col = array_walls[i].getCol();
        delete map[row][col];
        map[row][col] = new Wall();
    }

    //Change Path -> FakeWall at the given positions
    for (int i = 0; i < num_fake_walls; i++){
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
        if (map[i] != nullptr)
            delete[] map[i];
    }
    if (map != nullptr)
        delete[] map;
}

bool Map::isValid(const Position &pos, MovingObject *mv_obj) const
{
    //Out of Map
    if (pos.getRow() < 0 || pos.getRow() >= num_rows || 
        pos.getCol() < 0 || pos.getCol() >= num_cols )
        return false;

    //Meet Fake Wall
    if (map[pos.getRow()][pos.getCol()]->getType() == ElementType::FAKE_WALL)
    {
        //Waston need have enough exp to pass
        if (mv_obj->getName() == "Watson")
        {
            Watson * w = (Watson*)mv_obj;
            FakeWall * fake = (FakeWall*)map[pos.getRow()][pos.getCol()];
            if(w->getEXP() <= fake->getReqExp())
                return false;
        }
    }

    //Meet Wall
    if (map[pos.getRow()][pos.getCol()]->getType() == ElementType::WALL)
        return false;
    return true;
}

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

bool Position::isEqual(int in_r, int in_c) const
{ 
    return (r == in_r && c == in_c); 
}

bool Position::isEqual(Position pos)
{ 
    return (r == pos.getRow() && c == pos.getCol()); 
}
                            
MovingObject::MovingObject( int index, 
                            const Position pos, 
                            Map *map, 
                            const string &name)
    : index(index), pos(pos), map(map), name(name) {}

MovingObject::~MovingObject() {}

string MovingObject::getName() const
{ 
    return name; 
}

Position MovingObject::getCurrentPosition() const
{ 
    return pos; 
}

Character::Character(   int index,
                        const Position & init_pos,
                        Map * map,
                        bool pass,
                        const string & name)
    :MovingObject(index, init_pos, map, name), pass(pass){}
Character::~Character(){}

void Character::catchCriminal(Position Criminal_pos)
{ 
    this->pos = Criminal_pos; 
}

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
    sherlock_bag = new SherlockBag(this);
}

Position Sherlock::getNextPosition()
{
    if (moving_rule.empty()){
        return Position::npos;
    }
    Position next_pos = getCurrentPosition();
    if (step == moving_rule.size()) step = 0;
    char next_move = moving_rule[step++];
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
    if (map->isValid(next_pos, this)){
        return next_pos;
    }
    return Position::npos;
}

void Sherlock::move()
{
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos)){
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
    watson_bag = new WatsonBag(this);
}

Position Watson::getNextPosition()
{
    if (moving_rule.empty()){
        return Position::npos;
    }
    Position next_pos = getCurrentPosition();
    if (step == moving_rule.size()) step = 0;
    char next_move = moving_rule[step++];
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
    if (map->isValid(next_pos, this)){
        return next_pos;
    }
    return Position::npos;
}

void Watson::move()
{
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos)){
        pos = next_pos;
    }
}

string Watson::str() const
{
    return  "Watson[index=" + to_string(index) + 
            ";pos=" + pos.str() + 
            ";moving_rule=" + moving_rule + "]";
}

Watson::~Watson()
{ 
    return;
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
                            
Criminal::Criminal( int index , 
                    const Position & init_pos , 
                    Map * map , Sherlock * sherlock , 
                    Watson * watson)
    :MovingObject(index,init_pos,map,"Criminal"),
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
                next_pos = temp_pos;
                maxDistance = ManhattanDistance(Sherlock_pos, next_pos)+
                              ManhattanDistance(Waston_pos, next_pos);
            }
        
        }
    }
    return next_pos;
}

void Criminal::move()
{
    OldStep = this->pos;
    Position next_pos = getNextPosition();
    if (!next_pos.isEqual(Position::npos))
    {
        this->step++;
        pos = next_pos;
    }
}
Criminal::~Criminal(){
    return;
}

ArrayMovingObject::ArrayMovingObject(int capacity)
:capacity(capacity),count(0)
{
    arr_mv_objs = new MovingObject*[capacity];
}
ArrayMovingObject::~ArrayMovingObject()
{
    if (arr_mv_objs)
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
        result += arr_mv_objs[i]->str();
        if (i < count - 1){
            result += ";";
        }
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
    if (arr_walls != nullptr)
        delete[] arr_walls;
    if (arr_fake_walls != nullptr)
        delete[] arr_fake_walls;
}
void Configuration::init_pos(Position &mv_obj_pos, string line){
    mv_obj_pos = Position(line.substr(line.find("("), 
                    line.find(")") - line.find("(") + 1));
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
        arr[numArr++] = Position(temp.substr(temp.find("(", pos), 
                        temp.find(")", pos) - temp.find("(", pos) + 1));
        pos = temp.find(")", pos) + 1;
    }
}
string Configuration::str() const
{
    string result = "Configuration[\n";
    result += "MAP_NUM_ROWS=" + to_string(map_num_rows) + "\n";
    result += "MAP_NUM_COLS=" + to_string(map_num_cols) + "\n";
    result += "MAX_NUM_MOVING_OBJECTS=" + to_string(max_num_moving_objects) + "\n";
    result += "NUM_WALLS=" + to_string(num_walls) + "\n";
    result += "ARRAY_WALLS=[";
    for (int i = 0; i < num_walls; i++){
        result += "(" + to_string(arr_walls[i].getRow()) + "," + to_string(arr_walls[i].getCol()) + ")";
        if (i != num_walls - 1){
            result += ";";
        }
    }
    result += "]\n";
    result += "NUM_FAKE_WALLS=" + to_string(num_fake_walls) + "\n";
    result += "ARRAY_FAKE_WALLS=[";
    for (int i = 0; i < num_fake_walls; i++){
        result += "(" + to_string(arr_fake_walls[i].getRow()) + "," + to_string(arr_fake_walls[i].getCol()) + ")";
        if (i != num_fake_walls - 1){
            result += ";";
        }
    }
    result += "]\n";
    result += "SHERLOCK_MOVING_RULE=" + sherlock_moving_rule + "\n";
    result += "SHERLOCK_INIT_POS=(" + to_string(sherlock_init_pos.getRow()) + "," + to_string(sherlock_init_pos.getCol()) + ")\n";
    result += "SHERLOCK_INIT_HP=" + to_string(sherlock_init_hp) + "\n";
    result += "SHERLOCK_INIT_EXP=" + to_string(sherlock_init_exp) + "\n";
    result += "WATSON_MOVING_RULE=" + watson_moving_rule + "\n";
    result += "WATSON_INIT_POS=(" + to_string(watson_init_pos.getRow()) + "," + to_string(watson_init_pos.getCol()) + ")\n";
    result += "WATSON_INIT_HP=" + to_string(watson_init_hp) + "\n";
    result += "WATSON_INIT_EXP=" + to_string(watson_init_exp) + "\n";
    result += "CRIMINAL_INIT_POS=(" + to_string(criminal_init_pos.getRow()) + "," + to_string(criminal_init_pos.getCol()) + ")\n";
    result += "NUM_STEPS=" + to_string(num_steps) + "\n";
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
    sherlock_bag = sherlock->sherlock_bag;
    watson_bag = watson->watson_bag;
};
bool StudyPinkProgram::isStop() const
{
    if (sherlock->getCurrentPosition().isEqual(criminal->getCurrentPosition().getRow())
      ||watson->getCurrentPosition().isEqual(criminal->getCurrentPosition())
      ||sherlock->getHP() == 0 || watson->getHP() == 0)
    {
        return true;
    }
    return false;
}
int ArrayMovingObject::getCount()
{
    return count;
}
MovingObject * ArrayMovingObject::get(int i)
{
    if (i >= 0 && i < count)
        return arr_mv_objs[i];
    return nullptr;
}
void StudyPinkProgram::exchangeCard(){
    if (sherlock_bag->ItemExist(PASSING_CARD) && watson_bag->ItemExist(EXCEMPTION_CARD)){
        while (true){
            PassingCard * passing = (PassingCard*) sherlock_bag->get(PASSING_CARD);
            if (passing != nullptr){
                watson_bag->insert(passing);
            }else{
                break;
            }
        }
        while (true){
            ExcemptionCard * excemption = (ExcemptionCard*) watson_bag->get(EXCEMPTION_CARD);
            if (excemption != nullptr){
                sherlock_bag->insert(excemption);
            }else{
                break;
            }
        }
    }
}
int MovingObject::getStep() const {
    return step;
}
void StudyPinkProgram::run(bool verbose){
    int step = config->getNumStep();
    int numMovingObjects = arr_mv_objs->getCount() - 1;
    for (int istep = 1; istep <= step; ++istep) {
        for (int i = 0; i < numMovingObjects; ++i) {
            MovingObject * mv_oj = arr_mv_objs->get(i);
            mv_oj->move();
        }
        //Sherlock meet Watson
        if (sherlock->getCurrentPosition().isEqual(watson->getCurrentPosition())){
            exchangeCard();
        }
        //Sherlock & Watson meet Criminal
        for (int i = 3; i < numMovingObjects; ++i){
            //get Robot
            MovingObject * mv_oj = arr_mv_objs->get(i);
            if (mv_oj == nullptr){
                break;
            }
            //Sherlock meet robot
            if (sherlock->getCurrentPosition().isEqual(arr_mv_objs->get(i)->getCurrentPosition())){
                sherlock->meetRobot(arr_mv_objs->get(i));
            }

            //Watson meet robot
            if (watson->getCurrentPosition().isEqual(arr_mv_objs->get(i)->getCurrentPosition())){
                watson->meetRobot(arr_mv_objs->get(i));
            }
        }
        //Check and add Robot
        if (!arr_mv_objs->isFull()){
            int num_move_of_criminal = criminal->getStep();
            if (num_move_of_criminal == 3){
                RobotC * robot = new RobotC(arr_mv_objs->getCount(), criminal->OldStep, map, criminal);
                arr_mv_objs->add(robot);
            }
            else if (num_move_of_criminal % 3 == 0){
                Position Robot_pos = criminal->OldStep;
                Position Sherlock_pos = sherlock->getCurrentPosition();
                Position Watson_pos = watson->getCurrentPosition();
                int s_to_r = ManhattanDistance(Sherlock_pos, Robot_pos); 
                int w_to_r = ManhattanDistance(Watson_pos, Robot_pos);
                if (s_to_r < w_to_r){
                    RobotS * robot = new RobotS(arr_mv_objs->getCount(), criminal->OldStep, map, criminal, sherlock);
                    arr_mv_objs->add(robot);
                } 
                else if (s_to_r > w_to_r){
                    RobotW * robot = new RobotW(arr_mv_objs->getCount(), criminal->OldStep, map, criminal, watson);
                    arr_mv_objs->add(robot);
                }
                else if (s_to_r == w_to_r){
                    RobotSW * robot = new RobotSW(arr_mv_objs->getCount(), criminal->OldStep, map, criminal, sherlock, watson);
                    arr_mv_objs->add(robot);
                }
            }
        }
        if (isStop()) {
            printResult();
            break;
        }
        //Criminal create Robot
            if (!arr_mv_objs->isFull()){
                int num_move_of_criminal = criminal->getStep();
                if (num_move_of_criminal == 3){
                    RobotC * robot = new RobotC(arr_mv_objs->getCount(), criminal->OldStep, map, criminal);
                    arr_mv_objs->add(robot);
                }
                else if (num_move_of_criminal % 3 == 0){
                    Position Robot_pos = criminal->OldStep;
                    Position Sherlock_pos = sherlock->getCurrentPosition();
                    Position Watson_pos = watson->getCurrentPosition();
                    int s_to_r = ManhattanDistance(Sherlock_pos, Robot_pos); 
                    int w_to_r = ManhattanDistance(Watson_pos, Robot_pos);
                    if (s_to_r < w_to_r){
                        RobotS * robot = new RobotS(arr_mv_objs->getCount(), criminal->OldStep, map, criminal, sherlock);
                        arr_mv_objs->add(robot);
                    } 
                    else if (s_to_r > w_to_r){
                        RobotW * robot = new RobotW(arr_mv_objs->getCount(), criminal->OldStep, map, criminal, watson);
                        arr_mv_objs->add(robot);
                    }
                    else if (s_to_r == w_to_r){
                        RobotSW * robot = new RobotSW(arr_mv_objs->getCount(), criminal->OldStep, map, criminal, sherlock, watson);
                        arr_mv_objs->add(robot);
                    }
                }
            }
            if (verbose) {
                printStep(istep);
            }
    }
    
    
        
        
        // if (isStop()) {
        //     printStep(istep);
        //     break;
        // }
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
void Sherlock::meetRobot(MovingObject * robot){
    Robot * rb = (Robot*)robot;
    ExcemptionCard * excemption = (ExcemptionCard*) this->sherlock_bag->get(EXCEMPTION_CARD);
    if (excemption != nullptr){
        excemption->use(this, rb);
    }else{
        switch (rb->getType())
        {
            case S:
                if (this->getEXP() > 400){
                    sherlock_bag->insert(rb->item);
                }else
                {
                    changeEXP(-getEXP() * 0.1);
                }
                break;
            case W:
                sherlock_bag->insert(rb->item);
                return;
                break;
            case C:
                if (this->getEXP() > 500){
                    this->catchCriminal(Criminal_pos);
                }else
                {
                    sherlock_bag->insert(rb->item);
                }
                break;
            case SW:
                if (getEXP() > 300 && getHP() > 335){
                    sherlock_bag->insert(rb->item);
                }else{
                    changeHP(-getHP() * 0.15);
                    changeEXP(-getEXP() * 0.15);
                }
                break;
            default:
                break;
        }
    }
    //Challenge with Robot
    
    BaseItem * Item = sherlock_bag->get();
    if (Item != nullptr){
        Item->use(this, nullptr);
        delete Item;
    }
    
}
void Watson::meetRobot(MovingObject * robot){
    Robot * rb = (Robot*)robot;
    PassingCard * passing = (PassingCard*) this->watson_bag->get(PASSING_CARD);
    if (passing != nullptr){
        passing->use(this, rb);
    }else{
        switch (rb->getType())
        {
            case S:
                return;
                break;
            case W:
                if (this->getHP() > 350){
                    watson_bag->insert(rb->item);
                }else
                {
                    changeHP(-getHP() * 0.05);
                }
                break;
            case C:
                watson_bag->insert(rb->item);
                break;
            case SW:
                if (getEXP() > 600 && getHP() > 165){
                    watson_bag->insert(rb->item);
                }else{
                    changeHP(-getHP() * 0.15);
                    changeEXP(-getEXP() * 0.15);
                }
                break;
            default:
                break;
        }
    }
    //Challenge with Robot
    
    BaseItem * Item = watson_bag->get();
    if (Item != nullptr){
        Item->use(this, nullptr);
        delete Item;
    }
}
string Robot::str() const
{
    return "";
}
string RobotC::str()
{
    string s =  "Robot[pos=" + pos.str() + 
                ";type=" + 
                name + 
                ";dist="
                +"]";
    return s;
}
string RobotSW::str()
{
    string s =  "Robot[pos=" + pos.str() + 
                ";type=" + 
                name + 
                ";dist=" + 
                to_string(getDistance())
                +"]";
    return s;
}
string RobotS::str()
{
    string s =  "Robot[pos=" + pos.str() + 
                ";type=" + 
                name + 
                ";dist=" + 
                to_string(getDistance())
                +"]";
    return s;
}
string RobotW::str()
{
    string s =  "Robot[pos=" + pos.str() + 
                ";type=" + 
                name + 
                ";dist=" + 
                to_string(getDistance())
                +"]";
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
    return criminal->OldStep;
}
Position RobotS::getNextPosition()
{
    int minDistance = 1e9;
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
                < minDistance)
            {
                next_pos = temp_pos;
                minDistance =   ManhattanDistance(Sherlock_pos, next_pos);
            }
        
        }
    }
    return next_pos;
}
Position RobotW::getNextPosition()
{

    int minDistance = 1e9;
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
                < minDistance)
            {
                next_pos = temp_pos;
                minDistance = ManhattanDistance(Watson_pos, next_pos);
            }
        
        }
    }
    return next_pos;
}
Position RobotSW::getNextPosition()
{
    int minDistance = 1e9;
    Position Sherlock_pos = sherlock->getCurrentPosition();
    Position Watson_pos = watson->getCurrentPosition();
    Position next_pos = Position::npos;
    for (int i = 1; i <= 8; i++){
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
        case 5:
            temp_pos.setRow(temp_pos.getRow() - 1);
            temp_pos.setCol(temp_pos.getCol() - 1);
            break;
        case 6:
            temp_pos.setRow(temp_pos.getRow() + 1);
            temp_pos.setCol(temp_pos.getCol() + 1);
            break;
        case 7:
            temp_pos.setRow(temp_pos.getRow() + 1);
            temp_pos.setCol(temp_pos.getCol() - 1);
            break;
        case 8:
            temp_pos.setRow(temp_pos.getRow() - 1);
            temp_pos.setCol(temp_pos.getCol() + 1);
            break;
        default:
            break;
        }
        if (map->isValid(temp_pos,this)){
            if (ManhattanDistance(Sherlock_pos, temp_pos)+
                ManhattanDistance(Watson_pos, temp_pos)
                < minDistance)
            {
                next_pos = temp_pos;
                minDistance =   ManhattanDistance(Sherlock_pos, next_pos)+
                                ManhattanDistance(Watson_pos, next_pos);
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
                const Position &init_pos,
                Map * map,
                RobotType robot_type)
    :MovingObject(index, init_pos, map), robot_type(robot_type)
{
    Position pos_create_item = pos;
    int p = pos_create_item.getRow() * pos_create_item.getCol();
    int s = sumOfNum(p);
    if (s >= 0 && s <= 1){
        item = new MagicBook();
    }
    else if (s >= 2 && s <= 3){
        item = new EnergyDrink();
    }
    else if (s >= 4 && s <= 5){
        item = new FirstAid();
    }
    else if (s >= 6 && s <= 7){
        item = new ExcemptionCard();
    }
    else if (s >= 8 && s <= 9){
        PassingCard * temp = new PassingCard();
        temp->setType((pos_create_item.getRow() * 11 + pos_create_item.getCol()) % 4);
        item = temp;
        delete temp;
    }
}
RobotC::RobotC( int index,
                const Position & init_pos,
                Map * map,
                Criminal * criminal)
    :Robot(index, init_pos, map, C), criminal(criminal)
{}
RobotS::RobotS(   int index,
                const Position & init_pos,
                Map * map,
                Criminal * criminal,
                Sherlock *sherlock)
    :Robot(index, init_pos, map, S), criminal(criminal), sherlock(sherlock)
{}
RobotW::RobotW(   int index,
                const Position & init_pos,
                Map * map,
                Criminal * criminal,
                Watson *watson)
    :Robot(index, init_pos, map, W), criminal(criminal), watson(watson)
{}
RobotSW::RobotSW(   int index,
                const Position & init_pos,
                Map * map,
                Criminal * criminal,
                Sherlock * sherlock,
                Watson * watson)
    :   Robot(index, init_pos, map, SW), 
        criminal(criminal), 
        sherlock(sherlock), 
        watson(watson)
{}


void Sherlock::changeEXP(double change)
{
    if (abs(change - int(change)) > 1e-9) {
        change = ceil(change);
    }
    exp += (int)change;
    checkValue(exp, max_exp);
}
void Sherlock::changeHP(double change)
{
    if (abs(change - int(change)) > 1e-9) {
        change = ceil(change);
    }
    hp += (int)change;
    checkValue(exp, max_hp);
}
void Watson::changeEXP(double change)
{
    if (abs(change - int(change)) > 1e-9) {
        change = ceil(change);
    }
    exp += (int)change;
    checkValue(exp, max_exp);
}
void Watson::changeHP(double change)
{
    if (abs(change - int(change)) > 1e-9) {
        change = ceil(change);
    }
    hp += (int)change;
    checkValue(exp, max_hp);
}
BaseItem::BaseItem(ItemType type)
    :type(type)
{}
BaseItem::~BaseItem()
{
    return;
}
MagicBook::MagicBook()
    :BaseItem(ItemType::MAGIC_BOOK)
{}
bool MagicBook::canUse(Character * obj, Robot * robot) 
{
    int exp = obj->getEXP();
    if (exp <= 350) return true;
    else return false;
}
void MagicBook::use(Character * const &obj, Robot * robot) 
{
    obj->changeEXP(obj->getEXP()*0.25);
}

EnergyDrink::EnergyDrink()
    :BaseItem(ItemType::ENERGY_DRINK)
{}
bool EnergyDrink::canUse(Character * obj, Robot * robot)
{
    int hp = obj->getHP();
    if (hp <= 100) return true;
    else return false;
}
void EnergyDrink::use(Character * const &obj, Robot * robot)
{
    obj->changeHP(obj->getHP()*0.20);
}

FirstAid::FirstAid()
    :BaseItem(ItemType::FIRST_AID)
{}
bool FirstAid::canUse(Character * obj, Robot * robot)
{
    int hp = obj->getHP();
    int exp = obj->getEXP();
    if (hp <= 100 || exp <= 350) return true;
    else return false;
}
void FirstAid::use(Character * const &obj, Robot * robot)
{
    obj->changeHP(obj->getHP()*0.50);
}

ExcemptionCard::ExcemptionCard()
    :BaseItem(ItemType::EXCEMPTION_CARD)
{}
bool ExcemptionCard::canUse(Character * obj, Robot * robot)
{
    if(obj->getName() != "Sherlock") return false;
    int hp = obj->getHP();
    if (hp % 2 == 1) return true;
    else return false;
}
void ExcemptionCard::use(Character * const &obj, Robot * robot)
{
    switch (robot->getType())
    {
        case S:
            if (obj->getEXP() < 400){
                return;
            }
            break;
        case SW:
            if (obj->getEXP() < 300 || obj->getHP() < 335){
                return;
            }
            break;
        default:
            break;
    }
}
RobotType Robot::getType()
{
    return robot_type;
}
PassingCard::PassingCard()
    :BaseItem(ItemType::PASSING_CARD)
{}
bool PassingCard::canUse(Character * obj, Robot * robot)
{
    if(obj->getName() != "Watson") return false;
    int hp = obj->getHP();
    if (hp % 2 == 0) return true;
    else return false;
}
void PassingCard::use(Character * const &obj, Robot * robot)
{
    if (challenge == "all") return;
    if ( (challenge == " RobotC" && robot->getType() != C)
       ||(challenge == " RobotS" && robot->getType() != S)
       ||(challenge == " RobotW" && robot->getType() != W)
       ||(challenge == " RobotSW" && robot->getType() != SW))
    {
        obj->changeHP(-50);
    }
}
void PassingCard::setType(int t)
{
    switch (t)
    {
    case 0:
        challenge = "RobotS";
        break;
    case 1:
        challenge = "RobotC";
        break;
    case 2:
        challenge = "RobotSW";
        break;
    case 3:
        challenge = "all";
        break;
    default:
        break;
    }
}
void BaseItem::use(Character * const &obj, Robot * robot){
    return;
}
ItemType BaseItem::getType()
{
    return type;
}
BaseBag::BaseBag()
    : item(nullptr), next(nullptr), head(nullptr), tail(nullptr)
{}
BaseBag::~BaseBag()
{
    if (head != nullptr)
    {
        BaseBag * temp = head;
        while (temp != nullptr)
        {
            head = head->next;
            delete temp;
            temp = head;
        }
    }
}

bool BaseBag::insert(BaseItem * item)
{
    //insert item to the head of list
    if (item == nullptr) return false;
    if (count == capacity) return false;
    if (head == nullptr)
    {
        head = new BaseBag;
        head->item = item;
        head->obj = obj;
        tail = head;
        count = 1;
        return true;
    }
    else
    {
        BaseBag * temp = new BaseBag;
        temp->item = item;
        temp->obj = obj;
        temp->next = head;
        head = temp;
        ++count;
        return true;
    }
    return false;
}

BaseItem* BaseBag::get(ItemType itemType)
{
    if (!head) return nullptr;
    BaseBag * temp = head;
    while (temp != nullptr)
    {
        if (temp->item->getType() == itemType)
        {
            //delete item from list
            //swap it with first item and delete first item
            BaseItem * temp_item = temp->item;
            temp->item = head->item;
            head->item = nullptr;
            head = head->next;
            count--;
            return temp_item;
        }
        temp = temp->next;
    }
    return nullptr;
}

BaseItem* BaseBag::get()
{
    if (head == nullptr) return nullptr;
    BaseBag * temp = head;
    while (temp != nullptr)
    {
        if (temp->item->canUse(obj, nullptr))
        {
            //delete item from list
            //swap it with first item and delete first item
            BaseItem * temp_item = temp->item;
            temp->item = head->item;
            head->item = nullptr;
            head = head->next;
            count--;
            return temp_item;
        }
        temp = temp->next;
    }
    delete temp;
    return nullptr;
}

bool BaseBag::ItemExist(ItemType itemType)
{
    if (head == nullptr) return 0;
    BaseBag * temp = head;
    while (temp != nullptr)
    {
        if (temp->item->getType() == itemType)
        {
            return 1;
        }
        temp = temp->next;
    }
    delete temp;
    return 0;
}

string BaseBag::str() const
{
    if (head == nullptr) return "Bag[count=0]";
    string temp = "Bag[count=" + to_string(count) + ";";
    BaseBag * temp_bag = head;
    while (temp_bag->next != nullptr)
    {
        temp += BaseItem::getName(temp_bag->item->getType()) + ",";
        temp_bag = temp_bag->next;
    }
    temp += BaseItem::getName(temp_bag->item->getType()) + "]";
    return temp;
}
SherlockBag::SherlockBag(Sherlock * sherlock)
    :BaseBag()
{
    this->obj = sherlock;
    this->capacity = 13;
}
WatsonBag :: WatsonBag(Watson * watson)
    :BaseBag()
{
    this->obj = watson;
    this->capacity = 15;
}
////////////////////////////////////////////////
// HCMUT 23:37 12/03/2024
// DONE
////////////////////////////////////////////////