--region table.pack和table.unpack

-- table.pack将传入的参数打包成一个table
--[[ local packedTable = table.pack(1, 2, 3, "hello", true)
print(packedTable[1])  -- 输出: 1
print(packedTable[4])  -- 输出: hello
print(packedTable.n)    -- 输出: 5 (参数的数量)
 ]]

-- table.unpack将table中的元素解包成独立的值
local my_table = {1, 2, 3, 4, 5}
local a, b, c, d, e = table.unpack(my_table)
print(a, b, c, d, e)  -- 输出: 1 2 3 4 5

--endregion