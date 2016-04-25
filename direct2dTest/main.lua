require "keys"
require "Object"
print("qwek")
bob = Object.New("sprites/magnemite.png") --player atm
bob:setTextureOffset(-11, -10)
bob:setSize(11, 11)

bob:addDefaultAnimation()

pie = Object.New("sprites/pinkiePie.png")
pie:setSize(32, 32)
pie:addDefaultAnimation()
pie:setPos(20, 20)


function update()
	print(bob:collision(pie))

	if right then
		goRight()
	end
	if left then
		goLeft()
	end
	if up then
		goUp()
	end
	if down then
		goDown()
	end
end


