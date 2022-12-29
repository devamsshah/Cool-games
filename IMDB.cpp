/**********************************************************
 * Name: Devam Shah
 * Project Name: IMDB
 * Date: 11/04/2022
**********************************************************/
//relevant files that are needed in the program are declared here
#include <cctype>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>
#include <string>
#include <algorithm>
#include <cassert>
using namespace std;
/*********************************************** Helper functions
 ****************************************************************/

struct movieTitle {//struct for the movie.titles.tsv
    string titleid;
    string titleType;
    string primaryTitle;
    string originalTitle;
    string isAdult;
    string startYear;
    string endYear;
    string runtimeMinutes;
    string genres;
};
struct movieName {//struct for the movie.name.tsv
    string nameid;
    string primaryName;
    string birthYear;
    string deathYear;
    string primaryProfession;
};
struct moviePrincipal {//struct for the movie.principals.tsv
    string titleID;
    string ordering;
    string nameID;
    string category;
    string job;
    string character;
};
void splitString(string const line, char delimiter, vector<string> &items) {  //given function
    stringstream s_stream(line);
    while (s_stream.good()) {
        string item;
        getline(s_stream, item, delimiter);
        items.push_back(item);
    }
}
/**********************************************************************************************************/

vector<movieName> vectorizationName (string &fileNames) {//this function assigns the names.tsv file to vector named names
    ifstream namefile;
    string line1;  //breaks up the files into lines and then breaks up each line into words and assigns them to the names vector.
    vector<movieName> names;//names vector
    namefile.open(fileNames);
    assert(namefile.fail() == false);//checking if the files open or not
    while (getline(namefile, line1)) {
        vector<string> inputsName;
        splitString(line1, '\t', inputsName);//splits line1 into individual words
        movieName person;//assigns each word to the struct named person
        person.nameid = inputsName[0];
        person.primaryName = inputsName[1];
        person.birthYear = inputsName[2];
        person.deathYear = inputsName[3];
        person.primaryProfession = inputsName[4];
        names.push_back(person);//assigns each struct to new element in the names vector
        inputsName.clear();
    }
    namefile.close();//closes the file
    return names;
}

vector<moviePrincipal>  vectorizationPrincipals (string &filePrincipals) {//this function assigns the principals.tsv file to vector named principals
    ifstream principalsFile(filePrincipals);
    string line2; //breaks up the files into lines and then breaks up each line into words and assigns them to the principals vector
    vector<moviePrincipal> principals;//principals vector
    getline(principalsFile, line2);
    while (getline(principalsFile, line2)) {
        vector<string> inputsPrincipal;
        splitString(line2, '\t', inputsPrincipal);//splits line1 into individual words
        moviePrincipal principal;//assigns each word to the struct named principal
        principal.titleID = inputsPrincipal[0];
        principal.ordering = inputsPrincipal[1];
        principal.nameID = inputsPrincipal[2];
        principal.category = inputsPrincipal[3];
        principal.job = inputsPrincipal[4];
        principal.character = inputsPrincipal[5];
        principals.push_back(principal);//assigns each struct to new element in the principals vector
        inputsPrincipal.clear();
    }
    principalsFile.close();//closes the file
    return principals;
}

vector<movieTitle> vectorizationTitles (string &filesTitles){//this function assigns the titles.tsv file to vector named titles
    ifstream titlesFile(filesTitles);
    string line3;//breaks up the files into lines and then breaks up each line into words and assigns them to the titles vector
    vector<movieTitle> titles;//titles vector
    getline(titlesFile,line3);
    while (getline(titlesFile,line3)){
        vector<string> inputsTitle;
        splitString(line3, '\t', inputsTitle);//splits line1 into individual words
        movieTitle title;//assigns each word to the struct named title
        title.titleid =inputsTitle[0];
        title.titleType = inputsTitle[1];
        title.primaryTitle =inputsTitle[2];
        title.originalTitle = inputsTitle[3];
        title.isAdult = inputsTitle[4];
        title.startYear =inputsTitle[5];
        title.endYear = inputsTitle[6];
        title.runtimeMinutes = inputsTitle[7];
        title.genres =inputsTitle[8];
        titles.push_back(title);//assigns each struct to new element in the titles vector
        inputsTitle.clear();
    }
    titlesFile.close();//closes the file
    return titles;
}

