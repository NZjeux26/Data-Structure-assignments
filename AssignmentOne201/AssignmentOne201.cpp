// Phillip Jose Andre Brown 21011867
// 159201 assignment 1 skeleton
//You need to add your own AddNode and PrintLL functions, as well as an AddMatrices function
//
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct Node {  //declaration
	int row;
	int column;
	int value;
	Node* next;
};
Node* A, * B;  //declaration

struct findME
{
	int row;
	int column;
};
findME* F;

void AddNode2(Node*& listpointer, int row, int column, int value) {
	// add a new node to the TAIL of the list
	Node* current;
	current = listpointer;
	if (current != NULL) {
		while (current->next != NULL) {
			current = current->next;
		}
	}// now current points to the last element
	Node* temp;
	temp = new Node;
	temp->row = row;
	temp->column = column;
	temp->value = value;
	temp->next = NULL;
	if (current != NULL) current->next = temp;
	else listpointer = temp;
    //printf("AA %d AA \n", temp->row);
}

int rowcol(char* file_name) {

	//char* file_name;
	int col = 0, row = 0, value = 0;
	ifstream input;
	input.open(file_name);
	if (!input.good()) {
		cout << "Cannot open file [search]" << file_name << endl;
		exit(0);
	}
	int c;
	string line;
	//reads the first line to get dimensions
	if (input.good()) {
		getline(input, line);
		stringstream sline(line);
		sline >> row >> col;
		//cout << "Matrix dimensions " << row << " " << col << endl;
	}
	
	return row;
}

int search(Node* listpointer, int x, int y) {
	Node* current;
	current = listpointer;
	while (current != NULL) {
		if (current->row == x && current->column == y) {//If the row and column are a vaule > zero then return that to the print method to be printed.
			return current->value;
		}
		else
		{
			current = current->next;//Required so not stuck looking at the same X/Y
		}
	}
	return 0;//If it is null then return a 0 which will stop.
}

void AddMatrices(Node* A, Node* B, Node*&RES, char* file_name){
	int rowc = rowcol(file_name);
	for (int x = 0; x < rowc; x++) {
		for (int y = 0; y < rowc; y++) {
			int elementone = search(A, x, y);
			int elementtwo = search(B, x, y);
			int res = elementone + elementtwo;
			if (res != 0) {
				AddNode2(RES, x, y, res);
			}
		}
		
	}
}

void printMatrix(Node *&listpointer, char* file_name) {
	
	//char* file_name{};
	int rowc = rowcol(file_name);

	//printf("%d XX %d\n", data->column);//Test print to see what is being handled by the ptr

	for (int x = 0; x < rowc; x++) {
		listpointer->next;
		for (int y = 0; y < rowc; y++) {
			int elementone = search(listpointer, x, y);
			printf("%d ", elementone);
			
		}
		printf("\n");
	}
}

void PrintLL(Node* listpointer) {
	Node* current;
	current = listpointer;
	if (current == NULL) {
		printf("Matrix 1: \n");
		return;
	}
	printf("Matrix 1: ");
	while (current != NULL) {
		printf("%i ", current->value);
		current = current->next;
	}
	printf("\n");
}

void PrintLL2(Node* listpointer) {
	Node* current;
	current = listpointer;
	
	if (current == NULL) {
		printf("Matrix 2: \n");
		return;
	}
	printf("Matrix 2: ");
	while (current != NULL) {
		printf("%i ", current->value);
		current = current->next;
	}
	printf("\n");
}

void PrintLLR(Node* listpointer) {//Multiable print functions for different matrixs because i couldn't work out a smart way to print them dynamically.
	Node* current;
	current = listpointer;
	if (current == NULL) {
		printf("Matrix Result: \n");
		return;
	}
	printf("Matrix Result: ");
	while (current != NULL) {
		printf("%i ", current->value);
		current = current->next;
	}
	printf("\n");
}

void read_matrix(Node*& a, char* file_name) {
	//reads a matrix from a file
	int col = 0, row = 0, value = 0;
	ifstream input;
	input.open(file_name);
	if (!input.good()) {
		cout << "Cannot open file" << file_name << endl;
		exit(0);
	}
	int c;
	string line;
	//reads the first line to get dimensions
	if (input.good()) {
		getline(input, line);
		stringstream sline(line);
		sline >> row >> col;
		//cout << "Matrix dimensions " << row << " " << col << endl;
	}

	//rowcol(F, row, col);

	//read matrix;
	for (int i = 0; i < row; ++i) {
		if (input.good()) {
			getline(input, line);
			stringstream sline(line);
			for (int j = 0; j < col; ++j) {
				sline >> value;
				if (value == 0) continue;
				
				AddNode2(a, i, j,  value);

				//printf("BB %d BB \n", col);
				//The next line is for debbuging, it can be commented later
				//cout << "Element at (" << i << " " << j << ") is different than zero and it is: " << value << " ";
			}
			//the next line is for debbuging purposes, it can be commented out later
			//cout << endl;
		}
	}
	input.close();
}

int main(int argc, char** argv) {
	Node* A = NULL;
	Node* B = NULL;
	Node* RES = NULL;
	//findME* F = NULL;

	//printf("%d SS", F->column);

	if (argc != 3) { printf("needs two matrices \n"); exit(0); }
	//rowcol(argv[1]);
	//Matrix One -------------------------------------
	read_matrix(A, argv[1]);
	PrintLL(A);
	printMatrix(A,argv[1]);
	//printf("\n");
	//Matrix Two -------------------------------------
	read_matrix(B, argv[2]);
	PrintLL2(B);
	printMatrix(B, argv[2]);
	//Matrix combination and printing ----------------
	AddMatrices(A, B, RES, argv[2]);
	//printf("\n");
	PrintLLR(RES);
	printMatrix(RES, argv[2]);

	//ToDO: Formatting and Zero conditions
}