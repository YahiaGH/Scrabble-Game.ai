#include "Board.h"

Board::Board()
{
	for(int i=0;i<26;i++)// i want to create them at insertion of the letter as i dont need the whole 26 char along the game
	{
		BoardMap[(char)('A'+i)]= BoardMask(0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000);
	}
}
Board* Board::BoardInst_=nullptr;
Board* Board::getBoard()
{

	if(BoardInst_==nullptr)
	{
		BoardInst_=new Board;
	}
	return (BoardInst_);
}
std::vector<char>& Board::getNextHorizontal(int HorizontalIndex)
{
	vector<char> CharVect;
	vector<char> HorizontalVector;
	int ResIndex=0;
	BoardMask CheckBoard(0b0000000000000000000000000000000000000000000000000111111111111111, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000, 0b0000000000000000000000000000000000000000000000000000000000000000);
	CheckBoard=CheckBoard <<15*HorizontalIndex; // shift 15times in  each column 
	//check board func is to bring the char. that in the Horizontal index
	for (auto Instance : BoardMap) // an instance of a letter
	{
		if((Instance.second&CheckBoard).isEmpty()) 
		{
			CharVect.push_back(Instance.first);//  need to edit the position in the vector 

		}
	}
	for(int mOffsit=HorizontalIndex*15;mOffsit<(HorizontalIndex*15+15);mOffsit++)// looping on the col
	{
		for(std::size_t i=0; i<CharVect.size(); ++i) // looking on the char board that has  this bit
		{
			if(BoardMap[CharVect[i]].getBit(mOffsit))
			{
				HorizontalVector[ResIndex++]=CharVect[i];
				break; 
			}
			if(i==CharVect.size()-1)// i reached the end and this offsit is not in any char board
				HorizontalVector[ResIndex++]=' ';
		}
	}
	return HorizontalVector;
}
std::vector<char>& Board::getNextVertical(int VerticalIndex)
{
	vector<char> CharVect;
	vector<char> VerticalVector;
	int ResIndex=0;
	BoardMask CheckBoard(0b0001000000000000001000000000000001000000000000001000000000000001,0b0000000100000000000000100000000000000100000000000000100000000000, 0b0000000000010000000000000010000000000000010000000000000010000000, 0b0000000000000001000000000000001000000000000001000000000000001000);
	//specifying the row positions 
	CheckBoard=CheckBoard >>VerticalIndex;  // as each row is difference from its next row by 1
	for (auto Instance : BoardMap) 
	{
		if((Instance.second&CheckBoard).isEmpty())
		{
			CharVect.push_back(Instance.first);

		}
	}

	for(int mOffsit=VerticalIndex;mOffsit<(VerticalIndex+15);mOffsit++)// looping on the col
	{
		for(std::size_t i=0; i<CharVect.size(); ++i) // looking on the char board that has  this bit
		{
			if(BoardMap[CharVect[i]].getBit(mOffsit))
			{
				VerticalVector[ResIndex++]=CharVect[i];
				break; 
			}
			if(i==CharVect.size()-1)// i reached the end and this offsit is not in any char board
				VerticalVector[ResIndex++]=' ';
		}
	}
	return VerticalVector;

}
void Board::SetCharPos(char Letter,int Row,int Col)
{
	int Offsit=Row +15*Col;
	if(Offsit<0 || Offsit >(14+15*14) )
	return;
	BoardMap[Letter].setBit(Offsit);
}
int Board::calculateScore(std::vector<char>& suggestedMove, int position, bool horizontal)
{

}