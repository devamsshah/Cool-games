/****************************
 *
 *Project Name: password checket
 *Created By: Devam Shah
 *Date: 10/14/2022
 *
 * *** **********************/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <array>
#include <algorithm>
using namespace std;
vector<string> leakedFiles;
vector<string> englishWords;
const string rule_msg_1 = "The selected password must be at least eight characters long.";//declaration of all the strings to return in case the password doesnt meet a condition.
const string rule_msg_2 = "The selected password must have at least one uppercase letter.";//declaration of all the strings to return in case the password doesnt meet a condition.
const string rule_msg_3 = "The selected password must have at least one lowercase letter.";//declaration of all the strings to return in case the password doesnt meet a condition.
const string rule_msg_4 = "The selected password must have at least one digit.";//declaration of all the strings to return in case the password doesnt meet a condition.
const string rule_msg_5 = "The selected password must have at least one of special characters: [@,!,#,^,&,*,$]";//declaration of all the strings to return in case the password doesnt meet a condition.
const string rule_msg_6 = "The selected password has been leaked.";//declaration of all the strings to return in case the password doesnt meet a condition.
const string rule_msg_7 = "The selected password cannot contain a dictionary word.";//declaration of all the strings to return in case the password doesnt meet a condition.
void funct(string leaked_password_file, string english_word_file); //predeclaration of all the functions
void enterPassword(string password);
bool ruleOne(string password);
bool ruleTwo(string password);
bool ruleThree(string password);
bool ruleFour(string password);
bool ruleFive(string password);
bool binarySearch(vector<string> arr, string pass);
string removeIntAndSplChar(string password);
void ruleSix(string password, vector<string> b, vector<string> c);
bool firstFiveRules(string password);
int run(string password1);

void getFiles(string leaked_password_file, string english_word_file){//a function that converts both the files into 2 different vectors so it is easy to access each individual string
    string password; //also further explained in the run function
    ifstream lpfout;
    lpfout.open(leaked_password_file);
    vector<string> leakedFile;//vector initialization
    string line1;
    while (lpfout >> line1){//while loop that picks each word and assigns it to a position in the vector
        leakedFiles.push_back(line1);
    }
    ifstream ewfout; //also further explained in the run function
    ewfout.open(english_word_file);
    vector<string> englishWords;//vector initialization
    string line2;
    while (ewfout >> line2){//while loop that picks each word and assigns it to a position in the vector
        englishWords.push_back(line2);
    }
}

bool ruleOne(string password){//checks if the password contains 8 characters or not
    bool err1 = false;
    if (password.size()>=8){//if statement that checks if there are 8 characters and returns true if there are 8 characters.
        err1 = true;
    }
    return err1;//otherwise false is returned
}
bool ruleTwo(string password){//checks if there is 1 uppercase letter
    bool err2 = false;
    for (int i = 0; i<password.size(); i++){//for loop that checks each character of the string
        if(isupper(password[i])){//checks if the character is upper case or not
            err2 = true;//returns true and exits the lopp to return the final value of err2
            break;
        }
    }
    return err2;
}
bool ruleThree(string password){//checks if there is 1 lower case letter or not
    bool err3 = false;
    for (int i = 0; i<password.size(); i++){//for loop that checks each character of the string
        if(islower(password[i])){//checks if the character is lower case or not
            err3 = true;//returns true and exits the lop to return the final value of err3
            break;
        }
    }
    return err3;
}
bool ruleFour(string password){//checks if there is at least 1 digit or not
    bool err4 = false;
    for (int i = 0; i<password.size(); i++){//for loop that checks each character of the string
        if(isdigit(password[i])){//checks if the character is a digit or not
            err4 = true;//returns true and exits the loop to return the final value of err4
            break;
        }
    }
    return err4;
}
bool ruleFive(string password){//checks if there is at least 1 special character or not
    bool err5 = false;
    for (int i = 0; i<password.size(); i++){//for loop that checks each character of the string
        int b = password[i];
        if(((b>32)&&(b<48))||(password[i]=='@')){//checks if the character is a digit or not
            err5 = true;//returns true and exits the loop to return the final value of err5
            break;
        }
    }
    return err5;
}


