position = {x = 200, y = 50}
speed = 4
score = 0

function setPosition(x, y)
	position.x = x
	position.y = y
end

--mx = map x max, my = map y max

function collision(mx, my)
	if position.x > mx -16 then
        position.x = mx - 16
	elseif position.x < 16 then
        position.x = 16
    end
	
    if position.y > my -16 then
        position.y = my - 16
	elseif position.y < 16 then
        position.y = 16
	end

end

function move(delta, verticalDir, horizontalDir)

    if horizontalDir == 'left' then 
        position.x =  position.x - (delta * speed)
    elseif horizontalDir == 'right' then
        position.x = position.x + (delta * speed)
    end

    if verticalDir == 'up' then
        position.y = position.y - (delta * speed)
    elseif verticalDir == 'down' then
        position.y = position.y + (delta * speed)
    end

end

function getPosition()
    return position.x, position.y	
end


function collisionWithPlayer(playerPosx, playerPosy, playerSize)
	local intersection = {x = 0, y = 0}

	if position.x - playerSize / 2 < playerPosx + playerSize / 2 and
		position.x + playerSize / 2 > playerPosx - playerSize / 2 and
		position.y - playerSize / 2 < playerPosy + playerSize / 2 and
		position.y + playerSize / 2 > playerPosy - playerSize / 2 then
		
		intersection.x = (playerPosx + playerSize / 2) - (position.x + playerSize / 2)
		intersection.y = (playerPosy + playerSize / 2) - (position.y + playerSize / 2)
	
		intersection.x = -intersection.x / 8
		intersection.y = -intersection.y / 8

		if math.abs(intersection.x) > math.abs(intersection.y) then
			position.x = position.x + intersection.x
			return true, intersection.x, 0
		else
			position.y = position.y + intersection.y
			return true, 0, intersection.y
		end
		return true, intersection.x, intersection.y
		
	end

	return false, intersection.x, intersection.y
end


function collisionWithTile(tilePosx, tilePosy, tileSize, type)
	local intersection = {x = 0, y = 0}
	
	if position.x - tileSize / 2 < tilePosx + tileSize / 2 and
		position.x + tileSize / 2 > tilePosx - tileSize / 2 and
		position.y - tileSize / 2 < tilePosy + tileSize / 2 and
		position.y + tileSize / 2 > tilePosy - tileSize / 2 then

		if type == 0 then
			return true
		end
	end
	return false
end