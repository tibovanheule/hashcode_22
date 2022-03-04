#pragma  once

#include "fileparser.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include <algorithm>
#include "contributor.h"
#include "project.h"
#include "assigned_project.h"
#include "output.h"



void write_output(std::string outputname, std::vector<AssignedProject> assignedProjects);