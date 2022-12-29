
/****************************
 * Name: Devam Shah
 * Project Name: YAHTZEE
 * Date:  11/18/2022
 * ***************************/


#include <string>
#include <iostream>
#include <cstdlib>
#include <random>

using namespace std;
//#################################################################################################

class Dice{
private:
    int value;
    bool reRoll = true;
    //if true dice will roll again, if false then dice will stay constant
public:
    int roll(){
        value = (rand()%6)+1;
        return value;
        //Randomly assigns a value between from 1 to 6 to the dice.

    }
    //void roll();
    int reveal() {return value;}//gets the randomly assigned number of the given dice

    //The autograder will set the values directly instead of calling roll() to avoid randomness!
    void setValue(int value) {this->value = value;}//assigns a value to the dice
    //getter and setter for reroll
    bool getReRoll(){//gets the reroll boolean of the private dice
        return reRoll;
    }
    void setReRoll(bool a){//sets the reroll value according to program
       reRoll = a;
    }
};

//#################################################################################################

const int HAND_SIZE = 5;

class Hand {
public:

    //Display the value of the five dice
    void show(){//displays "hand" and the 5 values of the given dice
        cout << "Hand: ";
        for (int i = 0; i < 5; i++) {
            cout << diceResults[i].reveal() << " ";
        }
        cout << endl;
    }

    void play(){//if the reroll values are true then the dice are rolled again and vice versa
        for(int i =0; i<5; i++) {//goes through all the dice in the array
            if(diceResults[i].getReRoll()){
                diceResults[i].roll();
            }
        }
    }
    Dice* getDice(int diceNum){//gets the dice from the private array
        return &diceResults[diceNum];
    }

    //selection is the string of dice numbers that the player wants to keep.
    //For example, "125" means that player wants to keep the first, second, and fifth dice, and roll the rest.
    void setSelection(string selection){//takes in a string and assigns corresponding dice's reroll values to false
        for(int i =0; i<selection.length(); i++) {//goes trhough each character of the string (which will be a bunch of numbers)
            int tempNum = selection.at(i) - '0';//gets the position in which that number was assigned
            diceResults[tempNum-1].setReRoll(false);//sets that position's dice to false
        }
    }

    Hand() {
        for (int i = 0; i < 5; i++) {//initializes all the values of dice to true at first and rolls the dice.
            diceResults[i].setReRoll(true);
            diceResults[i].roll();
        }
    }
private:
    Dice diceResults[5];//array for the 5 dice to be rolled
};



//######################################################################


//List of rows in the board
const int ONES = 0;
const int TWOS = 1;
const int THREES = 2;
const int FOURS = 3;
const int FIVES = 4;
const int SIXES = 5;
const int THREE_OF_KIND = 6;
const int FOUR_OF_KIND = 7;
const int FULL_HOUSE = 8;
const int SMALL_STRAIGHT = 9;
const int LARGE_STRAIGHT = 10;
const int CHANCE = 11;
const int YAHTZEE = 12;

const int BOARD_SIZE=13;

