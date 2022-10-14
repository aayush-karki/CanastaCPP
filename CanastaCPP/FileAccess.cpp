/************************************************************
* Name:  Aayush Karki                                       *
* Project : Project 1, Canasta in C++                       *
* Class : CMPS 366 01 - OPL                                 *
* Date : September 27, 2022                                 *
************************************************************/

#include "FileAccess.h"

/* *********************************************************************
Function Name: FileAccess
Purpose: To construct a FileAccess and to populate its 	member variables.
Parameters: none
Return Value: none
Algorithm:
		1) Initialze the member function
		2) create the data directory if it does not exist
Assistance Received: none
********************************************************************* */
FileAccess::FileAccess() :
	m_fileHandler(), m_filePath(),
	m_dataFolderPath( std::filesystem::current_path() / "Data" )
{
	// creating a data folding if it does not exist
	std::filesystem::create_directories( m_dataFolderPath );
}

/* *********************************************************************
Function Name: FileAccess
Purpose: To destruct a FileAccess object and close file if it is open
Parameters: none
Return Value: none
Algorithm:
			1) close the file if it is open
Assistance Received: none
********************************************************************* */
FileAccess::~FileAccess()
{
	if( m_fileHandler.is_open() )
	{
		m_fileHandler.close();
	}
}

/* *********************************************************************
Function Name: OpenFile
Purpose: To opens the passed file in read and write mode
Parameters: 
			a_fileName, string, holds the filename of the file that  
				that is to be opened and is in  "(cwd)/data/" directory.
Return Value: true on successfull opening; else false
Algorithm:
			1) get a valid full path from the passed filename
			2) if the path does not exist return false
			3) if a file is open then close it
			4) save the file path
			5) open the file
			6) if the file did not open then return false
			7)	else return true
Assistance Received: none
********************************************************************* */
bool FileAccess::OpenFile( std::string a_fileName )
{
	// getting a path from the passed stirng
	std::filesystem::path passedPath = GetAPathFromStr( a_fileName );

	// if the passed file does not exist return false
	if( !std::filesystem::exists( passedPath ) )
	{
		Message::AddMessage( passedPath.stem().string() + " does not exist!" );
		return false;
	}

	// if a file is open then closing it
	if( m_fileHandler.is_open() )
	{
		m_fileHandler.close();
		m_filePath.clear();
	}

	// opening the path
	m_filePath = passedPath;

	m_fileHandler.open( m_filePath, std::ios::in | std::ios::out );

	// Check if the file has opened
	if( !m_fileHandler )
	{
		Message::AddMessage( "Could not open File: " + passedPath.stem().string() );
		return false;
	}

	return true;
}

/* *********************************************************************
Function Name: CreateFile
Purpose: To create a empty file with the passed filename and open it in 
		read and write mode.
Parameters: 
			a_fileName, string, holds the filename of the file that  that 
				is to be created and is in  "(cwd)/data/" directory.
Return Value: true on successfull creation and opening; else false
Algorithm:
			1) get a valid full path from the passed filename
			2) if the path does not exist create a new file
			3) opening the the file and remove all of its content on 
				successful opening and return true else return false
Assistance Received: none
********************************************************************* */
bool FileAccess::CreateFile( std::string a_fileName )
{
	std::filesystem::path passedPath = GetAPathFromStr( a_fileName );
	
	// if the file does not exist then create a new one
	if( !std::filesystem::exists( passedPath ) )
	{
		// creating a file
		std::ofstream tempFile( passedPath, std::ios::out );
		tempFile << "new file created!!!!! " << std::endl;
		tempFile.close();
	}

	// open the file and remove all content form the file if file opened
	if( OpenFile( passedPath.string() ) )
	{
		RemoveAllContent();
		return true;
	}

	// file did not successfully open
	Message::AddMessage("Could not create the file successfully");
	return false;
}

