#include "Board.h"
//Construct a Board with the indicated number of holes per side(not counting the pot) and 
//initial number of beans per hole.If nHoles is not positive, act as if it were 1; 
//if nInitialBeansPerHole is negative, act as if it were 0.
Board::Board(int nHoles, int nInitialBeansPerHole)
{
	if (nHoles <= 0)
		m_nholes = 1;
	else
		m_nholes = nHoles;
	if (nInitialBeansPerHole < 0)
		m_nholes = 0;
	else
		m_initialbeans = nInitialBeansPerHole * nHoles * 2;

	Node* pot1 = new Node;	//initalizing the NORTH pot
	pot1->side = NORTH;
	pot1->hole = 0;
	pot1->m_beans = 0;
	Node* pot2 = new Node;	//initializing the SOUTH pot
	pot2->side = SOUTH;	
	pot2->hole = 0;
	pot2->m_beans = 0;
	head1 = pot1;		//connecting them together
	pot1->next = pot2;
	pot2->next = pot1;
	head2 = pot2;

	Node* northGuide = pot1;
	Node* southGuide = pot2;
	for (int i = 1; i <= nHoles; i++) //traverse through linked list to add holes on 
	{
		Node* newNORTH = new Node;
		newNORTH->m_beans = nInitialBeansPerHole;
		newNORTH->hole = i;
		newNORTH->side = NORTH;
		newNORTH->next = northGuide;
		pot2->next = newNORTH;
		northGuide = newNORTH;

		Node* newSOUTH = new Node;
		newSOUTH->m_beans = nInitialBeansPerHole;
		newSOUTH->hole = nHoles - i + 1;
		newSOUTH->side = SOUTH;
		newSOUTH->next = southGuide;
		pot1->next = newSOUTH;
		southGuide = newSOUTH;
	}
}

Board::Board(const Board& otherBoard)
{
	m_nholes = otherBoard.holes();
	m_initialbeans = otherBoard.totalBeans();

	Node* pot1 = new Node;	//initalizing the NORTH pot
	pot1->side = NORTH;
	pot1->hole = 0;
	pot1->m_beans = otherBoard.beans(NORTH, 0);
	Node* pot2 = new Node;	//initializing the SOUTH pot
	pot2->side = SOUTH;
	pot2->hole = 0;
	pot2->m_beans = otherBoard.beans(SOUTH, 0);
	head1 = pot1;		//connecting them together
	pot1->next = pot2;
	pot2->next = pot1;
	head2 = pot2;
	
	Node* northGuide = pot1;
	Node* southGuide = pot2;

	for (int i = 0; i < m_nholes; i++) //traverse through linked list to add holes on 
	{
		Node* newNORTH = new Node;
		newNORTH->m_beans = otherBoard.beans(NORTH, i + 1);
		newNORTH->hole = i + 1;
		newNORTH->side = NORTH;
		newNORTH->next = northGuide;
		pot2->next = newNORTH;
		northGuide->next = newNORTH;

		Node* newSOUTH = new Node;
		newSOUTH->m_beans = otherBoard.beans(SOUTH, i + 1);
		newSOUTH->hole = m_nholes - i;
		newSOUTH->side = SOUTH;
		newSOUTH->next = southGuide;
		pot1->next = newSOUTH;
		southGuide->next = newSOUTH;
	}
	
}
//Return the number of holes on a side(not counting the pot).
int Board::holes() const
{
	return m_nholes;
}

//Return the number of beans in the indicated hole or pot, or −1 if the hole number is invalid.
int Board::beans(Side s, int hole) const
{
	Node* follower;
	if (s == NORTH)
	{
		follower = head1;
		for (int i = 0; i < hole; i++)
		{
			follower = follower->next;
		}
		return follower->m_beans;
	}
	else
	{
		follower = head2;
		for (int i = 0; i < holes() - hole; i++)
		{
			follower = follower->next;
		}
		return follower->m_beans;
	}
}

