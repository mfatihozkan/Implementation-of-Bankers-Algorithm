//*********************************************************
//
// Mehmet Ozkan
// Operating Systems
// Project #4  Implementation of Banker's Algorithm 
// November 29, 2017
// Instructor: Dr. Ajay K. Katangur
//*********************************************************
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <vector>

using namespace std;
bool issafe(vector<int>& ,vector<vector <int> >& , vector<vector <int> >&);
bool isgranted(vector<int>& ,vector<int>&,vector<vector <int> >&, int&);

//Global Variables
int numofpro, numofres; //number of process and number of researches
int main(int argc, char *argv[])
{

 vector<vector<int> > Allocation; // Allocation matrix
 vector<vector<int> > Max; // Max matrix
 vector<vector<int> > Need; // Need matrix
 
 vector<int> Available, Request; // Available and Request vectors
 vector<int> data, data2; // temporary vectors
 int number; // decleration of number variables from the input file 
 int ProRequester; // decleration of order of process requester 
 string element; // decleration of element in link array
 ifstream inputfile; // decleration of input file
 char link[1001]; // decleration of link array
 
 for(int i=0; i <= argc; i++)
	{
   if(argc >= 3 || argc < 2 )
   {
       cerr <<"You should write only one argument after ./banker\n"; 
	   cerr<<"and that argument should be input text file directory!\n";
      
       exit(-1);
   }
	}
 inputfile.open(argv[1], ios::in);
 
 if(!(inputfile.is_open()))
 {
 cerr<<"ERROR, FILE CAN NOT READ"<<endl;
 exit(EXIT_FAILURE);
 }
 
 if(inputfile.peek()!='\n')
 {
 // Reading the number of processes	
 inputfile>>numofpro;
 // Reading the number of resources
 inputfile>>numofres;
 }

//Initializing the Matrix by numberofpro*numberofres
for(int j = 0; j < numofres; j++){
	{
	data.push_back(0);
    }
}
 for(int i = 0; i < numofpro; i++)
 {
	 Need.push_back(data);
 }

//**** Saving the variables into Allocation Matrix////	  
 for(int i = 0; i < numofpro; i++)
{
    for(int j = 0; j < numofres; j++)
    {
	inputfile>>number;
	data2.push_back(number);

    }
	
	 Allocation.push_back(data2);
	
	for(int j=0; j< numofres; j++)
	{
	data2.pop_back();	
	}
	  
}
//**** Saving the variables into Max Matrix////	  
 for(int i = 0; i < numofpro; i++)
 {
    for(int j = 0; j < numofres; j++)
    {
	inputfile>>number;
	data2.push_back(number);
    }
	
	 Max.push_back(data2); 
	  
	for(int j=0; j< numofres; j++)
	{
	data2.pop_back();	
	}
 }
 
//**** Saving the variables into Available Vector////	  
 for(int j = 0; j < numofres; j++)
    {
	inputfile>>number;
	Available.push_back(number);
    }
//****Initilizing Request vector to store values
 for(int j = 0; j < numofres; j++)
    {
	
	Request.push_back(0);
    }
 
//****Saving the characters of Request vector into link array
 inputfile>> link;
 element +=link[0];

// Saving the the first(index 0) character of the Request vector as a Request number 
 ProRequester = atoi(element.c_str());
 element.clear();

// Ignore the index 1 character which is ':'
// Store remaining of the elements in link array to the Request vector

 element +=link[2];
 Request[0]=atoi(element.c_str());
 element.clear();

// Save the variables from input file to Request vector
 for(int i=1; i<numofres; i++)
 {
	 inputfile >> Request.at(i);
 }
 
// Calculate Need matrix 
 for(int i = 0; i < numofpro; i++)
 {
    for(int j = 0; j < numofres; j++)
    {
		Need[i][j]=Max[i][j]-Allocation[i][j];
	}
 }

//****DISPLAYING PART****//
	 cout<<endl;
	 cout<<"There are "<<numofpro<<" processes in the system."<<endl<<endl;
	 cout<<"There are "<<numofres<<" resource types."<<endl<<endl;
	 
 // Display Allocation Matrix 
	 cout<<"The Allocation Matrix is..."<<endl;
	 cout<<"  A B C D";
	 for(int i = 0; i < numofpro; i++)
	 {
		 cout<<"\n"<<i<<":";
		for(int j = 0; j < numofres; j++)
		{
			cout<<Allocation[i][j]<<" ";
		}
	 }
	  cout<<endl;
 
// Display Max Matrix 
	cout<<"\nThe Max Matrix is..."<<endl;
	cout<<"  A B C D";
	for(int i = 0; i < numofpro; i++)
	{
	cout<<"\n"<<i<<":";
    for(int j = 0; j < numofres; j++)
    {
		cout<<Max[i][j]<<" ";
	}
	}
	cout<<endl;
 
// Display Need Matrix 
	cout<<"\nThe Need Matrix is..."<<endl;
	cout<<"  A B C D";
	for(int i = 0; i < numofpro; i++)
	{
	cout<<"\n"<<i<<":";
    for(int j = 0; j < numofres; j++)
    {
		cout<<Need[i][j]<<" ";
	}
	}
	cout<<endl;

// Display Available Vector
	cout<<"\nThe Available Vector is..."<<endl;
	cout<<"A B C D"<<endl;
	for(int j = 0; j < numofres; j++)
    {
	cout<<Available[j]<<" ";
    }
	cout<<endl;


// Display If the System is in safe state
	if(issafe(Available,Allocation,Need))

	{
		cout<<"\nTHE SYSTEM IS IN A SAFE STATE!"<<endl;
		cout<<endl;
		cout<<"\nThe Request Vector is....!"<<endl;
		cout<<"  A B C D"<<endl;
		cout<<link[0]<<":";
	   for(int j = 0; j < numofres; j++)
		{
		cout<<Request[j]<<" ";
		}
		cout<<endl;

// Display If the Request can be granted
		
	if(isgranted(Request,Available,Need,ProRequester))
	{
		cout<<"\nTHE REQUEST CAN BE GRANTED!"<<endl<<endl;
		cout<<"\nThe Available Vector is..."<<endl;
		cout<<"A B C D"<<endl;
		for(int j = 0; j < numofres; j++)
		{
		cout<<Available[j]<<" ";
		}
		cout<<endl;
	}

	else {
		cout<<"\nTHE REQUEST CAN NOT BE GRANTED!"<<endl;
		cout<<endl;
		}
	}
	 
	 else 
	 {
	  cout<<"\nTHE SYSTEM IS NOT IN A SAFE STATE!"<<endl;
	  cout<<"\nThe Request Vector is....!"<<endl;
	  cout<<"  A B C D"<<endl;
	  cout<<link[0]<<":";
	  for(int j = 0; j < numofres; j++)
		{
		cout<<Request[j]<<" ";
		}
		cout<<endl;
	 }
 
 return 0;
}
//********************************************************************
//
// Safe State Checking Function
//
// This function determines if the system in safe state
//
// Return Value
// ------------
// bool                 True/False if the system is in safe state
//
// Value Parameters
// ----------------
// Available			vector<int>  			Available matrix reference
// Allocation			vector<vector<int> > 	Allocation matrix reference
// Need					vector<vector<int> >	Need matrix reference
//
// 
// Local Variables
// ---------------
// count     	  int      Limit for checking a prime number
// processSeq[]   int      Process sequence array
// flag        	  bool     true or false if system is in safe state
// Finish[]		  bool	   true or false if a process is finished its execution
 
