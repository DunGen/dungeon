/**
 * Dungeon irrlichtille.
 * @author Jari Saaranen <rasaari@pistoke.org>
 * @author Simo Krook
 * @version 2011.1006
 */

#include <iostream>
//#include <string>
#include <irrlicht.h>
#include "generator.h"
#include "tile.h"


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


/* Ohjelman aloituspiste */
int main( int argc, char* argv[]) {
	
	//Alustetaan irrlicht
	device = createDevice(EDT_BURNINGSVIDEO, dimension2d<u32>(1024, 768), 16,
		false, false, false, 0);
	
	//ikkunan otsikko
	device->setWindowCaption(L"Dungeon.");
	
	//videoajuri ja scenemanager
	IVideoDriver* driver = device->getVideoDriver();
	ISceneManager* smgr = device->getSceneManager();

	//lisätään kamera	
	smgr->addCameraSceneNode(0, vector3df(10,5,-5), vector3df(0,0,0));

	//tilekartta
	Tile map = Tile(smgr);


	//lisätään valoa
	ILightSceneNode* light1 = smgr->addLightSceneNode(0, core::vector3df(0,5,0), video::SColorf(0.5f, 1.0f, 0.5f, 0.0f), 800.0f);

	/* Luodaan uusi gridi ja alustetaan se */
	Generator grid;
	grid.initialize();
	grid.generateDungeon();
	
	cout << "Luolasto alustettu" << endl;
	
	//pääsilmukka pyörii niin kauan kun ikkuna on auki
	while(device->run()) {
		//aloitetaan scenen piirtäminen ja täytetään ruutu valitulla värillä
		if(driver->beginScene(true, true, SColor(255,100,101,140))) {
			
			//piirretään objektit
			smgr->drawAll();
			
		//Lopetetaan scenen käsittely tältä kierrokselta	
		driver->endScene();
		
		} else { std::cout << "Could not begin scene." << std::endl; }
	}
	
	//heitetään pois kaikki mitä on ladattu
	device->drop();
 	return 0;
}

