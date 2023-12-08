--a = 6 + 3 + math.sin(45)
--a = a + 400 * 10


function MoveTo(a , b, c)


  print("Inside moveto ("..a..","..b.." ,"..c..") Function call")

    local temp1 , temp2 , temp3  = MoveTransform(a ,b ,c )
    temp1 = a + 100
    temp2 = b + 10
    temp3 = c + 10

  return  temp1 , temp2 , temp3

end


