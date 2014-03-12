#pragma once

#include "Includes.h"
#include "PieceReader.h"

class PieceObjectManager
{
	std::vector<std::string> *_objs;
	std::vector<std::vector<Vertex>> *_pieces;
	std::vector<bool>* _hasTex;
	std::vector<std::vector<unsigned int>>* _indices;

public:

	void init();
	void loadAllObj();

	std::vector<Vertex> getPiece(int index);
	std::string getObjName(int index);
	bool getHasTexture(int index);
	int getNumPieces();
	std::vector<unsigned int> getIndices(int index);

	PieceObjectManager();
	virtual ~PieceObjectManager();
};

