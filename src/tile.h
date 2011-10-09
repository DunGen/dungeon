#include <set>
#include <irrlicht.h>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

#ifndef TILE_H
#define TILE_H
/**
 * 3D-tileluokka
 *
 * Tämä ylläpitää pelin aikana nähtäviä 3d-tilejä
 */
class Tile {
	private:
		IAnimatedMesh* tile[3];
		ISceneManager* smgr;
		std::set<IAnimatedMeshSceneNode*> entity;
	public:
		Tile() {};
		Tile(ISceneManager* psmgr);
};

//muista:
//node[0]->setPosition(core::vector3df(2,0,0));

#endif
