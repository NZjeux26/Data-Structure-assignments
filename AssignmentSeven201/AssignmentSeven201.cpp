// Phillip Jose Andre Brown 21011867
#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

vector<int> vector_random;
vector<int> vector_reversed;
vector<int> vector_sorted;

class Heap {
private:
    vector<int> data;
    int last;
    int countinsert;
    int countdelete;
public:
    Heap() {
        last = -1;
        countinsert = 0;
        countdelete = 0;
    }
    ~Heap() {};
    void insertheap(int newthing);
    void PrintHeap();
    // bool Delete(int valuetodelete);
    int Insertcomp();
    int rootNode();
    int DeleteCount();
    void DeleteR();
    void heapify(int i);
};

// bool Heap::Delete(int valuetodelete) {
//     if (last < 0) { return false; }
//     int a;
//     for (a = 0; a < last; a++) {
//         if (data[a] == valuetodelete) break;
//     }
//     //printf("Index to delete is %d for item %d \n", a, valuetodelete);
//     //swap node with last, "delete" last
//     data[a] = data[last];
//     data[last] = 0;//deleting... 
//     // subtract last
//     last = last - 1;
//     data.shrink_to_fit();
//     //now fix the heap
//     int parindex = a;
//     int leftindex = parindex * 2 + 1;//left child
//     int rightindex = parindex * 2 + 2;//right child
//     bool swapping = true;
//     while ((data[parindex] < data[leftindex] || data[parindex] < data[rightindex]) && swapping == true) {
//         swapping = false;
//         countdelete++;
//         //printf("Comparing %d with L%d and R%d\n", data[parindex], data[leftindex], data[rightindex]);
//         if (data[rightindex] < data[leftindex]) {//follow left  
//             countdelete++;
//             swap(data[leftindex], data[parindex]);
//             parindex = leftindex;
//             swapping = true;           
//         }
//         else {//else follow right    
//             countdelete++;
//             swap(data[rightindex], data[parindex]);     
//             parindex = rightindex;
//             swapping = true;
//         }
//         leftindex = parindex * 2 + 1;
//         rightindex = parindex * 2 + 2;
       
//         //countdelete++;
//        // printf("checking Left %d against last %d\n", leftindex, last);
//         if (leftindex > last) { break; }//reverse isn't breaking here:: it doesn't have too.
//         else {
//             //countdelete++;
//             if (rightindex > last) {
//                 //countdelete++;
//                 if (data[parindex] < data[leftindex]) {   
//                     swap(data[parindex], data[leftindex]);
//                 }
//                 break;
//             }
//         }
//     }
//     return true;
// }

int Heap::Insertcomp()
{
    return countinsert;
}

int Heap::rootNode()
{
    //if (last <= 0) { return; }
    unsigned int rootvalue = data[0];//root node
    return rootvalue;
}

int Heap::DeleteCount()
{
    return countdelete++;
}

void Heap::DeleteR()
{
    int lastE = data[last];

    data[0] = lastE;

    last = last - 1;
    
    heapify(0);
}

void Heap::heapify(int i)
{
    int parindex = i;
    int leftindex = 2 * i + 1;
    int rightindex = 2 * i + 2;

    //if leftchild exists and larger than the root
    if (leftindex < last + 1) {
        countdelete++;
    }
    if (leftindex < last + 1 && data[leftindex] > data[parindex]) { 
        parindex = leftindex;
    }

    //if rightchild exists and larger than root
    if (rightindex < last + 1) {
        countdelete++;
    }
    if (rightindex < last + 1 && data[rightindex] > data[parindex]) {
        parindex = rightindex;
    }
    
    if (parindex != i) {
        swap(data[i], data[parindex]);
        heapify(parindex);
    }
}

void Heap::insertheap(int newthing)
{
    data.push_back(newthing);
    //data[last + 1] = newthing;
    last = last + 1;
    if (last == 0) {
        return;
    }
    int child_index = last;
    int par_index = 0;
    bool swapping = true;
    while (swapping) {
        swapping = false;
        if (child_index % 2 == 0) { par_index = child_index / 2 - 1; }//right
        else { par_index = child_index / 2; }
        if (par_index >= 0) {//this if loop always does comparasions
            countinsert++;
            if (data[child_index] > data[par_index]) {
                swap(data[child_index], data[par_index]);
                swapping = true;
                child_index = par_index;
            }
        }
    }
}

