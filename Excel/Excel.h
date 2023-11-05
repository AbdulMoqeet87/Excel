#pragma once
#include"Cell.h"
#include<iostream>
#include<string>
#include<vector>
#include<SFML/Graphics.hpp>
#include<string>
using namespace sf;
using namespace std;

class Excel
{
	struct IndexCell
	{
		
		RectangleShape Cell;
		string Index;
		IndexCell* up;
		IndexCell* down;
		IndexCell* left;
		IndexCell* right;
		Text Str;
		Font romanT;
		IndexCell(string idx, IndexCell* _up = nullptr, IndexCell* _down = nullptr,  IndexCell* _left = nullptr,  IndexCell* _right = nullptr):up(_up),down(_down),left(_left),right(_right)
		{
			Str.setCharacterSize(15);
			Str.setFillColor(Color::Black);
			Cell.setFillColor(Color::White);
			Cell.setOutlineThickness(1);
			Cell.setOutlineColor(Color(135, 135, 135));
			Index = idx;
			sf::Color veryLightGrey(200, 200, 200);
			Cell.setFillColor(veryLightGrey);
			Str.setString(Index);
		}

		void setsize(int x,int y)
		{
			Cell.setSize(Vector2f(x, y));
		}
		void SetColor(sf::Color C)
		{
			Cell.setFillColor(C);
		}
		void SetString(string S)
		{
			Index = S;
		}
		void DrawIndexCell(int x, int y,sf::Font TimeRom,Vector2f Size,RenderWindow & window)
		{
			if (!Str.getFont())
			{
				romanT = TimeRom;
				Str.setFont(romanT);
			}
			Cell.setPosition(x, y);
			Cell.setSize(Size);
			Str.setPosition(x + Size.x / 2 - (Index.length() + 2), y + 2);
			window.draw(this->Cell);
			window.draw(Str);
		}



	};
	Node* head;
	Node* Current;
	Node* Prev;
	IndexCell* LeftIndexHead;
	IndexCell* TopIndexHead;
	IndexCell* LeftIndexTail;
	IndexCell* TopIndexTail;
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
	string Query;

public:
	Excel()
	{
		head = new Node("");
		Prev = {};
		Current = {};
		left_margin = 0;
		top_margin = 20;
		Node* temp = head;
		highlighted_rows = 1;
		highlighted_columns = 1;
		hr = 1, hc = 1;
		for (int i = 1; i < 10; i++)
		{
			temp->right = new Node("", nullptr, nullptr, temp, nullptr);
			temp = temp->right;
		}
		head->down = new Node("", head);
		Node* DownHead = head->down;
		Node* D_temp = head->down;
		temp = head->right;
		for (int i = 1; i < 10; i++)
		{
			for (int j = 1; j < 10; j++)
			{
				D_temp->right = new Node("", temp, nullptr, D_temp, nullptr);
				temp->down = D_temp->right;
				D_temp = D_temp->right;
				temp = temp->right;
			}
			if (i == 9)break;
			temp = DownHead->right;
			DownHead->down = new Node("", DownHead);
			DownHead = DownHead->down;
			D_temp = DownHead;	
		}
		no_of_rows = 10;
		no_of_cols = 10;
		LeftIndexHead= new IndexCell("1",nullptr,nullptr,nullptr,nullptr);
		TopIndexHead= new IndexCell("A",nullptr,nullptr,nullptr,nullptr);
		LeftIndexTail = LeftIndexHead;
		TopIndexTail = TopIndexHead;
		
		
		
		for (int i = 1; i < no_of_cols; i++)
		{
			char c = char(i+65);
			string s;
			s.append(1, c);
			TopIndexTail->right = new IndexCell(s, nullptr, nullptr, TopIndexTail, nullptr);
			TopIndexTail = TopIndexTail->right;
		}
		for (int i = 1; i < no_of_rows; i++)
		{
			LeftIndexTail->down = new IndexCell(to_string(0+i+1), LeftIndexTail, nullptr, nullptr, nullptr);
			LeftIndexTail = LeftIndexTail->down;
		}



		TimesRoman.loadFromFile("TimesRoman.ttf");

	}
	void DrawGrid(RenderWindow &window,int horizontalOffset,int verticalOffset)
	{
		
		Node* DownHead = head;
		Node* RightHead= head;
		for (int ri=100; DownHead;ri+=25)
		{
			for (int ci=30; RightHead;ci+=80)
			{
				RightHead->DrawCell(ri, ci, window, horizontalOffset, verticalOffset, TimesRoman);
			
				RightHead = RightHead->right;
			}
			DownHead=DownHead->down;
			RightHead = DownHead;
		}
		




		
	}
	void DrawIndexes(RenderWindow& window)
	{
		Vector2f left_index_start(30,head->GetPosition().y);
		left_index_start.x -= 30;
		Vector2f Top_index_start(head->GetPosition().x, 100);
		Top_index_start.y -= 26;

		IndexCell* LH = LeftIndexHead;
		IndexCell* TH = TopIndexHead;
		Vector2f Lsize(30, 24);
		Vector2f Tsize(80, 25);

		for (int x = left_index_start.x, y = left_index_start.y; LH; y += 25)
		{
			LH->DrawIndexCell(x, y, TimesRoman, Lsize, window);
			LH = LH->down;
		}

		for (int x = Top_index_start.x, y = Top_index_start.y; TH; x += 80)
		{
			TH->DrawIndexCell(x, y, TimesRoman, Tsize, window);
			TH = TH->right;
		}
	}
	void delete_Row(Node* temp)
	{
		if (!temp)return;
		while (temp->left)
		{
			temp = temp->left;
		}
		Node* current = temp;
		Node* above = temp->up;
		Node* below = temp->down;

		while (current)
		{
			above->down = below;			
			below->up = above;
			Node* t = current;
			current = current->right;
			delete t;
			above = above->right;
			below = below->right;
		}
		no_of_rows--;

		IndexCell* tail = LeftIndexTail;
		LeftIndexTail = LeftIndexTail->up;
		LeftIndexTail->down = nullptr;
		delete tail;

	}
	void delete_column(Node* temp)
	{
		if (!temp)return;

		while (temp->up)
			temp = temp->up;

		Node* current = temp;
		Node* Left = temp->left;
		Node* Right = temp->right;

		while (current)
		{
			Left->right = Right;
			Right->left = Left;
			Node* c = current;
			current = current->down;
			Left = Left->down;
			Right = Right->down;
			delete c;
		}

		IndexCell* a = TopIndexTail;
		TopIndexTail = TopIndexTail->left;
		TopIndexTail->right = nullptr;
		delete a;

		no_of_cols--;

	}
	void EraseRow(Node* temp)
	{
		if (!temp)return;
		while (temp->left)
		{
			temp = temp->left;
		}
		Node* current = temp;
		
		while (current)
		{
			current->Data = "";
			current = current->right;
		}
	}
	void EraseColumn(Node* temp)
	{
		if (!temp)return;
		while (temp->up)
		{
			temp = temp->up;
		}
		Node* current = temp;

		while (current)
		{
			current->Data = "";
			current = current->down;
		}
	}
	


