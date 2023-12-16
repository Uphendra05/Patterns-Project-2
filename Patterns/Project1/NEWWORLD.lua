
     
  SetGameObject("BALL")
        BeginCommand("SERIES", 2)
       --  MoveTo(0,5,0,1)
         FollowWithTime(7)
         AddPoint(0,2,0, 0,0,0)
         AddPoint(70,2,0, -25,0,0)
         AddPoint(102,2,0, 0,0,25)
        -- AddPoint(-1,7,0, 0,0,0)
         --OrientTo(360,90,0,5)
        Endcommand(2)  
  