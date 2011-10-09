#include "tile.h"

/**
 * Tämä konstruktori vaaditaan, että tile-järjestelmä toimisi
 */
Tile::Tile(ISceneManager* psmgr) { 
	smgr = psmgr; 
	tile[0] = smgr->getMesh("mdl/tile.obj");
	//IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(tile[0]); 
	//entity.insert(smgr->addAnimatedMeshSceneNode(tile[0]));
	
}
