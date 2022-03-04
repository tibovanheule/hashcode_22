#pragma once

#include <map>

using namespace std;

class Contributor
{
  private:
    string name;
    int num_skills;
    map<string, int> skills;
  public:
    Contributor(){};
    Contributor(string name, int num_skills, map<string, int> skills) : name(name), num_skills(num_skills), skills(skills) {};

    string get_name() {return name;};
    int get_num_skills() {return num_skills;};
    map<string, int> get_skills() {return skills;};
};
