#include "generator.h"
#include <iostream>
#include <string>
#include <cstdlib>

/**
 * Asettaa tilen
 *
 * @param pos			coord structina tilen koordinaatit arrayssä ( ja kentällä )
 * @param deadend		onko tile umpikuja, eli lisätäänkö se deadend_settiin
 */
void Generator::setTile(coord pos, bool deadend){
	if(this->checkBoundaries(pos) == false)
		return;
	if(this->getTileStatus(pos.x, pos.y) == true)
		this->clearTile(pos.x, pos.y);

	this->tile[pos.x][pos.y].x = pos.x;
	this->tile[pos.x][pos.y].y = pos.y;
	this->tile[pos.x][pos.y].set = true;
	/* this->tile[pos.x][pos.y].mesh = this->copyTile(); */
	/* PositionEntity(this->tile[pos.x][pos.y].mesh,Vec3(pos.x,0,pos.y)); */

	if(deadend == true)
		this->deadend_set.insert(pos);
}
/**
 * Tyhjentää tilen
 *
 * @param x			tilen x koordinaatti arrayssä
 * @param y			tilen y koordinaatti arrayssä
 */
void Generator::clearTile(int x, int y){
	/* if(this->tile[x][y].mesh == NULL)
		return;

	FreeEntity(this->tile[x][y].mesh); 
	this->tile[x][y].mesh = NULL; */
	this->tile[x][y].set = false;
	this->tile[x][y].x = 0;
	this->tile[x][y].y = 0;
}
/**
 * Asettaa muodostettavan dungeonin mutkikkuuden ( atm ei tee mitään )
 *
 * @param add		true = kasvatetaan mutkikkuutta nostamalla complexityn arvoa
 */
void Generator::setComplexity(bool add){
	this->complexity = (add == true)?this->complexity+1:this->complexity-1;
	this->complexity = (this->complexity > 50)?50:this->complexity;
	this->complexity = (this->complexity < 5)?5:this->complexity;
}
/**
 * Tarkistaa ettei liikuta tile arrayn ulkopuolella
 *
 * @param pos		tarkastettava koordinaatti coordina
 */
bool Generator::checkBoundaries(coord pos){
	return (pos.x < 0 || pos.x > 99 || pos.y < 0 || pos.y > 99)?false:true;
}
/**
 * Tarkastaa onko näissä koordinaateissa palanen dungeonia vai tyhjyyttä
 *
 * @param x			tile arrayn x koordinaatti
 * @param y			tile arrayn y koordinaatti
 * @return			true jos osa dungeonia
 */
bool Generator::getTileStatus(int x, int y){
	return this->tile[x][y].set;
}
/**
 * Ottaa instancen kuutiomodelista
 *
 * @param pos			coord structina tilen koordinaatit arrayssä ( ja kentällä )
 * @param deadend		onko tile umpikuja, eli lisätäänkö se deadend_settiin
 * @return				palauttaa TMesh meshinä instancen kuutiosta
 */
 /*
TMesh Generator::copyTile(){
	return CopyEntity(this->box);
}
*/

/**
 * Antaa feikki 8bit binäärinä annetun tilen ympärillä olevien tilejen statuksen
 *
 * @param x				..
 * @param y				..
 * @return				1 = tile on palanen dungeonia / 0 = tyhjää
 */
unsigned long int Generator::get8Sweep(int x, int y){
	unsigned long int result = 0;

	result = (this->getTileStatus(x,y+1))?		result:result+10000000;
	result = (this->getTileStatus(x+1,y+1))?	result:result+1000000;
	result = (this->getTileStatus(x+1,y))?		result:result+100000;
	result = (this->getTileStatus(x+1,y-1))?	result:result+10000;
	result = (this->getTileStatus(x,y-1))?		result:result+1000;
	result = (this->getTileStatus(x-1,y-1))?	result:result+100;
	result = (this->getTileStatus(x-1,y))?		result:result+10;
	result = (this->getTileStatus(x-1,y+1))?	result:result+1;
	return result;
}
/**
 * Tekee dungeonin lähtökohdan, eli 5 tilen kokoisen raksin, jonka ulokkeet ovat umpikujia
 *
 */
