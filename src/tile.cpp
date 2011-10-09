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

void Tile::addTile(float x, float y, float z) {
	IAnimatedMeshSceneNode* tempnode = smgr->addAnimatedMeshSceneNode(tile[0]);
	tempnode->setPosition(core::vector3df(x,y,z));
	entity.insert(tempnode);
}

void Tile::removeTile(float x, float y, float z) {
	IAnimatedMeshSceneNode* tempnode = smgr->addAnimatedMeshSceneNode(tile[0]);
	tempnode->setPosition(core::vector3df(x,y,z));
	
	//entity.erase(entity.find(tempnode)); // <-- kaatuu
}
