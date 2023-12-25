/* ---------------------------------------------
    Program 5: Unscrambler
        Program for an Unscrambler game where
        random words are selected from a file
        then put into a game board and scrambled.
        The user has to solve the board so that the
        words are correct.

    Course: CS 141, Fall 2021. Tues 9am lab
    System: Windows using CLion
    Author: Aleksandr Elifirenko
*/

#include <sstream>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cassert>
using namespace std;

//The unscrambler class with the game functions and variables
class Unscrambler{
public:
    //class Unscrambler variables
    int boardSize = 0;
    string words;
    string scrambled;
    //class Unscrambler functions
    void displayBoard();
    void displayScrambledBoard();
    void allWordsFromFile(vector<string> & fileWords);
    void rotateRow(int row, int changeAmount);
    void rotateColumn(int column, int changeAmount);
};//end Unscrambler class

//Displays the board with correct words
void Unscrambler::displayBoard()
{
    //Printing the column numbers
    for(int i = 0; i < boardSize; i++){
        cout << i << " ";
    }
    cout << endl;
    //The board loop
    for(int i = 0; i < boardSize; i++){
        //Prints the dashes at the top and after each following row
        for(int k = 0; k < (boardSize * 4) - 1; k++){
            cout << "-";
        }
        cout << endl;
        cout << i;
        //Prints a | followed by a letter in the board
        for(int j = 0; j < boardSize; j++){
            cout <<  "|" << words.at(i * boardSize + j);
        }
        cout << "|" << endl;
    }
    //Prints the dashes at the end of the board
    for(int i = 0; i < (boardSize * 4) - 1; i++) {
        cout << "-";
    }
    cout << endl;
}//end Unscrambler::displayBoard()

//Displays the scrambled words board
void Unscrambler::displayScrambledBoard()
{
    cout << "Current board: " << endl;
    //Printing the column numbers
    for(int i = 0; i < boardSize; i++){
        cout << i << " ";
    }
    cout << endl;
    for(int i = 0; i < boardSize; i++){
        //Prints the dashes at the top and after each following row
        for(int k = 0; k < (boardSize * 4) - 1; k++){
            cout << "-";
        }
        cout << endl;
        cout << i;
        //Prints a | followed by a letter in the board
        for(int j = 0; j < boardSize; j++){
            cout <<  "|" << scrambled.at(i * boardSize + j);
        }
        cout << "|" << endl;
    }
    //Prints the dashes at the end of the board
    for(int i = 0; i < (boardSize * 4) - 1; i++) {
        cout << "-";
    }
    cout << endl;
}//end Unscrambler::displayScrambledBoard()

//Choose random words from the all fileWords vector
void Unscrambler::allWordsFromFile(vector<string> & fileWords)
{
    //The condition variable for the loop
    int count = (boardSize*boardSize) - words.length();
    while(count > 2){
        int random = rand() % fileWords.size();
        //Stores random words into a string until there are 2 or less spaces left
        if(count >= fileWords.at(random).length()) {
            words += fileWords.at(random);
            if (count > 2){
                //Add a space after each word
                words += " ";
                count = (boardSize * boardSize) - words.length();
            }
        }
    }
    if(count > 1){
        //Add two spaces if there are only two possible spaces left in the string
        words += "  ";
    }else if(count > 0) {
        //Add one space if there is only one space left in the string
        words += " ";
    }
    //Set the scrambled string equal to words so that we can leave the words untouched
    scrambled = words;
}//end Unscrambler::allWordsFromFile()

//Rotates the row
void Unscrambler::rotateRow(int row, //Row number
                            int rotateAmount) //Amount to rotate
{
    while(rotateAmount < 0){//Takes care of negative inputs for rotate amount
        rotateAmount += boardSize;
    }
    for(int i = 0; i < rotateAmount; i++){
        //Store the last letter of a string in a char
        char lastElement = scrambled.at(row*boardSize+boardSize - 1);
        //Moves each letter over by one starting with the first letter
        for(int j = 0; j < boardSize - 1; j++){
            scrambled.at(boardSize * row + boardSize - 1 - j) = scrambled.at(boardSize * row + boardSize - 2 - j);
        }
        //Places the last letter in the beginning of the row
        scrambled.at(boardSize * row) = lastElement;
    }
}//end Unscrambler::rotateRow()

