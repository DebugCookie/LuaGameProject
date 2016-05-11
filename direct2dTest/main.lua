require "keys"
require "Object"
require "level"

player = Object.New("sprites/magnemite.png")
player:addDefaultAnimation()

player:setTextureOffset(-11, -10)
player:setSize(11, 11)
player:setPos(level.startPos[1], level.startPos[2])

firstclick = true
newWallPosX, newWallPosY = 0


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
	level.walls[level.nrOfWalls]:setSize(10 * (end_gridX - st_gridX), (end_gridY - st_gridY) * 10)


end

function wallCollision()
	for key, value in pairs(level.walls) do
		player:setCollision(value)
	end
end


--createWall("transparent.png", 6,6,6,6)
--createWall("sprites/wall.png", 0, 0, 60, 0)
--createWall("sprites/wall.png", 0, 0, 0, 40)
--createWall("sprites/wall.png", 0, 39, 60, 39)
--createWall("sprites/wall.png", 59, 0, 59, 40)

local justPressed = {}
local objTypes = {}
local mode = {}

objTypes.wall = function()
	if leftMouse and firstclick then
		newWallPosX, newWallPosY = getMousePos()
		firstclick = false
--[[	elseif not leftMouse and not firstclick then
		local x, y = getMousePos()
		createWall("sprites/wall.png", newWallPosX/10, newWallPosY/10, x/10, y /10)
		firstclick = true--]]
	end
end
objTypes.player = function()
	local x,  y = getMousePos()
	level.startPos[1] = x
	level.startPos[2] = y
	player:setPos(x, y)
end
objTypes.goal = function()
	local x,  y = getMousePos()
	level.goalPos[1] = x
	level.goalPos[2] = y
end

mode.menu = function()
	
end

mode.play = function()

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

	if player:pointCollision(level.goalPos[1], level.goalPos[2]) then
		print("WIN!!!!!!!!!!")
	end
end

local currentCreateObj = objTypes.wall

nrOfSaves = 0

mode.edit = function()
	
	if I then
		level:save()
		nrOfSaves = nrOfSaves +1
		print("saved " .. nrOfSaves .. " nr of times")
	end

	if A and not justPressed.A then--toggle between wall, playerStartPos and goal
		justPressed.A = true
		if currentCreateObj == objTypes.wall then
			print("set goal")
			currentCreateObj = objTypes.goal
		elseif currentCreateObj == objTypes.goal then
			print("set startPos")
			currentCreateObj = objTypes.player
		elseif currentCreateObj == objTypes.player then
			print("create wall")
			currentCreateObj = objTypes.wall
		end
	elseif not A and justPressed.A then
		justPressed.A = false
	end

	if W and not justPressed.W then
		justPressed.W = true
		level:load()
	elseif not W and justPressed.W then
		justPressed.W = false
	end

	if leftMouse and not justPressed.leftMouse then
		justPressed.leftMouse = true
		currentCreateObj()
	elseif not leftMouse and justPressed.leftMouse then--when leftMouse is released
		justPressed.leftMouse = false
			if not leftMouse and not firstclick then
				local x, y = getMousePos()
				if x < newWallPosX then
					local temp = x
					x = newWallPosX
					newWallPosX = temp
				end
				if y < newWallPosY then
					local temp = y
					y = newWallPosY
					newWallPosY = temp
				end

				if newWallPosX < x and newWallPosY < y then
					createWall("sprites/wall.png", newWallPosX/10, newWallPosY/10, x/10, y /10)
				elseif newWallPosX == x and newWallPosY == y then
					createWall("sprites/wall.png", newWallPosX/10, newWallPosY/10, x/10 + 1, y /10 + 1)
				end
				firstclick = true
		end
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


local currentMode = mode.play

function update()

	currentMode()
	
	if F1 and not justPressed.F1 then
	justPressed.F1 = true
	if currentMode == mode.play then
		print("--edit mode--")
		currentMode = mode.edit
	else
		print("--play mode--")
		currentMode = mode.play
	end
	elseif not F1 and justPressed.F1 then
		justPressed.F1 = false
	end

	if esc and not justPressed.esc then
	justPressed.esc = true
	player:toggleVisableBB()
		for key, value in pairs(level.walls) do
			value:toggleVisableBB()
		end
	elseif not esc and justPressed.esc then
		justPressed.esc = false
	end

	

end


