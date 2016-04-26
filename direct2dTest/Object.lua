function Object:addDefaultAnimation()
	for i = 1, 4 do
		local state = self:addSpriteState()
		self:addToSpriteState(0, 32*(i-1), 32, 32, state)
		self:addToSpriteState(32, 32*(i-1), 32, 32, state)
		self:addToSpriteState(64, 32*(i-1), 32, 32, state)
		self:addToSpriteState(32, 32*(i-1), 32, 32, state)
	end
end



function Object:goLeft()
	self:setPos(self:getPosX() - 100 * dt, self:getPosY())
	self:setSpriteState(1)
end

function Object:goUp()
	self:setPos(self:getPosX(), self:getPosY() - 100 * dt)
	self:setSpriteState(3)
end

function Object:goRight()
	self:setPos(self:getPosX() + 100* dt, self:getPosY())
	self:setSpriteState(2)
end

function Object:goDown()
	self:setPos(self:getPosX(), self:getPosY() + 100 * dt)
	self:setSpriteState(0)
end

function Object:setCollision(wall)
	if right then

		if self:collision(wall) then
			self:setPos(self:getPosX() - 100 * dt, self:getPosY())
		end
	end	

	if left then
		if self:collision(wall) then
			self:setPos(self:getPosX() + 100 * dt, self:getPosY())
		end
	end	

	if up then
		if self:collision(wall) then
			self:setPos(self:getPosX() , self:getPosY()+ 100 * dt)
		end
	end	

	if down then
		if self:collision(wall) then
			self:setPos(self:getPosX(), self:getPosY() - 100 * dt)
		end
	end	



end