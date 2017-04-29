// A simple stack program
//source: http://www.infocodify.com/cprog/stack

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"


// display program instructions to user
void instructions( void )
{ 
  puts( "Enter choice:\n"
  "1 to push a value on the stack\n"
  "2 to pop a value off the stack\n"
  "3 to end program" );
} // end function instructions

// insert a node at the stack top
void push( StackNodePtr *topPtr, int info ) 
{ 
  StackNodePtr newPtr; // pointer to new node
  newPtr = malloc( sizeof( StackNode ) );
  // insert the node at stack top
  if ( newPtr != NULL ) 
  {           
    newPtr->data = info;           
    newPtr->nextPtr = *topPtr;     
    *topPtr = newPtr;              
  } // end if                    
  else 
  { // no space available
    printf( "%d not inserted. No memory available.\n", info );
  } // end else
} // end function push


// remove a node from the stack top
int pop( StackNodePtr *topPtr ) 
{ 
  StackNodePtr tempPtr; // temporary node pointer
  int popValue; // node value
  tempPtr = *topPtr;             
  popValue = ( *topPtr )->data;  
  *topPtr = ( *topPtr )->nextPtr;
  free( tempPtr );               

  return popValue;
} // end function pop

// print the stack
void printStack( StackNodePtr currentPtr ) 
{ 
  // if stack is empty
  if ( currentPtr == NULL ) 
  {
    puts( "The stack is empty.\n" );
  } // end if
  else 
  { 
    puts( "The stack is:" );
  // while not the end of the stack
    while ( currentPtr != NULL ) 
    { 
       printf( "%d --> ", currentPtr->data );
       currentPtr = currentPtr->nextPtr;
    } // end while
  
    puts( "NULL\n" );
  } // end else
} // end function printList

// return 1 if the stack is empty, 0 otherwise
int isEmpty( StackNodePtr topPtr )
{ 
  return topPtr == NULL;
} // end function isEmpty

int stackLenght( StackNodePtr topPtr )
{
  int len = 0;
  while(topPtr != NULL)
    {
      len++;
      topPtr = topPtr->nextPtr;
    }

    return len;
}