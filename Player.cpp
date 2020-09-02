#include "Player.h"
#include "Board.h"
#include <cstdlib>
#include <iostream>

using namespace std;
//Create a Player with the indicated name.
Player::Player(std::string name)
{
	m_name = name;
	
}

//Return the name of the player.
std::string Player::name() const
{
	return m_name;
}

//Return false if the player is a computer player. Return true if the player is human.
//Most kinds of players will be computer players.
bool Player::isInteractive() const
{
	return false;
}

Player::~Player()
{
}
//Since this class is designed as a base class, it should have a virtual destructor.

/////////////////////////////////////////////The Virtual Classes//////////////////////////////////////////

////////HUMANPLAYER////////////
HumanPlayer::HumanPlayer(std::string name): Player(name)
{
	
}

//Every concrete class derived from this class must implement this function so that if the player 
//were to be playing side s and had to make a move given board b, the function returns the move 
//the player would choose. If no move is possible, return −1.
int HumanPlayer::chooseMove(const Board& b, Side s) const
{
	int counter = 0;
	for (int i = 0; i <= b.holes(); i++)
	{
		if (b.beans(s, b.holes() - i) == 0)
			counter++;
	}
	if (counter = b.holes())
		return -1;
	int hole = 0;
	cin >> hole;
	while (hole > b.holes() || hole < 0 || b.beans(s, b.holes()) == 0)
	{
		cout << "Please choose a valid or non-empty hole.";
		cin >> hole;
	}
	return hole;

}

bool HumanPlayer::isInteractive() const
{
	return true;
}

HumanPlayer::~HumanPlayer()
{

}

////////BADPLAYER///////////////////////////////
BadPlayer::BadPlayer(std::string name): Player(name)
{

}
	
//Every concrete class derived from this class must implement this function so that if the player 
//were to be playing side s and had to make a move given board b, the function returns the move 
//the player would choose. If no move is possible, return −1.
int BadPlayer::chooseMove(const Board& b, Side s) const
{
	for (int i = 0; i <= b.holes(); i++)
	{
		if (b.beans(s, b.holes() - i) != 0)
			return b.holes() - i;
	}
	return -1;
}

BadPlayer::~BadPlayer()
{
}

////////////SMARTPLAYER/////////////////////////////
SmartPlayer::SmartPlayer(std::string name): Player(name)
{

}

//Every concrete class derived from this class must implement this function so that if the player 
//were to be playing side s and had to make a move given board b, the function returns the move 
//the player would choose.If no move is possible, return −1.
int SmartPlayer::chooseMove(const Board& b, Side s) const
{
	for (int i = 0; i <= b.holes(); i++)
	{
		if (b.beans(s, b.holes() - i) != 0)
			return b.holes() - i;
	}
	return -1;
}
	
SmartPlayer::~SmartPlayer()
{

}
	