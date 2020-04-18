// Module:		Matrix.h
// Author:		Miguel Antonio Logarta
// Date:		April 17, 2020
// Purpose:		Header file for Matrix class
//				Bi-directional linked list

#pragma once
class Matrix
{
public:
	// Constructor
	Matrix(string, string, string, string, string);

	// Accessors
	TCHAR* GetName();
	TCHAR* GetDec();
	TCHAR* GetHex();
	TCHAR* GetOct();
	TCHAR* GetBin();

	// Link
	void SetNext(Matrix*);			// Set Next
	void SetPrev(Matrix*);			// Set Prev
	Matrix* GetNext();				// Return Next
	Matrix* GetPrev();				// Return Prev

private:
	// Stored data

	TCHAR szName[TCHAR_SIZE];
	TCHAR szDec[TCHAR_SIZE];
	TCHAR szHex[TCHAR_SIZE];
	TCHAR szOct[TCHAR_SIZE];
	TCHAR szBin[TCHAR_SIZE];

	Matrix* Next;					// Link to the next node
	Matrix* Prev;					// Link to the previous node
};

