//
// This is a FSA simulator - acceptor of real constants (+|-|e)D+.D*
//  implementation based on Aho-Sethi-Ullman algorithm
//
#include <string>
#include <iostream>
using namespace std;

struct State { string s; int num; };

// ColName[] contents scheme = { xx, Q0, ... Qn, QERR, QFinal }
State ColName[51] = { { "Fictive", -55 } }; int ColIndex;

struct InpSymb { string s; int num; };
InpSymb RowName[51] = { { "Fictive", -55 } }; int RowIndex;

State TT[51][51]; // Transition table

int iMove(int iOldState, int iInpChar);// transition from a state to a state on input char

void main()
{
 char line[80], *ptr, *qtr;
 int  iCrntInputChar,  iCrntState,  iNewState;

 cout << "\n Table driven FSA simulator \n";
 cout << "\n Section Internal states processing";
 cout << "\nEnter number of Operative/Working Q0...Qn only Internal States:";
 cin >> ColIndex;
 cout << "\n Enter states as strings separated by space\n";
 for (int i=1; i<=ColIndex; i++)
    {
		cin >> ColName[i].s;	ColName[i].num = i;
	}
 State Error, Accept;
 cout << "\n Enter Error state as string:";  cin >> Error.s;
 ColName[ColIndex+1].s = Error.s;  ColName[ColIndex+1].num = ColIndex+1;
 cout << "\n Enter Final/Accept state as string:";  cin >> Accept.s;
 ColName[ColIndex+2].s = Accept.s;  ColName[ColIndex+2].num = ColIndex+2;
    
 cout << "\nTest input of Internal States";
 for (int i=1; i<=ColIndex + 2; i++)
	{
		cout << endl << ColName[i].s << "\t\t" << ColName[i].num;
	}
 system("pause");
 
 cout << "\n\n\n Section Input Symbols processing";
 cout << "\nEnter number of Input Symbols:"; cin >> RowIndex;
 cout << "\n Enter Input Symbols as strings separated by space\n";
 for (int i=1; i<=RowIndex; i++)
	{
		cin >> RowName[i].s;	RowName[i].num = i;
	}
 // OTHER category set of input symbols always last coded
 cout << "\nTest input of Input Symbols";
 for (int i=1; i<=RowIndex; i++)
	{
		cout << endl << RowName[i].s << "\t\t" << RowName[i].num;
	}
 system("pause");

 cout << "\n Section Transition table processing";
 for (int i=0; i<=50; i++)
	for (int j=0; j<=50; j++)
	  {  
		TT[i][j].s = "Fictive";		TT[i][j].num = -55;
	  }
 cout << "\nTest input of TT Transition Table\n\t   ";
 for (int i=1; i<=ColIndex; i++) cout << ColName[i].s<< "    \t";
 cout << "\n---------------------------------------------------";
 for (int i=1; i<=RowIndex; i++)
	{
	 cout <<endl<< RowName[i].s<<"\t| ";
	 for (int j=1; j<=ColIndex; j++)
		{ 
		cout<< TT[i][j].s<<"  "<<TT[i][j].num<<"  \t";
		}
	}
 system("pause");

 cout << "\nZarejdane na TT Transition Table\n";
 for (int i=1; i<=RowIndex; i++)
	{
	 cout <<  "\nData for row " << RowName[i].s<<":";
	 string pom;
	 for (int j=1; j<=ColIndex; j++)
		{ 
		 cin >> pom; 
		 TT[i][j].s = pom;
		 TT[i][j].num = -1;
		 for (int k =1; k<=ColIndex+2; k++)
			if (ColName[k].s == pom ) { TT[i][j].num = ColName[k].num; break;}
		} 
	}
 cout << "\nTest input of TT Transition Table\n\t   ";
 for (int i=1; i<=ColIndex; i++)	cout << ColName[i].s<< "    \t";
 cout << "\n------------------------------------------------------";
 for (int i=1; i<=RowIndex; i++)
	{
	 cout <<endl<< RowName[i].s<<"\t| ";
	 for (int j=1; j<=ColIndex; j++)
		{ 
		 cout<< TT[i][j].s<<"  "<<TT[i][j].num<<"  \t";
		}
	}
 system("pause");
 
 cin.getline(line, '\n');
 cout << "\n Enter string to scan and recognize:";
 cin.getline( line, '\n');
 while(!cin.eof())
 {
	ptr = line;
	qtr=ptr;	while (*qtr != '\0') qtr++; *qtr='#';	qtr++; *qtr='\0';
	ptr--;
	ptr++;  while (isspace(*ptr)) ptr++;    // get new input character
	if(isdigit(*ptr))	iCrntInputChar = RowName[1].num;//Digit;
	else {
			iCrntInputChar = RowName[RowIndex].num; // input symbol Other
			for (int k =2; k<RowIndex; k++)
			{
				if (*ptr == (RowName[k].s).at(0) ) { iCrntInputChar = RowName[k].num; break;}
			}
		}

	//case invalid input character category "OTHER"
	if (iCrntInputChar==RowName[RowIndex].num) // invalid input char
	{
	  cout << endl<<endl<<line<<" string rejected, erroneous starting input char. Try again.";
	}
	else { // outer else
			iCrntState = ColName[1].num;  //	iCrntState = Q_0;

	// while ch != EOF
	while (iCrntInputChar != RowName[RowIndex-1].num )   //  ch != '#'
	{
	 iNewState = iMove(iCrntState, iCrntInputChar);
	 cout <<"\nTransition from state "<<ColName[iCrntState].s<<" to state "<<ColName[iNewState].s<<" on '"<<*ptr<<"' InputChar\n";
	 
	 if (iNewState == ColName[ColIndex+1].num) // check for error state
			break; // exit while loop
	 iCrntState = iNewState;

	 ptr++;  while (isspace(*ptr)) ptr++; // get new character
	
	 if(isdigit(*ptr))	iCrntInputChar = RowName[1].num;//Digit;
	 else {
		   iCrntInputChar = RowName[RowIndex].num; // input symbol Other
		   for (int k =2; k<RowIndex; k++)
				if (*ptr == (RowName[k].s).at(0) ) { iCrntInputChar = RowName[k].num; break;}
		  }

	 //case invalid input character category "OTHER", valued RowName[RowIndex]
	 if (iCrntInputChar==RowName[RowIndex].num)
	 {
	  cout << endl<<endl<<line<<" string rejected, erroneous current input char. Try again.";
	  break; // leave while loop
	 }

	}      // end of while loop

if (!(iCrntInputChar==RowName[RowIndex].num)) // not Other char
{
  if(iCrntInputChar == RowName[RowIndex-1].num )   //  ch = '#'
  {
   iNewState = iMove(iCrntState, iCrntInputChar);
   cout <<"\nTransition from state "<<ColName[iCrntState].s<<" to state "<<ColName[iNewState].s<<" on '"<<*ptr<<"' InputChar\n";
  }
	//case  Qf_accept
	if (iNewState==ColName[ColIndex+2].num)  //  QFinal/Accept
	  {
		  cout << endl<<endl<<line<< " string accepted.";
	  }

	//case  Qf_error
	if (iNewState==ColName[ColIndex+1].num)
	  {
		  cout << endl<<endl<<line<<" string rejected.";
	  }
}
	     } // end of outer else

	cout << "\n\n\n\nEnter new string to scan and recognize or CTRL/Z to quit:";
	cin.getline( line, '\n');
 }        // end of while (ptr = gets(line) != NULL)
 system("pause");
}         // end of main()

int iMove(int iOldState, int iInpChar) // transition from a state to a state on input char
{
  int iRow, iCol, iNewState;
  
	iRow = iInpChar;
	iCol = iOldState;
	iNewState = TT[iRow][iCol].num;

  return iNewState;
}