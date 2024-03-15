-- local slices = require("slices")
Pair = {}
Pair.__index = Pair

function Set(list)
    local set = {}
    for _, l in ipairs(list) do
        set[l] = true
    end
    return set
end

function Pair.new(x, y)
    local self = setmetatable({}, Pair)
    self.x = x
    self.y = y
    return self
end

function read_stdin()
    local lines = {}
    for line in io.lines() do
        table.insert(lines, line)
    end
    return lines
end

function is_empty_col(col, lines)
    for _, line in ipairs(lines) do
        if line:sub(col, col) ~= '.' then
            return false
        end
    end
    return true
end

function get_empty_cols(lines)
    local res = Set {}
    for i = 1, #lines[1] do
        if is_empty_col(i, lines) then
            res[i] = true
        end
    end
    return res
end

function load_points(lines, weight)
    local empty_cols = get_empty_cols(lines)
    local pts = {}
    local row = 0
    for _, line in ipairs(lines) do
        if not string.find(line, "#") then
            row = row + weight
        else
            local col = 0
            for i = 1, #line do
                if empty_cols[i] ~= nil then
                    col = col + weight
                else
                    if line:sub(i, i) == "#" then
                        table.insert(pts, Pair.new(row, col))
                    end
                    col = col + 1
                end
            end
            row = row + 1
        end
    end
    return pts
end

function my_abs_diff(x, y)
    if x < y then
        return y - x
    end
    return x - y
end

function manhattan_distance(a, b)
    return my_abs_diff(a.x, b.x) + my_abs_diff(a.y, b.y)
end

function get_distances(pts)
    local dists = {}
    for i = 1, #pts do
        for j = i + 1, #pts do
            table.insert(dists, manhattan_distance(pts[i], pts[j]))
        end
    end
    return dists
end

function sum(numbers)
    local sum = 0
    for _, num in ipairs(numbers) do
        sum = sum + num
    end
    return sum
end

function process_lines(lines, weight)
    local pts = load_points(lines, weight)
    local dists = get_distances(pts)
    return sum(dists)
end

local fileLines = read_stdin()
print(process_lines(fileLines, 2))
-- print(process_lines(fileLines, 10))
-- print(process_lines(fileLines, 100))
-- print(process_lines(fileLines, 1000))
print(process_lines(fileLines, 1000000))

