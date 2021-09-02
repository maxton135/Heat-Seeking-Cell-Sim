#include "Simulation.h"
#include <cmath>

// Constructor
Simulation::Simulation()
{
    this->initVariables();
    this->initWindow();
}

// Destructor
Simulation::~Simulation()
{
    delete this->window;
}

// Private Functions
void Simulation::initVariables()
{
    this->window = nullptr;
    this->maxCells = 10;
    this->maxHS = 5;

}

void Simulation::initWindow()
{
    this->videoMode.height = 1200;
    this->videoMode.width = 1600;
    this->window = new sf::RenderWindow(this->videoMode, "Cell Heat Simulation", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(72);
}

// Accessor Functions
const bool Simulation::running() const
{
    return this->window->isOpen();
}

// Public Functions
void Simulation::update()
{
    this->pollEvents();
    this->updateCells();
    this->updateMousePositions();
}

void Simulation::render()
{
    this->window->clear();
    this->renderHotspots();
    this->renderCells();
    this->window->display();
}

void Simulation::pollEvents()
{
    while (this->window->pollEvent(this->ev))
    {
        switch(this->ev.type)
        {
            case sf::Event::Closed:
                this->window->close();
                break;
            case sf::Event::KeyPressed:
                if (this->ev.key.code == sf::Keyboard::Escape)
                    this->window->close();
                break;
            case sf::Event::MouseButtonPressed:
                if (this->ev.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "the left button was pressed" << std::endl;
                    this->spawnCell();
                }
                else if (this->ev.mouseButton.button == sf::Mouse::Right)
                {
                    std::cout << "the right button was pressed" << std::endl;
                    this->spawnHS();
                }
        }
    }
}

void Simulation::updateMousePositions()
{
    this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}

void Simulation::spawnCell()
{
    sf::CircleShape newCell;
    newCell.setRadius(10.f);
    newCell.setFillColor(sf::Color::White);
    newCell.setOutlineColor(sf::Color::Blue);
    newCell.setOutlineThickness(2.f);
    newCell.setOrigin(10.f, 10.f);
    newCell.setPosition(this->mousePosWindow.x, this->mousePosWindow.y);
    newCell.setScale(2,1);
    cells.push_back(newCell);
    prevDist.push_back(INT_MAX);
}

void Simulation::updateCells()
{
    //for (sf::CircleShape &cell : this->cells)
    for (int i = 0; i < cells.size(); i++)
    {
        int curDist= INT_MAX;
        for (int j = 0; j < hotspots.size(); j++)
        {
            int thisDist = findDistance(cells[i].getPosition(), hotspots[j].getPosition());
            if (thisDist < curDist)
                curDist = thisDist;
        }
        
        if (curDist < prevDist[i])
        {
            prevDist[i] = curDist;
            cells[i].move(cos(cells[i].getRotation()*3.14159265/180)*3, sin(cells[i].getRotation()*3.14159265/180)*-3);
        }
        else
        {
            int decision = rand() % 2;
            if (decision == 0)
                cells[i].rotate(30);
            else
                cells[i].rotate(-30);
            cells[i].move(cos(cells[i].getRotation()*3.14159265/180)*3, sin(cells[i].getRotation()*3.14159265/180)*-3);

        }

        //cells[i].move(cos(cells[i].getRotation()*3.14159265/180)*3, sin(cells[i].getRotation()*3.14159265/180)*-3);
    }
}

void Simulation::renderCells()
{
    for (auto &cell : this->cells)
    {
        this->window->draw(cell);
    }
}

void Simulation::spawnHS()
{
    sf::CircleShape newHS;
    newHS.setRadius(100.f);
    newHS.setFillColor(sf::Color(255,165,0,128));
    newHS.setPosition(this->mousePosWindow.x - 100, this->mousePosWindow.y - 100);
    hotspots.push_back(newHS);
}

void Simulation::renderHotspots()
{
    for (auto &hs : this->hotspots)
    {
        this->window->draw(hs);
    }
}

int Simulation::findDistance(sf::Vector2f a, sf::Vector2f b)
{
    int y = b.y - a.y;
    int x = b.x - a.x;
    return sqrt((x*x)+(y*y));
}