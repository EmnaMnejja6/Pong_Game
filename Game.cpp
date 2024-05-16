#include "Game.h"
using namespace std;
Game::Game(sf::RenderWindow& window)
{
    std::cout << "game created";
    maxSpeed = 300.0f;
    //charger le font2
    font2.loadFromFile("ressources/pixel.otf");
    //charger l'image de background
    bg.loadFromFile("ressources/bg3.jpg");
    background.setTexture(bg);
    //initialisation de la balle
    ball.setRadius(15);
	ball.setPosition(ballPosX, ballPosY);
    //raquettes
    raquetteGauche.setSize(Vector2f(raquettesWidth, raquettesHeight));
	raquetteGauche.setPosition(posRaquettesLeftX, posRaquettesLeftY);

    raquetteDroite.setSize(Vector2f(raquettesWidth, raquettesHeight));
	raquetteDroite.setPosition(posRaquettesRightX, posRaquettesLeftY);

	setText(scoreZone,font);
    //son de la balle quand elle touche la raquette
    buffer.loadFromFile("ressources/ballsound.ogg");
    ballSound.setBuffer(buffer);
    //game over sound
    gameoverbuffer.loadFromFile("ressources/gameover.ogg");
    gameoversound.setBuffer(gameoverbuffer);
    music.setVolume(40);

    ballDir=Vector2f(1.5f, 2);
    ballPosX= WIN_WIDTH / 2;
    ballPosY = WIN_HEIGHT / 2;

    //rectangle de end
    end.setSize(Vector2f(800, 600));
    end.setFillColor(Color(34, 34, 99, 255));
    
    endgame.loadFromFile("ressources/gameover.png");
    gameover.setTexture(endgame);

    gameOverSoundPlayed = false;

    // Play music
    
    if (!music.openFromFile("ressources/gamemusic0.ogg"))
        std::cout << "Erreur de chargement de musique";

    //music.setVolume(40);
}

void Game::start_game(sf::RenderWindow& window, sf::Event event, int nb_players)
{
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
    cout << "starting" << endl;
    gameRunning = true;
    gameOverSoundPlayed = false;
    scoreA = 0;
    scoreB = 0;
    setText(scoreZone, font);

    while (window.isOpen())
    {
        music.play();

        while (scoreA < 11 && scoreB < 11 && gameRunning)
        {
            gameoversound.stop();
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                {
                    music.stop();
                    ballSound.stop();
                    window.close();
                    return;
                }
                    
                else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
                {
                    music.stop();
                    ballSound.stop();
                    window.close();
                    return;
                }
                if (nb_players == 1)
                    input.InputHandler1Player(event, window);
                else
                    input.InputHandler2Players(event, window);
            }

            CheckBtn(window, nb_players);

            raquetteDroite.setPosition(posRaquettesRightX, posRaquettesRightY);
            raquetteGauche.setPosition(posRaquettesLeftX, posRaquettesLeftY);
            

            moveBall();
            ball.setPosition(ballPosX, ballPosY);
            draw_all(window);

            window.display();

            if (scoreA >= 11 || scoreB >= 11) {
                gameRunning = false;
                music.stop();
                break;
            }
        }

        // Display end game 
        window.clear(sf::Color::Black);

        gameover.setPosition(sf::Vector2f(WIN_WIDTH / 2, WIN_HEIGHT / 2));
        gameover.setOrigin(gameover.getGlobalBounds().width / 2, gameover.getGlobalBounds().height / 2);


        restartGame.setCharacterSize(50);
        restartGame.setOrigin(restartGame.getGlobalBounds().width / 2, restartGame.getGlobalBounds().height / 2);
        restartGame.setPosition(WIN_WIDTH / 2, WIN_HEIGHT-80);        
        restartGame.setFillColor(sf::Color::Red);
        restartGame.setString("Press Enter to Restart");
        restartGame.setFont(font2);
        if (!gameOverSoundPlayed) {
            gameoversound.play();
            gameOverSoundPlayed = true;
        }
        winner = (scoreA > scoreB) ? 1 : 2;

        window.draw(end);
        
        window.draw(gameover);
        printwinner(winnertext, winner);
        window.draw(restartGame);
        window.draw(winnertext);
        window.display();

        Event aevent;
        while (window.pollEvent(aevent))
        {
            if (aevent.type == sf::Event::Closed)
                window.close();
            else if (aevent.type == sf::Event::KeyPressed && aevent.key.code == sf::Keyboard::Escape)
                window.close();
            else if (aevent.type == sf::Event::KeyPressed && aevent.key.code == sf::Keyboard::Enter)
            {
                music.stop();
                start_game(window, aevent, nb_players);
                break;
            }
        }
    }
}

Game::~Game() {}

void Game::draw_all(sf::RenderWindow& window)
{
	window.draw(background);
	window.draw(scoreZone);
	window.draw(ball);
	window.draw(raquetteGauche);
	window.draw(raquetteDroite);

}