//Rotates the Column
void Unscrambler::rotateColumn(int column, //Column number
                               int rotateAmount)//Amount to rotate
{
    while(rotateAmount < 0){//Takes care of negative inputs for rotate amount
        rotateAmount += boardSize;
    }
    for(int i = 0; i < rotateAmount; i++){
        //Store the last letter of a string in a char
        char lastElement = scrambled.at(column + boardSize * (boardSize - 1));
        //Moves each letter down by one starting with the first letter
        for(int j = 0; j < boardSize - 1; j++){
            scrambled.at(column + boardSize * (boardSize- 1 - j)) = scrambled.at(column + boardSize * (boardSize - 2 - j));
        }
        //Places the last letter in the beginning of the column
        scrambled.at(column) = lastElement;
    }
}//end Unscrambler::rotateColumn()

//Reads in the whole file into a vector
void readFile(vector <string> & fileWords)//The words from file
{
    ifstream dictFile("dictionary-3to5-letters.txt");
    assert(dictFile.fail() == false );
    string nextWord;
    //Looks for beginning of the word and places it in a vector
    while( dictFile >> nextWord) {
        fileWords.push_back(nextWord);
    }
    dictFile.close();
}//end readFIle()

//Displays the words in the correct board and scrambled board
void displayCurrentWords(string currentWords)
{
    vector <string> words;
    string outPutString;
    //Loop runs until the end of the line
    while(currentWords.find(' ') != string::npos) {
        //Checks that if two or more spaces in a row, it doesn't store a space
        if (currentWords.find(' ') != 0) {
            outPutString += currentWords.substr(0, currentWords.find(' ')) + ',';
        }
        currentWords = currentWords.substr(currentWords.find(' ') + 1);
    }
    outPutString = outPutString.substr(0, outPutString.size() - 1);
    //Period at teh end
    cout << outPutString << "." << endl;
}//end displayCurrentWords()

//Displays all instructions
void instructions(){
    cout << "Enter one of the following: \n"
         << "R to rotate a row or column, \n"
         << "C to view what the completed board should look like, \n"
         << "B to reset the board back to the beginning,\n"
         << "G to generate a new board with new random words,\n"
         << "S to have the computer automatically solve a board that you enter (5 points extra credit),\n"
         << "Q to quit.\n"
         << "Your choice: \n";
}//end instructions()

