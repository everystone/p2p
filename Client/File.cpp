#include "stdafx.h"
#include "File.h"



File::File(std::string fileName, int size)
{
	this->name = fileName;
	this->size = size;
}
