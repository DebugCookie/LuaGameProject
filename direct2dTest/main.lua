require "keys"
require "Object"
print("qwek")
player = Object.New("sprites/magnemite.png") --player atm

player:setTextureOffset(-11, -10)
player:setSize(11, 11)
player:setPos(300,200)

player:addDefaultAnimation()



function update()

	if right then
		player:goRight()
	end
	if left then
		player:goLeft()
	end
	if up then
		player:goUp()
	end
	if down then
		player:goDown()
	end

	player:setCollision(bob2)
	player:setCollision(wall0)
	player:setCollision(wall1)
	player:setCollision(wall2)
	player:setCollision(wall3)
end


