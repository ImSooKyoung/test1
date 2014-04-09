#include <cstdlib>
#include <fstream>
#include <iostream>
#include <Windows.h>
#include <time.h>
using namespace std;

#define	MAX 1000

void PrintLine( int Y, char *cFormat, ... )
{
	COORD Pos = {0, Y};		DWORD cCharsWritten;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
	GetConsoleScreenBufferInfo( GetStdHandle(STD_OUTPUT_HANDLE), &csbi );
	FillConsoleOutputCharacter(GetStdHandle(STD_OUTPUT_HANDLE), (TCHAR) ' ', csbi.dwSize.X, Pos, &cCharsWritten );
   
	static char buffer[1024];
	va_list	vlList;
	va_start( vlList, cFormat );
	_vsnprintf( buffer, 1024, cFormat, vlList );
	printf( buffer );
	va_end( vlList );
}

int Selection(int *selec){
	int num, numID;
	int	iTick = GetTickCount();

	for(int i=MAX; i>0; i--){
		num = selec[0];
		numID = 0;

		for (int j = 0 ; j < i ; j++){
			if(selec[j] > num){
				num = selec[j];
				numID = j;
			}
		}
		selec[numID] = selec[i-1];
		selec[i-1] = num;
	}
	
	return GetTickCount() - iTick;
}

int main()
{
	int	selec[MAX];
	int iTime;

	ofstream fr;
	fr.open("randomData.txt");

	srand((unsigned int)time(NULL));
	for(int i=0; i<MAX; i++ ){
		selec[i] = rand();
		fr<<selec[i]<<endl;
	}
	fr.close();

	PrintLine( 0, "Selection Sort  [Data::%8d] -----> [Time(ms)::Calc...]\n", MAX );
	iTime = Selection(selec);
	PrintLine( 0, "Selection Sort  [Data::%8d] -----> [Time(ms)::%8d]\n", MAX, iTime );

	ofstream fs;
	fs.open("selectionSort.txt");

	for(int i=0; i<MAX; i++ ){
		fs<<selec[i]<<endl;
	}
	fs.close();

	return 0;
}

