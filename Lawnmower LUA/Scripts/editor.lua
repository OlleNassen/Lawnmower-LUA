grid = {}
for x = 1, 20 do
    grid[x] = {}
    for y = 1, 25 do
        grid[x][y] = 1
    end
end

function setTile(x, y, type)
	grid[y][x] = type
end

function getGrid(x)
	return grid[x]
end

function saveToFile()
	save(grid)
end