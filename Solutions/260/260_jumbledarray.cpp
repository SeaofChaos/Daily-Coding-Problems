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

int* createArray(std::string *inputArray, int size){  //need the size as you cannot get it from a pointer
    int numMinus = 0;
    int numPlus = 0;

    queue<int> inputQueue;     //holds numbers depending on + and - counting away from 0

    for (int i=0; i<size; i++){
        if (inputArray[i] == "+"){
            numPlus++;
            inputQueue.push(numPlus);
        }
        else {  //counting "None" as - but could go either way
            inputQueue.push(0-numMinus);
            numMinus++;
        }
    }
    
    int* outputArray = new int[size];
    for (int i=0; !inputQueue.empty(); i++){    //shift numbers up depending on number of -'s so lowest number is 0
        int numtoPush = inputQueue.front() + numMinus-1;
        inputQueue.pop();
        outputArray[i] = numtoPush;
    }

    return outputArray;
}

int main(){
    std::string inputArray[] = {"None", "+", "+", "-", "+"};
    int size = sizeof(inputArray)/sizeof(inputArray[0]);
    int *outputArray = createArray(inputArray, size);

     //print array for visual purposes
    cout << '[';
    for (int i=0; i<size; i++){
        cout << outputArray[i];
        if (!(i==size-1))
            cout << ", ";
    }
    cout << ']';

    return 0;
}