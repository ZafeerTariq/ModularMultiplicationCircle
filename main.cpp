#include <iostream>
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#define SCREEN_WIDTH 1600
#define SCREEN_HEIGHT 900

#define TAU 6.28318530718

int getPoint( int N, int i, int k ) {
	return ( i * k ) % N;
}

int main() {
	const char* title = "Modular Multiplication Circle";
	sf::RenderWindow window( sf::VideoMode( SCREEN_WIDTH, SCREEN_HEIGHT ), title );
	if ( !ImGui::SFML::Init(window) ) {
		std::cout << "Could not init imgui\n";
		exit( EXIT_FAILURE );
	}

	sf::Clock clock;
	sf::Time dt;

	int N = 100;
	float k = 2;
	float radius = SCREEN_HEIGHT / 3.0f;
	sf::Vector2f center( SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f );

	sf::CircleShape circle( radius, 500 );
	circle.setOrigin( radius, radius );
	circle.setPosition( center );

	std::vector<sf::Vector2f> points;

	while( window.isOpen() ) {
		sf::Event event;
		while( window.pollEvent( event ) ) {
			ImGui::SFML::ProcessEvent( window, event );
			if( event.type == sf::Event::Closed ) {
				window.close();
			}
		}

		dt = clock.restart();
		ImGui::SFML::Update( window, dt );

		ImGui::Begin( "Menu" );
			ImGui::DragInt( "N", &N );
			if( N < 0 ) N = 0;
			ImGui::DragFloat( "k", &k, 0.01f );
			if( k < 0 ) k = 0;
		ImGui::End();

		window.clear( sf::Color( 14, 26, 37 ) );
		window.draw( circle );

		points.clear();
		for( size_t i = 0; i < N; i++ ) {
			sf::Vector2f point( center.x + radius * cos( TAU * i / N ), center.y + radius * sin( TAU * i / N ) );
			points.push_back( point );
		}
		for( size_t i = 0; i < N; i++ ) {
			int p = getPoint( N, i, k );

			sf::Vertex line[] = {
				sf::Vertex( points[i], sf::Color::Red ),
				sf::Vertex( points[p], sf::Color::Red )
			};
			window.draw( line, 2, sf::Lines );
		}

		ImGui::SFML::Render( window );
		window.display();
	}

	ImGui::SFML::Shutdown();
}