//Return the total number of beans in all the holes on the indicated side, not counting the beans in the pot.
int Board::beansInPlay(Side s) const
{
	int totalBeans = 0;
	
	for (int i = 1; i < m_nholes + 1; i++)
	{
		totalBeans += beans(s, i);
	}
	return totalBeans;
}
	

//Return the total number of beans in the game, including any in the pots.
int Board::totalBeans() const
{
	return m_initialbeans;
}

//If the hole indicated by(s, hole) is empty or invalid or a pot, this function returns false without 
//changing anything. Otherwise, it will return true after sowing the beans : the beans are removed from 
//hole(s, hole) and sown counterclockwise, including s's pot if encountered, but skipping s's 
//opponent's pot. The parameters endSide and endHole are set to the side and hole where the last bean was placed.
//(This function does not make captures or multiple turns; different Kalah variants have 
//	different rules about these issues, so dealing with them should not be the responsibility of the
//	Board class.)
bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
{
	if (hole > holes() || hole <= 0)
		return false;
	else
	{
		Node* follower;
		if (s == NORTH)
		{
			follower = head1;
			for (int i = 0; i < hole; i++)
			{
				follower = follower->next;
			}
			if (follower->m_beans == 0)
				return false;
			else
			{
				int counter = follower->m_beans;
				follower->m_beans = 0;
				for (int i = 0; i < counter; i++)
				{
					follower = follower->next;
					if (follower == head2 || follower == head1)
						follower = follower->next;
					follower->m_beans++;
				}
				endSide = follower->side;
				endHole = follower->hole;
				return true;
			}
		}
		else
		{
			follower = head2;
			for (int i = 0; i < holes() - hole; i++)
			{
				follower = follower->next;
			}
			if (follower->m_beans == 0)
				return false;
			else
			{
				int counter = follower->m_beans;
				follower->m_beans = 0;
				for (int i = 0; i < counter; i++)
				{
					follower = follower->next;
					if (follower == head2 || follower == head1)
						follower = follower->next;
					follower->m_beans++;
				}
				endSide = follower->side;
				endHole = follower->hole;
				return true;
			}
		}
		return true;
	}
}

//If the indicated hole is invalid or a pot, return false without changing anything.
//Otherwise, move all the beans in hole(s, hole) into the pot belonging to potOwner and return true.
bool Board::moveToPot(Side s, int hole, Side potOwner)
{
	if (hole > holes() || hole <= 0)
		return false;
	else
	{
		Node* follower;
		if (s == NORTH)
		{
			follower = head1;
			for (int i = 0; i < hole; i++)
			{
				follower = follower->next;
			}
			head1->m_beans = follower->m_beans;
			follower->m_beans = 0;
		}
		else
		{
			follower = head2;
			for (int i = 0; i < holes() - hole; i++)
			{
				follower = follower->next;
			}
			head2->m_beans = follower->m_beans;
			follower->m_beans = 0;
		}
		return true;
	}
}

//If the indicated hole is invalid or beans is negative, this function returns false without changing anything.
//Otherwise, it will return true after setting the number of beans in the indicated hole or pot to the value of 
//the third parameter. (This may change what beansInPlay and totalBeans return if they are called later.) 
//This function exists solely so that we and you can more easily test your program : None of your code that 
//implements the member functions of any class is allowed to call this function directly or indirectly. 
//(We'll show an example of its use below.)
bool Board::setBeans(Side s, int hole, int beans)
{
	if (hole > holes() || hole <= 0 || beans <= 0)
		return false;
	else
	{
		Node* follower;
		if (s == NORTH)
		{
			follower = head1;
			for (int i = 0; i < hole; i++)
			{
				follower = follower->next;
			}
			follower->m_beans = beans;
		}
		else
		{
			follower = head2;
			for (int i = 0; i < holes() - hole; i++)
			{
				follower = follower->next;
			}
			follower->m_beans = beans;
		}
		return true;
	}
}