void Generator::initialize(){
	coord pos[5];
	pos[0].x = 49;		pos[0].y = 50;
	pos[1].x = 51;		pos[1].y = 50;
	pos[2].x = 50;		pos[2].y = 49;
	pos[3].x = 50;		pos[3].y = 51;
	pos[4].x = 50;		pos[4].y = 50;

	for(int i=0; i<=3; i++){
		this->setTile(pos[i]);
		this->deadend_set.insert(pos[i]);
	}
	
	this->setTile(pos[4]);
}
/**
 * Muodostaa debug_stringin sisällön. Sisältö päivitetään joka 50. ruudunpäivitys
 *
 */
void Generator::debugDeadendSet(){
	this->refresh++;
	if(this->refresh < 50){
		//DrawText(30,30, "%s", this->debug_string.c_str());
		return;
	}
	//DrawText(30,30, "%s", this->debug_string.c_str());
	this->debug_string.erase();
	this->refresh = 0;
	std::string string;
	int run = 0;
	std::set<coord>::iterator it;
	char buffer[50];

	for(it = this->deadend_set.begin(); it != this->deadend_set.end(); it++){
		int itx = it->x;
		int ity = it->y;

		//sprintf(buffer,"%i,%i\n",itx,ity);
		this->debug_string.append(buffer);

		//DrawText (30,600+run,"%i,%i", itx, ity);
		
		//run = run+18;
	}
}
/**
 * Muodostaa annetuista integereistä coordin ja palauttaa sen
 *
 * @param x				..
 * @param y				..
 * @return				coord
 */
Generator::coord Generator::Tcoord(int x, int y){
	coord pos;
	pos.x = x;
	pos.y = y;
	return pos;
}
/**
 * Ottaa randomilla yhden deadend_setin umpikujista ja selvittää minkä tyyppinen umpikuja on kyseessä.
 * Tämän jälkeen annetaan kyseisen umpikujan koordinaatit ja umpikujatyyppi generateTile-funktiolle.
 */
void Generator::generateDungeon(){
	if(this->deadend_set.empty())
		return;

	int randm = rand() % this->deadend_set.size();
	std::set<coord>::iterator it;
	it = this->deadend_set.begin();
	advance(it,randm);

	unsigned long int sweep = this->get8Sweep(it->x, it->y);
	this->dbgx = it->x;		// debug
	this->dbgy = it->y;		// debug
	this->dbgbin = sweep;	// debug
	
	switch(sweep){
		case 11100110:
		case 10110111:
		case 11110110:
		case 10110110:
		case 11100111:
		case 11110011:
		case 11100011:
			this->generateTile(it->x, it->y, 1);			// ╔═╗
			break;
		case 10111001:
		case 11101101:
		case 10111101:
		case 10101101:
		case 11111001:
		case 11111100:
		case 11111000:										// ╗
			this->generateTile(it->x, it->y, 2);			// ╝
			break;
		case 1101110:
		case 1111011:
		case 1101111:
		case 1101011:
		case 111111:
		case 1111110:
		case 111110:
			this->generateTile(it->x, it->y, 3);			// ╚═╝
			break;
		case 10011011:
		case 11011110:
		case 11011011:
		case 11011010:
		case 11001111:
		case 10011111:
		case 10001111:										// ╔
			this->generateTile(it->x, it->y, 4);			// ╚
			break;
		case 11110111:										// ╔═╗
			this->generateTile(it->x, it->y, 5);			// ║ ║
			break;
		case 11111101:										// ══╗
			this->generateTile(it->x, it->y, 6);			// ══╝
			break;
		case 1111111:										// ║ ║
			this->generateTile(it->x, it->y, 7);			// ╚═╝
			break;
		case 11011111:										// ╔══
			this->generateTile(it->x, it->y, 8);			// ╚══
			break;
	}
}
/**
 * Generoi annettujen tietojen perusteella tietyn tyyppisen mutkan/suoran.
 *
 * @param x				..
 * @param y				..
 * @param suunta		Umpikujan tyyppi:
 *						1 = 1 tile ylös, 2 = 1 tile oikealle, 3 = 1 tile alas, 4 = 1 tile vasemmalle
						5-8 = sama suuntajärjestys kuin 1-4 mutta vähintään 2:n tilen suora, eli voidaan generoida mutka / risteys jatkamaan sitä.
 */
