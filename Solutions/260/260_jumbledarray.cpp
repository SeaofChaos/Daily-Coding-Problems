/*
    This problem was asked by Pinterest.

    The sequence [0, 1, ..., N] has been jumbled, and the only clue you have for its order is an 
    array representing whether each number is larger or smaller than the last. Given this 
    information, reconstruct an array that is consistent with it. For example, given 
    [None, +, +, -, +], you could return [1, 2, 3, 0, 4].
*/

#include <iostream>
#include <queue>
#include <string>

using namespace std;

int* createArray(std::string *inputArray, int size){
    int numMinus = 0;
    int numPlus = 0;
    int numNone = 0;

    queue<int> inputQueue;

    for (int i=0; i<size; i++){
        if (inputArray[i] == "+" ){    //I'm assuming there's no reason to handle case "None" 
            numPlus++;
            inputQueue.push(numPlus);
        }
        else if (inputArray[i] == "-"){
            inputQueue.push(0-numMinus);
            numMinus++;
        }
        else {
            numNone++;
        }
    }
    
    int* outputArray = new int[size - numNone];
    for (int i=0; !inputQueue.empty(); i++){
        int numtoPush = inputQueue.front() + numMinus-1;
        inputQueue.pop();
        outputArray[i] = numtoPush;
        cout << outputArray[i] << ' ';
    }

    return outputArray;
}

int main(){
    std::string inputArray[5] = {"None", "+", "+", "-", "+"};
    int size = sizeof(inputArray)/sizeof(inputArray[0]);
    createArray(inputArray, size);
    return 0;
}
