void setDoorScene(){
  unsigned long startMillis = 0;
  unsigned long doorStatusMillis = 0;
  if ((doorMoving) && (!doorStatus)  && (!doorDisable)) {
    doorStatus = true;
    startMillis = millis();    
  }

  // If Motor active
  if (doorStatus) {
    unsigned long currentMillis = millis();
    // Animation Door Movement
    Knx.write(COMOBJ_scene_out, sceneMove);
    if (currentMillis - startMillis >= doorDeadTime) {
      if (Door == down) {
        //If Door close
        doorStatus = false;
        doorDisable = true;
        doorStatusMillis = millis();
            Knx.write(COMOBJ_scene_out, sceneClose);
      } else if (Door == up) {
        //If Door open
        doorStatus = false;
        doorDisable = true;
        doorStatusMillis = millis();
        Knx.write(COMOBJ_scene_out, sceneOpen);
      } else if (currentMillis - startMillis >= doorMoveTime) {
        // Movement Time exeed
        doorStatus = false;
        doorDisable = true;
        doorStatusMillis = millis();
        Knx.write(COMOBJ_scene_out, sceneClose);
      }
    }
  }

  // If Door finished but Motor still on
  if (doorDisable) {
    unsigned long currentMillis = millis();
    if (currentMillis - doorStatusMillis >= doorMotorDeadTime) {
      doorDisable = false;
    }else {
      if ((Door == halfOpen) && (lastDoorState == down)) {
        doorStatus = true;
        startMillis = millis();
      }else if ((Door == halfOpen) && (lastDoorState == up)) {
        doorStatus = true;
        startMillis = millis();
      }
      lastDoorState = Door;
    }
  }
}
