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
	vector <vector<string>> Copy;
	int hr, hc;
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
		highlighted_rows = 1;
		highlighted_columns = 1;
		hr = 1, hc = 1;
		for (int i = 1; i < 20; i++)
		{
			temp->right = new Node("", nullptr, nullptr, temp, nullptr);
			temp = temp->right;
		}
		head->down = new Node("", head);
		Node* DownHead = head->down;
		Node* D_temp = head->down;
		temp = head->right;
		for (int i = 1; i < 35; i++)
		{
			for (int j = 1; j < 20; j++)
			{
				D_temp->right = new Node("", temp, nullptr, D_temp, nullptr);
				temp->down = D_temp->right;
				D_temp = D_temp->right;
				temp = temp->right;
			}
			if (i == 34)break;
			temp = DownHead->right;
			DownHead->down = new Node("", DownHead);
			DownHead = DownHead->down;
			D_temp = DownHead;	
		}
		no_of_rows = 35;
		no_of_cols = 20;
		TimesRoman.loadFromFile("TimesRoman.ttf");

	}

	void DrawGrid(RenderWindow &window,int horizontalOffset,int verticalOffset)
	{
		//rect.move(-horizontalOffset * 200, -verticalOffset * 400);
		Node* DownHead = head;
		Node* RightHead= head;
		for (int ri=20; DownHead;ri+=25)
		{
			for (int ci=0; RightHead;ci+=80)
			{
			RightHead->DrawCell(ri, ci, window, horizontalOffset, verticalOffset);

				
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
		sf::RenderWindow window(sf::VideoMode(150, 200), "options", sf::Style::Close);
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
				if(A)
				{
					A = A->left;
				}
				else return false;

			}
		}
		else
		{
			for (int i = 0; i < highlighted_columns; i++)
			{
				if (A == B)return true;
				if (A)
				{
					A = A->right;
				}
				else return false;
			}
		}

		return false;
	}
	bool HasSameCol(Node* A, Node* B, bool IsDown)
	{
		if (IsDown)
		{
			for (int i = 0; i < highlighted_rows; i++)
			{
				if (A == B)return true;
				if(A)
				{
					A = A->up;
				}
				else return false;

			}
		}
		else
		{
			for (int i = 0; i < highlighted_rows; i++)
			{
				if (A == B)return true;
				if(A)
				A = A->down;
				else return false;
			}
		}

		return false;
	}
	void ChangeColumnColor(bool IsSelectedDown,Node*&curr,Color C)
	{
		if(IsSelectedDown)
		{
			for (int i = 0; i < highlighted_rows; i++)
			{
				curr->Setcolor(C);
				curr = curr->up;
			}
		}
		else
		{
			for (int i = 0; i < highlighted_rows; i++)
			{

				curr->Setcolor(C);
				curr = curr->down;
			}
		}

	}
	void ChangeRowColor(bool IsSelectedRight,Node*& curr,Color C)
	{
		if (IsSelectedRight)
		{
			for (int i = 0; i < highlighted_columns; i++)
			{
				curr->Setcolor(C);
				curr = curr->left;
			}
		}
		else
		{
			for (int i = 0; i < highlighted_columns; i++)
			{
				curr->Setcolor(C);
				curr = curr->right;
			}
		}

	}
	void CopyData(bool Is_down,bool is_right)
	{
		Node* Temp_prev = Prev;
		Node* Temp_curr = Prev;
		vector<string>C;
		Copy.clear();
		if (is_right && Is_down)
		{
			for (int i = 0; i < highlighted_rows; i++)
			{
				for (int j = 0; j < highlighted_columns; j++)
				{
					C.push_back(Temp_curr->Data);
					selected_cells.push_back(Temp_curr);
					Temp_curr = Temp_curr->right;
				}
				Temp_prev = Temp_prev->down;
				Temp_curr = Temp_prev;
				Copy.push_back(C);
				C.clear();
			}
		}
		if (is_right && !Is_down)
		{
			for (int i = 0; i < highlighted_rows; i++)
			{
				for (int j = 0; j < highlighted_columns; j++)
				{
					C.push_back(Temp_curr->Data);
					selected_cells.push_back(Temp_curr);
					Temp_curr = Temp_curr->right;
				}
				Temp_prev = Temp_prev->up;
				Temp_curr = Temp_prev;
				Copy.push_back(C);
				C.clear();
			}
		}
		if (!is_right && Is_down)
		{
			for (int i = 0; i < highlighted_rows; i++)
			{
				for (int j = 0; j < highlighted_columns; j++)
				{
					C.push_back(Temp_curr->Data);
					selected_cells.push_back(Temp_curr);
					Temp_curr = Temp_curr->left;
				}
				Temp_prev = Temp_prev->down;
				Temp_curr = Temp_prev;
				Copy.push_back(C);
				C.clear();
			}
		}
		if (!is_right && !Is_down)
		{
			for (int j = 0; j < highlighted_rows; j++)
			{
				for (int i = 0; i < highlighted_columns; i++)
				{
					C.push_back(Temp_curr->Data);
					selected_cells.push_back(Temp_curr);
					Temp_curr = Temp_curr->left;
				}
				Temp_prev = Temp_prev->up;
				Temp_curr = Temp_prev;
				Copy.push_back(C);
				C.clear();
			}
		}
	}
	void StoreHighlightedCells(bool Is_down, bool is_right)
	{
		Node* Temp_prev = Prev;
		Node* Temp_curr = Prev;
		vector<string>C;
		if (is_right && Is_down)
		{
			for (int i = 0; i < highlighted_rows; i++)
			{
				for (int j = 0; j < highlighted_columns; j++)
				{
					selected_cells.push_back(Temp_curr);
					Temp_curr = Temp_curr->right;
				}
				Temp_prev = Temp_prev->down;
				Temp_curr = Temp_prev;
				
			}
		}
		if (is_right && !Is_down)
		{
			for (int i = 0; i < highlighted_rows; i++)
			{
				for (int j = 0; j < highlighted_columns; j++)
				{
					selected_cells.push_back(Temp_curr);
					Temp_curr = Temp_curr->right;
				}
				Temp_prev = Temp_prev->up;
				Temp_curr = Temp_prev;
			}
		}
		if (!is_right && Is_down)
		{
			for (int i = 0; i < highlighted_rows; i++)
			{
				for (int j = 0; j < highlighted_columns; j++)
				{
					selected_cells.push_back(Temp_curr);
					Temp_curr = Temp_curr->left;
				}
				Temp_prev = Temp_prev->down;
				Temp_curr = Temp_prev;
			}
		}
		if (!is_right && !Is_down)
		{
			for (int j = 0; j < highlighted_rows; j++)
			{
				for (int i = 0; i < highlighted_columns; i++)
				{
					selected_cells.push_back(Temp_curr);
					Temp_curr = Temp_curr->left;
				}
				Temp_prev = Temp_prev->up;
				Temp_curr = Temp_prev;
			}
		}
	}
	void Unhighlightselecteddata()
	{
		for (int i = 0; i < selected_cells.size(); i++)
		{
			selected_cells[i]->Setcolor(Color::White);
		}
	}
	void LaunchExcel()
	{
		
			sf::RenderWindow window(sf::VideoMode(1375, 696), "Mini_Excel_Sheet", sf::Style::Close | sf::Style::Resize);
			window.setPosition(sf::Vector2i(-10, 0));
			sf::Vector2f mouseWorldPosition ;
			sf::Vector2f scrollableArea(2420, 1500);
			bool isDragging = false;
			sf::Vector2f lastMousePosition;
			sf::RectangleShape Nav;
			Nav.setSize(Vector2f(2415,20));
			sf::Color greyColor(128, 128, 128);
			Nav.setFillColor(Color(0,130,0));
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
			bool Is_down = false;
			bool is_right = false;
			Vector2f Curr_position;
			//--------------------------------------
			bool isVerticalDragging = false;
			bool isHorizontalDragging = false;
			sf::RectangleShape verticalScrollBar(sf::Vector2f(20, 400));
			verticalScrollBar.setPosition(1350, 0);
			verticalScrollBar.setFillColor(sf::Color::Blue);

			sf::RectangleShape horizontalScrollBar(sf::Vector2f(400, 20));
			horizontalScrollBar.setPosition(4, 675);
			horizontalScrollBar.setFillColor(sf::Color::Blue);

			// Create the scroll thumbs
			sf::RectangleShape verticalThumb(sf::Vector2f(20, 40));
			verticalThumb.setPosition(1350, 0);
			verticalThumb.setFillColor(sf::Color::Red);

			sf::RectangleShape horizontalThumb(sf::Vector2f(40, 20));
			horizontalThumb.setPosition(4, 675);
			horizontalThumb.setFillColor(sf::Color::Red);
			float horizontalOffset;
			float verticalOffset;
			//-------------------------------------
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
						mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
						int height_of_cell = 25;
						int width_of_cell = 80;
						 x = (mouseWorldPosition.x - left_margin) / width_of_cell;
						 y = (mouseWorldPosition.y - top_margin) / height_of_cell; 
						T = GetNodeAt(y, x);
						 Highlighted_box.setSize(Vector2f(79, 24));
						 Current = T;
						 Prev = T;
						 hr = highlighted_rows;
						 hc = highlighted_columns;
						 highlighted_columns = 1;
						 highlighted_rows = 1;
						 Unhighlightselecteddata();
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

						if (evnt.key.control)
						{

							if (evnt.key.code == sf::Keyboard::C)
							{
								selected_cells.clear();
								CopyData(Is_down, is_right);
							}
							else if (evnt.key.code == sf::Keyboard::X)
							{
								selected_cells.clear();

								CopyData(Is_down, is_right);
								for (int i = 0; i < selected_cells.size(); i++)
								{
									selected_cells[i]->Data = "";
								}
							}
							else if (evnt.key.code == sf::Keyboard::V)
							{
								Node* Temp_prev = Current;
								Node* Temp_curr = Current;
								if (is_right && Is_down)
								{
									for (int i = 0; i < Copy.size(); i++)
									{
										for (int j = 0; j < Copy[i].size(); j++)
										{
											if (Temp_curr)
											{
												Temp_curr->Data = Copy[i][j];
												Temp_curr = Temp_curr->right;
											}
										}
										if (!Temp_prev->down)break;
										Temp_prev = Temp_prev->down;
										Temp_curr = Temp_prev;
									}
								}
								if (is_right && !Is_down)
								{
									for (int i = 0; i < Copy.size(); i++)
									{
										for (int j = 0; j < Copy[i].size(); j++)
										{
											if (Temp_curr)
											{
												Temp_curr->Data = Copy[i][j];
												Temp_curr = Temp_curr->right;
											}
										}
										if (!Temp_prev->up)break;
										Temp_prev = Temp_prev->up;
										Temp_curr = Temp_prev;
									}
								}
								if (!is_right && Is_down)
								{
									for (int i = 0; i < Copy.size(); i++)
									{
										for (int j = 0; j < Copy[i].size(); j++)
										{
											if (Temp_curr)
											{
												Temp_curr->Data = Copy[i][j];
												Temp_curr = Temp_curr->left;
											}
										}
										if (!Temp_prev->down)break;
										Temp_prev = Temp_prev->down;
										Temp_curr = Temp_prev;
									}
								}
								if (!is_right && !Is_down)
								{
									for (int i = 0; i < Copy.size(); i++)
									{
										for (int j = 0; j < Copy[i].size(); j++)
										{
											if (Temp_curr)
											{
												Temp_curr->Data = Copy[i][j];
												Temp_curr = Temp_curr->left;
											}
										}
										if (!Temp_prev->up)break;
										Temp_prev = Temp_prev->up;
										Temp_curr = Temp_prev;
									}
								}
								
								Unhighlightselecteddata();

							}
						}
						else if (evnt.key.shift)
						{
							
							if (evnt.key.code == sf::Keyboard::Down)
							{

								Is_down = false;
								Vector2f Box_size = Highlighted_box.getSize();
								if (Current && Current->down)
								{
									Current = Current->down;
									Node* temp = Current;
									if (HasSameRow(temp,Prev,is_right))
									{
										temp = Current->up;
										ChangeRowColor(is_right, temp, Color::White);
										if(is_right)
											Curr_position = Prev->GetPosition();
										else
											Curr_position = Current->GetPosition();
										Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));
										Box_size.y -= 25;
										Highlighted_box.setSize(Box_size);
										up_or_left = true;
										highlighted_rows--;

									}
									else if (Current->GetColor() == Color::White)
									{
										temp = Current;
										ChangeRowColor(is_right, temp, transparentGrey);
										Box_size.y += 25;
										Highlighted_box.setSize(Box_size);
										Is_down = true;
										highlighted_rows++;
									}
									else if (Current->GetColor() == transparentGrey)
									{
										temp = Current->up;
										Box_size.y -= 25;
										ChangeRowColor(is_right, temp, Color::White);
										temp = temp->down;
										if(is_right)
										Curr_position = temp->right->GetPosition();
										else
											Curr_position = Current->GetPosition();

										Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));
										Highlighted_box.setSize(Box_size);
										up_or_left = true;
										Is_down = false;											
										highlighted_rows--;
									}

								}
							}
							else if (evnt.key.code == sf::Keyboard::Up)
							{
								Is_down= false;

								Vector2f Box_size = Highlighted_box.getSize();
								if (Current && Current->up)
								{
									Current = Current->up;
									Node* temp = Current;
									if (HasSameRow(temp, Prev, is_right))
									{
										temp = Current->down;
										ChangeRowColor(is_right, temp, Color::White);
										if(is_right)
										Curr_position = Prev->GetPosition();
										else 
											Curr_position = Current->GetPosition();
										Box_size.y -= 25;
										Highlighted_box.setSize(Box_size);

										Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));
										up_or_left = true;
										highlighted_rows--;
									}
									else if (Current->GetColor() == Color::White)
									{
										temp = Current;
										ChangeRowColor(is_right, temp, transparentGrey);
										Box_size.y += 25;
										Highlighted_box.setSize(Box_size);
										if (is_right)
											Curr_position = temp->right->GetPosition();
										else
											Curr_position = Current->GetPosition();

										Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));
										Is_down = false;
										up_or_left = true;
										highlighted_rows++;
									}
									else if (Current->GetColor() == transparentGrey)
									{
										temp = Current->down;
										ChangeRowColor(is_right, temp, Color::White);
										Box_size.y -= 25;
										Highlighted_box.setSize(Box_size);
										up_or_left = true;
										Is_down = true;
										highlighted_rows--;
									}

								}
							}
							else if (evnt.key.code == sf::Keyboard::Right)
							{
								is_right = false;

								Vector2f Box_size = Highlighted_box.getSize();
								if (Current && Current->right)
								{
									Current = Current->right;
									Node* temp = Current;
									if (HasSameCol(temp, Prev, Is_down))
									{
										temp = Current->left;
										ChangeColumnColor(Is_down, temp, Color::White);
										if (Is_down)
											Curr_position = Prev->GetPosition();
										else
											Curr_position = Current->GetPosition();
										Box_size.x -= 80;
										Highlighted_box.setSize(Box_size);

										Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));
										up_or_left = true;
										highlighted_columns--;
									}
									else if (Current->GetColor() == Color::White)
									{
										temp = Current;
										ChangeColumnColor(Is_down, temp, transparentGrey);
										Box_size.x += 80;
										Highlighted_box.setSize(Box_size);
										is_right = true;;
										up_or_left = true;
										highlighted_columns++;
									}
									else if (Current->GetColor() == transparentGrey)
									{
										temp = Current->left;
										ChangeColumnColor(Is_down, temp, Color::White);
										Box_size.x -= 80;
										Highlighted_box.setSize(Box_size);
										temp = temp->down;
										if (Is_down)
											Curr_position = temp->right->GetPosition();
										else
											Curr_position = Current->GetPosition();

										Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));
										up_or_left = true;
										is_right = false;
										highlighted_columns--;
									}

								}

							}
							else if (evnt.key.code == sf::Keyboard::Left)
							{
								is_right = false;

								Vector2f Box_size = Highlighted_box.getSize();
								if (Current && Current->left)
								{
									Current = Current->left;
									Node* temp = Current;
									if (HasSameCol(temp, Prev, Is_down))
									{
										temp = Current->right;
										ChangeColumnColor(Is_down, temp, Color::White);
										if (Is_down)
											Curr_position = Prev->GetPosition();
										else
											Curr_position = Current->GetPosition();
										Box_size.x -= 80;
										Highlighted_box.setSize(Box_size);
										Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));
										highlighted_columns--;
										up_or_left = true;
									}
									else if (Current->GetColor() == Color::White)
									{
										temp = Current;
										Box_size.x += 80;
										ChangeColumnColor(Is_down, temp, transparentGrey);
										temp = temp->down;
										if (Is_down)
											Curr_position = temp->GetPosition();
										else
											Curr_position = Current->GetPosition();

										Highlighted_box.setPosition(Vector2f(Curr_position.x, Curr_position.y));

										Highlighted_box.setSize(Box_size);
										is_right = false;
										up_or_left = true;
										highlighted_columns++;
									}
									else if (Current->GetColor() == transparentGrey)
									{
										temp = Current->right;
										ChangeColumnColor(Is_down, temp, Color::White);
										Box_size.x -= 80;
										Highlighted_box.setSize(Box_size);
										up_or_left = true;
										is_right = true;
										highlighted_columns--;
									}

								}

							}
						
						
						}
						else
						{
							Unhighlightselecteddata();
							Highlighted_box.setSize(Vector2f(79, 24));
							if (evnt.key.code == sf::Keyboard::Down)
							{
								if (T->down)	T = T->down;
							}
							if (evnt.key.code == sf::Keyboard::Up)
								if (T->up)	T = T->up;
							if (evnt.key.code == sf::Keyboard::Left)
								if (T->left)	T = T->left;
							if (evnt.key.code == sf::Keyboard::Right)
								if (T->right)T = T->right;
							Prev = Current = T;
						}
					
						StoreHighlightedCells(Is_down, is_right);
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

				 if (evnt.type == evnt.MouseButtonPressed) 
				 {
					 if (evnt.mouseButton.button == sf::Mouse::Left) {
						 if (verticalThumb.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y))) {
							 isVerticalDragging = true;
						 }
						 else if (horizontalThumb.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y))) {
							 isHorizontalDragging = true;
						 }
					 }
				}
				 else if (evnt.type == evnt.MouseButtonReleased) {
					 if (evnt.mouseButton.button == sf::Mouse::Left) {
						 isVerticalDragging = false;
						 isHorizontalDragging = false;
					 }
							}
				 else if (evnt.type == evnt.MouseMoved) {
					 if (isVerticalDragging) {
						 // Move the vertical thumb along the y-axis
						 verticalThumb.setPosition(1350, evnt.mouseMove.y - verticalThumb.getSize().y / 2);
					 }
					 if (isHorizontalDragging) {
						 // Move the horizontal thumb along the x-axis
						 horizontalThumb.setPosition(evnt.mouseMove.x - horizontalThumb.getSize().x / 2, 675);
					 }
			}


				 verticalOffset = (verticalThumb.getPosition().y - 100) / (verticalScrollBar.getSize().y - verticalThumb.getSize().y);
				 // Calculate the horizontal offset for scrolling
				 horizontalOffset = (horizontalThumb.getPosition().x - 100) / (horizontalScrollBar.getSize().x - horizontalThumb.getSize().x);

				 /*for (int i = 0; i < 10; i++) {
					 sf::RectangleShape rect = rectangles[i];
					 rect.move(-horizontalOffset * 200, -verticalOffset * 400);
					 window.draw(rect);
				 }*/

				DrawGrid(window, horizontalOffset, verticalOffset);
				if (T)
				{
					if(!up_or_left)
					Highlighted_box.setPosition(T->GetPosition());
					window.draw(Highlighted_box);
					T->Setcolor(Color::Blue);
					cout << T->Data << " ";
				}
				
				window.draw(verticalScrollBar);
				window.draw(horizontalScrollBar);
				window.draw(verticalThumb);
				window.draw(horizontalThumb);
				window.draw(Nav);
				window.display();
			}	
	}
};
