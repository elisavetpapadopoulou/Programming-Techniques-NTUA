/*
 * Game.cpp
 *
 *  Created on: 20 Ìבס 2021
 *      Author: elisa
 */

#include <iostream>
#include "Players.hpp"
#include "movesandstates.hpp"
#include <string>
#include <stdexcept>

using namespace std;

class Game {
public:
	Game(int heaps, int players);
	~Game();

	void addHeap(int coins) throw(logic_error);
	void addPlayer(Player *player) throw(logic_error);
	void play(ostream &out) throw(logic_error);
	int getPlayers() const;
	const Player *getPlayer(int p) const throw(logic_error);
private:
	int *Heaps;
	Player **Players;
	int HeapNumber, PlayerNumber;
	int HeapCounter, PlayerCounter;
};

Game::Game(int heaps, int players){
	Heaps = new int[heaps];
	HeapNumber = heaps;
	Players = new Player*[players];
	PlayerNumber = players;
	PlayerCounter = 0;
	HeapCounter = 0;
}

Game::~Game() {
	delete []Heaps;
	delete []Players;
}

void Game::addHeap(int coins) throw(logic_error) {
	if (HeapCounter >= HeapNumber or coins < 0) throw logic_error("no space!");
	else {
		Heaps[HeapCounter++] = coins;
	}
}

void Game::addPlayer(Player *player) throw(logic_error) {
	if (PlayerCounter >= PlayerNumber) throw logic_error("no places for players left!");
	else {
		Players[PlayerCounter++] = player;
	}
}

void Game::play(ostream &out) throw (logic_error){
	State Playing(HeapNumber, Heaps, PlayerNumber);
	int i = 0;
	while(not Playing.winning()) {
		if (i >= PlayerNumber) i=0;
		out << "State: " << Playing << endl;
		Move NextMove = Players[i]->play(Playing);
		Playing.next(NextMove);
		out << *Players[i] << " " << NextMove << endl;
		i++;
	}
	out << "State: " << Playing << endl;
	out << *Players[i-1] << " wins" << endl;
}

int Game::getPlayers() const {
	return PlayerNumber;
}

const Player* Game::getPlayer(int p) const throw(logic_error){
	if (p<0 or p>=PlayerNumber) throw logic_error("Invalid player ID!");
	else return Players[p];
}

#ifndef CONTEST
int main() {
	 Game specker(3, 4);
	 specker.addHeap(10);
	 specker.addHeap(20);
	 specker.addHeap(17);
	 specker.addPlayer(new SneakyPlayer("Tom"));
	 specker.addPlayer(new SpartanPlayer("Mary"));
	 specker.addPlayer(new GreedyPlayer("Alan"));
	 specker.addPlayer(new RighteousPlayer("Robin"));
	 specker.play(cout);
}
#endif