int menuOption1P1(vector<movieTitle> &vecT, string s, vector<moviePrincipal> &vecP, vector <movieName> &vecN, vector<movieTitle> &shortlist) {//menu option 1 part 1
    vector<string> seperatedInput;//declaring a vector that will be assigned to the words from the input
    for (int l = 0; l < s.size(); l++) {//makes the input to lower case
        s[l] = tolower(s[l]);
    }
    splitString(s, '+', seperatedInput);//splits the input and assigns to seperatedInput
    int counter = 0;//a variable that checks if all of the input string elements have been compared
    for (int i = 0; i < vecT.size(); i++) {//for loop for accessing variables in the titles vector
        counter = 0;
        for (int d = 0;
             d < seperatedInput.size(); d++) {//for loop for accessing variables in the seperated input vector
            string temp = "";//declaring temp variable
            for (int j = 0; j < vecT.at(i).primaryTitle.size(); j++) {//accessing each character of the struct's primary title
                temp += tolower(vecT[i].primaryTitle.at(j));//converts temp to lowercase
            }
            if (temp.find(seperatedInput.at(d)) != string::npos) {//finds the temp in the seperated input
                counter++;
            }
        }
        if (counter == seperatedInput.size()) {//if all of the input strings have been compared then the resulting element in vecT gets assigned to the shortlist
            shortlist.push_back(vecT[i]);
        }
    }
    if (shortlist.size() == 0) {//if the shortlist  vector is empty then it prints "no march found"
        cout << "No match found!" << endl;
    } else {
        for (int w = 0; w < shortlist.size(); w++) {//prints relevant output and structs from the given shortlist
            cout << w << ":" << endl;
            cout << "Title: " << shortlist.at(w).primaryTitle << endl;
            cout << "Year: " << shortlist.at(w).startYear << endl;
            string genre = shortlist.at(w).genres;
            for (int z = 0; z < genre.size() - 1; z++) {
                if (genre.at(z) == ',') {
                    genre.replace(z, 1, " ");
                }
            }
            cout << "Genre: " << genre << endl;
            cout << "---------------" << endl;
        }
    }
    return 0;
}
int menuOption1P2(vector<movieTitle> &vecT, vector<moviePrincipal> &vecP, vector <movieName> &vecN, vector<movieTitle> &shortlist, int intForSecondPart){
    movieTitle titleInfo = shortlist.at(intForSecondPart);//assigns teh selected result to the relevant struct
    vector<moviePrincipal> preOutput;//declares 2 vectors that will be filled with the relevant structs that match the searchs
    vector<movieName> finalOutput;
    for (int i = 0; i< vecP.size(); i++){//for loop that accesses each element of principals
        if(titleInfo.titleid == vecP[i].titleID){//checks if the titles.tsv titleid matches the principals titleid
            if(vecP[i].category == "actor" || vecP[i].category == "actress") {//checks if they are actors/actresses or not
                preOutput.push_back(vecP[i]);//assigns the result to a new element in preOutput
            }
        }
    }
    for(int j = 0; j<preOutput.size(); j++){//for loop that accesses each element of preOutput
        for(int k =0; k<vecN.size(); k++){ //for loop that accesses each element of names
            if(preOutput[j].nameID == vecN[k].nameid) //checks if the preoutput nameID matches the names nameID
                finalOutput.push_back(vecN[k]);//assigns the result to a new element in finalOutput
        }

    }
    for(int l = 0; l<finalOutput.size(); l++) {//for loop that accesses each element of finalOutput and prints them out
        cout << finalOutput[l].primaryName << preOutput[l].character << endl;
    }
    return 0;
}

int menuOption2P1(vector<movieTitle> &vecT, string s, vector<moviePrincipal> &vecP, vector <movieName> &vecN, vector<movieName> &shortlist) {//menu option 2 part 1
    vector<string> seperatedInput;//declaring a vector that will be assigned to the words from the input
    for (int l = 0; l < s.size(); l++) {
        s[l] = tolower(s[l]);//makes the input to lower case
    }
    splitString(s, '+', seperatedInput);//splits the input and assigns to seperatedInput
    int counter = 0;//a variable that checks if all of the input string elements have been compared
    for (int i = 0; i < vecN.size(); i++) {//for loop for accessing variables in the titles vector
        counter = 0;
        for (int d = 0; d < seperatedInput.size(); d++) {//for loop for accessing variables in the seperated input vector
            string temp = "";//declaring temp variable
            for (int j = 0; j < vecN.at(i).primaryName.size(); j++) {//accessing each character of the struct's primary title
                temp += tolower(vecN[i].primaryName.at(j));//converts temp to lowercase
            }
            if (temp.find(seperatedInput.at(d)) != string::npos) {//finds the temp in the seperated input
                counter++;
            }
        }
        if (counter == seperatedInput.size()) {//if all of the input strings have been compared then the resulting element in vecT gets assigned to the shortlist
            shortlist.push_back(vecN[i]);
        }
    }
    if(shortlist.size() == 0){//if the shortlist  vector is empty then it prints "no march found"
        cout << "No match found!" << endl;
    } else {
        for (int w = 0; w < shortlist.size(); w++) {//prints relevant output and structs from the given shortlist
            cout << w << ":" << endl;
            cout << shortlist.at(w).primaryName << endl;
            cout << shortlist.at(w).primaryProfession << endl;
            cout << "(" << shortlist.at(w).birthYear << "-" << shortlist.at(w).deathYear << ")" << endl;
            cout << "---------------" << endl;
        }
    }
    return 0;
}
int menuOption2P2(vector<movieTitle> &vecT, vector<moviePrincipal> &vecP, vector <movieName> &vecN, vector<movieName> &shortlist, int intForSecondPart){
    movieName titleInfo = shortlist.at(intForSecondPart);//assigns teh selected result to the relevant struct
    vector<moviePrincipal> preOutput;//declares 2 vectors that will be filled with the relevant structs that match the searchs
    vector<movieTitle> finalOutput;
    for (int i = 0; i< vecP.size(); i++){//for loop that accesses each element of principals
        if(titleInfo.nameid == vecP[i].nameID){//checks if the titles.tsv titleid matches the principals titleid
                preOutput.push_back(vecP[i]);//assigns the result to a new element in preOutput
        }
    }
    for(int j = 0; j<preOutput.size(); j++){//for loop that accesses each element of preOutput
        for(int k =0; k<vecT.size(); k++){//for loop that accesses each element of names
            if(preOutput[j].titleID == vecT[k].titleid)//checks if the preoutput nameID matches the names nameID
                finalOutput.push_back(vecT[k]);//assigns the result to a new element in finalOutput
        }

    }
    for(int l = 0; l<finalOutput.size(); l++) {//for loop that accesses each element of finalOutput and prints them out
        cout << finalOutput[l].primaryTitle << " " << finalOutput[l].startYear << " " << preOutput[l].character << endl;
    }
    return 0;
}
int menuOption3(){//returns 0 to exit the program
    return 0;
}

