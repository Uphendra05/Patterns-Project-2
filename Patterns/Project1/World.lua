
SetGameObject("Sphere2")
BeginCommand("SERIAL",1)  -- First param as string ->(SERIAL or PARALLEL) |  second param ->  A unique group ID required
MoveTo(5,0,0,1)
MoveTo(2,0,0,2)
MoveTo(10,11,0,3)
MoveTo(-6,2,0,2)
MoveTo(0,0,0,1)
Endcommand(1)



SetGameObject("Sphere3")
BeginCommand("SERIAL",2)  -- First param as string ->(SERIAL or PARALLEL) |  second param ->  A unique group ID required
MoveTo(-10,0,0,2)
MoveTo(-3,-2,1,2)
Endcommand(2)