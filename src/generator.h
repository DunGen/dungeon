#include <set>
#include <iostream>
#include <string>
#ifndef GENERATOR_H
#define GENERATOR_H
class Generator {
	private:
		struct Grid_tile{
			/* TMesh mesh; */
			unsigned short x, y;
			bool set;
			Grid_tile(): x(0), y(0), set(false) /*, mesh(NULL)*/{}
		};
		struct coord{
			int x,y;
			coord():x(0),y(0){}
			bool operator<(const coord &a) const{
				return ((x < a.x) ||((x == a.x) && (y < a.y)));
			}
		};
		/* TMesh box; */
		Grid_tile tile[100][100];
		std::set<coord> deadend_set;
		std::string debug_string;
		int refresh;
	public:
		int dbgx, dbgy, dbgsize, complexity;	// debug
		unsigned long int dbgbin;
		bool success;
		Generator(){
			/* this->box = CreateCube();
			PaintEntity(this->box, LoadMaterial("abstract::concrete.mat"));
			PositionEntity(this->box, Vec3(0,300,0)); */
			debug_string = "";
			refresh = 0;
			dbgx = 0;	// debug
			dbgy = 0;	// debug
			dbgbin = 0;	// debug
			dbgsize = 0;
			complexity = 25;
			success = false;
		}
	private:
		void setTile(coord pos, bool deadend = false);
		/* TMesh copyTile(); */
		bool getTileStatus(int x, int y);
		unsigned long int get8Sweep(int x, int y);
		void generateTile(int x, int y, int suunta);
		bool checkBoundaries(coord pos);
		coord cOff(coord pos, int palikka, int suunta);
		void clearTile(int x, int y);
	public:
		void initialize();
		void debugDeadendSet();
		coord Tcoord(int x, int y);
		void generateDungeon();
		void clearDungeon();
		void setComplexity(bool add);
};
#endif
