
delayTimeScene1 =6
delayTimeScene2 =12
delayTimeScene3 =18
delayTimeScene4 =25

function Scene1()
	-- body

     SetGameObject("SPACESHIP")
     BeginCommand("SERIAL",3) 
     MoveTo(1,1,0,0.2)
     OrientTo(-40,0,0,0.2)
     MoveTo(11,1,-30,.5)
     OrientTo(40,0,0,0.1,1)
     MoveTo(35,1,20,.5,1)
     --OrientTo(-20,0,0,0.1,1)
     --MoveAlongAxisWithTime(1,5,5)
      MoveTo(250,1,200,.5,1)
     Endcommand(3)
     
     -- ASTEROIDGROUP1 movement
     SetGameObject("ASTEROIDGROUP1")
     BeginCommand("SERIAL", 2)
     MoveAlongAxisWithTime(1,5.5,-5)
     Endcommand(2)
     
     -- ASTEROIDGROUP2 movement
     SetGameObject("ASTEROIDGROUP2")
     BeginCommand("SERIAL", 2)
     MoveAlongAxisWithTime(1,5.5,-10)
     Endcommand(2)
     
     -- ASTEROIDGROUP3 movement
     SetGameObject("ASTEROIDGROUP3")
     BeginCommand("SERIAL", 2)
     MoveAlongAxisWithTime(1,5.5,-16)
     Endcommand(2)
     
     
     SetGameObject("ASTEROID1")
     BeginCommand("PARALLEL", 2)
     MoveTo(-40,-1,2,2)
     OrientTo(360,90,0,5)
     Endcommand(2)
     
     SetGameObject("ASTEROID2")
     BeginCommand("PARALLEL", 2)
     MoveTo(-60,-1,-40,3.1)
     OrientTo(360,90,0,5)
     Endcommand(2)
     
     SetGameObject("ASTEROID4")
     BeginCommand("PARALLEL", 2)
     MoveAlongAxisWithTime(1,3,-35)
     OrientTo(360,90,0,5)
     Endcommand(2)
     
     SetGameObject("ASTEROID3")
     BeginCommand("PARALLEL", 2)
     MoveAlongAxisWithTime(1,3,-20)
     OrientTo(360,90,0,5)
     Endcommand(2)  
end




