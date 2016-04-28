

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
	A = true
end
function AReleased()
	A = false
end

function DPressed()--D
	D = true
end
function DReleased()
	D = false
end

function WPressed()--W
	W = true
end
function WReleased()
	W = false
end

function SPressed()--S
	S = true
end
function SReleased()
	S = false
end

function EscPressed()--Esc

	player:toggleVisableBB()
end
function EscReleased()
	
end

function MouseLeftPressed()
	leftMouse = true
end
function MouseLeftReleased()
	leftMouse = false
end

function MouseRightPressed()
	rightMouse = true
end
function MouseRightReleased()
	rightMouse = false
end