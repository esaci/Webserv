#include "../include/w_library.hpp"

size_t		RP15::extract_body_check( void ){
	size_t	line = 0;
	DATA	tmp_data;

	for(DATA::iterator it = parse_data.begin(); it != parse_data.end(); it++, line++)
	{
		tmp_data.clear();
		for(;it < parse_data.end() && (*it == '\n'/*  || *it == '\r' */); it++)
			;
		for(; it < parse_data.end() && *it != '\n'; it++)
		{
			// if (*it == '\r')
				// break;
			tmp_data.push_back(*it);
		}
		if (tmp_data.size() == 1)
		{
			std::cout << line << " eme ligne ou commence le body\n";
			return (line);
		}
	}
	return (0);
}
