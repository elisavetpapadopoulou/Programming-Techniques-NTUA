/*
 * ChessBoardArray.cpp
 *
 *  Created on: 8 Apr 2021
 *      Author: elisa
 */

#include <iostream>
#include <exception>
#include <iomanip>
#include <math.h>
using namespace std;

class ChessBoardArray {
protected:
	int *data;
	unsigned Size, Base, RealSize;
	unsigned int loc(int i, int j) const throw(out_of_range) {
		if (i-Base >= Size or  i-Base < 0 or j-Base >= Size or j-Base < 0 or (i+j-2*Base)%2 != 0) throw out_of_range("invalid place!\n");
		unsigned Place = j - Base + (i - Base)*Size;
		return Place - (Place/2 + Place%2);
	}
	class Row {
	public:
		Row(ChessBoardArray &a, int i)
		:ChessRow(a), row(i) {}
		int & operator [] (int i) const {
			return ChessRow.select(row, i);
		}
	private:
		ChessBoardArray &ChessRow;
		int row;
	};

	class ConstRow {
	public:
		ConstRow(const ChessBoardArray &a, int i)
		: ChessRow(a), row(i) {}
		int operator [] (int i) const {
			return ChessRow.select(row, i);
		}
	private:
		const ChessBoardArray &ChessRow;
		const int row;
	};

public:
	ChessBoardArray(unsigned size = 0, unsigned base = 0);
	ChessBoardArray(const ChessBoardArray &a);
	~ChessBoardArray();

	ChessBoardArray & operator = (const ChessBoardArray &a) {
		delete []data;
		Size = a.Size;
		Base = a.Base;
		RealSize = a.RealSize;
		data = new int[a.RealSize];
		for (unsigned i=0; i<RealSize; i++){
			data[i] = a.data[i];
		}
		return *this;
	}

	int & select(int i, int j) {
		return data[loc(i, j)];
	}
	int select(int i, int j) const;

	const Row operator [] (int i) {
		return Row(*this, i);
	}
	const ConstRow operator [] (int i) const {
		return ConstRow(*this, i);
	}

	friend ostream & operator << (ostream &out, const ChessBoardArray &a);

};


ChessBoardArray::ChessBoardArray(unsigned size, unsigned base) {
	RealSize = size*size/2 + (size*size)%2;
	data = new int[RealSize];
	Size = size;
	Base = base;
	for (unsigned i=0; i<RealSize; i++)
		data[i] = 0;
}

ChessBoardArray::ChessBoardArray(const ChessBoardArray &a) {
	RealSize = a.Size*a.Size/2 +(a.Size*a.Size)%2;
	data = new int[RealSize];
	Size = a.Size;
	Base = a.Base;
	for (unsigned i=0; i < RealSize; i++) {
		data[i] = a.data[i];
	}
}

ChessBoardArray::~ChessBoardArray() {
	delete []data;
}

int ChessBoardArray::select(int i, int j) const {
	return data[loc( i, j)];
}

ostream & operator<< (ostream &out, const ChessBoardArray &a) {
    unsigned int i=0;
    unsigned counter = 0;

	for (i=0; i<a.RealSize; i++) {
		out << setw(4) << a.data[i];
		counter++;
		if (counter == a.Size) {
			out << endl;
			counter = 0;
			if (a.Size % 2 == 0 or i == a.RealSize - 1) continue;
		}

		out << setw(4) << "0";
		counter++;
		if (counter == a.Size and i != (a.RealSize - 1)) {
			out << endl;
			counter = 0;
			if (a.Size % 2 == 0) {
				out << setw(4) << "0";
				counter++;
			}
		}
	}
	return out;
}
/*
int main () {
    ChessBoardArray a(4,1);
	a[3][1] = 42;
	a[4][4] = 17;
	try {a[2][1] = 7;}
	catch(out_of_range &e) {cout << "a[2][1] is black" << endl;}
	try{cout << a[1][2] << endl;}
	catch(out_of_range &e){ cout << "and so is a[1][2]" << endl;}
	cout << a;
	}
*/

