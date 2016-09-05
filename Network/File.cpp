#include "stdafx.h"
#include "file.h"



File::File(std::string fileName, int size)
{
	this->m_filename = fileName;
	// calculate size

}

int File::size()
{
	return m_size;
}

std::string File::name()
{
	return m_filename;
}
