/*
    This problem was asked by Pinterest.

    The sequence [0, 1, ..., N] has been jumbled, and the only clue you have for its order is an 
    array representing whether each number is larger or smaller than the last. Given this 
    information, reconstruct an array that is consistent with it. For example, given 
    [None, +, +, -, +], you could return [1, 2, 3, 0, 4].
*/

#include <iostream>
#include <string>

using namespace std;

int* createArray(std::string *inputArray, const int size){  //need the size as you cannot get it from a pointer
    int numMinus = 0;
    int numPlus = 0;

   int* outputArray = new int[size];

    for (int i=0; i<size; i++){
        if (inputArray[i] == "+"){
            numPlus++;
            outputArray[i] = numPlus;
        }
        else {  //counting "None" as - but could go either way
            outputArray[i] = 0-numMinus;
            numMinus++;
        }
    }
    
    for (int i=0; i<size; i++){    //shift numbers up depending on number of -'s so lowest number is 0
        outputArray[i] += numMinus-1;
    }

    return outputArray;
}

int main(){
    std::string inputArray[] = {"None", "+", "+", "-", "+"};
    const int size = sizeof(inputArray)/sizeof(inputArray[0]);
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