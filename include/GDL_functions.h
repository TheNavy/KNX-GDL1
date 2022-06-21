void setDoorScene(){

  // If Motor Active (via KNX Input) but not yet recognised 
  if ((doorMoving) && (!doorStatus)  && (!doorDisable)) {
    doorStatus = true;
    startMillis = millis(); //Time when DoorMovement has started  
  }

  // If Motor active
  if (doorStatus) {
    unsigned long currentMillis = millis();
    // Animation Door Movement
    Knx.write(COMOBJ_scene_out, sceneMove);
    if (currentMillis - startMillis >= doorDeadTime) { // If Door-Runtime >= doorDeadTime
      if (Door == down) { //If Door close
        doorStatus = false;
        doorDisable = true;
        doorStatusMillis = millis();
            Knx.write(COMOBJ_scene_out, sceneClose);
      } else if (Door == up) { //If Door open
        doorStatus = false;
        doorDisable = true;
        doorStatusMillis = millis();
        Knx.write(COMOBJ_scene_out, sceneOpen);
      } else if (currentMillis - startMillis >= doorMoveTime) { // Movement Time exeed
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
    if (currentMillis - doorStatusMillis >= doorMotorDeadTime) { // If DoorDeadTime is exeed
      doorDisable = false;
    }
  }
}
