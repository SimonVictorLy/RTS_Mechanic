
typedef std::pair<int,int> Pair;
typedef std::pair<double, std::pair<int,int>> pPair;


struct Circle{
	int x, y;
	int r;
};

// use for A*
struct cell
{
    // Row and Column index of its parent
    // Note that 0 <= i <= ROW-1 & 0 <= j <= COL-1
    int parent_i, parent_j;
    // f = g + h
    double f, g, h;
};
