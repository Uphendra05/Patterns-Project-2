
     
  
--SetGameObject("BALL")
--BeginCommand("SERIES", 2)
-- MoveTo(0,5,0,1)
-- --OrientTo(360,90,0,5)
--Endcommand(2)  


SetGameObject("SHIP")
BeginCommand("SERIES",3)

         MoveTo(50,-2.5,-12,4)

        FollowWithTime(4)
        AddPoint(50,-2.5,-12,    20,0,0)
        AddPoint(50,-2.5,-32,    20,0,0)
    SetLookAtBool(1)


        SetLookAtOffset(0,-90,0)
       
        MoveTo(-30,-2.5,-32,4)
       
        FollowWithTime(4)
        AddPoint(-30,-2.5,-32,      -20,0,0)
        AddPoint(-30, -2.5, -12,    -20,0,0)
    SetLookAtBool(1)

        SetLookAtOffset(0,90,0)
        

Endcommand(2)

SetGameObject("SHIP")
BeginCommand("PARALLEL",3)

WaitForSeconds(0.8)
OrientTo(15,180,0,0.4)
WaitForSeconds(0.5)
OrientTo(0,180,0,0.4)

Endcommand(2)
  
---------------------------------------------------------
SetGameObject("ENEMYSHIP")
BeginCommand("SERIES",3)

MoveTo(-50,-2.5,12,4)

    FollowWithTime(4)
    AddPoint(-50,-2.5,12,    -20,0,0)
    AddPoint(-50,-2.5,32,    -20,0,0)
    SetLookAtBool(1)

    SetLookAtOffset(0,90,0)

    MoveTo(30,-2.5,32,4)

    FollowWithTime(4)
    AddPoint(30,-2.5,32,    20,0,0)
    AddPoint(30,-2.5,12,    20,0,0)
    SetLookAtBool(1)

    SetLookAtOffset(0,-90,0)

Endcommand(2)

SetGameObject("ENEMYSHIP")
BeginCommand("PARALLEL",3)


WaitForSeconds(0.8)
OrientTo(15,0,0,0.4)
WaitForSeconds(0.5)
OrientTo(0,0,0,0.4)



Endcommand(2)
 
SetGameObject("SHARK")
BeginCommand("SERIES",3)



    FollowWithTime(6)
    AddPoint(0,-25,-120,    0,25,0)
    AddPoint(0,-30,120,    0,25,0)
    SetLookAtBool(0)
    --SetLookAtOffset(0,180,0)

   -- OrientTo(0,180,0,0);

   

Endcommand(2)
  




