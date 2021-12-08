// Phillip Brown 21011867
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <locale>
#include <sstream>
#include <string>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

class Queue
{
public:
    Queue();
    ~Queue();
    void Join(int newthing);
    void Leave();
    int Front();
    bool isEmpty();
    int qSize();
    void Print();

private:
    Node* front, * rear;
    int counter = 0;
};

Queue::Queue()
{
    front = NULL;
    rear = NULL;
}

Queue::~Queue()
{
}

void Queue::Join(int newthing) {//places item at the front of the queue ~~WARNING: Circular array will overide items already in the array
    //places new node at the rear of the queue
    Node* temp;
    temp = new Node;
    temp->data = newthing;
    temp->next = NULL;

    if (rear != NULL) {
        rear->next = temp;
    }
    rear = temp;
    if (front == NULL) {
        front = temp;
    }

    counter++;
}

void Queue::Leave() {
    Node* temp;

    if (front == NULL) {
        return;
    }

    temp = front;//temp becomes the front
    front = front->next;//the next item in the queue becomes the front

    if (front == NULL) {
        rear = NULL;
    }
    delete temp;//delete temp which was the old front
    counter--;
}

int Queue::Front() {
   // if (isEmpty()) { return -1; }
    return front->data;
}//If the queue is empty will crash, wrap in isEmpty if/Else 

bool Queue::isEmpty() {

    if (front == 0) { return true; }
    return false;
}

int Queue::qSize()
{
    return counter;
}