bool binarySearch(vector<string> arr, string pass){//function that finds the string int the string vector
    int low = 0;//the lower limit variable
  bool b = true;//boolean variable to satisfy the function
    int high = arr.size()-1;//the upper limit variable
    unsigned int mid;//the middle of the checking area
    while(low<=high){//while loop that looks through each appropriate section
        mid = (low+high)/2;//cuts the unnecessary checking area where needed to narrow down the number of searching strings
        if(arr[mid]>pass){//checks if the password value is greatter than the vector string
            high = mid - 1;
        }else if (arr[mid]<pass){//checks if the password value is lesser than the vector string
            low = mid + 1;
        }else{//finally finds if there is a word that equals the password then it returns true and if not then it returns false
            if(arr[mid] ==pass){
                b= true;
            }
            else {
                b = false;
            }
        }
    }
  return b;
}
string removeIntAndSplChar(string password){//function that removes the special characters and integers fromt the actual password and assigns the new password that is without characters and digits to a new string called passW
  string passW="";
    for(int z = 0; z<password.size(); z++){//for loop that goes through each character and checks if it is a normal alphabetic character
        if (isalpha(password[z])) {//if it is an alphabet then it gets put in the new string and if not, then that character just gets ignored
            passW += tolower(password[z]);
        }
        //int temp = password[z];
        //if(((temp>47)&&(temp<58))||(temp == '@')||(isdigit(temp))){
          //  password.erase(z);
        //}
    }
    return passW; //returns the new string with only alphabets
}
void ruleSeven(string password, vector<string> a){//checks if the word is in the file of enlgish dictionary or not
  string passW = removeIntAndSplChar(password);//previous function is called and a new string that doesnt have spl characters or digits is assigned to the string
    if(find(a.begin(), a.end(), passW) != a.end()){//if statement that checks if there exists a word that is in the file.
      cout << rule_msg_7 << endl;//print statement for the case that there is a word.
      cout << "Password rejected!"<< endl;
    }else{//print statement for if there isnt that word.
      cout << "Password accepted!" << endl;
    }
}
void ruleSix(string password, vector<string> b, vector<string>c){//checks if the word is in the file of leaked passwords file or not
  string tempPass = removeIntAndSplChar(password);//previous function is called and a new string that doesnt have spl characters or digits is assigned to the string
  if(binarySearch(b, tempPass)){//if statement that checks if there exists a word that is in the file.
    cout<<rule_msg_6<< endl;//print statement for the case that there is a word.
    cout << "Password rejected!"<< endl;
  }else{
        ruleSeven(password, c);//if there isnt that word then the code moves on to execute rule seven
  }
}
bool firstFiveRules(string password){//function that checks if all five rules are checked or not
    if ((ruleOne(password)) && (ruleTwo(password)) && (ruleThree(password)) && (ruleFour(password)) && (ruleFive(password))) {
        ruleSix(password, leakedFiles, englishWords);
        return true;//if statement that returns true when all the 5 conditions are ment
    }
    else{
        if (!(ruleOne(password))) {//each if statement returns a message in case that particular condition is not met
            cout<<rule_msg_1<<endl;
        }
        if (!(ruleTwo(password))) {
            cout<<rule_msg_2<<endl;
        }
        if (!(ruleThree(password))) {
            cout << rule_msg_3 <<endl;
        }
        if(!(ruleFour(password))) {
            cout<<rule_msg_4<<endl;
        }
        if (!(ruleFive(password))) {
            cout<<rule_msg_5<<endl;
        }
        return false;//finally returns false so that the compiler doesnt move on to check rule six.
    }
}



int run(string file1, string file2){//the run funciton that calls and executes all the functions and makes the computer do what it is supposed to do-- check the password and if it meets the condiditons or not
  string password;
    cout << "Enter password: ";//print statement for entering password
    cin>> password;//feeds human input of a password to the computer
  bool firstFive = firstFiveRules(password);//checks if first 5 conditions have been met or not
    if (firstFive){//if the first five are true then the 2 files (english dictionary and leaked passwords) are accessed
        getFiles(file1,file2);
    ifstream lpfout;//code that converts the words in the files into a vector so it is easier to access and search each word in the leaked files file
    lpfout.open(file1);
    vector<string> leakedFile{};
    string line1;
    while (lpfout >> line1){
        leakedFiles.push_back(line1);
    }
    ifstream ewfout;//code that converts the words in the files into a vector so it is easier to access and search each word in the english words file
    ewfout.open(file2);
    vector<string> englishWords;
    string line2;
    while (ewfout >> line2){
        englishWords.push_back(line2);
    }
      lpfout.close();
    }
    return 0;//return statement to satisfy the run function
}

int main() {
    /** Change the address of the files appropriatly based on your local machine.
     * This main function will be replaced during testing. Do not add any line of code to the mai function
     **/
    string leaked_password_file = "alleged-gmail-passwords.txt"; //change this based on the location of the file on your machine
    string english_word_file = "words_5.txt"; //change this based on the location of the file on your machine
    int runVar = run(leaked_password_file, english_word_file);
    return 0;
}

