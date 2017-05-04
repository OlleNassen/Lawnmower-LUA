grid = {}
for x = 0, 25 do
    grid[x] = {}
    for y = 0, 20 do
        grid[x][y] = 0
    end
end

function setTile(x, y, type)
	grid[x][y] = type
end

function saveToFile()
	save(grid)
end