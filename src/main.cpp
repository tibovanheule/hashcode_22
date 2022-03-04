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
#include "main.h"

using namespace std;





int test_score_function(std::vector<Contributor> skillset,
                        std::vector<Project> taskset, 
                        std::vector<AssignedProject> assignset) {
    // if anything fails, the solution is invalid and will get score -1
    int fail = -1;
    int score = 0;
    std::map<string, int> contributor_availibility;
    // copy the skills to a map here
    std::map<string, std::map<string, int>> skills;
    for (Contributor c: skillset) {
        skills[c.get_name()] = c.get_skills();
    }
    // for each assigned project do the checks
    for (AssignedProject ass_project : assignset) {
        Project project = ass_project.get_project();
        println("Project name" + project.get_name());
        std::vector<Contributor> contributors = ass_project.get_contributors();
        std::map<string, int> has_mentor;
        for (int i=0; i < project.get_skill_keys().size(); i++) {
            string developer = contributors[i].get_name();
            string skill = project.get_skill_keys()[i];
            int skill_value = project.get_skill_values()[i];
            if (skills[developer][skill] == skill_value - 1) {
                has_mentor[project.get_skill_keys()[i]] = project.get_skill_values()[i];
            } else if (skills[developer][skill] < skill_value - 1) {
                return fail;
            }
        }
        for (auto sk: skills) {
            for (auto ment: has_mentor) {
                if (sk.second.count(ment.first) > 0 && sk.second[ment.first] >= ment.second){
                    has_mentor.erase(ment.first);
                }
            }
        }
        if (has_mentor.size() > 0) {
            return fail;
        }

        // decide start date 
        int startdate = 0;
        for (Contributor c: contributors){
            startdate = std::max(startdate, contributor_availibility[c.get_name()]);
        }
        println("Startdate: " + std::to_string(startdate));

        // update the availibities of the contributors
        int duration = project.get_duration();
        for (Contributor c: contributors){
            contributor_availibility[c.get_name()] = startdate + duration;          
        }

        // calculate score
        int best_before_date = project.get_best_before();
        println("Best_before "+std::to_string(best_before_date));
        int bbd_min_sd = - best_before_date + startdate + duration;
        println("BBD " + std::to_string(bbd_min_sd));
        if (bbd_min_sd <= 0) {
            score += project.get_score();
        } else if (bbd_min_sd < project.get_score()) {
            score += project.get_score() - bbd_min_sd;
        }
        
        // update skills
        for (int i=0; i < project.get_skill_keys().size(); i++) {
            string developer = contributors[i].get_name();
            string skill = project.get_skill_keys()[i];
            int skill_value = project.get_skill_values()[i];
            if (skills[developer][skill] == skill_value - 1 || skills[developer][skill] == skill_value) {
                skills[developer][skill]++;
            }
        }
    }
    return score;
}

void sortProjects(vector<Project> projects){
    sort(projects.begin(), projects.end(), compareProject);
}


int main(int argc, char *argv[]) {

    std::vector<Contributor> skillset;
    std::vector<Project> taskset;
    std::vector<AssignedProject> assignset;


    println("TEST");
    file_parse("./input/a_an_example.in.txt", &skillset, &taskset);

    std::vector contribs = {skillset[1], skillset[0]};
    AssignedProject ass_project = AssignedProject(taskset[1], contribs);
    assignset.push_back(ass_project);
    int score = test_score_function(skillset, taskset, assignset);
    println("The score is: " + std::to_string(score));

    //void write_output(std::string outputname, std::vector<AssignedProject> assignedProjects)
    std::string testname = "test";
    write_output(testname, assignset);
    
    return 0;
}

// ANDERE TODO's : contributions functie testen, project sort testen, mentorship implementeren ....

vector<AssignedProject> algorithm(vector<Contributor> contributors,vector<Project> projects) {
    
    sortProjects(projects);
   
    map<Contributor, int> taken;
    vector<AssignedProject> assigned_projects;
    vector<AssignedProject> retval = algorithm_recursive(contributors, taken, projects, assigned_projects , 0);
  
    return retval;
}


vector<AssignedProject> algorithm_recursive(vector<Contributor> contributors, map<Contributor, int> taken,vector<Project> projecten, <AssignedProject> assigned_projects , int k) {


    if (projecten.size() <= 0) {
        // geen projecten meer
        return assigned_projects;
    } else {
       //find best project
       Project project = projecten[0];
       
       // free contributors who are free
       map<Contributor, int> new_taken;
       auto iter = taken.begin();
       while (iter != taken.end()) {
            if ( iter->second == k){
                contributors.push_back(iter->first);
            } else {
                new_taken[iter->first] = iter->second;
            }
            ++iter;
        }
       
        // find best conributor for project
      auto  skill_needed = project.get_skill_keys();
      auto  level_needed = project.get_level();
      vector<Contributors> cccc;
      for ( int i = 0; i < skill_needed.size(); ++i){
        string skill = skill_needed[i];
        int level = level_needed[i];
        Contributor contributor = contributorFree(contributors, skill, level_needed);
        new_taken[contributor] = k;
        contributors.erase(contributors.begin(),contributors.end(),contributor);
        cccc.push_back(contributor);
      }
      projecten.erase(projecten.begin(),projecten.end(),project);
      AssignedProject ass_project = AssignedProject(project, cccc);
      assigned_projects.push_back(ass_project);
      algorithm_recursive(contributors, new_taken, projecten, assigned_projects , k+1);
    }
    return assigned_projects; // temp
}

std::vector<Contributor> possibleMentors(std::string skill, int skill_level, std::vector<Contributor> contributors){
    std::vector<Contributor> mentors;
    for (Contributor mentor: contributors) {
        if (mentor.get_skills()[skill] >= skill_level) {
            mentors.push_back(mentor);
        }
    }
    return mentors;
}

bool compareProject(Project p1, Project p2) {
    if (p1.get_best_before() == p2.get_best_before()) {
        return (p1.get_score() < p2.get_score());
    }
    return (p1.get_best_before() < p2.get_best_before());
}


// TODO mentor shit
Contributor contributorFree(vector<Contributor> contributors, string skill, int level_needed){
     // have the skill at the required level or higher

     // have the skill at exactly one level below the required level, only if another contributor on the same project (assigned to another role), has this skill at the required level or higher. In this case, the contributor will be mentored by their colleague :)

    Contributor contributor;
    int best = 1234323;
    for (int i = 0; i < contributors.size(); ++i) {
        Contributor con = contributors[i];
        // er is een contributor met minder skills (deze is dus meer inzetbaar)
        if (best < con.get_num_skills()) continue;
        auto skills = con.get_skills();
        // con heeft skill niet
        if (skills.find(skill) == skills.end()) continue;
        // level
        int level_con = skills[skill];
        if (level_needed > level_con) continue;
        best = con.get_num_skills();
        contributor = con;
    }            
    
    return contributor;
}
