
function LeftPressed()
	bob:setPos(bob:getPosX() - 0.01, bob:getPosY())
end

function RightPressed()
	bob:setPos(bob:getPosX() + 0.01, bob:getPosY())
end

function UpPressed()
	bob:setPos(bob:getPosX(), bob:getPosY() - 0.01)
end

function DownPressed()
	bob:setPos(bob:getPosX(), bob:getPosY() + 0.01)
end

function APressed()
	bob:setPos(bob:getPosX() - 0.01, bob:getPosY())
end

function DPressed()
	bob:setPos(bob:getPosX() + 0.01, bob:getPosY())
end

function WPressed()
	bob:setPos(bob:getPosX(), bob:getPosY() - 0.01)
end

function SPressed()
	bob:setPos(bob:getPosX(), bob:getPosY() + 0.01)
end