int main() {
    vector<string> fileWords;//vector of all words
    readFile(fileWords);
    Unscrambler board;
    int scrambleTimes;
    int boardSize;
    srand(1);//random seed
    cout << "Program 5: Unscrambler\n"
         << "CS 141, Fall 2021, UIC" << endl;
    cout << "You will be presented with a board that is filled\n"
         << "with scrambled words. Rotate the rows and columns\n"
         << "to get the words displayed in the right order.\n";
    cout << fileWords.size() << " words have been read in from the dictionary." << endl;
    string choiceQuit;
    cout << "Enter Q to quit or B to begin: " << endl;
    cin >> choiceQuit;
    //Quits in the beginning of the program if user decides
    if (choiceQuit == "Q" || choiceQuit == "q") {
        cout << "Thank you for playing!\n"
             << "Exiting program...";
        exit(EXIT_FAILURE);
    }
    //Continues the program if the user doesn't quit
    else if (choiceQuit == "B" || choiceQuit == "b") {
        cout << "Choose your board size (must be a number greater than or equal to 4): " << endl;
        cin >> boardSize;
        //Will prompt the user to keep entering the board size if it is less that 4
        while (boardSize < 4) {
            cout << "The board size must be at least 4. Retry." << endl;
            cout << "Choose your board size (must be a number greater than or equal to 4): " << endl;
            cin >> boardSize;
        }
        board.boardSize = boardSize;//Sets the board size
        board.allWordsFromFile(fileWords);//Makes a string of random words based on board size
        cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1):"
             << endl;
        cin >> scrambleTimes;
        //If times to scramble is less than 1 user will be prompted to enter scramble times until its bigger than 1
        while (scrambleTimes < 1) {
            cout << "The number of times you select must be at least 1. Retry." << endl;
            cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1):"
                 << endl;
            cin >> scrambleTimes;
        }
        cout << "These are the words that you should try to spell out using the board, in order:\n";
        displayCurrentWords(board.words);
        //Rotates random row and random column for however many times user inputs scrambleTimes
        for(int i = 0; i < scrambleTimes; i++){
            int randomRow = rand() % boardSize;//Random row
            int randomColumn = rand() % boardSize ;//Random column
            board.rotateRow(randomRow, 1);//Calls rotateRow to rotate a random row
            board.rotateColumn(randomColumn, 1);//Calls rotateColumn to rotate a random column
        }
        string firstScramble = board.scrambled;//Saves the first scramble
        board.displayScrambledBoard();//Displays the first scramble
        cout << "Current board words: " << board.scrambled << endl;
        char continuousChoice;
        instructions();
        while(true){
            cin >> continuousChoice;//Choice for different boards
            if(continuousChoice == 'R' || continuousChoice == 'r'){
                int pasNum, amountChange;
                char rowOrCol;
                //User input for row or column, row or column number and rotate amount
                cout << "Enter the row/column you would like to rotate, and the number of positions to rotate by.\n"
                     << "This should be in the format of <R or C> <row/column number> <number of positions to rotate>,\n"
                     << "where valid row and column numbers are between 0 and" << board.boardSize - 1 << ",\n"
                     << "E.g. R 0 1 would rotate the top row (row 0) of the board to the right once,\n"
                     << "c 1 -2 would rotate the second column (col 1) of the board upwards twice.\n"
                     << "Your choice: \n";
                cin >> rowOrCol >> pasNum >> amountChange;
                //Ensures user enters r for row or c for column
                while(rowOrCol != 'R' && rowOrCol != 'r' && rowOrCol != 'C' && rowOrCol != 'c'){
                    cout << "First input must be 'R' or 'C'. Try again." << endl;
                    cout << "Enter the row/column you would like to rotate, and the number of positions to rotate by.\n"
                         << "This should be in the format of <R or C> <row/column number> <number of positions to rotate>,\n"
                         << "where valid row and column numbers are between 0 and" << board.boardSize-1 << ",\n"
                         << "E.g. R 0 1 would rotate the top row (row 0) of the board to the right once,\n"
                         << "c 1 -2 would rotate the second column (col 1) of the board upwards twice.\n"
                         << "Your choice: \n";
                    cin >> rowOrCol >> pasNum >> amountChange;
                }
                //Loops until user enters a number between 0 and last column
                while(pasNum < 0 || pasNum > board.boardSize - 1){
                    cout << "Number must be between 0 and " << board.boardSize - 1 << ". Try again.";
                    cout << "Enter the row/column you would like to rotate, and the number of positions to rotate by.\n"
                         << "This should be in the format of <R or C> <row/column number> <number of positions to rotate>,\n"
                         << "where valid row and column numbers are between 0 and" << board.boardSize - 1 << ",\n"
                         << "E.g. R 0 1 would rotate the top row (row 0) of the board to the right once,\n"
                         << "c 1 -2 would rotate the second column (col 1) of the board upwards twice.\n"
                         << "Your choice: \n";
                    cin >> rowOrCol >> pasNum >> amountChange;
                }
                //If r is entered, row number that user entered is rotated by amount that user enters
                if(rowOrCol == 'R' || rowOrCol == 'r'){
                    board.rotateRow(pasNum, amountChange);
                }
                //If c is entered, column number that user entered is rotated by amount that user enters
                if(rowOrCol == 'C' || rowOrCol == 'c'){
                    board.rotateColumn(pasNum, amountChange);
                }
            }
            //Displays the completed unscrambled board
            if(continuousChoice == 'C' || continuousChoice == 'c')
            {
                cout << "The completed board should look like: " << endl;
                board.displayBoard();
                cout << "Current board words: " << board.words << endl;
            }
            //Generates a new scrambled board
            if(continuousChoice == 'G' || continuousChoice == 'g'){
                board.words = "";
                board.scrambled = "";
                board.allWordsFromFile(fileWords);
                //Rotates random row and random column for however many times user inputs scrambleTimes
                for(int i = 0; i < scrambleTimes; i++){
                    int randomRow = rand() % boardSize;
                    int randomColumn = rand() % boardSize ;
                    board.rotateRow(randomRow, 1);
                    board.rotateColumn(randomColumn, 1);
                }
                firstScramble = board.scrambled;
            }
            //Resets board to first time the board was scrambled
            if(continuousChoice == 'B' || continuousChoice == 'b'){
                board.scrambled = firstScramble;
            }
            //Quits the program
            if(continuousChoice == 'Q' || continuousChoice == 'q'){
                break;
            }
            //Prints current words
            if(board.words == board.scrambled){
                board.displayBoard();
                cout << "Current board words: " << board.scrambled << endl;
                cout << "Congratulations, you won!" << endl;
                break;
            }
            //Print the correct words for user to guess
            cout << "These are the words that you should try to spell out using the board, in order:\n";
            displayCurrentWords(board.words);
            board.displayScrambledBoard();
            cout << "Current board words: " << board.scrambled << endl;
            instructions();
        }
        cout << "Thank you for playing!\n"
             << "Exiting program...";

    }
}//end of main