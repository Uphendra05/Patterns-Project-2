



BeginCommand("SERIAL",1)  -- First param as string ->(SERIAL or PARALLEL) |  second param ->  A unique group ID required
OrientTo(0,90,0,5)
MoveTo(0,7,0,3)
MoveTo(0,11,0,4)
MoveTo(0,-5,0,4)
Endcommand(1)

--BeginCommand("PARALLEL",2)  -- First param as string ->(SERIAL or PARALLEL) |  second param ->  A unique group ID required
--MoveTo(0,7,0,5)
--Endcommand(2) -- Always need to end with the Group ID specified in BeginCommand




