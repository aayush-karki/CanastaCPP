/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#pragma once
#include <sstream> // to extract data
#include <fstream> // read and write to a file
#include <filesystem> // for path, resize, and exist
#include "Message.h"

class FileAccess
{
public:
	// constructor
	FileAccess();

	// destructor
	~FileAccess();

	// copy constructor can not copy a fileaccess object 
	// because of the fstream member varialbe
	FileAccess( const FileAccess& a_other ) = delete;

	// assignment operator can not assigne a fileaccess object 
	// because of the fstream member varialbe
	FileAccess& operator=( const FileAccess& a_other ) = delete;

	// opens the passed file
	bool OpenFile( std::string a_fullfileName );

	// creates a file and returns the file
	bool CreateFile( std::string a_fullfileName );

	// closes the file
	void CloseFile() { if( m_fileHandler.is_open() ) { m_fileHandler.close(); } }

	// gets next line form the file
	bool GetNextLine( std::string& a_line );

	// appends a line to the end
	bool WriteOneLineToFile( const std::string a_line );

	// removes all content form the file and goes to 
	// beginning of the file
	bool RemoveAllContent();

	// checks if the eof reached or not
	bool CheckEOF();
private:

	// holds the file handler
	std::fstream m_fileHandler;

	// holds the path to file path
	std::filesystem::path m_filePath;

	// holds the path to data directory
	const std::filesystem::path m_dataFolderPath;

	// gets a path that is in "( cwd )/data/" directory.
	std::filesystem::path GetAPathFromStr( std::string a_filename );

	// clears the file and goes back to the beginning of the file
	bool Rewind();
};