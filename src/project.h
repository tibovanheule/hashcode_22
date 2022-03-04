#pragma once

#include <vector>

// using namespace std;


class Project
{
  private:
    std::string name;
    int duration;
    int score;
    int best_before;
    int num_contributors;
    std::vector<std::string> skill_keys;
    std::vector<int> skill_values;
  public:
    Project(){};
    Project(std::string name, int duration, int score, int best_before, int num_contributers, std::vector<std::string> skill_keys, std::vector<int> skill_values) :
    name(name), duration(duration), score(score), best_before(best_before), num_contributors(num_contributers), skill_keys(skill_keys), skill_values(skill_values) {};

    std::string get_name() {return name;};
    int get_duration() {return duration;};
    int get_score() {return score;};
    int get_best_before() {return best_before;};
    int get_num_contributors() {return num_contributors;};
    std::vector<std::string> get_skill_keys() {return skill_keys;};
    std::vector<int> get_skill_values() {return skill_values;};
};
