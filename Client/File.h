#pragma once

class File
{
public:
	File(std::string fileName, int size);

private:
	std::string name;
	int size;
	int seeds;
};

