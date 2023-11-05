#pragma once
#include"Cell.h"
#include<iostream>
#include<string>
#include<vector>
#include<SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Excel
{
	Node* head;
	Node* Current;
	Node* Prev;
	int no_of_rows;
	int no_of_cols;
	int left_margin;
	int top_margin;
	vector<Node*>selected_cells;
	vector<string>Copy;
	int highlighted_rows;
	int highlighted_columns;
	Font TimesRoman;
public:
	Excel()
	{
		head = new Node("");
		left_margin = 0;
		top_margin = 20;
		Node* temp = head;
		highlighted_rows = 0;
		highlighted_columns = 0;
		for (int i = 1; i < 20; i++)
		{
			temp->right = new Node("", nullptr, nullptr, temp, nullptr);
			temp = temp->right;
		}
		head->down = new Node("", head);
		Node* DownHead = head->down;
		Node* D_temp = head->down;
		temp = head->right;
		for (int i = 1; i < 15; i++)
		{
			for (int j = 1; j < 20; j++)
			{
				D_temp->right = new Node("", temp, nullptr, D_temp, nullptr);
				temp->down = D_temp->right;
				D_temp = D_temp->right;
				temp = temp->right;
			}
			if (i == 14)break;
			temp = DownHead->right;
			DownHead->down = new Node("", DownHead);
			DownHead = DownHead->down;
			D_temp = DownHead;	
		}
		no_of_rows = 15;
		no_of_cols = 20;
		TimesRoman.loadFromFile("TimesRoman.ttf");

	}

	void DrawGrid(RenderWindow &window)
	{

		Node* DownHead = head;
		Node* RightHead= head;
		for (int ri=20; DownHead;ri+=25)
		{
			for (int ci=0; RightHead;ci+=80)
			{
			RightHead->DrawCell(ri, ci, window);

				
				RightHead = RightHead->right;
			}
			DownHead=DownHead->down;
			RightHead = DownHead;
		}
	
		
	}

	void InsertData(string A,int ri,int ci)
	{

		Node* T = head;

		for (int i = 0; i < ri; i++)
		{
			T = T->down;
		}
		for (int i = 0; i < ci; i++)
		{
			T = T->right;
		}
		T->Data = A;
	}

	void InsertRowBelow(int row_index)
	{
		if (row_index <= 0 || row_index > no_of_rows)return;
		if (row_index == no_of_rows)
		{
			InsertRowATBottom();
			return;
		}
		
		Node* current =head;

		for (int i = 0; i <row_index; i++)
		{
			current = current->down;
		}
		Node* _down = current;
		Node* _up = current->up;
		current= new Node("", _up, _down);
		_up->down = current;
		_down->up = current;
		_up = _up->right;
		_down=_down->right;

		while (_up)
		{
			current->right = new Node("", _up, _down, current);
			_up->down = current->right;
			_down->up = current->right;
			_up = _up->right;
			_down = _down->right;
			current = current->right;
		}
		no_of_rows++;
	}
	void InsertRowAtTop()
	{
		Node* current = head;

		Node* _down = current;

		current = new Node("n", nullptr, _down);
		head = current;
		_down->up = current;
		_down = _down->right;

		while (_down)
		{
			current->right = new Node("", nullptr, _down, current);
			_down->up = current->right;
			_down = _down->right;
			current = current->right;
		}
		no_of_rows++;
	}	
	void InsertRowAbove(int row_index)
	{
		if (row_index > no_of_rows)return;
		if (row_index == 1)
		{
			InsertRowAtTop(); return;
		}
		InsertRowBelow(row_index - 1);
	}
	void InsertRowATBottom()
	{
		
		Node* current = head;
		Node* _up{};

		while(current)
		{
			_up = current;
			current = current->down;
		}
		current = new Node("n", _up);
		_up->down = current;
		_up = _up->right;


		while (_up)
		{
			current->right = new Node("", _up,nullptr, current);
			_up->down = current->right;
			_up = _up->right;
			current = current->right;
		}

		no_of_rows++;
	}

	void InsertColumnAtLeft(int col_index)
	{
		if (col_index > no_of_cols)return;
		if (col_index == 1)
		{
			InsertColumnAtStart();
			return;
		}
		InsertColumnAtRight(col_index - 1);
	}
	void InsertColumnAtStart()
	{
		
		Node* current = head;
		Node* _right= current;
		head=current = new Node("n", nullptr, nullptr,nullptr,_right);
		
		_right->left = current;
		_right= _right->down;

		while (_right)
		{
			current->down = new Node("", current, nullptr, nullptr,_right);
			_right->left = current->down;
			_right = _right->down;		
			current = current->down;
		}
		no_of_cols++;
	}
	void InsertColumnAtEnd()
	{
		Node* current = head;
		Node* _left{};
		while(current)
		{
			_left = current;
			current = current->right;
		}
		current = new Node("n", nullptr, nullptr,_left);
		_left->right = current;
		_left= _left->down;

		while (_left)
		{
			current->down = new Node("", current, nullptr, _left);
			_left->right = current->down;
			_left = _left->down;
			current = current->down;
		}
		no_of_cols++;
	}
	Node*& GetNodeAt(int ri, int ci)
	{
		Node* T = head;
		for (int i = 0; i < ri; i++)
		{
			if (!T)break;
			T = T->down;
		}
		for (int i = 0; i < ci; i++)
		{
			if (!T)break;
			T = T->right;
		}
		return T;
	}
	void InsertColumnAtRight(int col_index)
	{
		if ( col_index<= 0 || col_index > no_of_cols)return;
		if (col_index == no_of_cols)
		{
			InsertColumnAtEnd();		
			return;
		}
		Node* current = head;

		for (int i = 0; i <col_index; i++)
		{
			current = current->right;
		}
		Node* _left= current->left;
		Node* _right= current;
		current = new Node("n", nullptr, nullptr,_left,_right);
		_left->right = current;
		_right->left = current;
		_left= _left->down;
		_right= _right->down;

		while (_left)
		{
			current->down = new Node("", current, nullptr, _left,_right);
			_left->right = current->down;
			_right->left = current->down;
			_left = _left->down;
			_right = _right->down;		
			current = current->down;
		}
		no_of_cols++;
	}
	int DisplayOptions(int Pos_x,int Pos_y)
	{
		sf::RenderWindow window(sf::VideoMode(150, 200), "options", sf::Style::Close | sf::Style::Resize);
		RectangleShape highlighter;
		sf::Color transparentGrey(192, 192, 192, 128);
		Color Gray(160, 160, 160, 255);
		highlighter.setSize(Vector2f(150, 20));
		highlighter.setFillColor(Color(0,0,0,0));
		Text insert_below;
		insert_below.setFont(TimesRoman);
		insert_below.setPosition(5, 3);
		insert_below.setCharacterSize(15);
		insert_below.setString("Insert row below");
		insert_below.setFillColor(Color::Black);
		Text insert_above;
		insert_above.setFont(TimesRoman);
		insert_above.setPosition(5, 25);
		insert_above.setCharacterSize(15);
		insert_above.setString("Insert row above");
		insert_above.setFillColor(Color::Black);
		Vector2i mouse_pos;
			window.setPosition(sf::Vector2i(Pos_x, Pos_y));
			while (window.isOpen()) 
			{
				sf::Event evnt;
				window.clear(Color::White);
				while (window.pollEvent(evnt)) 
				{
					mouse_pos = sf::Mouse::getPosition(window);
					if (evnt.type == sf::Event::Closed)
						window.close();
					else if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left)
					{
						if (insert_below.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
							return 1;
						if (insert_above.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
							return 2;
					}

				
				}
				if (insert_below.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
				{
					highlighter.setPosition(0, 3);
					highlighter.setFillColor(transparentGrey);
					highlighter.setOutlineColor(Gray);
				}
				else if (insert_above.getGlobalBounds().contains(mouse_pos.x, mouse_pos.y))
				{
					highlighter.setPosition(0, 25);
					highlighter.setFillColor(transparentGrey);
					highlighter.setOutlineColor(Gray);
				}
				else
				{
					insert_below.setFillColor(Color::Black);
					highlighter.setFillColor(Color(0, 0, 0, 0));
					highlighter.setOutlineColor(Color::White);
				}

				window.draw(highlighter);
				window.draw(insert_below);
				window.draw(insert_above);
				window.display();

			}
	
	
	
	}
	bool HasSameRow(Node* A, Node* B,bool IsRight)
	{
		if(IsRight)
		{
			for (int i = 0; i < highlighted_columns; i++)
			{
				if (A == B)return true;
				A = A->left;

			}
		}
		return false;
	}
	void LaunchExcel()
	{
		
			sf::RenderWindow window(sf::VideoMode(1375, 696), "Mini_Excel_Sheet", sf::Style::Close | sf::Style::Resize);
			window.setPosition(sf::Vector2i(-10, 0));
			sf::View view;
			sf::Vector2f mouseWorldPosition ;
			view.setSize(1375, 696);
			view.setCenter((1375 / 2) , (696 / 2));
			view.setViewport(sf::FloatRect(0, 0,1, 1));
			sf::Vector2f scrollableArea(2420, 1500);
			bool isDragging = false;
			sf::Vector2f lastMousePosition;
			sf::RectangleShape Nav;
			Nav.setSize(Vector2f(2000,20));
			sf::Color greyColor(128, 128, 128);
			Nav.setFillColor(greyColor);
			Nav.setPosition(0, 0);
			bool edit_text_selected = false;
			Node* T{};
			RectangleShape Highlighted_box;
			Highlighted_box.setSize(Vector2f(79, 24));
			Highlighted_box.setFillColor(Color(0, 0, 0, 0));
			Highlighted_box.setOutlineColor(Color(0, 130, 0));
			Highlighted_box.setOutlineThickness(3);
			bool leftshift = false;
			bool rightshift = false;
			sf::Vector2i lastRightClickPos;
			bool up_or_left = false;
			bool selected_up = false;
			bool selected_down = false;
			bool selected_left = false;
			bool selected_right = false;
			sf::Color transparentGrey(255, 255, 255, 190);
			int x, y;

			while (window.isOpen()) {
				sf::Event evnt;
				window.clear();
				while (window.pollEvent(evnt)) {
					if (evnt.type == sf::Event::Closed)
						window.close();
					
					else if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left)
					{
						mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
						int height_of_cell = 25;
						int width_of_cell = 80;
						 x = (mouseWorldPosition.x - left_margin) / width_of_cell;
						 y = (mouseWorldPosition.y - top_margin) / height_of_cell; 
						T = GetNodeAt(y, x);
						 Highlighted_box.setSize(Vector2f(79, 24));
						 Current = T;
						 Prev = T;
						 highlighted_columns = 1;
						 highlighted_rows = 1;
						 up_or_left = false;;
					}					
					if (evnt.type == sf::Event::TextEntered) 
					{
						if (Current)
						{
							
							if (evnt.text.unicode < 128)
							{
								if (evnt.text.unicode == 8) 
								{ 
									if (!Current->Data.empty())
									{
										Current->Data.pop_back();
									}
								}
								else if(evnt.text.unicode >= 48 && evnt.text.unicode <= 57)
								{
									if(Current->Data.length()<7)
										
									Current->Data += static_cast<char>(evnt.text.unicode);
									
								}
							}
						}
					}
					if (evnt.type == sf::Event::KeyPressed) 
					{

						if (evnt.key.shift)
						{
							if (evnt.key.code == sf::Keyboard::Down)
							{

								Vector2f Box_size = Highlighted_box.getSize();
								if (Current && Current->down)
								{
									Current = Current->down;					
									Node* _temp = Current;
									if (HasSameRow(_temp,Prev,true))
									{
										Node* _temp=Current;
										for (int i = 0; i < highlighted_columns; i++)
										{
											_temp->up->Setcolor(Color::White);
											_temp = _temp->left;
										}
										if (Current->down)
										{
											Current = Current->down;
											_temp = Current;
											for (int i = 0; i < highlighted_columns; i++)
											{
												_temp->Setcolor(transparentGrey);
												_temp = _temp->left;
											}
											Vector2f Curr_position = Prev->GetPosition();
											Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));
											up_or_left = true;
										}
										selected_down = false;
										selected_up = false;
									}
									else if (Current->GetColor() != transparentGrey)
									{
										Node* _temp = Current;
										for (int i = 0; i < highlighted_columns; i++)
										{
											_temp->Setcolor(transparentGrey);
											_temp=_temp->left;
										}
										Current->Setcolor(transparentGrey);
										Box_size.y += 25;
										selected_down = true;
										selected_up = false;
									}
									else
									{
										Node* _temp = Current;
										for (int i = 0; i < highlighted_columns; i++)
										{
											_temp->up->Setcolor(Color::White);
										}
										Box_size.y -= 25;
										Vector2f Curr_position = _temp->GetPosition();
										Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));
										up_or_left = true;
										selected_down = false;
										selected_up = true;
									}
									highlighted_rows++;
									Highlighted_box.setSize(Box_size);
								}
							}
							else if (evnt.key.code == sf::Keyboard::Right)
							{
								Vector2f box_size = Highlighted_box.getSize();
								if (Current && Current->right)
								{
									Current = Current->right;
									Node* temp = Prev;
									for (int i = 0; i < highlighted_columns; i++)
									{
											if (temp && temp->right)
												temp = temp->right;
									}

									int start = 0,end=0;
									//if(selected_down)
									{
										if(temp->right)
										{
											while (temp != Current)
											{
												temp->Setcolor(transparentGrey);
												temp = temp->down;
											}
										}
										Current->Setcolor(transparentGrey);
										box_size.x += 80;

									}
									highlighted_columns++;
									Highlighted_box.setSize(box_size);
								}
							}
							else 	if (evnt.key.code == sf::Keyboard::Up)
							{
								
									Vector2f Pos = Highlighted_box.getSize();
								if (Current && Current->up)
								{
									Current= Current->up;
									if (Current== Prev)
									{
										Current->down->Setcolor(Color::White);
										if(Current->up)
										{
											Current= Current->up;
											Current->Setcolor(transparentGrey);
											Vector2f Curr_position = Prev->GetPosition();
											Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y - 25));
											up_or_left = true;
										}

									}
									else if (Current->GetColor() != transparentGrey)
									{
										Current->Setcolor(transparentGrey);
										Pos.y += 25;
										Vector2f Curr_position = Current->GetPosition();
										Highlighted_box.setPosition(Vector2f(Curr_position.x,Curr_position.y));
										up_or_left = true;
									}
									else
									{

										Current->down->Setcolor(Color::White);
										Pos.y -= 25;
									}
									
									Highlighted_box.setSize(Pos);
									highlighted_rows++;

								}
							}
							else 	if (evnt.key.code == sf::Keyboard::Left)
							{
								//if (temp && temp->left)
								{
									Vector2f Pos = Highlighted_box.getSize();
									Pos.x += 80;
									Highlighted_box.setSize(Pos);
								}
							}
							
						}
						else
						{
							Highlighted_box.setSize(Vector2f(79, 24));
							if (evnt.key.code == sf::Keyboard::Down)
							{
							if(T->down)	T = T->down;
							}
							if (evnt.key.code == sf::Keyboard::Up)
								if (T->up)	T = T->up;
							if (evnt.key.code == sf::Keyboard::Left)
								if (T->left)	T = T->left;
							if (evnt.key.code == sf::Keyboard::Right)
								if (T->right)T = T->right;
							Prev=Current = T;
						}
					}
					if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Right)
					{
						if (T)
						{
							int option = DisplayOptions(T->GetPosition().x+30, T->GetPosition().y+60);
							if (option == 1)
								InsertRowBelow(y + 1);
							
							else if (option == 2)
							{
								InsertRowAbove(y + 1);
							}

						}
					}

				
				}

				


				//if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
				//{
				//	 mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
				//	int height_of_cell = 25;
				//	int width_of_cell = 80;
				//	int x = (mouseWorldPosition.x - left_margin) / width_of_cell;
				//	int y = (mouseWorldPosition.y - top_margin) / height_of_cell; // Use y here, not x
				//	T = GetNodeAt(y, x);

				//}

				sf::Vector2f mousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					if (!isDragging) {
						isDragging = true;
						lastMousePosition = mousePosition;
					}
					sf::Vector2f delta = lastMousePosition - mousePosition;
				
					view.move(delta);
				}
				else 
				{
					isDragging = false;
				}
				if (view.getCenter().x - view.getSize().x / 2 <0)
					view.setCenter(view.getSize().x / 2, view.getCenter().y);
				if (view.getCenter().x + view.getSize().x / 2 > scrollableArea.x)
					view.setCenter(scrollableArea.x - view.getSize().x / 2, view.getCenter().y);
				if (view.getCenter().y - view.getSize().y / 2 < 0)
					view.setCenter(view.getCenter().x, view.getSize().y / 2);
				if (view.getCenter().y + view.getSize().y / 2 > scrollableArea.y)
					view.setCenter(view.getCenter().x, scrollableArea.y - view.getSize().y / 2);

				
				DrawGrid(window);
				if (T)
				{
					if(!up_or_left)
					Highlighted_box.setPosition(T->GetPosition());
					window.draw(Highlighted_box);
					
				}
				
				window.setView(view);
				window.draw(Nav);
				window.display();
			}	
	}
};
