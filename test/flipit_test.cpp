#include <iostream>
#include <string.h>
#include <assert.h>
#include <stdio.h>

// Only way to test private methods
#define private public

#include "../include/flipIt.h"
#include "../include/grid.h"

#define TAB_SIZE 3

using namespace std;
typedef void (*callback_function)(void);


// TODO: turn all oft his into a class
static int tab_depth = 0;
static bool g_passing = true;
string _get_tabs(int depth) {
	string str("");
	return str.insert(0, depth * TAB_SIZE, ' ');
}

void expect(int left, int right) {
	bool pass = left == right;
	if(!pass) cout << _get_tabs(tab_depth + 1) << "FAIL - Expected " << left << " to equal " << right << endl;
	g_passing &= pass;
}

void describe(string description, callback_function cb) {
	cout << _get_tabs(tab_depth) << description << endl;
	tab_depth++;
	if (cb)	cb();
	tab_depth--;
}


// TODO: Make these functions the same for now
void (&it)(string description, callback_function cb) = describe;

// TODO: beforeEach

/**
 * Main testing suite. Tests all classes. Runs other test suites
 * in larger projects
 */
int main()
{

	describe("\nFlipIt class tests", [&]() {
		describe("FlipIt constructor/getter tests", [&]() {
			it("should have 3 rows and 3 columns", [&]() {
				FlipIt game( 3, 3, 0, 1, FlipIt::cross_, true);

				expect(3, game.numRows());
				expect(3, game.numCols());
				expect(FlipIt::solid_, game.fetch(0, 0));
				expect(FlipIt::solid_, game.fetch(1, 0));
				expect(FlipIt::solid_, game.fetch(2, 0));
				expect(FlipIt::clear_, game.fetch(0, 1));
				expect(FlipIt::solid_, game.fetch(1, 1));
				expect(FlipIt::clear_, game.fetch(2, 1));
				expect(FlipIt::clear_, game.fetch(0, 2));
				expect(FlipIt::solid_, game.fetch(1, 2));
				expect(FlipIt::clear_, game.fetch(2, 2));
			});
		});
		describe("click test", [&](){
			it("pattern: cross", [&](){
				FlipIt game( 3, 4, 4, 1, FlipIt::cross_, true);
				game.click(1, 2);
				expect(FlipIt::solid_, game.fetch(0, 0));
				expect(FlipIt::clear_, game.fetch(0, 3));
				expect(FlipIt::solid_, game.fetch(2, 0));
				expect(FlipIt::clear_, game.fetch(2, 3));
			});
			it("pattern: x", [&](){
				FlipIt game( 3, 4, 4, 1, FlipIt::x_, true);
				game.click(1, 2);
				expect(FlipIt::clear_, game.fetch(0, 0));
				expect(FlipIt::clear_, game.fetch(0, 3));
				expect(FlipIt::clear_, game.fetch(2, 0));
				expect(FlipIt::clear_, game.fetch(2, 3));
			});
			it("pattern: square", [&](){
				FlipIt game( 3, 4, 4, 1, FlipIt::square_, true);
				game.click(1, 2);
				expect(FlipIt::solid_, game.fetch(0, 0));
				expect(FlipIt::clear_, game.fetch(0, 3));
				expect(FlipIt::solid_, game.fetch(2, 0));
				expect(FlipIt::clear_, game.fetch(2, 3));
			});
			it("pattern: hollow", [&](){
				FlipIt game( 3, 4, 4, 1, FlipIt::hollowSquare_, true);
				game.click(1, 2);
				expect(FlipIt::solid_, game.fetch(0, 0));
				expect(FlipIt::clear_, game.fetch(0, 3));
				expect(FlipIt::solid_, game.fetch(2, 0));
				expect(FlipIt::clear_, game.fetch(2, 3));
			});
			it("pattern: corners", [&](){
				FlipIt game( 3, 4, 4, 1, FlipIt::corners_, true);
				game.click(1, 2);
				expect(FlipIt::clear_, game.fetch(0, 0));
				expect(FlipIt::clear_, game.fetch(0, 3));
				expect(FlipIt::clear_, game.fetch(2, 0));
				expect(FlipIt::clear_, game.fetch(2, 3));
			});
		});
		describe("fetch test", [&](){
			it("", [&](){
				FlipIt game( 3, 4, 4, 1, FlipIt::cross_, true);
			});
		});
		describe("done test", [&](){
			it("testing done true and false", [&](){
				FlipIt game( 3, 4, 4, 1, FlipIt::cross_, true);
				expect(false, game.done());
				game.click(1, 0);
				expect(true, game.done());
			});
			it("toggle different cell after done returns true", [&](){
				FlipIt game( 3, 4, 4, 1, FlipIt::cross_, true);
				expect(false, game.done());
				game.click(1, 0);
				expect(true, game.done());
				game.click(2, 2);
				expect(false, game.done());
			});
		});
		describe("getWrappedNeighbor tests", [&]() {
			it("testing wrapped visit from all possible directions to index zero.", [&]() {
				FlipIt g( 3, 4, 4, 1, FlipIt::cross_, true);
				expect(0, g.neighbor_x( 0,  0 ));
				expect(0, g.neighbor_y( 0,  0 ));
				expect(0, g.neighbor_x( 1, -1 ));
				expect(0, g.neighbor_y( 1,  0 ));
				expect(0, g.neighbor_x( 3,  1 ));
				expect(0, g.neighbor_y( 3,  0 ));
				expect(0, g.neighbor_x( 4,  0 ));
				expect(0, g.neighbor_y( 4,  -1 ));
				expect(0, g.neighbor_x( 5, -1 ));
				expect(0, g.neighbor_y( 5, -1 ));
				expect(0, g.neighbor_x( 7,  1 ));
				expect(0, g.neighbor_y( 7,  -1 ));
				expect(0, g.neighbor_x( 8,  0 ));
				expect(0, g.neighbor_y( 8,  1 ));
				expect(0, g.neighbor_x( 9, -1 ));
				expect(0, g.neighbor_y( 9, 1 ));
				expect(0, g.neighbor_x( 11, 1 ));
				expect(0, g.neighbor_y( 11, 1 ));
			});
			it("testing 1D getWrapped_ (no actual wrapping)", [&]() {
				FlipIt g( 3, 3, 4, 1, FlipIt::corners_, true);
				expect(1, g.neighbor_x(7, 0));
				expect(1, g.neighbor_x(3, 1));
				expect(1, g.neighbor_x(5, -1));
				expect(1, g.neighbor_x(1, 0));

				expect(1, g.neighbor_y(7, -1));
				expect(1, g.neighbor_y(3, 0));
				expect(1, g.neighbor_y(5, 0));
				expect(1, g.neighbor_y(1, 1));
			});
			it("testing 1D getWrapped_ (with wrapping)", [&]() {
				FlipIt g( 3, 3, 4, 1, FlipIt::corners_, true);
				expect(0, g.neighbor_x(2, 1));
				expect(0, g.neighbor_x(5, 1));
				expect(0, g.neighbor_x(8, 1));

				expect(0, g.neighbor_y(6, 1));
				expect(0, g.neighbor_y(7, 1));
				expect(0, g.neighbor_y(8, 1));
			});
		});
	});

	if (g_passing) { return 0; }
	else { return -1; }
}
