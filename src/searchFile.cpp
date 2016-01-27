#include <fstream>
#include <streambuf>
#include <string>
#include <cerrno>
#include <iostream>

std::string get_file_contents(const char *filename)	//read file contents to a string
{
	std::ifstream in(filename, std::ios::in | std::ios::binary);
		if (in)
		{
			return(std::string((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>()));
		}
		throw(errno);
}

/*This program finds the job number. This is done in the following steps:
 * 1. Find the position of the word 'als'. This position may vary.
 * 2. The position of the word 'Stelle' is always constant and begins at index 18. At index 24 begins the job number
 * 3. Display the job number
 * 4. Write the job number to a file 'coverLetterCodeNumber.txt'
 */

int main()
{
	const char *fileNameRead = "/media/ntfs2/FirefoxProfile/zotero/storage/MKDMD6AZ/variables/coverLetterPosition.txt";
	const char *fileNameWrite = "/media/ntfs2/FirefoxProfile/zotero/storage/MKDMD6AZ/variables/coverLetterCodeNumber.txt";
	std::string fileString;
	std::string searchAls = "als";

	fileString = get_file_contents(fileNameRead);
	std::cout << fileString;

	std::size_t found = fileString.find(searchAls);
	if (found!=std::string::npos)
		std::cout << "Als found at: " << found << '\n';

	std::size_t startPosition = 25;
	std::size_t length;
	length = found - startPosition -1;		// this is the length of the job number. In case of lack of the job number length
											// becomes negative -1 and because it is unsigned int length is turned to a very big
											// number.
											// This case checks if length > 20 as the job is never longer than 20 letters.
	if (length>20)
	{
		length = 0;
		std::cout << "Job length: " << length << '\n';

		std::string jobNumber (fileString, startPosition, length);
		std::cout << "Job number: " << jobNumber << '\n';

		std::ofstream out(fileNameWrite);
		out << "\\ " << jobNumber;		//job number needs \ in order to work in latex
		out.close();
	}
	else
	{
		std::cout << "Job length: " << length << '\n';

		std::string jobNumber (fileString, startPosition, length);
		std::cout << "Job number: " << jobNumber << '\n';

		std::ofstream out(fileNameWrite);
		out << "\\ " << jobNumber;		//job number needs \ in order to work in latex
		out.close();
	}

	return 0;
}
