#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>

using namespace std;

/* implement your stack here */
struct Node {
	float data;
	Node* next;
};

class Stack {

public:
	Stack();
	~Stack();
	void push(int newthing);
	void pop();
	int top();
	bool isEmpty();

private://Holds data we want these to be private so they cannot be called or used outside the class 

	Node* listpointer;
};

Stack::Stack()
{
	listpointer = NULL;
}

Stack::~Stack()
{
}

void Stack::push(int newthing) {//pushes a new thing onto the top of the stack

	Node* temp;
	temp = new Node;
	temp->data = newthing;
	temp->next = listpointer;
	listpointer = temp;
}

void Stack::pop() {//removes the top item of the stack
	Node* p;
	p = listpointer;
	if (listpointer != NULL) {
		listpointer = listpointer->next;
		delete p;
	}
}

int Stack::top() {//returns the vaule of the top item on the stack _-- Should always be wraped with isEmpty method so not to crash
	return listpointer->data;
}

bool Stack::isEmpty() {
	if (listpointer == NULL) {
		return true;
	}

	return false;
}

int main(int argc, char** argv) {//get arguments from command line, i.e., yourexec filename
	Stack S;
	int result = 0;
	int op1 = 0;
	int op2 = 0; 
	int number = 0; 
	int i = 0;;
	char oper;
	string expression;
	ifstream input_file;
	

	if (argc != 2) {
		cout << "needs a filename as argument  " << endl;
		exit(0);
	}
	input_file.open(argv[1]);
	if (!input_file.good()) {
		cout << "cannot read file " << argv[1] << endl;
		exit(0);
	}
	while (!input_file.eof()) {
		getline(input_file, expression);
		if (isdigit(expression[0])) {
			stringstream line(expression);
			line >> number;
			printf("reading number %d\n", number);
			//modify here to deal with the Stack
			
			S.push(number);
		
		}
		else {
			if (expression[0] == '+' || expression[0] == '-' || expression[0] == '/' || expression[0] == '*') {
				stringstream line(expression);
				line >> oper;
				printf("reading operator %c\n", oper);

				if (S.isEmpty() == false) {
					op2 = S.top();
					S.pop();
				  }
				else {
					printf("too many operators\n");
					
				}

				if (S.isEmpty() == false) {
					op1 = S.top();
					S.pop();
				}
				else {
					printf("too many operators\n");
					
				}

					int result;
					if (oper == '+') result = op2 + op1;
					if (oper == '*') result = op2 * op1;
					if (oper == '-') result = op1 - op2;
					if (oper == '/') result = op1 / op2;
					//printf("Result: %d", result);
					S.push(result);

					
				
			}
		}
	}
	result = S.top();
	S.pop();
	if (S.isEmpty() == false) {
		printf("too many numbers\n");
		exit;
	}
	else {
		printf("The result is %d\n", result);
	}
	//S.pop();

}
	//finalanswer = TOP
	//the last element of the stack should be the final answer...