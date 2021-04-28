--Simple Libbase Offset Converter for Game Gaurdian
--It's just Reduces Your Effort by doing the Task Automatically.
--Open Source Code 
--Written By @Rhytm113
--Don't Remove Any Credits.
--Copy Pasters Fuck Off
--© Infinity Creators
local RHM = gg
function HOME()
menu = RHM.multiChoice({
"⚙️Libbase Address > GG Value",
"⚙️GG Value > Libbase Address ",
"📃Credits",
"Exit",},nil," Libbase Converter By Rhythm113")
if menu == nil then else
if menu[1] == true then LIB() end
if menu[2] == true then GG() end
if menu[3] == true then CRD() end
if menu[4] == true then EXIT() end
end
LOL = -1
end
function LIB()
main = RHM.prompt({"Lib Name : ","Offset Address :", "Type (int)"},nil,{"text","text","text"})
super = RHM.getRangesList(main[1])[1].start
rsl = super + main[2]
RHM.addListItems({
[1] = {
address = rsl,
flags = main[3]
}})
RHM.alert("Done. Chk Your Saved List\nBy : @Rhythm113")
print('© Infinity Creators')
os.exit()
end
function GG()
maik = RHM.prompt({"Lib Name : ","Value Address  :"},nil,{"text","text",})
IC = RHM.getRangesList(maik[1])[1].start
ic = maik[2] - IC
local output = string.format("%x", ic)
RHM.alert("Done !\nOffset : 0x"..output.."\nCopied Successfully " )
RHM.copyText("0x"..output.."")
print('© Infinity Creators')
os.exit()
end
function CRD()
RHM.alert("Made By : @Rhythm113\nChannel : @InfinityCreators1\n©Infinity Creators")
end
function EXIT()
print('© Infinity Creators')
os.exit()
end
while true do
if RHM.isVisible(true) then
LOL = 1
RHM.setVisible(false) 
end
RHM.clearResults()
if LOL == 1 then HOME() end
end
