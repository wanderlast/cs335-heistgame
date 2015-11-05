#include <iostream>
using namespace std;

int main(){
    int array[100];

    for(int i = 0; i <100; i++){
	array[i] = i+1;
    }
    for (int i = 0; i < 100; i++){
	cout << array[i] << endl;
    }
    return 0;
}
