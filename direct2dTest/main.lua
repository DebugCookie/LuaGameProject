require "keys"
require "Object"
require "level"

player = Object.New("sprites/magnemite.png")
player:addDefaultAnimation()

player:setTextureOffset(-11, -10)
player:setSize(11, 11)
player:setPos(300,200)





function createObject(gridX, gridY, texturePath)
	bob = Object.New(texturePath)
	bob:setPos(gridX * 10, gridY * 10)
end

function createWall(texturePath, st_gridX, st_gridY, end_gridX, end_gridY)
	print("")

--	print("nrOfWalls b_adding: " .. level.nrOfWalls)
	level.nrOfWalls = level.nrOfWalls + 1
--	print("nrOfWalls a_adding: " .. level.nrOfWalls)

	level.walls[level.nrOfWalls] = Object.New(texturePath)
	level.walls[level.nrOfWalls]:setPos(st_gridX * 10, st_gridY * 10)
	level.walls[level.nrOfWalls]:setSize(10 * (end_gridX - st_gridX) + 10, (end_gridY - st_gridY) * 10 + 10)


end

function wallCollision()
	for key, value in pairs(level.walls) do
		player:setCollision(value)
	end
--	for i = 1, level.nrOfWalls do
--		player:setCollision(level.walls[i])
--	end
end


--createWall("transparent.png", 6,6,6,6)
createWall("transparent.png", 0, 0, 60, 0)
createWall("transparent.png", 0, 0, 0, 40)
createWall("transparent.png", 0, 39, 60, 39)
createWall("transparent.png", 59, 0, 59, 40)

local justPressed = {}


function update()


	if right or D then
		player:goRight()
		wallCollision()
	end
	if left or A then
		player:goLeft()
		wallCollision()
	end
	if up or W then
		player:goUp()
		wallCollision()
	end
	if down or S then
		player:goDown()
		wallCollision()
	end

	if leftMouse and not justPressed.leftMouse then
		local x,  y = getMousePos()
		createWall("default.png", x/10, y/10, x/10, y/10)
		justPressed.leftMouse = true
	elseif not leftMouse and justPressed.leftMouse then
		justPressed.leftMouse = false
	end


	if rightMouse and not justPressed.rightMouse then
		print("")
		print("pressed rightMouse")
		justPressed.rightMouse = true
		local removed = false
		local mouseX, mouseY = getMousePos()
		local loops = 1
		local toDelete

		for key, value in pairs(level.walls) do
			if (value:pointCollision(mouseX, mouseY)) and not removed then
				toDelete = level.walls[key]:getIndex()
		--		print("toDel:" .. toDelete)
				removed = true
			end
		end

		if removed then
			level.walls[toDelete]:destroy(toDelete)
			for i = toDelete, level.nrOfWalls-1 do
				level.walls[i] = level.walls[i+1]
				level.walls[i]:setIndex(level.walls[i]:getIndex()-1)
			end
			level.walls[level.nrOfWalls] = nil
		--	print("nrOfWalls b_removing: " .. level.nrOfWalls)
			level.nrOfWalls = level.nrOfWalls - 1
		--	print("nrOfWalls a_removing: " .. level.nrOfWalls)
		end


		
	elseif not rightMouse and justPressed.rightMouse then
		justPressed.rightMouse = false
	end


end