function Scene2()
	-- body

    --RESETING previous sequences models
   
       SetGameObject("ASTEROIDGROUP1")
       BeginCommand("SERIAL",1) 
       WaitForSeconds(delayTimeScene1)
       ScaleTo(0,0,0,0)
       SetGameObject("ASTEROIDGROUP2")
       ScaleTo(0,0,0,0)
       SetGameObject("ASTEROIDGROUP3")
       ScaleTo(0,0,0,0)
       SetGameObject("ASTEROID1")
       ScaleTo(0,0,0,0)
       SetGameObject("ASTEROID2")
       ScaleTo(0,0,0,0)
       SetGameObject("ASTEROID3")
       ScaleTo(0,0,0,0)
       SetGameObject("ASTEROID4")
       ScaleTo(0,0,0,0)
       Endcommand(1)

    --- DEFAULT POSITION AND ROTATION VALUES
       SetGameObject("SPACESHIP")
       BeginCommand("SERIAL",1) 

        WaitForSeconds(delayTimeScene1)

        MoveTo(-2, 6,3,0)
        OrientTo(40, 90,0,0)
        ScaleTo(0.02,0.02,0.02,0)

        SetGameObject("ASTEROID16")
        MoveTo(8, 2, -15,0)
        OrientTo(90, 90, 0,0)
        ScaleTo( 0.044, 0.044, 0.044, 0)

        SetGameObject("DIRECTIONLIGHT")
        OrientTo(-80, 0, 90,0)
        Endcommand(1)


      SetGameObject("SPACESHIP")
      BeginCommand("SERIAL",1)  -- First param as string ->(SERIAL or PARALLEL) |  second param ->  A unique group ID required
      WaitForSeconds(delayTimeScene1)
      MoveTo(-1,5,-1,1.9,0.2,0.9)
      MoveTo(13,1,-40, 1,0.8,0.2)
      Endcommand(1)
      
      
      SetGameObject("SPACESHIP")
      BeginCommand("PARALLEL",1)  -- First param as string ->(SERIAL or PARALLEL) |  second param ->  A unique group ID required
      WaitForSeconds(delayTimeScene1)
      OrientTo(70,90,-40,2,0.5,0.4)
      WaitForSeconds(2)
      OrientTo(60,70,-30,.3,0.1,0.5)
      WaitForSeconds(.2)
      OrientTo(-60,70,30,.9, 0.5,0.2)
      Endcommand(1)

    
    
      SetGameObject("ASTEROID16")
      BeginCommand("PARALLEL", 2)
      WaitForSeconds(delayTimeScene1)
      MoveTo(30,2,80,10)
      OrientTo(-360,360,0,10)
      Endcommand(2)
    --  
    --  
     SetGameObject("FIGHTER1")
     BeginCommand("SERIAL",2) 
     WaitForSeconds(delayTimeScene1)

     WaitForSeconds(2)
     MoveTo(-1,5,-5,1.9)
     MoveTo(13,1,-45, 1)
     Endcommand(2)
      
      
      SetGameObject("FIGHTER1")
      BeginCommand("PARALLEL",2) 
      WaitForSeconds(delayTimeScene1)

      WaitForSeconds(2)
      OrientTo(90,-60,0,2)
      WaitForSeconds(2)
      OrientTo(70,-60,0,.3)
      WaitForSeconds(.2)
      OrientTo(70,-10,30,.3)
      Endcommand(2)
    --
    ----------------------------------------
    --
    --
      SetGameObject("FIGHTER2")
      BeginCommand("SERIAL",2) 
      WaitForSeconds(delayTimeScene1)

      WaitForSeconds(2)
      MoveTo(0,-1,-13,1.9)
      MoveTo(13,-1,-45, 1)
      Endcommand(2)
     
     
     SetGameObject("FIGHTER2")
     BeginCommand("PARALLEL",2) 
     WaitForSeconds(delayTimeScene1)

     WaitForSeconds(2)
     OrientTo(90,-60,0,2)
     WaitForSeconds(2)
     OrientTo(70,-60,0,.3)
     WaitForSeconds(.2)
     OrientTo(70,-10,30,.3)
     Endcommand(2)
     
     ------------------------------------------
     
     SetGameObject("FIGHTER3")
     BeginCommand("SERIAL",2) 
     WaitForSeconds(delayTimeScene1)

     WaitForSeconds(2)
     MoveTo(-1,2,-2, 1.9)
     MoveTo(13,2,-45, 1)
     Endcommand(2)
     
     
     SetGameObject("FIGHTER3")
     BeginCommand("PARALLEL",2) 
     WaitForSeconds(delayTimeScene1)

     WaitForSeconds(2)
     OrientTo(90,-60,0,2)
     WaitForSeconds(2)
     OrientTo(70,-60,0,.3)
     WaitForSeconds(.2)
     OrientTo(70,-10,30,.3)
     Endcommand(2)
     
     
     SetGameObject("FIGHTER4")
     BeginCommand("SERIAL",2) 
     WaitForSeconds(delayTimeScene1)

     WaitForSeconds(2)
     MoveTo(-1,5,-9,1.9)
     MoveTo(13,5,-45, 1)
     Endcommand(2)
    
    
     SetGameObject("FIGHTER4")
     BeginCommand("PARALLEL",2) 
     WaitForSeconds(delayTimeScene1)

     WaitForSeconds(2)
     OrientTo(90,-60,0,2)
     WaitForSeconds(2)
     OrientTo(70,-60,0,.3)
     WaitForSeconds(.2)
     OrientTo(70,-10,30,.3)
     Endcommand(2)
 end


 function Scene3()
	-- body
     --RESETING TO to DEFAULT 
     SetGameObject("FIGHTER1")
     BeginCommand("SERIAL",2) 

     WaitForSeconds(delayTimeScene2)
      ScaleTo(0,0,0,0)
      SetGameObject("FIGHTER2")
      ScaleTo(0,0,0,0)
      SetGameObject("FIGHTER3")
      ScaleTo(0,0,0,0)
      SetGameObject("FIGHTER4")
      ScaleTo(0,0,0,0)
      SetGameObject("ASTEROID16")
      ScaleTo(0,0,0,0)
      SetGameObject("SPACESHIP")
      ScaleTo(0,0,0,0)

     Endcommand(2)


      SetGameObject("FIGHTER5")
      BeginCommand("SERIAL",2) 
      WaitForSeconds(delayTimeScene2)

      MoveTo(8, 1.0, -13,1)
      Endcommand(2)
      
      SetGameObject("FIGHTER5")
      BeginCommand("PARALLEL",2) 
      WaitForSeconds(delayTimeScene2)

      OrientTo(90,0,20,2)
      WaitForSeconds(.4)
      MoveTo(8, -1.0, -50,1)
      Endcommand(2)
      
      SetGameObject("FIGHTER6")
      BeginCommand("SERIAL",2) 
      WaitForSeconds(delayTimeScene2)
      MoveTo(8, 0.0, -11,1)
      Endcommand(2)
      
      SetGameObject("FIGHTER6")
      BeginCommand("PARALLEL",2) 
      WaitForSeconds(delayTimeScene2)
      OrientTo(90,0 ,10,.3)
      WaitForSeconds(.4)
      MoveTo(17,0.0,-45,1)
      Endcommand(2)
      
      
      SetGameObject("FIGHTER7")
      BeginCommand("SERIAL",2)
      WaitForSeconds(delayTimeScene2)
      MoveTo(5, 1.0, -50,2)
      Endcommand(2)
      
      SetGameObject("FIGHTER7")
      BeginCommand("PARALLEL",2) 
      WaitForSeconds(delayTimeScene2)

      OrientTo(90,0 ,10,.3)
      Endcommand(2)
      
      
      SetGameObject("FIGHTER8")
      BeginCommand("SERIAL",2) 
      WaitForSeconds(delayTimeScene2)

      MoveTo(8,0.0,-23,4)
      Endcommand(2)
      
      
      SetGameObject("FIGHTER8")
      BeginCommand("PARALLEL",2) 
      WaitForSeconds(delayTimeScene2)

      OrientTo(90,0 ,10,.3)
      Endcommand(2)
      
      
      SetGameObject("ASTEROID5")
      BeginCommand("PARALLEL",2) 
      WaitForSeconds(delayTimeScene2)

      MoveTo(0,-20 ,0, 4)
      Endcommand(2)