void Game::moveBall()
{
    //pos balle
    ballPosX += ballDir.x * ballSpeed;
    ballPosY += ballDir.y * ballSpeed;
    //gerer les collisions de la balle
    //raquette gauche ou droite touchée?
    if ((ballPosX < posRaquettesLeftX + raquettesWidth
        && ballPosX > posRaquettesLeftX
        && ballPosY < posRaquettesLeftY + raquettesHeight
        && ballPosY > posRaquettesLeftY)
        ||
        (ballPosX > posRaquettesRightX - raquettesWidth
            && ballPosX < posRaquettesRightX
            && ballPosY < posRaquettesRightY + raquettesHeight
            && ballPosY > posRaquettesRightY))
    {
        ballSound.play();
        ballDir.x *= -1;
    }
    // mur gauche 
    if (ballPosX < 0)
    {
        scoreB++;
        ballPosX = WIN_WIDTH / 2;
        ballPosY = WIN_HEIGHT / 2;
        ballDir.x = fabs(ballDir.x);
        ballDir.y *= -1;
        setText(scoreZone,font);
    }
    // mur droit 
    if (ballPosX > WIN_WIDTH)
    {
        scoreA++;
        ballPosX = WIN_WIDTH / 2;
        ballPosY = WIN_HEIGHT / 2;
        ballDir.x = -fabs(ballDir.x);
        ballDir.y *= -1;
        setText(scoreZone,font);
    }
    //mur haut ou bas 
    if (ballPosY > WIN_HEIGHT || ballPosY < 0)
    {
        ballDir.y *= -1; //la balle rebondit
    }

}

void Game::setText(Text& scoreZone, sf::Font& font)
{
    if (!font.loadFromFile("ressources/poppins.ttf"))
        cout << "erreur de chargement de font";
    scoreZone.setString("  "+to_string(scoreA) + "      " + to_string(scoreB));
    scoreZone.setFont(font);
    scoreZone.setCharacterSize(40);
    scoreZone.setPosition(Vector2f(WIN_WIDTH/2-80,20));

}
void Game::printwinner(sf::Text& winnertext ,int winner_player)
{
    if (!font.loadFromFile("ressources/poppins.ttf"))
        cout << "erreur de chargement de font";
    winnertext.setString("Player  "+to_string(winner_player)+"  won!");
    winnertext.setFont(font2);
    winnertext.setCharacterSize(50);
    winnertext.setOrigin(winnertext.getGlobalBounds().width / 2, winnertext.getGlobalBounds().height / 2);
    winnertext.setPosition(WIN_WIDTH / 2, 50);
    winnertext.setFillColor(sf::Color::White);
}

void Game::CheckBtn(sf::RenderWindow &window, int nb_players)
{
  
    delta = clock.restart(); //get elapsed time since last frame

    switch (nb_players)
    {
    case 1:
        //raquette droite jouée automatiquement
        computerPlay(delta);
        //Raquette gauche
        if (input.GetButton().up == true)
        {
            posRaquettesLeftY -= raquettesSpeed;
            if (posRaquettesLeftY < 0)
                posRaquettesLeftY = 0;
        }
        if (input.GetButton().down == true)
        {
            posRaquettesLeftY += raquettesSpeed;
            if (posRaquettesLeftY + raquettesHeight > WIN_HEIGHT)
                posRaquettesLeftY = WIN_HEIGHT - raquettesHeight;
        }
        if (input.GetButton().escape == true)
        {
            window.close();
        }
        break;
        
    case 2: 
        //Raquette gauche
        if (input.GetButton().up == true)
        {
            posRaquettesLeftY -= raquettesSpeed;
            if (posRaquettesLeftY < 0)
                posRaquettesLeftY = 0;
        }
        if (input.GetButton().down == true)
        {
            posRaquettesLeftY += raquettesSpeed;
            if (posRaquettesLeftY + raquettesHeight > WIN_HEIGHT)
                posRaquettesLeftY = WIN_HEIGHT -raquettesHeight;
        }

        //Raquette droite
        if (input.GetButton().left == true)
        {
            posRaquettesRightY -= raquettesSpeed;
            if (posRaquettesRightY < 0)
                posRaquettesRightY = 0;
        }
        if (input.GetButton().right == true)
        {
            posRaquettesRightY += raquettesSpeed;
            if (posRaquettesRightY + raquettesHeight > WIN_HEIGHT)
                posRaquettesRightY = WIN_HEIGHT - raquettesHeight;
        }

        if (input.GetButton().escape == true)
        {
            window.close();
        }
        break;
}
}



void Game::computerPlay(sf::Time delta) {
    // calculer le centre de la balle
    float ballCenterY = ballPosY + ball.getTextureRect().height / 2.0f;
    // calculer la position cible
    float targetY = ballCenterY - raquettesHeight / 2.0f;
    // ajouter un délai 
    float randomOffset = static_cast<float>(rand() % 21 - 10); 
    targetY += randomOffset;
    // calculer le mouvement maximal possible
    float maxMovement = maxSpeed * delta.asSeconds();
    // déterminer la direction de la balle
    float direction = targetY - posRaquettesRightY;

    //limiter le mouvement à la distance maximale autorisée
    float movement = std::abs(direction);
    if (movement > maxMovement) {
        movement = maxMovement;
    }

    // Ajouter un léger délai de réaction
    static float reactionDelay = 0.05f; // Délai en secondes
    static float timeSinceLastMove = 0.0f;
    timeSinceLastMove += delta.asSeconds();
    if (timeSinceLastMove < reactionDelay) {
        return; // Ne rien faire pendant ce frame pour créer un délai
    }
    timeSinceLastMove = 0.0f; // Réinitialiser le délai

    // Mettre à jour la position de la raquette
    if (direction < 0) {
        // Monter
        posRaquettesRightY -= movement;
    }
    else if (direction > 0) {
        // Descendre
        posRaquettesRightY += movement;
    }

    // Arrondir la position de la raquette à l'entier le plus proche
    posRaquettesRightY = std::round(posRaquettesRightY);

    // Limiter la position de la raquette aux bords de la fenêtre
    if (posRaquettesRightY < 0.0f) {
        posRaquettesRightY = 0.0f;
    }
    else if (posRaquettesRightY + raquettesHeight > WIN_HEIGHT) {
        posRaquettesRightY = WIN_HEIGHT - raquettesHeight;
    }
}