void Generator::generateTile(int x, int y, int suunta){
	coord pos = Tcoord(x,y);
	// vanhan tilen poisto setistä
	this->deadend_set.erase(Tcoord(x,y));

	switch(suunta){
		case 1:
			y++;
			break;
		case 2:
			x++;
			break;
		case 3:
			y--;
			break;
		case 4:
			x--;
			break;
		case 5:
		case 6:
		case 7:
		case 8:
			this->setTile(this->cOff(pos,0,suunta));

			int randomi = rand()%50;
			if(randomi >= 2 && randomi <= 40)
				this->setTile(this->cOff(pos,1,suunta), true);
			else if(randomi > 40 && randomi <= 45)
				this->setTile(this->cOff(pos,2,suunta), true);
			else if(randomi > 45 && randomi <= 50)
				this->setTile(this->cOff(pos,3,suunta), true);
			else{
				this->setTile(this->cOff(pos,1,suunta), true);
				this->setTile(this->cOff(pos,2,suunta), true);
				this->setTile(this->cOff(pos,3,suunta), true);
			}

			this->dbgsize = this->deadend_set.size();
			return;
	}
	this->setTile(Tcoord(x,y));
	this->deadend_set.insert(Tcoord(x,y));

	this->dbgsize = this->deadend_set.size();
	if (this->deadend_set.size() > 25)
		this->success = true;
}
/**
 * Apufunktio jolla tuntuvasti lyhennetään generateTile() pituutta. Annetun suunnan ja palikan perusteella palauttaa..
 * .. saatana tätä funktiota on vaikea selittää.
 *
 * @param pos			..
 * @param palikka		0-3 -> dir arrayn toinen ulottuvuus
 * @param suunta		(5-9)-5 -> dir arrayn ensimmäinen ulottuvuus
 */
Generator::coord Generator::cOff(coord pos, int palikka, int suunta){
	coord dir[4][4];
	dir[0][0].x = 0;	dir[1][0].x = 1;
	dir[0][0].y = 1;	dir[1][0].y = 0;
	dir[0][1].x = 0;	dir[1][1].x = 2;
	dir[0][1].y = 2;	dir[1][1].y = 0;
	dir[0][2].x = -1;	dir[1][2].x = 1;
	dir[0][2].y = 1;	dir[1][2].y = 1;
	dir[0][3].x = 1;	dir[1][3].x = 1;
	dir[0][3].y = 1;	dir[1][3].y = -1;
	for(int i=0; i<=3; i++){
		dir[2][i].x = -dir[0][i].x;
		dir[2][i].y = -dir[0][i].y;
	}
	for(int i=0; i<=3; i++){
		dir[3][i].x = -dir[1][i].x;
		dir[3][i].y = -dir[1][i].y;
	}

	return Tcoord(pos.x+dir[suunta-5][palikka].x, pos.y+dir[suunta-5][palikka].y);
}
/**
 * Tyhjentää kerralla koko tile-arrayn, deadend_setin ja debug-arvot. Sen jälkeen alustaa uuden dungeonin alun initialize():lla
 *
 */
void Generator::clearDungeon(){
	this->deadend_set.clear();
	this->dbgbin = 0;
	this->dbgsize = 0;
	this->dbgx = 0;
	this->dbgy = 0;

	for(int x=0; x<=99; x++){
		for(int y=0; y<=99; y++){
			this->clearTile(x, y);
		}
	}

	this->initialize();
}
