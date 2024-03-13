/*
* Ho Chi Minh City University of Technology
* Faculty of Computer Science and Engineering
* Submit code for Assignment 1
* Programming Fundamentals Spring 2024
* Author: Nguyen Phuc Nhan
* Student ID: 2312438
* Date: 10.03.2024
*/
#include "study_in_pink2.h"
#include <vector>
using namespace std;
void g_satc_02() { // global
    string test_input_file = "sa_tc_02_config";
    cout << "----- Sample Testcase 02 -----" << endl;
    StudyPinkProgram * program = new StudyPinkProgram(test_input_file);
    program->run(1);
    delete program;
}

class TestStudyInPink {
public:
    TestStudyInPink() = default;
    private:
        int map_size_row, map_size_col;
        int num_walls;
        Position * arr_walls;
        Position * arr_fake_walls;
        int max_num_moving_objects;
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
        Map * map;
    public:
    void checkSherlock(string & file_path){
        ifstream input_file(file_path);
        input_file >> map_size_row >> map_size_col;
        input_file >> num_walls;
        arr_walls = new Position[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_walls[i] = Position(u,v);
        }
        int num_fake_walls;
        input_file >> num_fake_walls;
        arr_fake_walls = new Position[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_fake_walls[i] = Position(u,v);
        }

        map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        
        string movingrule;
        int hp, exp;
        int x,y;
        input_file >> movingrule;
        input_file >> x >> y;
        input_file >> hp >> exp;
        Sherlock * sherlock = new Sherlock(1, movingrule, Position(x,y), map, hp, exp);
        cout << sherlock->str() << endl;
        delete sherlock;
        delete map;
        delete[] arr_walls;
        delete[] arr_fake_walls;
    }

    void checkWatson(string & file_path){
        ifstream input_file(file_path);
        input_file >> map_size_row >> map_size_col;
        input_file >> num_walls;
        arr_walls = new Position[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_walls[i] = Position(u,v);
        }
        int num_fake_walls;
        input_file >> num_fake_walls;
        arr_fake_walls = new Position[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_fake_walls[i] = Position(u,v);
        }

        map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        
        string movingrule;
        int hp, exp;
        int x,y;
        input_file >> movingrule;
        input_file >> x >> y;
        input_file >> hp >> exp;
        Watson * watson = new Watson(1, movingrule, Position(x,y), map, hp, exp);
        cout << watson->str() << endl;
        delete watson;
        delete map;
        delete[] arr_walls;
        delete[] arr_fake_walls;
    }

    void checkCriminal(string & file_path){
        ifstream input_file(file_path);
        input_file >> map_size_row >> map_size_col;
        input_file >> num_walls;
        arr_walls = new Position[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_walls[i] = Position(u,v);
        }
        int num_fake_walls;
        input_file >> num_fake_walls;
        arr_fake_walls = new Position[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_fake_walls[i] = Position(u,v);
        }

        map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        int x,y;
        input_file >> x >> y;
        Criminal * criminal = new Criminal(0, Position(x,y), map, nullptr, nullptr);
        cout << criminal->str() << endl;
        delete criminal;
        delete map;
        delete[] arr_walls;
        delete[] arr_fake_walls;
    }

