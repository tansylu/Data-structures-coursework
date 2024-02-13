#include <cstdlib>;
#include <iostream>;
#include <fstream>;
#include "Stack.h";
#include <vector>;
#include <algorithm>;
#include <sstream>;
#include <string>;
using namespace std;

bool breakdown(Stack<Cell>& maze, vector<Coord>& visited, string step, Cell* current_cell, int m, int n ) {
	bool flag = false;
	if (step == "left" && current_cell->c.x > 0) { /// go left
		Coord c = Coord(current_cell->c.x - 1, current_cell->c.y);
		if (find(visited.begin(), visited.end(), c) == visited.end()) {
			flag = true;
			visited.push_back(c);
			vector<string> init_arr = { "left", "none", "up", "down" };
			Cell* next = new Cell(init_arr,c,1, 0, 1, 1, "right");
			current_cell->l = 0;
			maze.push(next);

		}
	}

	else if (step == "right" && current_cell->c.x < n - 1) {//go right
		Coord c = Coord(current_cell->c.x + 1, current_cell->c.y);
		if (find(visited.begin(), visited.end(), c) == visited.end()) {
			flag = true;
			visited.push_back(c);
			vector<string> init_arr = { "none", "right", "up", "down" };
			 Cell* next = new Cell(init_arr, c, 0, 1, 1, 1, "left");
			current_cell->r = 0;
			maze.push(next);

		}
	}

	else if ("up"==step && current_cell->c.y < m - 1) {//go up
		Coord c = Coord(current_cell->c.x, current_cell->c.y + 1);
		if (find(visited.begin(), visited.end(), c) == visited.end()) {
			flag = true;
			visited.push_back(c);
			vector<string> init_arr = { "left", "right", "up", "none" };
			Cell* next = new Cell(init_arr, c,1, 1, 1, 0, "down");
			current_cell->u = 0;
			maze.push(next);

		}
	}

	else if ("down" == step && current_cell->c.y > 0) {//go down
		Coord c = Coord(current_cell->c.x, current_cell->c.y - 1);
		if (find(visited.begin(), visited.end(), c) == visited.end()) {
			flag = true;
			visited.push_back(c);
			vector<string> init_arr = { "left", "none", "none", "down" };
			Cell* next = new Cell(init_arr, c, 1, 1, 0, 1, "up");
			current_cell->d = 0;
			maze.push(next);

		}

	}
	return flag;
}

int find_neighbors(Cell* current_cell, vector<Cell* > & history, int n, int m) {//check vector of history cells
	Coord current = current_cell->c;

	if (current.x == 0 ) {
		current_cell->arr[0] = "none";
	}
	if (current.x == n - 1) {
		current_cell->arr[1] = "none";
		
	}
	if (current.y == 0 ) {
		current_cell->arr[3] = "none";
		
	}
	if (current.y == m - 1) {
		current_cell->arr[2] = "none";
		
	}
	
	int s = std::count(current_cell->arr.begin(), current_cell->arr.end(), "none");
	int i = 0;
	for (i = history.size()-1; i > -1;i--) {
		Coord e = history[i]->c;
		if (s == 4) {
				return 0;
			}
			if (e.x == current.x && abs(e.y - current.y) == 1 || e.y == current.y && abs(e.x - current.x) == 1) {

				if (e.x == current.x && e.y - current.y == 1) {//up
					current_cell->arr[2] = "none";
				}
				else if (e.x == current.x && e.y - current.y == -1) {//down
					current_cell->arr[3] = "none";
				
				}
				else if (e.y == current.y && e.x - current.x == 1) {//right
					current_cell->arr[1] = "none";
					
				}
				else if (e.y == current.y && e.x - current.x == -1) {//left
					current_cell->arr[0] = "none";
				}
				s = std::count(current_cell->arr.begin(), current_cell->arr.end(), "none");
			}


		}

	return 4-s;
}

void generate_mazes(int i, int k, int m, int n) {
	int randNum = -1;
	while (i < k + 1) {//start of maze generation stage
		ofstream myfile;
		myfile.open("maze_" + (to_string(i)) + ".txt");
		myfile << m << " " << n << endl;

		vector<Coord> visited = { Coord(0, 0) };
		vector<string> arr = { "left", "right", "up", "down" };
		vector<string> init_arr = { "none", "right", "up", "none" };

		Stack<Cell> maze(m * n);
		Cell* start = new Cell(init_arr, Coord(0, 0));
		maze.push(start);
		vector<Cell*> history = { start };
		string step = "none";
		int k = 0;

		while (history.size() != m * n) {
			randNum = -1;
			k = count(maze.currentCell->arr.begin(), maze.currentCell->arr.end(), "none");//count available directions
			if (k != 4 && find_neighbors(maze.currentCell, history, n, m) != 0) {//check for updates on neigbors

				while (randNum == -1 || step == maze.currentCell->blocked_way || maze.currentCell->arr[randNum] == "none") {//pick an available way
					randNum = (std::rand() % maze.currentCell->arr.size());
					step = maze.currentCell->arr[randNum];
				}

				Cell* prev = maze.currentCell;
				if (breakdown(maze, visited, step, maze.currentCell, m, n) == true) {//if created a new cell succesfully
					history.push_back(prev);
				}
			}
			else {
				//cout << "POPPED" << endl;
				Cell* curr = maze.currentCell;
				while (count(curr->arr.begin(), curr->arr.end(), "none") == 4) {//pop until a free neigbor appears
					maze.pop();
					curr = maze.currentCell;
				}


			}
		}

		for (Cell* e : history) {
			myfile << "x=" << e->c.x << " y=" << e->c.y << " l=" << e->l << " r=" << e->r << " u=" << e->u << " d=" << e->d << endl;
		}
		i++;

		myfile.close();
	}
}

