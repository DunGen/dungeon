#include "control.h"
void Control::SpawnControl(TCamera *cam){
	//camera = cam;
	EntityParent(*cam, dummy);
	PositionEntity(dummy, Vec3(50,10,45));
	RotateEntity(*cam, Vec3(45,0,0));
}
void Control::CameraControl(){		
	if (KeyDown(KEY_W))
		MoveEntity(dummy,Vec3(0,0,AppSpeed()*0.2*wasdnopeus));
	if (KeyDown(KEY_D)) 
		MoveEntity(dummy,Vec3(AppSpeed()*0.2*wasdnopeus,0,0));
	if (KeyDown(KEY_A)) 
		MoveEntity(dummy,Vec3(AppSpeed()*-0.2*wasdnopeus,0,0));
	if (KeyDown(KEY_S)) 
		MoveEntity(dummy,Vec3(0,0,AppSpeed()*-0.2*wasdnopeus));
	if (KeyDown(KEY_Q)) 
		TurnEntity(dummy,Vec3(0,AppSpeed()*1.4*wasdnopeus,0),1);
	if (KeyDown(KEY_E)) 
		TurnEntity(dummy,Vec3(0,AppSpeed()*-1.4*wasdnopeus,0),1);
	if (MouseZ() > mousekorkeus) 
		TranslateEntity(dummy,Vec3(0,2*AppSpeed(),0));	
	if (MouseZ() < mousekorkeus)
		TranslateEntity(dummy,Vec3(0,-2*AppSpeed(),0));

	wasdnopeus = (KeyDown(KEY_LSHIFT))? 2 : 1 ;
	mousekorkeus = MouseZ();
}