#include "engine.h"
#ifndef CONTROL_H
#define CONTROL_H
class Control {
	private:
		int mousekorkeus, wasdnopeus;
		TPivot dummy;
	public:
		Control(){
			mousekorkeus = MouseZ();
			wasdnopeus = 1;
			dummy = CreatePivot();
		}
		void SpawnControl(TCamera *cam);
		void CameraControl();
};
#endif