void Heap::PrintHeap()
{
    //printf("HEAP: \n");
    for (int i = 0; i < last + 1; i++) {//needs to be plus one to print all elements in the HEAP
        printf("%d ", data[i]);
    }
    printf("\n");
}


/* this is a possible prototype for the heapsort function */
/* the char* filename is just for printing the name, the file is opened and dealt with in the main() */
void heapsort(vector<int>& sortingvector, int number_of_elements, char* filename) {
    Heap H;
	/* Using the sortingvector, INSERT elements into the Heap */
    int i;
    int ci;
    int cd;
    int root;
    for (i = 0; i < number_of_elements; i++) {
        H.insertheap(sortingvector[i]);
    }
    sortingvector.clear();
	/* After building the heap from the file, PRINT the current state of the heap before sorting */
    cout << "Heap before sorting: " << filename << endl;
    H.PrintHeap();//will need to mod to reflect the requested output
	/* STORE how many comparisons were made until this point */
    ci = H.Insertcomp();
	/* DELETE elements from the Heap, copying it back to the vector in a way that it is sorted */
    for (i = (number_of_elements - 1); i >= 0; i--) {
        root = H.rootNode();
        //copy root to vector
        sortingvector.push_back(root);
        //delete root and reshuffle
        H.DeleteR(); 
    }
	/* STORE how many comparisons were made for the deletion process */
    cd = H.DeleteCount();
	/* PRINT the number of comparisons for the Insert and Deletion tasks */
    cout << "InsertHeap: " << ci << " comparisons" << endl;
    cout << "DeleteRoot: " << cd << " comparisons" << endl;
	/* Print the state of the vector after sorting */
    cout << "Vector after sorting:" << endl;
    for (int f = sortingvector.size() - 1; f >=0; f--) {//start from the right last position and move to the front.
        cout << sortingvector[f] << " ";
    }
    printf("\n");
}




int main(int argc, char** argv) {//get filename from arguments
	char expression[100];
	int number;
	ifstream input_file_random;
	ifstream input_file_reversed;
	ifstream input_file_sorted;

	if (argc == 4) {
		input_file_random.open(argv[1]);
		input_file_reversed.open(argv[2]);
		input_file_sorted.open(argv[3]);
	}
	else { printf("The program needs 3 filenames, in this order: random, reversed and sorted.\n"); exit(0); }
	int number_of_elements_random = 0;
  
	while (input_file_random >> number) {
		sscanf(expression, "%d", &number);
		/*Comment out this printout, this is just to check that the file can be read */
		//printf("%d ",number );	
		vector_random.push_back(number);
		number_of_elements_random++;
	}
	/*Comment out this printout, this is just to check that the array was copied */
	//printf("File %s:\n", argv[1]);
	//for (int count = 0; count < number_of_elements_random; count++) {
	//	printf("%d ", vector_random[count]);
	//}
	//printf("\n");
	/*end printout*/

	int number_of_elements_reversed = 0;
	while (input_file_reversed >> number) {
		sscanf(expression, "%d", &number);
		/*Comment out this printout, this is just to check that the file can be read */
		//printf("%d ",number );	
		vector_reversed.push_back(number);
		number_of_elements_reversed++;
	}
	/*Comment out this printout, this is just to check that the array was copied */
	/*printf("File %s:\n", argv[2]);
	for (int count = 0; count < number_of_elements_reversed; count++) {
		printf("%d ", vector_reversed[count]);
	}
	printf("\n");*/
	/*end printout*/


	int number_of_elements_sorted = 0;
	while (input_file_sorted >> number) {
		sscanf(expression, "%d", &number);
		/*Comment out this printout, this is just to check that the file can be read */
		//printf("%d ",number );	
		vector_sorted.push_back(number);
		number_of_elements_sorted++;
	}
	/*Comment out this printout, this is just to check that the array was copied */
	/*printf("File %s:\n", argv[3]);
	for (int count = 0; count < number_of_elements_sorted; count++) {
		printf("%d ", vector_sorted[count]);
	}
	printf("\n");*/
	/*end printout*/

	/* Implement or call your Heap sort here, the Heap class with methods should be copied/implemented before main() */
	heapsort(vector_random, number_of_elements_random, argv[1]);
	cout << endl;
	heapsort(vector_reversed, number_of_elements_reversed, argv[2]);
	cout << endl;
	heapsort(vector_sorted, number_of_elements_sorted, argv[3]);
   

}
