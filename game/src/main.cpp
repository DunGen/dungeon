#include <irrlicht.h>
#include <iostream>
#include <string>

using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace io;
using namespace gui;

using namespace std;

IrrlichtDevice* device;
IVideoDriver* driver;
ISceneManager* smgr;


IAnimatedMeshSceneNode* getModel(ISceneManager* smgr, IVideoDriver* drv);


int main() {	
	device = createDevice(EDT_SOFTWARE, dimension2d<u32>(1024, 768), 16,
		false, false, false, 0);
	
	device->setWindowCaption(L"Dungeon.");
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();
	
	
	IAnimatedMeshSceneNode* node = getModel(smgr, driver);
	
	smgr->addCameraSceneNode(0, vector3df(10,5,-5), vector3df(0,0,0));
	
	while(device->run()) {
		if(driver->beginScene(true, true, SColor(255,100,101,140))) {
			smgr->drawAll();
			driver->endScene();
		} else { std::cout << "Could not begin scene." << std::endl; }
	}
	
	device->drop();
 	return 0;
}

IAnimatedMeshSceneNode* getModel(ISceneManager* smgr, IVideoDriver* drv) {
	//load mesh
	IAnimatedMesh* mesh = smgr->getMesh("../model/box.obj");
	
	//set mesh to new node
	IAnimatedMeshSceneNode* node = smgr->addAnimatedMeshSceneNode(mesh);
	
	//if node is created, add some texture on it
	if(node) {
		node->setMaterialFlag(EMF_LIGHTING, false);
		//node->setMaterialTexture(0,drv->getTexture("../model/kuva2.bmp"));
		//node->setMaterialType( EMT_SOLID );
		node->setMaterialFlag(EMF_BACK_FACE_CULLING, false);
		node->setMaterialFlag(EMF_FRONT_FACE_CULLING, false);
		std::cout << "node ok\n";
	}
	
	return node;
}
