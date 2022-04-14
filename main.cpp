#include <filesystem>
#include <iostream>
#include <vector>
#include "compare.h"

int main(int argc, const char * argv[]) {
    std::string folder_name_given = argv[1];
    //std::string folder_name_given2 = ;
    //std::filesystem::current_path("/Users/Caden/Downloads/HW3_Supp");
    std::string CurrentDirectory = std::filesystem::current_path();
    std::string Fullpath = CurrentDirectory+"/"+folder_name_given;
    std::filesystem::path submission_folder_path = Fullpath;
    std::vector< std::filesystem::path> subdirectories;
    std::vector< std::filesystem::path> file_paths;
    std::vector<std::pair<std::filesystem::path, std::filesystem::path>> submission_pairings; //create vector of pairs i.e. <"./Bob_Submission", "./Alice_Submission">
    
    
    if(is_directory(submission_folder_path)){ //if we are given valid dirctory
        //std::filesystem::current_path(submission_folder_path); //change working directory to 
        std::filesystem::directory_iterator cd_iterator{submission_folder_path};
        
        for (const auto& SubDirectory : cd_iterator) { //loop through given directory
            if (SubDirectory.is_directory()) { //if subdirectory is a valid directory
                subdirectories.push_back(SubDirectory.path()); //add path to subdirectories vector
            }
        }
        for (const auto& SubDirect: subdirectories ){ //loop through sub-directories
            std::filesystem::directory_iterator iterator{SubDirect};
            if(iterator->is_regular_file()){ //if the first file in the subdirectory is a valid file
                file_paths.push_back(iterator->path()); //add file path to vector holding all file paths
            }
        }
        size_t NumSubs = file_paths.size();
        for ( size_t i = 0; i < NumSubs; i++) { //loop through file paths, and store pairwise pairs
                for (size_t j = i + 1; j < NumSubs; j++) {
                    submission_pairings.emplace_back(file_paths[i], file_paths[j]);
                }
            }
        
    }
    for (const auto & pairings: submission_pairings){
        Longest_Common_Substring(folder_name_given,pairings); // run longest common substring on all pairings
    }
    
    return 0;
}