class Game {

public:
    //calcScore returns a score of a hand (5 dice) for given row in the board.
    //Note the rows are indexed from zero.
    //For example if the hand is 2 1 1 5 1 then calcScore(hand, ONES) returns 3 and  calcScore(hand, TWOS) returns 2.
    int arrayIsPlayed[13] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
                             0}; //checks if the category that the player wants to play is played or not. uses 0 for not played and 1 for played
    string output[17] = {"-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-","-"};//array that stores the scores of all the categories.
    int calcScore(Hand *hand, int row) {//calculates the desired catagory's scores.
        Dice *givenDice = hand->getDice(1);
        Dice *tempDice1;//temp dices declared for each dice in teh temp array.
        Dice *tempDice2;
        Dice *tempDice3;
        Dice *tempDice4;
        Dice tempSort[5];//temporary array for sorting the dice in ascending order
        Dice temp;//temp dice taht will be used for sorting the tempSort array
        for (int i = 0; i < 5; i++) {//for loop that copies original dice array to tempSort array
            tempSort[i] = *hand->getDice(i);
        }
        for (int j = 0; j < 5; j++) {//loop that sorts the tempSort array in ascending order
            for (int k = j + 1; k < 5; k++) {
                if (tempSort[j].reveal() > tempSort[k].reveal()) {
                    temp = tempSort[j];
                    tempSort[j] = tempSort[k];
                    tempSort[k] = temp;
                }
            }

        }
        int numOnes = 0, numTwos = 0, numThrees = 0, numFours = 0, numFives = 0, numSixes = 0;//integers initialized for counting the number of each numbers in the dice array
        int sum = 0;//variable for the sum of all the dice values
        for (int i = 0; i < 5; ++i) {//for loop that goes through all the dice, checks the number of it and increases the values of that number accordingly
            if(hand->getDice(i)->reveal() == 1){
                numOnes++;//increases 1
            }else if (hand->getDice(i)->reveal() == 2){
                numTwos++;//increases 2
            }else if (hand->getDice(i)->reveal() == 3){
                numThrees++;//increases 3
            }else if (hand->getDice(i)->reveal() == 4){
                numFours++;//increases 4
            }else if (hand->getDice(i)->reveal() == 5){
                numFives++;//increases 5
            }else if (hand->getDice(i)->reveal() == 6){
                numSixes++;//increases 6
            }
        }
        for (int j = 0; j < 5; ++j) {//for loop that calculates the sum of the values of dice
            sum = sum + (hand->getDice(j)->reveal());
        }
        int total = 0;
        bool threeOfAKind = false;//initializing boolean values to the bottom of the board
        bool fourOfAKind = false;
        bool fullHouse = false;
        bool smallStraight = false;
        bool largeStraight = false;
        bool yahtzee = false;
        bool twoOfAKind = false;
        if(numSixes>1||numFives>1||numFours>1||numThrees>1||numTwos>1||numOnes>1){//if the values of either of the dice is greater than 1, then there are at least one set of 2 dice with the same value.
            twoOfAKind = true;
        }
        if(numSixes>2||numFives>2||numFours>2||numThrees>2||numTwos>2||numOnes>2){//if the values of either of the dice is greater than 2, then there are at least one set of 3 dice with the same value.
            threeOfAKind = true;
        }
        if (numSixes > 3 || numFives > 3 || numFours > 3 || numThrees > 3 || numTwos > 3 || numOnes > 3) {//if the values of either of the dice is greater than 3, then there are at least one set of 4 dice with the same value.
            fourOfAKind = true;
        }
        if ((numOnes>4)||(numTwos>4)||(numThrees>4)||(numFours>4)||(numFives>4)||(numSixes>4)){//if the values of either of the dice is greater than 4, then all the dice are of the same value
            yahtzee = true;
        }
            //upto 6
        if ((row + 1) < 7) {//looks at all the rows in the upper board
            for (int i = 0; i < 5; i++) {//checks through all the dice
                Dice temp = *((*hand).getDice(i));//assigns the dice to a temp dice
                if (temp.reveal() == row +1) {//checks if the dice value is equal to the relevant category or not
                    total++;//if it is then variable total would increase by 1;
                }
            }
            output[row] = to_string(total * (row +1));//the output will be assigned to the relevant score.
            arrayIsPlayed[row] = 1;//and teh category will be classified as played.
            return total * (row +1);//returns the score
        }
            //for three of a kind
        else if ((row + 1) == 7) {
            if(threeOfAKind){//if 3of a kind is true then
                output[row] = to_string(sum);//the output will be assigned to the relevant score.
                arrayIsPlayed[row] = 1;//and teh category will be classified as played.
                return sum;//returns the score
            }else{
                output[row] = to_string(0);//the output will be assigned to the relevant score.
                arrayIsPlayed[row] = 1;//and teh category will be classified as played.
                return 0;//returns the score
            }
        }
            //for four of a kind
        else if ((row+1)==8) {
            if (fourOfAKind) {//if 4of a kind is true then
                output[row] = to_string(sum);//the output will be assigned to the relevant score.
                arrayIsPlayed[row] = 1;//and teh category will be classified as played.
                return sum;//returns the score
            } else {
                output[row] = to_string(0);//the output will be assigned to the relevant score.
                arrayIsPlayed[row] = 1;//and teh category will be classified as played.
                return 0;//returns the score

            }
        }
            //for full house
        else if ((row+1)==9){
            if((twoOfAKind&&threeOfAKind&&!fourOfAKind)||(yahtzee)){//if 2 of a kind and 3 of a kind but not four of a kind are all true or if its yahtzee then full house will execute
                fullHouse = true;
            }
            if(fullHouse){//if full house is true
                output[row] = to_string(25);//the output will be assigned to the relevant score.
                arrayIsPlayed[row] = 1;//and teh category will be classified as played.
                return 25;//returns the score
            }
            else {
                output[row] = to_string(0);//the output will be assigned to the relevant score.
                arrayIsPlayed[row] = 1;//and teh category will be classified as played.
                return 0;//returns the score
            }
    }

        //for small straight
    else if ((row+1)==10){
        if(((numOnes>0)&&(numTwos>0)&&(numThrees>0)&&(numFours>0))||
            ((numTwos>0)&&(numThrees>0)&&(numFours>0)&&(numFives>0))||
                ((numThrees>0)&&(numFours>0)&&(numFives>0)&&(numSixes>0))){
            smallStraight = true;//checks if there is any combination of "1234" or "2345" or "3456" in the given dice and if there is then small straight will be true
        }
        if(smallStraight) {//if small straight is true then assigning 30 points
            output[row] = to_string(30);//the output will be assigned to the relevant score.
            arrayIsPlayed[row] = 1;//and teh category will be classified as played.
            return 30;//returns the score
        }
        else{//if not then 0 points are given
            output[row] = to_string(0);//the output will be assigned to the relevant score.
            arrayIsPlayed[row] = 1;//and teh category will be classified as played.
            return 0;//returns the score
        }
    }
        //for large straight
    else if ((row+1)==11){
        if(((tempSort[0].reveal() == 1)&&(tempSort[1].reveal() == 2)&&(tempSort[2].reveal() == 3)&&(tempSort[3].reveal() == 4)&&(tempSort[4].reveal() == 5))||((tempSort[0].reveal() == 2)&&(tempSort[1].reveal() == 3)&&(tempSort[2].reveal() == 4)&&(tempSort[3].reveal() == 5)&&(tempSort[4].reveal() == 6))){
            largeStraight = true;//checks if the array is "12345" or "23456" and if they are then large straight would be true
        }
        if(largeStraight){//if large straight is true then assigning 40 points
            output[row] = to_string(40);//the output will be assigned to the relevant score.
            arrayIsPlayed[row] = 1;//and teh category will be classified as played.
            return 40;//returns the score
        }else{//if not then 0 points are given
            output[row] = to_string(0);//the output will be assigned to the relevant score.
            arrayIsPlayed[row] = 1;//and teh category will be classified as played.
            return 0;//returns the score
        }
    }
    //for chance
    else if ((row+1)==12){
            output[row] = to_string(sum);//the output will be assigned to the relevant score.
            arrayIsPlayed[row] = 1;//and teh category will be classified as played.
            return sum;//returns the score
    }
    //for YAHTZEE
    else if((row+1)==13){
        if(yahtzee){//if yahtzee is true then
            output[row] = to_string(50);//the output will be assigned to the relevant score.
            arrayIsPlayed[row] = 1;//and teh category will be classified as played.
            return 50;//returns the score

        } else {
            output[row] = to_string(0);//the output will be assigned to the relevant score.
            arrayIsPlayed[row] = 1;//and teh category will be classified as played.
            return 0;//returns the score

        }
    }
}
    //iterate through each element of the vector, check if its sorted and if the is consecutive numbers and if teh counter is 4 or5 for small and large straight = both are flat 30 and 40 points
    //for chance sum total of all the dice
    //yahtzee is 5 of a kind
    //if there is 3 fo a kind and a pair then full house
    //Display the board
    void show(){//prints out the board and updates score accordingly
        cout << "1.\tOnes:"<<"\t\t\t\t"<<output[1]<<endl;
        cout << "2.\tTwos:"<<"\t\t\t\t"<<output[2]<<endl;
        cout << "3.\tThrees:"<<"\t\t\t\t"<<output[3]<<endl;
        cout << "4.\tFours:"<<"\t\t\t\t"<<output[4]<<endl;
        cout << "5.\tFives:"<<"\t\t\t\t"<<output[5]<<endl;
        cout << "6.\tSixes:"<<"\t\t\t\t"<<output[6]<<endl;
        cout << "  \tSum:"<<"\t\t\t\t"<<output[14]<<endl;
        cout << "  \tBonus:"<<"\t\t\t\t"<<output[15]<<endl;
        cout << "7.\tThree of a kind:"<<"\t"<<output[7]<<endl;
        cout << "8.\tFour of a kind:"<<"\t\t"<<output[8]<<endl;
        cout << "9.\tFull house:"<<"\t\t\t"<<output[9]<<endl;
        cout << "10.\tSmall straight:"<<"\t\t"<<output[10]<<endl;
        cout << "11.\tLarge straight:"<<"\t\t"<<output[11]<<endl;
        cout << "12.\tChance:"<<"\t\t\t\t"<<output[12]<<endl;
        cout << "13.\tYahtzee:"<<"\t\t\t"<<output[13]<<endl;
        cout << "Total:"<<"\t\t\t\t\t"<<output[16]<<endl;
    }

    //Returns the score of the upper part of the board
    int getUpperScore(){
        int sum = 0;
        if(output[0]=="-") {//checks if output is still in its initialized value
            upperVector[0] = "0";//if it is then uppervector gets assigned to 0
        }else{
            upperVector[0] = output[1];
        }
        if(output[1]=="-"){
            upperVector[1] = "0";
        }else{
            upperVector[1] = output[2];
        }
        if(output[2]=="-"){
            upperVector[2] = "0";
        }else{
            upperVector[2] = output[3];
        }
        if(output[3]=="-"){
            upperVector[3] = "0";
        }
        else{
            upperVector[3] = output[4];
        }
        if(output[4]=="-"){
            upperVector[4] = "0";
        }else{
            upperVector[4] = output[5];
        }if(output[5]=="-"){
            upperVector[5] = "0";
        }else{
            upperVector[5] = output[6];
        }

        int finUpperVector[16];//final upper vector is a vector that converts the string type of upper vector to int type
        for(int p=0; p<6; p++){
            if(upperVector[p] == "-"){//assigns each element of uppervector to corresponding final uppervector
                finUpperVector[p] = 0;//checks if uppervector is not "-"
            }
            else{
                finUpperVector[p] = (stoi(upperVector[p]));//if its not, then only it will assign the value to finuppervector
            }
        }
        for (int i = 0; i<6; i++){
            sum = sum + finUpperVector[i];//sums up each element of finuppervector
        }
        return sum;//returns that sum
    }

    //Returns the score of the lower part of the board
    int getLowerScore(){
        int counter = 0;
        int sum = 0;
        if(output[7]=="-") {//checks if output is still in its initialized value
            lowerVector[counter] = "0";//if it is then lowervector gets assigned to 0
        }else{
            lowerVector[counter] = output[7];
        }
        if(output[8]=="-"){
            lowerVector[counter] = "0";
        }else{
            lowerVector[counter] = output[8];
        }
        if(output[9]=="-"){
            lowerVector[counter] = "0";
        }else{
            lowerVector[counter] = output[9];
        }
        if(output[10]=="-"){
            lowerVector[counter] = "0";
        }
        else{
            lowerVector[counter] = output[10];
        }
        if(output[11]=="-"){
            lowerVector[counter] = "0";
        }else{
            lowerVector[counter] = output[11];
        }
        if(output[12]=="-"){
            lowerVector[counter] = "0";
        }else{
            lowerVector[counter] = output[12];
        }
        if(output[13]=="-"){
            lowerVector[counter] = "0";
        }else{
            lowerVector[counter] = output[13];
        }
        vector<int> finLowerVector;//final lower vector is a vector that converts the string type of lower vector
        for(int p=0; p<16; p++){
            if(lowerVector[p] == "-"){//assigns each element of lowervector to corresponding final lowervector
                finLowerVector[p] = 0;//checks if lowervector is not "-"
            }
            else{
                finLowerVector[p] = (stoi(lowerVector[p]));//if its not, then only it will assign the va
            }
        }
        for (int i = 0; i<6; i++){
            sum = sum + finLowerVector[i];//sums up each element of finlowervector
        }
        return sum;//returns that sum
    }

    //Returns the bonus points
    int getBonusScore(){
        if(getUpperScore()>=63){
            return 35;
        }
        else{
            return 0;
        }
    }


    //Play a hand based on the selected row
    void play(Hand* hand, int row){
        if(row<7){//assigns the relevant scores to the vector output
            if(row==1){
                output[1] = to_string(calcScore(hand, 1));
            }
            else if(row==2){
                output[2] = to_string(calcScore(hand, 2));
            }
            else if(row==3){
                output[3] = to_string(calcScore(hand, 3));
            }
            else if(row==4){
                output[4] = to_string(calcScore(hand, 4));
            }
            else if(row==5){
                output[5] = to_string(calcScore(hand, 5));
            }
            else if(row==6){
                output[6] = to_string(calcScore(hand, 6));
            }
        }
        else if(row==7){
            output[7] = to_string(calcScore(hand, 7));
        }
        else if(row==8){
            output[8] = to_string(calcScore(hand, 8));
        }
        else if(row==9){
            output[9] = to_string(calcScore(hand, 9));
        }
        else if(row==10){
            output[10] = to_string(calcScore(hand, 10));
        }
        else if(row==11){
            output[11] = to_string(calcScore(hand, 11));
        }
        else if(row==12){
            output[12] = to_string(calcScore(hand, 12));
        }
        else if(row==13){
            output[13] = to_string(calcScore(hand, 13));
        }
    }

    //Check to see if a row has been played or not (returns true if a row has been played)
    bool isPlayed(int row){//checks if the given category is played or not
        if(arrayIsPlayed[row] == 1){//goes through each element of the vector and if it is 1 then the category is played and returns true
            return true;
        }
        return false;//otherwise returns false.
    }

    //Check to see if all rows haven been played or not (returns true if all rows have been played)
    bool isFinished(){
        for (int i =0; i<13; i++){//goes through all is played and even if one is not played then false is returned
            if(!isPlayed(i)){
                return false;
            }
        }
        return true;//if all of them are played then true is returned
    }

