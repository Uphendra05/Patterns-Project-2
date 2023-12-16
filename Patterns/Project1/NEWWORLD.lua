
     
  
--SetGameObject("BALL")
--BeginCommand("SERIES", 2)
-- MoveTo(0,5,0,1)
-- --OrientTo(360,90,0,5)
--Endcommand(2)  


SetGameObject("SHIP")
BeginCommand("SERIES",3)

         MoveTo(50,-2.5,-12,4,1,0.5,"SINE","QUAD")

        FollowWithTime(4)
        AddPoint(50,-2.5,-12,    20,0,0)
        AddPoint(50,-2.5,-32,    20,0,0)
    SetLookAtBool(1)


        SetLookAtOffset(0,-90,0)
       
        MoveTo(-30,-2.5,-32,4,1,1,"QUAD","QUAD")
       
        FollowWithTime(4)
        AddPoint(-30,-2.5,-32,      -20,0,0)
        AddPoint(-30, -2.5, -12,    -20,0,0)
    SetLookAtBool(1)

        SetLookAtOffset(0,90,0)
        

Endcommand(2)

SetGameObject("SHIP")
BeginCommand("PARALLEL",3)

WaitForSeconds(0.8)
OrientTo(15,180,0,0.4,0.01,0.01,"QUART","QUART")
WaitForSeconds(0.5)
OrientTo(0,180,0,0.4, 0.02,0.02,"QUINT","QUART")

Endcommand(2)
  
---------------------------------------------------------
SetGameObject("ENEMYSHIP")
BeginCommand("SERIES",3)

MoveTo(-50,-2.5,12,4,1,1,"EXPO","CIRC")

    FollowWithTime(4)
    AddPoint(-50,-2.5,12,    -20,0,0)
    AddPoint(-50,-2.5,32,    -20,0,0)
    SetLookAtBool(1)

    SetLookAtOffset(0,90,0)

    MoveTo(30,-2.5,32,4,1,1,"CIRC","EXPO")

    FollowWithTime(4)
    AddPoint(30,-2.5,32,    20,0,0)
    AddPoint(30,-2.5,12,    20,0,0)
    SetLookAtBool(1)

    SetLookAtOffset(0,-90,0)

Endcommand(2)

SetGameObject("ENEMYSHIP")
BeginCommand("PARALLEL",3)


WaitForSeconds(0.8)
OrientTo(15,0,0,0.4,0.01,0.01,"CIRC","EXPO")
WaitForSeconds(0.5)
OrientTo(0,0,0,0.4,0.02,0.02,"SINE","QUAD" )



Endcommand(2)
 
SetGameObject("SHARK")
BeginCommand("SERIES",3)



    FollowWithTime(15)
    AddPoint(0,-25,-120,    0,27,0)
    AddPoint(0,-30,120,    0,27,0)
     SetLookAtBool(1)
    SetLookAtOffset(0,180,0)
  
   

Endcommand(2)


SetGameObject("Bullet")
BeginCommand("SERIES",3)



   WaitForSeconds(0.9)
   ScaleTo(0.9,0.9,0.9,0)
   
   FollowWithTime(1)
    AddPoint(10,-4.5,12,    0,10,0)
    AddPoint(10,-4.5,-12,    0,10,0)
   


Endcommand(2)

SetGameObject("Bullet2")
BeginCommand("SERIES",3)


   WaitForSeconds(0.9)
   ScaleTo(0.9,0.9,0.9,0)
   
   FollowWithTime(1)
    AddPoint(-11,-4.5,-12,    0,10,0)
    AddPoint(-11,-4.5,12,     0,10,0)
 

Endcommand(2)



SetGameObject("SHARK2")
BeginCommand("SERIES",3)



    FollowWithTime(15)
    AddPoint(0,-25,-80,    0,25,0)
    AddPoint(0,-30,120,    0,25,0)
    
    SetLookAtBool(1)
    SetLookAtOffset(0,180,0)

Endcommand(2)
  


SetGameObject("CAMERA")
BeginCommand("PARALLEL",3)

  MoveTo(91,13,-17,1)
   LookAt("ENEMYSHIP",19)
   
Endcommand(2)

SetGameObject("Seagull")
BeginCommand("SERIES",3)

   FollowObject("SHIP",17, 20,2,1, 2,0,25,1)
   --followGameObjectName,time,speed, acceleration, deceleration, distance, followOffsetX,followOffsetY,followOffsetZ


Endcommand(2)

SetGameObject("SEAGUL2")
BeginCommand("SERIES",3)

   FollowObject("ENEMYSHIP",17, 20,2,1, 2,0,25,1)
   --followGameObjectName,time,speed, acceleration, deceleration, distance, followOffsetX,followOffsetY,followOffsetZ

Endcommand(2)


SetGameObject("BARREL")
BeginCommand("SERIES",3)

SetCollisionTrigger(0)
SpawnObject("BARREL",0.1)
SpawnObject("BARREL2",0.1)
SetGameObject("BARREL2")
--MoveTo(-20,-2,5,0)
OrientTo(90,0,0,5);
SetGameObject("BARREL")
OrientTo(90,0,0,5);  

Endcommand(2)
