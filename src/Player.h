#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player
{
public:
	Player(int numRows, int numCols);
	int play(bool valid);
private:
	int numColumns;
	int numRows;
};


#endif // PLAYER_H 