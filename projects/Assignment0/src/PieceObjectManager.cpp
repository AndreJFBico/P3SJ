#include "PieceObjectManager.h"

PieceObjectManager::PieceObjectManager()
{
	_pieces = new std::vector<std::vector<Vertex>>();
	_objs = new std::vector<std::string>();
	_hasTex = new std::vector<bool>();
	_indices = new std::vector<std::vector<unsigned int>>();
}

void PieceObjectManager::init()
{
	_objs->push_back("sphere");
	_objs->push_back("quad");
	_objs->push_back("Torus(blend)");
	_objs->push_back("lion");
}

void PieceObjectManager::loadAllObj()
{
	for (unsigned int i = 0; i < _objs->size(); i++)
	{
		std::string pre = "..\\objects\\";
		std::string post = ".obj";
		PieceReader::getInstance().readObject(pre + _objs->at(i) + post);
		_pieces->push_back(PieceReader::getInstance().getVertices());
		_hasTex->push_back(PieceReader::getInstance().getHasTex());
		_indices->push_back(PieceReader::getInstance().getIndices());
	}
}

std::string PieceObjectManager::getObjName(int index)
{
	return _objs->at(index);
}

std::vector<Vertex> PieceObjectManager::getPiece(int index)
{
	return _pieces->at(index);

}

bool PieceObjectManager::getHasTexture(int index)
{
	return _hasTex->at(index);

}

std::vector<unsigned int> PieceObjectManager::getIndices(int index)
{
	return _indices->at(index);
}

int PieceObjectManager::getNumPieces()
{
	return _objs->size();

}

PieceObjectManager::~PieceObjectManager(){}
