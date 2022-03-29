#ifndef INDEXCOMP_HPP
#define INDEXCOMP_HPP

# include <functional>
# include <string>

	struct indexcomp : public std::binary_function<std::string, std::string, bool>
	{
		bool operator()(const std::string& lhs, const std::string& rhs) const;
	};

#endif