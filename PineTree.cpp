/**------------------------------------------

    Program Name: Layered Pine Tree
    Prompt for the number of tree layers and display
    ASCII layered pine tree
    System: MacOS and G++
    Author: Devam Shah

 ---------------------------------------------**/

#include <iostream>   // for cin and cout
#include <iomanip>    // for setw. The number in setw(...) is the total of blank spaces including the printed item.

using namespace std; // so that we don't need to preface every cin and cout with std::

int main()
{
    // Display the menu and get the user choice
    int menu_option = 0;
    cout << "Program 1: The Pine Tree            \n"
         << "Choose from the following options:  \n"
         << "   1. Display the HELLO graphic  \n"
         << "   2. Display The Pine Tree        \n"
         << "   3. Exit the program          \n"
         << "Your choice -> ";
    cin >> menu_option;

    if (menu_option == 3) { // Handle menu option of 3 to exit
        exit(0); // The call to exit the code successfully (0 means the runs didn't encounter any problem).
    }

    else if (menu_option == 1) { // Handle menu option of 1 to display custom ASCII graphics
        // Display ASCII graphics for "HELLO".
        // The main purpose of this part is to give you hints about usnig setw and setfill and their behaviors.
        //the character for the frame of our display.
        char frame = '-';
        cout << "Enter your frame character: ";
        cin >> frame;
        cout << endl;
        // The goal of next three lines is to print a line with 77 dashes differently.
        cout << setfill(frame); //change the default character for filling the fields defined using setw. You can change it fill to different character to see the difference.
        cout << setw(78) << "\n"; // \n counts in 78 so you will get 77 dashes plus one \n
        cout << setw(78) << endl; ///after setfill you need to pass a string or character to push setfil to fill the field, otherwise you will see an empty line for this instruction. See the differnce in output from this line and the above line.
        cout << setw(77) << frame << endl; //I use 77 with setfill and one extra at the end to get the same result

        cout << setw(8) << " " << "   **    **    ********    **         **         ********    " << setw(9) << "\n";
        cout << setw(8) << " " << "   **    **    ********    **         **         ********    " << setw(9) << "\n";
        cout << setw(8) << " " << "   **    **    **          **         **         **    **    " << setw(9) << "\n";
        cout << setw(8) << " " << "   ********    ********    **         **         **    **    " << setw(9) << "\n";
        cout << setw(8) << " " << "   ********    ********    **         **         **    **    " << setw(9) << "\n";
        cout << setw(8) << " " << "   **    **    **          **         **         **    **    " << setw(9) << "\n";
        cout << setw(8) << " " << "   **    **    ********    ********   ********   ********    " << setw(9) << "\n";
        cout << setw(8) << " " << "   **    **    ********    ********   ********   ********    " << setw(9) << "\n";
        cout << setw(77) << frame << endl; //the extra character is - so in total we will have 77 dashes.
        cout << setw(78) << "\n"; //again, the extra character is \n so you have set the width to 78

        //you can do it this way using a for-loop too
        for (int i = 0; i < 77; i++) {
            cout << frame;
        }
        cout << endl;



    }
    else if (menu_option == 2) {
        // Prompt for and get the number of layers for the tree.
    int treeLayers = 0;
    cout << "Number of tree layers -> ";
    cin >> treeLayers;
    cout << endl; //do not remove this line. It is essential for the autograder!
    int indent = treeLayers; //this gives the number of spaces or indentations we need
    int originalIndent = indent; //originalIndent is the place holder, so when the var indent changes, we still have a variable that holds the original number of indents
    int numAst = 5; //number of asterisks. they are 5 because the 3rd line of the first layer is 5
    for (int i = 0; i < treeLayers; i++) { //for loop to iterate multiple layers
        numAst -= 4; //-4 because we want only 1 asterisk on the topmost line of the first layer.
        indent += 2; //we do 5/2 = 2 since we want an int. there is no such thing as 2.5 spacess. and then print the character'*'
        for (int x = 0; x < 3; x++) {//nested for loop which adds indents
            cout << setw(indent);// sets the umber of spaces needed
            for (int counter = 0; counter < numAst; counter++) {// tweaks and adds the numbeer of the asts in the layer
            cout << "*"; // gets a new line so every line of asts is printed on a new line
                } //adds to to the asts to you can go from 1-3-5-3-5-7-5-7-9
            cout << endl; // decreases the number of spaces by 1
            numAst += 2;
            indent--;
            }
        }
        int barkLength = treeLayers * 2; // we set the length of the bark *2 to the layers
        for (int i = 0; i < barkLength; i++) { //loop to iterate which prints out ||| the number of times the layers are *2
            cout << setw(originalIndent + 3) << "|||" << endl;
        }
    } //end if( menu_option == 2)
    cout << endl; //DO NOT CHANGE THIS LINE
    return 0;
}
