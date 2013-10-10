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
		Log("Valid "..name)
		return true
	end
end

function RegisterGlobal()
	XLSetGlobal("Log", Log)
	XLSetGlobal("Warn", Warn)
	XLSetGlobal("Check", Check)
end