    void checkMovingObject(string file_path){
        ifstream input_file(file_path);
        ofstream output_file(file_path + "_output");
        input_file >> map_size_row >> map_size_col;
        input_file >> num_walls;
        arr_walls = new Position[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_walls[i] = Position(u,v);
        }
        int num_fake_walls;
        input_file >> num_fake_walls;
        arr_fake_walls = new Position[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_fake_walls[i] = Position(u,v);
        }

        map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        
        Criminal * criminal;
        Sherlock * sherlock;
        Watson * watson;
        for (int i = 0; i < 3; i++){
            if (i == 0){
                int x,y;
                input_file >> x >> y;
                criminal = new Criminal(0, Position(x,y), map, nullptr, nullptr);
            }
            else if (i == 1){
                string movingrule;
                int hp, exp;
                int x,y;
                input_file >> movingrule;
                input_file >> x >> y;
                input_file >> hp >> exp;
                sherlock = new Sherlock(1, movingrule, Position(x,y), map, hp, exp);
            }
            else if (i == 2){
                string movingrule;
                int hp, exp;
                int x,y;
                input_file >> movingrule;
                input_file >> x >> y;
                input_file >> hp >> exp;
                watson = new Watson(1, movingrule, Position(x,y), map, hp, exp);
            }
        }
        output_file << "* Criminal make a move *" << endl;
        criminal->move();
        output_file << criminal->str() << endl;

        output_file << "* Sherlock make a move *" << endl;
        sherlock->move();
        output_file << sherlock->str() << endl;

        output_file << "* Watson make a move *" << endl;
        watson->move();
        output_file << watson->str() << endl;
        delete criminal;
        delete sherlock;    
        delete watson;
    }
    void checkarrayMovingObject(string file_path){
        ifstream input_file(file_path);
        ofstream output_file(file_path + "_output");
        input_file >> map_size_row >> map_size_col;
        input_file >> num_walls;
        arr_walls = new Position[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_walls[i] = Position(u,v);
        }
        int num_fake_walls;
        input_file >> num_fake_walls;
        arr_fake_walls = new Position[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_fake_walls[i] = Position(u,v);
        }

        map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        
        Criminal * criminal;
        Sherlock * sherlock;
        Watson * watson;
        ArrayMovingObject * arr_mv_objs = new ArrayMovingObject(10);
        for (int i = 0; i < 3; i++){
            if (i == 0){
                int x,y;
                input_file >> x >> y;
                criminal = new Criminal(0, Position(x,y), map, nullptr, nullptr);
                arr_mv_objs->add(criminal);
            }
            else if (i == 1){
                string movingrule;
                int hp, exp;
                int x,y;
                input_file >> movingrule;
                input_file >> x >> y;
                input_file >> hp >> exp;
                sherlock = new Sherlock(1, movingrule, Position(x,y), map, hp, exp);
                arr_mv_objs->add(sherlock);
            }
            else if (i == 2){
                string movingrule;
                int hp, exp;
                int x,y;
                input_file >> movingrule;
                input_file >> x >> y;
                input_file >> hp >> exp;
                watson = new Watson(1, movingrule, Position(x,y), map, hp, exp);
                arr_mv_objs->add(watson);
            }
        }
        output_file << arr_mv_objs->str() << endl;
        delete arr_mv_objs;
        delete criminal;
        delete sherlock;
        delete watson;
        delete map;
        delete[] arr_walls;
        delete[] arr_fake_walls;
    }

