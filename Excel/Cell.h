#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<SFML/Graphics.hpp>
using namespace std;
using namespace sf;
class Node
{

	sf::RectangleShape cell;
	Font TimesRoman;
	Text Txt;

public:

	int row, col;
	Node* left;
	Node* right;
	Node* up;
	Node* down;
	string Data = "";
	bool Contains(int x, int y)
	{
		if (this->cell.getGlobalBounds().contains(x, y))
			return true;
		return false;
	}
	void ShiftTextLeft(RenderWindow&window)
	{
		int x = Txt.getPosition().x;
		int y = Txt.getPosition().y;
		Txt.setPosition(x - 2, y);
		window.draw(Txt);

	}
	void ShiftTextRight(RenderWindow &window)
	{
		int x = Txt.getPosition().x;
		int y = Txt.getPosition().y;
		Txt.setPosition(x + 2, y);
		window.draw(Txt);

	}
	
	void DrawCell(int ri, int ci, RenderWindow& window,int horizontalOffset,int verticalOffset)
	{
	
		cell.setSize(Vector2f(80, 25));
		cell.setPosition(ci , ri);
		Txt.setString(Data);
		Txt.setPosition(static_cast<long long int> (ci)+25 - (Data.length()) - 5, ri + 3);
	
		cell.move(-horizontalOffset * 200, -verticalOffset * 400);
		Txt.move(-horizontalOffset * 200, -verticalOffset * 400);
		window.draw(cell);
		window.draw(Txt);
	}
	void Setcolor(sf::Color clr) 
	{
		cell.setFillColor(clr);
	}
	Vector2f GetPosition()
	{
		return Vector2f (cell.getPosition().x,cell.getPosition().y);
	}
	sf::Color GetColor()
	{
		return cell.getFillColor();
	}
	void BoxSelected()
	{
		Vector2f S(cell.getSize().x - 1, cell.getSize().y - 1);
		cell.setSize(S);
		cell.setOutlineThickness(2);
		cell.setOutlineColor(Color(0, 120, 0));
	}
	Node(string D = "-", Node* _u = nullptr, Node* _d = nullptr, Node* _l = nullptr, Node* _r = nullptr) :Data(D), up(_u), down(_d), left(_l), right(_r)
	{
		TimesRoman.loadFromFile("Lato.ttf");
		Txt.setFont(TimesRoman);
		Txt.setCharacterSize(15);
		Txt.setFillColor(Color::Black);
		cell.setFillColor(Color::White);
		cell.setOutlineThickness(1);
		cell.setOutlineColor(Color(135, 135, 135));
	}



};

