#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include <SFML/System.hpp>
#include <algorithm>
#include <cstdlib> 
#include <ctime>  
#include "main.h"
#include "input.h"
class Game
{
private:
	bool startGame;

	sf::Texture bg;
	sf::Sprite background;

	sf::RectangleShape end;
	//input 
	Input input;

	//raquettes
	int posRaquettesLeftX = 50;
	int posRaquettesRightX = WIN_WIDTH - 70;
	int posRaquettesLeftY = WIN_HEIGHT / 2;
	int posRaquettesRightY = posRaquettesLeftY;
	int raquettesSpeed = 13;
	int raquettesHeight = 150;
	int raquettesWidth = 20;
	float maxSpeed;


	//info balle
	int ballSpeed = 5;
	sf::Vector2f ballDir;
	int ballPosX;
	int ballPosY;

	//score
	sf::Text scoreZone;
	int scoreA = 0, scoreB = 0;


	//endgame 
	sf::Text restartGame;

	sf::Texture endgame;
	sf::Sprite gameover;
	

	//fonts
	sf::Font font;
	sf::Font font2;


	//Ball
	sf::CircleShape ball;

	//Raquette gauche
	RectangleShape raquetteGauche;

	//Raquette droite
	RectangleShape raquetteDroite;

	//music and sound effects
	Music music;
	SoundBuffer buffer;
	Sound ballSound;
	SoundBuffer gameoverbuffer;
	Sound gameoversound;

	//clock
	Clock clock; 
	Time delta;

	bool gameOverSoundPlayed = false;
	bool gameRunning;

	//winner score
	int winner;
	sf::Text winnertext;

public:
	Game(sf::RenderWindow& window);
	~Game();
	void start_game(sf::RenderWindow& window, sf::Event event, int nb_players);
	void draw_all(sf::RenderWindow& window);
	void moveBall();
	void CheckBtn(sf::RenderWindow& window,int nb_players);
	void setText(Text& scoreZone,sf::Font& font);
	void computerPlay(sf::Time delta);
	void printwinner(sf::Text& ,int winner_player);
};

