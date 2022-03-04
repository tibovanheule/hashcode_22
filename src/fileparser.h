#pragma once

#include "utils.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>
#include "fileparser.h"
#include "contributor.h"
#include "project.h"

void file_parse(std::string filename, vector<Contributor>* contributors, vector<Project>* projects);