private:
    string upperVector[6];//declaration of vecotrs used above
    string lowerVector[6];
};




//#######################################################################################

//The run function is the main loop of your program
void run() {
    Hand mainHand;//declaring the hand and game object
    Game mainGame;
    int numFilled = 0; //checks how many of the categories are filled
    int counter = 0;//counter for not letting the player re roll for more than three times.
    while(numFilled<15 && !mainGame.isFinished()) {
        mainGame.show();//shows the board and the hand
        mainHand.play();//assigns the random values to dice
        mainHand.show();//displays the random values
        cout << "Keep Dice (s to stop rolling): ";
        string inputForDiceConstant;
        cin >> inputForDiceConstant;//takes in the dice that the player wants to keep constant
        if((mainGame.isPlayed(1))&&(mainGame.isPlayed(2))&&(mainGame.isPlayed(3))&&(mainGame.isPlayed(4))&&(mainGame.isPlayed(5))&&(mainGame.isPlayed(6))) {
            mainGame.output[15] = mainGame.getBonusScore();//checks if the upper board has been played or not  if it is then bonus is executed  otherwise not
        }
        while (inputForDiceConstant!="s"&&counter<2){//loop that goes until the player has put s or has played thrice
            mainHand.setSelection(inputForDiceConstant);//sets the desired dice to constant and rolls the rest
            mainGame.show();//shows board and random dice
            mainHand.show();
            cout << "Keep Dice (s to stop rolling): ";
            cin >> inputForDiceConstant;
            counter++;//counter increases
            for (int l=0; l<5; l++){
                mainHand.getDice(l)->setReRoll(true);
            }//resets all the dice rerolls to true
        }
        bool correctPlay = true;//checks if the player doesnt play an already played function
        while (correctPlay) {//as long as player plays a valid category then
            cout << "enter a combination to play: ";
            int input;
            cin >> input;//takes in the category the player wants to play
                mainGame.play(&mainHand, input);
                cout << mainGame.output[input - 1];
                mainGame.arrayIsPlayed[input] = 1;//calculates score accordingly
                numFilled++;//increases the score value
                correctPlay = false;//changes the correct play value so it goes through teh checks again 
            }
        }
    }

//For these types of programs there exists many combinations that you might have missed.
//The best way to check them all is to write test cases for your program.
//Here I give you an example of checking large straight. You can design your own test cases for different parts.

// THE AUTOGRADER WILL REPLACE THE MAIN FUNCTION.
// DO NOT ADD ANY LOGIC OF YOUR PROGRAM HERE.
int main() {
    srand(time(0));
    run();
    return 0;
}