    void checkConfig(string file_path){
        ifstream input_file(file_path);
        ofstream output_file(file_path + "_output");
        Configuration * config = new Configuration(file_path);
        config->str();
        delete config;
    }
    void checkrobotC(string file_path){
       ifstream input_file(file_path);
       ofstream output_file(file_path + "_output");
       input_file >> map_size_row >> map_size_col;
        input_file >> num_walls;
        arr_walls = new Position[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_walls[i] = Position(u,v);
        }
        int num_fake_walls;
        input_file >> num_fake_walls;
        arr_fake_walls = new Position[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_fake_walls[i] = Position(u,v);
        }

        map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        int x,y;
        input_file >> x >> y;
        Criminal * criminal = new Criminal(0, Position(x,y), map, nullptr, nullptr);
        RobotC * robotC = new RobotC(3, Position(x,y), map, C, criminal);
        output_file << robotC->str() << endl;
        delete robotC;
        delete criminal;
        delete map;
        delete[] arr_walls;
        delete[] arr_fake_walls;
   }/*
    void checkrobotS(string file_path){
       ifstream input_file(file_path);
       ofstream output_file(file_path + "_output");
       input_file >> map_size_row >> map_size_col;
        input_file >> num_walls;
        arr_walls = new Position[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_walls[i] = Position(u,v);
        }
        int num_fake_walls;
        input_file >> num_fake_walls;
        arr_fake_walls = new Position[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_fake_walls[i] = Position(u,v);
        }

        map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        int x,y;
        input_file >> x >> y;
        Criminal * criminal = new Criminal(0, Position(x,y), map, nullptr, nullptr);
        //init Sherlock from file
        string movingrule;
        int hp, exp;
        int x1,y1;
        input_file >> movingrule;
        input_file >> x1 >> y1;
        input_file >> hp >> exp;
        Sherlock * sherlock = new Sherlock(1, movingrule, Position(x1,y1), map, hp, exp);
        RobotS * robotS = new RobotS(3, Position(x,y), map, S, criminal, sherlock);
        output_file << robotS->str() << endl;
        delete robotS;
        delete criminal;
        delete sherlock;
        delete map;
        delete[] arr_walls;
        delete[] arr_fake_walls;
    }
    //CHECK robotW, print str()
    void checkrobotW(string file_path){
       ifstream input_file(file_path);
       ofstream output_file(file_path + "_output");
       input_file >> map_size_row >> map_size_col;
        input_file >> num_walls;
        arr_walls = new Position[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_walls[i] = Position(u,v);
        }
        int num_fake_walls;
        input_file >> num_fake_walls;
        arr_fake_walls = new Position[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_fake_walls[i] = Position(u,v);
        }

        map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        int x,y;
        input_file >> x >> y;
        Criminal * criminal = new Criminal(0, Position(x,y), map, nullptr, nullptr);
        //init Watson from file
        string movingrule;
        int hp, exp;
        int x1,y1;
        input_file >> movingrule;
        input_file >> x1 >> y1;
        input_file >> hp >> exp;
        Watson * watson = new Watson(1, movingrule, Position(x1,y1), map, hp, exp);
        RobotW * robotW = new RobotW(3, Position(x,y), map, W, criminal, watson);
        output_file << robotW->str() << endl;
        delete robotW;
        delete criminal;
        delete watson;
        delete map;
        delete[] arr_walls;
        delete[] arr_fake_walls;
    }
    void checkrobotSW(string file_path){
       ifstream input_file(file_path);
       ofstream output_file(file_path + "_output");
       input_file >> map_size_row >> map_size_col;
        input_file >> num_walls;
        arr_walls = new Position[num_walls];
        for (int i = 0; i < num_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_walls[i] = Position(u,v);
        }
        int num_fake_walls;
        input_file >> num_fake_walls;
        arr_fake_walls = new Position[num_fake_walls];
        for (int i = 0; i < num_fake_walls; i++){
            int u, v;
            input_file >> u >> v;
            arr_fake_walls[i] = Position(u,v);
        }

        map = new Map(map_size_row, map_size_col, num_walls, arr_walls, num_fake_walls, arr_fake_walls);
        int x,y;
        input_file >> x >> y;
        Criminal * criminal = new Criminal(0, Position(x,y), map, nullptr, nullptr);
        string movingrule;
        int hp, exp;
        int x1,y1;
        input_file >> movingrule;
        input_file >> x1 >> y1;
        input_file >> hp >> exp;
        Sherlock * sherlock = new Sherlock(1, movingrule, Position(x1,y1), map, hp, exp);
        string movingrule1;
        int hp1, exp1;
        int x2,y2;
        input_file >> movingrule1;
        input_file >> x2 >> y2;
        input_file >> hp1 >> exp1;
        Watson * watson = new Watson(1, movingrule1, Position(x2,y2), map, hp1, exp1);
        RobotSW * robotSW = new RobotSW(3, Position(x,y), map, SW, criminal, sherlock, watson);
        output_file << robotSW->str() << endl;
        delete robotSW;
        delete criminal;
        delete sherlock;
        delete watson;
        delete map;
        delete[] arr_walls;
        delete[] arr_fake_walls;
    }*/
};

int main(int argc, const char * argv[]) {
   // TestStudyInPink::satc_01();
    //TestStudyInPink::satc_02();
    //TestStudyInPink::satc_03();
    return 0;
}