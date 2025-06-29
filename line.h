#ifndef LINE_H
#define LINE_H

#include <SFML/Graphics.hpp>

class Line : sf::Drawable {
public:
	sf::Vertex start;
	sf::Vertex end;

	Line( sf::Vertex start, sf::Vertex end ) : start( start ), end( end ) {}

	void draw( sf::RenderTarget& target, sf::RenderStates states ) const {

	}
};

#endif