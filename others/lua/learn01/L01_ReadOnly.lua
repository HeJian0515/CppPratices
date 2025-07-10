function readOnly(t)
    local proxy = {}
    local mt = {
        __index = t,
        __newindex = function(tbl, key, value)
            error("attempt to update a read-only table", 2)
        end
    }
    setmetatable(proxy, mt)
    return proxy
end

-- 使用示例
local config = readOnly({
    width = 800,
    height = 600
})

print(config.width)  -- 输出 800
config.width = 1000  -- 触发错误：attempt to update a read-only table