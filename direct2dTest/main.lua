require "keys"
require "Object"
require "level"
print("qwek")
player = Object.New("sprites/magnemite.png")
player:setAnimated(true)

player:setTextureOffset(-11, -10)
player:setSize(11, 11)
player:setPos(300,200)

player:addDefaultAnimation()





function createObject(gridX, gridY, texturePath)
	bob = Object.New(texturePath)
	bob:addDefaultAnimation()
	bob:setPos(gridX * 10, gridY * 10)
end

function createWall(texturePath, st_gridX, st_gridY, end_gridX, end_gridY)
	level.nrOfWalls = level.nrOfWalls + 1
	level.walls[level.nrOfWalls], i = Object.New(texturePath)
	level.walls[level.nrOfWalls]:setPos(st_gridX * 10, st_gridY * 10)
	level.walls[level.nrOfWalls]:setSize(10 * (end_gridX - st_gridX) + 10, (end_gridY - st_gridY) * 10 + 10)
	level.walls[level.nrOfWalls]:addDefaultAnimation()
	--level.walls[level.nrOfWalls].index = i

end

function wallCollision()
	for i = 1, level.nrOfWalls do
		player:setCollision(level.walls[i])
	end
end


createWall("transparent.png", 6,6,6,6)
createWall("transparent.png", 0, 0, 60, 0)
createWall("transparent.png", 0, 0, 0, 40)
createWall("transparent.png", 0, 39, 60, 39)
createWall("transparent.png", 59, 0, 59, 40)
startX, startY = 0
firstClick = true

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
	if leftMouse and firstClick then
		startX,startY = getMousePos()
		firstClick = false
		
	elseif not leftMouse and not firstClick then
			local x,y = getMousePos()
			createWall("default.png", startX/10, startY/10, x/10, y/10)
			firstClick = true
		end
	if rightMouse then
		local mobj, i = Object.New("transparent.png")
		mobj:addDefaultAnimation()
		mobj:setPos(getMousePos())
		mobj:setSize(20 ,20)
		for key, value in pairs(level.walls) do
			if (mobj:collision(value)) then
				--value:destroy(value.index)
			end
		end
	mobj:destroy(i)
	end
	wallCollision()

end


