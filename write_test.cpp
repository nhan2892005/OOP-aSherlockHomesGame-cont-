#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <map>
#include <unordered_map>
#include <algorithm>
using namespace std;

char moveRule[] = {'U', 'D', 'L', 'R'}; 
void write_test(int i){
    ofstream output_file("Testcase/input/input"+to_string(i));
    srand(time(0));
    int map_size_row = rand() % 500 + 1;
    int map_size_col = rand() % 500 + 1;
    output_file << map_size_row << " " << map_size_col << endl;
    int num_walls = rand() % 2001;
    output_file << num_walls << endl;
    for (int i = 0; i < num_walls; i++){
        int u = rand() % map_size_row;
        int v = rand() % map_size_col;
        output_file << u << " " << v << endl;
    }
    int num_fake_walls = rand() % 2001;
    output_file << num_fake_walls << endl;
    for (int i = 0; i < num_fake_walls; i++){
        int u = rand() % map_size_row;
        int v = rand() % map_size_col;
        output_file << u << " " << v << endl;
    }
    string movingrule = "";
    int size_movingrule = rand() % 101;
    for (int i = 0; i < size_movingrule; i++){
        movingrule += moveRule[rand() % 4];
    }
    int x = rand() % map_size_row;
    int y = rand() % map_size_col;
    output_file << movingrule << endl;
    output_file << x << " " << y << endl;
    int hp = rand() % 1010 - 10;
    int exp = rand() % 1010 - 10;
    output_file << hp << " " << exp << endl;
    output_file.close();
}
void checkMovingObject(int i){
    ofstream output_file("Testcase/input/input"+to_string(i));
    srand(time(0));
    int map_size_row = rand() % 500 + 1;
    int map_size_col = rand() % 500 + 1;
    output_file << map_size_row << " " << map_size_col << endl;
    int num_walls = rand() % 2001;
    output_file << num_walls << endl;
    for (int i = 0; i < num_walls; i++){
        int u = rand() % map_size_row;
        int v = rand() % map_size_col;
        output_file << u << " " << v << endl;
    }
    int num_fake_walls = rand() % 2001;
    output_file << num_fake_walls << endl;
    for (int i = 0; i < num_fake_walls; i++){
        int u = rand() % map_size_row;
        int v = rand() % map_size_col;
        output_file << u << " " << v << endl;
    }
    for (int i = 0; i < 3; i++){
        string movingrule = "";
        int size_movingrule = rand() % 101;
        for (int i = 0; i < size_movingrule; i++){
            movingrule += moveRule[rand() % 4];
        }
        int x = rand() % map_size_row;
        int y = rand() % map_size_col;
        output_file << movingrule << endl;
        output_file << x << " " << y << endl;
        int hp = rand() % 1010 - 10;
        int exp = rand() % 1010 - 10;
        output_file << hp << " " << exp << endl;
    }
    output_file.close();
}
void checkConfig(int i){
    unordered_map<string, string> config;
    ofstream output_file("Testcase/input/input"+to_string(i));
    srand(time(0));
    int map_size_row = rand() % 500 + 1;
    int map_size_col = rand() % 500 + 1;
    config["MAP_NUM_ROWS"] = to_string(map_size_row);
    config["MAP_NUM_COLS"] = to_string(map_size_col);
    int num_walls = rand() % 2001;
    config["ARRAY_WALLS"] = "[";
    for (int i = 0; i < num_walls; i++){
        int u = rand() % map_size_row;
        int v = rand() % map_size_col;
        config["ARRAY_WALLS"] += "(" + to_string(u) + "," + to_string(v) + ")";
        if (i != num_walls - 1){
            config["ARRAY_WALLS"] += ";";
        }
    }
    config["ARRAY_WALLS"] += "]";
    int num_fake_walls = rand() % 2001;
    config["ARRAY_FAKE_WALLS"] = "[";
    for (int i = 0; i < num_fake_walls; i++){
        int u = rand() % map_size_row;
        int v = rand() % map_size_col;
        config["ARRAY_FAKE_WALLS"] += "(" + to_string(u) + "," + to_string(v) + ")";
        if (i != num_fake_walls - 1){
            config["ARRAY_FAKE_WALLS"] += ";";
        }
    }
    config["ARRAY_FAKE_WALLS"] += "]";
    string movingrule = "";
    int size_movingrule = rand() % 101;
    for (int i = 0; i < size_movingrule; i++){
        movingrule += moveRule[rand() % 4];
    }
    int x = rand() % map_size_row;
    int y = rand() % map_size_col;
    config["SHERLOCK_MOVING_RULE"] = movingrule;
    config["SHERLOCK_INIT_POS"] = "(" + to_string(x) + "," + to_string(y) + ")";
    int hp = rand() % 1010 - 10;
    int exp = rand() % 1010 - 10;
    config["SHERLOCK_INIT_HP"] = to_string(hp);
    config["SHERLOCK_INIT_EXP"] = to_string(exp);
    string movingrule1 = "";
    int size_movingrule1 = rand() % 101;
    for (int i = 0; i < size_movingrule1; i++){
        movingrule1 += moveRule[rand() % 4];
    }
    int x1 = rand() % map_size_row;
    int y1 = rand() % map_size_col;
    config["WATSON_MOVING_RULE"] = movingrule1;
    config["WATSON_INIT_POS"] = "(" + to_string(x1) + "," + to_string(y1) + ")";
    int hp1 = rand() % 1010 - 10;
    int exp1 = rand() % 1010 - 10;
    config["WATSON_INIT_HP"] = to_string(hp1);
    config["WATSON_INIT_EXP"] = to_string(exp1);
    int x2 = rand() % map_size_row;
    int y2 = rand() % map_size_col;
    config["CRIMINAL_INIT_POS"] = "(" + to_string(x2) + "," + to_string(y2) + ")";
    int num_steps = rand() % 1001;
    config["NUM_STEPS"] = to_string(num_steps);
    vector<string> keys;
    for (auto it = config.begin(); it != config.end(); it++){
        keys.push_back(it->first);
    }
    random_shuffle(keys.begin(), keys.end());
    for (auto key: keys){
        output_file << key << "=" << config[key] << endl;
    }
    output_file.close();
}
int main(){
    for (int i = 1; i <= 90; i++){
        write_test(i);
    }
    for (int i = 91; i <= 240; i++){
        checkMovingObject(i);
    }
    for (int i = 240; i <= 270; i++){
        checkConfig(i);
    }
    return 0;
}