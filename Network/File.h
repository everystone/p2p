#pragma once

class File
{
public:
	File(std::string fileName, int size);

	int size();
	std::string name();

private:
	std::string m_filename;
	int m_size;
	int m_seeds;
};

