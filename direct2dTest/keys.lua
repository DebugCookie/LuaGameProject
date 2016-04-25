left = false
up = false
down = false
right = false




function LeftPressed()--Left
	left = true
end
function LeftReleased()
	left = false
end

function RightPressed()--Right
	right = true
end
function RightReleased()
	right = false
end

function UpPressed()--Up
	up = true
end
function UpReleased()
	up = false
end

function DownPressed()--Down
	down = true
end
function DownReleased()
	down = false
end

function APressed()--A
	left = true
end
function AReleased()
	left = false
end

function DPressed()--D
	right = true
end
function DReleased()
	right = false
end

function WPressed()--W
	up = true
end
function WReleased()
	up = false
end

function SPressed()--S
	down = true
end
function SReleased()
	down = false
end

function EscPressed()--Esc

	player:toggleVisableBB()
end
function EscReleased()
	
end

