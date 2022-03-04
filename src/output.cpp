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
#include "output.h"



void write_output(std::string outputname, std::vector<AssignedProject> assignedProjects) {

    std::ofstream outfile;
    std::string filename = "./output/" + outputname;
    outfile.open(filename, std::ofstream::out);
    
    int size = assignedProjects.size();

    //Write amount of projects
    outfile << size << "\n";

    for (auto asProject : assignedProjects) {
        std::string projectName = asProject.get_project().get_name();
        
        outfile << projectName << "\n";
        
        std::vector<Contributor> contributors = asProject.get_contributors();

        for (Contributor contributor : contributors) {

            outfile << contributor.get_name() << " ";
        }

        outfile << "\n";
    }

    outfile.close();

}