void Queue::Print()//For debugging
{
    if (front == NULL) {
        printf("The Queue is empty!\n");
        return;
    }

    Node* temp = front;

    while (temp != NULL) {
        printf("%i ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

////////////////////////////////////////////////////////////////////////

#define TIMEDELAY 3 //DO NOT CHANGE THIS VALUE!!!
#define N 128 //DO NOT CHANGE THIS VALUE!!!
int OutQueues_current[N];
int Congestion_Size[N];

/*include your array of queues declarations somewhere here, for example: */
//Queue InputQueues[N];
//Queue OutputQueues[N];
Queue InputQueue[N];
Queue OutputQueue[N];

void init_simulation() {
    for (int a = 0; a < N; a++) {
        OutQueues_current[a] = 0;
        Congestion_Size[a] = 0;
    }
}

int sum_elements_array(int array[]) {
    int sum = 0;
    for (int a = 0; a < N; a++) {
        sum = sum + array[a];
    }
    return sum;
}

int number_of_ports = 0;

int main(int argc, char** argv) {//get arguments from command line, the name of the simulation text file
  //read the file, print the input ports contents

    int portnumber = 0;
    int destination = 0;
    //char oper;
    string expression;
    string geninput;
    ifstream input_file;
    if (argc != 2) { cout << "Type a file name. " << endl << argv[1] << endl; exit(0); }
    input_file.open(argv[1]);
    if (input_file.is_open() == false) { cout << "Could not read file: " << endl << argv[1] << endl; exit(0); }
    string token;
    while (!input_file.eof()) {
        getline(input_file, expression);
        stringstream line(expression);
        if (input_file.eof()) break;
        if (expression[0] == '#') continue;//jump line, this is a line of comments
        if (expression[0] == 'P') {
            getline(line, token, ' ');
            getline(line, token, ' ');
            number_of_ports = atoi(token.c_str());
            //cout << "Found the number of ports to be " << number_of_ports << endl;
            continue;//got the number of ports
        }

        portnumber++;//get data for the next port

        //cout << "Port " << portnumber << ": " << endl;//DEBUG, comment for final version

        while (getline(line, token, ' ')) {
            int destination;
            //destination = stoi(token);//only works with option -std=c++11
            destination = atoi(token.c_str());//use this one if your compiler is not C++11
            if (destination < 0 || destination > number_of_ports || number_of_ports < portnumber) { cout << "ERROR in the format of the text file" << endl; exit(0); }

            InputQueue[portnumber - 1].Join(destination);//How is each line seperated? By using portnumber as the array number, also flexible because if there is more than three ports it doesn't matter

           // cout << "destination " << destination << endl;//DEBUG, comment for final version
        }
        int sumofinputpackets = 0;
        sumofinputpackets = sumofinputpackets + InputQueue[portnumber - 1].qSize();
       // cout << "Input packets at input queue for port " << portnumber << " = " << sumofinputpackets << endl;//DEBUG, comment for final version
        //cout << "if this value is still zero, it is because you did not implement the queues yet..." << endl;//DEBUG, comment for final version
    }
    //now carry on with the simulation 
    //cout << endl << "Start of the simulation, press a key " << endl << endl;//DEBUG, comment for final version
   // getline(cin, geninput);// pause //DEBUG, comment for final version
    init_simulation();
    unsigned long int clock = 0;
    unsigned long int currentsum = 999999999; // sum_elements_array(OutQueues_current);
    unsigned long int maxSum = 0;
    portnumber = 0;

    while (currentsum > 0) {
       // cout << "Input portnumber " << portnumber + 1 << endl;//DEBUG, comment for final version
       
       /* printf("\nQueues array InputArray:\n");//DEBUG
        InputQueue[portnumber].Print();
        printf("\n");
        */
        if (InputQueue[portnumber].isEmpty() == false) {
           OutputQueue[InputQueue[portnumber].Front() - 1].Join(InputQueue[portnumber].Front());
           InputQueue[portnumber].Leave();
           //cout << "Time t=" << clock << ": port " << portnumber << " transfers a packet " << InputQueue[portnumber].Front() << " to port " << InputQueue[portnumber].Front() << endl;//DEBUG
        }
        
        for (int i = 0; i < number_of_ports; i++) {
            OutQueues_current[i] = OutputQueue[i].qSize();//qSize is returning null because the current size of the outputQ for the current portnumber is null.
        }
       
        currentsum = sum_elements_array(OutQueues_current);

        portnumber++;
        if (portnumber > (number_of_ports - 1)) portnumber = 0;

        clock++;

        if (clock % (TIMEDELAY * number_of_ports) == 0 && clock != 0) { //DO NOT MODIFY THIS LINE!
          //  cout << "Packets can leave the output queues at " << clock << " microsec " << endl;//DEBUG, comment for final version
            for (int a = 0; a < number_of_ports; a++) {
                OutputQueue[a].Leave();
            }
        }

        for (int i = 0; i < number_of_ports; i++) {
            OutQueues_current[i] = OutputQueue[i].qSize();//qSize is returning null because the current size of the outputQ for the current portnumber is null.
        }
        //OutQueues_current[portnumber] = OutputQueue[portnumber].qSize();//i want to have OutQueues Current to be reading ALL output queues in the array, not just the current port.
        currentsum = sum_elements_array(OutQueues_current);

        //if (maxSum <= currentsum) { maxSum = currentsum; }
       // else break;
       
       /* printf("\nQueues array OutputArray:\n");//DEBUG REMOVE
        OutputQueue[portnumber - 1].Print();
        printf("\n");
        */
       // for (int a = 0; a < number_of_ports; a++) {//DEBUG
       ////     printf("\nCongestion Size %i || %i\n",a, Congestion_Size[a]);
        //}

        //compute the current state of the output queues
        //cout << "Current sum: " << currentsum << endl;//DEBUG, comment for final version
        //cout << "Maxsum: " << maxSum << endl;//DEBUG
        
        //clock++;
        if (currentsum > sum_elements_array(Congestion_Size)) {//DEBUG
            for (int a = 0; a < number_of_ports; a++) {
                Congestion_Size[a] = OutQueues_current[a];
            }
        }
    }

    //FINAL PRINTOUT, remember to comment out all the other debugging printouts above 
    for (int a = 0; a < number_of_ports; a++) {
        cout << "output port " << a + 1 << ": " << Congestion_Size[a] << " packets" << endl;
    }
}