int run(string titleFile, string nameFile, string principalFile) {
    vector<movieName> inputsName = vectorizationName(nameFile); //assigning the words in name.tsv file to elements in vector to inputsName
    vector<moviePrincipal> inputsPrincipal = vectorizationPrincipals(principalFile);//assigning the words in principals.tsv file to elements in vector to inputsPrincipals
    vector<movieTitle> inputsTitle = vectorizationTitles(titleFile);//assigning the words in titles.tsv file to elements in vector to inputsTitle
    cout<< "Select a menu option:" << endl;//prints the relevant instructions and information so that user can know information
    cout << "\t1. Search for movies" << endl;
    cout << "\t2. Search for actors/actresses" << endl;
    cout << "\t3. Exit" << endl;
    int choiceByUser;
    cout << "Your choice --> ";
    cin >> choiceByUser;//takes in the option that the user selects
    string searchPhrase1 = "";//declaring the input string that will be fed by the user
    if(choiceByUser==1){//executes option one
        cout << "Enter search phrase: ";
        cin >> searchPhrase1;//takes in user input
        vector<movieTitle> shortlist1;//vector that helps satisfy the parameter
        menuOption1P1(inputsTitle, searchPhrase1, inputsPrincipal, inputsName, shortlist1);//executing menu option 1
        int intForSecondPart1;//executes the second part of the 1st option
        cout << "Select a movie to see its actors/actresses (-1 to go back to the previous menu): ";
        cin >> intForSecondPart1;
        if(intForSecondPart1 == -1){//checks if user wants to go back to the previous menu
            run(titleFile, nameFile, principalFile);
        }else{//if they dont want to go to the previous menu, the option fed in is printed
            menuOption1P2(inputsTitle, inputsPrincipal, inputsName, shortlist1, intForSecondPart1);
        }
    }else if(choiceByUser==2){//if the user wants to access option 2
        string searchPhrase2 = "";//string for entering the search
        cout << "Enter search phrase: ";
        cin >> searchPhrase2;
        vector<movieName> shortlist2;//vector that will take in the elements of movieName and eventually print out the desired output
        menuOption2P1(inputsTitle, searchPhrase2, inputsPrincipal, inputsName, shortlist2);
        int intForSecondPart2;
        cout << "Select a actors/actresses to see movies (-1 to go back to the previous menu): ";
        cin >> intForSecondPart2;
        if(intForSecondPart2 == -1){//checks if the user wants to go back to the previous menu
            run(titleFile, nameFile, principalFile);
        }else{//if they dont want to go to the previous menu, the next part of the menu option 2 will print out
            menuOption2P2(inputsTitle, inputsPrincipal, inputsName, shortlist2, intForSecondPart2);
        }
    }else if(choiceByUser==3){//checks if the user wants to exit the search program
        menuOption3();
    }
    return 0;
}

int main() {
    //Change these addresses according to your local machine
    string titlesFile =    "movie.titles.tsv";
    string namesFile = "movie.names.tsv";
    string principalsFile = "movie.principals.tsv";

    //DO NOT change the main function. The main function will be removed by the autograder
    run(titlesFile, namesFile, principalsFile);
    return 0;
}

