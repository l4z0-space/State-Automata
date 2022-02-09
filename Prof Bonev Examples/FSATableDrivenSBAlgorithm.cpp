//
// file fsaRealcns1.cpp
//
// This is a FSA simulator - acceptor of real constants (+|-|e)D+.D*
//  endless cycle while( 1 )  by SB
//

#include <string>
#include <iostream>
using namespace std;

struct State { string s; int num; };
State ColName[51] = { { "Fictive", -55 } }; int ColIndex;

struct InpSymb { string s; int num; };
InpSymb RowName[51] = { { "Fictive", -55 } }; int RowIndex;

State TT[51][51]; // Transition table

int iMove(int iOldState, int iInpChar);// transition from a state to a state on input char

void main()
{
 char line[80], *ptr, *qtr;
 int  iCrntInputChar,  iCrntState,  iNewState;

 cout << "\n Table driven FSA simulator";

	cout << "\n\n\n Section Internal states processing";
	cout << "\nEnter number of Operative/Working Q0-QN only Internal States:";
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

	cout << "\nTest input of Input Symbols";
	for (int i=1; i<=RowIndex; i++)
	{
		cout << endl << RowName[i].s << "\t\t" << RowName[i].num;
	}
	system("pause");

//State TT[51][51]; // Transition table
	cout << "\n Section Transition table processing";
	for (int i=0; i<=50; i++)
	  for (int j=0; j<=50; j++)
	  {  
		TT[i][j].s = "Fictive";		TT[i][j].num = -55;
	  }
	cout << "\nTest input of TT Transition Table";
cout << endl<< "\t   ";
for (int i=1; i<=ColIndex; i++)	cout << ColName[i].s<< "    \t";
cout << "\n---------------------------------------------";
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
	cout <<endl << "Data for row " << RowName[i].s<<":";
	for (int j=1; j<=ColIndex; j++)
	{ 
		string pom; cin >> pom; 
		TT[i][j].s   = pom;
		TT[i][j].num = -1;
		for (int k =1; k<=ColIndex+2; k++)
			if (ColName[k].s == pom ) { TT[i][j].num = ColName[k].num; break;}
	}
}

cout << "\nTest input of TT Transition Table";
cout << endl<< "\t   " ;
for (int i=1; i<=ColIndex; i++)	cout << ColName[i].s<< "    \t";
cout << "\n---------------------------------------------";
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
/*	if(isdigit(*ptr))                iCrntInputChar = RowName[1].num;//Digit;
		else         if(*ptr == '+')     iCrntInputChar = RowName[2].num;//Plus;
			else         if(*ptr == '-')     iCrntInputChar = RowName[3].num;//Minus;
				else         if(*ptr == '.')     iCrntInputChar = RowName[4].num;//Dot;
					 else         if(*ptr == '#')     iCrntInputChar = RowName[RowIndex-1].num;//EndDelim;
											 else     iCrntInputChar = RowName[RowIndex].num;//OtherChar;
*/
	if(isdigit(*ptr))	iCrntInputChar = RowName[1].num;//Digit;
	else {
			iCrntInputChar = RowName[RowIndex].num;  // Other char
			for (int k=2; k<RowIndex; k++)
			{
				if (*ptr == (RowName[k].s).at(0) ) { iCrntInputChar = RowName[k].num; break;}
			}
		}
	  //case  invalid input character category "OTHER"
	if (iCrntInputChar==RowName[RowIndex].num)
	{
	  cout << endl<<endl<<line<<" string rejected, erroneous starting input char. Try again!";
	}
	else { // outer else

	iCrntState = ColName[1].num;  //	iCrntState = Q_0;
	while (1)    // endless loop
	{
	 iNewState = iMove(iCrntState, iCrntInputChar);
	 cout <<"\nTransition from state "<<ColName[iCrntState].s<<" to state "<<ColName[iNewState].s<<" on '"<<*ptr<<"' InputChar\n";
	 	 	 
	 if (iNewState==ColName[1].num) NULL; //case  Q_0:	 break;
	 else  // inner else
	 {
	  
	if(iNewState==ColName[2].num || iNewState==ColName[3].num || iNewState==ColName[4].num)
	 {
		iCrntState = iNewState;

		ptr++;  while (isspace(*ptr)) ptr++; // get new character
	/*	if(isdigit(*ptr))           iCrntInputChar = RowName[1].num;//digit [0-9]
		  else  if(*ptr == '+')     iCrntInputChar = RowName[2].num;//Plus;
				  else  if(*ptr == '-')     iCrntInputChar = RowName[3].num;//Minus;
						  else  if(*ptr == '.')     iCrntInputChar = RowName[4].num;//Dot;
								  else  if(*ptr == '#')    iCrntInputChar = RowName[RowIndex-1].num;//EndDelim;
										  else            iCrntInputChar = RowName[RowIndex].num;//OtherChar;
									  */

		if(isdigit(*ptr))	iCrntInputChar = RowName[1].num;//Digit;
		else {
			  iCrntInputChar = RowName[RowIndex].num;
			  for (int k=2; k<RowIndex; k++)
				if(*ptr == (RowName[k].s).at(0)) {iCrntInputChar = RowName[k].num; break;}
		}

	 }  // END of  if...
	
	//case  Qf_accept
	if (iNewState==ColName[ColIndex+2].num) // ACCEPT
	{
		cout << endl<<endl<<line<< " string accepted."; break;
	}

	//case  Qf_error
	if (iNewState==ColName[ColIndex+1].num) // ERROR
	{
		cout << endl<<endl<<line<<" string rejected.";  break;
	}
						
	 }  // end of inner else
	 
	 //if (iNewState==Qf_accept || iNewState==Qf_error) break; // leave while(1) loop
if(iNewState==ColName[ColIndex+2].num || iNewState==ColName[ColIndex+1].num) break; // leave while(1) loop
	
	//case  invalid input character category "OTHER"
	if (iCrntInputChar==RowName[RowIndex].num)
	{
	 cout <<endl<<endl<<line<<" string rejected, erroneous current input char. Try again!";
	 break; // leave while(1) loop
	}

	}      // end of while(1) loop
	
	  } // end of outer else
	
	cout << "\n\n\n\nEnter new string to scan and recognize or CTRL/Z to exit:";
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