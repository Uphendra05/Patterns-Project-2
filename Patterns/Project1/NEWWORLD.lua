
     
  
--SetGameObject("BALL")
--BeginCommand("SERIES", 2)
-- MoveTo(0,5,0,1)
-- --OrientTo(360,90,0,5)
--Endcommand(2)  


SetGameObject("SHIP")
BeginCommand("SERIES",3)

MoveTo(7,-2.5,-12,4)

Endcommand(2)

SetGameObject("SHIP")
BeginCommand("PARALLEL",3)

OrientTo(9,180,0,1)
WaitForSeconds(1)

OrientTo(-9,180,0,1)
WaitForSeconds(1)

OrientTo(9,180,0,1)
WaitForSeconds(1)

OrientTo(-9,180,0,1)
WaitForSeconds(1)


Endcommand(2)
  
---------------------------------------------------------
SetGameObject("ENEMYSHIP")
BeginCommand("SERIES",3)

MoveTo(-7,-2.5,12,4)

Endcommand(2)

SetGameObject("ENEMYSHIP")
BeginCommand("PARALLEL",3)

OrientTo(9,0,0,1)
WaitForSeconds(1)

OrientTo(-9,0,0,1)
WaitForSeconds(1)

OrientTo(9,0,0,1)
WaitForSeconds(1)

OrientTo(-9,0,0,1)
WaitForSeconds(1)


Endcommand(2)
 
  




