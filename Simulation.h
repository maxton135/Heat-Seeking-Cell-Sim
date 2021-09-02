#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Simulation
{
    private:
        // Window variables
        sf::RenderWindow* window;
        sf::VideoMode videoMode;
        sf::Event ev;

        // Mouse position
        sf::Vector2i mousePosWindow;

        // Game object variables
        int maxCells;
        std::vector<sf::CircleShape> cells;
        std::vector<int> prevDist;
        int maxHS;
        std::vector<sf::CircleShape> hotspots;

        // Private functions
        void initVariables();
        void initWindow();
        void insertCell();
    
    public:
        // Constructor/Destructor
        Simulation();
        virtual ~Simulation();

        // Accessors
        const bool running() const;
        
        // Public functions
        void pollEvents();
        void updateMousePositions();
        void spawnCell();
        void updateCells();
        void renderCells();
        void spawnHS();
        void renderHotspots();
        int findDistance(sf::Vector2f a, sf::Vector2f b);
        void update();
        void render();
};


#endif