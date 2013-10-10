function Log(log)
	local logClassFactory = XLGetObject("LogClass.Factory")
	local logClass = logClassFactory:CreateInstance()
	logClass:Log("Log:"..log)
end

function Warn(log)
	local logClassFactory = XLGetObject("LogClass.Factory")
	local logClass = logClassFactory:CreateInstance()
	logClass:Warn("!!!"..log.."!!!")
end

function Check(value, name, warnmessage)
	if value == nil then
		if warnmessage then
			Warn("Invalid "..name.." "..warnmessage)
		else
			Warn("Invalid "..name)
		end
		return false
	else
		local type_ = type(value)
		Log("Valid "..name..":"..type_)
		return true
	end
end

function CheckUIObject(value, name)
	if value==nil then
		Warn("Invalid UI "..name)
		return false
	else
		local class = value:GetClass()
		local id = value:GetID()
		Log("class:"..class.." id:"..id.." "..name)
	end
end

local prepend=""
function LogTableTree(_table)
	if _table == nil then return nil end
	if type(_table) ~= "table" then
		Log(prepend.._table)
	end
	if type(_table) == "table" then
		for k,v in pairs(_table) do
			local oldPrepend = prepend
			prepend=prepend..k.."-"
			LogTableTree(v)
			prepend=oldPrepend
		end
	end
end

-- in:Node
function LogNodeTree(node)
	Log(prepend.."Key:"..(node.Key).." Count:"..(#(node.Children)))
	local op = prepend
	prepend = prepend.."---"
	for k,v in pairs(node.Children) do
		LogNodeTree(v)
	end
	prepend = op
end

function RegisterGlobal()
	XLSetGlobal("Log", Log)
	XLSetGlobal("Warn", Warn)
	XLSetGlobal("Check", Check)
	XLSetGlobal("LogTableTree", LogTableTree)
	XLSetGlobal("LogNodeTree", LogNodeTree)
	XLSetGlobal("CheckUIObject", CheckUIObject)
end