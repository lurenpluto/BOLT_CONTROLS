local bitmap = {}
local path = __document
local index = string.find(path, "/[^/]*$")
local currentFolder = string.sub(path,1,index)
local xlgraphic = XLGetObject("Xunlei.XLGraphic.Factory.Object")
local dirIconPath = currentFolder.."../res/default/bitmap/folder.png"
local dirIcon = xlgraphic:CreateBitmap(dirIconPath, "ARGB32")
bitmap.dir = dirIcon
local exeIconPath = currentFolder.."../res/default/bitmap/exe.png"
local exeIcon = xlgraphic:CreateBitmap(exeIconPath, "ARGB32")
bitmap.exe = exeIcon
local luaIconPath = currentFolder.."../res/default/bitmap/lua.png"
local luaIcon = xlgraphic:CreateBitmap(luaIconPath, "ARGB32")
bitmap.lua = luaIcon
local rarIconPath = currentFolder.."../res/default/bitmap/rar.png"
local rarIcon = xlgraphic:CreateBitmap(rarIconPath, "ARGB32")
bitmap.rar = rarIcon
local jsIconPath = currentFolder.."../res/default/bitmap/js.png"
local jsIcon = xlgraphic:CreateBitmap(jsIconPath, "ARGB32")
bitmap.js = jsIcon
local dllIconPath = currentFolder.."../res/default/bitmap/dll.png"
local dllIcon = xlgraphic:CreateBitmap(dllIconPath, "ARGB32")
bitmap.dll = dllIcon
local txtIconPath = currentFolder.."../res/default/bitmap/txt.png"
local txtIcon = xlgraphic:CreateBitmap(txtIconPath, "ARGB32")
bitmap.txt = txtIcon

function getFileExtention(path)
	if string.sub(path, -4, -1) == ".exe" then
		return "exe"
	elseif string.sub(path, -4, -1) == ".cpp" then
		return "cpp"
	elseif string.sub(path, -4, -1) == ".lua" then
		return "lua"
	elseif string.sub(path, -3, -1) == ".js" then
		return "js"
	elseif string.sub(path, -4, -1) == ".rar" or string.sub(path, -4, -1) == ".zip" then
		return "rar"
	elseif string.sub(path, -4, -1) == ".dll" then
		return "dll"
	elseif string.sub(path, -4, -1) == ".txt" then
		return "txt"
	end
end
	

function CreateNodeObject(data,key)
	local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
	local object = objFactory:CreateUIObject(nil, "TreeView.Node")
	local textObject = object:GetObject("text")
	local text = ""
	local isDir = false
	if type(data) == "table" then
		text = data.path
		isDir = data.isDir
	else
		text =data
	end
	textObject:SetText(text)
	
	local imageObject = object:GetObject("icon")
	if isDir then
		imageObject:SetBitmap(bitmap.dir)
	else
		local ext = getFileExtention(text)
		imageObject:SetBitmap(bitmap[ext])
	end
	local size = {width=math.ceil(string.len(text)*10)+20,height=20}
	return object,size
end

-- clinet method
-- expected method:SetLinePoint
function CreateLineObject()
	local objFactory = XLGetObject("Xunlei.UIEngine.ObjectFactory")
	local line = objFactory:CreateUIObject(nil, "LineObject")
	line:SetVisible(true)
	line:SetLinePenResID("pen.dot")
	line:SetLineColorResID("system.black")
	line:SetObjPos2(0,0, "father.width", "father.height")
	return line
end

function GetCustomItemFactory(tree)
	local itemFactory = {}
	itemFactory.CreateNodeObject = CreateNodeObject
	itemFactory.CreateLineObject = CreateLineObject
	return itemFactory
end