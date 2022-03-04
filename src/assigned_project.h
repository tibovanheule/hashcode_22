#pragma once

#include <vector>
#include "contributor.h"
#include "project.h"

using namespace std;


class AssignedProject
{
  private:
    Project project;
    vector<Contributor> contributors;
  public:
    AssignedProject(){};
    AssignedProject(Project project, vector<Contributor> contributors) : project(project), contributors(contributors) {};

    Project get_project() {return project;};
    vector<Contributor> get_contributors() {return contributors;};
};

