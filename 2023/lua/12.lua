-- https://github.com/0xcacti/aoc-2023/blob/master/12/one.lua
local function mysplit(inputstr, sep)
    if sep == nil then
        sep = "%s"
    end
    local t = {}
    for str in string.gmatch(inputstr, "([^" .. sep .. "]+)") do
        table.insert(t, str)
    end
    return t
end

local function buildElem(mut, split)
    local chunks = {}
    local originalChunks = mysplit(split[2], ",")

    if mut == 1 then
        for i, chunk in ipairs(originalChunks) do
            chunks[i] = tonumber(chunk)
        end
        return {split[1] .. ".", chunks}
    end

    len = #originalChunks * mut
    for i = 1, len do
        local chunk = originalChunks[(i - 1) % #originalChunks + 1]
        chunks[i] = tonumber(chunk)
    end

    local line = ""
    for i = 1, mut - 1 do
        line = line .. split[1] .. "?"
    end

    line = line .. split[1] .. "."

    return {line, chunks}
end

local function parseInput(src, mut)
    -- io.input("input.txt")
    lines = {}
    for i, line in ipairs(src) do
        split = mysplit(line, " ")
        table.insert(lines, buildElem(mut, split))
    end
    return lines
end

local function getNewGroup(group)
    if group == nil or #group <= 1 then -- Adjusted to check for single-element group
        return nil
    end
    newGroup = {}
    for i = 2, #group do
        table.insert(newGroup, group[i])
    end
    return newGroup
end

local memo = {}

local function createKey(line, groups, size)
    local groupsKey = table.concat(groups or {}, ",")
    return line .. ":" .. groupsKey .. ":" .. tostring(size)
end

local function recurse(line, groups, size)
    size = size or 0
    local key = createKey(line, groups, size)
    if memo[key] then
        return memo[key]
    end

    if line == "" or line == nil then
        if (groups == nil or #groups == 0) and (size == 0) then
            memo[key] = 1
            return 1
        end
        memo[key] = 0
        return 0
    end

    local lineSolutions = 0
    local symbols = (line:sub(1, 1) == '?') and {'.', '#'} or {line:sub(1, 1)}

    for _, sym in ipairs(symbols) do
        if sym == '#' then
            lineSolutions = lineSolutions + recurse(line:sub(2), groups, size + 1)
        else
            if size > 0 then
                if groups and #groups > 0 and groups[1] == size then
                    lineSolutions = lineSolutions + recurse(line:sub(2), getNewGroup(groups), 0)
                end
            else
                lineSolutions = lineSolutions + recurse(line:sub(2), groups, 0)
            end
        end
    end

    memo[key] = lineSolutions

    return lineSolutions
end

function solve(lines, mut)
    local lines = parseInput(lines, mut)
    local count = 0
    for i, line in ipairs(lines) do
        ret = recurse(line[1], line[2], 0)
        count = count + ret
    end
    return count
end

function loadInput()
    lines = {}
    for line in io.lines() do
        table.insert(lines, line)
    end
    return lines
end

local lines = loadInput()
print(solve(lines, 1))
print(solve(lines, 5))
