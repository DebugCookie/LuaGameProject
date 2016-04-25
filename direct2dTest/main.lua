require "keys"
require "Object"
print("qwek")
player = Object.New("sprites/magnemite.png")
player:setAnimated(true)

player:setTextureOffset(-11, -10)
player:setSize(11, 11)
player:setPos(300,200)

player:addDefaultAnimation()

wall0 = Object.New()
wall0:addDefaultAnimation()
wall0:setSize(600, 10)

wall1 = Object.New()
wall1:addDefaultAnimation()
wall1:setSize(600, 10)
wall1:setPos(0, 390)

wall2 = Object.New()
wall2:addDefaultAnimation()
wall2:setSize(10, 400)

wall3 = Object.New()
wall3:addDefaultAnimation()
wall3:setSize(10, 400)
wall3:setPos(590, 0)

bob2 = Object.New()
bob2:addDefaultAnimation()
bob2:setPos(500, 200)
bob2:setSize(20,20)

function createObject(gridX, gridY)
	bob = Object.New("sprites/pinkiePie.png")
	bob:addDefaultAnimation()
	bob:setPos(gridX * 10, gridY * 10)
end

	createObject(7,7)
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


