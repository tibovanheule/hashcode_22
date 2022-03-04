#include "utils.h"
#include "fileparser.h"
#include "contributor.h"
#include "project.h"
#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <cstring>


using namespace std;

void file_parse(std::string filename, vector<Contributor>* contributors, vector<Project>* projects) {
    std::string line;
    ifstream input_file(filename);

    if (input_file.is_open()) {
        std::getline(input_file, line);

         // Used to split string around spaces.
        istringstream ss(line);
        string word; // for storing each word
        std::vector<string> wordsvec;
        while (ss >> word) 
        {
            wordsvec.push_back(word);
        }

        int nr_contributors = stoi(wordsvec[0]);
        int nr_projects = stoi(wordsvec[1]);
        println(std::to_string(nr_projects));
        println(std::to_string(nr_contributors));
        int skill_lines = 0;
        string projectname;
        int days;
        int score;
        int bbf;
        int amount_roles;
        //string current_contributor;
        string contributor_name;
        int num_skills;
        Contributor current_contributor;
        Project current_project;
        // Parse the contributors 
        while (nr_contributors > 0){
            map<string, int> skillset;
  
            if(skill_lines == 0) {
                std::getline(input_file, line);
                // new person, add to list of contributors & add new skillset entry

                istringstream ss(line);
                string word; // for storing each word
                std::vector<string> wordsvec;
                while (ss >> word) 
                {
                    wordsvec.push_back(word);
                }

                //ANNA 1
                contributor_name = wordsvec[0];
                skill_lines = stoi(wordsvec[1]);
                num_skills = stoi(wordsvec[1]);

            }
            while (skill_lines > 0) {
                std::getline(input_file, line);
                println(line);
                istringstream ss(line);
                string word; // for storing each word
                std::vector<string> wordsvec;
                while (ss >> word) 
                {
                    wordsvec.push_back(word);
                }

                // New skill for person, add to list
                println(wordsvec[0]);
                println(wordsvec[1]);
                skillset[wordsvec[0]] = stoi(wordsvec[1]);
                // Python, 3
                skill_lines--;
      
            }

            /*
            Add skills to contributor
            */
            
            current_contributor = Contributor(contributor_name, num_skills, skillset);
            contributors->push_back(current_contributor);


            nr_contributors--;

        }
        
        // Parse the projects
        
        while ( nr_projects > 0) {
            std::getline(input_file, line);
                // new project, add to list of contributors & add new skillset entry

            istringstream ss(line);
            string word; // for storing each word
            std::vector<string> wordsvec;
            while (ss >> word) 
            {
                wordsvec.push_back(word);
                
            }

            println("GOT HERE 420");

            projectname = wordsvec[0];
            days = stoi(wordsvec[1]);
            score = stoi(wordsvec[2]);
            bbf = stoi(wordsvec[3]);
            amount_roles = stoi(wordsvec[4]);

            vector<string> skill_keys;
            vector<int> skill_levels;


            while (amount_roles > 0){
                // Parse line & seperate
                std::getline(input_file, line);
                istringstream ss(line);
                string word; // for storing each word
                std::vector<string> wordsvec;
                while (ss >> word) 
                {
                    wordsvec.push_back(word);
                } 


                std::string skill = wordsvec[0];
                int skill_lvl = stoi(wordsvec[1]);

                skill_keys.push_back(skill);
                skill_levels.push_back(skill_lvl);
                
                amount_roles--;
            }

            nr_projects--;

            current_project = Project(projectname, days, score, bbf, amount_roles, skill_keys, skill_levels);
            projects->push_back(current_project);

        }
            
    }
        input_file.close();

}