level = {}
level.startPos = {210,210}
level.goalPos = {400,400}
level.walls = {}
level.nrOfWalls = 0

function level:save()
	
	local file = io.open("aLevel.thistypedoesnotexist" , "w")
	io.input(file)
	
	file:write(self.startPos[1] .. "\n" .. self.startPos[2] .. "\n")
	file:write(self.goalPos[1] .. "\n" .. self.goalPos[2].. "\n")

	file:write(self.nrOfWalls .. "\n")

	for key, value in pairs(self.walls) do
		file:write(value:getPosX() .. "\n" .. value:getPosY() .. "\n")
		file:write(value:getSizeX() .. "\n" .. value:getSizeY() .. "\n")
	end


	io.close(file)
end

function level:load()
	
	local file = io.open("aLevel.thistypedoesnotexist" , "r")
	io.input(file)

	self.startPos = {file:read(), file:read()}
	self.goalPos = {file:read(), file:read()}
	local nrOfWalls = file:read()

	for i = 1, nrOfWalls do
		local x = file:read()/10
		local y = file:read()/10
		createWall("sprites/wall.png", x, y, file:read()/10 + x, file:read()/10 + y)
	end
	player:setPos(self.startPos[1], self.startPos[2])
	io.close(file)
end