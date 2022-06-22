/*
    Problem Statement:

    Create a basic sentence checker that takes in a stream of characters 
    and determines whether they form valid sentences. If a sentence is 
    valid, the program should print it out.

    We can consider a sentence valid if it conforms to the following rules:

        The sentence must start with a capital letter, followed by a lowercase 
            letter or a space.

        All other characters must be lowercase letters, separators (,,;,:) or 
            terminal marks (.,?,!,‽).
        
        There must be a single space between each word.

        The sentence must end with a terminal mark immediately following a 
            word.
*/

#include <iostream>
#include <string>
#include <unordered_set>

std::unordered_set<wchar_t> TERMINALS = {'.', '?', '!', L'‽'};
std::unordered_set<char> SEPARATORS = {',', ';', ':', ' '};

/*
    Function to check if terminal character is valid.
*/
bool checkTerminal(std::wstring sentence){
    wchar_t terminal = sentence[sentence.length()-1];
    //check for terminal at end of sentence
    if (TERMINALS.count(terminal)){
        terminal = sentence[sentence.length()-2];
        //if there is a word (character) before terminal
        if (terminal >= 'a' && terminal <= 'z') return true;
        else return false;
    }
    return false;
}

/*
    Function to check for proper word spacing.
*/
bool checkSpaces(std::wstring sentence){
    //check for multiple spaces between words
    for (int i=0; i<sentence.length()-2; i++){
        if (sentence[i] == ' '){
            if (sentence[i+1] == ' ' || sentence[i-1] == ' ') 
                return false;
        }
    }
    return true;
}

/*
    Function to check for any illegal characters.
*/
bool checkCharacters(std::wstring sentence){
    //check every character in sentence
    for (int i=1; i < sentence.length()-1; i++){
        char letter = sentence[i];
        if (letter >= 'a' && letter <= 'z')
            continue;
        else if (SEPARATORS.count(letter))
            continue;
        return false;
    }
    return true;
}

void checkSentence(std::wstring sentence){
    bool valid = true;
    if (!isupper(sentence.at(0))) valid = false;
    if (!checkCharacters(sentence)) valid = false;
    if (!checkSpaces(sentence)) valid = false;
    if (!checkTerminal(sentence)) valid = false;
    if (valid) {
        std::wcout << sentence << std::endl;
    }
    else {
        std::cout << "Invalid Sentence" << std::endl;
    }
}

int main(){
    //set locale to account for unicode characters
    setlocale(LC_CTYPE,"");
    //sentences must be wstring so they can hold any potential unicode characters
    checkSentence(L"Hello world."); //valid sentence
    checkSentence(L"HelLo WorlD."); //invalid sentence (multiple capitals)
    checkSentence(L"Hello world?"); //valid
    checkSentence(L"Hello. world."); //invalid (terminal not at end of sentence)
    checkSentence(L"Hello world"); //invalid (no terminal)
    checkSentence(L"Hello  world!"); //invalid (two spaces between words)
    
    //unicode representation on windows is slightly confusing, which makes printing
    // them slightly difficult, but it should work (it may depend on compiler).
    checkSentence(L"Hello world‽"); //valid
}