end

  function Scene4( ... )

  -- RESETING TO 0 to make it invisible
  SetGameObject("FIGHTER5")
     BeginCommand("SERIAL",2) 
     WaitForSeconds(delayTimeScene3)
      ScaleTo(0,0,0,0)
      SetGameObject("FIGHTER6")
      ScaleTo(0,0,0,0)
      SetGameObject("FIGHTER7")
      ScaleTo(0,0,0,0)
      SetGameObject("FIGHTER8")
      ScaleTo(0,0,0,0)
      SetGameObject("ASTEROID5")
      ScaleTo(0,0,0,0)
     Endcommand(2)

     SetGameObject("ASTEROID40") 
     BeginCommand("PARALLEL",1) 
     WaitForSeconds(delayTimeScene3)
     MoveTo(0,20 ,0, 14) 
     OrientTo(360,90,0,4) 
     OrientTo(270,90,0,4) 
     Endcommand(1)

     SetGameObject("ASTEROID6") 
     BeginCommand("PARALLEL",1) 
     WaitForSeconds(delayTimeScene3)
     MoveTo(0,20 ,20, 14) 

     OrientTo(270,90,0,4) 
     Endcommand(1)
     
     SetGameObject("ASTEROID7") 
     BeginCommand("PARALLEL",1) 
     WaitForSeconds(delayTimeScene3)
     MoveTo(0,-20 ,20, 14) 
     Endcommand(1)
     
     SetGameObject("SPACESHIP2") 
     BeginCommand("SERIAL",1) 
     WaitForSeconds(delayTimeScene3)
     MoveTo(16, -2 ,-20, 2) 
     
     Endcommand(1)
     
     SetGameObject("SPACESHIP2") 
     BeginCommand("PARALLEL",1) 
     WaitForSeconds(delayTimeScene3)
     OrientTo(-60,90,0,.5)
     WaitForSeconds(.7)
     MoveTo(-30, -3 ,-20, 2) 
     
     OrientTo(-90,90,0,.5)
     WaitForSeconds(.2)
     
     OrientTo(-20,90,0,.5)
     
     Endcommand(1)

     SetGameObject("ASTEROID8") 
     BeginCommand("PARALLEL",1) 
     WaitForSeconds(delayTimeScene3)
     WaitForSeconds(1)
     MoveTo(20, 20 ,0, 2) 

   OrientTo(-60,90,0,.5)


   OrientTo(-20,90,0,.5)


   --SetGameObject("FIGHTER9") 
   --BeginCommand("SERIAL",1) 
   --WaitForSeconds(delayTimeScene3)
   --
  ----MoveTo(20, 20 ,0, 2) 
   --
   --
   --Endcommand(1)

  SetGameObject("FIGHTER9")
  BeginCommand("PARALLEL",1) 
  WaitForSeconds(delayTimeScene3)
  MoveTo(5, 0 ,-30, 2)
  WaitForSeconds(1.5)
  OrientTo(0,0,-360,1)
  MoveTo(7, 3 ,-45, 1) 
   Endcommand(1)

   SetGameObject("FIGHTER10")
   BeginCommand("PARALLEL",1) 
   WaitForSeconds(delayTimeScene3)
   MoveTo(5, -2 ,-45, 2.5)
   Endcommand(1)

   SetGameObject("FIGHTER11")
   BeginCommand("PARALLEL",1) 
   WaitForSeconds(delayTimeScene3)
   MoveTo(5, 8 ,-45, 2.5)
   Endcommand(1)
 
