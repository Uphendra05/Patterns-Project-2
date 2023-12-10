



BeginCommand("SERIAL",1)  -- First param as string ->(SERIAL or PARALLEL) |  second param ->  A unique group ID required
MoveTo(0,5,0,1)
MoveTo(0,7,0,3)
MoveTo(0,11,0,4)
MoveTo(0,2,0,3)
MoveTo(0,0,0,10)
Endcommand(1)

--BeginCommand("PARALLEL",2)  -- First param as string ->(SERIAL or PARALLEL) |  second param ->  A unique group ID required
--MoveTo(7,1,3)
--MoveTo(6,7,3)
--MoveTo(8,3,3)
--MoveTo(4,4,3)
--Endcommand(2) -- Always need to end with the Group ID specified in BeginCommand




