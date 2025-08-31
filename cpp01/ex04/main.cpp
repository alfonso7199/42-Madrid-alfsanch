#include <fstream>
#include <iostream>

int	replace(char **argv, std::string content)
{
	std::ofstream	outfile;
	std::string		s1 = argv[2];
	std::string		s2 = argv[3];
	size_t			s1_len = s1.size();

	outfile.open((std::string(argv[1]) + ".replace").c_str());
	if (outfile.fail())
		return (1);

	for (size_t i = 0; i < content.size(); i++)
	{
		if (i + s1_len <= content.size() && 
		    content.substr(i, s1_len) == s1)
		{
			outfile << s2;
			i += s1_len - 1;
		}
		else
			outfile << content[i];
	}
	outfile.close();
	return (0);
}

int	main(int argc, char **argv)
{
	char			c;
	std::ifstream	infile;
	std::string		content;

	if (argc != 4)
	{
		std::cout << "uso: ./replace <file> old_word new_word" << std::endl;
		return (1);
	}
	infile.open(argv[1]);
	if (infile.fail())
	{
		std::cout << "Error: " << argv[1] << ": no such file or directory" << std::endl;
		return (1);
	}
	while(!infile.eof() && infile >> std::noskipws >> c)
		content += c;
	infile.close();
	return (replace(argv, content));
}