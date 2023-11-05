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
	Font _TimesRoman;
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
	
	void DrawCell(int y, int x, RenderWindow& window,int horizontalOffset,int verticalOffset,sf::Font TimesRoman)
	{
		if (!Txt.getFont())
		{
			_TimesRoman = TimesRoman;
			Txt.setFont(_TimesRoman);
		}
		cell.setSize(Vector2f(80, 25));
		cell.setPosition(x, y);
		Txt.setString(Data);
		Txt.setPosition(x+40/2-Data.length()-2, y+3/2);
	
		cell.move(-horizontalOffset * 70, -verticalOffset * 20);
		Txt.move(-horizontalOffset * 70, -verticalOffset * 20);
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
		row = 0; col = 0;
		//TimesRoman.loadFromFile("Lato.ttf");
	//	Txt.setFont(TimesRoman);
		Txt.setCharacterSize(15);
		Txt.setFillColor(Color::Black);
		cell.setFillColor(Color::White);
		cell.setOutlineThickness(1);
		cell.setOutlineColor(Color(135, 135, 135));
	}



};