/* *********************************************************************
Function Name: GetNextLine
Purpose: Get the next line from the file.
Parameters: 
			a_line, a string passed by reference, it holds the string 
				where the extracted line is to be passed
Return Value: true on successfull extraction; else false
Algorithm:
			1) if the file is not open return false
			2) if eof is reased return false
			3) get a line into the passed string and return true
Assistance Received: none
********************************************************************* */
bool FileAccess::GetNextLine( std::string& a_line )
{
	// if the file is not open then return false
	if( m_fileHandler.is_open() )
	{
		Message::AddMessage( "File is not open" );
		return false;
	}

	//if eof reached return false
	if( m_fileHandler.eof() )
	{
		return false;
	}

	std::getline( m_fileHandler, a_line );

	return true;
}
 
/* *********************************************************************
Function Name: WriteOneLineToFile
Purpose: Wrties a line to the the file.
Parameters:
			a_line, const a string passed by value, it holds the string
				that is to be added to the file
Return Value: true on successfull insertion; else false
Algorithm:
			1) if the file is not open return false
			2) add the passed string into the file and return true
Assistance Received: none
********************************************************************* */
bool FileAccess::WriteOneLineToFile( const std::string a_line )
{
	// if the file is not open then return false
	if( m_fileHandler.is_open() )
	{
		Message::AddMessage( "File is not open" );

		return false;
	}

	m_fileHandler << a_line << std::endl;

	return true;
}

/* *********************************************************************
Function Name: RemoveAllContent
Purpose: Removes all content form the file and points the pointer to 
		beginning of the file
Parameters: none
Return Value: true on successful clearing the file content; else false
Algorithm:
			1) if the file is not open return false
			2)  resize the file to 0
Assistance Received: cplusplus
********************************************************************* */
bool  FileAccess::RemoveAllContent()
{

	// if the file is not open then return false
	if( m_fileHandler.is_open() )
	{
		Message::AddMessage( "File is not open" );

		return false;
	}

	std::filesystem::resize_file( m_filePath, 0 );
	return true;
}
 
/* *********************************************************************
Function Name: CheckEOF
Purpose: checks if the end of file is reached or not
Parameters: none
Return Value: true if file pointer is pointed at end of file else false
Algorithm:
			1) call eof() funciton on file handler 
Assistance Received: cplusplus
********************************************************************* */
bool FileAccess::CheckEOF()
{
	return m_fileHandler.eof();
}

/* *********************************************************************
Function Name: GetAPathFromStr
Purpose: To get a file path from the passed string
Parameters:
			a_fileName, string, holds the filename of the file that  that
				is is in  "(cwd)/data/" directory.
Return Value: std::filesystem::path object with file name beign the stem
			of passed file name, and parent_path beign the dataFolderPath
Algorithm:
			1) if the parent path of the passed file does not equal to 
				dataFolder path then set it to dataFolderpath
			2) if the stem of the passed file does not equal to 
				.txt then set it to .txt
			3) return the newly created path object
Assistance Received: none
********************************************************************* */
std::filesystem::path FileAccess::GetAPathFromStr( std::string a_filename )
{
	std::filesystem::path passedPath( a_filename );

	// chekcing if the file is in dataFolder or not
	if( passedPath.parent_path() != m_dataFolderPath )
	{
		passedPath = m_dataFolderPath / passedPath.filename();
	}

	// chekcing if the file's extension is .txt or not
	if( passedPath.extension() != ".txt" )
	{
		passedPath = passedPath.replace_extension( ".txt" );
	}

	return passedPath;
}

/* *********************************************************************
Function Name: Rewind
Purpose: Points the file pointer to beginning of the file.
Parameters: none
Return Value: true on successful rewind; else false
Algorithm:
			1) if the file is not open return false
			2)  clear the flags and pointer the seeker to top of file
Assistance Received: none
********************************************************************* */
bool FileAccess::Rewind()
{
	// if the file is not open then return false
	if( m_fileHandler.is_open() )
	{
		Message::AddMessage( "File is not open" );

		return false;
	}

	m_fileHandler.clear();
	m_fileHandler.seekg( 0, std::ios::beg );
	return true;
}