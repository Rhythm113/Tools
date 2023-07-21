--Offsets Converter 2.0
--Author : @Rhythm113
--Copyright Infinity Creators
gg.alert("Offset converter 2.0\nBy: Infinity Creators")
input = gg.prompt({"Lib Name : "},nil,{"text"})
function getBase()
base = gg.getRangesList(input[1])[1].start
end
if pcall(getBase) then 
local output = string.format("%x", base)
gg.alert("Library is found at 0x".. string.upper(output)..". Press ok to collect offsets.")
function getCount()
count = gg.getResultCount()
if count == 0 then 
print('Search Results are empty')
os.exit()
end
results = gg.getResults(count)
end
if pcall(getCount) then
res = {} 
for i = 1 , count do
if (results [i].address - base) < 1 then end
table.insert(res, (string.format("%x", results[i].address - base)))
--if ok < 1 then end
end
local file = io.open("output.txt", "w") -- Change the path as needed
        if file then
            for _, offset in ipairs(res) do
                us = string.upper(offset)
                file:write("0x"..us.. "\n")
            end
            file:close()
            gg.alert("Offsets written to output.txt")
        else
            gg.alert("Failed to open the file for writing.")
        end
print("Offsets written successfully\n© Infinity Creators")
end
else
gg.alert("Library not found. Please check the process & name ")
print('Library error')
end