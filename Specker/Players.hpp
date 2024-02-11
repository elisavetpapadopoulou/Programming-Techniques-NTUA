/*
 * Players.hpp
 *
 *  Created on: 20 Ìבס 2021
 *      Author: elisa
 */

#ifndef PLAYERS_HPP_
#define PLAYERS_HPP_
#include <iostream>
#include "movesandstates.hpp"
#include <string>

using namespace std;

class Player {
public:
	Player(const string &n);
	virtual ~Player();
	string getName() const {return *name;}
	virtual const string & getType() const = 0;
	virtual Move play(const State &s) = 0;

	friend ostream & operator << (ostream &out, const Player &player);
protected:
	string *name;
};

Player::Player(const string &n){
	name = new string(n);
}

Player::~Player(){
	delete name;
}

//const string & Player::getType() const{
	//return Type;
//}

ostream& operator<< (ostream &out, const Player &player) {
	out << player.getType() << " player " << player.getName();
	return out;
}


class GreedyPlayer : public Player {
public:
	GreedyPlayer(const string &n)
	: Player(n), Type(new string("Greedy")) {}
	~GreedyPlayer() override;
	const string & getType() const override;
	Move play(const State &s) override;
private:
	string *Type;
};

/*GreedyPlayer::GreedyPlayer(const string &n) {
	 Player(n);
	 Type = string("Greedy");
}*/
const string & GreedyPlayer::getType() const {
	return *Type;
}

GreedyPlayer::~GreedyPlayer() {
	delete Type;
}

Move GreedyPlayer::play(const State &s) {
	int max = 0;
	int position = 1000000;
	for(int i=0; i<s.getHeaps(); i++) {
		if (s.getCoins(i) > max) {
			max = s.getCoins(i);
			position = i;
		}
	}
	return Move(position, max, 0, 0);
}

class SpartanPlayer : public Player {
public:
	SpartanPlayer (const string &n)
		: Player(n), SpartanType(new string("Spartan")) {}
	~SpartanPlayer() override;
	const string & getType() const override;
	Move play (const State &s) override;
private:
	string *SpartanType;
};

SpartanPlayer::~SpartanPlayer() {
	delete SpartanType;
}
const string & SpartanPlayer::getType() const {
	return *SpartanType;
}

Move SpartanPlayer::play(const State &s) {
	int max = -1;
	int position = 10000000;
	for(int i=0; i<s.getHeaps(); i++){
		if (s.getCoins(i) > max){
			max = s.getCoins(i);
			position = i;
		}
	}
	return Move(position, 1, 0, 0);
}

class SneakyPlayer : public Player {
public:
	SneakyPlayer(const string &n)
	: Player(n), SneakyType(new string("Sneaky")) {}
	~SneakyPlayer() override;
	const string & getType() const override;
	Move play(const State &s) override;
private:
	string *SneakyType;
};

SneakyPlayer::~SneakyPlayer() {
	delete SneakyType;
}
const string & SneakyPlayer::getType() const {
	return *SneakyType;
}

Move SneakyPlayer::play(const State &s){
	int position = 100000000;
	int min = 1000000000;
	int heaps = s.getHeaps();
	for(int i=0; i<heaps; i++){
		int coins = s.getCoins(i);
		if (coins < min and coins > 0) {
			min = s.getCoins(i);
			position = i;
		}
	}
	return Move(position, min, 0, 0);
}

class RighteousPlayer : public Player {
public:
	RighteousPlayer (const string &n)
	: Player(n), RighteousType(new string("Righteous")) {}
	~RighteousPlayer() override;
	const string & getType() const override;
	Move play(const State &s) override;
protected:
	string *RighteousType;
};

RighteousPlayer::~RighteousPlayer() {
	delete RighteousType;
}
const string & RighteousPlayer::getType() const {
	return *RighteousType;
}

Move RighteousPlayer::play(const State &s){
	int max = -1;
	int min = 10000000;
	int positionM = 1000000000;
	int positionm = 1000000000;
	int heaps = s.getHeaps();
	int coins=0;
	for(int i=0; i<heaps; i++){
		coins = s.getCoins(i);
		if (coins > max){
			max = coins;
			positionM = i;
		}
		if (coins < min){
			min = coins;
			positionm = i;
		}
	}
	int takes = (max/2)+max%2;
	int gives = takes - 1;
	return Move(positionM, takes, positionm, gives);
}


#endif /* PLAYERS_HPP_ */
