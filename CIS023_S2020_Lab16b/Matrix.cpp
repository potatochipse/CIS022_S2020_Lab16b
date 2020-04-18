// Module:		Matrix.cpp
// Author:		Miguel Antonio Logarta
// Date:		April 17, 2020
// Purpose:		Implementation file for Matrix class
//				Bi-directional linked list

#include "framework.h"
#include "CIS023_S2020_Lab16b.h"

Matrix::Matrix(string strName, string strDec, string strHex, string strOct, string strBin)
{
	// Convert the strings to TCHARS and store them
	StringtoTCHAR(&strName, szName);		// Convert Name
	StringtoTCHAR(&strDec, szDec);			// Convert Decimal
	StringtoTCHAR(&strHex, szHex);			// Convert Hexadecimal
	StringtoTCHAR(&strOct, szOct);			// Convert Octaldecimal
	StringtoTCHAR(&strBin, szBin);			// Convert Binary
}

// Accessors
TCHAR* Matrix::GetName()
{
	return szName;
}

TCHAR* Matrix::GetDec()
{
	return szDec;
}

TCHAR* Matrix::GetHex()
{
	return szHex;
}

TCHAR* Matrix::GetOct()
{
	return szOct;
}

TCHAR* Matrix::GetBin()
{
	return szBin;
}

// Set the address of the next node
void Matrix::SetNext(Matrix* node)
{
	Next = node;
}

// Set the address of the previous node
void Matrix::SetPrev(Matrix* node)
{
	Prev = node;
}

// Get the address to the next node
Matrix* Matrix::GetNext()
{
	return Next;
}

// Get the address to the previous node
Matrix* Matrix::GetPrev()
{
	return Prev;
}
