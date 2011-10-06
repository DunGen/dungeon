#include "generatorset.h"
Generatorset::coord Generatorset::Tcoord(int x, int y){
    coord pos;
    pos.x = x;
    pos.y = y;
    return pos;
}
int Generatorset::getDeadendSize(){
    return this->deadend_set.size();
}
int Generatorset::getTilesetSize(){
    return this->tile_set.size();
}
void Generatorset::addTile(coord pos, bool deadend){
    this->tile_set.insert(pos);

    if(deadend == true)
	this->deadend_set.insert(pos);
}
void Generatorset::removeTile(coord pos){
    this->tile_set.erase(pos);
}
void Generatorset::initialize(){
    coord pos[5];
    pos[0].x = 49;	pos[0].y = 50;
    pos[1].x = 51;	pos[1].y = 50;
    pos[2].x = 50;	pos[2].y = 49;
    pos[3].x = 50;	pos[3].y = 51;
    pos[4].x = 50;	pos[4].y = 50;

    for(int i=0; i<=3; i++){
	this->addTile(pos[i]);
	this->deadend_set.insert(pos[i]);
    }
	
    this->addTile(pos[4]);
}
void Generatorset::buildMeshes(){
    std::set<coord> temp;
    std::set<coord>::iterator it;
    int round = 0;
    for(it = this->tile_set.begin(); it != this->tile_set.end(); it++){
	PositionEntity(this->copyTile(), Vec3(it->x,0,it->y));
	temp.insert(*it);
	round++;
	if(round > 50*AppSpeed())
	    break;
    }
    for(it = temp.begin(); it != temp.end(); it++){
	this->tile_set.erase(*it);
    }
}
TMesh Generatorset::copyTile(){
    TMesh temp = CopyEntity(this->box);
    EntityOcclusionMode(temp,0);
    return temp;
}
bool Generatorset::getTileStatus(coord pos){
    return (this->tile_set.count(pos) == 1)?true:false;
}
unsigned long int Generatorset::get8Sweep(coord pos){
    unsigned long int result = 0;

    result = (this->getTileStatus(Tcoord(pos.x,pos.y+1)))?	result:result+10000000;
    result = (this->getTileStatus(Tcoord(pos.x+1,pos.y+1)))?    result:result+1000000;
    result = (this->getTileStatus(Tcoord(pos.x+1,pos.y)))?	result:result+100000;
    result = (this->getTileStatus(Tcoord(pos.x+1,pos.y-1)))?    result:result+10000;
    result = (this->getTileStatus(Tcoord(pos.x,pos.y-1)))?	result:result+1000;
    result = (this->getTileStatus(Tcoord(pos.x-1,pos.y-1)))?    result:result+100;
    result = (this->getTileStatus(Tcoord(pos.x-1,pos.y)))?	result:result+10;
    result = (this->getTileStatus(Tcoord(pos.x-1,pos.y+1)))?    result:result+1;
    return result;
}
void Generatorset::generateDungeon(){
    if(this->deadend_set.empty())
	return;

    int randm = rand() % this->deadend_set.size();
    std::set<coord>::iterator it;
    it = this->deadend_set.begin();
    advance(it,randm);

    unsigned long int sweep = this->get8Sweep(*it);
	
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
	case 11111000:							// ╗
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
	case 10001111:							// ╔
	    this->generateTile(it->x, it->y, 4);			// ╚
	    break;
	case 11110111:							// ╔═╗
	    this->generateTile(it->x, it->y, 5);			// ║ ║
	    break;
	case 11111101:							// ══╗
	    this->generateTile(it->x, it->y, 6);			// ══╝
	    break;
	case 1111111:							// ║ ║
	    this->generateTile(it->x, it->y, 7);			// ╚═╝
	    break;
	case 11011111:							// ╔══
	    this->generateTile(it->x, it->y, 8);			// ╚══
	    break;
	default:
	    this->deadend_set.erase(*it);
    }
}
void Generatorset::generateTile(int x, int y, int suunta){
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
	    this->addTile(this->cOff(pos,0,suunta));

	    int randomi = rand()%50;
	    if(randomi >= 5 && randomi <= 40)
		this->addTile(this->cOff(pos,1,suunta), true);
	    else if(randomi > 40 && randomi <= 45)
		this->addTile(this->cOff(pos,2,suunta), true);
	    else if(randomi > 45 && randomi <= 50)
		this->addTile(this->cOff(pos,3,suunta), true);
	    else{
		this->addTile(this->cOff(pos,1,suunta), true);
		this->addTile(this->cOff(pos,2,suunta), true);
		this->addTile(this->cOff(pos,3,suunta), true);
	    }
	    return;
    }
    this->addTile(Tcoord(x,y));
    this->deadend_set.insert(Tcoord(x,y));

}
Generatorset::coord Generatorset::cOff(coord pos, int palikka, int suunta){
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