	void InsertRowBelow(Node*temp)
	{
		if (!temp)return;
		if (temp&&!temp->down)
		{
			InsertRowATBottom();
			return;
		}
		
		Node* current =temp->down;
		while (current->left)
		{
			current = current->left;
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
		int index = stoi(LeftIndexTail->Index);
		index++;
		string S = to_string(index);
		LeftIndexTail->down = new IndexCell(S, LeftIndexTail);
		LeftIndexTail = LeftIndexTail->down;
		no_of_rows++;
	}
	void InsertRowAtTop()
	{
		Node* current = head;

		Node* _down = current;

		current = new Node("", nullptr, _down);
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
		int index = stoi(LeftIndexTail->Index);
		index++;
		string S = to_string(index);
		LeftIndexTail->down = new IndexCell(S, LeftIndexTail);
		LeftIndexTail = LeftIndexTail->down;
		no_of_rows++;
		no_of_rows++;
	}	
	void InsertRowAbove(Node*temp)
	{
		if (!temp)return;
		if (temp&&!temp->up)
		{
			InsertRowAtTop(); return;
		}
		InsertRowBelow(temp->up);
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
		current = new Node("", _up);
		_up->down = current;
		_up = _up->right;


		while (_up)
		{
			current->right = new Node("", _up,nullptr, current);
			_up->down = current->right;
			_up = _up->right;
			current = current->right;
		}
		int index = stoi(LeftIndexTail->Index);
		index++;
		string S = to_string(index);
		LeftIndexTail->down = new IndexCell(S, LeftIndexTail);
		LeftIndexTail = LeftIndexTail->down;
		no_of_rows++;
		no_of_rows++;
	}

	void InsertColumnAtLeft(Node* temp)
	{
		if (!temp)return;
		if (temp&&!temp->left)
		{
			InsertColumnAtStart();
			return;
		}
		InsertColumnAtRight(temp->left);
	}
	void InsertColumnAtStart()
	{
		
		Node* current = head;
		Node* _right= current;
		head=current = new Node("", nullptr, nullptr,nullptr,_right);
		
		_right->left = current;
		_right= _right->down;

		while (_right)
		{
			current->down = new Node("", current, nullptr, nullptr,_right);
			_right->left = current->down;
			_right = _right->down;		
			current = current->down;
		}
		char C = (TopIndexTail->Index[0]);
		C += 1;
		string S;
		S.append(1, C);
		TopIndexTail->right = new IndexCell(S, nullptr, nullptr, TopIndexTail, nullptr);
		TopIndexTail = TopIndexTail->right;
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
		current = new Node("", nullptr, nullptr,_left);
		_left->right = current;
		_left= _left->down;

		while (_left)
		{
			current->down = new Node("", current, nullptr, _left);
			_left->right = current->down;
			_left = _left->down;
			current = current->down;
		}
		char C = (TopIndexTail->Index[0]);
		C += 1;
		string S;
		S.append(1, C);
		TopIndexTail->right = new IndexCell(S, nullptr, nullptr, TopIndexTail, nullptr);
		TopIndexTail = TopIndexTail->right;
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
	void InsertColumnAtRight(Node*temp)
	{
		if ( !temp)return;
		if (temp&&!temp->right)
		{
			InsertColumnAtEnd();		
			return;
		}
		while (temp->up)
		{
			temp = temp->up;
		}
		temp = temp->right;
		Node* current = temp;
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
		char C=(TopIndexTail->Index[0]);
		C += 1;
		string S;
		S.append(1, C);
		TopIndexTail->right = new IndexCell(S, nullptr, nullptr, TopIndexTail, nullptr);
		TopIndexTail = TopIndexTail->right;
		no_of_cols++;
	}
	void Starting()
	{
		sf::RenderWindow window(sf::VideoMode(500, 400), "Starting", sf::Style::Close);
		window.setPosition(Vector2i(500, 200));
		Font TimesRoman2 = TimesRoman;
		sf::Color transparentGrey(192, 192, 192, 128);
		Color Gray(160, 160, 160, 255);
		Text Excel;
		Excel.setFont(TimesRoman2);
		Excel.setCharacterSize(60);
		Excel.setPosition(150, 150);
		Excel.setString("EXCEL");
		int i = 0;
		
			while (window.isOpen()) 
			{
				sf::Event evnt;
				window.clear((Color(0, 130, 0)));
				while (window.pollEvent(evnt)) 
				{
					if (evnt.type == sf::Event::Closed)
						window.close();				
				}
				i++;
				if (i == 5000)return;
				window.draw(Excel);
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
	void FindClickedCell(Node*& T, Vector2f mouseWorldPosition)
	{
		bool found = false;
		Node* DownHead = head;
		Node* RightHead = head;
		while (DownHead)
		{
			while (RightHead)
			{
				if (RightHead->Contains(mouseWorldPosition.x, mouseWorldPosition.y))
				{
					T = RightHead;
					found = true;
					break;
				}
				if (found)break;
				RightHead = RightHead->right;
			}
			DownHead = DownHead->down;
			RightHead = DownHead;
		}

	}
	void InsertCellAtLeft(Node* temp)
	{
		if (!temp)return;
		InsertColumnAtEnd();
		Node* Tr = temp;
		Node* prev = temp->left;
		while (Tr->right)
		{
			Tr = Tr->right;
		}
		if (prev)
			prev->right = Tr;

		Tr->left->right = nullptr;;
		Tr->left = prev;
		Tr->right = temp;
		Node* Tup = Tr->up;
		Node* Tdown = Tr->down;
		
		temp->left = Tr;
		while (temp->right)
		{
			Tr->up = temp->up;
			temp->up->down = Tr;
			Tr->down = temp->down;
			Tr->down->up = Tr;
			temp->up = temp->right->up;
			temp->right->up->down = temp;
			temp->down = temp->right->down;
			temp->right->down->up = temp;
			temp = temp->right;
			Tr = Tr->right;
		}
		temp->up = Tup;
		temp->down = Tdown;
		Tup->down = temp;
		Tdown->up = temp;
	}
	void InsertCellAtRight(Node* temp)
	{
		if (!temp)return;
		if (temp && !right)
		{
			InsertColumnAtEnd(); return;
		}
		temp = temp->right;
		InsertCellAtLeft(temp);
	}
	bool IsValidQuery(string S)
	{
		if (S.empty())return false;
		if (S[0] != '=')return false;
		if(S[4] != '(')return false;
		if ((S[5] < 65 || S[5]>90)||(S[8]<65||S[8]>90))return false;
		if ((S[6] < 48 || S[6]>=58)||(S[9]<48||S[9]>=58))return false;
		if (S[7] != ':')return false;
		if (S[10] != ')')return false;
		if (S[5] != S[8])return false;
		return true;
	}
	bool isCountQuery(string S)
	{
		if (S.empty())return false;
		if (S[0] != '=')return false;
		if (S[1] != 'C' || S[2] != 'O' || S[3] != 'U' || S[4] != 'N' || S[5] != 'T')
			return false;
		if (S[6] != '(')return false;
		if ((S[7] < 65 || S[7]>90) || (S[10] < 65 || S[10]>90))return false;
		if ((S[8] < 48 || S[8] >= 58) || (S[11] < 48 || S[11] >= 58))return false;
		if (S[9] != ':')return false;
		if (S[12] != ')')return false;
		if (S[7] != S[10])return false;
		return true;
	}
	string CalculateRange(string funct)
	{
		int count=0;
		string S{};
		int sum = 0;
		
	
		if (isCountQuery(funct))
		{
			return CalculculateCountRange(funct);
		}
		else if (IsValidQuery(funct))
		{
			count = funct[9] - funct[6]+1;
			if (funct[1] == 'S' && funct[2] == 'U' && funct[3] == 'M')
				return CalculculateSumRange(funct);
			else if (funct[1] == 'A' && funct[2] == 'V' && funct[3] == 'G')
			{
				S = CalculculateSumRange(funct);
				sum = stoi(S);
				S = CalculculateCountRange(funct);
				sum = sum / stoi(S);
				return to_string(sum);

			}

			else	if (funct[1] == 'M' && funct[2] == 'I' && funct[3] == 'N')
			{
				return CalculculateMinRange(funct);
			}
			else	if (funct[1] != 'M' && funct[2] != 'A' && funct[3] != 'X')
				return CalculculateMaxRange(funct);
		}
		
		else return "";
	}
	string CalculculateCountRange(string funct)
	{
		int Count = 0;

		if (((funct[11]) - 48) > no_of_rows)return "";
		if ((funct[7] - 64) > no_of_cols)return "";
		Node* temp = head;
		for (int i = 1; i < funct[7] - 64; i++)
		{
			temp = temp->right;
		}
		for (int i = 1; i < funct[8] - 48; i++)
		{
			temp = temp->down;
		}
		for (char i = funct[8]; i <= funct[11]; i++)
		{
			if (temp->Data != "")
				Count++;;
			temp = temp->down;
		}

		return to_string(Count);


	
	}
	string CalculculateSumRange(string funct)
	{
		int sum = 0;

		if (((funct[9]) - 48) > no_of_rows)return "";
		if ((funct[5] - 64) > no_of_cols)return "";
		Node* temp = head;
		for (int i = 1; i < funct[5] - 64; i++)
		{
			temp = temp->right;
		}
		for (int i = 1; i < funct[6] - 48; i++)
		{
			temp = temp->down;
		}
		for (char i = funct[6]; i <= funct[9]; i++)
		{
			if (temp->Data != "")
				sum += stoi(temp->Data);
			temp = temp->down;
		}

		return to_string(sum);


	}
	string CalculculateMinRange(string funct)
	{
		int min = INT_MAX;

		if (((funct[9]) - 48) > no_of_rows)return "";
		if ((funct[5] - 64) > no_of_cols)return "";
		Node* temp = head;
		for (int i = 1; i < funct[5] - 64; i++)
		{
			temp = temp->right;
		}
		for (int i = 1; i < funct[6] - 48; i++)
		{
			temp = temp->down;
		}
		for (char i = funct[6]; i <= funct[9]; i++)
		{
			if (temp->Data != "")
			{
				if (stoi(temp->Data) < min)
					min = stoi(temp->Data);
			}
			temp = temp->down;
		}
		if (min == INT_MAX)return "";
		return to_string(min);


	}
	string CalculculateMaxRange(string funct)
	{
		int max = INT_MIN;

		if (((funct[9]) - 48) > no_of_rows)return "";
		if ((funct[5] - 64) > no_of_cols)return "";
		Node* temp = head;
		for (int i = 1; i < funct[5] - 64; i++)
		{
			temp = temp->right;
		}
		for (int i = 1; i < funct[6] - 48; i++)
		{
			temp = temp->down;
		}
		for (char i = funct[6]; i <= funct[9]; i++)
		{
			if (temp->Data != "")
			{
				if (stoi(temp->Data) > max)
					max = stoi(temp->Data);
			}
			temp = temp->down;
		}
		if (max == INT_MIN)return "";
		return to_string(max);


	}
	void LaunchExcel()
	{
			sf::RenderWindow window(sf::VideoMode(1375, 696), "Mini_Excel_Sheet", sf::Style::Close | sf::Style::Resize);
			window.setPosition(sf::Vector2i(-10, 0));
			sf::Color veryLightGrey(200, 200, 200);
			sf::Color HighlightGrey(192, 192, 192, 128);
			sf::Vector2f mouseWorldPosition ;
			sf::Vector2f scrollableArea(2420, 1500);
			bool isDragging = false;
			sf::Vector2f lastMousePosition;
			sf::RectangleShape Nav;
			Nav.setSize(Vector2f(2415,75));
			sf::Color greyColor(128, 128, 128);
			Nav.setFillColor(Color(0,130,0));
			Nav.setPosition(0, 0);
			//-------------
			RectangleShape insertRange;
			insertRange.setPosition(170, 28);
			insertRange.setSize(Vector2f(1000,27));
			insertRange.setOutlineColor(Color::White);
			insertRange.setOutlineThickness(1);
			insertRange.setFillColor(veryLightGrey);
			Text Fx;
			Font fx;
			fx.loadFromFile("Fx.ttf");
			Fx.setFont(fx);
			Fx.setString("fx : ");
			Fx.setCharacterSize(19);
			Fx.setPosition(179, 25);
			Fx.setFillColor(Color::Black);

			Text function;
			Font f;
			f=TimesRoman;
			function.setFont(f);
			function.setCharacterSize(19);
			function.setPosition(279, 27);
			function.setFillColor(Color::Black);


			//------------
			RectangleShape indexSep;
			indexSep.setPosition(0, 75);
			indexSep.setSize(Vector2f(30, 25));
			indexSep.setOutlineColor(greyColor);
			indexSep.setOutlineThickness(1);
			indexSep.setFillColor(veryLightGrey);
			//----------------
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
			sf::RectangleShape verticalScrollBar(sf::Vector2f(22, 670));
			verticalScrollBar.setPosition(1350, 0);
			verticalScrollBar.setFillColor(veryLightGrey);

			sf::RectangleShape horizontalScrollBar(sf::Vector2f(1200, 22));
			horizontalScrollBar.setOutlineThickness(1);
			horizontalScrollBar.setOutlineColor(sf::Color::Black);
			horizontalScrollBar.setPosition(4, 674);
			horizontalScrollBar.setFillColor(veryLightGrey);

			// Create the scroll thumbs
			sf::RectangleShape verticalThumb(sf::Vector2f(20, 40));
			verticalThumb.setPosition(1350, 0);
			verticalThumb.setFillColor(sf::Color::White);

			sf::RectangleShape horizontalThumb(sf::Vector2f(40, 18));
			horizontalThumb.setPosition(4, 676);
			horizontalThumb.setOutlineThickness(1);
			horizontalThumb.setOutlineColor(greyColor);
			horizontalThumb.setFillColor(sf::Color::White);
			float horizontalOffset;
			float verticalOffset;
			int Hr_thumb_last_pos = 0,Hr_thumb_current_pos=0;
			bool Query_entering = false;
			bool hoovered = false;
			//-------------------------------------
			sf::Color transparentGrey(255, 255, 255, 190);
			int x = {} ,y = {};
			//------------------------------
			sf::Vector2f contextMenuPosition;
			bool isContextMenuVisible = false;
			sf::Text Insert_RB("Insert Row Below", TimesRoman, 13);
			Insert_RB.setFillColor(sf::Color::Black);

			sf::Text Insert_RA("Insert Row Above", TimesRoman, 13);
			Insert_RA.setFillColor(sf::Color::Black);

			sf::Text ClearRow("Clear Row", TimesRoman, 13);
			ClearRow.setFillColor(sf::Color::Black);
			
			sf::Text Insert_CB("Insert Col Left", TimesRoman, 13);
			Insert_RB.setFillColor(sf::Color::Black);

			sf::Text Insert_CA("Insert Col Right", TimesRoman, 13);
			Insert_RA.setFillColor(sf::Color::Black);

			sf::Text ClearColumn("Clear Column", TimesRoman, 13);
			ClearRow.setFillColor(sf::Color::Black);
			//--------------------------
		
			sf::Text InsertCell_L("Insert Cell Left", TimesRoman, 13);
			InsertCell_L.setFillColor(sf::Color::Black);

			sf::Text InsertCell_R("Insert Cell Right", TimesRoman, 13);
			InsertCell_R.setFillColor(sf::Color::Black);

			sf::Text Delete_Row("Delete Row", TimesRoman, 13);
			Delete_Row.setFillColor(sf::Color::Black);

			sf::Text Delete_Col("Delete Column", TimesRoman, 13);
			Delete_Col.setFillColor(sf::Color::Black);

			//-----------------------------
			while (window.isOpen()) {
				sf::Event evnt;
				window.clear();
			
				while (window.pollEvent(evnt))
				{
					if (evnt.type == sf::Event::Closed)
						window.close();

					else if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left)
					{
						mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

						
						
							if (T&&Insert_RB.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y)))
							{
								InsertRowBelow(T);
							}
							else if (T && Insert_RA.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y))) {
								InsertRowAbove(T);
							}
							else if (T && ClearRow.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y))) {
								EraseRow(T);
							}
							else if (T&&Insert_CB.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y)))
							{
								InsertColumnAtLeft(T);
							}
							else if (T && Insert_CA.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y))) {
								InsertColumnAtRight(T);
							}
							else if (T && ClearColumn.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y))) {
								EraseColumn(T);
							}
							
							else if (T && InsertCell_L.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y))) {
								InsertCellAtLeft(T);
							}
							else if (T&& InsertCell_R.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y)))
							{
								InsertCellAtRight(T);
							}
							else if (T && Delete_Row.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y))) {
								delete_Row(T);
							}
							else if (T && Delete_Col.getGlobalBounds().contains(sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y))) {
								delete_column(T);
							}



							else
							{
								FindClickedCell(T, mouseWorldPosition);
								Highlighted_box.setSize(Vector2f(79, 24));
								Current = T;
								Prev = T;
								if (T)
								{
									Query = "";
									function.setString(Query);
								}
								hr = highlighted_rows;
								hc = highlighted_columns;
								highlighted_columns = 1;
								highlighted_rows = 1;
								Unhighlightselecteddata();
								up_or_left = false;;

							}
							isContextMenuVisible = false;
					}
					if (evnt.type == sf::Event::TextEntered)
					{
						if(!Query_entering)
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
									else if (evnt.text.unicode >= 48 && evnt.text.unicode <= 57)
									{
										if (Current->Data.length() < 7)

											Current->Data += static_cast<char>(evnt.text.unicode);

									}
								}
							}
						}
						else
						{
							if((Current))
							{
								if (evnt.type == sf::Event::TextEntered)
								{
									if (evnt.text.unicode < 128)
									{
										if (evnt.text.unicode == 8)
										{
											if (!Query.empty())
											{
												Query.pop_back();
											}
										}
										else if (evnt.text.unicode != 8)
										{

											Query += static_cast<char>(evnt.text.unicode);
										}
										function.setString(Query);
									}
								}
							}


						}
					
					
					
					}
					if (evnt.type == sf::Event::KeyPressed)
					{

						if ((evnt.key.code == sf::Keyboard::Enter))
						{

							Current->Data=CalculateRange(Query);
							
							Query_entering = false;
						}
						else
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
										if (HasSameRow(temp, Prev, is_right))
										{
											temp = Current->up;
											ChangeRowColor(is_right, temp, Color::White);
											if (is_right)
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
											if (is_right)
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
									Is_down = false;

									Vector2f Box_size = Highlighted_box.getSize();
									if (Current && Current->up)
									{
										Current = Current->up;
										Node* temp = Current;
										if (HasSameRow(temp, Prev, is_right))
										{
											temp = Current->down;
											ChangeRowColor(is_right, temp, Color::White);
											if (is_right)
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
					}

					if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Right)
					{
						isContextMenuVisible = true;
						contextMenuPosition = sf::Vector2f(evnt.mouseButton.x, evnt.mouseButton.y);
					}

					if (evnt.type == sf::Event::MouseButtonPressed && evnt.mouseButton.button == sf::Mouse::Left)
					{
						mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));
						if (insertRange.getGlobalBounds().contains(mouseWorldPosition.x, mouseWorldPosition.y))
							Query_entering = true;
					}
					
					//if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) 
				//{
				//	 mouseWorldPosition = window.mapPixelToCoords(sf::Mouse::getPosition(window), view);
				//	int height_of_cell = 25;
				//	int width_of_cell = 80;
				//	int x = (mouseWorldPosition.x - left_margin) / width_of_cell;
				//	int y = (mouseWorldPosition.y - top_margin) / height_of_cell; // Use y here, not x
				//	T = GetNodeAt(y, x);

				}

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
						 horizontalThumb.setPosition(evnt.mouseMove.x - horizontalThumb.getSize().x / 2, 676);
					 }
					if(T)
					{
					
						sf::Vector2f mousePosition3 = window.mapPixelToCoords(sf::Mouse::getPosition(window));
						if (Insert_RB.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y)))
							Insert_RB.setFillColor(greyColor);
						
						else
							Insert_RB.setFillColor(Color::Black);

						  if (Insert_RA.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y))) 
							Insert_RA.setFillColor(greyColor);
						 
						  else
						  Insert_RA.setFillColor(Color::Black);						
						  if (ClearRow.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y))) 
						 	ClearRow.setFillColor(greyColor);
						  else
							  ClearRow.setFillColor(Color::Black);
						  
						  if (Insert_CB.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y)))
						
							Insert_CB.setFillColor(greyColor);
						
						else
							Insert_CB.setFillColor(Color::Black);

						  if (Insert_CA.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y))) 
							Insert_CA.setFillColor(greyColor);
						  else
						  Insert_CA.setFillColor(Color::Black);
						  if (ClearColumn.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y))) 
							  ClearColumn.setFillColor(greyColor);
						  else
							  ClearColumn.setFillColor(Color::Black);

						  if (InsertCell_L.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y)))
							  InsertCell_L.setFillColor(greyColor);
						  else
							  InsertCell_L.setFillColor(Color::Black);
						  if (InsertCell_R.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y)))
							  InsertCell_R.setFillColor(greyColor);
						  else
							  InsertCell_R.setFillColor(Color::Black);
						  if (Delete_Row.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y)))
							  Delete_Row.setFillColor(greyColor);
						  else
							  Delete_Row.setFillColor(Color::Black);
						  if (Delete_Col.getGlobalBounds().contains(sf::Vector2f(mousePosition3.x, mousePosition3.y)))
							  Delete_Col.setFillColor(greyColor);
						  else
							  Delete_Col.setFillColor(Color::Black);

					 
					}

				 }


				

				 verticalOffset = (verticalThumb.getPosition().y + 10) / ((verticalScrollBar.getSize().y-500) - verticalThumb.getSize().y);
				 // Calculate the horizontal offset for scrolling
				 horizontalOffset = (horizontalThumb.getPosition().x + 10) / ((horizontalScrollBar.getSize().x - 800) - horizontalThumb.getSize().x);

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
				}
				DrawIndexes(window);
				window.draw(Nav);
				window.draw(insertRange);
				window.draw(Fx);
				window.draw(function);
				window.draw(indexSep);
				window.draw(verticalScrollBar);
				window.draw(horizontalScrollBar);
				window.draw(verticalThumb);
				window.draw(horizontalThumb);
				if (isContextMenuVisible&&T) {
					sf::RectangleShape contextMenuBackground(sf::Vector2f(120, 220));
					contextMenuBackground.setPosition(contextMenuPosition);
					contextMenuBackground.setFillColor(Color::White);
					contextMenuBackground.setOutlineColor(greyColor);
					contextMenuBackground.setOutlineThickness(1);
					
					Insert_RB.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 10);
					Insert_RA.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 30);
					ClearRow.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 50);
					Insert_CB.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 70);
					Insert_CA.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 90);
					ClearColumn.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 110);
					InsertCell_L.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 130);
					InsertCell_R.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 150);
					Delete_Row.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 170);
					Delete_Col.setPosition(contextMenuPosition.x + 10, contextMenuPosition.y + 190);
					window.draw(contextMenuBackground);
					window.draw(Insert_RB);
					window.draw(Insert_RA);
					window.draw(ClearRow);
					window.draw(Insert_CB);
					window.draw(Insert_CA);
					window.draw(ClearColumn);
					window.draw(InsertCell_L);
					window.draw(InsertCell_R);
					window.draw(Delete_Row);
					window.draw(Delete_Col);
				}
				else
				{
					Insert_RB.setPosition(-100,-100);
					Insert_RA.setPosition(-100, -100);
					ClearRow.setPosition(-100, -100);
					Insert_CB.setPosition(-100, -100);
					Insert_CA.setPosition(-100, -100);
					ClearColumn.setPosition(-100, -100);
					InsertCell_L.setPosition(-100, -100);
					InsertCell_R.setPosition(-100, -100);
					Delete_Row.setPosition(-100, -100);
					Delete_Col.setPosition(-100, -100);
				}
				window.display();
			}	
	}
};
