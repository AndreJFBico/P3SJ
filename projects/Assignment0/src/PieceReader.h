#pragma once
#include "Piece.h"

class PieceReader
{
	std::vector<Vertex>* vertices;
	std::vector<unsigned int>* indices;
	bool hasTex;


	PieceReader() {};
	PieceReader(PieceReader const&);

public:
	static PieceReader& getInstance()
	{
		static PieceReader instance;
		return instance;
	}

	void init();

	void readObject(std::string fpath);

	std::vector<Vertex> getVertices();
	std::vector<unsigned int> getIndices();

	bool getHasTex();

	void clearAll();

	~PieceReader();
};

