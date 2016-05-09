
//

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <math.h>
#include "token.h"
#include "STokenize.h"
#include "ETokenize.h"
#include "Shunt.h"
#include "Evaluator.h"

#include "ResourcePath.hpp"

#define PI 3.14159265

Queue<std::pair<int, double> > getPoints(string expression, double low, double high, double increment);

int main(int, char const**)
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML window");

    //Draw the x-axis
    sf::Vertex xAxis[2];
    xAxis[0].position = sf::Vector2f(0, 300);
    xAxis[0].color  = sf::Color::White;
    xAxis[1].position = sf::Vector2f(800, 300);
    xAxis[1].color  = sf::Color::White;
    //Draw the y-axis
    sf::Vertex yAxis[2];
    yAxis[0].position = sf::Vector2f(400, 0);
    yAxis[0].color  = sf::Color::White;
    yAxis[1].position = sf::Vector2f(400, 600);
    yAxis[1].color  = sf::Color::White;
    //Zoom window to a 100x100 view.
    sf::View view(sf::FloatRect(350, 250, 100, 100));
    view.setCenter(400, 300);
    //view.move(15,15);
    window.setView(view);
    
    string expression;
    
    // Start the game loop
    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        
        while (window.pollEvent(event))
        {
            switch(event.type){
                case sf::Event::Closed:
                    window.close(); //closes the window when I press the 'x' button
                    break;
                case sf::Event::KeyPressed:
                    switch (event.key.code){
                        case sf::Keyboard::Z: // Press "Z" to zoom in
                            view.zoom(0.9f);
                            window.setView(view);
                            break;
                        case sf::Keyboard::X: //Press "X" to zoom out
                            view.zoom(1.1f);
                            window.setView(view);
                            break;
                        case sf::Keyboard::W: //Press "W" to move upwards
                            view.move(0, -5);
                            window.setView(view);
                            break;
                        case sf::Keyboard::S: //Press "S" to move downwards
                            view.move(0, 5);
                            window.setView(view);
                            break;
                        case sf::Keyboard::A: //Press "A" to move left
                            view.move(-5, 0);
                            window.setView(view);
                            break;
                        case sf::Keyboard::D: //Press "D" to move right
                            view.move(5, 0);
                            window.setView(view);
                            break;
                    }
            }
        }
        window.clear();
        //draw the x and y axis
        window.draw(xAxis, 2, sf::Lines);
        window.draw(yAxis, 2, sf::Lines);
        
        //declare vertex array for graph
        sf::Vertex line[2];
        try{ //try block
            Queue<std::pair<int, double> > answers; //Queue to store the points
            expression = "(1 / x ^ 2)"; //expression to the graphed
            answers = getPoints(expression, -10, 10, .2); //call function to get the points
       
            while (answers.Size() > 1){ //while the Queue is not empty
                std::pair<int, double> p1 = answers.pop(); //get the first 2 coordinates
                std::pair<int, double> p2 = answers.peek();
                int x1 = std::get<0>(p1); //get the actual values of them
                double y1 = std::get<1>(p1);
                int x2 = std::get<0>(p2);
                double y2 = std::get<1>(p2);
                line[0].position = sf::Vector2f(x1 + 400, 300- y1); //plot them. Had to re-adjust the coordinates because SFML uses a different coordinate system.
                line[0].color = sf::Color::Red;
                line[1].position = sf::Vector2f(x2 + 400, 300- y2);
                line[1].color = sf::Color::Red;
                window.draw(line, 2, sf::Lines); //draw the lines
            }
        }
        catch (invalidExpression){ //catch
            cout<<"The number of left and right parenthesis do not match"<<endl;
        }
        window.display(); //display the updated window
  
    }

    return EXIT_SUCCESS;
}

Queue<std::pair<int, double> > getPoints(string expression, double low, double high, double increment){
    Queue<std::pair<int, double> > answers; //Queue to store the points
    for (double x = low; x <= high; x = x + increment){
        Evaluator eval(expression, x); //create Evaluator object
        double answer = eval.evaluate(); //get the y-value
        int xValue = x * 5; //scale up 5x
        answer = answer * 5; //scale up 5x
        std::pair<int, double> coordinate (xValue, answer); //create a coordinate pair
        answers.push(coordinate); //push into the Queue
    }
    return answers; //return the Queue of points.
}
