end


function Scene5()

     SetGameObject("ASTEROID40")
     BeginCommand("SERIAL",2) 
     WaitForSeconds(delayTimeScene4)
      ScaleTo(0,0,0,0)
      SetGameObject("ASTEROID6")
      ScaleTo(0,0,0,0)
      SetGameObject("ASTEROID7")
      ScaleTo(0,0,0,0)
      SetGameObject("SPACESHIP2")
      ScaleTo(0,0,0,0)
      SetGameObject("ASTEROID8")
      ScaleTo(0,0,0,0)
       SetGameObject("FIGHTER9")
      ScaleTo(0,0,0,0)
      SetGameObject("FIGHTER10")
      ScaleTo(0,0,0,0)
      SetGameObject("FIGHTER11")
      ScaleTo(0,0,0,0)
     Endcommand(2)

     

      SetGameObject("FIGHTER12")
      BeginCommand("PARALLEL",1) 
      WaitForSeconds(delayTimeScene4)
      OrientTo(0,0,720,3)
      Endcommand(1)

      SetGameObject("FIGHTER12")
      
      BeginCommand("SERIAL",1) 
      WaitForSeconds(delayTimeScene4)
       MoveTo(8,2,10,3)
       Endcommand(1)

       SetGameObject("ASTEROID_STATIC")
       BeginCommand("SERIAL",1) 
       WaitForSeconds(delayTimeScene4)
       MoveTo(15,-1.9,22,0)
       Endcommand(1)
      
end



Scene1()

Scene2()

Scene3()

Scene4()

Scene5()