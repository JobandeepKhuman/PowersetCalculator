//The goal of the powerset program is to calculate the powerset of a valid set
//provided by the user. The set input by the user is defined by the number
//of elements in it and what each element is. A valid set will have less than 25
//elements in it. This is ensured by checking that the setLength input by the user
//is an integer, using the typeChecker function, and then using an if statement to
//check the setLengthInput is less than 25. If either of these conditions fail the
//user will be prompted for another input and this process continues until a valid
//serLength is entered.  Once a valid setLength is entered the user will be
//to enter the elements of the set 1 at a time and ff a duplicate element is input
//by the user it is not entered into the set. This continues until the set contains
//a number of elements equal to setLength. After this the powerset of the set is
//calculated and as each element of each subset of the set input is ouput as it
//is calculated.

//Importing neccessary libraries
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Function to test if the user entered an integer
//Recieves a pointer pointing to the first element of the string and the
//length of the string as input parameters
//Returns 0 if the user does not enter an integer and 1 if the user does enter an integer
int typeChecker(char *input, int inputLength){
  //Initialising variables
  int counter=0;
  int test=1;
  char n='a';
  //Looping through each character of the string input and checking if it is a numerical character
  for(counter=0;counter<inputLength;counter++){
    //the pointer variable 'n' is created to make the following if statement more easily readable
    n=*(input+counter);
    if(n!='0'& n!='1'& n!='2'& n!='3'& n!='4'& n!='5'& n!='6'& n!='7'& n!='8'& n!='9'){
      test=0;//Setting the test value to 0 if the user does not enter an integer
    }
  }
  return test;//retturning the result of the function
}



//The main function which will calculate the powerset and handle error cases
//Takes the setLength and each element of the set as input from the user
//Calls the typeChecker function as part of the validation of the setLength input
//by the user.
//Outputs the powerset to stdout
int main(int argc, char *argv[]){
  //Initialising variables
  int counter,internalCounter,i,j,test,setLength,duplicate=0;
  int elementSize=33;//maximum length of an individual element
  char setLengthInput[2];

  //Asking for user input until an integer less than 25 is entered
  while(test!=1){
    //Recieving set cardinality from the user
    printf("Please enter the carinality of your set: \n");
    scanf("%s", setLengthInput);
    //checking if setLengthInput is an integer by passing it into the typeChecker function
    test=typeChecker(setLengthInput,strlen(setLengthInput));
    if(test==0){
      printf("The set cardinality must be an integer less than 24\n");
    }
    //If the setLengthInput is an integer, checking that it is less than 25
    else if(24<atoi(setLengthInput)){
      printf("The set cardinality must be an integer less than 24\n");
      test=0;
    }
  }

  //Once a valid setLengthInput is entered, converting the input from a string to
  //an integer data type
  setLength=atoi(setLengthInput);
  //Calculating the cardinality of the powerset based on the cardinality of the set
  int powersetLength = pow(2, setLength);
  //Initialising the set and element arrays
  char set[setLength][elementSize];//2D array of chars=1D array of strings
  char element[elementSize];//1D array of chars=string

  //Recieving each element of the set from the user
  for(i=0;i<setLength;i++){
    duplicate=0;//0 implies that current element is not a duplicate, 1 implies it is a duplicate
    //Asking for and recieving user input
    printf("Please enter a new element to the set: ");
    scanf("%s", element);
    printf("\n");
    //Looping through all the element currently in the set
    for(j=0;j<setLength;j++){
      //Checking if any of the elements in the set are the same as the element input
      //and hence identifying if a duplicate has been input
      if(strcmp(set[j],element)==0){
        duplicate=1;//Updating variable to signify a duplicate has been input
        printf("That element is invalid, because it has been entered before\n");
        //Decrementing i when a duplicate is entered so that the cardinality of the
        //set once all elements have been input is stil equal to setLengthInput
        i--;
      }
    }
    //Adding the element to the set if it is not a duplicate
    if(duplicate==0){
      strcpy(set[i], element);
    }
  }

  //Outputting the emptySet because it is a subset of all sets
  printf("emptySet\n");
  //looping through each subset of the set input, except the empty set
  for(counter=1;counter<powersetLength;counter++){
    //looping through each element of the current subset subset
    for(internalCounter=0; internalCounter<setLength; internalCounter++){
      //Checking if the current element has it's corresponding bit set to 1
      //When counting from 0 to powersetLength, using a bitshift to make a mask
      //then performing a logical AND between the mask and the counter in order
      //to isolate the elements that need to be output
      if(counter & (1<<internalCounter)){
        //Outputting each element of the current subset
        printf("%s,",set[internalCounter]);
      }
    }
    //Starting a new line once the entire subset has been output
    printf("\n");
  }
}