bool issafe(vector<int> &Available,vector<vector<int> > &Allocation, vector<vector<int> >&Need)
{
	// Local Variables
	int count = 0;
	bool flag;
	bool Finish[numofpro] = {0};
	int ProcessSeq[numofpro];
	
	// Temporary vector to save available matrix
    vector<int> tempvec(numofres);
	
	// Copy available matrix to temporary vector
	for(int j = 0; j < numofres; j++)
	{
		tempvec[j]=Available[j];
	}
	  
 
    // While all processes are not finished, system is not in safe state.
   
    while (count < numofpro)
    {
        int j;
		flag = false;
        for (int i = 0; i < numofpro; i++)
        {
        // Check if a process is finished,
        // if it is not, check next condition
            if (Finish[i] == 0)
            {
                // Check if Need matrix is less than tempvec
                // for each process
                for (j = 0; j < numofres; j++)
                    if (Need[i][j] > tempvec[j])
                        break;
 
                // Check if all need matrix of each process is satisfied
                if (j == numofres)
                {
                    // Add the allocated resources of
                    // current process to the tempvec matrix
                    
                    for (int j = 0 ; j < numofres ; j++)
                       tempvec[j] += Allocation[i][j];
 
                    // Add this current process to the safe sequence
                    ProcessSeq[count++] = i;
 
                    // Mark this process as finished
                    Finish[i] = 1;
 
                    flag = true;
                }
            }
        }
 
        // If next process is not in safe sequence
        if (flag == false)
        {
         return false;
        }
    }
  
    return true;
	
}

//********************************************************************
//
// Requester Vector Granted Checking Function
//
// This function determines if the request vector is granted
//
// Return Value
// ------------
// bool                 True/False if the request vector is granted
//
// Value Parameters
// ----------------
// Available			vector<int>  			Available matrix reference
// Request				vector<int> 			Request vector
// Need					vector<vector<int> >	Need matrix reference
// ProRequester			int						Process requester index
// 
// Local Variables
// ---------------
// _flag        	  bool     true or false if the request vector is granted

bool isgranted(vector<int> &Request, vector<int> &Available, vector<vector<int> >&Need,int &ProRequester)
{
	bool _flag;
	
	
	for(int j=0; j<numofres; j++)
	{
		//If request researches are more than need researches in requester process
		if(Request[j] > Need[ProRequester][j])
		{
			return false;
		}
		//If request researches are more  than available
		else if(Request[j] > Available[j])
		{
			return false;
			
		}
		
		//If request researches are less than available
		else if(Request[j] <= Available[j])
		{
			_flag=true;
			Available[j] -= Request[j];
			
		}
		
	}
	
	
	return true;
}
