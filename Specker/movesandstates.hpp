/*
 * movesandstates.hpp
 *
 *  Created on: 19 Ìבס 2021
 *      Author: elisa
 */

#ifndef MOVESANDSTATES_HPP_
#define MOVESANDSTATES_HPP_
#include <iostream>
#include <stdexcept>
using namespace std;

class Move {
	//Take sc coins from heap sh and put tc coins in heap th.
public:
	Move (int sh, int sc, int th, int tc);

	int getSource () const;
	int getSourceCoins () const;
	int getTarget () const;
	int getTargetCoins () const;

	friend ostream & operator << (ostream &out, const Move &move);
private:
	int sh, sc, th, tc;
};

Move::Move (int sh, int sc, int th, int tc){
	Move::sc = sc;
	Move::sh = sh;
	Move::tc = tc;
	Move::th = th;
}

int Move::getSource() const {
	return sh;
}

int Move::getSourceCoins() const {
	return sc;
}

int Move::getTarget() const {
	return th;
}

int Move::getTargetCoins () const {
	return tc;
}

ostream& operator<< (ostream &out, const Move &move){

	out << "takes " << move.sc << " coins from heap " << move.sh << " and puts ";
	if (move.getTargetCoins() != 0)
		out << move.tc << " coins to heap " <<move.th;
	else
		out << "nothing";
	return out;
}

int counter=0;

class State {
public:
	//State with h heaps, where the i-th heap starts with c[i] coins.
	//A total of n players are in the game, numbered from 0 up to n-1.
	//Player 0 is the first to play.
	State (int h, const int c[], int n);
	~State();

	void next (Move &move) throw (logic_error);
	bool winning () const;

	int getHeaps() const;
	int getCoins(int h) const throw (logic_error);

	int getPlayers() const;
	int getPlaying() const;

	friend ostream & operator << (ostream &out, const State &state);
private:
	int *heaps;
	int players;
	int HeapNumber;
};

State::State (int h, const int c[], int n){
    heaps = new int[h];
    for (int i=0; i<h; i++){
    	heaps[i] = c[i];
    }
	players = n;
	HeapNumber = h;
}

State::~State() {
	delete []heaps;
}

void State::next (Move &move) throw (logic_error){
	int a = move.getSource();
	int b = move.getSourceCoins();
	int c = move.getTarget();
	int d = move.getTargetCoins();
	if (a<0 or b<0 or c<0 or d<0 or a>=HeapNumber or b>heaps[a] or c>=HeapNumber or d>=b)
		throw logic_error("invalid move\n");
	heaps[a]-=b;
	heaps[c]+=d;
	if (counter < players - 1) counter++;
	else counter = 0;

	}

bool State::winning () const {
	for(int i=0; i<HeapNumber; i++)
		if (heaps[i] != 0) return false;
	return true;
}

int State::getHeaps() const {
	return HeapNumber;
}

int State::getCoins(int h) const throw (logic_error){
	if (h<0 or h>=HeapNumber) throw logic_error ("invalid heap\n");
	else return heaps[h];
}

int State::getPlayers() const {
	return players;
}

int State::getPlaying() const {
	return counter;
}

ostream& operator<< (ostream &out, const State &state){
	for(int i=0; i<state.HeapNumber; i++){
		out << state.heaps[i];
		if (i==state.HeapNumber-1) break;
		out << ", ";
	}
	out << " with " << state.getPlaying() << "/" << state.getPlayers() << " playing next";
	return out;
}


#endif /* MOVESANDSTATES_HPP_ */
