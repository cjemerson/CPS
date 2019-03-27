// alt_main.cpp
//
// Alternative main to create Shapes based on an input file.


#include <iostream>
#include <fstream>
#include <map>

#include "TextParser.hpp"
#include "BasicShapes.hpp"
#include "CompoundShapes.hpp"


int main(int argc, char const *argv[])
{
	if ( argc == 1 )
	{
		std::cout << "Usage: \"" << argv[0] << " <input_filename> [<output_filename>]\"" << std::endl;
		return 0;
	}

	TextParser file(argv[1]);

	std::map<std::string, std::unique_ptr<Shape>> shapes;

	for (int i = 0; i < file.size(); ++i)
	{
		auto tokens = file.getLine(i);

		if (tokens.size() < 3 || tokens[1] != "=")
		{
			if (tokens.size() > 1 && tokens[0] == "output")
			{
				auto output = shapes[tokens[1]]->evaluate();

				if (argc > 2)
				{
					std::ofstream file(argv[2]);

				    if(file.is_open())
			    	{
			    		file << output << std::endl;
			    		return 0;
					}
					else
					{
						std::cout << "Unable to open output file." << std::endl;
					}
				}
				else
				{
					std::cout << output << std::endl;
					return 0;
				}
			}

			// This is an invalid command.
			continue;
		}

		auto name = tokens[0];
		auto typeOfShape = tokens[2];

		// std::cout << typeOfShape << std::endl;

		if (typeOfShape == "circle")
		{
			if (tokens.size() < 4)
			{
				// Invalid
				continue;
			}
			shapes[name] = std::make_unique<Circle>(TextParser::parseFloat(tokens[3]));
		}
		else if (typeOfShape == "rectangle")
		{
			if (tokens.size() < 5)
			{
				// Invalid
				continue;
			}

			shapes[name] = std::make_unique<Rectangle>(TextParser::parseFloat(tokens[3]), TextParser::parseFloat(tokens[4]));
		}
		else if (typeOfShape == "polygon")
		{
			if (tokens.size() < 5)
			{
				// Invalid
				continue;
			}

			shapes[name] = std::make_unique<Polygon>((unsigned int) TextParser::parseInt(tokens[3]), TextParser::parseFloat(tokens[4]));
		}
		else if (typeOfShape == "spacer")
		{
			if (tokens.size() < 5)
			{
				// Invalid
				continue;
			}

			shapes[name] = std::make_unique<Spacer>(TextParser::parseFloat(tokens[3]), TextParser::parseFloat(tokens[4]));
		}
		else if (typeOfShape == "rotated")
		{
			if (tokens.size() < 5)
			{
				// Invalid
				continue;
			}

			shapes[name] = std::make_unique<Rotated>(*shapes[tokens[3]], TextParser::parseFloat(tokens[4]));
		}
		else if (typeOfShape == "scaled")
		{
			if (tokens.size() < 6)
			{
				// Invalid
				continue;
			}

			shapes[name] = std::make_unique<Scaled>(*shapes[tokens[3]], TextParser::parseFloat(tokens[4]), TextParser::parseFloat(tokens[5]));
		}
		else if (typeOfShape == "vertical")
		{
			if (tokens.size() < 4)
			{
				// Invalid
				continue;
			}

			std::vector<std::reference_wrapper<const Shape>> v;

			for (std::size_t j = 3; j < tokens.size(); ++j)
				v.push_back(*shapes[tokens[j]]);

			shapes[name] = std::make_unique<Vertical>(v);
		}
		else if (typeOfShape == "horizontal")
		{
			if (tokens.size() < 4)
			{
				// Invalid
				continue;
			}

			std::vector<std::reference_wrapper<const Shape>> v;

			for (std::size_t j = 3; j < tokens.size(); ++j)
				v.push_back(*shapes[tokens[j]]);

			shapes[name] = std::make_unique<Horizontal>(std::move(v));
		}
		else
		{
			// Invalid
			continue;
		}
	}

	// Input file never had "output <shape_name>"
	return 0;
}
