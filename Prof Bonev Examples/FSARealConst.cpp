//
// file fsaRealConst.cpp
//
// This is a FSA simulator - acceptor of real constants (+|-|e)D+.D*
//  endless cycle while( 1 )  by SB
//

#include <string>
#include <iostream>
using namespace std;

// FSA internal states
#define  Q_0        01
#define  Q_1_C      02
#define  Q_2_S      03
#define  Q_3_F      04
#define  Qf_accept  05
#define  Qf_error   06

char *states[]={"QFictive",
				"Q0       ", "Q1_C     " , "Q2_S     ", "Q3_F     ",
				"Qf_ACCEPT", "Qf_ERROR " };

// horizontal and vertical indexes for the control table
//							0		1		2			3			4
//									Q_0		Q_1_C		Q_2_S		Q_3_F
//    0                     -55		-55		-55			-55			-55

//    1    digit            -55		Q_1_C	Q_1_C		Q_1_C		Q_3_F
//    2    plus				-55		Q_2_S	Q_Err		Q_Err		Q_Err
//    3    minus			-55		Q_2_S	Q_Err		Q_Err		Q_Err
//	  4    dot				-55		Q_Err	Q_3_F		Q_Err		Q_Err
//    5    end_delim   #    -55		Q_Err	Q_Err		Q_Err		Qf_accept
//    6    Any other char   -55     Q_Err	Q_Err		Q_Err		Q_Err
//
#define    Digit        01
#define    Plus         02
#define    Minus        03
#define    Dot	        04
#define    EndDelim     05
#define    OtherChar    06

char *inpsymbols[]={"Fictive","Dig 0-9","+ Sign ","- Sign ",". Dot  ","# End  ","Other  "};

// FSA accepting real constants (+|-|e)D+.D* control table
  int iCtrlTab[7][5] =
				{
				 { -55,   -55,        -55,		-55,		-55,     },	// fictive
				 { -55,   Q_1_C,      Q_1_C,	Q_1_C,		Q_3_F    },	// dig
				 { -55,   Q_2_S,	  Qf_error, Qf_error,	Qf_error },	// plus
				 { -55,   Q_2_S,	  Qf_error, Qf_error,	Qf_error },	// minus
				 { -55,   Qf_error,   Q_3_F,	Qf_error,	Qf_error },	// dot .
				 { -55,   Qf_error,   Qf_error, Qf_error,	Qf_accept},	// enddelim #
				 { -55,   Qf_error,   Qf_error, Qf_error,   Qf_error },	// other
				};

int iMove(int iOldState, int iInpChar);// transition from a state to a state on input char

void main()
{
 char line[80], *ptr, *qtr;
 int  iCrntInputChar,  iCrntState,  iNewState;

 cout << "\n FSA - recognizer of real signed constants described with LG and/or RE";
 cout << "\n Linear Grammar					Regular Expression";
 cout << "\n  C -> C dig					 (+|-|e)D+.D*";
 cout << "\n  C -> S dig";
 cout << "\n  C -> dig";
 cout << "\n  F -> C dot(.)";
 cout << "\n  F -> F dig";
 cout << "\n  S -> +";
 cout << "\n  S -> -\n";

 cout << "\n FSA transition table";
 cout << "\n\t\t  "<< states[1] <<"     "<< states[2] <<"     "<< states[3] <<"     "<< states[4] <<"   ";
 for (int i=1; i<=6; i++)
 {
	 cout << "\n" << inpsymbols[i] << "\t\t";
	 for (int j=1; j<=4; j++) cout << states[iCtrlTab[i][j]]<< "     ";
 }


 cout << "\n\n\n Enter string to be scanned and checked as a valid constant:";

 cin.getline( line, '\n');
 while(!cin.eof())
 {
	ptr = line;
	qtr=ptr;	while (*qtr != '\0') qtr++; *qtr='#';	qtr++; *qtr='\0';
	ptr--;

	ptr++;  while (isspace(*ptr)) ptr++;    // get new input character
	if(isdigit(*ptr))                iCrntInputChar = Digit;
		else         if(*ptr == '+')     iCrntInputChar = Plus;
			else         if(*ptr == '-')     iCrntInputChar = Minus;
				else         if(*ptr == '.')     iCrntInputChar = Dot;
					 else         if(*ptr == '#')     iCrntInputChar = EndDelim;
											 else     iCrntInputChar = OtherChar;

	iCrntState = Q_0;

	while (1)    // endless loop
	{
	 iNewState = iMove(iCrntState, iCrntInputChar);

	 cout <<"\nTransition from state "<<states[iCrntState]<<" to state "<<states[iNewState]<<" on '"<<*ptr<<"' InputChar";
	 switch (iNewState)
	 {
	  case  Q_0:	 break;

	  case  Q_1_C:
	  case  Q_2_S:
	  case  Q_3_F:
				iCrntState = iNewState;

				ptr++;  while (isspace(*ptr)) ptr++; // get new character
				if(isdigit(*ptr))           iCrntInputChar = Digit;
				  else  if(*ptr == '+')     iCrntInputChar = Plus;
						  else  if(*ptr == '-')     iCrntInputChar = Minus;
								  else  if(*ptr == '.')     iCrntInputChar = Dot;
										  else  if(*ptr == '#')    iCrntInputChar = EndDelim;
												  else            iCrntInputChar = OtherChar;
				break;

	  case  Qf_accept: cout << endl<<endl<<line<< " string accepted as a valid constant.";
							 break;

	  case  Qf_error: cout << endl<<endl<<line<<" string rejected as invalid constant.";
							break;

	  default:        break;

	 };    // end of switch statement
	 if (iNewState==Qf_accept || iNewState==Qf_error) break; // leave while(1) loop

	

	}      // end of while(1) loop
	cout << "\n\n\n";
	cout << "\nEnter new string to be scanned and checked or CTRL/Z to quit:";
	cin.getline( line, '\n');
 }        // end of while (ptr = gets(line) != NULL)

 system("pause");
}         // end of main()

int iMove(int iOldState, int iInpChar) // transition from a state to a state on input char
{
  int iRow, iCol, iNewState;
  
				  iRow = iInpChar;
				  iCol = iOldState;
  iNewState = iCtrlTab[iRow][iCol];
  return iNewState;
}