void parse_maze(ifstream & input, Cell* (& ees)[3], vector<vector<Cell*> > & history, int entry_x, int entry_y, int exit_x, int exit_y) {
	Cell* enter = nullptr;
	Cell* exit = nullptr;
	Cell* start = nullptr;
	Cell* prev = nullptr;
	Cell* current = nullptr;
	string line;
	string xs, ys, ls, rs, us, ds;
	int  x, y, l, r, u, d;
	vector<string> arr = { "left", "right", "up", "down" };

	while (std::getline(input, line))
	{
		stringstream s(line);
		if (!(s >> xs >> ys >> ls >> rs >> us >> ds)) {// error
			std::cout << line;
			break;
		}
		// process cell info
		x = stoi(xs.substr(2));
		y = stoi(ys.substr(2));
		l = stoi(ls.substr(2));
		r = stoi(rs.substr(2));
		u = stoi(us.substr(2));
		d = stoi(ds.substr(2));
		//c(c), connected_to(?), l(l), r(r), u(u), d(d)
		current = new Cell(arr, Coord(x, y),  l, r, u, d);

		if (prev == nullptr) {
			start = current;
		}
		prev = current;

		history[y][x]=current;

		if ((x == exit_x && y == exit_y) || entry_x == x && entry_y == y) {
			if (enter == nullptr) {
				std::cout << "Found enter" << endl;
				enter = current;
			}
			else {
				std::cout << "Found exit" << endl;
				exit = current;

			}
		}

	}
	input.close();
	ees[0] = start;
	ees[1] = enter;
	ees[2] = exit;
	return;
}

int main() {
	int i = 1, k = 0, m = 0, n = 0;
	srand(time(NULL));
	std::cout << "Enter the number of mazes : ";
	std::cin >> k;
	std::cout << "Enter the number of rows and columns(M and N) : ";
	std::cin >> m >> n;
	generate_mazes(i, k, m, n);

	//end of maze gen stage
	std::cout << "All mazes are generated." << endl;

	int id_num;
	int entry_x = 0, entry_y = 0;
	int exit_x = 0, exit_y = 0;

	std::cout << "Enter a maze ID between 1 to " << k << " inclusive to find a path : ";
	std::cin >> id_num;
	std::cout << "Enter x and y coordinates of the entry points(x, y) or (column, row) : ";
	std::cin >> entry_x >> entry_y;
	std::cout << "Enter x and y coordinates of the exit points(x, y) or (column, row) : ";
	std::cin >> exit_x >> exit_y;

	ifstream input("maze_" + (to_string(id_num)) + ".txt", ios::in);
	string line;
	std::getline(input, line);
	int row, col;
	istringstream s(line);
	s >> row >> col;
	vector<vector<int>> vec(m, vector<int>(n, 0));
	vector<vector<Cell*>> history(row, vector<Cell*> (col, nullptr));
	Cell* ees[3] = {nullptr, nullptr, nullptr};
	parse_maze( input,ees, history,entry_x, entry_y, exit_x, exit_y);
	Cell* start = ees[0];
	Cell* enter = ees[1];
	Cell* exit = ees[2];
	Cell* tmp;
	Stack<Cell> solution(m * n);
	solution.push(history[entry_y][entry_x]);
	while (!solution.isEmpty()) {
		tmp = solution.pop();
		if (tmp->c.x == exit_x && tmp->c.y == exit_y) {
			cout << "reached exit" << endl;
			break;
		}
		if (!tmp->visited) {
			tmp->visited = true;
	

			if (tmp->l == 0) {
				Cell* left = history[tmp->c.y][tmp->c.x - 1];
				if (left!=nullptr&&!left->visited) {
					solution.push(left);
				}
			}

			if (tmp->r == 0) {
				Cell* right = history[tmp->c.y][tmp->c.x + 1];
				if (right != nullptr && !right->visited) {
					solution.push(right);
				}
			}

			if (tmp->u == 0) {
				Cell* up = history[tmp->c.y+1][tmp->c.x];
				if (up != nullptr && !up->visited) {
					solution.push(up);
				}
			}

			if (tmp->d == 0) {
				Cell* down = history[tmp->c.y - 1][tmp->c.x];
				if (down != nullptr && !down->visited) {
					solution.push(down);
				}
			}
		}
	}

	return 0;
	
}
