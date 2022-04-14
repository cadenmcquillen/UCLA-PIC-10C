#include "compare.h"
void Longest_Common_Substring(std::string Submission_Folder,std::pair<std::filesystem::path, std::filesystem::path> File_Pair){
    
    std::ifstream file1; //first file to open
    std::ifstream file2; //second file to open
    std::string path1 = std::get<0>(File_Pair); //path to first file
    std::string path2 = std::get<1>(File_Pair); //path to second file
    std::string text1; //text output from first file (char by char)
    text1.insert(0, "~"); //add ~ as marker instead of "" char to start of string
    std::string text2; //text output from first file (char by char)
    text2.insert(0, "~");//add add ~ as marker instead of "" to start of string
    
    file1.open (path1, std::ifstream::in); //open first file
    char character1;
    while(file1>>std::noskipws >>character1){  //read data from first submisson and put it into string (making sure to include whitespace)
        text1.push_back(character1);
    }
    file1.close();
    
    file2.open (path2, std::ifstream::in); //open second file
    char character2;
    while(file2>>std::noskipws>>character2){ //read data from second submission and put into string (making sure to include whitespace)
        text2.push_back(character2);
    }
    file2.close();
    
    size_t startingPos1 = path1.find(Submission_Folder); //find posistion of full path that starts at directory that user specified
    std::string ForPrintOutput1 = path1.substr(startingPos1,path1.size()); //splice full path string to only "Submissions/Diego/source.cpp" for example
    
    size_t startingPos2 = path2.find(Submission_Folder); //do same thing for second path
    std::string ForPrintOutput2 = path2.substr(startingPos2,path2.size());
    
    //std::cout<<ForPrintOutput1<<"\n";
    //std ::cout<<ForPrintOutput2<<"\n";
    
   // std::cout<<text1<<"\n";
    //std::cout<<text2<<"\n";
    
    
    bool matches[text1.size()][text2.size()];
    size_t count[text1.size()][text2.size()];
    
    for (size_t i = 0; i< text1.size(); i++){ //create matches matrix
        for(size_t j = 0; j< text2.size(); j++){

            if(text1[i]==text2[j]){
                matches[i][j] = true;
            }
            else{
                matches[i][j] = false;
            }
        }
    }

    //std::cout<<"This is 0,0: "<<matches[0][0]<<"\n";
    //std::cout<<"This is 1,1: "<<matches[1][1]<<"\n";

    
    for (size_t i = 0; i< text1.size(); i++){ //intialize count matrix
        for(size_t j = 0; j< text2.size(); j++){
            if(i==0 || j==0){
                count[i][j] = 1;
            }
            else{
                count[i][j] = 0;
            }
        }
    }
    

    
    for (size_t i = 1; i< text1.size(); i++){ // fill in rest of count matrix
        for(size_t j = 1; j< text2.size(); j++){
            if(matches[i][j]== false){
                count[i][j] = std::max(count[i][j-1], count[i-1][j]);
                //std::cout<<i<<","<<j<<","<<count[i][j]<<"\n";
            }
            else{
                count[i][j]= 1+count[i-1][j-1];
                //std::cout<<i<<","<<j<<","<<count[i][j]<<"\n";
            }
        }
    }
    
   
    std::string longestCommonSubstring;
    size_t i = text1.size()-1;
    size_t j = text2.size()-1;
    //std::cout<<i<<","<<j<<"\n";
    while(i>0 && j>0){ //backtracking and "removing" the "~" we added at the start by stopping when either i or j gets to 0
        if(matches[i][j]== true){
            longestCommonSubstring.push_back(text1[i]);
            //longestCommonSubstring2.push_back(text1[i]);
            //std::cout<<i<<","<<j<<"\n";
            //std::cout<<text1[i]<<"\n";
            i--;
            j--;
        }
        else{
            if(count[i][j-1]>count[i-1][j]){
                j--;
            }
            else{
                i--;
            }
        }
        //std::cout<<i<<","<<j<<"\n";
        //if(count[i][j]==1){
            //break;
       // }
        
    }

    
    
    //std::cout<<text1[text1.size()-1];
    //size_t Total_Overlap = longestCommonSubstring.size();
    
    //for(size_t i = 0; i<longestCommonSubstring.length()/2;i++){
        //using std;
        //std::swap(longestCommonSubstring[i],longestCommonSubstring[longestCommonSubstring.length()/2 -i+1]);
   // }
    //std::string longestCommonSubstring_final(longestCommonSubstring);
    
    //longestCommonSubstring_final.erase(0);
   // longestCommonSubstring2.erase(longestCommonSubstring.begin());

    //std::vector<char> final_output;
    std::reverse(longestCommonSubstring.begin(), longestCommonSubstring.end());
   // std::cout<<longestCommonSubstring;
    
   // for(size_t i=longestCommonSubstring2.size()-1;i>0;i--){
       // size_t j = 0;
        //std::cout<<longestCommonSubstring2[i];
        //final_output[j]=longestCommonSubstring2[i];
        //std::cout<<final_output[j];
       // j++;
   // }
    //std::cout<<final_output<<"\n";
    std::cout<<"Pairing "<<ForPrintOutput1<<"-"<<ForPrintOutput2<<"\n";
    std::cout<<"Common Subsequence Length: "<<longestCommonSubstring.size()<<"\n";
    std::cout<<"Overlap:\n";
    std::cout<<longestCommonSubstring<<"\n";
    
    
}
