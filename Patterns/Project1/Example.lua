--a = 6 + 3 + math.sin(45)
--a = a + 400 * 10


function MoveTo(a , b, c)


  print("Inside moveto ("..a..","..b.." ,"..c..") Function call")

    MoveTransform(a ,b ,c )

  return  a, b, c ;

end

function RotateTo(physicObj, rotation, easein, easeout)

  print("Inside RotateTo Function call")
    easein = easein or 0.2
    easeout = easeout or 0.1
    

    return {
        physicObj = physicObj,
        rotation = rotation,
        easein = easein,
        easeout = easeout,
      
    }
end
