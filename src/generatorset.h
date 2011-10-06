#include "engine.h"
#include <set>
#ifndef GENERATORSET_H
#define GENERATORSET_H
class Generatorset {
	private:
		struct Grid_tile{
			TMesh mesh;
			unsigned short x, y;
			bool set;
			Grid_tile(): x(0), y(0), set(false), mesh(NULL){}
		};
		struct coord{
			int x,y;
			coord():x(0),y(0){}
			bool operator<(const coord &a) const{
				return ((x < a.x) ||((x == a.x) && (y < a.y)));
			}
		};
		TMesh box;
		std::set<coord> tile_set;
		std::set<coord> deadend_set;
	public:
		Generatorset(){
			this->box = CreateCube();
			EntityOcclusionMode(this->box, 0);
			PaintEntity(this->box, LoadMaterial("abstract::concrete.mat"));
			PositionEntity(this->box, Vec3(0,300,0));
		}
	private:
		void addTile(coord pos, bool deadend = false);
		void removeTile(coord pos);
		TMesh copyTile();
		bool getTileStatus(coord pos);
		unsigned long int get8Sweep(coord pos);
		void generateTile(int x, int y, int suunta);
		coord cOff(coord pos, int palikka, int suunta);
	public:
		void initialize();
		void buildMeshes();
		coord Tcoord(int x, int y);
		void generateDungeon();
		int getDeadendSize();
		int getTilesetSize();
};
#endif