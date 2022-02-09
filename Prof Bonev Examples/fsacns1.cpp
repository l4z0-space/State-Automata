//
// file fsacns1.cpp
//
// This is a FSA simulator - acceptor of integer unsigned constants
//  endless cycle while( 1 )  by SB
//
#include <stdio.h>
#include <ctype.h>
#include <conio.h>

// FSA internal states
#define  Q_0        01
#define  Q_1        02
#define  Qf_accept  03
#define  Qf_error   04

// horizontal and vertical indexes for the control table
//  					              0          1               2
//                                        Q_0             Q_1
//    0                        -55        -55             -55
//    1    digit               -55        Q_1             Q_1
//    2    end_delim   #       -55        Qf_error        Qf_accept
//    3    Any other char      -55        Qf_error        Qf_error
//
#define    Digit        01
#define    EndDelim     02
#define    OtherChar    03

int iMove(int iOldState, int iInpChar);// transition from a state to a state on input char

void main()
{
 char line[80], *ptr, *qtr;
 int  iCrntInputChar,  iCrntState,  iNewState;

// int a=-5;
 printf("\n FSA simulator - acceptor of integer unsigned constants\n\n\n");
 printf("\n Enter string to be scanned and checked as a valid contant:");
 while ( (ptr = gets(line)) != NULL)
 {
	qtr=ptr;	while (*qtr != '\0') qtr++; *qtr='#';	qtr++; *qtr='\0';
	ptr--;

	ptr++;  while (isspace(*ptr)) ptr++;    // get new input character
	if(isdigit(*ptr))                       iCrntInputChar = Digit;
			 else         if(*ptr == '#')     iCrntInputChar = EndDelim;
											 else     iCrntInputChar = OtherChar;

	iCrntState = Q_0;

	while (1)    // endless loop
	{
	 iNewState = iMove(iCrntState, iCrntInputChar);

	 printf("\nTransition from  %d state to  %d state on  '%c'  InputChar",iCrntState,iNewState,*ptr);
	 switch (iNewState)
	 {
	  case  Q_0:	 break;

	  case  Q_1:
																  iCrntState = iNewState;

							 ptr++;  while (isspace(*ptr)) ptr++; // get new character
							 if(isdigit(*ptr))           iCrntInputChar = Digit;
								else 	 if(*ptr == '#')    iCrntInputChar = EndDelim;
											 else            iCrntInputChar = OtherChar;
							 break;

	  case  Qf_accept: printf("\n\n String %s accepted as a valid constant.",line);
							 break;

	  case  Qf_error: printf("\n\n String %s rejected as invalid constant.",line);
							break;

	  default:        break;

	 };    // end of switch statement
	 if (iNewState==Qf_accept || iNewState==Qf_error) break; // leave while(1) loop
	}      // end of while(1) loop
	printf("\n\n\n");
	printf("\nEnter new string to be scanned and checked or CTRL/Z to end:");
 }        // end of while (ptr = gets(line) != NULL)
}         // end of main()

int iMove(int iOldState, int iInpChar) // transition from a state to a state on input char
{
  int iRow, iCol, iNewState;
  // FSA accepting identifiers control table
  int iCtrlTab[4][3] =
							{
								 { -55,   -55,        -55       },
								 { -55,   Q_1,        Q_1       },
								 { -55,   Qf_error,   Qf_accept },
								 { -55,   Qf_error,   Qf_error  },
							};
				  iRow = iInpChar;
				  iCol = iOldState;
  iNewState = iCtrlTab[iRow][iCol];
  return iNewState;
}
