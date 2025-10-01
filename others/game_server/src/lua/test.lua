local test = {}
test.__index = test

function test.new()
    local obj = {}
    setmetatable(obj, test)
    return obj
end

function test:test()
    print("test")
end

return test